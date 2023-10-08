#pragma once
#include <iostream>
#include <string>

class Student {

public:
  std::string name;
  int id;
  int height;
  Student *left;
  Student *right;
  Student(std::string Name, int Id);
};
