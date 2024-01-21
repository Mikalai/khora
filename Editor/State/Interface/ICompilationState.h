#pragma once

#include <Fonts/Interface.h>
#include <Catalog/Interface/IEntry.h>

namespace Vandrouka::State {

class ICompilationState : public IReferenced {
public:
  virtual const std::string &GetName() const = 0;
  virtual bool GetShowTransforms() const = 0;
  virtual void SetShowTransforms(bool flag) = 0;
  virtual vsg::ref_ptr<vsg::Node> GetTransformProxy() const = 0;
  virtual void SetTransformProxy(vsg::ref_ptr<vsg::Node> value) = 0;
  virtual vsg::ref_ptr<vsg::Node> GetActiveCursor() const = 0;
  virtual void SetActiveCursor(vsg::ref_ptr<vsg::Node> value) = 0;
  virtual Catalog::EntryRef GetActiveEntry() const = 0;
  virtual void SetActiveEntry(Catalog::EntryRef entry) = 0;
  virtual vsg::ref_ptr<vsg::Font> FindFont(const std::string &name) const = 0;
  virtual void AddFont(const std::string &name,
                       vsg::ref_ptr<vsg::Font> font) = 0;
  virtual Ref<Fonts::ISystemFonts> GetFonts() const = 0;
  virtual void SetFonts(Ref<Fonts::ISystemFonts> fonts) = 0;
  virtual Catalog::EntryRef GetRoot() const = 0;
  virtual void SetRoot(Catalog::EntryRef entry) = 0;
  virtual const Catalog::EntryPath &GetRootPath() const = 0;
  virtual void SetRootPath(const Catalog::EntryPath &path) = 0;
  virtual const std::string &GetLanguage() const = 0;
  virtual void SetLanguage(const std::string &value) = 0;
  virtual void IncreaseFontCompilationJobs() = 0;
  virtual void DecreaseFontCompilationJobs() = 0;
  virtual bool HasFontCompilationJobs() const = 0;
  // int requestedFontCompilations{0};
};

} // namespace Vandrouka::State

DECLARE_IID(Vandrouka::State::ICompilationState, 0x12, 0x71, 0xb8, 0xd5, 0x9a,
            0x7d, 0x4a, 0xe6, 0x89, 0xd3, 0x7a, 0xaf, 0x3a, 0xa, 0xfb, 0x24);
