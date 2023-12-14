#pragma once

#include <mutex>
#include <memory>
#include <functional>
#include <string_view>
#include <nlohmann/json.hpp>
#include <vector>
#include "EntryPath.h"
#include "EntryType.h"
#include "IEntryObserver.h"

class Entry;
class IEntryObserver;

struct EntryProperty {
    std::string Key;
    std::string Value;
};

using EntryProperties = nlohmann::json;

class Entry : protected IEntryObserver, public std::enable_shared_from_this<Entry> {
public:

    virtual ~Entry() {}

    virtual EntryType GetType() const = 0;
    virtual std::shared_ptr<Entry> Clone() = 0;

    auto GetParent() { return _parent.lock(); }
    auto GetParent() const { return _parent.lock(); }
    void SetParent(std::shared_ptr<Entry> parent) { _parent = parent; }

    std::shared_ptr<Entry> GetRoot() const;
    void AddObserver(std::shared_ptr<IEntryObserver> observer);
    void RemoveObserver(std::shared_ptr<IEntryObserver> observer);

    virtual std::shared_ptr<Entry> CreateProxy(EntryPath path) = 0;   
    virtual std::shared_ptr<Entry> FindEntry(const EntryPath& path) const = 0;
    
    virtual void Serialize(EntryProperties& properties) const;
    void Deserialize(const EntryProperties& properties);

protected:
    virtual void DeserializeInternal(EntryPath path, const EntryProperties& properties);

    void OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) override;
    void OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) override;
    void OnPropertyChanged(std::shared_ptr<Entry> sender, std::string_view name) override;

    void CopyObserversTo(Entry& entry);

private:
    std::weak_ptr<Entry> _parent;
    std::mutex _cs;
    std::vector<std::weak_ptr<IEntryObserver>> _observers;

    friend class DirectoryEntry;
};
