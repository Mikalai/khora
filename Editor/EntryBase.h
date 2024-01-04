#pragma once

#include "Observer.h"
#include "IEntry.h"

namespace Vandrouka {

template <typename Derived, typename... Interfaces>
class EntryBase : public ObservableBase<Derived, Interfaces...> {
public:
 
  EntryRef GetParent() override { return this->_parent; }

  EntryRef GetParent() const override { return this->_parent; }

  void SetParent(EntryRef parent) override {
    // do not increase references. TODO: Add weak references support.
    this->_parent = parent.get();
  }

  EntryRef GetRoot() const override {
    Ref<Derived> root{const_cast<Derived*>(this)};
    auto next = root->GetParent();

    while (next) {
      root = next;
      next = root->GetParent();
    }

    return root;
  }

  private:
  IEntry* _parent{nullptr};
};

} // namespace Vandrouka
