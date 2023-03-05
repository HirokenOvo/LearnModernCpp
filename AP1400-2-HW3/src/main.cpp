#include "bst.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char **argv) {
  if (false) // make false to run unit-tests
  {
    BST bst{};
    bst.add_node(25);
    bst.add_node(10);
    bst.add_node(50);
    bst.add_node(65);
    bst.add_node(60);
    bst.add_node(70);
    bst.add_node(5);
    bst.add_node(2);
    bst.add_node(7);
    bst.add_node(75);
    std::cout << bst;
    EXPECT_EQ(bst.length(), 10);
    EXPECT_TRUE(bst.delete_node(50)); // only right child
    EXPECT_EQ(bst.length(), 9);
    EXPECT_EQ(bst.get_root()->right->value, 65);
    EXPECT_EQ(bst.get_root()->right->right->value, 70);
    EXPECT_EQ(bst.get_root()->right->right->right->value, 75);
    EXPECT_EQ(bst.get_root()->right->left->value, 60);
    EXPECT_EQ(bst.get_root()->right->left->left, nullptr);
    EXPECT_EQ(bst.get_root()->right->left->right, nullptr);
    std::cout << "passed" << std::endl;
  } else {
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