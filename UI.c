#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "UI.h"

UI* createUI(Controller* c)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->ctrl = c;

	return ui;
}

void destroyUI(UI* ui)
{
	// first destroy the controller
	destroyController(ui->ctrl);
	// free the UI memory
	free(ui);
}

/*
	Prints the available menu for the problem
	Input: -
	Output: the menu is printed at the console
*/
void printMenu()
{
	printf("\n**********************************************************\n");
	printf("1 - add a product.\n");
	printf("2 - list all products.\n");
	printf("3 - delete a product. \n");
	printf("4 - update a product.\n");
	printf("5 - Search by name and order by quantity.\n");
	printf("6 - Search by name and order by name.\n");
	printf("7 - Display by category and below a date.\n");
	printf("8 - undo.\n");
	printf("9 - redo.\n");
	printf("0 - to exit.\n");
	printf("\n**********************************************************\n");
}

/*
	Verifies if the given command is valid (is either 1, 2, 3or 0)
	Input: command - integer
	Output: 1 - if the command is valid
	0 - otherwise
*/
int validCommand(int command)
{
	if (command >= 0 && command <= 9)
		return 1;
	return 0;
}

/*
	Reads an integer number from the keyboard. Asks for number while read errors encoutered.
	Input: the message to be displayed when asking the user for input.
	Returns the number.
*/
int readIntegerNumber(const char* message)
{
	char s[16];
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		scanf("%s", s);

		r = sscanf(s, "%d", &res);	// reads data from s and stores them as integer, if possible; returns 1 if successful
		flag = (r == 1);
		if (flag == 0)
			printf("Error reading number!\n");
	}
	return res;
}

/*
	Reads a string with spaces from the standard input.
	Input:	message - string, message to be shown to the user.
			maxStrSize - the maximum size for the string to be read
	Output: the string that was read.
*/
void readStringWithSpaces(const char* message, int maxStrSize, char str[])
{
	printf(message);
	fgets(str, maxStrSize, stdin);
	// the newline is also read so we must eliminate it from the string
	size_t size = strlen(str) - 1;
	if (str[size] == '\n')
		str[size] = '\0';
}

int addProductUI(UI* ui)
{
	// read the peoduct's data
	char name[50], category[50];
	int quantity,day,month,year;

	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Please input the name: ", 50, name);
	readStringWithSpaces("Please input the category: ", 50, category);
	printf("Please input the quantity: ");
	scanf("%d", &quantity);
	printf("Please input the day: ");
	scanf("%d", &day);
	printf("Please input the month: ");
	scanf("%d", &month);
	printf("Please input the year: ");
	scanf("%d", &year);
	Data d;
	d.day = day;
	d.month = month;
	d.year = year;
	return addProductCtrl(ui->ctrl, name, category,quantity,d);
}
int deleteProductUI(UI* ui)
{
	char name[50];
	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Please input the name: ", 50, name);
	return deleteProductCtrl(ui->ctrl, name);

}
int updateProductUI(UI* ui)
{
	// read the peoduct's data
	char name[50], category[50];
	int quantity, day, month, year;

	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Please input the name: ", 50, name);
	readStringWithSpaces("Please input the category: ", 50, category);
	printf("Please input the quantity: ");
	scanf("%d", &quantity);
	printf("Please input the day: ");
	scanf("%d", &day);
	printf("Please input the month: ");
	scanf("%d", &month);
	printf("Please input the year: ");
	scanf("%d", &year);
	Data d;
	d.day = day;
	d.month = month;
	d.year = year;
	return updateProductCtrl(ui->ctrl, name, category, quantity, d);
}
void orderQuantityUI(UI* ui)
{
	char name[50];

	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Please input the name: ", 50, name);

	DynamicArray*d = orderQuantityCtrl(ui->ctrl, name);
	int length = getSize(d);
	printf("%d", length);
	for (int i = 0; i < length; i++)
	{
		Product* product = d->arr[i];
		char* str = toString(product);
		printf("%d) %s", i, str);
		free(str);
	}
	destroyArray(d);
}

void orderByNameUI(UI* ui)
{
	char name[50];

	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Please input the name: ", 50, name);

	DynamicArray*d = orderNameCtrl(ui->ctrl, name);
	int length = getSize(d);
	printf("%d", length);
	for (int i = 0; i < length; i++)
	{
		Product* product = d->arr[i];
		char* str = toString(product);
		printf("%d) %s", i, str);
		free(str);
	}
	destroyArray(d);
	

}
void displayByCategory(UI* ui)
{
	char category[50];
	int day,month,year;

	fgetc(stdin); // read the newline, to prevent it from going further to fgets
	readStringWithSpaces("Please input the category: ", 50, category);
	printf("Please input the day: ");
	scanf("%d", &day);
	printf("Please input the month: ");
	scanf("%d", &month);
	printf("Please input the year: ");
	scanf("%d", &year);
	Data d;
	d.day = day;
	d.month = month;
	d.year = year;

	DynamicArray*dy = displayByCategoryCtrl(ui->ctrl, category,d);
	int length = getSize(dy);
	printf("%d", length);
	for (int i = 0; i < length; i++)
	{
		Product* product = dy->arr[i];
		char* str = toString(product);
		printf("%d) %s", i, str);
		free(str);
	}
	destroyArray(dy);


}

void listAllProducts(UI* ui)
{
	ProductRepo* repo = getRepo(ui->ctrl);
	int length = getRepoLength(repo);
	for (int i = 0; i < length; i++)
	{
		Product* product = getProductOnPos(repo,i);
		char* str = toString(product);
		printf("%d) %s", i, str);
		free(str);
	}
	
}

void startUI(UI* ui)
{
	while (1)
	{
		printMenu();
		int command = readIntegerNumber("Input command: ");
		while (validCommand(command) == 0)
		{
			printf("Please input a valid command!\n");
			command = readIntegerNumber("Input command: ");
		}
		if (command == 0)
			break;
		switch (command)
		{
		case 1:
		{
			int res = addProductUI(ui);
			if (res == 1)
				printf("Product successfully added.\n");
			else
				printf("Error! Product could not be added, as there is another product with the same symbol combination!\n");
			break;
		}
		case 2:
		{
			listAllProducts(ui);
			break;
		}
		case 3:
		{
			int res = deleteProductUI(ui);
			if (res == 1)
				printf("Product successfully deleted.\n");
			else
				printf("Error! Product could not be deleted!\n");
			break;
		}
		case 4:
		{
			int res = updateProductUI(ui);
			if (res == 1)
				printf("Product successfully updated.\n");
			else
				printf("Error! Product could not be updated!\n");
			break;
		}
		case 5:
		{
			orderQuantityUI(ui);
			break;
		}
		case 6:
		{
			orderByNameUI(ui);
			break;
		}
		case 7:
		{
			displayByCategory(ui);
			break;
		}
		case 8:
		{
			int res = undo(ui->ctrl);
			if (res == 1)
				printf("Undo was successful.\n");
			else
				printf("No more undos to be made.\n");
			break;
		}
		case 9:
		{	
			int res = redo(ui->ctrl);
			if (res == 1)
				printf("Redo was successful.\n");
			else
				printf("No more redos to be made.\n");
			break;

		}
		}
	}
}