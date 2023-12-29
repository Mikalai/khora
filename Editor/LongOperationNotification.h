#pragma once

#include <compare>
#include <string>

struct LongOperation {
    std::string Name{};
    std::string Description{};

    auto operator<=>(const LongOperation&) const = default;
};

struct LongOperationStarted {
    LongOperation Operation;
    // TODO: Add cancel source
};

struct LongOperationEnded {
    LongOperation Operation;
    // TODO: Add cancel source
};

template <typename T, typename Start, typename End>
struct LongOperationScope {
    LongOperationScope(T& self, Start start, End end, LongOperation op)
        : _self{self}, _start{start}, _end{end}, _op{op} {
        (_self.*_start)(LongOperationStarted{.Operation = _op});
    }

    ~LongOperationScope() {
        (_self.*_end)(LongOperationEnded{.Operation = _op});
    }

   private:
    T& _self;
    Start _start;
    End _end;
    LongOperation _op;
};
