#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <cstddef>
#include <string>
#include <vector>

class Ingredient {
public:
  double get_price_unit() { return this->price_unit; }
  size_t get_units() { return this->units; }
  virtual std::string get_name() = 0;

  double price() { return this->price_unit * this->units; }

protected:
  Ingredient(double price_unit, size_t units)
      : price_unit{price_unit}, units{units} {}
  double price_unit;
  size_t units;
  std::string name;
};

#endif // INGREDIENT_H