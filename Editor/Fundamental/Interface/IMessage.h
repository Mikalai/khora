#pragma once

#include <Fundamental/Interface/IReferenced.h>
#include <boost/uuid/uuid_hash.hpp>

namespace Vandrouka {
namespace Fundamental {

using MessageId = boost::uuids::uuid;

class IMessage : public Fundamental::IReferenced {
public:
  virtual const MessageId &GetTypeID() const = 0;
};

template <typename T>
concept MessageType = requires(T a) {
  { std::derived_from<T, IMessage> };
};

template <> struct GetIID<IMessage> {
  static constexpr InterfaceId Id = {{0xad, 0x15, 0xcd, 0x2b, 0xe4, 0x2b, 0x43,
                                      0xef, 0x8f, 0x74, 0x5d, 0x2f, 0x9a, 0xb1,
                                      0xce, 0x5}};
};
} // namespace Fundamental

using Fundamental::IMessage;
using Fundamental::MessageId;

} // namespace Vandrouka
