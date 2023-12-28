#pragma once

#include <functional>
#include <mutex>
#include <unordered_map>

#include "Entry.h"
#include "EntryPath.h"
#include "IEntryObserver.h"

class DirectoryEntry : public Entry {
    std::unordered_map<std::string, size_t> _nameToIndex;
    std::vector<std::pair<std::string, std::shared_ptr<Entry>>> _entries;

   public:
    DirectoryEntry();
    // DirectoryEntry(const DirectoryEntry& entry);

    void ForEachEntry(
        std::function<void(const std::string& name, std::shared_ptr<Entry>)>
            cb) {
        for (auto& [name, entry] : _entries) {
            cb(name, entry);
        }
    }

    void TraverseTopDown(
        std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
        TraverseTopDown({}, cb);
    }

    void TraverseDownTop(
        std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb) {
        TraverseDownTop({}, cb);
    }

    bool IsEmpty() const { return _entries.empty(); }

    bool Add(const EntryPath& path, std::shared_ptr<Entry> entry) {
        if (!CanAdd(entry)) return false;

        return Add(path, {}, entry);
    }

    std::shared_ptr<Entry> Remove(const EntryPath& path) {
        return Remove(path, {});
    }

    std::shared_ptr<Entry> FindEntry(const EntryPath& path) const override;

    void Serialize(EntryProperties& properties) const override;

   protected:
    virtual bool CanAdd(std::shared_ptr<Entry> entry) = 0;
    void DeserializeInternal(EntryPath path,
                             const EntryProperties& properties) override;
    void CloneFrom(std::shared_ptr<Entry> entry) override;

   private:
    bool Add(const EntryPath& path, EntryPath parent,
             std::shared_ptr<Entry> entry);
    std::shared_ptr<Entry> Remove(const EntryPath& path, EntryPath parent);
    void TraverseTopDown(
        const EntryPath& parent,
        std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb);
    void TraverseDownTop(
        const EntryPath& parent,
        std::function<void(EntryPath path, std::shared_ptr<Entry>)> cb);
};
