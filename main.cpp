#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Define color constants using Truecolor (RGB) codes
const std::string BOLD_ON = "\x1B[1m";
const std::string BOLD_OFF = "\x1B[0m";

// Truecolor escape codes for specific RGB values
const std::string RED_RGB = "\x1B[38;2;255;0;0m";    // Red text
const std::string BLUE_RGB = "\x1B[38;2;0;0;255m";   // Blue text
const std::string GREEN_RGB = "\x1B[38;2;0;255;0m";  // Green text
const std::string RESET = "\x1B[0m";                 // Reset colors and formatting

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

void render_heading(const std::string &line)
{
  size_t prefix = 0;
  while (prefix < line.size() && line[prefix] == '#') ++prefix;  // Count the number of '#' characters

  std::string heading = line.substr(prefix);
  switch (prefix)
  {
    case 1:
      std::cout << RED_RGB << BOLD_ON << heading << BOLD_OFF << RESET << '\n';  // H1 (Red)
      break;
    case 2:
      std::cout << BLUE_RGB << BOLD_ON << heading << BOLD_OFF << RESET << '\n';  // H2 (Blue)
      break;
    case 3:
      std::cout << GREEN_RGB << BOLD_ON << heading << BOLD_OFF << RESET << '\n';  // H3 (Green)
      break;
    default:
      std::cout << heading << '\n';  // For headings with more than 6 '#'
      break;
  }
}

void print_markdown(const std::string &content)
{
  std::string line;
  std::stringstream ss(content);
  while (std::getline(ss, line))
    if (line.find("#") == 0)
      render_heading(line);
    else
      std::cout << line << '\n';  // Print other lines as plain text
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "\n\x1B[38;2;255;0;0m[ ERROR ]:\x1B[0m Usage: " << argv[0] << " <file_path>\n";
    return EXIT_FAILURE;
  }
  try
  {
    std::string file_path = argv[1];
    std::string content = read_file(file_path);
    print_markdown(content);
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
