#include "espresso_based.h"
#include "sub_ingredients.h"

void EspressoBased::brew() {}

std::vector<Ingredient *> &EspressoBased::get_ingredients()
{
  return this->ingredients;
}

EspressoBased::~EspressoBased()
{
  for (const auto &i : ingredients)
    delete i;
  ingredients.clear();
}

EspressoBased::EspressoBased() {}

EspressoBased::EspressoBased(const EspressoBased &esp) : name{esp.name}
{
  build(ingredients, esp.ingredients);
}

void EspressoBased::operator=(const EspressoBased &esp)
{
  if (this == &esp)
  {
    return;
  }
  for (auto &t : this->ingredients)
    delete t;
  this->ingredients.clear();
  build(ingredients, esp.ingredients);
  this->name = esp.name;
}