#include "mocha.h"
#include "sub_ingredients.h"

Mocha::Mocha()
{
  this->name = "Mocha";
  this->ingredients.push_back(new Espresso(2));
  this->ingredients.push_back(new Milk(2));
  this->ingredients.push_back(new MilkFoam(1));
  this->ingredients.push_back(new Chocolate(1));
}

Mocha::Mocha(const Mocha &cap)
{
  this->name = cap.name;
  build(side_items, cap.side_items);
  build(ingredients, cap.ingredients);
}

Mocha::~Mocha()
{
  for (const auto &i : side_items)
    delete i;
  side_items.clear();
}

void Mocha::operator=(const Mocha &cap)
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

std::string Mocha::get_name() { return this->name; }

double Mocha::price()
{
  double ans{0};
  for (auto &t : this->side_items)
    ans += t->price();
  for (auto &t : this->ingredients)
    ans += t->price();
  return ans;
}

void Mocha::add_side_item(Ingredient *side)
{
  this->side_items.push_back(side);
}

std::vector<Ingredient *> &Mocha::get_side_items() { return this->side_items; }
