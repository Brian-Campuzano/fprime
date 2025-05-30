// ======================================================================
// \title  RandomScenario.hpp
// \author bocchino
// \brief  Apply rules in a random sequence
//
// \copyright
// Copyright (C) 2017 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#ifndef STest_RandomScenario_HPP
#define STest_RandomScenario_HPP

#include "STest/Scenario/InterleavedScenario.hpp"
#include "STest/Scenario/RepeatedRuleScenario.hpp"

namespace STest {

  //! Apply rules in a random sequence
  template<typename State> class RandomScenario :
    public InterleavedScenario<State>
  {

    public:

      // ----------------------------------------------------------------------
      // Constructors and destructors
      // ----------------------------------------------------------------------

      //! Construct a RandomScenario from an array of rules
      RandomScenario(
          const char *const a_name, //!< The name of the scenario
          Rule<State>** rules, //!< The rules in the array
          const U32 size //!< The size of the array
      ) :
        InterleavedScenario<State>(a_name, new Scenario<State>*[size], size)
      {
        assert(this->scenarioArray != nullptr);
        Scenario<State>** scenarios = this->scenarioArray->getScenarios();
        assert(scenarios != nullptr);
        for (U32 i = 0; i < size; ++i) {
          scenarios[i] = new RepeatedRuleScenario<State>(*rules[i]);
        }
      }

      //! Destroy a RandomScenario
      ~RandomScenario() {
        assert(this->scenarioArray != nullptr);
        Scenario<State>** scenarios = this->scenarioArray->getScenarios();
        assert(scenarios != nullptr);
        for (U32 i = 0; i < this->scenarioArray->size; ++i) {
          assert(scenarios[i] != nullptr);
          delete scenarios[i];
        }
        delete[] scenarios;
      }

  };

}

#endif
