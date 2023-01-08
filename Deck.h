#pragma once

#include <array>
#include <cassert>
#include <functional>

template<typename T, int Count, T Def>
class Deck {
public:    

    bool CanTake() const {
		return _top >= 0;
    }

    std::tuple<T, int> Next() {
		assert(_top >= 0);
        auto index = _top--;
        auto v = _cards[index];
        
        assert(v != Def);
        _cards[index] = Def;
        return { v, index };
    }
	

    void Drop(T policy) {
		assert(_top < Count - 1);
        assert(_cards[_top + 1] == Def);
        if (!Empty()) {
            for (int i = _top; i >= 0; --i) {
                std::swap(_cards[i], _cards[i + 1]);
            }
        }
		_cards[0] = policy;
        ++_top;
    }

    void ForEach(std::function<void(int, T)> action) const {
        for (int i = 0; i < Count; ++i) {			
            action(i, _cards[i]);
        }
    }

    bool Empty() const {
        return _top < 0;
    }

	constexpr int Size() const {
		return Count;
	}

protected:
    std::array<T, Count> _cards;
    int _top{ Count - 1 };
};
