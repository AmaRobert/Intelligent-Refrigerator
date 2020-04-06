#pragma once
#include "Controller.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>

Controller* createController(ProductRepo* r, OperationsStack* undoS, OperationsStack* redoS)
{
	Controller* c = (Controller*)malloc(sizeof(Controller));
	c->repo = r;
	c->undoStack = undoS;
	c->redoStack = redoS;

	return c;
}

void destroyController(Controller * c)
{	
	
	// first destroy the repository inside
	destroyRepo(c->repo);

	// then the operation stack
	destroyStack(c->undoStack);
	destroyStack(c->redoStack);

	// then free the memory
	free(c);
}

int addProductCtrl(Controller* c, char* name, char* category, int quantity, Data dataC)
{
	Product* p = createProduct(name,category,quantity,dataC);

	int res = add(c->repo, p);

	if (res == 1) // if the product was successfully added - register the operation
	{
		Operation* o = createOperation(p, "add");
		push(c->undoStack, o);
		// once added, the operation can be destroyed (a copy of the operation was added)
		destroyOperation(o);
	}

	// destroy the product that was just created, as the repository stored a copy
	destroyProduct(p);

	return res;
}

int deleteProductCtrl(Controller* c, char* name)
{	int i = findPosOfProduct(c->repo, name);
	Product* p = copyProduct(getProductOnPos(c->repo, i));
	int res = deleteProduct(c->repo, name);

	if (res == 1)// if the product was deleted
	{
		Operation* o = createOperation(p, "remove");
		push(c->undoStack, o);
		destroyOperation(o);
		return 1;
	}
	destroyProduct(p);
	return 0;
}
int updateProductCtrl(Controller* c, char* name, char* category, int quantity, Data dataC)
{
	Product* p = createProduct(name, category, quantity, dataC);
	
	int index = findPosOfProduct(c->repo, name);
	Product* p2 = copyProduct(getProductOnPos(c->repo, index));
	int res = updateProduct(c->repo, p);

	if (res == 1) // if the product was successfully added - register the operation
	{
		Operation* o = createOperation(p, "update");
		push(c->undoStack, o);
		// once added, the operation can be destroyed (a copy of the operation was added)
		destroyOperation(o);
	}

	// destroy the planet that was just created, as the repository stored a copy
	destroyProduct(p);
	destroyProduct(p2);

	return res;
}
DynamicArray* orderQuantityCtrl(Controller* c,char* name)
{
	DynamicArray* a = copyVector(c->repo->products);
	DynamicArray* a2 = searchString(a, name);
	orderByQuantity(a2);
	return a2;
	
}
DynamicArray* orderNameCtrl(Controller* c, char* name)
{
	DynamicArray* b = copyVector(c->repo->products);
	DynamicArray* a = searchString(b,name);
	printf("%d",getSize(a));
	orderByName(a);
	return a;

}
DynamicArray* displayByCategoryCtrl(Controller* c, char* name,Data d)
{
	DynamicArray* b = copyVector(c->repo->products);
	DynamicArray* a = searchStringCategory(b, name,d);
	printf("%d", getSize(a));
	orderByName(a);
	return a;

}
ProductRepo* getRepo(Controller* c)
{
	return c->repo;
}

int undo(Controller* c)
{
	if (isEmpty(c->undoStack))
	{
		return 0;
	}

	Operation* operation = pop(c->undoStack);

	push(c->redoStack, operation);
	if (strcmp(getOperationType(operation), "add") == 0)
	{
		Product* product = getProduct(operation);
		char name[50];
		strcpy(name, getName(product));
		deleteProduct(c->repo, name);
	}
	else if (strcmp(getOperationType(operation), "remove") == 0)
	{
		Product* product = getProduct(operation);
		add(c->repo, product);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Product* product = getProduct(operation);
		updateProduct(c->repo, product);
	}

	// the operation must be destroyed
	destroyOperation(operation);

	return 1;

}
int redo(Controller* c)
{
	if (isEmpty(c->redoStack))
	{
		return 0;
	}

	Operation* operation = pop(c->redoStack);

	if (strcmp(getOperationType(operation), "add") == 0)
	{
		Product* product = getProduct(operation);
		add(c->repo, product);
	}
	else if (strcmp(getOperationType(operation), "remove") == 0)
	{
		Product* product = getProduct(operation);
		char name[50];
		strcpy(name, getName(product));
		deleteProduct(c->repo, name);
	}
	else if (strcmp(getOperationType(operation), "update") == 0)
	{
		Product* product = getProduct(operation);
		updateProduct(c->repo, product);
	}

	// the operation must be destroyed
	destroyOperation(operation);

	return 1;

}

void test()
{
	OperationsStack* undoS = createStack();
	OperationsStack* redoS = createStack();
	ProductRepo* r = createRepo();
	Controller* c = createController(r, undoS,redoS);
	Data d;
	d.day = 1;
	d.month = 10;
	d.year = 2010;
	Product* p1 = createProduct("portocala", "fruct", 3, d);
	addProductCtrl(c, "portocala", "fruct", 3, d);
	assert(getRepoLength(c->repo) == 1);
	deleteProductCtrl(c, "portocala", "fruct", 3, d);

	assert(getRepoLength(c->repo) == 0);

}
void testsProductCtrl()
{
	test();
}