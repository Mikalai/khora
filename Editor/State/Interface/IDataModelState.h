#pragma once

#include <unordered_map>
#include <vsg/all.h>

#include <Catalog/Interface/IConfigEntry.h>
#include <Catalog/Interface/IDirectoryEntry.h>
#include <Catalog/Interface/IGroupEntry.h>
#include <Catalog/Interface/ITextEntry.h>
#include <Fonts/Interface.h>
#include <Fundamental/Interface/IAsyncQueue.h>

namespace Vandrouka::State {

const std::string ROOT_PACKAGES{"PACKAGES"};
const std::string ROOT_SCENE{"SCENE"};
const std::string ROOT_CONFIG{"CONFIG"};

const std::string PACKAGE_ENTRY_TRANSFORMS{"Transforms"};
const std::string PACKAGE_ENTRY_GEOMETRIES{"Geometries"};
const std::string PACKAGE_ENTRY_MATERIALS{"Materials"};

struct PackageInfo {
  std::filesystem::path Path;
  vsg::ref_ptr<vsg::Node> Root;
};

struct TextConfig {
  Ref<Catalog::ITextEntry> Entry;
  vsg::ref_ptr<vsg::Font> Font;
  vsg::ref_ptr<vsg::Options> Options;
};

class IDataModelState : public Fundamental::IReferenced {
public:
  virtual void Execute(Ref<IMessage> msg) = 0;
  virtual Ref<IAsyncQueue> GetSyncContext() = 0;
  virtual Ref<Catalog::IConfigEntry> GetConfig() = 0;
  virtual void DenyCompilation() = 0;
  virtual void AllowCompilation() = 0;
  virtual bool CanCompile() const = 0;
  virtual Ref<Fonts::ISystemFonts> GetFonts() = 0;
  virtual vsg::ref_ptr<vsg::Node> FindPreviewPackage(std::string_view name) = 0;
  virtual void AddPreviewPackage(std::string_view name, PackageInfo info) = 0;
  virtual Ref<Catalog::IDirectoryEntry> GetDir() = 0;
  virtual void SetDir(Ref<Catalog::IDirectoryEntry> dir) = 0;
  virtual Ref<Catalog::IEntry> GetActiveEntry() = 0;
  virtual void SetActiveEntry(Ref<Catalog::IEntry> entry) = 0;
  virtual vsg::ref_ptr<vsg::Node> GetAxis() = 0;
  virtual std::unordered_map<std::string, PackageInfo> GetPackages() const = 0;
  virtual vsg::ref_ptr<vsg::Options> GetOptions() const = 0;
  virtual void ClearPackages() = 0;
};

} // namespace Vandrouka::State

DECLARE_IID(Vandrouka::State::IDataModelState, 0x10, 0xa8, 0x18, 0x6a, 0x79,
            0x4e, 0x47, 0xd6, 0xbc, 0x38, 0x6f, 0xa5, 0x82, 0x20, 0xec, 0x3d);