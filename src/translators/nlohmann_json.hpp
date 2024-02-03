#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include "i18n/i18n.hpp"
#include "i18n/utils.hpp"

namespace i18n::translators
{
class nlohmann_json
{
public:
  void initialize()
  {
    const auto locale = i18n::locale();
    const std::filesystem::path full_path = default_directory_name / locale / (default_file_name + _file_extension);
    auto json_string = i18n::utils::read_file(full_path);
    _object = nlohmann::json::parse(std::move(json_string));
  }

  std::string translate(const char* composed_key, std::size_t length) const
  {
    std::string_view view{composed_key, length};
    i18n::split_iterator it{view};

    auto* current_object = &_object;

    for (i18n::split_iterator it{view}; !(*it).empty(); ++it)
    {
      const std::string_view key = *it;

      if (current_object->contains(key))
      {
        current_object = &((*current_object)[key]);
      }
      else
      {
        return std::string{view};
      }
    }

    if (current_object->is_null() || !current_object->is_string())
    {
      return std::string{view};
    }

    return current_object->get<std::string>();
  }

private:
  nlohmann::json _object;
  std::string _file_extension = ".json";
};
}
