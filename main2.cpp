#include <fstream>
#include <iostream>
#include <sstream>

#include "md_lexer.hpp"
#include "md_parser.hpp"

bool is_markdown(const std::string &file_path) { return file_path.substr(file_path.find_last_of('.') + 1) == "md"; }
std::string read_file(const std::string &file_path)
{
  if (is_markdown(file_path))
  {
    std::ifstream file(file_path);
    if (!file.is_open())
      throw std::runtime_error("\n\x1B[38;2;255;0;0m[ ERROR ]: Failed to open file '" + file_path + "', does this even exist?\n\x1B[0m");
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
    file.close();
  }
  else
  {
    throw std::runtime_error("\n\x1B[38;2;255;0;0m[ ERROR ]: '" + file_path +
                             "' is not a markdown file, provide a file with '.md' extension!\x1B[0m\n");
  }
}

std::string type_to_string(utl::Token_type type)
{
  switch (type)
  {
    case utl::Token_type::HEADING_1:
      return "HEADING_1";
    case utl::Token_type::HEADING_2:
      return "HEADING_2";
    case utl::Token_type::HEADING_3:
      return "HEADING_3";
    case utl::Token_type::HEADING_4:
      return "HEADING_4";
    case utl::Token_type::BOLD:
      return "BOLD";
    case utl::Token_type::ITALIC:
      return "ITALIC";
    case utl::Token_type::TEXT:
      return "TEXT";
    case utl::Token_type::SPACE:
      return "SPACE";
    case utl::Token_type::NEWLINE:
      return "NEW LINE";
    case utl::Token_type::UNKNOWN:
      return "UNKNOWN";
    case utl::Token_type::END_OF_FILE:
      return "END_OF_FILE";
    default:
      return "UNKNOWN";
  }
}

std::string type_to_string(utl::Node_type type)
{
  switch (type)
  {
    case utl::Node_type::HEADING_1:
      return "HEADING_1";
    case utl::Node_type::HEADING_2:
      return "HEADING_2";
    case utl::Node_type::HEADING_3:
      return "HEADING_3";
    case utl::Node_type::HEADING_4:
      return "HEADING_4";
    case utl::Node_type::BOLD:
      return "BOLD";
    case utl::Node_type::ITALIC:
      return "ITALIC";
    case utl::Node_type::TEXT:
      return "TEXT";
    case utl::Node_type::UNKNOWN:
      return "UNKNOWN";
    case utl::Node_type::PARAGRAPH:
      return "PARAGRAPH";
    default:
      return "UNKNOWN";
  }
}
int main()
{
  std::string data = read_file("./test.md");
  utl::Md_lexer md(data);
  auto tokens = md.tokenize();
  utl::Md_parser mdp(tokens);
  auto parsed = mdp.parse();
  std::cout << tokens.size() << '\n';
  for (auto token : tokens)
  {
    std::string type = type_to_string(token._type);
    std::cout << "[ " << type << " ]: " << "{ " << token._value << " }" << '\n';
  }

  for (auto parsed_node : parsed)
  {
    std::string type = type_to_string(parsed_node._type);
    std::cout << "[ " << type << " ]: " << "{ " << parsed_node._content << " }" << '\n';
  }
}
