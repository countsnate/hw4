#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void shiftLeft(AVLNode<Key ,Value>* left); // need to rebalance 
      // for left rotations 

    virtual void shiftRight(AVLNode<Key, Value>* right); // same for right 
      //both move pointers to satisfy the propery w


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    // TODO

    // rem new item replaces keyvalue pari 

  // using bst as template then need to *reminder add balance checks ofc 
    // bst had the override
  // code copied over form bst h 
    AVLNode<Key, Value>* rPoint = static_cast<AVLNode<Key, Value>*>(this->root_); //updated to avl based on above
      // need to make root an AVL node so i can call stuff 
    //intialize my nodes for access to update balcnes 
    AVLNode<Key, Value>* lNode=nullptr; 
    AVLNode<Key, Value>* pNode= nullptr; //sh be null
      // avl to call

    // if its null 
    if (rPoint ==nullptr) {
      //whole thing is empty 
      // must be this 
      this->root_= new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr); 
        // no p - update with new item not key v
        return; // stop here
    } 
    while (rPoint!=nullptr) {
        // go trhought eh tree to insert at the empty spot here 
          // while its vaklid 
        if (rPoint->getKey()==new_item.first) { // new item 
            //case where the keys are the same need to overrid
            // change the value
            rPoint->setValue(new_item.second);// just change the value set it
            return; // its done replace and nothing left
        }
        else if(rPoint->getKey() < new_item.first) {
          // put it right if its biggger than
          // need the empty right spot 
            if(rPoint->getRight()==nullptr) {
                // change avl swap and new item 
          
              pNode = new AVLNode<Key, Value>(new_item.first, new_item.second, rPoint); // make this one given its parent should be the pointer to root node so its rc
              rPoint->setRight(pNode); // put it on the rc
              break;   // breakand thats it
            }
            else {
              //cant put it so 
              rPoint = rPoint->getRight(); // just whatever is there 
            }
        }
        else {
          // same deal for the left side need empty then insert the new or getLef 
          if (rPoint->getLeft()== nullptr) {
              // update
            lNode = new AVLNode<Key, Value>(new_item.first, new_item.second, rPoint); //saame
            // creat that new and put in on the lc
              rPoint->setLeft(lNode);
              break; // break 
                //again insert here and thats it
          }
          else {
              // the lc is full 
              rPoint=rPoint->getLeft();// lef
          }
        }

    }

    // now check balances and call the roatiosn if needed 
      // implet here remind er
    AVLNode<Key, Value>* nBel = nullptr; // track the node to check above p
      AVLNode<Key, Value>* nAbv = nullptr;  // should be the rpoint
    if (pNode!= nullptr && lNode== nullptr) { // whichever node is valid should be the staring to gUP
      nBel= pNode; 
    }
    else {
      nBel = lNode; // possite should be lNode 
    }
    nAbv = rPoint; // above or the root here 

    // okay now while its existing from the root need to go thro
  
      while (nAbv!= nullptr) { // while its not null

        if (nAbv->getLeft() ==nBel) { // left side means balcne --
          nAbv->updateBalance(-1); // balance upd
        }
          // if its right then the balance should ++d 
          if (nAbv->getRight()== nBel) {
            nAbv->updateBalance(1); // balance inc
          }
        // need to check the balacne sa
        if (nAbv->getBalance()== 0) {
          // its goo d 
          return; 
        }
        else if (nAbv->getBalance() >= 2) {
          // rebalance need to add the checks 
            // checks here for right if its posit
            //pasting from left balance to swap *check correcly 
          // need the one for zig zig / zag if its not then need to double shift
            if (nBel->getBalance()!=1) {
              // one below eg gc 
              AVLNode<Key, Value>* gcBel = nBel->getLeft(); // grand child below that
                // swap left ab
              // check balance 
                int grandbalance= gcBel->getBalance(); // balance at the two down from nAb
                
                if (grandbalance ==0) {
                  // the others set 0 
                    nBel->setBalance(0); 
                    nAbv->setBalance(0); // 0 case
                }
                // 
                else if (grandbalance ==-1) { // gc balance case nefg
                  nBel->setBalance(1);  // postive below in case
                  nAbv->setBalance(0); 
                }
                else {
                  // grandbalcne here 1 - swapped the else ye 1
                  nBel->setBalance(0); 
                   nAbv->setBalance(-1); // above fic 
                    // sign swap 
                }
                // set grand balance need 2 rem
                gcBel->setBalance(0); // set
                // balacnes yes 
                // shifts in this case -2 out of balacne 
                shiftRight(nBel); // zig zag case here need to perform two 
                shiftLeft(nAbv);  //swap
                  // swapped left n right 
                  // second 
            }
            else {
              // one shift 
              // if its zig zig 
              shiftLeft(nAbv); //1 rot
                // swap left
              nBel->setBalance(0); // also
                nAbv->setBalance(0); 
            }
            return; 

        }
        else if (nAbv->getBalance() ==-2) {
          // left or neg 
          // need the one for zig zig / zag if its not then need to double shift
            if (nBel->getBalance()!=-1) {
              // one below eg gc 
              AVLNode<Key, Value>* gcBel = nBel->getRight(); // grand child below that 
              // check balance 
                int grandbalance= gcBel->getBalance(); // balance at the two down from nAb
                
                if (grandbalance ==0) {
                  // the others set 0 
                    nBel->setBalance(0); 
                    nAbv->setBalance(0); // 0 case
                }
                // 
                else if (grandbalance ==1) { // gc balance case nefg
                  nBel->setBalance(-1); 
                  nAbv->setBalance(0); 
                }
                else {
                  // grandbalcne here -1
                  nBel->setBalance(0); 
                  nAbv->setBalance(1); // above fic 
                }
                // set grand balance need 2 rem
                gcBel->setBalance(0); // set
                // balacnes yes 
                // shifts in this case -2 out of balacne 
                shiftLeft(nBel); // zig zag case here need to perform two 
                shiftRight(nAbv);  //swap
                  // second 
            }
            else {
              // one shift 
              // if its zig zig 
              shiftRight(nAbv); //1 rot
              nBel->setBalance(0); // also
                nAbv->setBalance(0); 
            }
            return; 
        }
       
        else if (nAbv->getBalance() ==-1 ||nAbv->getBalance() == 1) { // push the nodes up to check 
            nBel= nAbv; // below goes to the p
          nAbv = nAbv->getParent(); // push one up to p 
            

        }
      }
    
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO

}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}

// roations implement 
template<class Key, class Value>  // template
void AVLTree<Key, Value>::shiftLeft(AVLNode<Key ,Value>* left) { //my
  AVLNode<Key, Value>* gUp = left->getRight(); // rc of the target

  // and also note store the nodes below that as well
    AVLNode<Key, Value>* g2Up = gUp->getRight(); // rc ofrc of target 
    //and the other 
    AVLNode<Key, Value>* gOver = gUp->getLeft(); // left of thed

    // parent pointer asw
    AVLNode<Key, Value>* P = left->getParent(); // grab parent 
  // setting 
  gUp->setLeft(left); // left falls left need to 
    // swap the root so left falls left ofc 
    // need to be left c of the gup so first set to rotati left
    left->setRight(gOver); // the over one falls rc of left now 

    gUp->setRight(g2Up); // now this fallas as the new roots rc 

    // and what the new parents are P
    left->setParent(gUp); // checks 

    if (gOver!= nullptr ) { // if theres a node there for roation 
        gOver->setParent(left); // same w check 
    }

    if (g2Up!= nullptr ) { // if that node exists 
        // make sure its not null and then can make sure parents are aligned 
        g2Up->setParent(gUp); //same
    }
      // handle cases with the new onewe moved up 
        // could be just null parent 
      if (P!= nullptr ) {
        gUp->setParent(P); //
        // check the chld
        if (P->getLeft() !=left) {
          P->setRight(gUp); // if its not then 

        }
        else {
          P->setLeft(gUp);  // ps left should be gUp if it is tur
        }
      }
      else {
        gUp->setParent(nullptr); // if it is then it would point to null so parent nullp
        // and its just the ro 
        this->root_ = gUp; 
      }
   
    

}

// now the right rotations model strcuter 
// pasted left to swap 
// right implent 
template<class Key, class Value>  // template
void AVLTree<Key, Value>::shiftRight(AVLNode<Key ,Value>* right) { //updated forr 
  AVLNode<Key, Value>* gUp = right->getLeft(); // rc of the target

  // and also note store the nodes below that as well
    AVLNode<Key, Value>* g2Up = gUp->getLeft(); // updated lc of lc of target 
    //and the other 
    AVLNode<Key, Value>* gOver = gUp->getRight(); // update right of thed

    // parent pointer asw
    AVLNode<Key, Value>* P = right->getParent(); // grab parent 
      // right this time of
  // setting 
  gUp->setRight(right); //update swap direction s
    // swap the root so left falls left ofc 
    // need to be left c of the gup so first set to rotati left
    right->setLeft(gOver); // the over one falls rc of left now 

    gUp->setLeft(g2Up); // dont forget update this swap direcitons

    // and what the new parents are P
    right->setParent(gUp); // checks 

    if (gOver!= nullptr ) { // if theres a node there for roation 
        gOver->setParent(right); // same w check 
    }

    if (g2Up!= nullptr ) { // if that node exists 
        // make sure its not null and then can make sure parents are aligned 
        g2Up->setParent(gUp); //same
    }
      // handle cases with the new onewe moved up 
        // could be just null parent 
      if (P!= nullptr ) {
        gUp->setParent(P); //
        // check the chld
        if (P->getLeft() !=right) { // udpate
          P->setRight(gUp); // if its not then 

        }
        else {
          P->setLeft(gUp);  // ps left should be gUp if it is tur
        }
      }
      else {
        gUp->setParent(nullptr); // if it is then it would point to null so parent nullp
        // and its just the ro 
        this->root_ = gUp; 
      }
   
    

}


#endif
