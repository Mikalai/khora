#pragma once

#include "ICompilationState.h"

namespace Vandrouka {

class CompilationState
    : public ReferenceCountedBase<CompilationState, ICompilationState> {
public:
  using Interfaces = QueryInterfaces<CompilationState, ICompilationState,
                                     IReferenced>;

  const std::string &GetName() const override { return Name; }
  bool GetShowTransforms() const override { return ShowTransforms; }
  void SetShowTransforms(bool flag) override { ShowTransforms = flag; }
  vsg::ref_ptr<vsg::Node> GetTransformProxy() const override {
    return TransformProxy;
  }
  void SetTransformProxy(vsg::ref_ptr<vsg::Node> value) override {
    TransformProxy = value;
  }
  vsg::ref_ptr<vsg::Node> GetActiveCursor() const override {
    return ActiveCursor;
  }
  void SetActiveCursor(vsg::ref_ptr<vsg::Node> value) override {
    ActiveCursor = value;
  }
  EntryRef GetActiveEntry() const override { return ActiveEntry; }
  void SetActiveEntry(EntryRef entry) override { ActiveEntry = entry; }
  vsg::ref_ptr<vsg::Font> FindFont(const std::string &name) const override {
    if (auto it = UsedFonts.find(name); it != UsedFonts.end()) {
      return it->second;
    }
    return {};
  }

  void AddFont(const std::string &name, vsg::ref_ptr<vsg::Font> font) override {
    UsedFonts[name] = font;
  }

  Ref<ISystemFonts> GetFonts() const override { return Fonts; }

  void SetFonts(Ref<ISystemFonts> fonts) override { Fonts = fonts; }
  EntryRef GetRoot() const override { return Root; }
  void SetRoot(EntryRef entry) override { Root = entry; }
  const EntryPath &GetRootPath() const override { return RootPath; }
  void SetRootPath(const EntryPath &path) override { RootPath = path; }
  const std::string &GetLanguage() const override { return Language; }
  void SetLanguage(const std::string &value) override { Language = value; }

  void IncreaseFontCompilationJobs() override { requestedFontCompilations++; }
  void DecreaseFontCompilationJobs() override { requestedFontCompilations--; }
  bool HasFontCompilationJobs() const override {
    return requestedFontCompilations != 0;
  }
  
  void OnFontCompiled(const std::string &name, vsg::ref_ptr<vsg::Font> font);

private:
  std::string Name = "Final Scene Compilation";
  bool ShowTransforms{false};
  vsg::ref_ptr<vsg::Node> TransformProxy;
  vsg::ref_ptr<vsg::Node> ActiveCursor;
  EntryRef ActiveEntry;
  std::unordered_map<std::string, vsg::ref_ptr<vsg::Font>> UsedFonts;
  Ref<ISystemFonts> Fonts{nullptr};
  EntryRef Root;
  EntryPath RootPath;
  std::string Language;
  int requestedFontCompilations{0};
};

} // namespace Vandrouka