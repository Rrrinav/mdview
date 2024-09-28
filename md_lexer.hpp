// This file will have implementation of markdown lexer
#pragma once

#include <cctype>
#include <string>
#include <vector>

namespace utl
{
  enum class Token_type
  {
    HEADING_1,
    HEADING_2,
    HEADING_3,
    HEADING_4,
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
    Token(Token_type type, const std::string &value) : _type(type), _value(value) {}
  };

  class Md_lexer
  {
    bool _at_line_start;
    size_t _pos;
    char _current_char;
    std::vector<Token> _tokens;
    std::string _input;

  public:
    Md_lexer(const std::string &input) : _pos(0), _input(input)
    {
      advance();
      _at_line_start = true;  // We assume lexer starts at the beginning of the first line.
    }

    std::vector<Token> tokenize()
    {
      while (_current_char != '\0')
      {
        if (isspace(_current_char))
        {
          handle_whitespace();
          continue;
        }
        else if (_current_char == '#' && _at_line_start)
        {
          _tokens.push_back(lex_heading());
          continue;
        }
        else 
        {
          _tokens.push_back(lex_text());
        }

        // Handle other markdown token cases (e.g., bold, italic) as needed
        // Here we can expand for further markdown token handling
      }

      return _tokens;
    }

  private:
    void advance()
    {
      if (_pos < _input.size() - 1)
        _current_char = _input[_pos++];
      else
        _current_char = '\0';  // End of file
    }

    void handle_whitespace()
    {
      // Skip whitespace, set _at_line_start to true after a newline
      while (_current_char != '\0' && isspace(_current_char))
      {
        if (_current_char == '\n')
          _at_line_start = true;  // Line starts after a newline
        advance();
      }
    }

    char peek() const { return (_pos < _input.size()) ? _input[_pos] : '\0'; }

    Token lex_heading()
    {
      size_t heading_level = 0;
      std::string heading_text = "";

      // Count the number of '#' symbols
      while (_current_char == '#')
      {
        heading_level++;
        advance();
      }

      // Skip any trailing spaces after the '#' symbols
      while (_current_char == ' ' || _current_char == '\t') advance();

      // Collect the heading content
      while (_current_char != '\n' && _current_char != '\0')
      {
        heading_text += _current_char;
        advance();
      }

      // Reset the line start flag (since we've passed the line)
      _at_line_start = false;

      // Determine token type based on heading level
      switch (heading_level)
      {
        case 1:
          return Token(Token_type::HEADING_1, heading_text);
        case 2:
          return Token(Token_type::HEADING_2, heading_text);
        case 3:
          return Token(Token_type::HEADING_3, heading_text);
        case 4:
          return Token(Token_type::HEADING_4, heading_text);
        default:
          return Token(Token_type::UNKNOWN, heading_text);  // If more than 4 '#', return as unknown
      }
    }

    Token lex_text()
    {
      std::string text = "";
      // Collect the text content
      while (_current_char != '\n' && _current_char != '\0' && !isspace(_current_char))
      {
        text += _current_char;
        advance();
      }
      // Reset the line start flag (since we've passed the line)
      _at_line_start = false;
      return Token(Token_type::TEXT, text);
    }
  };
}  // namespace utl
