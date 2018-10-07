#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>

template <typename input_it_t>
void parse(input_it_t&& start, const input_it_t&& end, std::map<long long, char>& tape, long long pointer = 0)
{
  if (start == end)
  {
    return;
  }

  do
  {
    char symbol = *start;
    switch (symbol)
    {
      case '>':
      {
        ++pointer;
        break;
      }
      case '<':
      {
        --pointer;
        break;
      }
      case '+':
      {
        ++tape[pointer];
        break;
      }
      case '-':
      {
        --tape[pointer];
        break;
      }
      case '.': 
      {
        std::cout << tape[pointer];
        break;
      }
      case ',': 
      {
        std::cin >> tape[pointer];
        break;
      }
      case '[': 
      {
        std::string buffer;
        long long count = 1;
        while (++start != end)
        {
          if (*start == '[')
          {
            ++count;
          }
          else if (*start == ']' && !--count)
          {
            break;
          }
          buffer += *start;
        }
        if (start == end)
        {
          throw std::runtime_error("[ found without matching ]");
        }
        while (tape[pointer])
        {
          parse(buffer.begin(), buffer.end(), tape, pointer);
        }
        break;
      }
      case ']':
      {
        throw std::runtime_error("] found without matching [");
      }
    }
  }
  while (++start != end);
}

int main(int argc, char* argv[])
{
  if (argc < 1)
  {
    throw std::runtime_error("No file specified");
  }

  std::ifstream input(argv[1]);
  if (!input)
  {
    throw std::runtime_error("File could not be opened");
  }

  std::map<long long, char> tape;
  parse(std::istream_iterator<char>(input), std::istream_iterator<char>(), tape);
}
