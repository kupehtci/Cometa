#ifndef COMETA_SPARSE_SET_H
#define COMETA_SPARSE_SET_H

#include <vector>

template<typename T>
class SparseSet {

private: 
	std::vector<T> _dense;
	std::vector<size_t> _sparse; 

	size_t _size = 0;				// Number of elements within the Sparse Set
	size_t _capacity = 100000;		// Maximum capacity of the SparseSet. Used for initialization 


public: 
	SparseSet();

	void Add(size_t index, const T value);
	void Pop(size_t index);

	T Get(size_t index) const; 
	
	bool Contains(size_t value) const; 
	bool Contains(T data) const; 

	void Print() const; 


};

#endif