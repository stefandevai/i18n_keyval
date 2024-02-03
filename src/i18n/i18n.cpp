#include "i18n/i18n.hpp"

namespace i18n
{
  std::string translate(const std::string& key)
  {
    return key + " (from lib)\n";
  }
}
