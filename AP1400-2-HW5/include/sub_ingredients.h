#ifndef SUB_INGREDIENTS_H
#define SUB_INGREDIENTS_H
#include "ingredient.h"
#include <cstddef>
#include <string>

#define DEFCLASS(ClassName, PriceUnit)                                         \
  class ClassName : public Ingredient {                                        \
  public:                                                                      \
    ClassName(size_t units) : Ingredient{PriceUnit, units} {                   \
      this->name = #ClassName;                                                 \
    }                                                                          \
    virtual std::string get_name() { return this->name; }                      \
  };

DEFCLASS(Cinnamon, 5);
DEFCLASS(Chocolate, 5);
DEFCLASS(Sugar, 1);
DEFCLASS(Cookie, 10);
DEFCLASS(Espresso, 15);
DEFCLASS(Milk, 10);
DEFCLASS(MilkFoam, 5);
DEFCLASS(Water, 1);

inline void build(std::vector<Ingredient *> &tmp,
                  const std::vector<Ingredient *> &ve) {
  for (auto t : ve) {
    if (t->get_name() == "Cinnamon")
      tmp.push_back(new Cinnamon(t->get_units()));
    else if (t->get_name() == "Chocolate")
      tmp.push_back(new Chocolate(t->get_units()));
    else if (t->get_name() == "Sugar")
      tmp.push_back(new Sugar(t->get_units()));
    else if (t->get_name() == "Cookie")
      tmp.push_back(new Cookie(t->get_units()));
    else if (t->get_name() == "Espresso")
      tmp.push_back(new Espresso(t->get_units()));
    else if (t->get_name() == "Milk")
      tmp.push_back(new Milk(t->get_units()));
    else if (t->get_name() == "MilkFoam")
      tmp.push_back(new MilkFoam(t->get_units()));
    else if (t->get_name() == "Water")
      tmp.push_back(new Water(t->get_units()));
  }
}

#endif // SUB_INGREDIENTS_H