#include "SparseSet.h"

#include <stdio.h>

template<typename T> 
SparseSet<T>::SparseSet() {
	_size = 0; 
	_capacity = 100000; 
	
	_dense = std::vector<T>();
	_sparse = std::vector<T>(_capacity, -1);		// initialize with all values to -1. Used for checking if empty
}

template<typename T>
void SparseSet<T>::Add(size_t index, const T value) {
	size_t actualSize = _dense.size(); 
	_sparse[index] = actualSize; 

	std::count << "Added element at sparse position: " << index << " and dense position" << actualSize << std::end; 

	_dense.push_back(value);

	size++; 
}

template<typename T>
void SparseSet<T>::Pop(size_t index) {
	
}

template<typename T>
T Get(size_t index) const {
	if (!Contains(index)) {
		return 0; 
	}

	return _dense[_sparse[index]]; 
}


template<typename T>
bool SparseSet<T>::Contains(size_t value) const {
	return (_sparse[value] != -1); 
}
