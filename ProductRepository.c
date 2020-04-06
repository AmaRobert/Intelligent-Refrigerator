#pragma once
#include "ProductRepository.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

ProductRepo* createRepo()
{
	ProductRepo* repo = (ProductRepo*)malloc(sizeof(ProductRepo));
	repo->products = createDynamicArray(2);

	return repo;
}

void destroyRepo(ProductRepo* repo)
{
	if (repo == NULL)
		return;
	destroyArray(repo->products);
	free(repo);
}

int findPosOfProduct(ProductRepo* repo, char* name)
{
	int index = -1;
	for (int i = 0; i < getSize(repo->products); i++)
	{
		if (strcmp(getName(repo->products->arr[i]), name) == 0)
			index = i;
	}
	return index;
}

int add(ProductRepo* repo, Product* product)
{
	if (repo == NULL)
		return 0;
	if (findPosOfProduct(repo, getName(product)) != -1)
		return 0;

	Product* copy = copyProduct(product);
	addElement(repo->products, copy);
	return 1;
}

int deleteProduct(ProductRepo* v, char* name)
{
	if (v == NULL)
		return 0;
	int i = findPosOfProduct(v, name);
	Product* product = get(v->products, i);
	destroyProduct(product);
	if (i == -1)
		return 0;
	deleteElement(v->products, i);
	return 1;
}

int updateProduct(ProductRepo* v, Product* product)
{
	if (v == NULL)
		return 0;
	int i = findPosOfProduct(v, getName(product));
	if (i == -1)
		return 0;

	strcpy(v->products->arr[i]->category, getCategory(product));
	v->products->arr[i]->quantity = getQuantity(product);
	v->products->arr[i]->dataC = getData(product);
	return 1;
}
DynamicArray* copyVector(DynamicArray* dynamicVector)
{
	int i;
	DynamicArray* copie = createDynamicArray(2);
	for (i = 0; i < dynamicVector->size; i++)
	{
		addElement(copie,copyProduct(dynamicVector->arr[i]));
	}
	return copie;
}

DynamicArray* searchString(DynamicArray* dynamicVector, char* str)
{
	int i;
	printf(str);
	printf("%d", dynamicVector->size);
	for (i = 0; i < dynamicVector->size; i++)
	{

		if (strstr(dynamicVector->arr[i]->name, str) == NULL)
		{
			int ok = deleteElement(dynamicVector, i);
			i--;
		}

	}


	return dynamicVector;
}
DynamicArray* searchStringCategory(DynamicArray* dynamicVector, char* str,Data d)
{
	int i;
	printf(str);
	printf("%d", dynamicVector->size);
	for (i = 0; i < dynamicVector->size; i++)
	{

		if (strstr(dynamicVector->arr[i]->category, str) != NULL )
		{
			if (dynamicVector->arr[i]->dataC.year > d.year)
			{
				int ok = deleteElement(dynamicVector, i);
				i--;
			}
			else {
				if (dynamicVector->arr[i]->dataC.month > d.month)
				{
					int ok = deleteElement(dynamicVector, i);
					i--;

				}
				else
				{
					if (dynamicVector->arr[i]->dataC.day > d.day)
					{
						int ok = deleteElement(dynamicVector, i);
						i--;
					}

				}
					

			}
		
		}
		else
		{
			int ok = deleteElement(dynamicVector, i);
			i--;
				
				
			
		}





	}


	return dynamicVector;
}
void orderByQuantity(DynamicArray* copy)
{
	int i, j;

	Product* aux;
	for (i = 0; i < copy->size - 1; i++)
	{
		for (j = i + 1; j < copy->size; j++)
		{
			if (copy->arr[i]->quantity > copy->arr[j]->quantity)
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
			if (strcmp(copy->arr[i]->name, copy->arr[j]->name) > 0)
			{
				aux = copy->arr[i];
				copy->arr[i] = copy->arr[j];
				copy->arr[j] = aux;
			}
		}
	}
}

int getRepoLength(ProductRepo* v)
{
	if (v == NULL)
		return -1;

	return getSize(v->products);
}

Product* getProductOnPos(ProductRepo* v, int pos)
{
	return v->products->arr[pos];

}


// Tests
void testAdd()
{
	ProductRepo* v = createRepo();
	Data d;
	d.day = 1;
	d.month = 10;
	d.year = 2010;
	Product* p1 = createProduct("portocala", "fruct", 3,d);
	add(v, p1);
	assert(getRepoLength(v) == 1);
	assert(strcmp(getName(getProductOnPos(v, 0)), "portocala") == 0);
	deleteProduct(v, getName(getProductOnPos(v, 0)));
	assert(getRepoLength(v) == 0);
	add(v, p1);
	Product* p2 = createProduct("unt", "nush", 4,d);
	assert(add(v, p2) == 1);
	assert(getRepoLength(v) == 2);

	assert(findPosOfProduct(v, "unt") == 1);

	// now try to add the same Product again -> add must return 0
	assert(add(v, p2) == 0);

	// destroy the test repository
	destroyRepo(v);

	// now the memory allocated for the Products must be freed
	destroyProduct(p1);
	destroyProduct(p2);
}

void testsProductRepo()
{
	testAdd();
}