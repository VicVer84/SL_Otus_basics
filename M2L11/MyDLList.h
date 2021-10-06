#pragma once

template <typename T>
class MyDLList {
public:
    struct Node {
        T value;
        Node* next = nullptr;
		Node* prev = nullptr;
    };

	MyDLList() : first_(nullptr), last_(nullptr), size_(0) {}
	
    ~MyDLList();

	const Node* front() const { return first_; }
	Node* front() { return first_; }
	
	const Node* back() const { return last_; }
	Node* back() { return last_; }
	
    void push_front(const T& value);
    void pop_front();
	
	void push_back(const T& value);
	void pop_back();
    
    void insert(Node* node, const T& value);
    void erase(Node* node);
	size_t size() const { return size_; } 
    
private:
    Node* first_;
	Node* last_;
	size_t size_;
};

template <typename T>
void MyDLList<T>::push_front(const T& value){
	Node* new_first = new Node;
	new_first->value = value;
	if (first_ != nullptr) {
		first_->prev = new_first;
	}
	new_first->next = first_;	
	
	if(first_ == nullptr && last_  == nullptr) {		
		last_ = new_first;
	}
	first_ = new_first;

	size_++;
}

template <typename T>
void MyDLList<T>::pop_front(){
    if(first_ != nullptr){
        auto old_first = first_;
		first_->prev = nullptr;
		first_ = first_->next;		
        delete old_first;
		size_--;
		if(first_ == nullptr){
			last_ = nullptr;
		}
    }
}

template <typename T>
void MyDLList<T>::push_back(const T& value){
    Node* new_last = new Node;
	new_last->value = value;
	if (last_ != nullptr) {
		last_->next = new_last;
	}
	new_last->prev = last_;    
	
	if(first_ == nullptr && last_  == nullptr) {		
		first_ = new_last;
	}
	last_ = new_last;
	
	size_++;
}

template <typename T>
void MyDLList<T>::pop_back(){
    if(last_ != nullptr){
        auto old_last = last_;
		last_->next = nullptr;
		last_ = last_->prev;		
        delete old_last;
		size_--;
		if(last_ == nullptr){
			first_ = nullptr;
		}
    }
}

template <typename T>
void MyDLList<T>::insert(Node* node, const T& value){
	if(node == nullptr){
		return;
	}
    if(node == first_){
        push_front(value);
        return;
    }

	auto prev = node->prev;
	Node* new_node = new Node{};	
    new_node->value = value;
    new_node->prev = prev;
	new_node->next = node;

	node->prev = new_node;
	prev->next = new_node;

	size_++;
}

template <typename T>
void MyDLList<T>::erase(Node* node){
    if(node == nullptr){
        return;
    }
	if(node == first_){
		pop_front();
		return;
	}
	if(node == last_){
		pop_back();
		return;
	}    
	auto next = node->next;
	auto prev = node->prev;
	
	prev->next = next;
	next->prev = prev;
	
	delete node;
	size_--;
    	
}
template <typename T>
MyDLList<T>::~MyDLList(){
    while(first_ != nullptr){
        pop_front();
    }
}
 