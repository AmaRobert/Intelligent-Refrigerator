#pragma once
#include "Product.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
Product* createProduct(char name[], char category[], int quantity) {
	Product product;
	strcpy(product.name, name);
	strcpy(product.category, category);
	product.quantity = quantity;
	Product *product2 = product;
	return product2;
}
*/


Product* createProduct(char* name, char* category, int quantity, Data dataC)
{
	Product* new_product = (Product*)malloc(sizeof(Product));

	new_product->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(new_product->name, name);

	new_product->category = (char*)malloc(sizeof(char) * (strlen(category) + 1));
	strcpy(new_product->category, category);

	new_product->quantity = quantity;

	new_product->dataC = dataC;

	return new_product;
}
void destroyProduct(Product* p)
{
	if (p == NULL)
		return;
	free(p->name);
	free(p->category);
	
	free(p);
}
Product* copyProduct(Product* p)
{
	if (p == NULL)
		return NULL;

	Product* newProduct = createProduct(getName(p), getCategory(p), getQuantity(p), getData(p));
	return newProduct;
}
char* toString(Product* product) {
	char *productToString = (char*)malloc(100 * sizeof(char));
	sprintf(productToString, "Product: %s ; Category: %s ; Quantity: %d ; Data:%d-%d-%d \n", product->name, product->category, product->quantity, product->dataC.day, product->dataC.month, product->dataC.year);
	return productToString;
}

char* getName(Product* product) {
	return product->name;
}

char* getCategory(Product* product)
{
	return product->category;
}

void setQuantity(Product* product, int quantity)
{
	product->quantity = quantity;
}

int getQuantity(Product* product)
{
	return product->quantity;
}

Data getData(Product* product)
{
	return product->dataC;
}