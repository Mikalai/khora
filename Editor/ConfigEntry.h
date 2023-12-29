#pragma once

#include <vsg/all.h>

#include <semaphore>

#include "DirectoryEntry.h"

class AsyncQueue;

class ConfigEntry : public DirectoryEntry {
public:
  EntryType GetType() const override;

  virtual bool GetShowTransform() const;
  virtual void SetShowTransform(bool value);

  virtual bool AddLanguage(const std::string &value);
  virtual bool RemoveLanguage(const std::string &value);
  virtual std::vector<std::string> GetLanguages() const;
  virtual std::string GetActiveLanguage() const;
  virtual bool SetActiveLanguage(const std::string &value);

  virtual std::shared_ptr<Entry>
  CreateView(std::shared_ptr<AsyncQueue> sync) override;

  void Serialize(EntryProperties &properties) const override;
  void DeserializeInternal(EntryPath path,
                           const EntryProperties &properties) override;

  std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
  bool CanAdd(std::shared_ptr<Entry> entry) override;

protected:
  void CloneFrom(std::shared_ptr<Entry> entry) override;
  std::shared_ptr<Entry> CreateCopy() const override;

private:
  bool _showTransform{true};
  std::vector<std::string> _languages;
  std::string _activeLanguage;
};

class ConfigEntryView : public ConfigEntry {
public:
  ConfigEntryView(std::shared_ptr<ConfigEntry> dataModel,
                  std::shared_ptr<AsyncQueue> syncContext)
      : _model{dataModel}, _sync{syncContext} {}

  std::shared_ptr<Entry> CreateProxy(EntryPath path) override;
  bool CanAdd(std::shared_ptr<Entry> entry) override;

  void Serialize(EntryProperties &properties) const override;
  void DeserializeInternal(EntryPath path,
                           const EntryProperties &properties) override;

  bool GetShowTransform() const override;
  void SetShowTransform(bool value) override;
  bool AddLanguage(const std::string &value) override;
  bool RemoveLanguage(const std::string &value) override;
  std::vector<std::string> GetLanguages() const override;
  std::string GetActiveLanguage() const override;
  bool SetActiveLanguage(const std::string &value) override;

protected:
  void CloneFrom(std::shared_ptr<Entry> entry) override;
  std::shared_ptr<Entry> CreateCopy() const override;

private:
  std::shared_ptr<ConfigEntry> _model;
  std::shared_ptr<AsyncQueue> _sync;
};
