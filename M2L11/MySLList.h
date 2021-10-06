#pragma once

template <typename T>
class MySLList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
    };

	MySLList() : head_(nullptr), size_(0) {}
	
    ~MySLList();

    void push_front(const T& value);
    void pop_front();
    
    void insert(Node* node, const T& value);
    void erase(Node* node);
	size_t size() const { return size_; } 
    
    Node* getHead() { return head_; }
    const Node* getHead() const { return head_; }
private:
    Node* head_;
	size_t size_;
};

template <typename T>
void MySLList<T>::push_front(const T& value){
    Node* new_head = new Node;
	new_head->value = value;
	new_head->next = head_;       
    head_ = new_head;
	size_++;
}

template <typename T>
void MySLList<T>::pop_front(){
    if(head_ != nullptr){
        auto old_head = head_;
        head_ = head_->next;
        delete old_head;
		size_--;
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
	size_++;
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
		size_--;
    }	
}
template <typename T>
MySLList<T>::~MySLList(){
    while(head_ != nullptr){
        pop_front();
    }
}