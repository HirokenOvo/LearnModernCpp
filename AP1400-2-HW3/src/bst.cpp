#include "bst.h"
#include <compare>
#include <cstddef>
#include <initializer_list>
#include <ostream>
/*
    Node
*/
BST::Node::Node() : value{0}, left{nullptr}, right{nullptr} {}

BST::Node::Node(const Node &node)
    : value{node.value}, left{node.left}, right{node.right} {}

BST::Node::Node(int value, Node *left, Node *right)
    : value{value}, left{left}, right{right} {}

std::ostream &operator<<(std::ostream &out, const BST::Node node) {
  return out << &node << "       => value:" << node.value
             << "        left:" << node.left << "      right:" << node.right
             << std::endl;
}

std::partial_ordering BST::Node::operator<=>(int x) {
  return this->value <=> x;
}

bool BST::Node::operator==(int x) { return this->value == x; }

/*
    BST
*/
BST::BST(std::initializer_list<int> nodes) : root{nullptr} {
  for (auto t : nodes)
    add_node(t);
}

BST::BST(BST &bst) : root{nullptr} {
  if (&bst == this)
    return;
  bst.bfs([&](BST::Node *x) { this->add_node(x->value); });
}

BST::BST(BST &&bst) {
  this->root = bst.root;
  bst.root = nullptr;
}

BST::~BST() {
  std::vector<Node *> nodes;
  bfs([&nodes](BST::Node *&node) { nodes.push_back(node); });
  for (auto &node : nodes)
    delete node;
}

BST &BST::operator++() {
  this->bfs([&](BST::Node *x) { x->value++; });
  return *this;
}

BST BST::operator++(int) {
  BST nw{*this};
  ++(*this);
  return nw;
}

BST &BST::operator=(BST &bst) {
  if (this != &bst) {
    BST::~BST();
    bst.bfs([&](BST::Node *x) { this->add_node(x->value); });
  }
  return *this;
}

BST &BST::operator=(BST &&bst) {
  if (this == &bst)
    return *this;

  BST::~BST();
  this->root = bst.root;
  bst.root = nullptr;
  return *this;
}

BST::Node *&BST::get_root() { return root; }

void BST::bfs(std::function<void(Node *&node)> func) {
  std::queue<BST::Node *> qe;
  if (root == nullptr)
    return;

  qe.push(root);
  while (qe.size()) {
    auto t = qe.front();
    func(t);
    qe.pop();
    if (t->left != nullptr)
      qe.push(t->left);
    if (t->right != nullptr)
      qe.push(t->right);
  }
}

size_t BST::length() {
  size_t cnt{0};
  std::function func = [&](BST::Node *&node) { cnt++; };
  this->bfs(func);
  return cnt;
}

bool BST::add_node(int value) {
  BST::Node *nw{new BST::Node(value, nullptr, nullptr)};
  if (root == nullptr) {
    root = nw;
    return true;
  }
  BST::Node *now{root};
  while (1) {
    if (now->value == value)
      return false;
    else if (now->value < value) {
      if (now->right == nullptr) {
        now->right = nw;
        return true;
      } else {
        now = now->right;
      }
    } else if (now->value > value) {
      if (now->left == nullptr) {
        now->left = nw;
        return true;
      } else {
        now = now->left;
      }
    }
  }
}

BST::Node **BST::find_node(int value) {
  BST::Node **now{&root};
  while (*now != nullptr) {
    if ((*now)->value == value)
      return now;
    else if ((*now)->value > value)
      now = &((*now)->left);
    else if ((*now)->value < value)
      now = &((*now)->right);
  }
  return nullptr;
}

void check(BST::Node now) {
  if (now.left)
    check(*now.left);
  std::cout << now;
  if (now.right)
    check(*now.right);
}

BST::Node **BST::find_parrent(int value) {
  if (find_node(value) == nullptr || root->value == value)
    return nullptr;

  BST::Node **now{&root};

  while (1) {
    if (((*now)->left != nullptr && (*now)->left->value == value) ||
        ((*now)->right != nullptr && (*now)->right->value == value))
      return now;

    if ((*now)->value < value)
      now = &((*now)->right);
    else if ((*now)->value > value)
      now = &((*now)->left);
  }
}

BST::Node **BST::find_successor(int value) {
  BST::Node **now{find_node(value)};
  if (now == nullptr)
    return nullptr;

  if ((*now)->left == nullptr)
    return nullptr;

  now = &((*now)->left);
  while ((*now)->right != nullptr)
    now = &((*now)->right);

  return now;
}
// 懒得写了直接暴力删掉重插了
// 哈哈不能暴力删，那不想写了
bool BST::delete_node(int value) {
  BST::Node **removing_node{BST::find_node(value)};
  if (removing_node == nullptr)
    return false;

  std::vector<int> ve;
  std::queue<BST::Node *> qe;
  qe.push(*removing_node);

  BST::Node **fa{BST::find_parrent(value)};
  while (qe.size()) {
    auto t = qe.front();
    qe.pop();
    if (t->left)
      qe.push(t->left);
    if (t->right)
      qe.push(t->right);
    ve.push_back(t->value);
    if (*t == value)
      continue;
    delete t;
  }

  if ((*fa)->left != nullptr && (((*fa)->left->value) == value))
    (*fa)->left = nullptr;
  else if ((*fa)->right != nullptr && (((*fa)->right->value) == value)) {
    (*fa)->right = nullptr;
    delete (*fa)->right;
  }

  for (auto &t : ve) {
    if (t == value)
      continue;
    add_node(t);
  }

  return true;
}

std::ostream &operator<<(std::ostream &out, BST &bst) {
  out << std::string(30, '*') << std::endl;
  size_t cnt{0};
  bst.bfs([&](BST::Node *&now) {
    cnt++;
    out << *now;
  });
  out << "Binary Search tree size: " << cnt << std::endl;
  return out << std::string(30, '*') << std::endl;
}