#pragma once

#include <cstdint>
#include <iterator>
#include <string>

namespace i18n::util
{
template <char delimeter = '.'>
class split_iterator
{
 public:
  using iterator_category = std::forward_iterator_tag;
  using value_type = char;
  using pointer = const char*;
  using reference = const char&;

  std::string_view _value;
  std::size_t _from = 0;
  std::size_t _length = 0;
  std::size_t _index = 0;

  split_iterator(std::string_view value_) : _value(value_) { operator++(); }

  split_iterator(const split_iterator& other)
      : _value(other._value), _from(other._from), _length(other._length), _index(other._index)
  {
  }

  split_iterator& operator=(const split_iterator& rhs)
  {
    _value = rhs._value;
    return *this;
  }

  std::string_view operator*() { return _value.substr(_from, _length); }

  split_iterator& operator++()
  {
    if (_index >= _value.size())
    {
      _from = 0;
      _length = 0;
      return *this;
    }

    const auto initial_index = _index;

    for (; _index < _value.size(); ++_index)
    {
      if (_value[_index] == delimeter)
      {
        _from = initial_index;
        _length = _index - initial_index;
        _index += 1;
        return *this;
      }
    }

    if (_index == _value.size())
    {
      _from = initial_index;
      _length = _index - initial_index;
    }

    return *this;
  }

  split_iterator operator++(int)
  {
    split_iterator temp(*this);
    operator++();
    return temp;
  }

  bool operator==(const split_iterator& rhs) const
  {
    return _value == rhs._value && _from == rhs.from && _length == rhs.length;
  }

  bool operator!=(const split_iterator& rhs) const { return !(*this == rhs); }
};

}  // namespace i18n
