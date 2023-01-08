#pragma once

#include <Deck.h>
#include <Resources.h>
#include <Policies.h>
#include <Platform/NumberConverter.h>

class PoliciesDeck : public Deck<Policies, static_cast<int>(Policies::policies_count), Policies::policy_unknown> {
public:
    void Reset(bool shuffle);
};

