#pragma once


#include "modifier_wrapper.hh"
#include "nonterminal_classification.hh"


#include <functional>
#include <unordered_map>
#include <vector>


namespace parser
{


std::vector<std::vector<modifier_wrapper>> productions(nonterminal_classification classification)
{
  // Create modifier instances for each nonterminal-modifier pair used in productions
  const static modifier_wrapper commands(nonterminal_classification::COMMAND, modifier_wrapper::modifier_class::REPETITION);
  const static modifier_wrapper loop(nonterminal_classification::LOOP);
  const static modifier_wrapper move_left(nonterminal_classification::MOVE_LEFT);
  const static modifier_wrapper move_right(nonterminal_classification::MOVE_RIGHT);
  const static modifier_wrapper increment(nonterminal_classification::INCREMENT);
  const static modifier_wrapper decrement(nonterminal_classification::DECREMENT);
  const static modifier_wrapper output(nonterminal_classification::OUTPUT);
  const static modifier_wrapper input(nonterminal_classification::INPUT);
  const static modifier_wrapper loop_begin(nonterminal_classification::LOOP_BEGIN);
  const static modifier_wrapper loop_end(nonterminal_classification::LOOP_END);
  const static modifier_wrapper eoi(nonterminal_classification::EOI);
  
  // Create map representing productions
  const static std::unordered_map<nonterminal_classification, std::vector<std::vector<modifier_wrapper>>> prods = {
                                                                                                                    {
                                                                                                                      nonterminal_classification::PROGRAM,
                                                                                                                      {
                                                                                                                        {
                                                                                                                          commands,
                                                                                                                          eoi
                                                                                                                        }
                                                                                                                      }
                                                                                                                    },

                                                                                                                    {
                                                                                                                      nonterminal_classification::COMMAND,
                                                                                                                      {
                                                                                                                        {
                                                                                                                          move_left
                                                                                                                        },

                                                                                                                        {
                                                                                                                          move_right
                                                                                                                        },

                                                                                                                        {
                                                                                                                          increment
                                                                                                                        },

                                                                                                                        {
                                                                                                                          decrement
                                                                                                                        },

                                                                                                                        {
                                                                                                                          output
                                                                                                                        },

                                                                                                                        {
                                                                                                                          input
                                                                                                                        },

                                                                                                                        {
                                                                                                                          loop
                                                                                                                        }
                                                                                                                      }
                                                                                                                    },

                                                                                                                    {
                                                                                                                      nonterminal_classification::LOOP,
                                                                                                                      {
                                                                                                                        {
                                                                                                                          loop_begin,
                                                                                                                          commands,
                                                                                                                          loop_end
                                                                                                                        }
                                                                                                                      }
                                                                                                                    }
                                                                                                                  };
  
  // Find nonterminal_classification production
  auto class_prods = prods.find(classification);

  // If found then return it
  if (class_prods != prods.end())
  {
    return class_prods->second;
  }

  // Otherwise return an empty vector of vectors
  else
  {
    return {};
  }
}


}
