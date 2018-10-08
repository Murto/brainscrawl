#pragma once


#include "nonterminal_classification.hh"


#include <unordered_map>


namespace lexer
{


/**
 * A lexer for the brainfuck language
**/
template <typename input_it_type>
class tokeniser
{

public:


  /**
   * Constructs a tokeniser with the given begin and end input iterator
   *
   * begin -- The given begin input iterator
   * end   -- The given end input iterator
  **/
  tokeniser(input_it_type begin, input_it_type end) noexcept
    : _curr{begin}, _end{end}
  {}


  /**
   * Returns the next token from the input
  **/
  token next() noexcept
  {
    // Static map of characters to nonterminal classes for tokenisation
    const static std::unordered_map<char, nonterminal_classification> classifications = {
                                                                                          { '<' , nonterminal_classification::MOVE_LEFT },
                                                                                          { '>' , nonterminal_classification::MOVE_RIGHT },
                                                                                          { '+' , nonterminal_classification::INCREMENT },
                                                                                          { '-' , nonterminal_classification::DECREMENT },
                                                                                          { '.' , nonterminal_classification::OUTPUT },
                                                                                          { ',' , nonterminal_classification::INPUT },
                                                                                          { '[' , nonterminal_classification::LOOP_BEGIN },
                                                                                          { ']' , nonterminal_classification::LOOP_END }
                                                                                        };

    // While the end of input has not been reached
    while (_curr != _end)
    {

      // Record current input character and location
      auto input = *_curr;
      auto line = _line;
      auto column = _column;
      
      // Increment input iterator
      ++_curr;

      // Newline constant
      const auto NEWLINE = '\n';
      
      // Return a token if a valid classification exists
      if (classifications.find(input) != classifications.end())
      {
        ++_column;
        return token(classifications.at(input), line, column);
      }

      // If the input is a newline, update the line and column numbers accordingly
      else if (input == NEWLINE)
      {
        ++_line;
        _column = 1;
      }

      // Otherwise increment the column number
      else
      {
        ++_column;
      }

    }
    
    // If we have reached end of input then return an EOI token
    return token(nonterminal_classification::EOI, _line, _column);
    
  }
  

private:


  input_it_type _curr;
  const input_it_type _end;
  int _line = 1;
  int _column = 1;

};


/**
 * Returns a tokeniser constructed with the given begin and end iterator
 * Helpful as the user does not have to explicitly define the constructor template arguments
 *
 * begin -- The given begin iterator
 * end   -- The given end iterator
**/
template <typename input_it_type>
tokeniser<input_it_type> make_tokeniser(input_it_type begin, input_it_type end)
{
  return tokeniser<input_it_type>(begin, end);
}


}
