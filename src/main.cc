#include "token.hh"
#include "tokeniser.hh"
#include "parser.hh"


#include <fstream>
#include <iostream>
#include <iterator>
#include <string>


int main(int argc, char* argv[])
{

  // If there are no arguments then exit
  if (argc != 3)
  {
    std::cout << argv[0] << " [-i file | -c file]\n";
    return 1;
  }

  std::string option(argv[1]);
  std::ifstream file(argv[2]);

  if (option != "-i" && option != "-c")
  {
    std::cout << "Invalid option\n";
    return 1;
  }
  
  if (!file)
  {
    std::cout << "Invalid file\n";
    return 1;
  }

  // Create a tokeniser
  auto t = lexer::make_tokeniser(std::istream_iterator<char>(file), std::istream_iterator<char>());

  // Create a parser
  auto p = parser::make_parser(t);

  p.parse();
}
