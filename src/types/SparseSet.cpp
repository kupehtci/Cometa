//include "SparseSet.h"

//#include <stdio.h>
//
//#include "debug/Assertion.h"
//
//template<typename T> 
//SparseSet<T>::SparseSet() {
//	_size = 0; 
//	_capacity = 100000; 
//	
//	_dense = std::vector<T>();
//	_sparse = std::vector<T>(_capacity, -1);		// initialize with all values to -1. Used for checking if empty
//}
//
//template<typename T>
//void SparseSet<T>::Add(size_t index, const T value) {
//	//size_t actualSize = _dense.size(); 
//	_sparse[index] = _size; 
//
//	std::count << "Added element at sparse position: " << index << " and dense position" << actualSize << std::end; 
//
//	_dense[_size] = value;
//
//	size++; 
//}
//
//template<typename T>
//void SparseSet<T>::Pop(size_t index) {
//	if (!Contains(index)) return; 
//	if (index > _capacity) {
//		COMETA_WARNING("Index to pop from sparse set out of bounds"); 
//		return; 
//	}
//}
//
//template<typename T>
//T SparseSet<T>::Get(size_t index) const {
//	if (!Contains(index)) {
//		return 0; 
//	}
//
//	return _dense[_sparse[index]]; 
//}
//
//template<typename T>
//T SparseSet<T>::GetLast() const {
//	return _size == 0 ? reinterpret_cast<T>(0) : _dense[_size]; 
//}
//
//
//template<typename T>
//bool SparseSet<T>::Contains(size_t value) const {
//	return (_sparse[value] != -1); 
//}
//
//template<typename T>
//bool SparseSet<T>::Contains(T data) const{
//	for (size_t i = 0; i < _size; i++) {
//		if (_dense[i] == data) {
//			return true; 
//		}
//	}
//
//	return false; 
//}
//
//template<typename T>
//void SparseSet<T>::Clear() {
//	_size = 0;
//}
//
//
//template<typename T>
//void SparseSet<T>::Print() const{
//	for (size_t i = 0; i < _size; i++) {
//		std::cout << "SparseSet [" << i << "] : " << _dense[i] << std::endl;
//	}
//}