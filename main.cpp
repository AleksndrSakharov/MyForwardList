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
class QueueMyForwardList
{
private:
    Node<T>* _head;
    Node<T>* _tail;
    size_t _size;
    size_t _count;
public:
    QueueMyForwardList() : _size(1000), _count(0){
        _head = nullptr;
        _tail = nullptr;
    };
    QueueMyForwardList(size_t size) : _size(size), _count(0){
        _head = nullptr;
        _tail = nullptr;
    };
    void Push(T data){
        if (_size == _count) return;
        if (_head == nullptr){
            _head = new Node<T>(data, nullptr);
            _tail = _head;
            _count++;
            _tail->Next = nullptr;
        }else{
            _tail->Next = new Node<T>(data, nullptr);
            _tail = _tail->Next;
            _count++;
            _tail->Next = nullptr;
        }
    };
    void Pop() {
    if (!_head) return; 
    auto tmp = _head;
    _head = _head->Next;
    _count--;
    delete tmp;
};
    bool Contains(T data){
        ListIterator<T> it = begin();
        while (it != end()){
            if (*it == data) return true;
            it++;
        }
        return false;
    };
    ListIterator<T> begin(){return ListIterator<T>(_head);};
    ListIterator<T> end(){return ListIterator<T>(_tail->Next);};
    size_t size(){return _size;}
    size_t count(){return _count;}
    ConstListIterator<T> cbegin(){return ConstListIterator<T>(_head);};
    ConstListIterator<T> cend(){return ConstListIterator<T>(_tail->Next);};
    ~QueueMyForwardList(){
        ListIterator<T> it = begin();
        Node<T>* prev = _head;
        Node<T>* curr = _head->Next;
        it++;
        for (it; it != end(); it++) {
            if (curr != _tail){
            delete prev;
            prev = curr;
            curr = curr->Next;
            }
            else {
                delete prev;
                delete curr;
                return;
            }
        }
    };
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
    void Delete(T data) {
    if (!_head) return; 

    ListIterator<T> it = begin();
    if (*it == data) {
        Node<T>* tmp = _head;
        _head = _head->Next;
        delete tmp;
        if (!_head) _tail = nullptr;
        return;
    }
    Node<T>* prev = _head;
    Node<T>* curr = _head->Next;
    it++;
    for (it; it != end(); it++) {
        if (*it == data) {
            prev->Next = curr->Next;
            if (curr == _tail) _tail = prev;
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->Next;
    }
};
    bool Contains(T data){
        ListIterator<T> it = begin();
        while (it != end()){
            if (*it == data) return true;
            it++;
        }
        return false;
    };
    ListIterator<T> begin(){return ListIterator<T>(_head);};
    ListIterator<T> end(){return ListIterator<T>(_tail->Next);};
    ConstListIterator<T> cbegin(){return ConstListIterator<T>(_head);};
    ConstListIterator<T> cend(){return ConstListIterator<T>(_tail->Next);};
    ~MyForwardList(){
        ListIterator<T> it = begin();
        Node<T>* prev = _head;
        Node<T>* curr = _head->Next;
        it++;
        for (it; it != end(); it++) {
            if (curr != _tail){
            delete prev;
            prev = curr;
            curr = curr->Next;
            }
            else {
                delete prev;
                delete curr;
                return;
            }
        }
    };
};



int main(){
    QueueMyForwardList<int> mlf(3);
    mlf.Push(5);
    mlf.Push(777);
    mlf.Push(1000);
    mlf.Pop();
    for (auto it = mlf.cbegin(); it != mlf.cend(); it++){
            cout << *it << endl;
        }
        cout << endl;
    for (auto it = mlf.begin(); it != mlf.end(); it++){
            *it += 1;
            cout << *it << endl;
        }
        cout << endl;

        for (auto it = mlf.cbegin(); it != mlf.cend(); it++){
            cout << *it << endl;
        }
    mlf.Contains(5) ? cout <<  "yes " : cout <<  "no ";
    mlf.Contains(1001) ? cout <<  "yes " : cout <<  "no ";
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