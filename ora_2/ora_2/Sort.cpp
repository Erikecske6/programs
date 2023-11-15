#include "Sort.hpp"

int* copyToNew(int* array, int length) {
	//Létrehoz és átmásol egy új tömbbe
	int* copy = new int[length];
	for (int i = 0; i < length; i++) {
		copy[i] = array[i];
	}
	return copy;
};

void bubbleSort(int* array, int length) {
	for (int i=length-1;i>0;i--)
		for (int j = 0; j < i; j++) {
			if (array[j] > array[j + 1]) {
				int tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}

};

int Sum(int* array, int length) {
	int summa = 0;
	for (int i = 0; i < length; i++) 
		summa += array[i];
	return summa;
};

int* Sum(int* array1, int* array2, int length) {
	int* summa = new int[length];
	for (int i = 0; i < length; i++) 
		summa[i] = array1[i] + array2[i];
	return summa;
};