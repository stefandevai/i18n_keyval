#pragma once

#include <memory>
#include <string>

#include "i18n/core/translator.hpp"

namespace i18n
{
class registry
{
 public:
  std::string locale = "";

  registry() = default;
  registry(const registry&) = delete;
  registry& operator=(const registry&) = delete;

  void initialize_translator(std::shared_ptr<translator> translator_);
  [[nodiscard]] std::string translate(const char* composed_key_, const std::size_t length_) noexcept;
  void set_locale(std::string locale_) noexcept;
  [[nodiscard]] static registry& instance() noexcept;

 private:
  std::shared_ptr<translator> _translator = nullptr;
};
}  // namespace i18n
