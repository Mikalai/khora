#pragma once

#include <unordered_map>
#include <mutex>
#include <functional>

#include "IEntryObserver.h"
#include "EntryPath.h"
#include "Entry.h"

class DirectoryEntry : public Entry {
    mutable std::mutex _cs;
    std::unordered_map<std::string, std::shared_ptr<Entry>> _entries;
public:

    void ForEachEntry(std::function<void(const std::string& name, std::shared_ptr<Entry>)> cb) {
        std::unique_lock lock{ _cs };
        for (auto& [name, entry] : _entries) {
            cb(name, entry);
        }
    }

    void TraverseTopDown(std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
        TraverseTopDown({}, cb);
    }

    void TraverseDownTop(std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
        TraverseDownTop({}, cb);
    }

    bool IsEmpty() const {
        std::unique_lock<std::mutex> lock{ _cs };
        return _entries.empty();
    }

    virtual bool CanAdd(std::shared_ptr<Entry> entry) = 0;

    void Add(const EntryPath& path, std::shared_ptr<Entry> entry) {
        Add(path, {}, entry);
    }

    std::shared_ptr<Entry> Remove(const EntryPath& path) {
        return Remove(path, {});
    }

    std::shared_ptr<Entry> FindEntry(const EntryPath& path) const override;

    void Serialize(EntryProperties& properties) const override;

protected:
    void DeserializeInternal(EntryPath path, const EntryProperties& properties) override;

private:
    void Add(const EntryPath& path, EntryPath parent, std::shared_ptr<Entry> entry);
    std::shared_ptr<Entry> Remove(const EntryPath& path, EntryPath parent);
    void TraverseTopDown(const EntryPath& parent, std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb);
    void TraverseDownTop(const EntryPath& parent, std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb);
};

