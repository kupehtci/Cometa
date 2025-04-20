#ifndef COMETA_SPARSE_SET_H
#define COMETA_SPARSE_SET_H

#include <iostream>
#include <vector>
#include "debug/Assertion.h"

template<typename T>
class SparseSet {

protected: 
	std::vector<T> _dense;
	std::vector<int> _sparse; 

	size_t _size = 0;					// Number of elements within the Sparse Set. Its also a pointer to the end of the sparse set
	size_t _capacity = 100;				// Maximum capacity of the Sparse.
	size_t _denseCapacity = 100;		// Maximum capacity of the Dense.

	size_t _lastInsertedSparse = 0;		// Keeps track of the last item inserted in the sparse. This is helpful for popping items (removing efficiently)


public: 
	SparseSet() {
		_size = 0;
		_capacity = 100;
		_denseCapacity = 100;

		_dense = std::vector<T>(_denseCapacity);
		_sparse = std::vector<int>(_capacity, -1);		// initialize with all values to -1. Used for checking an empty value


		COMETA_MSG("initialized SparseSet with capacity: ", _capacity);
	}

	void Add(size_t index, const T value) {

		if (Contains(index))
		{
			COMETA_WARNING("SparseSet: Tried to insert a currently existing item");
			return;
		}

		// Increase dense and sparse capacity
		if (_size >= _denseCapacity) {
			_denseCapacity = _capacity = _denseCapacity * 2;
			_dense.resize(_denseCapacity);
			_sparse.resize(_capacity, -1);
		}
		std::cout << "Added value at index: " << index << " dense capacity: " << _denseCapacity << std::endl;

		_sparse[index] = _size;
		_dense[_size] = value;

		_lastInsertedSparse = index;

		_size++;
		// std::cout << "Current size value: " << _size << std::endl;
	}

	void Pop(size_t index) {
		if (!Contains(index)) return;

		// Swap deleted item with the last one and update both sparse's values
		_dense[_sparse[index]] = _dense[_size - 1];
		_sparse[_lastInsertedSparse] = _sparse[index];
		_sparse[index] = -1;
		_size--;
	}

	T* Get(const size_t index) {
		if (!Contains(index)) {
			return nullptr;
		}

		return &_dense[_sparse[index]];
	}

	T* GetLast() {
		return _size == 0 ? nullptr : _dense[_size - 1];
	}
	
	bool Contains (const size_t value) const {
		return (value < _capacity && _sparse[value] != -1);
	}

	bool Contains(T data) const {
		for (size_t i = 0; i < _size; i++) {
			if (_dense[i] == data) {
				return true;
			}
		}

		return false;
	}

	void Clear() {
		_size = 0;
	}

	void Print() const {
		for (size_t i = 0; i < _size; i++) {
			std::cout << "SparseSet [" << i << "] : " << _dense[i] << " dense capacity:  " << std::endl;
		}
	}

	void PrintIndex() const {
		std::cout << "SparseSet print index: " << std::endl;
		for (size_t i = 0; i < _capacity; i++) {
			if (_sparse[i] >= 0) {
				std::cout << "Sparse[" << i << "] contains dense index: " << _sparse[i] << std::endl;
			}
		}
	}


	// --------- GETTERS AND SETTERS ---------
public: 
	[[nodiscard]] size_t GetSize() const { return _size;  }
	[[nodiscard]] size_t GetCapacity() const{ return _capacity;  }
	[[nodiscard]] size_t GetDenseCapacity() const{ return _denseCapacity;  }

	// ITERATION IMPLEMENTATION
	// This allows to use the class with a for each loop, example:
	// for (auto element : example_sparse_set){} ...
	typename std::vector<T>::iterator begin() {return _dense.begin();}
	typename std::vector<T>::iterator end() {return _dense.begin() + _size;}

	typename std::vector<T>::const_iterator begin() const { return _dense.begin(); }
	typename std::vector<T>::const_iterator end() const { return _dense.begin() + _size; }
};

#endif