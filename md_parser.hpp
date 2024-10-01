#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "./md_lexer.hpp"

namespace utl
{

  enum class Node_type
  {
    HEADING_1,
    HEADING_2,
    HEADING_3,
    HEADING_4,
    PARAGRAPH,
    BOLD,
    ITALIC,
    TEXT,
    UNKNOWN
  };

  struct Node
  {
    Node_type _type;
    std::string _content;
    std::vector<Node> _children;

    Node() : _type(Node_type::UNKNOWN), _content("") {}
    Node(Node_type type, const std::string &value) : _type(type), _content(value) {}
  };

  class Md_parser
  {
    size_t _pos;
    Token _current_token;
    std::vector<Token> _tokens;
    std::vector<Node> _nodes;

  public:
    Md_parser(const std::vector<Token> &tokens) : _pos(0), _tokens(tokens) { _current_token = _tokens[_pos]; }

    std::vector<Node> parse()
    {
      while (_current_token._type != Token_type::END_OF_FILE) _nodes.push_back(parse_block());
      return _nodes;
    }

  private:
    void advance()
    {
      if (_pos < _tokens.size() - 1)
        _current_token = _tokens[++_pos];
      else
        _current_token = Token(Token_type::END_OF_FILE, "");
    }

    Node parse_block()
    {
      switch (_current_token._type)
      {
        case Token_type::HEADING_1:
          return parse_heading(0);
        case Token_type::HEADING_2:
          return parse_heading(1);
        case Token_type::HEADING_3:
          return parse_heading(2);
        case Token_type::HEADING_4:
          return parse_heading(3);
        default:
          return parse_paragraph();
      }
    }

    Node parse_heading(size_t level)
    {
      Node heading_node(static_cast<Node_type>(((size_t)Node_type::HEADING_1 + level)), _current_token._value);
      advance();  // Move past the heading token
      return heading_node;
    }

    Node parse_paragraph()
    {
      std::string paragraph_content = "";
      while (_current_token._type != Token_type::END_OF_FILE && _current_token._type != Token_type::HEADING_1 &&
             _current_token._type != Token_type::HEADING_2 && _current_token._type != Token_type::HEADING_3 &&
             _current_token._type != Token_type::HEADING_4)
      {
        paragraph_content += _current_token._value;
        advance();
      }

      Node paragraph_node(Node_type::PARAGRAPH, paragraph_content);
      return paragraph_node;
    }
  };
}  // namespace utl
