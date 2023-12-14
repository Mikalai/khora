#pragma once

#include <mutex>
#include <memory>
#include <functional>
#include <string_view>
#include <nlohmann/json.hpp>
#include <vector>
#include "EntryPath.h"
#include "EntryType.h"


class Entry;

class IEntryObserver : public std::enable_shared_from_this<IEntryObserver> {
public:
    virtual ~IEntryObserver();
    virtual void OnPropertyChanged(std::shared_ptr<Entry> sender, std::string_view name) = 0;
};

struct EntryProperty {
    std::string Key;
    std::string Value;
};

using EntryProperties = nlohmann::json;

class Entry : public std::enable_shared_from_this<Entry> {
public:

    virtual ~Entry() {}

    virtual EntryType GetType() const = 0;
    virtual std::shared_ptr<Entry> Clone() = 0;

    auto GetParent() { return _parent.lock(); }
    void SetParent(std::shared_ptr<Entry> parent) { _parent = parent; }

    void AddObserver(std::shared_ptr<IEntryObserver> observer);
    void RemoveObserver(std::shared_ptr<IEntryObserver> observer);

    virtual std::shared_ptr<Entry> CreateProxy(std::shared_ptr<Entry> root, EntryPath path) = 0;   
    virtual std::shared_ptr<Entry> FindEntry(const EntryPath& path) const = 0;
    
    virtual void Serialize(EntryProperties& properties) const;
    virtual void Deserialize(const EntryProperties& properties);

private:
    std::weak_ptr<Entry> _parent;
    std::mutex _cs;
    std::vector<std::weak_ptr<IEntryObserver>> _observers;
};
