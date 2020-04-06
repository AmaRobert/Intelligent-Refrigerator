#pragma once
#include "Product.h"

typedef Product* TElement;

typedef struct
{
	TElement* arr;
	int size, capacity;

}DynamicArray;

DynamicArray * createDynamicArray(int capacity);


void destroyArray(DynamicArray*);

int resize(DynamicArray* dynamicVector);

void addElement(DynamicArray* dynamicVector, TElement element);

int deleteElement(DynamicArray* dynamicVector, int pos);

int getSize(DynamicArray* dynamicVector);

TElement get(DynamicArray* dynamicVector, int pos);

void testsDynamicArray();