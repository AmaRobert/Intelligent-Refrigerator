#pragma once
typedef struct {
	int day, month, year;
}Data;
typedef struct {
	char* name;
	char* category;
	int quantity;
	Data dataC;
}Product;

Product* createProduct(char *name, char *category, int quantity, Data dataC);
void destroyProduct(Product* product);
Product* copyProduct(Product* product);

char* toString(Product* product);

char* getName(Product* product);
char* getCategory(Product* product);
void setQuantity(Product* product, int quantity);
int getQuantity(Product* product);
Data getData(Product* product);