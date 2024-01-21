#pragma once

#include <State/Interface/ICompilationState.h>
#include <Fundamental/Module/Referenced.h>

namespace Vandrouka::State::Private {

class CompilationState
    : public Fundamental::Private::ReferenceCountedBase<CompilationState, ICompilationState> {
public:
  using Interfaces = Fundamental::Private::QueryInterfaces<CompilationState, ICompilationState,
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
  Catalog::EntryRef GetActiveEntry() const override { return ActiveEntry; }
  void SetActiveEntry(Catalog::EntryRef entry) override { ActiveEntry = entry; }
  vsg::ref_ptr<vsg::Font> FindFont(const std::string &name) const override {
    if (auto it = UsedFonts.find(name); it != UsedFonts.end()) {
      return it->second;
    }
    return {};
  }

  void AddFont(const std::string &name, vsg::ref_ptr<vsg::Font> font) override {
    UsedFonts[name] = font;
  }

  Ref<Fonts::ISystemFonts> GetFonts() const override { return Fonts; }

  void SetFonts(Ref<Fonts::ISystemFonts> fonts) override { Fonts = fonts; }
  Catalog::EntryRef GetRoot() const override { return Root; }
  void SetRoot(Catalog::EntryRef entry) override { Root = entry; }
  const Catalog::EntryPath &GetRootPath() const override { return RootPath; }
  void SetRootPath(const Catalog::EntryPath &path) override { RootPath = path; }
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
  Catalog::EntryRef ActiveEntry;
  std::unordered_map<std::string, vsg::ref_ptr<vsg::Font>> UsedFonts;
  Ref<Fonts::ISystemFonts> Fonts{nullptr};
  Catalog::EntryRef Root;
  Catalog::EntryPath RootPath;
  std::string Language;
  int requestedFontCompilations{0};
};

} // namespace Vandrouka