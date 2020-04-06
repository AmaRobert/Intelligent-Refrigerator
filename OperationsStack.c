#pragma once
#include "OperationsStack.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

Operation* createOperation(Product* p, char* operationType)
{
	Operation* o = (Operation*)malloc(sizeof(Operation));
	o->product = copyProduct(p);

	if (operationType != NULL)
	{
		o->operationType = (char*)malloc(sizeof(char) * (strlen(operationType) + 1));
		strcpy(o->operationType, operationType);
	}
	else
			o->operationType = NULL;
	return o;
}

void destroyOperation(Operation* o)
{
	if (o == NULL)
		return;

	// first destroy the product
	destroyProduct(o->product); // POSIBIL SA FI GRESIT AICI
	// then the operationType
	free(o->operationType);
	// then free the operation
	free(o);
}

Operation* copyOperation(Operation * o)
{
	if (o == NULL)
		return NULL;

	Operation* newOperation = createOperation(getProduct(o), getOperationType(o));
	return newOperation;
}

char* getOperationType(Operation* o)
{
	return o->operationType;
}

Product* getProduct(Operation* o)
{
	return o->product;
}

OperationsStack* createStack()
{
	OperationsStack* s = (OperationsStack*)malloc(sizeof(OperationsStack));
	s->length = 0;

	return s;
}

void destroyStack(OperationsStack* s)
{
	if (s == NULL)
		return;

	// first deallocate memory of operations (this is allocated when a new operation is pushed onto the stack)
	for (int i = 1; i < s->length; i++)
		destroyOperation(s->operations[i]);

	// then free the stack
	free(s);
}

void push(OperationsStack* s, Operation* o)
{
	if (o == NULL)
		return;
	if (s == NULL)
		return;
	s->length++;
	int i = s->length;
	s->operations[i] = copyOperation(o);
}

Operation* pop(OperationsStack* s)
{
	if (s == NULL)
		return;
	int i = s->length;
	s->length--;
	return s->operations[i];
}

int isEmpty(OperationsStack* s)
{
	return (s->length == 0);
}

int isFull(OperationsStack* s)
{
	return s->length == 100;
}


// Tests
void testsStack()
{
	OperationsStack* s = createStack();
	Data d;
	d.day = 1;
	d.month = 10;
	d.year = 2010;
	Product* p1 = createProduct("lapte", "nush", 2,d);
	Product* p2 = createProduct("mar", "fruct", 3,d);
	Operation* o1 = createOperation(p1, "add");
	Operation* o2 = createOperation(p2, "add");
	Operation* o3 = createOperation(p1, "remove");

	// the Products may be destroyed, as the operations contain copies of these Products
	destroyProduct(p1);
	destroyProduct(p2);

	push(s, o1);
	assert(s->length == 1);
	push(s, o2);
	assert(s->length == 2);
	push(s, o3);
	// the operations may be destroyed, as the stack contains copies of these operations
	destroyOperation(o1);
	destroyOperation(o2);
	destroyOperation(o3);

	assert(isFull(s) == 0);
	assert(isEmpty(s) == 0);
	assert(s->length == 3);
	Operation* o = pop(s);
	printf(o->operationType);
	assert(strcmp(o->operationType, "remove") == 0);
	// after each pop, the operations must be destroyed
	destroyOperation(o);

	o = pop(s);
	assert(strcmp(o->operationType, "add") == 0);
	destroyOperation(o);

	o = pop(s);
	assert(strcmp(o->operationType, "add") == 0);
	destroyOperation(o);

	assert(isEmpty(s) == 1);

	// destroy the stack
	destroyStack(s);
}