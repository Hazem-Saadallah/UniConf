#pragma once

#include <string>
#include <cstddef>

namespace Util {
  namespace Misc {
    std::string generate_random_string(std::size_t length, std::string prefix, std::string suffix);
  }
}
