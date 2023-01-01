
#ifndef WET1_NODE_H
#define WET1_NODE_H

static const int NULL_NODE_HEIGHT = -1;


template<class K,class V>
class node {
private:
    int numOfNodesInSubWood;
    int height;
    node *left;
    node *right;
    node *dady;
    K key;
    V value;

public:
    node(const K& key,const V& value);
    ~node()=default;
    int getHeight();
    void setHeight(int newHeight);
    const V& getValue() const;
    const K& getKey() const;
    V& getValue() ;
    int getNumOfNodesInSubWood();
    void setNumOfNodesInSubWood(int num);
    node* getLeftSon();
    node* getRightSon();
    void setRightSon(node* newRight);
    void setLeftSon(node* newLeft);
    node*  getParent();
    void setParent(node* newDady);
    void setValue(const V& val);
    bool  operator<(const node& other)const;
    bool  operator==(const node& other)const;

};


template<class K,class V>
node < K, V> ::  node(const K& key,const V& value):height(0),numOfNodesInSubWood(1),left(nullptr),right(nullptr),dady(nullptr),key(key),value(value)
{

}

template<class K,class V>
void node < K, V> ::setValue(const V &val) {value = val;}

template<class K,class V>
int node < K, V> :: getHeight(){
    return height;
}

template<class K,class V>
void node < K, V> :: setHeight(int newHeight){
    height=newHeight;
}
template<class K,class V>
const V& node < K, V> :: getValue() const{
    return value;
}

template<class K,class V>
V& node < K, V> :: getValue() {
    return value;
}

template<class K,class V>
const K& node <K,V> :: getKey() const{
    return key;
}

template<class K,class V>
node<K,V>* node <K,V> ::getLeftSon(){
    return left;
}

template<class K,class V>
node<K,V>* node <K,V> :: getRightSon(){
    return right;
}

template<class K,class V>
void node <K,V> :: setLeftSon(node* newLeft){
    left=newLeft;
    if(newLeft)
        newLeft->dady = this;
}

template<class K,class V>
void node <K,V> :: setRightSon(node* newRight){
    right=newRight;
    if(newRight)
        newRight->dady = this;
}

template<class K,class V>
node<K,V>* node <K,V>:: getParent(){
    return dady;
}

template<class K,class V>
void node <K,V>:: setParent(node* newDady){
    dady = newDady;
}

template<class K,class V>
void node <K,V>::setNumOfNodesInSubWood(int num) {
    numOfNodesInSubWood = num;
}

template<class K,class V>
int node <K,V>::getNumOfNodesInSubWood() {
   return numOfNodesInSubWood;
}

template<class K,class V>
bool node <K,V>:: operator<(const node& other)const{
    if (key < other.key)
        return true;
    else
        return false;
}

template<class K,class V>
bool node <K,V>:: operator==(const node& other)const{
    return (key == other.key);
}


#endif //WET1_NODE_H
