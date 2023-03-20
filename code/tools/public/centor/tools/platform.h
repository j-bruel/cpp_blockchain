#pragma once

namespace centor
{

  enum class platform
  {
    linux,
    windows,
    mac_os,
    unsupported
  };

  constexpr platform current_platform() noexcept
  {
#ifdef __APPLE__
  #ifdef __MACH__
    return centor::platform::mac_os;
  #else
    return centor::platform::unsupported;
  #endif
#elif defined(__linux__)
    return centor::platform::linux;
#elif defined(_WIN32)
    return centor::platform::windows;
#else
    return centor::platform::unsupported;
#endif
  }

}