#pragma once

#include <Fundamental/Interface/Result.h>
#include <vsg/all.h>

namespace Vandrouka::Catalog {

class ITransformEntry : public Fundamental::IReferenced {
public:
  virtual Result<vsg::ref_ptr<vsg::MatrixTransform>> GetTransform() const = 0;
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

} // namespace Vandrouka::Catalog

DECLARE_IID(Vandrouka::Catalog::ITransformEntry, 0x1b, 0xbf, 0x32, 0xf, 0x84,
            0xa4, 0x45, 0x54, 0x83, 0xe5, 0xc1, 0xa, 0x9b, 0xec, 0x53, 0x9);

DECLARE_CID(Catalog, TransformProxyEntry, 0xb7, 0xff, 0x62, 0x8b, 0xa1, 0xa4,
            0x4e, 0xf4, 0x9f, 0x1a, 0xa7, 0xb, 0xa9, 0x6a, 0x25, 0x81);

DECLARE_CID(Catalog, TransformPackageEntry, 0x11, 0x1c, 0xf7, 0x2a, 0x69, 0x3e,
            0x49, 0x37, 0xa1, 0x3f, 0x4c, 0xcb, 0x5d, 0x9a, 0x97, 0x32);
