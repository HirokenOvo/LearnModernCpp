#include "bst.h"
#include <algorithm>
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

std::ostream &operator<<(std::ostream &out, const BST::Node &node)
{
  out << &node;
  out << "\t";
  out << "=> value:" << node.value;
  out << "\t";
  out << "left:" << (node.left == nullptr ? 0 : node.left) << " "
      << (node.left == nullptr ? 0 : node.left->value);
  out << "\t\t\t";
  out << "right:" << (node.right == nullptr ? 0 : node.right) << " "
      << (node.right == nullptr ? 0 : node.right->value);
  return out << std::endl;
}

std::partial_ordering BST::Node::operator<=>(int x)
{
  return this->value <=> x;
}

bool BST::Node::operator==(int x) { return this->value == x; }

/*
    BST
*/
BST::BST(std::initializer_list<int> nodes) : root{nullptr}
{
  for (auto t : nodes)
    add_node(t);
}

BST::BST(BST &bst) : root{nullptr}
{
  if (&bst == this)
    return;
  bst.bfs([&](BST::Node *x)
          { this->add_node(x->value); });
}

BST::BST(BST &&bst)
{
  this->root = bst.root;
  bst.root = nullptr;
}

BST::~BST()
{
  std::vector<Node *> nodes;
  bfs([&nodes](BST::Node *&node)
      { nodes.push_back(node); });
  for (auto &node : nodes)
    delete node;
}

BST &BST::operator++()
{
  this->bfs([&](BST::Node *x)
            { x->value++; });
  return *this;
}

BST BST::operator++(int)
{
  BST nw{*this};
  ++(*this);
  return nw;
}

BST &BST::operator=(BST &bst)
{
  if (this != &bst)
  {
    BST::~BST();
    bst.bfs([&](BST::Node *x)
            { this->add_node(x->value); });
  }
  return *this;
}

BST &BST::operator=(BST &&bst)
{
  if (this == &bst)
    return *this;

  BST::~BST();
  this->root = bst.root;
  bst.root = nullptr;
  return *this;
}

std::ostream &operator<<(std::ostream &out, BST &bst)
{
  out << std::string(30, '*') << std::endl;
  size_t cnt{0};
  bst.bfs([&](BST::Node *&now)
          {
    cnt++;
    out << *now; });
  out << "Binary Search tree size: " << cnt << std::endl;
  return out << std::string(30, '*') << std::endl;
}

BST::Node *&BST::get_root() { return root; }

void BST::bfs(std::function<void(Node *&node)> func)
{
  std::queue<BST::Node *> qe;
  if (root == nullptr)
    return;

  qe.push(root);
  while (qe.size())
  {
    auto t = qe.front();
    func(t);
    qe.pop();
    if (t->left != nullptr)
      qe.push(t->left);
    if (t->right != nullptr)
      qe.push(t->right);
  }
}

size_t BST::length()
{
  size_t cnt{0};
  std::function func = [&](BST::Node *&node)
  { cnt++; };
  this->bfs(func);
  return cnt;
}

bool BST::add_node(int value)
{
  BST::Node *nw{new BST::Node(value, nullptr, nullptr)};
  if (root == nullptr)
  {
    root = nw;
    return true;
  }
  BST::Node *now{root};
  while (1)
  {
    if (now->value == value)
      return false;
    else if (now->value < value)
    {
      if (now->right == nullptr)
      {
        now->right = nw;
        return true;
      }
      else
      {
        now = now->right;
      }
    }
    else if (now->value > value)
    {
      if (now->left == nullptr)
      {
        now->left = nw;
        return true;
      }
      else
      {
        now = now->left;
      }
    }
  }
}

BST::Node **BST::find_node(int value)
{
  auto now{get_root()};
  while (now != nullptr)
  {
    if (now->value == value)
    {
      break;
    }
    else if (now->value > value)
      now = now->left;
    else
      now = now->right;
  }
  if (now == nullptr)
    return nullptr;
  auto ans{new BST::Node *{now}};
  return ans;
}

BST::Node **BST::find_parrent(int value)
{
  if (find_node(value) == nullptr || root->value == value)
    return nullptr;

  auto now{get_root()};

  while (true)
  {
    if ((now->left != nullptr && now->left->value == value) ||
        (now->right != nullptr && now->right->value == value))
      break;

    if (now->value < value)
      now = now->right;
    else if (now->value > value)
      now = now->left;
  }
  auto ans{new BST::Node *{now}};
  return ans;
}

BST::Node **BST::find_successor(int value)
{
  auto now{find_node(value)};
  if (now == nullptr || (*now)->left == nullptr)
  {
    delete now;
    return nullptr;
  }

  auto p{(*now)->left};
  while (p->right != nullptr)
    p = p->right;
  auto ans{new BST::Node *{p}};
  delete now;
  return ans;
}
// 懒得写了直接暴力删掉重插了
// 哈哈不能暴力删，那不想写了
// 艹rnm二级指针

bool BST::delete_node(int value)
{
  auto node = find_node(value);
  auto fa = find_parrent(value);

  if (node == nullptr)
  {
    return false;
  }

  if ((*node)->left == nullptr && (*node)->right == nullptr)
  {
    if (get_root() == *node)
      root = nullptr;
    else
    {
      if (value > (*fa)->value)
        (*fa)->right = nullptr;
      else
        (*fa)->left = nullptr;
    }
  }
  else if ((*node)->left != nullptr && (*node)->right != nullptr)
  {
    auto next = find_successor(value);
    auto new_one = new Node{(*next)->value, (*node)->left, (*node)->right};
    delete_node((*next)->value);
    delete next;
    if (get_root() == *node)
    {
      new_one->left = root->left;
      new_one->right = root->right;
      root = new_one;
    }
    else
    {
      if ((*fa)->left == *node)
        (*fa)->left = new_one;
      else
        (*fa)->right = new_one;
    }
  }
  else
  {
    Node *new_one = nullptr;
    if ((*node)->left)
      new_one = (*node)->left;
    else
      new_one = (*node)->right;

    if (root == *node)
    {
      new_one->left = root->left;
      new_one->right = root->right;
      root = new_one;
    }
    else
    {
      if ((*fa)->left == *node)
        (*fa)->left = new_one;
      else
        (*fa)->right = new_one;
    }
  }
  delete *node;
  delete node;
  delete fa;

  return true;
}
