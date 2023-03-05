#include "shared_ptr.h"
#include "shared_ptr.hpp"
#include "unique_ptr.h"
#include "unique_ptr.hpp"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char **argv)
{
  if (false) // make false to run unit-tests
             //   if (true) // make false to run unit-tests
  {
    SharedPtr<std::string> ptr{new std::string{"hello world!"}};
    EXPECT_EQ(ptr->length(), 12);
    ptr.reset();
    EXPECT_EQ(ptr.get(), nullptr);
    std::cout << "A" << std::endl;
    EXPECT_EQ(ptr.use_count(), 0);
    std::cout << "passed" << std::endl;
  }
  else
  {
    ::testing::InitGoogleTest(&argc, argv);
    std::cout << "RUNNING TESTS ..." << std::endl;
    int ret{RUN_ALL_TESTS()};
    if (!ret)
      std::cout << "<<<SUCCESS>>>" << std::endl;
    else
      std::cout << "FAILED" << std::endl;
  }
  return 0;
}