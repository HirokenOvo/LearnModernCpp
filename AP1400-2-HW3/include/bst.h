#ifndef BST_H
#define BST_H
#include <compare>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <queue>
class BST {
public:
  class Node {
  public:
    int value;
    Node *left, *right;

    Node();
    Node(const Node &node);
    Node(int value, Node *left, Node *right);

    friend std::ostream &operator<<(std::ostream &out, const Node &node);
    std::partial_ordering operator<=>(int x);
    bool operator==(int x);
  };

  BST(std::initializer_list<int> nodes);
  BST(BST &bst);
  BST(BST &&bst);
  ~BST();
  BST &operator++();
  BST operator++(int);
  BST &operator=(BST &bst);
  BST &operator=(BST &&bst);

  Node *&get_root();
  void bfs(std::function<void(Node *&node)> func);
  size_t length();
  bool add_node(int value);
  Node **find_node(int value);
  Node **find_parrent(int value);
  Node **find_successor(int value);
  bool delete_node(int value);
  friend std::ostream &operator<<(std::ostream &out, BST &bst);

private:
  Node *root;
};
#endif // BST_H