#include "DynamicArray.h"
#include "ProductRepository.h"
#include <crtdbg.h>
#include "OperationsStack.h"
#include "UI.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
int main()
{
	//testsDynamicArray();
	//testsProductRepo();
	//testsStack();
	//testsProductCtrl();

	ProductRepo* repo = createRepo();
	OperationsStack* undoStack = createStack();
	OperationsStack* redoStack = createStack();
	Controller* ctrl = createController(repo, undoStack,redoStack);

	Data dataC;
	dataC.day = 1;
	dataC.month = 2;
	dataC.year = 2019;

	addProductCtrl(ctrl, "mar", "fructe", 5, dataC);
	addProductCtrl(ctrl, "sunca", "carne", 3, dataC);
	addProductCtrl(ctrl, "chedar", "branza", 2, dataC);
	addProductCtrl(ctrl, "ketchup", "sos", 4, dataC);
	addProductCtrl(ctrl, "maioneza", "sos", 1, dataC);
	addProductCtrl(ctrl, "oua", "nush", 10, dataC);
	addProductCtrl(ctrl, "lapte", "lapte", 1, dataC);
	addProductCtrl(ctrl, "cake", "desert", 2, dataC);
	addProductCtrl(ctrl, "morcov", "legume", 3, dataC);
	addProductCtrl(ctrl, "rosie", "leguma", 4, dataC);


	UI* ui = createUI(ctrl);

	startUI(ui);

	destroyUI(ui);

	_CrtDumpMemoryLeaks();

	return 0;
}