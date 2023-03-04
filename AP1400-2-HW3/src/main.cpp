#include "bst.h"
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char **argv) {
  if (true) // make false to run unit-tests
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

    BST::Node *address_of_5{*bst.find_node(5)};
    BST::Node *address_of_2{*bst.find_node(2)};

    EXPECT_TRUE(bst.delete_node(10)); // only left child

    // the remainig nodes should not be regenerated
    // => address of remaning nodes before and after deletion should be the same
    // when deleting a node: just reconnect the needed parrents and childs
    EXPECT_EQ(*bst.find_node(5), address_of_5);
    EXPECT_EQ(*bst.find_node(2), address_of_2);
  }
  return 0;
}