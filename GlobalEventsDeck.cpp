#include <random>
#include <chrono>
#include <numeric>
#include "GlobalEventsDeck.h"

void GlobalEventsDeck::Reset(bool shuffle) {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	auto eng = std::default_random_engine(seed);
	std::array<int, (int)GlobalEventType::Count> numbers;
	std::iota(numbers.begin(), numbers.end(), 0);
	std::shuffle(numbers.begin() + 1, numbers.end() - 1, eng);

	_cards.front() = (GlobalEventType)numbers.front();
	_cards.back() = (GlobalEventType)numbers.back();

	for (int i = 1; i < 8; ++i) {
		_cards[i] = (GlobalEventType)numbers[i];
	}

	std::reverse(_cards.begin(), _cards.end());
}

int GlobalEventsDeck::AddToOpen(GlobalEventType evt) {
	auto index = ++_openTop;
	_openedEvents[index] = evt;
	return index;
}

GlobalEventType GlobalEventsDeck::Current() const {
	assert(_openTop >= 0 && _openTop < 9);
	return _openedEvents[_openTop];
}
