#include <iostream>
#include <utility>
#include <algorithm>
using std::pair;
using namespace std;
template<class T1,class T2>
struct Node
{
    Node *left;
    Node *right;
    pair<T1,T2> data;
    Node(pair<T1,T2> data,Node *left,Node *right)
    {
        this->data=data;
        this->left=left;
        this->right=right;
    }
};
template<class T1,class T2>
class Set
{
private:
    Node<T1,T2> *root;
    int size;
public:
    Set();
    Set(Set<T1,T2> &temp);
    ~Set();
    void add_node(pair<T1,T2> &number)
    {
        _add_node(number,root);
    }
    void preorder_print()
    {
        _preorder_print(root);
    }
    void order_print()
    {
        _order_print(root);
    }
    void delete_element(T1 key)
    {
        _delete_element(key,root);
    }
    int Size()
    {
        return size;
    }
    bool empty()
    {
        if(size==0){
            return true;
        }
        return false;
    }
/*    void find_previous(T1 key)
    {
        _find_previous( key,root);
    }
    void find_next(T1 &key)
    {
        _find_next( key,root);
    }
     find_maximum()
    {
        _find_maximum(root);
    }
    void find_minimum()
    {
        _find_maximum(root);
    }
 */
    void clear()
    {
        _clear(root);
        root=nullptr;
    }
    T2& operator[](T1 key)
    {
        Node <T1,T2>* temp=_find_current(root,key);
        return temp->data.second;
    }
    class Iterator;
    Iterator begin()
    {
        return Iterator(_find_minimum(root),this);
    }
    Iterator end()
    {
        return Iterator(_find_maximum(root) + 1,this);
    }
 
private:
    Iterator _begin(Node<T1,T2> *leaf);
    Node<T1,T2>* _add_node(pair<T1,T2> &number,Node<T1,T2> *leaf);
    void _preorder_print(Node<T1,T2> *leaf);
    void _order_print(Node<T1,T2> *leaf);
    void _clear(Node<T1,T2>* leaf);
    Node<T1,T2>* _find_previous(T1 &key,Node <T1,T2>*leaf);
    Node<T1,T2>* _find_next(T1 &key,Node <T1,T2>*leaf);
    Node<T1,T2>* _delete_element(T1 &key,Node <T1,T2>*leaf);
    Node<T1,T2>* _find_current(Node <T1,T2>* leaf,T1 &key);
    Node <T1,T2>* _find_maximum(Node <T1,T2>*leaf);
    Node <T1,T2>* _find_minimum(Node <T1,T2>*leaf);
    void CopyTree(Node<T1, T2>* temp)
        {
            if (!temp)
                return;
            add_node(temp->data);
            CopyTree(temp->left);
            CopyTree(temp->right);
        }
};
template<class T1,class T2>
Set<T1,T2>::Set()
{
    root=nullptr;
    size=0;
}
template<class T1,class T2>
Set<T1,T2>::Set(Set<T1,T2> &temp)
{
	root = 0;
    size = 0;
    CopyTree(temp.root);
 
}
template<class T1,class T2>
Set<T1,T2>::~Set()
{
    _clear(root);
    root=nullptr;
}
template<class T1,class T2>
void Set<T1,T2>::_clear(Node<T1,T2>* leaf)
{
    if(leaf!=nullptr){
        _clear(leaf->left);
        _clear(leaf->right);
        delete leaf;
    }
}
template<class T1,class T2>
Node<T1,T2>* Set<T1,T2>::_add_node(pair<T1,T2> &number,Node<T1,T2> *leaf)
{
    if(leaf==nullptr){
        leaf=new Node<T1,T2>(number,0,0);
        if(root==nullptr)root=leaf;
        size++;
    }
    if(leaf->data.first>number.first){
        leaf->left=_add_node(number,leaf->left);
    }
    if(leaf->data.first<number.first){
        leaf->right=_add_node(number,leaf->right);
    }
    return leaf;
}
template<class T1,class T2>
void Set<T1,T2>::_preorder_print(Node<T1,T2> *leaf)
{
    if(leaf!=nullptr){
        _preorder_print(leaf->left);
        cout<<leaf->data.second;
        _preorder_print(leaf->right);
    }
}
template<class T1,class T2>
void Set<T1,T2>::_order_print(Node<T1,T2> *leaf)
{
    if(leaf!=nullptr){
        _order_print(leaf->right);
        cout<<leaf->data.second;
        _order_print(leaf->left);
    }
}
template<class T1,class T2>
Node<T1,T2>* Set<T1,T2>::_find_current(Node<T1,T2>* leaf,T1 &key)
{
    while(1){
        if(leaf->data.first>key){
            leaf=leaf->left;
        }else if(leaf->data.first<key){
 
            leaf=leaf->right;
        }else if(leaf->data.first==key){
            return leaf;
        }
    }
}
template<class T1,class T2>
Node<T1,T2>* Set<T1,T2>::_delete_element(T1 &key,Node<T1,T2> *leaf)
{
    if(leaf==nullptr){
        return leaf;
    }
    if(leaf->data.first>key){
        leaf->left=_delete_element(key, leaf->left);
    }else if(leaf->data.first<key){
        leaf->right=_delete_element(key, leaf->right);
    }else{
        if(leaf->left==nullptr && leaf->right==nullptr){
            delete leaf;
            leaf=nullptr;
            return leaf;
        }
        if(leaf->left!=nullptr && leaf->right!=nullptr){
            Node<T1,T2>* temp=_find_maximum(leaf->left);
            leaf->data=temp->data;
            leaf->left=_delete_element(temp->data.first, leaf->left);
 
        }else{
            Node<T1,T2>* temp;
            if(leaf->right!=nullptr){
                temp=leaf->right;
            }else{
                temp=leaf->left;
            }
            delete leaf;
            leaf=nullptr;
            return temp;
        }
    }
    size--;
    return leaf;
}
template<class T1,class T2>
Node<T1,T2>* Set<T1,T2>::_find_previous(T1 &key,Node<T1,T2> *leaf)
{
    Node<T1,T2>* prec=nullptr;
    while(1){
        if(leaf->data.first>key){
            leaf=leaf->left;
        }
        if(leaf->data.first<key){
            prec=leaf;
            leaf=leaf->right;
        }
        if(leaf->data.first==key){
            if(leaf->left){
                prec=_find_maximum(leaf->left);
            }
            return prec;
            break;
        }
    }
}
template<class T1,class T2>
Node<T1,T2>* Set<T1,T2>::_find_next(T1 &key,Node<T1,T2> *leaf)
{
    Node<T1,T2> *prec=nullptr;
    while(1)
    {
        if(leaf->data.first>key){
            prec=leaf;
            leaf=leaf->left;
        }
        if(leaf->data.first<key){
            leaf=leaf->right;
        }
        if(leaf->data.first==key){
            if(leaf->left){
                prec=_find_minimum(leaf->right);
            }
            return prec;
            break;
        }
    }
}
template<class T1,class T2>
 Node<T1,T2>* Set<T1,T2>::_find_maximum(Node<T1,T2> *leaf)
{
    if (leaf)
    while(leaf->right!=NULL){
       leaf= leaf->right;
    }
    return leaf;
}
template<class T1,class T2>
 Node<T1,T2>* Set<T1,T2>::_find_minimum(Node<T1,T2> *leaf)
{
    if (leaf)
    while(leaf->left){
       leaf= leaf->left;
    }
    return leaf;
}
 
template<class T1,class T2>
class Set<T1,T2>::Iterator
{
private:
    Node<T1,T2>*it;
    Set<T1,T2>*myset;
 
public:
    Iterator(Node<T1,T2>* temp,Set<T1,T2> *MYSET): it(temp), myset(MYSET) {};
    Iterator& operator ++()
    {
        if (it == myset->_find_maximum(myset->root))
            ++it;
        else
        it=myset->_find_next(it->data.first,myset->root);
 
        return *this;
    }
    Iterator& operator ++(int)
    {
        if (it == myset->_find_maximum(myset->root))
            ++it;
        else
        it=myset->_find_next(it->data.first,myset->root);
 
        return *this;
    }
    Iterator& operator --()
    {
        if (it == myset->_find_maximum(myset->root) + 1)
            --it;
        else
        it =myset->_find_previous(it->data.first,myset->root);
 
        return *this;
    }
    Iterator& operator --(int)
    {
        if (it == myset->_find_maximum(myset->root) + 1)
            --it;
        else
        it =myset->_find_previous(it->data.first,myset->root);
 
        return *this;
    }
    T1& operator*()
    {
        return it->data.first;
    }
    bool operator!=(Iterator &temp){
        return it!=temp.it;
    }
    bool operator==(Iterator &temp){
        return it ==temp.it;
    }
    bool operator>=(Iterator &temp){
        return it>=temp.it;
    }
    bool operator<=(Iterator &temp){
        return it<=temp.it;
    }
};
int main(int argc, const char * argv[]) {
    pair<int,string>ab(100,"564");
    pair<int,string>ab2(75,"5465");
    //pair<int,string>ad(110,"valya");
    //pair<int,string>acn(65,"andrey");
    //pair<int,string>abg(80,"alena");
   // pair<int,string>ab2h(90,"gena");
   // pair<int,string>add(50,"valya");
    Set<int,string> a;
    a.add_node(ab);
    a.add_node(ab2);
    Set<int,string> b(a);
    b.preorder_print();
   // a.add_node(acn);
    //a.add_node(abg);
   // a.add_node(ab2h);
   // a.add_node(add);
 
   // a.delete_element(25);
    //a.preorder_print();
    //a.find_previous(100);
  //  auto it=  a.begin();
 
 
    //--it;
   // cout<<*it;
   // auto it=a.begin();
 
    //a.delete_element(25);
  //  a.delete_element(13);
    //a.delete_element(25);
   // a.delete_element(15);
 system("pause");
 
    return 0;
}
 