#include <iostream>
using namespace std;
class MyString
{
private:
    char *element;
    int length;
    int n;
    void init(char *s = "", int length = 32);

public:
    MyString(char *s = "", int length = 32);
    MyString(char ch);
    MyString(MyString &str);
    MyString& operator=(MyString &str);
    MyString& operator=(char *str);
    ~MyString();
    bool empty();
    int count();
    char& operator[](int i);
    friend ostream& operator<<(ostream& out, MyString &str);
    void printPrevious();
    void reverse();
    int search(MyString &pattern, int start = 0);
    bool isTwisted();
    MyString substring(int i, int n);
};

void MyString::init(char *s, int length)
{
    this->n = strlen(s);
    this->length = (n * 2) > length ? (n * 2) : length;
    this->element = new char[this->length];
    for (int i = 0; s[i] != '\0'; i++) this->element[i] = s[i];
    this->element[this->n] = '\0';
}

MyString::MyString(char *s, int length) { this->init(s, length); }

MyString::MyString(char ch)
{
    this->init("");
    this->n = 1;
    this->element[0] = ch;
    this->element[1] = '\0';
}

bool MyString::empty() { return (this->element[0] == '\0') ? true : false; }

int MyString::count()
{
    int i = 0;
    while (this->element[i] != '\0') i++;
    return i;
}

MyString::MyString(MyString &str){ this->init(str.element); }

MyString& MyString::operator=(MyString &str)
{
    this->~MyString();
    this->init(str.element);
    return *this;
}

char& MyString::operator[](int i)
{   
    if (i < 0) i = 0;
    if (i >= this->n) i = (this->n - 1);
    return this->element[i];
}

ostream& operator<<(ostream& out, MyString& str)
{
    out << str.element;
    return out;
}

MyString& MyString::operator=(char *str)
{
    this->~MyString();
    this->init(str);
    return *this;
}

MyString::~MyString(){ delete this->element; }

void MyString::printPrevious()
{   
    for (int i = (n - 1); i >= 0; i--)
        cout << element[i];
    cout << endl;
}

void MyString::reverse()
{
    for (int i = 0; i < this->n / 2; i++)
    {   
        int end = this->n - i - 1;
        char temp = element[end];
        element[end] = element[i];
        element[i] = temp;
    }
}

int MyString::search(MyString &pattern, int start)
{
    int i = start, j = 0;
    while (i < this->n)
    {
        if (this->element[i] == pattern.element[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
        if (j == pattern.n)
            return (i - j);
    }
    return -1;
}

bool MyString::isTwisted()
{
    for (int i = 0; i < this->n / 2; i++)
    {
        int end = this->n - i - 1;
        if (element[i] != element[end])
            return false;
    }
    return true;
}

MyString MyString::substring(int i, int n)
{
    if (i < 0) i = 0;
    if (i > this->n - 1) i = (this->n - 1);
    if (n < 0) n = 0;
    if (n > this->n - i) n = this->n - i;
    MyString sub;
    sub.n = n;
    for (int j = 0; j < n; j++)
        sub.element[j] = this->element[i + j];
    sub.element[n] = '\0';
    return sub;
}
