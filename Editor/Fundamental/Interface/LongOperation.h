#pragma once

#include <Fundamental/Interface/IError.h>
#include <string>

namespace Vandrouka {
namespace Fundamental {

struct LongOperation {
  std::string Name{};
  std::string Description{};

  auto operator<=>(const LongOperation &) const = default;
};

} // namespace Fundamental

using Fundamental::LongOperation;

} // namespace Vandrouka
