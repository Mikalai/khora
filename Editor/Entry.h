#pragma once

#include <memory>
#include "EntryType.h"

class Entry : public std::enable_shared_from_this<Entry> {
public:

    virtual ~Entry() {}

    virtual EntryType GetType() const = 0;
    virtual std::shared_ptr<Entry> Clone() = 0;

    auto GetParent() { return _parent.lock(); }
    void SetParent(std::shared_ptr<Entry> parent) { _parent = parent; }

private:
    std::weak_ptr<Entry> _parent;
};
