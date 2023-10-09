#include "Student.h"
#include <iostream>
#include <string>

Student::Student(std::string Name, int Id) {
  name = Name;
  id = Id;
  left = nullptr;
  right = nullptr;
  height = 0;
}
