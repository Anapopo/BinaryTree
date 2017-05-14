template <class T>
class BinaryNode
{
public:
    T data;
    BinaryNode<T> *left, *right;

    BinaryNode(T data, BinaryNode<T> *left = nullptr, BinaryNode<T> *right = nullptr)
    {
        this->data = data;
        this->left = left;
        this->right = right;
    }
};
