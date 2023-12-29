#include <PoliciesDeck.h>
#include <Resources.h>

#include <chrono>
#include <random>

void PoliciesDeck::Reset(bool shuffle) {
    for (int i = 0; i < As<int>(PoliciesType::policies_count); ++i) {
        _cards[i] = (PoliciesType)i;
    }
    if (shuffle) {
        unsigned seed =
            std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(_cards.begin(), _cards.end(),
                     std::default_random_engine(seed));
    }
}
