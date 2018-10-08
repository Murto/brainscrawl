#pragma once


#include "nonterminal_classification.hh"
#include "parse_exception.hh"
#include "productions.hh"
#include "token.hh"
#include "tokeniser.hh"


#include <list>
#include <unordered_set>


namespace parser
{


/**
 * A parser for the brainfuck language
**/
template <typename input_it_type>
class parser
{

public:

  
  /**
   * Constructs a parser with the given tokeniser
   *
   * t -- The given tokeniser
  **/
  parser(lexer::tokeniser<input_it_type> t)
    : _tokeniser{t}
  {}


  /**
   * Parses the token sequence given by the associated tokeniser and returns an abstract syntax tree
  **/
  void parse()
  {

    // Create initial nonterminal
    const static modifier_wrapper program(nonterminal_classification::PROGRAM);

    // The list of possible parses
    std::list<std::list<modifier_wrapper>> possible = { { program } };

    // While there are possible parses
    while (!possible.empty())
    {

      // The list of possible parses beginning with a terminal
      std::list<std::list<modifier_wrapper>> nexts;

      // While there are possible parses
      while (!possible.empty())
      {

        // Get the first possible parse
        const auto& par = possible.front();

        // If its empty then a valid parse has been found
        if (par.empty())
        {
          return;
        }

        // Get the first modifier of a classification
        const auto& mod = par.front();

        // If its a repetition then branch possible parses
        if (mod.modifier() == modifier_wrapper::modifier_class::REPETITION)
        {

          // End of repetition
          auto less = par;
          less.pop_front();
          possible.push_back(less);

          // Continuation of repetition
          auto more = par;
          more.push_front(modifier_wrapper(mod.classification()));
          possible.push_back(more);

          // Remove current possible parse
          possible.pop_front();

          // Jump back to start of loop
          continue;
        }
        
        // Get productions for first nonterminal
        const auto& prods = productions(mod.classification());

        // If there are no productions, its a terminal
        if (prods.empty())
        {

          // Add it to the list of expanded parses
          nexts.push_back(par);

          // Remove the current parse
          possible.pop_front();
        }

        // Otherwise, if there are productions expand them
        else
        {

          // Create a new possible parse for each production
          for (const auto& prod : prods)
          {

            // Copy current parse
            auto copy = par;

            // Remove the first classification modifier
            copy.pop_front();

            // Insert the production
            copy.insert(copy.begin(), prod.begin(), prod.end());

            // Add it to the list of possible parses
            possible.push_back(copy);

          }
          
          // Remove the current parse
          possible.pop_front();
        }
      }

      // A set of expected classifications
      std::unordered_set<nonterminal_classification> expected;

      // Collect first terminal from each possible parse
      for (const auto& next : nexts)
      {
        expected.insert(next.front().classification());
      }
      
      // Get the next token
      auto tok = _tokeniser.next();

      // If the token is not an expected classification then throw an exception
      if (expected.find(tok.classification()) == expected.end())
      {
        throw parse_exception(tok);
      }

      // Otherwise remove the possible parses that do not begin with token classification
      else
      {
        for (auto it = nexts.begin(); it != nexts.end(); )
        {

          // Remove parse if it does not begin with token classification
          if (it->front().classification() != tok.classification())
          {
            it = nexts.erase(it);
          }

          // Otherwise remove the terminal and increment the iterator
          else
          {
            it->pop_front();
            possible.push_back(*it);
            ++it;
          }
        }
      }
    }
  }


private:


  lexer::tokeniser<input_it_type> _tokeniser;

};


/**
 * Returns a parser constructed with the given tokeniser
 * Helpful as the user does not have to explicitly define the constructor template argument
 *
 * t - The given tokeniser
**/
template <typename input_it_type>
parser<input_it_type> make_parser(lexer::tokeniser<input_it_type> t)
{
  return parser<input_it_type>(t);
}


}
