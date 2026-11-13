#ifndef RECCHECK
//if you want to add any #includes like <iostream> you must do them here (before the next endif)

#include <algorithm>
#endif

#include "equal-paths.h"
using namespace std;


// You may add any prototypes of helper functions here

//need deth of the tree from a node

int nDepth(Node* n) {
  if (n == nullptr) { // if its just null then 
    return 0;  // no detpth 
  }
  else { // return the starting node and max d
      return 1+ max(nDepth(n->left), nDepth(n->right)); // first level and then depth of Returns


  }

}



bool equalPaths(Node * root)
{
    // Add your code below
  //first root check 
  if (root == nullptr) {
    return true; // its equal if the root is j null
  }
  else if (root->left == nullptr && root->right == nullptr) {
    return true; // if its just a nodd w no children eg leaf its equal of


  }
  else if (root->left ==nullptr) {
    return equalPaths(root->right); // if its no left then explore right path eg same left

   //same for left side call again 
  }
  else if (root->right==nullptr) {
    return equalPaths(root->left); // same thing has

  }
  else { // in any other case eg theres two children or 2 paths d 
    if (equalPaths(root->left) ==false) {
      return false; // left side isnt evenS
    } 
    //same on right
    if (equalPaths(root->right)==false) {
      return false; // same if right side fails
    }
    //depths are sym
    return nDepth(root->right) == nDepth(root->left); // sides are the same det

  }

}

