#pragma once
#include "Product.h"
#include "DynamicArray.h"

typedef struct
{
	DynamicArray* products;
}ProductRepo;

ProductRepo* createRepo();

void destroyRepo(ProductRepo* repo);

int findPosOfProduct(ProductRepo* repo, char* name);

DynamicArray* copyVector(DynamicArray* dynamicVector);

DynamicArray* searchString(DynamicArray* dynamicVector, char* str);

void orderByQuantity(DynamicArray* copy);

void orderByName(DynamicArray* copy);

int add(ProductRepo* repo, Product* product);

int deleteProduct(ProductRepo* v, char* name);

int updateProduct(ProductRepo* v, Product* product);

int getRepoLength(ProductRepo* v);

Product* getProductOnPos(ProductRepo* v, int pos);

void testsProductRepo();

