// ======================================================================
// \title  Random.cpp
// \author bocchino
// \brief  Random number generation
//
// \copyright
// Copyright (C) 2017-2022 California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged.
// ======================================================================

#include <cassert>
#include <cinttypes>
#include <ctime>

#include "STest/Random/Random.hpp"

extern "C" {
#include "STest/Random/bsd_random.h"
}

namespace STest {

  namespace Random {

    namespace SeedValue {

      U32 getFromTime() {
        struct timeval tv;
        (void) gettimeofday(&tv, nullptr);
        return static_cast<U32>(tv.tv_usec);
      }

      bool getFromFile(
          const char *const fileName,
          U32& value
      ) {
        bool result = false;
        FILE *fp = fopen(fileName, "r");
        if (fp != nullptr) {
          result = (fscanf(fp, "%" PRIu32, &value) == 1);
          (void) fclose(fp);
        }
        return result;
      }

      void set(const U32 value) {
        bsd_srandom(value);
      }

      bool appendToFile(
          const char *const fileName,
          const U32 seedValue
      ) {
        bool result = false;
        FILE *fp = fopen(fileName, "a");
        if (fp != nullptr) {
          int status = fprintf(
              fp,
              "%" PRIu32 "\n",
              seedValue
          );
          result = (status > 0);
          (void) fclose(fp);
        }
        return result;
      }

    }

    void seed() {
      U32 seedValue = 0;
      const bool seedValueOK =
        SeedValue::getFromFile("seed", seedValue);
      if (seedValueOK) {
        (void) printf("[STest::Random] Read seed %" PRIu32 " from file\n", seedValue);
      }
      else {
        seedValue = SeedValue::getFromTime();
        (void) printf("[STest::Random] Generated seed %" PRIu32 " from system time\n", seedValue);
      }
      (void) SeedValue::appendToFile("seed-history", seedValue);
      SeedValue::set(seedValue);
    }

    U32 startLength(
        const U32 start,
        const U32 length
    ) {
      assert(length > 0);
      return lowerUpper(start, start + length - 1);
    }

    U32 lowerUpper(
        const U32 lower,
        const U32 upper
    ) {
      assert(lower <= upper);
      const F64 length = static_cast<F64>(upper) - lower + 1;
      const F64 randFloat = inUnitInterval() * length;
      const U32 offset = static_cast<U32>(randFloat);
      const U32 result = lower + offset;
      // Handle boundary case where inUnitInterval returns 1.0
      return (result <= upper) ? result : result - 1;
    }

    double inUnitInterval() {
      const long randInt = bsd_random();
      const F64 ratio = static_cast<F64>(randInt) / static_cast<F64>(MAX_VALUE);
      return ratio;
    }

  }

}
