#pragma once

#include <tinyxml2.h>

#include <filesystem>

#include "i18n/i18n.hpp"
#include "i18n/util/extension.hpp"
#include "i18n/util/split_iterator.hpp"

namespace i18n::translators
{
class tinyxml2
{
 public:
  tinyxml2(std::filesystem::path directory_path_ = default_directory_name) : _directory_path(std::move(directory_path_))
  {
  }

  tinyxml2(const tinyxml2& rhs)
  {
    _directory_path = rhs._directory_path;
    rhs._document.DeepCopy(&_document);
  }

  void set_locale(const std::string& locale)
  {
    if (locale.empty())
    {
      return;
    }

    const std::filesystem::path full_path = _directory_path / locale / (default_file_name + util::extension::xml);

    auto res = _document.LoadFile(full_path.c_str());

    if (res != ::tinyxml2::XML_SUCCESS)
    {
      printf("Failed to load file %s\n", _document.ErrorStr());
      return;
    }
  }

  std::string translate(const char* composed_key, std::size_t length) const
  {
    if (length == 0)
    {
      return std::string{composed_key, length};
    }

    std::string_view view{composed_key, length};
    i18n::util::split_iterator<'/'> it{view};
    std::string_view key = *it;
    std::string key_str{key};
    ++it;

    const ::tinyxml2::XMLElement* root = _document.FirstChildElement(key_str.c_str());

    if (root == nullptr)
    {
      return std::string{view};
    }

    auto current_element = root->ToElement();

    for (; !(*it).empty(); ++it)
    {
      if (current_element == nullptr)
      {
        return std::string{view};
      }

      key = *it;
      key_str = std::string{key};
      auto next_element = current_element->FirstChildElement(key_str.c_str());

      if (next_element != nullptr)
      {
        current_element = next_element;
      }
      else
      {
        return std::string{view};
      }
    }

    if (current_element == nullptr)
    {
      return std::string{view};
    }

    return current_element->GetText();
  }

 private:
  std::filesystem::path _directory_path;
  ::tinyxml2::XMLDocument _document{};
};
}  // namespace i18n::translators
