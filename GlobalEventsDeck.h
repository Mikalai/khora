#pragma once

#include <Deck.h>
#include <Resources.h>

class GlobalEventsDeck : public Deck<GlobalEventType, 9, GlobalEventType::Unknown> {
public:
    void Reset(bool shuffle);
    int AddToOpen(GlobalEventType evt);
    GlobalEventType Current() const;
private:
    std::array<GlobalEventType, 9> _openedEvents;
    int _openTop{ -1 };
};
