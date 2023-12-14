#pragma once

#include <memory>
#include "EntryPath.h"

class Entry;

class IEntryObserver {
public:
    virtual ~IEntryObserver() {}

    virtual void OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) = 0;
    virtual void OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) = 0;
    virtual void OnPropertyChanged(std::shared_ptr<Entry> sender, std::string_view name) = 0;
};


