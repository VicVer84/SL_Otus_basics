#pragma once

#include "Iterator.h"

#include <cstdlib>
#include <cstring>

template <typename T>
class MyVector {
public:
    MyVector() = default;
    
    explicit MyVector(size_t size) : data_(new T[size]), current_(size), end_(size) {
    } 
    ~MyVector(){
        release();
    }
    
    T& operator[](size_t index){
        return *(data_ + index);
    }

    /*T* begin() {
        return data_;
    }
	
    T* end() {
        return data_ + current_;
    }
	
    const T* begin() const {
        return data_;
    }
	
    const T* end() const {
        return data_ + current_;
    }*/
	
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
	
    void push_back(const T& value){
        if(end_ == 0){
            release();
            data_ = new T[1];
            end_ = 1;
        }
        if(size() == capacity()){
            realloc();
        }            
        data_[current_] = value;
        current_++;                 
    }
	
	void insert(const size_t pos, const T& value) {
		if(end_ == 0){
            release();
            data_ = new T[1];
            end_ = 1;
        }
        if(size() == capacity()){
			realloc();
        }
		// there is no clue on what to do if pos exceeds the size of container, so if pos is more than size(), insert will perform push_back
		if(pos >= current_){ 
			push_back(value);
			return;
		}
		
		// shift(copy) every element from last down to pos minus one to the next "cell" of container
		for(size_t i = current_; i >= pos; --i) {
			// if pos = 0 then when i reaches 0 next number will be again more than pos
			if(i > current_){ 
				break;
			}
			*(data_ + 1 + i) = *(data_ + i);
		}
		// assign new value at pos
		*(data_ + pos) = value;
		
		current_++;
	}

	void erase(const size_t pos) {
		if(pos > current_) { 
			return;
		}
		for(size_t i = pos; i < current_; ++i) {
			*(data_ + i) = *(data_ + 1 + i);
		}
		--current_;
	}	

private:
    T* data_ = nullptr;
    size_t current_ = 0; // current last used item
    size_t end_ = 0; // capacity
   
    void realloc(){
        end_ *= 2;
        T* new_alloc = new T[end_];
        for(size_t i = 0; i < current_; ++i){
            *(new_alloc + i) = *(data_ + i);
        }
        release();
        data_ = new_alloc;        
    }
    void release(){
        delete[] data_;
    }
};