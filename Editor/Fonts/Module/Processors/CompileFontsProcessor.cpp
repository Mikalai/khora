#pragma once

#include "CompileFontsProcessor.h"
#include <Fundamental/Module/LongOperationScope.h>
#include <Fonts/Module/Messages/FontCompiledMessage.h>
#include <Fonts/Module/Messages/FontsRefreshCompletedMessage.h>

namespace Vandrouka::Fonts::Private::Processors {

void CompileFontsProcessor::ReportMessage(Ref<IMessage> msg,
                                          Ref<IReferenced> observer,
                                          Ref<IMessageOutput> output) {
  output->SubmitMessage(msg);
}

void CompileFontsProcessor::ProcessMessage(
    Ref<ISystemFontsPrivate> state,
    Ref<Fonts::Messages::ICompileFontMessage> cmd, Ref<IMessageOutput> sink) {

  Fundamental::Private::LongOperationScope scope{
      *sink.Get(), &IMessageOutput::SubmitMessage,
      LongOperation{.Name = "Compile font: " + cmd->GetDisplayName()}};

  if (auto fnt = state->FindCompiledFont(cmd->GetDisplayName()); fnt) {
    ReportMessage(new Messages::FontCompiledMessage{cmd->GetDisplayName(),
                                                    fnt->Font, fnt->Root,
                                                    cmd->GetState()},
                  cmd->GetState(), sink);
    return;
  }

  if (auto fnt = state->FindFontFile(cmd->GetDisplayName()); !fnt) {
    sink->SubmitError(CreateError(LOG_ENTRY_NOT_FOUND, cmd->GetDisplayName()));
    ReportMessage(
        new Messages::FontCompiledMessage{
            cmd->GetDisplayName(), {}, {}, cmd->GetState()},
        cmd->GetState(), sink);
    return;
  } else if (auto object = vsg::read(fnt->Path.string(), state->GetOptions());
             object) {
    if (auto font = object.cast<vsg::Font>(); font) {
      auto scenegraph = vsg::MatrixTransform::create();

      auto layout = vsg::StandardLayout::create();
      layout->position = vsg::vec3(0.0, 0.0, 0.0);
      layout->horizontal = vsg::vec3(1.0, 0.0, 0.0);
      layout->vertical = vsg::vec3(0.0, 1.0, 0.0);
      layout->color = vsg::vec4(1.0, 1.0, 1.0, 1.0);

      std::set<uint32_t> characters;
      for (auto c : *(font->charmap)) {
        if (c != 0)
          characters.insert(c);
      }

      size_t num_glyphs = characters.size();
      size_t row_length = static_cast<size_t>(ceil(sqrt(float(num_glyphs))));

      if (row_length == 0) {
        sink->SubmitError(
            CreateError(LOG_FILE_LOAD_FAILED, cmd->GetDisplayName()));
        return;
      }

      size_t num_rows = num_glyphs / row_length;
      if ((num_glyphs % num_rows) != 0)
        ++num_rows;

      // use an uintArray to store the text string as the full
      // font charcodes can go up to very large values.
      auto text_string = vsg::uintArray::create(num_glyphs + num_rows - 1);
      auto text_itr = text_string->begin();

      size_t i = 0;
      size_t column = 0;

      for (auto c : characters) {
        ++i;
        ++column;

        (*text_itr++) = c;

        if (column >= row_length) {
          (*text_itr++) = '\n';
          column = 0;
        }
      }

      auto text = vsg::Text::create();
      text->font = font;
      text->layout = layout;
      text->text = text_string;
      text->setup(0, state->GetOptions());

      scenegraph->addChild(text);

      state->CacheCompiledFont(cmd->GetDisplayName(),
                               {.Font = font, .Root = scenegraph});

      ReportMessage(new Messages::FontCompiledMessage{cmd->GetDisplayName(),
                                                      font, scenegraph,
                                                      cmd->GetState()},
                    cmd->GetState(), sink);

    } else {
      sink->SubmitError(
          CreateError(LOG_FILE_LOAD_FAILED, cmd->GetDisplayName()));
      ReportMessage(
          new Messages::FontCompiledMessage{
              cmd->GetDisplayName(), {}, {}, cmd->GetState()},
          cmd->GetState(), sink);
    }
  } else {
    sink->SubmitError(CreateError(LOG_FILE_LOAD_FAILED, cmd->GetDisplayName()));
    ReportMessage(
        new Messages::FontCompiledMessage{
            cmd->GetDisplayName(), {}, {}, cmd->GetState()},
        cmd->GetState(), sink);
  }
}

} // namespace Vandrouka::Fonts::Private::Processor
