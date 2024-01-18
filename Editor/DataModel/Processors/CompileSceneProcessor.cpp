#include <iostream>

#include "../../IGeometryEntry.h"
#include "../../IGroupEntry.h"
#include "../../ILocalizedEntry.h"
#include "../../IMaterialEntry.h"
#include "../../ITransformEntry.h"
#include "../../Messages/CompileFontMessage.h"
#include "../../Messages/SceneCompeledMessage.h"
#include "../../Text.h"
#include "../CompilationState.h"
#include "CompileSceneProcessor.h"

namespace Vandrouka {

void CompileSceneProcessor::ProcessMessage(Ref<IDataModelState> model,
                                           Ref<ICompileSceneMessage> cmd,
                                           Ref<IMessageOutput> sink) {

  if (!model->CanCompile()) {
    sink->SubmitMessage(new SceneCompeledMessage{{}});
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
      sink->SubmitMessage({new SceneCompeledMessage{root}});
    }
  } else if (cmd->GetRoot().GetName() == ROOT_PACKAGES) {
    auto root = model->FindPreviewPackage(cmd->GetRoot().GetNext().GetName());
    if (!root) {
      sink->SubmitError(NotFoundError(cmd->GetRoot().GetNext().GetName()));
      return;
    }
    sink->SubmitMessage(new SceneCompeledMessage{root});
  }
}

vsg::ref_ptr<vsg::Node>
CompileSceneProcessor::Compile(EntryPath path, Ref<ICompilationState> state,
                               EntryRef entry, Ref<IMessageOutput> sink) {
  if (!entry)
    return {};

  if (auto g = entry.Cast<IGeometryEntry>())
    return g->GetGeometry();

  if (auto t = entry.Cast<ITextEntry>()) {
    auto fontName = t->GetFont();

    if (fontName.empty()) {
      return {};
    }

    if (!state->GetFonts()) {
      sink->SubmitError(
          new GenericError(LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND, fontName));
      return {};
    }

    if (auto font = state->FindFont(fontName); !font) {
      sink->SubmitError(
          new GenericError(LOG_LEVEL_ERROR, LOG_ENTRY_NOT_FOUND, fontName));
      return {};
    } else {
      TextConfig cfg;
      cfg.Entry = t;
      cfg.Font = font;
      return CompileText(cfg);
    }
  }

  auto dir = entry.Cast<IDirectoryEntry>();

  if (!dir) {
    std::cerr << "Unexpected entry type "
              << magic_enum::enum_name(entry->GetType()) << std::endl;
    return {};
  }

  vsg::ref_ptr<vsg::Group> group;

  if (auto g = entry.Cast<IGroupEntry>()) {
    group = g->GetGroup();
  }

  if (auto g = entry.Cast<IMaterialEntry>()) {
    group = g->GetState().Value();
  }

  if (auto g = entry.Cast<ITransformEntry>()) {
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

  if (auto localized = dir.Cast<ILocalizedEntry>()) {
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
      e->GetHorizontalAlignment() == TextHorizontalAlignment::Left
          ? vsg::StandardLayout::LEFT_ALIGNMENT
      : e->GetHorizontalAlignment() == TextHorizontalAlignment::Right
          ? vsg::StandardLayout::RIGHT_ALIGNMENT
          : vsg::StandardLayout::CENTER_ALIGNMENT;

  layout->verticalAlignment =
      e->GetVerticalAlignment() == TextVerticalAlignment::Top
          ? vsg::StandardLayout::TOP_ALIGNMENT
      : e->GetVerticalAlignment() == TextVerticalAlignment::Bottom
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
                                         EntryRef entry) {
  if (!entry) {
    return;
  }

  if (auto f = entry.Cast<ITextEntry>()) {
    if (auto fnt = f->GetFont(); !fnt.empty()) {
      state->IncreaseFontCompilationJobs();
      model->GetFonts()->Execute(
          {new CompileFontMessage{fnt, state}});
    }
  }

  if (auto dir = entry.Cast<IDirectoryEntry>(); dir) {
    dir->ForEachEntry(
        [&](auto, auto centry) { CompileFonts(model, state, centry); });
  }
}
} // namespace Vandrouka