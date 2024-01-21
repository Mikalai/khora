#include <iostream>
#include <magic_enum.hpp>

#include <Text.h>
#include <Catalog/Interface/IGeometryEntry.h>
#include <Catalog/Interface/IGroupEntry.h>
#include <Catalog/Interface/ILocalizedEntry.h>
#include <Catalog/Interface/IMaterialEntry.h>
#include <Catalog/Interface/ITransformEntry.h>
#include <Fonts/Interface/Messages/ICompileFontMessage.h>
#include <State/Module/Messages/SceneCompeledMessage.h>
#include <Fonts/Module/Messages/CompileFontMessage.h>
#include <State/Module/CompilationState.h>
#include "CompileSceneProcessor.h"

namespace Vandrouka::State::Private::Processors {

void CompileSceneProcessor::ProcessMessage(Ref<IDataModelState> model,
                                           Ref<State::Messages::ICompileSceneMessage> cmd,
                                           Ref<IMessageOutput> sink) {

  if (!model->CanCompile()) {
    sink->SubmitMessage(new Messages::SceneCompeledMessage{{}});
    return;
  }

  auto config = model->GetConfig();
  assert(config);

  if (cmd->GetRoot().GetName() == ROOT_SCENE) {
    auto scale = vsg::MatrixTransform::create();
    scale->matrix = vsg::scale(0.01f, 0.01f, 0.01f);
    scale->addChild(model->GetAxis());

    Ref<ICompilationState> state{new CompilationState};
    state->SetShowTransforms(config->GetShowTransform());
    state->SetTransformProxy(scale);
    state->SetActiveCursor(scale);
    state->SetActiveEntry(model->GetActiveEntry());
    state->SetFonts(model->GetFonts());
    state->SetLanguage(config->GetActiveLanguage());
    state->SetRootPath({cmd->GetRoot().GetName()});
    state->SetRoot(model->GetDir()->FindEntry(state->GetRootPath()));

    CompileFonts(model, state, state->GetRoot());

    if (!state->HasFontCompilationJobs()) {
      auto root = Compile(state->GetRootPath(), state, state->GetRoot(), sink);
      sink->SubmitMessage({new Messages::SceneCompeledMessage{root}});
    }
  } else if (cmd->GetRoot().GetName() == ROOT_PACKAGES) {
    auto root = model->FindPreviewPackage(cmd->GetRoot().GetNext().GetName());
    if (!root) {
      sink->SubmitError(CreateError(LOG_ENTRY_NOT_FOUND, cmd->GetRoot().GetNext().GetName()));
      return;
    }
    sink->SubmitMessage(new Messages::SceneCompeledMessage{root});
  }
}

vsg::ref_ptr<vsg::Node>
CompileSceneProcessor::Compile(Catalog::EntryPath path, Ref<ICompilationState> state,
                               Ref<Catalog::IEntry> entry, Ref<IMessageOutput> sink) {
  if (!entry)
    return {};

  if (auto g = entry.Cast<Catalog::IGeometryEntry>())
    return g->GetGeometry();

  if (auto t = entry.Cast<Catalog::ITextEntry>()) {
    auto fontName = t->GetFont();

    if (fontName.empty()) {
      return {};
    }

    if (!state->GetFonts()) {
      sink->SubmitError(CreateError(LOG_ENTRY_NOT_FOUND, fontName));
      return {};
    }

    if (auto font = state->FindFont(fontName); !font) {
      sink->SubmitError(CreateError(LOG_ENTRY_NOT_FOUND, fontName));
      return {};
    } else {
      TextConfig cfg;
      cfg.Entry = t;
      cfg.Font = font;
      return CompileText(cfg);
    }
  }

  auto dir = entry.Cast<Catalog::IDirectoryEntry>();

  if (!dir) {
    std::cerr << "Unexpected entry type "
              << magic_enum::enum_name(entry->GetType()) << std::endl;
    return {};
  }

  vsg::ref_ptr<vsg::Group> group;

  if (auto g = entry.Cast<Catalog::IGroupEntry>()) {
    group = g->GetGroup();
  }

  if (auto g = entry.Cast<Catalog::IMaterialEntry>()) {
    group = g->GetState().Value();
  }

  if (auto g = entry.Cast<Catalog::ITransformEntry>()) {
    group = g->GetTransform().Value();

    if (state->GetShowTransforms() && state->GetTransformProxy()) {
      group->addChild(state->GetTransformProxy());
    }
  }

  assert(group);
  if (!group) {
    std::cerr << "Unexpected directory type "
              << magic_enum::enum_name(entry->GetType()) << std::endl;
    return {};
  }

  if (state->GetActiveEntry() == entry && state->GetActiveCursor()) {
    group->addChild(state->GetActiveCursor());
  }

  if (auto localized = dir.Cast<Catalog::ILocalizedEntry>()) {
    dir->ForEachEntry([&](auto name, auto centry) {
      if (name == state->GetLanguage()) {
        auto child = Compile(path.Append(name), state, centry, sink);
        if (child) {
          group->addChild(child);
        }
      }
    });
  } else {
    dir->ForEachEntry([&](auto name, auto centry) {
      auto child = Compile(path.Append(name), state, centry, sink);
      if (child) {
        group->addChild(child);
      }
    });
  }

  return group;
}
vsg::ref_ptr<vsg::Text> CompileSceneProcessor::CompileText(TextConfig &cfg) {
  auto e = cfg.Entry;
  auto layout = vsg::StandardLayout::create();

  // layout->lineSpacing = e->GetLineSpacing();

  layout->horizontalAlignment =
      e->GetHorizontalAlignment() == Catalog::TextHorizontalAlignment::Left
          ? vsg::StandardLayout::LEFT_ALIGNMENT
      : e->GetHorizontalAlignment() == Catalog::TextHorizontalAlignment::Right
          ? vsg::StandardLayout::RIGHT_ALIGNMENT
          : vsg::StandardLayout::CENTER_ALIGNMENT;

  layout->verticalAlignment =
      e->GetVerticalAlignment() == Catalog::TextVerticalAlignment::Top
          ? vsg::StandardLayout::TOP_ALIGNMENT
      : e->GetVerticalAlignment() == Catalog::TextVerticalAlignment::Bottom
          ? vsg::StandardLayout::BOTTOM_ALIGNMENT
          : vsg::StandardLayout::CENTER_ALIGNMENT;

  layout->position.set((float)e->GetOffsetX(), (float)e->GetOffsetY(),
                       (float)e->GetOffsetZ());

  layout->horizontal.set((float)e->GetHorizontalAxisX(),
                         (float)e->GetHorizontalAxisY(),
                         (float)e->GetHorizontalAxisZ());

  layout->vertical.set((float)e->GetVerticalAxisX(),
                       (float)e->GetVerticalAxisY(),
                       (float)e->GetVerticalAxisZ());

  layout->color.set((float)e->GetColorR(), (float)e->GetColorG(),
                    (float)e->GetColorB(), (float)e->GetColorA());

  auto wstr = utf8_to_wstring(e->GetValue());
  auto text = vsg::Text::create();
  text->text = vsg::wstringValue::create(wstr);
  text->font = cfg.Font;
  text->layout = layout;
  text->setup(0, cfg.Options);
  return text;
}

void CompileSceneProcessor::CompileFonts(Ref<IDataModelState> model,
                                         Ref<ICompilationState> state,
                                         Ref<Catalog::IEntry> entry) {
  if (!entry) {
    return;
  }

  if (auto f = entry.Cast<Catalog::ITextEntry>()) {
    if (auto fnt = f->GetFont(); !fnt.empty()) {
      state->IncreaseFontCompilationJobs();
      model->GetFonts()->Execute(
          {new Fonts::Private::Messages::CompileFontMessage{fnt, state}});
    }
  }

  if (auto dir = entry.Cast<Catalog::IDirectoryEntry>(); dir) {
    dir->ForEachEntry(
        [&](auto, auto centry) { CompileFonts(model, state, centry); });
  }
}
} // namespace Vandrouka::State::Private