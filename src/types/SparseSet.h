#ifndef COMETA_SPARSE_SET_H
#define COMETA_SPARSE_SET_H

#include <vector>

template<typename T>
class SparseSet {

private: 
	std::vector<T> _dense;
	std::vector<int> _sparse; 

	size_t _size = 0;				// Number of elements within the Sparse Set. Its also a pointer to the end of the sparse set
	size_t _capacity = 100000;		// Maximum capacity of the SparseSet. Used for initialization 
	size_t _denseCapacity = 10; 


public: 
	SparseSet() {
		_size = 0;
		_capacity = 100000;
		_denseCapacity = 10; 

		_dense = std::vector<T>(_denseCapacity);
		_sparse = std::vector<int>(_capacity, -1);		// initialize with all values to -1. Used for checking if empty
		for (size_t i = 0; i < _capacity; i++) {
			_sparse[i] = -1; 
		}
	}

	void Add(size_t index, const T value) {

		// Increase dense capacity
		if (_size >= _denseCapacity) {
			_denseCapacity = _denseCapacity * 2; 
			_dense.resize(_denseCapacity); 
		}
		std::cout << "Added " << value << " at index: " << index << " dense capacity: " << _denseCapacity << std::endl; 

		_sparse[index] = _size;
		_dense[_size] = value;

		_size++;
	}

	void Pop(size_t index) {
		if (!Contains(index)) return;
		if (index > _capacity) {
			COMETA_WARNING("Index to pop from sparse set out of bounds");
			return;
		}

		_dense[index] = _dense[_size - 1];
		_size--; 
	}

	T Get(size_t index) const {
		if (!Contains(index)) {
			return 0;
		}

		return _dense[_sparse[index]];
	}

	T GetLast() const {
		return _size == 0 ? reinterpret_cast<T>(0) : _dense[_size];
	}
	
	bool Contains(size_t value) const {
		return (_sparse[value] != -1);
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
		for (size_t i = 0; i < _sparse.size(); i++) {
			if (_sparse[i] >= 0) {
				std::cout << "[" << i << "] index value: " << _sparse[i] << " has value associated in dense: " << _dense[_sparse[i]] << std::endl; 
			}
		}
	}


	// --------- GETTERS AND SETTERS ---------
public: 
	size_t GetSize() const { return _size;  }
	size_t GetCapacity() const{ return _capacity;  }
};

#endif