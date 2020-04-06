#pragma once
#include "ProductRepository.h"
#include "OperationsStack.h"
typedef struct
{
	ProductRepo* repo;
	OperationsStack* undoStack;
	OperationsStack* redoStack;
} Controller;


Controller* createController(ProductRepo* r, OperationsStack* undoS, OperationsStack* redoS);
void destroyController(Controller* c);

int addProductCtrl(Controller* c, char* name, char* category, int quantity, Data dataC);
int deleteProductCtrl(Controller* c, char* name);
int updateProductCtrl(Controller* c, char* name, char* category, int quantity, Data dataC);

ProductRepo* getRepo(Controller* c);

int undo(Controller* c);