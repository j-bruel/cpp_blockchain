#pragma once

#include "my_blockchain_export.hpp"

#include <stdexcept>

namespace centor
{

  struct MY_BLOCKCHAIN_EXPORT blockchain_handling_exception : public std::runtime_error
  {
    using std::runtime_error::runtime_error;
  };

}