#pragma once

#include "MaterialEntry.h"
#include "Clone.h"

EntryType MaterialEntry::GetType() const {
    return EntryType::Material;
}

std::shared_ptr<Entry> MaterialEntry::Clone() {
    return std::make_shared<MaterialEntry>(::Clone(_state));
}

vsg::ref_ptr<vsg::StateGroup> MaterialEntry::GetState() const {
    return ::Clone(_state);
}

bool MaterialEntry::CanAdd(std::shared_ptr<Entry> entry) {
    return true;
}