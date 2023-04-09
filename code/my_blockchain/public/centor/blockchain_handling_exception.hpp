#pragma once

#include <stdexcept>

namespace centor
{

  struct blockchain_handling_exception : public std::runtime_error
  {
    using std::runtime_error::runtime_error;
  };

}
