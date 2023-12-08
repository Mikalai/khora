#pragma once

#include "Entry.h"
#include "EntryPath.h"

class IDirectoryObserver {
public:
    virtual ~IDirectoryObserver() {}

    virtual void OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry) = 0;
    virtual void OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry) = 0;
};


