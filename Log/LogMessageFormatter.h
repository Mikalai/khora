#pragma once

#include <Config.h>

#ifdef MAD_ENGINE_ENABLE_LOG
//#include <Message.h>
//#include <Math/Vector.h>
//#include <Math/ComponentAccessor.h>
//#include <Settings/MemorySize.h>

#ifdef MAD_ENGINE_USE_FMT

#ifdef __linux__
#define FMT_HEADER_ONLY
#endif

#include <fmt/core.h>
#include <fmt/os.h>
#include <fmt/format.h>

//
//template <>
//struct fmt::formatter<vec3> : fmt::formatter<std::string> {
//
//	auto format(const vec3& v, fmt::format_context& ctx) -> decltype(ctx.out()) {
//		return fmt::format_to(ctx.out(), "({},{},{})", x(v), y(v), z(v));
//	}
//};
//
//template <>
//struct fmt::formatter<MemorySize> : fmt::formatter<std::string> {
//
//	auto format(const MemorySize& v, fmt::format_context& ctx) -> decltype(ctx.out()) {
//		switch (v.Type)
//		{
//			case SizeType::Byte:
//				return fmt::format_to(ctx.out(), "{} B", v.Value);
//			case SizeType::KibiByte:
//				return fmt::format_to(ctx.out(), "{} KiB", v.Value);
//			case SizeType::MibiByte:
//				return fmt::format_to(ctx.out(), "{} MiB", v.Value);
//			case SizeType::GibiByte:
//				return fmt::format_to(ctx.out(), "{} GiB", v.Value);
//			case SizeType::TebiByte:
//				return fmt::format_to(ctx.out(), "{} TiB", v.Value);
//		default:
//			return fmt::format_to(ctx.out(), "{} B", v.Value);
//		}		
//	}
//};
//
//template <>
//struct fmt::formatter<Message> : fmt::formatter<std::string> {
//	
//	auto format(const Message& v, fmt::format_context& ctx) -> decltype(ctx.out()) {
//
//		switch (v.Type)
//		{
//		case MessageType::PLATFORM:
//		{
//			switch (v.platform.Type)
//			{
//			case PlatformMessageType::WINDOW:
//			{
//				switch (v.platform.window.Type)
//				{
//				case WindowMessageType::WINDOW_RESIZE:
//				{
//					return fmt::format_to(ctx.out(), "PLATFORM::WINDOW::RESIZED (Width={}, Height={})"
//						, v.platform.window.WindowResize.Width
//						, v.platform.window.WindowResize.Height);
//				}
//				case WindowMessageType::KEY:
//					return fmt::format_to(ctx.out(), "PLATFORM::WINDOW::KEY (Key={}, State={}, Shift={}, Control={}, Alt={}, Super={}, CapsLock={}, NumLock={})"
//					, static_cast<int>(v.platform.window.Key.Key)
//					, v.platform.window.Key.IsKeyPress() ? "PRESS" : v.platform.window.Key.IsKeyRelease() ? "RELEASE" : "REPEAT"
//					, v.platform.window.Key.IsShiftModifier()
//					, v.platform.window.Key.IsControlModifier()
//					, v.platform.window.Key.IsAltModifier()
//					, v.platform.window.Key.IsSuperModifier()
//					, v.platform.window.Key.IsCapsLockModifier()
//					, v.platform.window.Key.IsNumLockModifier());
//
//				case WindowMessageType::MOUSE_BUTTON:
//					return fmt::format_to(ctx.out(), "PLATFORM::WINDOW::MOUSE_BUTTON (Button={}, State={}, Shift={}, Control={}, Alt={}, Super={}, CapsLock={}, NumLock={})"
//						, static_cast<int>(v.platform.window.MouseButton.Button)
//						, v.platform.window.MouseButton.IsButtonPress() ? "PRESS" : "RELEASE"
//						, v.platform.window.MouseButton.IsShiftModifier()
//						, v.platform.window.MouseButton.IsControlModifier()
//						, v.platform.window.MouseButton.IsAltModifier()
//						, v.platform.window.MouseButton.IsSuperModifier()
//						, v.platform.window.MouseButton.IsCapsLockModifier()
//						, v.platform.window.MouseButton.IsNumLockModifier());
//
//				case WindowMessageType::MOUSE_MOVE:
//					return fmt::format_to(ctx.out(), "PLATFORM::WINDOW::MOUSE_MOVE (X={}, Y={})"
//						, v.platform.window.MouseMove.X
//						, v.platform.window.MouseMove.Y);
//
//				case WindowMessageType::CLOSE:
//					return fmt::format_to(ctx.out(), "PLATFORM::WINDOW::CLOSE");
//				default:
//					break;
//				}
//			}
//			default:
//				break;
//			}
//		}
//		break;
//		default:
//			break;
//		}
//
//		return fmt::format_to(ctx.out(), "{}", 0);
//	}
//};

#endif

#endif

