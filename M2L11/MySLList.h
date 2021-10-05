#pragma once

template <typename T>
class MySLList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
    };

    ~MySLList();

    void push_front(const T& value);
    void pop_front();
    
    void insert(Node* node, const T& value);
    void erase(Node* node);
    
    Node* getHead() { return head; }
    const Node* getHead() const { return head; }
private:
    Node* head = nullptr;
};

template <typename T>
void MySLList<T>::push_front(const T& value){
    Node* new_head = new Node;
	new_head->value = value;
	new_head->next = head;       
    head = new_head;
}

template <typename T>
void MySLList<T>::pop_front(){
    if(head != nullptr){
        auto old_head = head;
        head = head->next;
        delete old_head;
    }
}
template <typename T>
void MySLList<T>::insert(Node* node, const T& value){
    if(node == nullptr){
        push_front(value);
        return;
    }
    Node* new_node = new Node{};
    new_node->value = value;
    new_node->next = node->next;

    node->next = new_node;
}

template <typename T>
void MySLList<T>::erase(Node* node){
    if(node == nullptr){
        pop_front();
        return;
    }
    if(node->next != nullptr){
        auto buf = node->next;
        node->next = buf->next;
        delete buf;
    }
}
template <typename T>
MySLList<T>::~MySLList(){
    while(head != nullptr){
        pop_front();
    }
}