// This file will have implementation of markdown lexer
#pragma once

#include <string>
#include <vector>

namespace utl
{
  enum class Token_type
  {
    HEADING,
    BOLD,
    ITALIC,
    TEXT,
    UNKNOWN,
    END_OF_FILE
  };

  struct Token
  {
    Token_type _type;
    std::string _value;

    Token() : _type(Token_type::UNKNOWN), _value("") {}
    Token(Token_type type, std::string value) : _type(type), _value(value) {}
  };

  class Md_lexer
  {
    size_t _pos;
    char _current_char;
    std::vector<Token> _tokens;
    std::string _input;

  public:
    Md_lexer(std::string input) : _pos(0), _input(input) { advance(); }

    void advance()
    {
      _pos++;
      if (_pos < _input.size())
        _current_char = _input[_pos];
      else
        _current_char = '\0';  // End of file!
    }
  };

}  // namespace utl
