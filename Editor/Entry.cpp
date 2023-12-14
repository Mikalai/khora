#include <magic_enum.hpp>
#include "Entry.h"

std::shared_ptr<Entry> Entry::GetRoot() const
{
	auto root = const_cast<Entry&>(*this).shared_from_this();
	auto next = root->GetParent();
	
	while (next) {
		root = next;
		next = root->GetParent();
	}

	return root;
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
	DeserializeInternal({}, properties);
}

void Entry::DeserializeInternal(EntryPath path, const EntryProperties& properties)
{
}

void Entry::OnEntryAdded(EntryPath path, std::shared_ptr<Entry> entry)
{
	std::unique_lock lock{ _cs };
	std::for_each(_observers.begin(), _observers.end(), [&](auto v) {
		if (auto p = v.lock(); p) {
			p->OnEntryAdded(path, entry);
		}
	});
}

void Entry::OnEntryRemoved(EntryPath path, std::shared_ptr<Entry> entry)
{
	std::unique_lock lock{ _cs };
	std::for_each(_observers.begin(), _observers.end(), [&](auto v) {
		if (auto p = v.lock(); p) {
			p->OnEntryRemoved(path, entry);
		}
	});
}

void Entry::OnPropertyChanged(std::shared_ptr<Entry> sender, std::string_view name)
{
	std::unique_lock lock{ _cs };
	std::for_each(_observers.begin(), _observers.end(), [&](auto v) {
		if (auto p = v.lock(); p) {
			p->OnPropertyChanged(sender, name);
		}
	});
}

void Entry::CopyObserversTo(Entry& entry) {
	std::vector<std::weak_ptr<IEntryObserver>> myObserver;
	{
		std::unique_lock lock{ _cs };
		myObserver = _observers;
	}
	{
		std::unique_lock lock{ entry._cs };
		entry._observers = myObserver;
	}
}
