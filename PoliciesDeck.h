#pragma once

#include <Deck.h>
#include <Resources.h>
#include <Policies.h>
#include <Platform/NumberConverter.h>

class PoliciesDeck : public Deck<PoliciesType, static_cast<int>(PoliciesType::policies_count), PoliciesType::policy_unknown> {
public:
    void Reset(bool shuffle);
};

