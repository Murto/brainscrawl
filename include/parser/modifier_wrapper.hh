#pragma once


#include "nonterminal_classification.hh"


namespace parser
{


/**
 * A wrapper for classification modifiers used in the brainfuck grammar
**/
class modifier_wrapper
{

public:


  /**
   * The possible modifiers for a classification
  **/
  enum class modifier_class
  {

    NONE,
    REPETITION

  };


  /**
   * Constructs a modifier with the given classification
  **/
  modifier_wrapper(nonterminal_classification classification, modifier_class modifier = modifier_class::NONE)
    : _classification{classification}, _modifier{modifier}
  {}


  /**
   * Returns the classification this wrapper is associated with
  **/
  const nonterminal_classification& classification() const
  {
    return _classification;
  }


  /**
   * Returns the modifier this wrapper represents
  **/
  const modifier_class modifier() const
  {
    return _modifier;
  }


private:


  const nonterminal_classification _classification;
  const modifier_class _modifier;

};


}
