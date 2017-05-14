#include "stdafx.h"
#include "BinaryTree.h"

void test_1()
{
    char prelist[] = { 'A', 'B', 'D', NULL, 'G', NULL, NULL, NULL, 'C', 'E', NULL, NULL, 'F', 'H' };
    BinaryTree<char> bitree(prelist, 14);
    cout << bitree;
    bitree.inOrder();
    bitree.postOrder();
    bitree.insert(bitree.root->left, 'X', true);
    bitree.insert(bitree.root->right, 'Y', false);
    bitree.insert('Z');
    cout << bitree;
}

void test_2()
{
    char prelist[] = { 'A', 'B', 'D', NULL, 'G', NULL, NULL, NULL, 'C', 'E', NULL, NULL, 'F', 'H' };
    BinaryTree<char> bitree(prelist, 14);
    cout << bitree;
}

void test_3()
{
    BinaryTree<MyString> bitree("A(B(D(^,G),^),C(E,F(H,^)))");
    cout << bitree;
}

void test_4()
{
    char prelist[] = { 'A', 'B', 'D', 'G', 'C', 'E', 'F', 'H' };
    char inlist[] = { 'D', 'G', 'B', 'A', 'E', 'C', 'H', 'F' };
    BinaryTree<char> bitree(prelist, inlist, 8);
    cout << bitree;
}

void test_5()
{
    char prelist[] = { 'A', 'B', 'D', 'G', 'C', 'E', 'F', 'H' };
    char inlist[] = { 'D', 'G', 'B', 'A', 'E', 'C', 'H', 'F' };
    BinaryTree<char> bitree(prelist, inlist, 8);
    BinaryNode<char>* p = bitree.search('D');
    if (p) cout << p->data << endl;
    else cout << "can not find it!" << endl;
    BinaryNode<char>* q = bitree.parent(p);
    if (q) cout << q->data << endl;
    else cout << "can not find its parent!" << endl;
}

int main()
{
    test_1();
    test_2();
    test_3();
    test_4();
    test_5();
    return 0;
}
