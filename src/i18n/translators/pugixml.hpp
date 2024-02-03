#pragma once

#include <filesystem>
#include <pugixml.hpp>

#include "i18n/util/extension.hpp"

namespace i18n::translators
{
class pugixml
{
 public:
  pugixml(std::filesystem::path directory_path_ = default_directory_name) : _directory_path(std::move(directory_path_))
  {
  }

  void set_locale(const std::string& locale)
  {
    if (locale.empty())
    {
      return;
    }

    const std::filesystem::path full_path = _directory_path / locale / (default_file_name + util::extension::xml);
    _document.load_file(full_path.c_str());
  }

  std::string translate(const char* composed_key, std::size_t length) const
  {
    if (length == 0)
    {
      return "";
    }

    auto nodes = _document.select_nodes(composed_key);

    if (nodes.empty())
    {
      return std::string{composed_key, length};
    }

    return nodes[0].node().first_child().value();
  }

 private:
  pugi::xml_document _document;
  std::filesystem::path _directory_path;
};
}  // namespace i18n::translators
