#include <magic_enum.hpp>
#include "Entry.h"

IEntryObserver::~IEntryObserver() {
}

void Entry::AddObserver(std::shared_ptr<IEntryObserver> observer) {
	std::unique_lock lock{ _cs };
	_observers.push_back(observer);
}

void Entry::RemoveObserver(std::shared_ptr<IEntryObserver> observer) {
	std::unique_lock lock{ _cs };
	auto it = std::find_if(_observers.begin(), _observers.end(), [=](auto v) {
		return v.lock() == observer;
		});

	if (it == _observers.end())
		return;

	_observers.erase(it);
}

void Entry::Serialize(EntryProperties& properties) const {
	properties["Type"] = magic_enum::enum_name(GetType());
}

void Entry::Deserialize(const EntryProperties& properties) {
}
