#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>

/**
 * A templated class for a Node in a search tree.
 * The getters for parent/left/right are virtual so
 * that they can be overridden for future kinds of
 * search trees, such as Red Black trees, Splay trees,
 * and AVL trees.
 */
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};

/*
  -----------------------------------------
  Begin implementations for the Node class.
  -----------------------------------------
*/

/**
* Explicit constructor for a node.
*/
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

/**
* Destructor, which does not need to do anything since the pointers inside of a node
* are only used as references to existing nodes. The nodes pointed to by parent/left/right
* are freed by the BinarySearchTree.
*/
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{

}

/**
* A const getter for the item.
*/
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

/**
* A non-const getter for the item.
*/
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

/**
* A const getter for the key.
*/
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

/**
* A const getter for the value.
*/
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}

/**
* A non-const getter for the value.
*/
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}

/**
* An implementation of the virtual function for retreiving the parent.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}

/**
* An implementation of the virtual function for retreiving the left child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}

/**
* An implementation of the virtual function for retreiving the right child.
*/
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}

/**
* A setter for setting the parent of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}

/**
* A setter for setting the left child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}

/**
* A setter for setting the right child of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}

/**
* A setter for the value of a node.
*/
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}

/*
  ---------------------------------------
  End implementations for the Node class.
  ---------------------------------------
*/

/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;

    template<typename PPKey, typename PPValue>
    friend void prettyPrintBST(BinarySearchTree<PPKey, PPValue> & tree);
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator  // TODO
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;
    Value& operator[](const Key& key);
    Value const & operator[](const Key& key) const;

protected:
    // Mandatory helper functions
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    // Note:  static means these functions don't have a "this" pointer
    //        and instead just use the input argument.

    // Provided helper functions
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;

    // Add helper functions here
    // one for successor 
    static Node<Key, Value>* successor(Node<Key, Value>* current); 

    //one for no deletion to call on clear 
    void deleteNodes(Node<Key, Value>* dNode); 

    //one to track if hiehgts are balanced so i can call in isbalanced 
    //return an int 
    int heightbalanced(Node<Key, Value>* hNode) const; 


protected:
    Node<Key, Value>* root_;
    // You should not need other data members
};

/*
--------------------------------------------------------------
Begin implementations for the BinarySearchTree::iterator class.
---------------------------------------------------------------
*/

/**
* Explicit constructor that initializes an iterator with a given node pointer.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    // TODO
    current_ = ptr;
}

/**
* A default constructor that initializes the iterator to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator() 
{
    // TODO
    //same but its null 
    current_ =nullptr;

}

/**
* Provides access to the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

/**
* Provides access to the address of the item.
*/
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    if (current_ == rhs.current_) { // ceck if point at sm
      return true; // y
    }
    else {
      return false; 
      }
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    // TODO
    // same but check if its not so.
    if (current_!=rhs.current_) {
      return true;  // if the iternator point at diff
    }
    else {
      return false; 
    }

}


/**
* Advances the iterator's location using an in-order sequencing
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{
    // TODO
    // need succ as move to the next larger key sa sa
    current_ = successor(current_);  // move it to bigger node
      // return the iterator here 
    return *this; 

}


/*
-------------------------------------------------------------
End implementations for the BinarySearchTree::iterator class.
-------------------------------------------------------------
*/

/*
-----------------------------------------------------
Begin implementations for the BinarySearchTree class.
-----------------------------------------------------
*/

/**
* Default constructor for a BinarySearchTree, which sets the root to NULL.
*/
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    // TODO
    root_ = nullptr; 
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    // TODO
    // per desc clear 
    clear(); // just ts

}

/**
 * Returns true if tree is empty
*/
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

/**
* Returns an iterator to the "smallest" item in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

/**
* Returns an iterator whose value means INVALID
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
 * @precondition The key exists in the map
 * Returns the value associated with the key
 */
template<class Key, class Value>
Value& BinarySearchTree<Key, Value>::operator[](const Key& key)
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}
template<class Key, class Value>
Value const & BinarySearchTree<Key, Value>::operator[](const Key& key) const
{
    Node<Key, Value> *curr = internalFind(key);
    if(curr == NULL) throw std::out_of_range("Invalid key");
    return curr->getValue();
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
* Recall: If key is already in the tree, you should 
* overwrite the current value with the updated value.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    // TODO
    //same startneed a rpointer 
    Node<Key, Value>* rPoint = root_; //start at the root 
    // if its null 
    if (rPoint ==nullptr) {
      //whole thing is empty 
      root_= new Node<Key, Value>(keyValuePair.first, keyValuePair.second, nullptr); //no parent 
        return; // stop here
    } 
    while (rPoint!=nullptr) {
        // go trhought eh tree to insert at the empty spot here 
          // while its vaklid 
        if (rPoint->getKey()==keyValuePair.first) {
            //case where the keys are the same need to overrid
            // change the value
            rPoint->setValue(keyValuePair.second);// just change the value set it
            return; // its done replace and nothing left
        }
        else if(rPoint->getKey() < keyValuePair.first) {
          // put it right if its biggger than
          // need the empty right spot 
            if(rPoint->getRight()==nullptr) {
              Node<Key, Value>* pNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, rPoint); // make this one given its parent should be the pointer to root node so its rc
              rPoint->setRight(pNode); // put it on the rc
              return;   // insert there and thats it
            }
            else {
              //cant put it so 
              rPoint = rPoint->getRight(); // just whatever is there 
            }
        }
        else {
          // same deal for the left side need empty then insert the new or getLef 
          if (rPoint->getLeft()== nullptr) {
            Node<Key, Value>* lNode = new Node<Key, Value>(keyValuePair.first, keyValuePair.second, rPoint); //saame
            // creat that new and put in on the lc
              rPoint->setLeft(lNode);
              return; 
                //again insert here and thats it
          }
          else {
              // the lc is full 
              rPoint=rPoint->getLeft();// lef
          }
        }

    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    // TODO

    Node<Key, Value>* rmNode = internalFind(key); // make a pointer eg find the nodde kery 
    if (rmNode==nullptr) {
      return;   // if it snot there then good nothign to remove 

    }
    // okay now check fo rthe two children \  // then swap with pred 
    if (rmNode->getLeft() !=nullptr && rmNode->getRight()!= nullptr) { // if theres two exisitn children off that 
      // need a pointer for pred 
      Node<Key, Value>* pPred = predecessor(rmNode);  // pointer to pre
        // swap em but then rem
      nodeSwap(rmNode, pPred); // swap the two using the swap node there 
        
    }

    // need to track parent 
    Node<Key, Value>* p = rmNode->getParent(); // parent pointer here 
    // and chidl 
      Node<Key, Value>* c; // then if the l or r child are there set this to is 

        if(rmNode->getRight() != nullptr) {
          // set it for the right 
            c=rmNode->getRight(); 

        }
        else {
            // otherwise la 
            c= rmNode->getLeft(); 
        }

        //parent and chld check
        if (p==nullptr) { // if the parent is null 
          // the childup
          root_ =c;// the child is the root 

        }
        else if (rmNode ==p->getRight()) { // if its rc of p
          p->setRight(c); // chld taking place 
        }
          else {
          // othrsie its juts the lef
          p->setLeft(c); // 
          }

          // then just set parent and remo 
          if (c!=nullptr) {
            c->setParent(p); // set the new parent if its existing ofc 
          }
        delete rmNode; // actually delting the one we cwan remove

}



template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current)
{
    // TODO
    if (current ==nullptr) {
      return nullptr;  // its just null
    }

    //check the left paths to find the next smallest so on left but right most on ls 
      // lc must not be null eg exist 
    if(current->getLeft() !=nullptr) {
      Node<Key, Value>* cPoint = current->getLeft(); // pointer to the left of current 
        while(cPoint->getRight()!= nullptr) {
          // for the nodes right of the left here
          cPoint =cPoint->getRight(); 
            // move it right and then

        }
          return cPoint; // pred will be the biggest on the left branch
    }
    else {
      //same but will need one for parent check 
        // must be above the curr
      Node<Key, Value>* pPoint = current->getParent(); // parent of curr 
      while (pPoint!=nullptr) {
          // parent exists e
            if(current!= pPoint->getLeft()) { // parent is smaller
              break; 
                // found pred 
            }
              // go up agqin to parent of the parent
            current = pPoint; 
            pPoint=pPoint->getParent();
      }
      // ofc need to return the pred 
      return pPoint; 
    }

}

// copying over for successor implentation here 

template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::successor(Node<Key, Value>* current)
{
    // TODO
    if (current ==nullptr) {
      return nullptr;  // its just null
    }

    //check the - swap out to do the opposite right paths  
      // lc must not be null eg exist 
    if(current->getRight() !=nullptr) {
      Node<Key, Value>* cPoint = current->getRight(); // pointer to the right *update now of current 
        while(cPoint->getLeft()!= nullptr) {
          // swapped so now its nodes left of right h
          cPoint =cPoint->getLeft(); 
            // move it swapped for left

        }
          return cPoint; // succ not pred* will be the smallest on right swappe
            // swapped
    }
    else {
      //same but will need one for parent check 
        // must be above the curr
      Node<Key, Value>* pPoint = current->getParent(); // parent of curr 
      while (pPoint!=nullptr) {
          // parent exists e
            if(current!= pPoint->getRight()) { // parent is larger now swapped
              break; 
                // found succ
            }
              // go up agqin to parent of the parent
            current = pPoint; 
            pPoint=pPoint->getParent();
      }
      // return succ here 
      return pPoint; 
    }

}

/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    // TODO
      // delete nodes form the root and then the 
        // root is now null
    deleteNodes(root_); // call that should delete if theres ndoes going down left and right paths 
    root_ = nullptr; 
}

// defining my deleting nodes functin to call in clear 
template<typename Key, typename Value>
  //sig
void BinarySearchTree<Key, Value>::deleteNodes(Node<Key, Value>* dNode) {
  if(dNode==nullptr) {
    return; // its already empty so no deleting case
  }

  if (dNode->getLeft()!= nullptr) { // if theres a left child 
    deleteNodes(dNode->getLeft());  // delete the lc 
  }
  // same for right 
  if (dNode->getRight() != nullptr) {
    deleteNodes(dNode->getRight()); // if a right chld exists
      // delete the righ t
  }
  delete dNode; // actually deletes it and will get rescusivesly called
}
/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    // TODO
    // same pointer at root and go thru 
    Node<Key, Value>* rPoint = root_;
    if (rPoint==nullptr) {
      return nullptr; // if root is null
    }
      //go LEFt
    // go through left for smallest here left path reminder
      while (rPoint->getLeft()!=nullptr) { // while there a lc off the root ob isnt nul

          rPoint=rPoint->getLeft();
        
      }
      return rPoint; 


}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    // TODO
    // node pointer dec root
    Node<Key, Value>* rPoint = root_; //make root p set that to the roo
    
    while (rPoint!= nullptr) {
      //need to check eg compare with key so need
      // so
        if (rPoint->getKey() == key) {
          //if so t
          return rPoint;
        }
        else if (rPoint->getKey() <key){// iss larger
          //rc 
          rPoint= rPoint->getRight();

        }
        else{
          rPoint=rPoint->getLeft();
        }
    }
    return nullptr; // again ya if no item with that key 

}

/**
 * Return true iff the BST is balanced.
 */
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    // TODO
    // call the check for any tree starting rot 
    if (heightbalanced(root_) !=-1) {   // call
          // theres no breaks or places breaking the balancing ru
        return true; 
    }
    else {
      return false; // not balacned
    }
}

//function to track the heights to call here 
//template here 
template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::heightbalanced(Node<Key, Value>* hNode) const {

  if (hNode==nullptr) {
    return 0; // no hiehgt so its ba
  }

  //need to do the checks for the difference being 2 or more on the left and right side

  int leftSide = heightbalanced(hNode->getLeft());  // left hiehg
  //and the right ofc 
    int rightSide = heightbalanced(hNode->getRight());  // right heigh t

    if (leftSide- rightSide >=2) {
      return -1; // UNbanced its failing the property
    }

    // and same for the reserves 
    if(rightSide - leftSide >=2) {
      //not balanced if right side is 2 or more taller 
      return -1; 
    }
       if (leftSide ==-1) { // left side already breaks the cond
        return -1; 
       }

       if (rightSide ==-1) {  
        // same right breaks it 
        return -1; 
       }

  int bigger = std::max(leftSide, rightSide); // grab the taller path either right or left which bigger
       //longest path from starting to the bttom there 
    return 1+bigger; 



} 


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
 * Lastly, we are providing you with a print function,
   BinarySearchTree::printRoot().
   Just call it with a node to start printing at, e.g:
   this->printRoot(this->root_) // or any other node pointer

   It will print up to 5 levels of the tree rooted at the passed node,
   in ASCII graphics format.
   We hope it will make debugging easier!
  */

// include print function (in its own file because it's fairly long)
#include "print_bst.h"

/*
---------------------------------------------------
End implementations for the BinarySearchTree class.
---------------------------------------------------
*/

#endif
