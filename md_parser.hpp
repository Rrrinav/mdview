#pragma once

#include "./md_lexer.hpp"

#include <string>
#include <vector>

namespace utl
{

  enum class Node_type
  {
    HEADING_1,
    HEADING_2,
    HEADING_3,
    HEADING_4,
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
  };
}  // namespace utl
