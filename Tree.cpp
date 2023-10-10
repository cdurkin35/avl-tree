#include "Tree.h"
#include "Student.h"
#include <iostream>
#include <regex>
#include <string>
#include <vector>

// Function declaration's
int getHeight(Student *node);
void updateHeight(Student *node);
bool checkNameValidity(std::string name);
bool checkIDValidity(int id);
Student *insertS(Student *root, std::string NAME, int ID);
Student *deleteS(Student *root, int ID);
Student *rotateLeft(Student *node);
Student *rotateRight(Student *node);
Student *balanceTree(Student *root);
Student *searchI(Student *root, int ID);
void searchN(Student *root, std::string NAME, int *x);
void inOrder(Student *root, std::string &names);
void preOrder(Student *root, std::string &names);
void postOrder(Student *root, std::string &names);

int getHeight(Student *node) {
  if (node == nullptr) {
    return 0;
  }
  return node->height;
}

void updateHeight(Student *node) {
  if (node == nullptr) {
    return;
  }
  node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
}

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

Student *deleteS(Student *root, int ID) {

  if (root == nullptr) {
    std::cout << "unsuccessful" << std::endl;
    return nullptr;
  } else if (ID < root->id) {
    root->left = deleteS(root->left, ID);
  } else if (ID > root->id) {
    root->right = deleteS(root->left, ID);
  } else {
    if (root->left == nullptr) {
      Student *temp = root->right;
      delete root;
      return temp;
    } else if (root->right == nullptr) {
      Student *temp = root->left;
      delete root;
      return temp;
    } else {
      Student *successor = root->right;
      while (successor != nullptr) {
        successor = successor->left;
      }
      root->id = successor->id;
      root->name = successor->name;
      root->right = deleteS(root->right, successor->id);
    }
    std::cout << "successful" << std::endl;
  }
  return root;
}

Student *searchI(Student *root, int ID) {
  if (root == nullptr) {
    std::cout << "unsuccessful" << std::endl;
    return nullptr;
  } else if (ID < root->id) {
    root->left = searchI(root->left, ID);
  } else if (ID > root->id) {
    root->right = searchI(root->right, ID);
  } else {
    std::cout << root->name << "\n";
  }
  return root;
}

void searchN(Student *root, std::string NAME, int *x) {

  if (root == nullptr) {
    return;
  }
  if (root->name == NAME) {
    std::cout << root->id << "\n";
    (*x)++;
  }
  searchN(root->left, NAME, x);
  searchN(root->right, NAME, x);
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

void inOrder(Student *root, std::string &names) {
  if (root == nullptr) {
    return;
  }
  inOrder(root->left, names);
  names += root->name + ",";
  inOrder(root->right, names);
}

void preOrder(Student *root, std::string &names) {
  if (root == nullptr) {
    return;
  }
  names += root->name + ",";
  preOrder(root->left, names);
  preOrder(root->right, names);
}

void postOrder(Student *root, std::string &names) {
  if (root == nullptr) {
    return;
  }
  postOrder(root->left, names);
  postOrder(root->right, names);
  names += root->name + ",";
}

Student *balanceTree(Student *root) {

  if (root == nullptr) {
    return nullptr;
  }
  updateHeight(root);
  int balanceFactor = getHeight(root->left) - getHeight(root->right);

  if (balanceFactor > 1) { // Tree is left heavy

    if (getHeight(root->left->left) >=
        getHeight(root->left->right)) { // Left Left

      return rotateRight(root);

    } else {

      root->left = rotateLeft(root->left);
      return rotateRight(root);
    }

  } else if (balanceFactor < -1) {

    if (getHeight(root->right->right) >= getHeight(root->right->left)) {

      return rotateLeft(root);

    } else {

      root->right = rotateRight(root->right);
      return rotateLeft(root);
    }
  }
  return root; // Balancing is not needed
}

void getNthID(Student *root, int N, int &count, int &ID) {
  if (root == nullptr) {
    return;
  }
  getNthID(root->left, N, count, ID);
  if (count == N) {
    ID = root->id;
  }
  count++;
  getNthID(root->right, N, count, ID);
}

void Tree::insert(std::string NAME, int ID) {

  // Check's if name and ID are valid, if they aren't 'unsuccessful' is printed
  // and it returns out of the function
  if (!checkNameValidity(NAME) || !checkIDValidity(ID)) {
    std::cout << "unsuccessful";
    return;
  }
  root = insertS(root, NAME, ID);
  root = balanceTree(root);
}

void Tree::remove(int ID) {

  if (!checkIDValidity(ID)) {
    std::cout << "unsuccessful\n";
    return;
  }
  root = deleteS(root, ID);
  root = balanceTree(root);
}

void Tree::search(int ID) {

  if (!checkIDValidity(ID)) {
    std::cout << "unsuccessful\n";
    return;
  }
  root = searchI(root, ID);
}

void Tree::search(std::string NAME) {

  int *count = 0;
  searchN(root, NAME, count);
  std::cout << ((*count) > 0 ? "" : "unsuccessful\n");
}

void Tree::printInorder() {
  std::string names = "";
  inOrder(root, names);
  names.pop_back();
  std::cout << names << "\n";
}

void Tree::printPreOrder() {
  std::string names = "";
  inOrder(root, names);
  names.pop_back();
  std::cout << names << "\n";
}

void Tree::printPostOrder() {
  std::string names = "";
  inOrder(root, names);
  names.pop_back();
  std::cout << names << "\n";
}

void Tree::printLevelCount() {
  if (root == nullptr) {
    std::cout << 0;
  } else {
    updateHeight(root);
    std::cout << (root->height);
  }
}

void Tree::removeInorder(int N) {
  int count = 0;
  int id = 0;
  getNthID(root, N, count, id);
  if (id == 0) {
    std::cout << "unsuccessful\n";
  } else {
    root = deleteS(root, id);
    root = balanceTree(root);
  }
}
