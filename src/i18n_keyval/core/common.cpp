#include "i18n_keyval/core/common.hpp"

#include <utility>

namespace i18n
{
i18n_exception::i18n_exception(const char* message_)
{
  _message = message_;
}

const char* i18n_exception::what() const noexcept
{
  return _message;
}

void throw_i18n_exception(const char* msg)
{
  I18N_THROW(i18n_exception(std::move(msg)));
}
}  // namespace i18n
