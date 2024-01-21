#pragma once

#include <boost/uuid/uuid_hash.hpp>
#include <Fundamental/Interface/IMessage.h>
#include <Fundamental/Module/Referenced.h>

namespace Vandrouka::Fundamental::Private {

template <typename Derived, typename Interface>
class MessageBase : public ReferenceCountedBase<Derived, Interface, IToString> {
public:
  using Interfaces =
      QueryInterfaces<Derived, Interface, IMessage, IToString, IReferenced>;

  const MessageId &GetTypeID() const override { return GetIID<Interface>::Id; }

  std::string ToString() const override { return typeid(Derived).name(); }
};

}; // namespace Vandrouka::Fundamental::Private