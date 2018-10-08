#pragma once


#include "nonterminal_classification.hh"


namespace lexer
{


/**
 * A lexical token
**/
class token
{

public:


  /**
   * Constructs a token with the given nonterminal class, line and coloumn
   *
   * ntclass -- The given nonterminal class
   * line    -- The line the token appears on
   * column  -- The column the token appears on
  **/
  token(nonterminal_classification classification, int line, int column) noexcept
    : _classification{classification}, _line{line}, _column{column}
  {}


  /**
   * Returns the classification of the token
  **/
  const nonterminal_classification& classification() const noexcept
  {
    return _classification;
  }


  /**
   * Returns the line number of the token
  **/
  const int& line() const noexcept
  {
    return _line;
  }


  /**
   * Returns the column number of the token
  **/
  const int& column() const noexcept
  {
    return _column;
  }


private:


  nonterminal_classification _classification;
  int _line;
  int _column;

};


}
