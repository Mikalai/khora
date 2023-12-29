#pragma once

#include <vsg/all.h>

#include "DirectoryEntry.h"

class MaterialEntry : public DirectoryEntry {
public:
  MaterialEntry();
  MaterialEntry(const MaterialEntry &entry);

  EntryType GetType() const override;
  virtual vsg::ref_ptr<vsg::StateGroup> GetState() const = 0;
  virtual std::shared_ptr<Entry>
  CreateView(std::shared_ptr<AsyncQueue> sync) override;

protected:
  bool CanAdd(std::shared_ptr<Entry>) final { return true; }
};

class MaterialPackageEntry : public MaterialEntry {
public:
  MaterialPackageEntry(vsg::ref_ptr<vsg::StateGroup> state) : _state{state} {}

  MaterialPackageEntry() {}

  vsg::ref_ptr<vsg::StateGroup> GetState() const override;
  std::shared_ptr<Entry> CreateProxy(EntryPath path) override;

protected:
  void CloneFrom(std::shared_ptr<Entry> entry) override;
  std::shared_ptr<Entry> CreateCopy() const override;

private:
  vsg::ref_ptr<vsg::StateGroup> _state;
};

class MaterialProxyEntry : public MaterialEntry {
public:
  MaterialProxyEntry(EntryPath path);
  MaterialProxyEntry() {}

  vsg::ref_ptr<vsg::StateGroup> GetState() const override;
  std::shared_ptr<Entry> CreateProxy(EntryPath path) override;

  void Serialize(EntryProperties &properties) const override;
  void DeserializeInternal(EntryPath path,
                           const EntryProperties &properties) override;

protected:
  void CloneFrom(std::shared_ptr<Entry> entry) override;
  std::shared_ptr<Entry> CreateCopy() const override;

private:
  EntryPath _path;
};

class MaterialEntryView : public MaterialEntry {
public:
  MaterialEntryView(std::shared_ptr<MaterialEntry> entry,
                    std::shared_ptr<AsyncQueue> sync)
      : _model{entry}, _sync{sync} {}

  MaterialEntryView() {}

  vsg::ref_ptr<vsg::StateGroup> GetState() const override;
  std::shared_ptr<Entry> CreateProxy(EntryPath path) override;

protected:
  void CloneFrom(std::shared_ptr<Entry> entry) override;
  std::shared_ptr<Entry> CreateCopy() const override;

private:
  std::shared_ptr<MaterialEntry> _model;
  mutable std::shared_ptr<AsyncQueue> _sync;
};