#pragma once

#include "IReferenced.h"

namespace Vandrouka {

enum class TextHorizontalAlignment { Left, Center, Right };
enum class TextVerticalAlignment { Bottom, Center, Top };

class ITextEntry : public IReferenced {
public:
  virtual void SetFont(const std::string &fontName) = 0;
  virtual std::string GetFont() const = 0;

  virtual void SetValue(const std::u8string &value) = 0;
  virtual std::u8string GetValue() const = 0;

  virtual double GetOffsetX() const = 0;
  virtual double GetOffsetY() const = 0;
  virtual double GetOffsetZ() const = 0;

  virtual double GetHorizontalAxisX() const = 0;
  virtual double GetHorizontalAxisY() const = 0;
  virtual double GetHorizontalAxisZ() const = 0;

  virtual double GetVerticalAxisX() const = 0;
  virtual double GetVerticalAxisY() const = 0;
  virtual double GetVerticalAxisZ() const = 0;

  virtual double GetColorR() const = 0;
  virtual double GetColorG() const = 0;
  virtual double GetColorB() const = 0;
  virtual double GetColorA() const = 0;

  virtual TextHorizontalAlignment GetHorizontalAlignment() const = 0;
  virtual TextVerticalAlignment GetVerticalAlignment() const = 0;
  virtual double GetLineSpacing() const = 0;

  virtual void SetOffsetX(double value) = 0;
  virtual void SetOffsetY(double value) = 0;
  virtual void SetOffsetZ(double value) = 0;

  virtual void SetHorizontalAxisX(double value) = 0;
  virtual void SetHorizontalAxisY(double value) = 0;
  virtual void SetHorizontalAxisZ(double value) = 0;

  virtual void SetVerticalAxisX(double value) = 0;
  virtual void SetVerticalAxisY(double value) = 0;
  virtual void SetVerticalAxisZ(double value) = 0;

  virtual void SetColor(double r, double g, double b, double a) = 0;
  virtual void SetColorR(double value) = 0;
  virtual void SetColorG(double value) = 0;
  virtual void SetColorB(double value) = 0;
  virtual void SetColorA(double value) = 0;

  virtual void SetHorizontalAlignment(TextHorizontalAlignment value) = 0;
  virtual void SetVerticalAlignment(TextVerticalAlignment value) = 0;
  virtual void SetLineSpacing(double value) = 0;
};

template <> struct GetIID<ITextEntry> {
  static constexpr InterfaceId Id = {{0xe7, 0x76, 0x30, 0x6e, 0x88, 0x5, 0x41,
                                      0xa9, 0xbb, 0x76, 0xbe, 0x62, 0xc6, 0x6a,
                                      0xba, 0xfe}};
};

class TextEntry;

template <> struct GetCID<TextEntry> {
  static constexpr InterfaceId Id = {{0x82, 0xc4, 0x36, 0xa, 0x48, 0xf1, 0x4a,
                                      0x80, 0x97, 0x60, 0x2f, 0xb7, 0x3d, 0xe5,
                                      0xc1, 0x80}};
};

} // namespace Vandrouka
