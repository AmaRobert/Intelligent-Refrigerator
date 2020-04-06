#pragma once
#include "DynamicArray.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>


DynamicArray* createDynamicArray(int capacity)
{
	DynamicArray* dynamicVector = (DynamicArray*)malloc(sizeof(DynamicArray));
	if (dynamicVector == NULL)
		return NULL;

	dynamicVector->arr = (TElement*)malloc(capacity * sizeof(TElement));
	if (dynamicVector == NULL)
		return NULL;

	dynamicVector->size = 0;
	dynamicVector->capacity = capacity;

	return dynamicVector;
}

void destroyArray(DynamicArray* dynamicVector)
{
	if (dynamicVector == NULL)
		return;

	for (int i = 0; i < dynamicVector->size; i++)
		destroyProduct(dynamicVector->arr[i]);

	free(dynamicVector->arr);

	free(dynamicVector);
}

int resize(DynamicArray* dynamicVector)
{
	if (dynamicVector == NULL)
	{
		return -1;
	}
	dynamicVector->capacity *= 2;
	TElement* arr2 = (TElement*)malloc(dynamicVector->capacity * sizeof(TElement));
	if(arr2 == NULL)
		return -1;	
	for (int i = 0; i < dynamicVector->size; i++)
		arr2[i] = dynamicVector->arr[i];
	free(dynamicVector->arr);
	dynamicVector->arr = arr2;
	return 0;
}

void addElement(DynamicArray* dynamicVector, TElement element)
{
	if (dynamicVector == NULL)
		return;
	if (dynamicVector->arr == NULL)
		return;

	// resize the array, if necesarry
	if (dynamicVector->size >= dynamicVector->capacity)
		resize(dynamicVector);
	dynamicVector->arr[dynamicVector->size++] = element;
}

int deleteElement(DynamicArray* dynamicVector, int index)
{
	int i;
	
	for (i = index; i < dynamicVector->size - 1; i++)
	{
		dynamicVector->arr[i] = dynamicVector->arr[i + 1];
	}
	dynamicVector->size--;
	return 1;
	
}

int getSize(DynamicArray* dynamicVector)
{
	if (dynamicVector == NULL)
		return -1;

	return dynamicVector->size;
}

TElement get(DynamicArray* dynamicVector, int pos)
{
	return dynamicVector->arr[pos];
}

/*
void updateElement(DynamicArray* dynamicVector, Product element)
{
	int i;
	for (i = 0; i < dynamicVector->size; i++)
	{
		if (strcmp(getName(dynamicVector->arr[i]), element.name) == 0 && strcmp(getCategory(dynamicVector->arr[i]), element.category) == 0)
		{
			setQuantity(dynamicVector->arr[i],element.quantity);
		}
	}
}
DynamicArray* copyVector(DynamicArray* dynamicVector)
{
	int i;
	DynamicArray* copie = createDynamicArray(2);
	for (i = 0; i < dynamicVector->size; i++)
	{
		addElement(copie, dynamicVector->arr[i]);
	}
	return copie;
}

DynamicArray* searchString(DynamicArray* dynamicVector, char* str)
{
	int i;
	DynamicArray* copy = copyVector(dynamicVector);
	for (i = 0; i < copy->size; i++)
	{

		if (strstr(getName(copy->arr[i]), str) == NULL)
		{
			int ok = deleteElement(copy, copy->arr[i]);
			i--;
		}

	}


	return copy;
}
void orderByQuantity(DynamicArray* copy)
{
	int i, j;

	Product* aux;
	for (i = 0; i < copy->size - 1; i++)
	{
		for (j = i + 1; j < copy->size; j++)
		{
			if (getQuantity(copy->arr[i]) > getQuantity(copy->arr[j]))
			{
				aux = copy->arr[i];
				copy->arr[i] = copy->arr[j];
				copy->arr[j] = aux;
			}
		}
	}
}

void orderByName(DynamicArray* copy)
{
	int i, j;

	Product* aux;
	for (i = 0; i < copy->size - 1; i++)
	{
		for (j = i + 1; j < copy->size; j++)
		{
			if (strcmp(getName(copy->arr[i]), getName(copy->arr[j])) > 0)
			{
				aux = copy->arr[i];
				copy->arr[i] = copy->arr[j];
				copy->arr[j] = aux;
			}
		}
	}
}

int searchElement(DynamicArray* dynamicVector, Product element)
{
	int i;
	for (i = 0; i < dynamicVector->size; i++)
	{
		if (strcmp(getName(dynamicVector->arr[i]), element.name) == 0 && strcmp(getCategory(dynamicVector->arr[i]), element.category) == 0)
		{
			return i;
		}
	}
	return -1;
}
*/
// TESTS --------------------------------------------------------------------------
void testsDynamicArray()
{
	DynamicArray* da = createDynamicArray(2);
	if (da == NULL)
		assert(0);

	assert(da->capacity == 2);
	assert(da->size == 0);
	Data d;
	d.day = 1;
	d.month = 10;
	d.year = 2010;
	Product* p1 = createProduct("lapte", "nush", 5, d);
	addElement(da, p1);
	assert(da->size == 1);

	Product* p2 = createProduct("mar", "fruct", 3,d);
	addElement(da, p2);
	assert(da->size == 2);

	Product* p3 = createProduct("cascaval", "nush", 1,d);
	addElement(da, p3);
	assert(da->size == 3);
	assert(da->capacity == 4);

	// delete Product on position 0
	// first get the pointer to the Product, to still be able to access the pointed memory
	Product* p = get(da, 0);
	deleteElement(da, 0);
	destroyProduct(p); // What is another option for implementing the function "delete" to make sure that the Product is destroyed inside?

	p = get(da, 0);
	assert(strcmp(getName(p), "mar") == 0);
	assert(da->size == 2);

	// destroy the dynamic array - this will also destroy the Products
	destroyArray(da);
}