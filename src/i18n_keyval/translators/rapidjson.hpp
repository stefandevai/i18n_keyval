#pragma once

#include <filesystem>

#include "i18n_keyval/core/common.hpp"
#include "i18n_keyval/util/extension.hpp"
#include "i18n_keyval/util/file.hpp"
#include "i18n_keyval/util/split_iterator.hpp"
#include "rapidjson/document.h"

namespace i18n::translators
{
class rapidjson
{
 public:
  rapidjson(std::filesystem::path directory_path_ = default_directory_name)
      : _directory_path(std::move(directory_path_))
  {
  }

  void set_locale(const std::string& locale_)
  {
    if (locale_.empty())
    {
      throw_i18n_exception("Locale is empty");
      _document.SetObject();
      return;
    }

    const std::filesystem::path locale_directory = _directory_path / locale_;

    if (!std::filesystem::exists(locale_directory) || !std::filesystem::is_directory(locale_directory))
    {
      throw_i18n_exception("Locale not found");
      _document.SetObject();
      return;
    }

    const std::filesystem::path full_path = locale_directory / (default_file_name + util::extension::json);

    auto json_string = i18n::util::read_file(full_path);
    _document.Parse(json_string.c_str());
  }

  std::string translate(const char* composed_key_, std::size_t length_) const noexcept
  {
    std::string_view view{composed_key_, length_};
    auto member_iterator = _document.MemberEnd();
    bool first_time = true;

    for (i18n::util::split_iterator it{view}; !(*it).empty(); ++it)
    {
      const auto key_str = std::string(*it);
      const auto& key = key_str.c_str();

      if (first_time)
      {
        member_iterator = _document.FindMember(key);
        first_time = false;
        if (member_iterator == _document.MemberEnd())
        {
          return std::string{view};
        }
      }
      else
      {
        auto old_member_iterator = member_iterator;
        member_iterator = member_iterator->value.FindMember(key);

        if (member_iterator == old_member_iterator->value.MemberEnd())
        {
          return std::string{view};
        }
      }
    }

    if (member_iterator == _document.MemberEnd() || member_iterator->value.IsNull() ||
        !member_iterator->value.IsString())
    {
      return std::string{view};
    }

    return member_iterator->value.GetString();
  }

 private:
  ::rapidjson::Document _document;
  std::filesystem::path _directory_path;
};
}  // namespace i18n::translators
