#pragma once

#include <filesystem>
#include <pugixml.hpp>

#include "i18n/core/common.hpp"
#include "i18n/util/extension.hpp"

namespace i18n::translators
{
class pugixml
{
 public:
  pugixml(std::filesystem::path directory_path_ = default_directory_name) : _directory_path(std::move(directory_path_))
  {
  }

  void set_locale(const std::string& locale_)
  {
    if (locale_.empty())
    {
      throw_i18n_exception("Locale not found");
      _document.load_file("");
      return;
    }

    const std::filesystem::path full_path = _directory_path / locale_ / (default_file_name + util::extension::xml);

    if (!std::filesystem::exists(full_path))
    {
      throw_i18n_exception("Locale not found");
      _document.load_file("");
      return;
    }

    _document.load_file(full_path.c_str());
  }

  std::string translate(const char* composed_key_, std::size_t length_) const noexcept
  {
    if (length_ == 0)
    {
      return std::string{composed_key_, length_};
    }

    auto nodes = _document.select_nodes(composed_key_);

    if (nodes.empty())
    {
      return std::string{composed_key_, length_};
    }

    return nodes[0].node().first_child().value();
  }

 private:
  pugi::xml_document _document;
  std::filesystem::path _directory_path;
};
}  // namespace i18n::translators
