#pragma once


#include "token.hh"


#include <stdexcept>
#include <string>


/**
 * This signals when an exception has occured during parsing
**/
class parse_exception : public std::runtime_error
{

public:

  /**
   * Constructs a parse_exception with the given token
   *
   * t -- The given token
  **/
  parse_exception(lexer::token t)
    : std::runtime_error("Unexpected token at " + std::to_string(t.line()) + ":" + std::to_string(t.column())), _token(t)
  {}


private:


  const lexer::token _token;

};
