#include "BinaryNode.h"
#include "MyString.h"
using namespace std;

template <class T>
class BinaryTree
{
public:
    BinaryNode<T> *root;

    BinaryTree();
    BinaryTree(T prelist[], int n);
    BinaryTree(T prelist[], T inlist[], int n);
    BinaryTree(MyString genlist);
    ~BinaryTree();

    bool empty();
    void remove();
    BinaryNode<T>* search(T value);
    BinaryNode<T>* parent(BinaryNode<T> *node);

    void preOrder(bool showEmptyTree = false);
    void inOrder();
    void postOrder();
    friend ostream& operator<<<>(ostream& out, BinaryTree<T>&);

    BinaryNode<T>* insert(T x);
    BinaryNode<T>* insert(BinaryNode<T> *p, T x, bool leftChild = true);
    void remove(BinaryNode<T> *parent, bool leftChild);
    void printGenList();
    void printGenList(BinaryNode<T> *p);

private:
    void preOrder(BinaryNode<T> *p, bool showEmptyTree = false);
    void inOrder(BinaryNode<T> *p);
    void postOrder(BinaryNode<T> *p);
    void remove(BinaryNode<T> *p);
    BinaryNode<T>* create(T prelist[], int n, int &i);
    BinaryNode<T>* create(T prelist[], T inlist[], int n);
    BinaryNode<T>* create(MyString &genlist, int &i);
    BinaryNode<T>* preSearch(BinaryNode<T>* p, T value);
    BinaryNode<T>* preParent(BinaryNode<T>* start, BinaryNode<T>* node);
};

template <class T>
BinaryTree<T>::BinaryTree(MyString genlist)
{
    int i = 0;
    this->root = this->create(genlist, i);
}

template <class T>
BinaryNode<T>* BinaryTree<T>::create(MyString &genlist, int &i)
{
    if (genlist[i] == '^')
    {
        i++;
        return NULL;
    }
    int n = 0;
    char ch;
    while (i < genlist.count() && (ch = genlist[i + n]) && ch != '(' && ch != ',' && ch != ')')
        n++;
    MyString str = genlist.substring(i, n);
    i += n;
    BinaryNode<T> *p = new BinaryNode<T>(str);
    if (genlist[i] == '(')
    {
        i++;
        p->left = create(genlist, i);
        i++;
        p->right = create(genlist, i);
        i++;
    }
    return p;
}

template <class T>
BinaryTree<T>::BinaryTree(){ this->root = nullptr; }

template <class T>
BinaryTree<T>::BinaryTree(T prelist[], int n)
{
    int i = 0;
    this->root = this->create(prelist, n, i);
}

template <class T>
BinaryNode<T>* BinaryTree<T>::create(T prelist[], int n, int &i)
{
    BinaryNode<T> *p = nullptr;
    if (i < n)
    {
        T elem = prelist[i];
        i++;
        if (elem)
        {
            p = new BinaryNode<T>(elem);
            p->left = create(prelist, n, i);
            p->right = create(prelist, n, i);
        }
    }
    return p;

}

template <class T>
bool BinaryTree<T>::empty() { return (this->root == nullptr); }

template <class T>
ostream& operator<<<>(ostream& out, BinaryTree<T> &btree)
{
    out << "PreOrder: ";
    btree.preOrder(btree.root, true);
    out << endl;
    return out;
}

template <class T>
void BinaryTree<T>::preOrder(bool showEmptyTree)
{
    cout << "PreOrder: ";
    this->preOrder(root, showEmptyTree);
    cout << endl;
}

template <class T>
void BinaryTree<T>::preOrder(BinaryNode<T> *p, bool showEmptyTree)
{
    if (!p && showEmptyTree)
        cout << "^ ";
    else
    {
        cout << p->data << " ";
        this->preOrder(p->left, showEmptyTree);
        this->preOrder(p->right, showEmptyTree);
    }
}

template <class T>
void BinaryTree<T>::inOrder()
{
    cout << "InOrder: ";
    this->inOrder(root);
    cout << endl;
}

template <class T>
void BinaryTree<T>::inOrder(BinaryNode<T> *p)
{   
    if (p)
    {
        this->inOrder(p->left);
        cout << p->data << " ";
        this->inOrder(p->right);
    }
}

template <class T>
void BinaryTree<T>::postOrder()
{
    cout << "PostOrder: ";
    this->postOrder(root);
    cout << endl;
}

template <class T>
void BinaryTree<T>::postOrder(BinaryNode<T> *p)
{
    if (p)
    {
        this->postOrder(p->left);
        this->postOrder(p->right);
        cout << p->data << " ";
    }
}

template <class T>
BinaryNode<T>* BinaryTree<T>::insert(T x){ return this->root = new BinaryNode<T>(x, this->root, nullptr); }

template <class T>
BinaryNode<T>* BinaryTree<T>::insert(BinaryNode<T> *parent, T x, bool leftChild)
{
    if (!parent) return nullptr;
    if (leftChild) return parent->left = new BinaryNode<T>(x, parent->left, nullptr);
    return parent->right = new BinaryNode<T>(x, nullptr, parent->right);
}

template <class T>
void BinaryTree<T>::remove(BinaryNode<T> *parent, bool leftChild)
{
    if (!parent)
    {
        if (leftChild)
        {
            remove(parent->left);
            parent->left = nullptr;
        }
        else
        {
            remove(parent->right);
            parent->right = nullptr;
        }
    }
}

template <class T>
void BinaryTree<T>::remove(BinaryNode<T> *p)
{
    if (p)
    {
        remove(p->left);
        remove(p->right);
        delete p;
    }
}

template <class T>
BinaryTree<T>::~BinaryTree(){ this->remove(this->root); }

template <class T>
void BinaryTree<T>::remove() { this->remove(this->root); }

template <class T>
void BinaryTree<T>::printGenList()
{
    this->printGenList(root);
    cout << endl;
}

template <class T>
void BinaryTree<T>::printGenList(BinaryNode<T> *p)
{
    if (!p)
    {
        cout << "^";
    }
    else
    {
        cout << p->data;
        if (p->left || p->right)
        {
            cout << "(";
            printGenList(p->left);
            cout << ",";
            printGenList(p->right);
            cout << ")";
        }
    }
}

template <class T>
BinaryTree<T>::BinaryTree(T prelist[], T inlist[], int n)
{   
    this->root = create(prelist, inlist, n);
}

template <class T>
BinaryNode<T>* BinaryTree<T>::create(T prelist[], T inlist[], int n)
{   
    if (!n) return nullptr;
    int i;
    for (i = 0; i < n; i++) if (inlist[i] == prelist[0]) break;
    BinaryNode<T> *p = new BinaryNode<T>(prelist[0]);
    p->left = create(prelist+1, inlist, i);
    p->right = create(prelist+i+1, inlist+i+1, n-i-1);
    return p;
}

template <class T>
BinaryNode<T>* BinaryTree<T>::search(T key) { return this->preSearch(root, key); }

template <class T>
BinaryNode<T>* BinaryTree<T>::preSearch(BinaryNode<T>* p, T value)
{  
    static BinaryNode<T> *find = nullptr;
    if (!p) return nullptr;
    if (p->data == value) find = p;
    if (!find) preSearch(p->left, value);
    if (!find) preSearch(p->right, value);
    return find;
}

template <class T>
BinaryNode<T>* BinaryTree<T>::parent(BinaryNode<T> *node) { return preParent(root, node); }

template <class T>
BinaryNode<T>* BinaryTree<T>::preParent(BinaryNode<T> *start, BinaryNode<T> *node)
{
    static BinaryNode<T>* parent = nullptr; 
    if (!start) return nullptr;
    if (start->left && node->data == start->left->data || 
        start->right && node->data == start->right->data) 
        parent = start;
    if (!parent) preParent(start->left, node);
    if (!parent) preParent(start->right, node);
    return parent;
}
