#pragma once

#include <iostream> //kell -->  ebben vannak az alapvetõ fv-ek amiket használunk; cout endl
#include <cmath>    //math.h helyett
#include <ctime>    //randomlás
#include <iomanip>  //width...

//#include "Pragma.hpp"


#define SZAM 45

using namespace std;

int* copyToNew(int* array, int length = 100);
void bubbleSort(int* array, int length);
int Sum(int* array, int length = 100);
int* Sum(int* array1,int* array2, int length = 100);