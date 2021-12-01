#pragma once

//#include "Iterator.h"

#include <cstdlib>
#include <cstring>


template <typename T>
class MyVector {
private:
	struct Iterator {
	public:
		Iterator(T* ptr) : ptr_(ptr) {}

		T& operator*() const {
			return *ptr_;
		}
		T* operator->() {
			return ptr_;
		}

		// Prefix increment/decrement
		Iterator& operator++() {
			++ptr_;
			return *this;
		}
		
		Iterator& operator--() {
			--m_ptr;
			return (*this);
		}

		// Postfix increment/decrement
		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator operator--(int) {
			Iterator temp(*this);
			--m_ptr;
			return temp;
		}

		Iterator& operator+=(const std::ptrdiff_t& movement) {
			m_ptr += movement;
			return (*this);
		}
		Iterator& operator-=(const std::ptrdiff_t& movement) {
			m_ptr -= movement;
			return (*this);
		}

		Iterator operator+(const std::ptrdiff_t& movement) {
			auto oldPtr = ptr_;
			ptr_ += movement;
			auto temp(*this);
			ptr_ = oldPtr;
			return temp;
		}
		Iterator operator-(const std::ptrdiff_t& movement) {
			auto oldPtr = ptr_;
			ptr_ -= movement;
			auto temp(*this);
			ptr_ = oldPtr;
			return temp;
		}

		T& operator*() {
			return *ptr_;
		}

		std::ptrdiff_t operator-(const Iterator& rawIterator) {
			return std::distance(rawIterator.getPtr(), this->getPtr());
		}

		T* getPtr()const {
			return ptr_;
		}

		friend bool operator== (const Iterator& a, const Iterator& b) {
			return a.ptr_ == b.ptr_;
		}
		friend bool operator!= (const Iterator& a, const Iterator& b) {
			return a.ptr_ != b.ptr_;
		}

	private:
		T* ptr_;
	};

	void realloc() {
		end_ *= 2;
		T* new_alloc = new T[end_];
		for (size_t i = 0; i < current_; ++i) {
			*(new_alloc + i) = *(data_ + i);
		}
		release();
		data_ = new_alloc;
	}
	void release() {
		delete[] data_;
	}

	T* data_ = nullptr;
	size_t current_ = 0; // current last used item
	size_t end_ = 0; // capacity


public:
    MyVector() = default;
    
    explicit MyVector(size_t size) : data_(new T[size]), current_(size), end_(size) {
    } 
    
	MyVector(MyVector&& other);
	
	MyVector<T>& operator=(const MyVector& other);
	
	MyVector<T>& operator=(MyVector&& other) noexcept;
	
	~MyVector(){
        release();
    }
	
    T& operator[](size_t index){
        return *(data_ + index);
    }
	
	auto begin() {
        return Iterator(data_);
    }
	
    auto end() {
        return Iterator(data_ + current_);
    }
	
    const auto begin() const {
        return Iterator(data_);
    }
	
    const auto end() const {
        return Iterator(data_ + current_);
    }
	
    size_t size() const{
        return current_;
    }
	
    size_t capacity() const{
        return end_;
    }
	
	void push_back(const T& value);
	void erase(const size_t pos);
	void insert(const size_t pos, const T& value);	
};

template <typename T>
MyVector<T>::MyVector(MyVector&& other) : data_(std::move(other.data_))
										, current_(std::move(other.current_))
										, end_(std::move(other.end_)) {
	other.data_ = nullptr;
	other.current_ = 0;
	other.end_ = 0;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
	if (this != &other) {
		this->release();
		data_ = nullptr;
		data_ = new T[other.end_];
		current_ = other.current_;
		end_ = other.end_;
		std::copy(other.data_, other.data_ + other.end_, data_);
		//std::copy(other.begin(), other.end(), begin());
	}
	return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector&& other) noexcept {
	if (this != &other) {
		this->release();
		data_ = std::move(other.data_);
		other.data_ = nullptr;
		current_ = std::move(other.current_);
		end_ = std::move(other.end_);
		other.current_ = 0;
		other.end_ = 0;
	}
	return *this;
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
	if (end_ == 0) {
		release();
		data_ = new T[1];
		end_ = 1;
	}
	if (size() == capacity()) {
		realloc();
	}
	data_[current_] = value;
	current_++;
}


template <typename T>
void MyVector<T>::erase(const size_t pos) {
	if (pos > current_) {
		return;
	}
	for (size_t i = pos; i < current_; ++i) {
		*(data_ + i) = *(data_ + 1 + i);
	}
	--current_;
}

template <typename T>
void MyVector<T>::insert(const size_t pos, const T& value) {
	if (end_ == 0) {
		release();
		data_ = new T[1];
		end_ = 1;
	}
	if (size() == capacity()) {
		realloc();
	}
	// there is no clue on what to do if pos exceeds the size of container, so if pos is more than size(), insert will perform push_back
	if (pos >= current_) {
		push_back(value);
		return;
	}

	// shift(copy) every element from last down to pos to the next "cell" of container
	for (size_t i = current_; i >= pos; --i) {
		// size_t overflow protection;
		if (i > current_) {
			break;
		}
		*(data_ + 1 + i) = *(data_ + i);
	}
	// assign new value at pos
	*(data_ + pos) = value;

	current_++;
}