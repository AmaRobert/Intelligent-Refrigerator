#pragma once
#include "Product.h"
#include "DynamicArray.h"
#include <string.h>
typedef struct
{
	Product* product;
	char* operationType;
}Operation;

Operation* createOperation(Product* p, char* operationType);
void destroyOperation(Operation* o);
Operation* copyOperation(Operation* o);
char* getOperationType(Operation* o);
Product* getProduct(Operation* o);




//-------------------------------------------
typedef struct
{
	Operation* operations[100];
	int length;
}OperationsStack;

OperationsStack* createStack();
void destroyStack(OperationsStack* s);
void push(OperationsStack* s, Operation* o);
Operation* pop(OperationsStack* s);
int isEmpty(OperationsStack* s);
int isFull(OperationsStack* s);

void testsStack();
