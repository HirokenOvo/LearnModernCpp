#include "cappuccino.h"
#include "ingredient.h"
#include "sub_ingredients.h"

Cappuccino::Cappuccino()
{
  this->name = "Cappuccino";
  this->ingredients.push_back(new Espresso(2));
  this->ingredients.push_back(new Milk(2));
  this->ingredients.push_back(new MilkFoam(1));
}

Cappuccino::Cappuccino(const Cappuccino &cap)
{
  this->name = cap.name;
  build(side_items, cap.side_items);
  build(ingredients, cap.ingredients);
}

Cappuccino::~Cappuccino()
{
  for (const auto &i : side_items)
    delete i;
  side_items.clear();
}

void Cappuccino::operator=(const Cappuccino &cap)
{
  if (this == &cap)
  {
    return;
  }
  for (const auto &i : side_items)
    delete i;
  side_items.clear();
  for (const auto &i : ingredients)
    delete i;
  ingredients.clear();
  this->name = cap.name;
  build(side_items, cap.side_items);
  build(ingredients, cap.ingredients);
}

std::string Cappuccino::get_name() { return this->name; }

double Cappuccino::price()
{
  double ans{0};
  for (auto &t : this->side_items)
    ans += t->price();

  for (auto &t : this->ingredients)
    ans += t->price();
  return ans;
}

void Cappuccino::add_side_item(Ingredient *side)
{
  this->side_items.push_back(side);
}

std::vector<Ingredient *> &Cappuccino::get_side_items()
{
  return this->side_items;
}
