//
// Created by Pasha on 28/12/2022.
//

#ifndef WET2_AVLTREE_H
#define WET2_AVLTREE_H


#include <iostream>
#include <memory>
#include "Exception.h"
#include "node.h"


template<class K,class V>
class AVLTree {
private:
    node<K, V> *root;
    int count;
    void BinarySearchTreeInsert(node<K,V>* toInsert,node<K,V>* next);
    bool fixBalanceFactorForInsert(node<K,V>* v);
    void fixBalanceFactorForRemove(node<K,V>* v);
    node<K,V>* findNode (node<K,V>* node ,const K& key )const;
    node<K,V>* removeNode (node<K,V>* node);
    int getBF(node<K,V> *v);
    void fixUpperTree(node<K,V>* innerTreeNewRoot,node<K,V>* innerTreeOldRoot);
    node<K,V>*  RR_Rotation(node<K,V>* b);
    node<K,V>*  RL_Rotation(node<K,V>* c);
    node<K,V>*  LR_Rotation(node<K,V>* c);
    node<K,V>*  LL_Rotation(node<K,V>* b);
    int numOfNodesInSubWoodOfRightSon(node<K, V>* node);
    int numOfNodesInSubWoodOfLeftSon(node<K, V>* node);
    void fixNodesInSubWood(node<K, V>* cur);
    node<K,V>* findByRankHelper(node<K, V>* cur , const int i) const;
    node<K,V>*  inOrderSuccessorSmaller(node<K,V>* nodeToSearthFor);
    node<K,V>*  inOrderSuccessorBigger(node<K,V>* nodeToSearthFor);
    void fixHeightForAllNodes(node<K,V>* cur);
    void fixExtraField(node<K,V>* cur);

public:
    ~AVLTree();
    AVLTree();
    //interface
    int getCount() const;
    void remove(const K& key);
    bool insert(const K& key,const V& val);
    bool isEmpty() const;
    bool isTreeValid();
    V& findValue(const K& key) const;
    V& findByRank(const int i) const;
    bool keyExists(const K& key) const;
    V& findMax();
    node<K,V>*  getRoot();
    void  DestroyRecursive(node<K,V>* root);
    void setRoot(node<K, V>*);

};

template<class K,class V>
void AVLTree<K,V> ::fixHeightForAllNodes(node<K, V> *cur) {

    while(cur)
    {
        fixHeight(cur);
        cur = cur->getParent();
    }
}



template<class K,class V>
node<K,V>* AVLTree<K,V> ::findByRankHelper(node<K, V> *cur, const int i) const {
    if(!cur)
    {return nullptr;}
    //if the node have left son and it was found
    if(cur->getLeftSon() && cur->getLeftSon()->getNumOfNodesInSubWood() == i -1)
    {
        return cur;
    }
    //if the node don't have left son and it was found
    else if(!cur->getLeftSon() && i == 1)
    {
        return cur;
    }
    //if the node is in the left subtree
    if (cur->getLeftSon() && cur->getLeftSon()->getNumOfNodesInSubWood() > i -1)
    {
        return findByRankHelper(cur->getLeftSon(),i);
    }
    // if the node is in the right subtree
    if(cur->getLeftSon() && cur->getLeftSon()->getNumOfNodesInSubWood() < i -1)
    {
        return findByRankHelper(cur->getRightSon() , i - cur->getLeftSon()->getNumOfNodesInSubWood()-1);
    }
    return nullptr;


}

template<class K,class V>
V& AVLTree<K,V> ::findByRank(const int i) const {
    node<K,V>* theNode = findByRankHelper(root,i);

    if (theNode == nullptr)
    {throw RankIsNotInRange();}
    return theNode->getValue();

}

template<class K,class V>
node<K,V>* AVLTree<K,V> ::getRoot(){
    return root;
}

template<class K,class V>
void AVLTree<K,V> ::setRoot(node<K, V> *node){
    root = node;
}

template<class K,class V>
void AVLTree<K,V> :: DestroyRecursive(node<K,V>* root)
{
    if (root)
    {
        DestroyRecursive(root->getLeftSon());
        DestroyRecursive(root->getRightSon());
        delete root;
    }
}

template<class K,class V>
AVLTree <K,V>::~AVLTree(){
    DestroyRecursive(root);
}

template<class K,class V>
AVLTree <K,V>:: AVLTree():root(nullptr),count(0){}

template<class K,class V>
int AVLTree <K,V>::getCount() const{
    return count;
}

template<class K,class V>
void AVLTree <K,V>:: fixBalanceFactorForRemove(node<K,V>* v)
{
    int firstHeight = v->getHeight();
    node<K,V>* son;
    while(v!= nullptr){
        fixHeight(v);
        //if need to do roll
        if(getBF(v) == 2 || getBF(v) == -2)
        {
            // if the left side is bigger
            if(getBF(v) == 2)
            {
                son = v->getLeftSon();
                // LL roll
                if(getBF(son) >= 0)
                {
                    v =  LL_Rotation(v);
                }
                    // LR ROLL
                else if(getBF(son) ==-1)
                {
                    v = LR_Rotation(v);
                }
            }
                // if the right side is bigger
            else
            {
                son = v->getRightSon();
                //RR ROLL
                if(getBF(son) <= 0)
                {
                    v = RR_Rotation(v);

                }
                    //RL ROLL
                else if(getBF(son) == 1)
                {
                    v = RL_Rotation(v);
                }
            }
            if(firstHeight == v->getHeight())
            {break;}
            else
            {
                v = v->getParent();
                continue;
            }
        }

        v = v->getParent();

    }

}

template<class K,class V>
bool AVLTree <K,V>:: insert(const K& key,const V& val){
    node<K,V>* toInsert = new  node<K,V>(key,val);
    count ++;
    BinarySearchTreeInsert(toInsert,root);
    fixNodesInSubWood(toInsert);
    return fixBalanceFactorForInsert(toInsert);
}

template<class K,class V>
void AVLTree <K,V>:: BinarySearchTreeInsert(node<K,V>* toInsert,node<K,V>* next) {
    node<K, V> *current = next;
    while (next != nullptr) {
        current = next;
        if (*toInsert < *next)
            next = next->getLeftSon();
        else
            next = next->getRightSon();
    }
    if (current == nullptr) { root = toInsert;}
    else if (*toInsert < *current) {current->setLeftSon(toInsert) ;}
    else {current->setRightSon(toInsert);}
}

template<class K,class V>
bool AVLTree <K,V>:: fixBalanceFactorForInsert(node<K,V>* v) {
    node<K,V>* p ;//1
    while(v!=root){
        p =v->getParent();
        if(p->getHeight()>=v->getHeight()+1){
            return true;
        }
        p->setHeight(v->getHeight()+1);

        if (getBF(p)==2 && getBF(v)==-1){
            //assert(v != p->getLeftSon());
            LR_Rotation(p);
            return true;
        }
        else if (getBF(p)==2 && getBF(v)>=0){
            //assert(v != p->getLeftSon());
            LL_Rotation(p);
            return true;
        }
        else if (getBF(p)==-2 && getBF(v) ==1){
            //assert(v != p->getLeftSon());
            RL_Rotation(p);
            return true;
        }
        else if (getBF(p)==-2 && getBF(v)<=0){
            //assert(v != p->getLeftSon());
            RR_Rotation(p);
            return true;
        }
        v=p;
    }
    return false;
}

template<class K,class V>
node<K, V> * AVLTree <K,V>:: findNode ( node<K, V>* node ,const K& key ) const{
    if(node == nullptr)
        return nullptr;
    if (key == node->getKey())
    {
        return node;
    }
    else {
        if (key > node->getKey()) {
            return findNode(node->getRightSon(), key);
        } else {
            return findNode(node->getLeftSon(), key);
        }
    }
}

template<class K,class V>
V& AVLTree <K,V>::findMax(){
    node<K,V>* current = root;
    while (current->getRightSon() != nullptr)
        current = current->getRightSon();
    return current->getValue();
}

template<class K,class V>
node<K,V> * removeLeaf ( node<K, V>* Node,node<K, V>*& root){
    if(Node->getParent())
    {
        node<K, V> * toreturn = Node->getParent();
        if(*toreturn < *Node)
        {
            toreturn->setRightSon(nullptr);
        } else{
            toreturn->setLeftSon(nullptr);
        }
        delete Node;
        return toreturn;
    }
    root = nullptr;
    delete Node;
    return nullptr;

}

template<class K,class V>
node<K,V> * AVLTree <K,V>:: removeNode ( node<K, V>* Node)
{
    //leaf
    if(!Node->getLeftSon() && !Node->getRightSon())
        return removeLeaf ( Node,root);
        //only right son
    else if(!Node->getLeftSon() && Node->getRightSon())
    {
        //if the node was root
        if(Node->getParent() == nullptr)
        {
            root = Node->getRightSon();
            Node->getRightSon()->setParent(nullptr);
            delete Node;
            return nullptr;
        }
        //if the node was in the right
        if(*(Node->getParent()) < *Node)
        {
            Node->getParent()->setRightSon(Node->getRightSon());
        }
            //if the node was in the left
        else
        {
            Node->getParent()->setLeftSon(Node->getRightSon());
        }
        node<K, V>* toreturn = Node->getRightSon();
        delete Node;
        return toreturn;
    }
        //only left son
    else if(Node->getLeftSon() && !Node->getRightSon())
    {

        //if the node was the root
        if(Node->getParent() == nullptr)
        {
            root = Node->getLeftSon();
            Node->getLeftSon()->setParent(nullptr);
            delete Node;
            return nullptr;
        }
        //if the node was in the right
        if(*(Node->getParent()) < *Node)
        {
            Node->getParent()->setRightSon(Node->getLeftSon());
        }
            //if the node was in the left
        else
        {
            Node->getParent()->setLeftSon(Node->getLeftSon());
        }
        node<K, V> * toreturn = Node->getLeftSon();
        delete Node;
        return toreturn;
    }
        //there is also a right and left son
    else
    {
        node<K,V> * nearNode = inOrderSuccessorBigger(Node);
        node<K,V> * parentOfNear = nearNode->getParent();
        if(nearNode->getRightSon() && parentOfNear != Node )
        {
            parentOfNear->setLeftSon(nearNode->getRightSon());
        }
        else if(parentOfNear != Node)
        {
            parentOfNear->setLeftSon(nullptr);
        }

        if(Node == parentOfNear)
        {
            nearNode->setLeftSon(Node->getLeftSon());

            nearNode->setParent(Node->getParent());


        }
        else
        {
            nearNode->setLeftSon(Node->getLeftSon());
            nearNode->setRightSon(Node->getRightSon());
            nearNode->setParent(Node->getParent());
        }

        if(Node->getParent())
        {
            if(Node->getParent()->getRightSon() == Node)
            {
                Node->getParent()->setRightSon(nearNode);
            }
            else
            {
                Node->getParent()->setLeftSon(nearNode);
            }
        }
        if(root == Node)
        {
            root = nearNode;
        }
        if(Node == parentOfNear)
        {
            delete Node;
            return nearNode;
        }
        delete Node;
        return parentOfNear;

    }


}

template<class K,class V>
node<K,V>* AVLTree <K,V>:: inOrderSuccessorSmaller(node<K,V>* nodeToSearthFor)  {
    node<K,V>* current = nodeToSearthFor;
    if(current->getLeftSon() != nullptr)
    {
        return maxValueNode(current->getLeftSon());
    }
    node<K,V>* parent = current->getParent();
    while(parent != nullptr && (parent->getLeftSon()) == current)
    {
        current = parent;
        parent = parent->getParent();
    }
    return parent;
}

template<class K,class V>
node<K,V>* AVLTree <K,V>:: inOrderSuccessorBigger(node<K,V>* nodeToSearthFor)
{
    node<K,V>* current = nodeToSearthFor;
    if(current->getRightSon() != nullptr)
    {
        return minValue(current->getRightSon());
    }
    node<K,V>* parent = current->getParent();
    while(parent != nullptr && (parent->getRightSon()) == current)
    {
        current = parent;
        parent = parent->getParent();
    }
    return parent;
}

template<class K,class V>
node<K,V>*  minValue (node<K,V>* nodeToSearchFor)
{
    node<K,V>* current = nodeToSearchFor;
    while(current->getLeftSon() != nullptr)
    {
        current = current->getLeftSon();
    }
    return current;
}

template<class K,class V>
void AVLTree <K,V>:: remove(const K& key){
    node<K, V> * toremove = findNode(root,key);
    if(toremove == nullptr)
    {
        throw keyDoesntExist();
    }
    count--;
    node<K, V> * tofix =  removeNode(toremove);
    if(tofix == nullptr)
        return;
    else{
        fixBalanceFactorForRemove(tofix);
        fixHeightForAllNodes(tofix);
        fixExtraField(tofix);
        fixNodesInSubWood(tofix);

    }

}

template<class K,class V>
int AVLTree <K,V>::getBF(node<K,V> *v){
    if(v->getLeftSon() && v->getRightSon()){
        return v->getLeftSon()->getHeight() - v->getRightSon()->getHeight();
    }
    else if(v->getLeftSon() && v->getRightSon() == nullptr){
        return v->getLeftSon()->getHeight() - NULL_NODE_HEIGHT;
    }
    else if(v->getLeftSon()== nullptr && v->getRightSon() ){
        return NULL_NODE_HEIGHT - v->getRightSon()->getHeight();
    }
    else
        return 0;
}

template<class K,class V>
void AVLTree <K,V>:: fixUpperTree(node<K,V>* innerTreeNewRoot,node<K,V>* innerTreeOldRoot){
    if(root == innerTreeOldRoot){
        root =innerTreeNewRoot;
        innerTreeNewRoot->setParent(nullptr);
    }
    else{
        if(innerTreeOldRoot==innerTreeOldRoot->getParent()->getLeftSon())
            innerTreeOldRoot->getParent()->setLeftSon(innerTreeNewRoot);
        else
            innerTreeOldRoot->getParent()->setRightSon(innerTreeNewRoot);

    }

}

template<class K,class V>
node<K,V>* AVLTree <K,V>:: RR_Rotation(node<K,V>* b){
    int numOfSubWoodOfB = b->getNumOfNodesInSubWood();
    int numOfSubWoodOfLeftSonOfB = numOfNodesInSubWoodOfLeftSon(b);
    node<K,V>* a = b->getRightSon();
    int numOfSubWoodOfLeftSonOfA = numOfNodesInSubWoodOfLeftSon(a);
    fixUpperTree(a,b);
    b->setRightSon(a->getLeftSon());
    a->setLeftSon(b);
    fixHeight(b);
    fixHeight(a);
    b->setNumOfNodesInSubWood(numOfSubWoodOfLeftSonOfA+numOfSubWoodOfLeftSonOfB+1);
    a->setNumOfNodesInSubWood(numOfSubWoodOfB);
    return a;
}

template<class K,class V>
node<K,V>* AVLTree <K,V>:: LL_Rotation(node<K,V>* b){ //right rotation b is the rollroot
    int numOfSubWoodOfB = b->getNumOfNodesInSubWood();
    int numOfSubWoodOfRightSonOfB = numOfNodesInSubWoodOfRightSon(b);
    node<K,V>* a = b->getLeftSon();
    int numOfSubWoodOfRightSonOfA = numOfNodesInSubWoodOfRightSon(a);
    fixUpperTree(a,b);
    b->setLeftSon(a->getRightSon());
    a->setRightSon(b);
    fixHeight(b);
    fixHeight(a);
    b->setNumOfNodesInSubWood(numOfSubWoodOfRightSonOfA+numOfSubWoodOfRightSonOfB+1);
    a->setNumOfNodesInSubWood(numOfSubWoodOfB);
    return a;

}

template<class K,class V>
node<K,V>* AVLTree <K,V>:: RL_Rotation(node<K,V>* c){
    node<K,V>* b = c->getRightSon();
    node<K,V>* a = b->getLeftSon();
    LL_Rotation(b);
    //c->setRightSon(a);
    RR_Rotation(c);
    return a;
}

template<class K,class V>
node<K,V>* AVLTree <K,V>:: LR_Rotation(node<K,V>* c){ // c is the rollroot
    node<K,V>* b = c->getLeftSon();
    node<K,V>* a = b->getRightSon();
    RR_Rotation(b);
    //c->setLeftSon(a);
    LL_Rotation(c);
    return a;
}

template<class K, class V>
bool AVLTree <K,V>::isEmpty() const{
    return root == nullptr;
}

template<class K,class V>
V& AVLTree<K,V>::findValue(const K& key) const
{
    node<K,V>* toReturn = findNode(root ,key);
    if(toReturn == nullptr)
    {
        throw keyDoesntExist();
    }
    return toReturn->getValue();
}

template<class K,class V>
bool AVLTree<K,V>::keyExists(const K& key) const
{
    node<K,V>* toFind = findNode(root ,key);
    return toFind != nullptr;

}

template<class K,class V>
static void fixHeight(node<K,V>* toFix){
    int left = NULL_NODE_HEIGHT;
    int right = NULL_NODE_HEIGHT;

    if(toFix->getRightSon())
        right = toFix->getRightSon()->getHeight();
    if(toFix->getLeftSon())
        left = toFix->getLeftSon()->getHeight();
    toFix->setHeight(std::max(right+1,left+1));


}

template<class K,class V>
static node<K, V> *  findNode ( node<K, V>* node ,const K& key ) {
    if(node == nullptr)
        return nullptr;
    if (key == node->getKey())
    {
        return node;
    }
    else {
        if (key > node->getKey()) {
            return findNode(node->getRightSon(), key);
        } else {
            return findNode(node->getLeftSon(), key);
        }
    }
}

template<class K,class V>
int AVLTree<K,V>:: numOfNodesInSubWoodOfRightSon(node<K, V>* node)
{
    if(node->getRightSon())
    {
        return node->getRightSon()->getNumOfNodesInSubWood();
    }
    else
    {
        return 0;
    }
}

template<class K,class V>
int AVLTree<K,V>:: numOfNodesInSubWoodOfLeftSon(node<K, V>* node)
{
    if(node->getLeftSon())
    {
        return node->getLeftSon()->getNumOfNodesInSubWood();
    }
    else
    {
        return 0;
    }
}

template<class K,class V>
void AVLTree<K,V>:: fixNodesInSubWood(node<K, V>* cur)
{
    node<K,V>* prev = cur->getParent();
    while(prev)
    {
        prev->setNumOfNodesInSubWood(numOfNodesInSubWoodOfLeftSon(prev)+ numOfNodesInSubWoodOfRightSon(prev)+1);
        prev = prev->getParent();
    }


}

template<class K,class V>
void AVLTree<K ,V>::fixExtraField(node<K, V> *cur) {
    if(!cur->getLeftSon() && !cur->getRightSon())
    {
        cur->setNumOfNodesInSubWood(1);
    }
    else if (!cur->getLeftSon())
    {
        cur->setNumOfNodesInSubWood(cur->getRightSon()->getNumOfNodesInSubWood()+1);
    }
    else if(!cur->getRightSon())
    {
        cur->setNumOfNodesInSubWood(cur->getLeftSon()->getNumOfNodesInSubWood()+1);
    }
    else
    {
        cur->setNumOfNodesInSubWood(cur->getLeftSon()->getNumOfNodesInSubWood()+cur->getRightSon()->getNumOfNodesInSubWood()+1);
    }
}




#endif //WET2_AVLTREE_H
