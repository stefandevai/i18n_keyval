# i18n_keyval

![build status](https://github.com/stefandevai/i18n_keyval/actions/workflows/linux.yml/badge.svg)
![build status](https://github.com/stefandevai/i18n_keyval/actions/workflows/macos.yml/badge.svg)
![build status](https://github.com/stefandevai/i18n_keyval/actions/workflows/windows.yml/badge.svg)

Easy to use and customizable internationalization library.

# Features
- [x] String literal usage
- [x] Free function usage
- [x] Nested json
- [x] Plurals
- [x] Plural interpolation
- [ ] Thread safety

# Translators
- [x] Default using `unordered_map`
- [x] nlohman/json (json)
- [x] rapidjson (json)
- [x] sol2 (lua)
- [x] pugixml (xml)
- [x] tinyxml2 (xml)
- [ ] simdjson (json)

# Usage
## Default translator

You need to provide a `i18n::translations` object containing all your locales with their respective localized strings.

**Example:**
```cpp
#include <i18n_keyval/i18n.hpp>
#include <i18n_keyval/translators/basic.hpp>

using namespace i18n::literals;

i18n::translations translations{
  {"en", {{"moon", "Moon"}, {"sun", "Sun"}}},
  {"es", {{"moon", "Luna"}, {"sun", "Sol"}}},
};

i18n::initialize_translator(translations);

i18n::set_locale("en");
std::cout << "moon"_t << '\n';
std::cout << "sun"_t << '\n';

i18n::set_locale("es");
std::cout << i18n::t("moon") << '\n';
std::cout << i18n::t("sun") << '\n';
```

**Output**:
```
Moon
Sun
Luna
Sol
```

## nlohmann/json translator

Built-in [nlohmann/json](https://github.com/nlohmann/json) translator. You need to set up the library by yourself.

**Example:**
```jsonc
// translations/en/translation.json
{
    "moon": "Moon",
    "animals": {
        "cat": "Cat"
    }
}
```
```jsonc
// translations/es/translation.json
{
    "moon": "Luna",
    "animals": {
        "cat": "Gato"
    }
}
```
```cpp
#include <i18n_keyval/i18n.hpp>
#include <i18n_keyval/translators/nlohmann_json.hpp>

using namespace i18n::literals;

i18n::initialize_translator<i18n::translators::nlohmann_json>();

// Or provide a custom directory where the translator can find the locales
// i18n::initialize_translator<i18n::translators::nlohmann_json>("data/translations");

i18n::set_locale("en");
std::cout << "moon"_t << '\n';
std::cout << "animals.cat"_t << '\n';

i18n::set_locale("es");
std::cout << i18n::t("moon") << '\n';
std::cout << i18n::t("animals.cat") << '\n';
```

**Output**:
```
Moon
Cat
Luna
Gato
```

## Custom translator
To use a custom translator, you have to provide any class that implements a `set_locale` and `translate` methods. This allows you to retrieve strings with other methods such as xml, lua, other json library or a custom container.

**Example:**
```cpp
#include <i18n_keyval/i18n.hpp>

using namespace i18n::literals;

struct translator
{
  std::string locale{};
  std::unordered_map<std::string, std::string> en_translations{{ "moon", "Moon" }};
  std::unordered_map<std::string, std::string> es_translations{{ "moon", "Luna" }};

  void set_locale(const std::string& locale)
  {
    this->locale = locale;
  }

  std::string translate(const char* key, const std::size_t length) const
  {
    if (locale == "en")
    {
      return en_translations.at(std::string(key));
    }
    else if (locale == "es")
    {
      return es_translations.at(std::string(key));
    }

    return std::string(key);
  }
};

i18n::initialize_translator<translator>();

i18n::set_locale("en");
std::cout << "moon"_t << '\n';

i18n::set_locale("es");
std::cout << i18n::t("moon") << '\n';
```

**Output**:
```
Moon
Luna
```
