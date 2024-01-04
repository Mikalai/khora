#pragma once

#include "IReferenced.h"
#include <vsg/all.h>

namespace Vandrouka {

class ITransformEntry : public IReferenced {
public:
  virtual vsg::ref_ptr<vsg::MatrixTransform> GetTransform() const = 0;
  virtual void SetOverride(bool) = 0;
  virtual bool GetOverride() const = 0;
  virtual void SetPosition(vsg::dvec3) = 0;
  virtual vsg::dvec3 GetPosition() const = 0;
  virtual void SetScale(vsg::dvec3) = 0;
  virtual vsg::dvec3 GetScale() const = 0;
  virtual void SetOrientation(vsg::dquat) = 0;
  virtual vsg::dquat GetOrientation() const = 0;
  virtual bool IsMutable() const = 0;
  virtual vsg::dmat4 GetWorldMatrix() = 0;
};

template <> struct GetIID<ITransformEntry> {
  static constexpr InterfaceId Id = {{0x1b, 0xbf, 0x32, 0xf, 0x84, 0xa4, 0x45,
                                      0x54, 0x83, 0xe5, 0xc1, 0xa, 0x9b, 0xec,
                                      0x53, 0x9}};
};

class TransformProxyEntry;
template <> struct GetCID<TransformProxyEntry> {
  static constexpr InterfaceId Id = {{0xb7, 0xff, 0x62, 0x8b, 0xa1, 0xa4, 0x4e,
                                      0xf4, 0x9f, 0x1a, 0xa7, 0xb, 0xa9, 0x6a,
                                      0x25, 0x81}};
};

} // namespace Vandrouka
