#include <iostream>
using namespace std;

template <typename T>
struct Node
{
    T Data;
    Node* Next;
    Node(T data, Node* next){
        Data = data;
        Next = next;
    }
};



template <typename T>
struct ListIterator
{
    using iterator_category = forward_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using reference = T&;
    using pointer = T*;
    ListIterator(Node<T>* node): _node(node){};
    reference operator*() const {return _node->Data;};
    pointer operator->() {return &(_node->Data);};
    ListIterator& operator++(){_node = _node->Next; return *this;};
    ListIterator operator++(int){ListIterator t = *this; ++(*this); return t;};
    friend bool operator==(const ListIterator& a, const ListIterator& b){return a._node == b._node;};
    friend bool operator!=(const ListIterator& a, const ListIterator& b){return a._node != b._node;};
    private:
        Node<T>* _node;
};

template <typename T>
struct ConstListIterator
{
    using iterator_category = forward_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = T;
    using reference = const T&;
    using pointer = const T*;
    ConstListIterator(Node<T>* node): _node(node){};
    const reference operator*() const {return _node->Data;};
    const pointer operator->() {return &(_node->Data);};
    ConstListIterator& operator++(){_node = _node->Next; return *this;};
    ConstListIterator operator++(int){ConstListIterator t = *this; ++(*this); return t;};
    friend bool operator==(const ConstListIterator& a, const ConstListIterator& b){return a._node == b._node;};
    friend bool operator!=(const ConstListIterator& a, const ConstListIterator& b){return a._node != b._node;};
    private:
        Node<T>* _node;
};

template <typename T>
class MyForwardList
{
private:
    Node<T>* _head;
    Node<T>* _tail;
public:
    MyForwardList(){
        _head = nullptr;
        _tail = nullptr;
    };
    void Add(T data){
        if (_head == nullptr){
            _head = new Node<T>(data, nullptr);
            _tail = _head;
        }else{
            _tail->Next = new Node<T>(data, nullptr);
            _tail = _tail->Next;
        }
    };
    void Delete(T data){
        if (_head->Data == data){
            Node<T>* tmp = _head;
            delete [] _head;
            _head = tmp->Next;
        }else{
        ListIterator<T> tmp = this->begin();
        for (auto it = *this->begin(); it != *this->end(); it++){
            if (*it == data){
                ListIterator<T> t = it;
                delete [] it;
                tmp->Next = t->Next;
                return;
            }
            ListIterator<T>* tmp = it;
        }
        return;}
    };
    bool Contains(T data){
        return false;
    };
    ListIterator<T> begin(){return ListIterator<T>(_head);};
    ListIterator<T> end(){return ListIterator<T>(_tail->Next);};
    ConstListIterator<T> cbegin(){return ConstListIterator<T>(_head);};
    ConstListIterator<T> cend(){return ConstListIterator<T>(_tail->Next);};
    ~MyForwardList(){};
};

struct Iterator
{
    using iterator_category = forward_iterator_tag;
    using difference_type = ptrdiff_t;
    using value_type = int;
    using reference = int&;
    using pointer = int*;
    Iterator(pointer ptr): _ptr(ptr){};
    reference operator*() const {return *_ptr;};
    pointer operator->() {return _ptr;};
    Iterator& operator++(){_ptr++; return *this;};
    Iterator operator++(int){Iterator t = *this; ++(*this); return t;};
    friend bool operator==(const Iterator& a, const Iterator& b){return a._ptr == b._ptr;};
    friend bool operator!=(const Iterator& a, const Iterator& b){return a._ptr != b._ptr;};
    private:
        pointer _ptr;
};

class ConstIterator{
    public:
        using iterator_category = forward_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = int;
        using reference = const int&;
        using pointer = const int*;
        ConstIterator(pointer ptr): _ptr(ptr){};
        const reference operator*() const {return *_ptr;};
        const pointer operator->() {return _ptr;};
        ConstIterator& operator++(){_ptr++; return *this;};
        ConstIterator operator++(int){ConstIterator t = *this; ++(*this); return t;};
        friend bool operator==(const ConstIterator& a, const ConstIterator& b){return a._ptr == b._ptr;};
        friend bool operator!=(const ConstIterator& a, const ConstIterator& b){return a._ptr != b._ptr;};
    private:
        pointer _ptr;
};

class IntArr
{
private:
    int _data[99];
public:
    Iterator begin(){return Iterator(&_data[0]);};
    Iterator end(){return Iterator(&_data[99]);};//DOPISAT AND PROTESTIT
    ConstIterator cbegin(){return ConstIterator(&_data[0]);};
    ConstIterator cend(){return ConstIterator(&_data[99]);};
};





int main(){
    MyForwardList<int> mlf;
    mlf.Add(5);
    mlf.Add(777);
    mlf.Add(1000);
    mlf.Delete(777);
    for (auto it = mlf.cbegin(); it != mlf.cend(); it++){
            cout << *it << endl;
        }
    return 0;
}

// #include <iostream>
// #include <vector>
// #include <algorithm>
// #include <forward_list>

// using std::cout;
// using std::endl;
// using std::sort;
// using std::vector;




// int main(){
//     vector<int> vec = {1, 3, -5, -2, 0, 10, -10};
//     std::forward_list<int> list = {1, 3, -5, -2, 0, 10, -10};
//     sort(vec.begin(), vec.end());
//     sort(list.begin(), list.end()); //FORWARD ACCESS < RANDOM ACCESS
//     for(auto it : vec) cout << it << endl; // ВЕКТОР НЕ МЕНЯЕТСЯ
//     return 0;
// }