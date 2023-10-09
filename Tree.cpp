#include "Tree.h"
#include "Student.h"
#include <iostream>
#include <regex>
#include <string>

bool checkNameValidity(std::string name) {
  std::regex pattern("^[a-zA-Z ]*$");
  if (std::regex_match(name, pattern))
    return true;
  return false;
}

bool checkIDValidity(int id) {
  std::string strID = std::to_string(id);
  std::regex pattern("^[0-9]{8}$");
  if (std::regex_match(strID, pattern))
    return true;
  return false;
}

Student *insertS(Student *root, std::string NAME, int ID) {
  if (root == nullptr) {
    return new Student(NAME, ID);
    std::cout << "successful" << std::endl;
  } else if (ID < root->id)
    root->left = insertS(root->left, NAME, ID);
  else if (ID > root->id)
    root->right = insertS(root->right, NAME, ID);
  else
    std::cout << "unsuccessful" << std::endl;

  return root;
}

Student *rotateLeft(Student *node) {

  Student *grandchild = node->right->left;
  Student *newParent = node->right;
  newParent->left = node;
  node->right = grandchild;
  return newParent;
}

Student *rotateRight(Student *node) {
  Student *grandchild = node->left->right;
  Student *newParent = node->left;
  newParent->right = node;
  node->left = grandchild;
  return newParent;
}

void Tree::insert(std::string NAME, int ID) {

  // Check's if name and ID are valid, if they aren't 'unsuccessful' is printed
  // and it returns out of the function
  if (!checkNameValidity(NAME) || !checkIDValidity(ID)) {
    std::cout << "unsuccessful\n";
    return;
  }
  insertS(root, NAME, ID);
}
