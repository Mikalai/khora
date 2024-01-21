#pragma once

#include "DataModelState.h"
#include <Fundamental/Interface/IObserver.h>

namespace Vandrouka::State::Private {

DataModelState::DataModelState(Ref<IAsyncQueue> queue, IReferenced *owner) {
  _queue = queue;
  _owner = owner;
}

vsg::ref_ptr<vsg::Options> DataModelState::GetOptions() const {
  return _options;
}

void DataModelState::ClearPackages() { _packagePreviewRoots.clear(); }

Ref<Catalog::IConfigEntry> DataModelState::GetConfig() {
  return _dir->FindEntry({ROOT_CONFIG}).Cast<Catalog::IConfigEntry>();
}

void DataModelState::SetDir(Ref<Catalog::IDirectoryEntry> dir) {
  _dir = dir;
  assert(_dir);
  if (auto o = _dir.Cast<IObservable>(); o) {
    _dirSubscription = o->Subscribe(Ref<IReferenced>(_owner).Cast<IObserver>());
  }
}

vsg::ref_ptr<vsg::Node> DataModelState::GetAxis() { return _axis; }

Ref<Fonts::ISystemFonts> DataModelState::GetFonts() { return _fonts; }

std::unordered_map<std::string, PackageInfo>
DataModelState::GetPackages() const {
  return _packagePreviewRoots;
}

vsg::ref_ptr<vsg::Node>
DataModelState::FindPreviewPackage(std::string_view name) {
  auto it = _packagePreviewRoots.find(std::string(name));
  if (it != _packagePreviewRoots.end()) {
    return it->second.Root;
  }
  return {};
}

void DataModelState::AddPreviewPackage(std::string_view name,
                                       PackageInfo info) {
  _packagePreviewRoots[std::string(name)] = info;
}

void DataModelState::DenyCompilation() { _denyCompilation++; }

void DataModelState::AllowCompilation() { _denyCompilation--; }

bool DataModelState::CanCompile() const { return _denyCompilation == 0; }

Ref<Catalog::IDirectoryEntry> DataModelState::GetDir() { return _dir; }

Ref<Catalog::IEntry> DataModelState::GetActiveEntry() { return _activeEntry; }

void DataModelState::SetActiveEntry(Ref<Catalog::IEntry> entry) {
  _activeEntry = entry;
}

void DataModelState::CreateAxis() {
  _builder->options = _options;
  stateInfo.lighting = false;

  vsg::GeometryInfo geomInfo;
  geomInfo.dx.set(4.0f, 0.0f, 0.0f);
  geomInfo.dy.set(0.0f, 0.01f, 0.0f);
  geomInfo.dz.set(0.0f, 0.0f, 0.01f);
  geomInfo.color.set(1, 0, 0, 1);
  geomInfo.position.set(2, 0, 0);

  auto x = _builder->createBox(geomInfo, stateInfo);

  geomInfo.dx.set(0.01f, 0.0f, 0.0f);
  geomInfo.dy.set(0.0f, 4.0f, 0.0f);
  geomInfo.dz.set(0.0f, 0.0f, 0.01f);
  geomInfo.color.set(0, 1, 0, 1);
  geomInfo.position.set(0, 2, 0);

  auto y = _builder->createBox(geomInfo, stateInfo);

  geomInfo.dx.set(0.01f, 0.0f, 0.0f);
  geomInfo.dy.set(0.0f, 0.01f, 0.0f);
  geomInfo.dz.set(0.0f, 0.0f, 4.0f);
  geomInfo.color.set(0, 0, 1, 1);
  geomInfo.position.set(0, 0, 2);

  auto z = _builder->createBox(geomInfo, stateInfo);

  _axis = vsg::Group::create();
  _axis->addChild(x);
  _axis->addChild(y);
  _axis->addChild(z);

  stateInfo.lighting = true;
}

void DataModelState::Execute(Ref<IMessage> msg) {
  throw std::runtime_error("Not implemented");
}

} // namespace Vandrouka
