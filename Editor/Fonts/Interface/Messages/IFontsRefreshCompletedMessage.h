#include <Fonts/Interface/ISystemFonts.h>
#include <Fundamental/Interface/IMessage.h>

namespace Vandrouka::Fonts::Messages {

class IFontsRefreshCompletedMessage : public IMessage {
public:
  virtual const std::vector<FontInfo> &GetFonts() = 0;
};

} // namespace Vandrouka::Fonts::Messages

DECLARE_IID(Vandrouka::Fonts::Messages::IFontsRefreshCompletedMessage, 0xff,
            0x91, 0xd0, 0x59, 0x1b, 0x27, 0x49, 0x4f, 0xaa, 0x57, 0x5a, 0x32,
            0x53, 0xb0, 0x38, 0xe0);
