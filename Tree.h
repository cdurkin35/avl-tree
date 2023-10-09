#pragma once
#include "Student.h"
#include <iostream>
#include <numeric>
#include <string>

class Tree {
public:
  Student *root;
  Tree() : root(nullptr){};
  void insert(std::string NAME, int ID);
  void remove(int ID);
  void search(int ID);
  void search(std::string NAME);
  void printInorder();
  void printPreOrder();
  void printPostOrder();
  void printLevelCount();
  void removeInorder(int N);
};
