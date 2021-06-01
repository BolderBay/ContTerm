#include "Terminal.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include "windows.h"
#include <regex>

void uploadTerminal() {
	int count = 0;
	char imput = ' ';
	cout << "Available terminals: \n";
	WIN32_FIND_DATAW wfd;

	HANDLE const hFind = FindFirstFileW(L"F:\\*", &wfd);
	setlocale(LC_ALL, "");

	if (INVALID_HANDLE_VALUE != hFind)
	{
		do
		{
			wstring ws(&wfd.cFileName[0]);
			string str(ws.begin(), ws.end());
			if (str.rfind("file", 0) == 0) { 
				count++;
				cout << count << ") Number ";
				regex target1("(file)+");
				regex target2("(.dat)+");
				string str2 = regex_replace(str, target1, "");
				str = regex_replace(str2, target2, "");
				cout << str << endl; 
			}
		} while (NULL != FindNextFileW(hFind, &wfd));

		FindClose(hFind);
	}
	cout << "\n0) Back\n-> ";
}

void toNewTerminal(Terminal &terminal) {						//добавить првоерки
	unsigned int input;
	system("cls");
	cout << "Terminal " << terminal.getNum() << endl;
	cout << "1) Add warehouse\n";
	cout << "2) List of warehouse\n";
	cout << "3) Resize Warehouse\n";
	cout << "4) Delete warehouse\n";
	cout << "5) Save terminal to file\n";

	cout << "\n0) Back\n-> ";
	cin >> input;

	switch (input)
	{
	case 1:
		unsigned int num;
		unsigned int l;
		unsigned int w;
		unsigned int h;
		float temp;
		cout << "Enter warehouse number, length, width, height and temperature (num, l, w, h, t):\n";
		cin >> num >> l >> w >> h >> temp;
		try { 
			Warehouse ware(l, w, h, temp); 
			terminal.addWarehouse(num, ware);
			cout << "Warehouse created successfully\n";
			cout << "\n0) Back\n-> ";
			cin >> input;
			toNewTerminal(terminal);
		}
		catch (std::exception& error) { cout << error.what(); }
		break;
	case 2:
		cout << "Enter the warehouse number to display information or make changes\n";
		terminal.getInformation();
		cout << "\n0) Back\n-> ";
		cin >> input;
		if (input == 0) { toNewTerminal(terminal); }
		else {
			try {
				string t;
				std::string co;
				unsigned int n;
				unsigned int l;
				unsigned int w;
				unsigned int h;
				float c;
				float m;
				float mm;
				float mt;
				unsigned int warehousenum = input;
				char si;
				terminal.getInformWare(input);
				cout << "1) Add container with position\n";
				cout << "2) Add container automatically\n";
				cout << "3) Rotate container\n";
				cout << "4) Move container\n";
				cout << "5) Remove container\n";
				cout << "6) Change warehouse size\n";
				cout << "7) Show information about container\n";
				cout << "8) Show floor plan\n";
 
				cout << "\n0) Back\n-> ";
				cin >> input;

				switch (input)
				{
				case 1:
					cout << "Enter the container type (C, CC, CF, CFC) and its characteristics (comp,num,len,wid,hei,cos,mass) + temp/maxmaxx for CC,CF,CFC:\n";
					cin >> t;
					if (t == "C") { 
						try {
							cin >> co >> n >> l >> w >> h >> c >> m;
							cout << "Enter coordinates (x,y,z,orientation): \n";
							unsigned int x;
							unsigned int y;
							unsigned int z;
							char orient;
							cin >> x >> y >> z >> orient;
							Container cont(co, n, l, w, h, c, m);
							Coordinatios pos(x, y, z, orient);
							terminal.addContainer(warehousenum,cont, pos);
							cout << "Container added successfully\n";
							cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
						catch (std::exception& error) { 
							cout << error.what(); cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
					}
					if (t == "CC") {
						try {
							cin >> co >> n >> l >> w >> h >> c >> m >> mt;
							cout << "Enter coordinates (x,y,z,orientation): \n";
							unsigned int x;
							unsigned int y;
							unsigned int z;
							char orient;
							cin >> x >> y >> z >> orient;
							ContainerCold cont(co, n, l, w, h, c, m, mt);
							Coordinatios pos(x, y, z, orient);
							terminal.addContainer(warehousenum, cont, pos);
							cout << "Container added successfully\n";
							cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
						catch (std::exception& error) {
							cout << error.what(); cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
					}
					if (t == "CF") {
						try {
							cin >> co >> n >> l >> w >> h >> c >> m >> mm;
							cout << "Enter coordinates (x,y,z,orientation): \n";
							unsigned int x;
							unsigned int y;
							unsigned int z;
							char orient;
							cin >> x >> y >> z >> orient;
							ContainerFragile cont(co, n, l, w, h, c, m, mm);
							Coordinatios pos(x, y, z, orient);
							terminal.addContainer(warehousenum, cont, pos);
							cout << "Container added successfully\n";
							cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
						catch (std::exception& error) {
							cout << error.what(); cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
					}
					if (t == "CFC") {
						try {
							cin >> co >> n >> l >> w >> h >> c >> m >> mt >> mm;
							cout << "Enter coordinates (x,y,z,orientation): \n";
							unsigned int x;
							unsigned int y;
							unsigned int z;
							char orient;
							cin >> x >> y >> z >> orient;
							ContainerFC cont(co, n, l, w, h, c, m, mt, mm);
							Coordinatios pos(x, y, z, orient);
							terminal.addContainer(warehousenum, cont, pos);
							cout << "Container added successfully\n";
							cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
						catch (std::exception& error) {
							cout << error.what(); cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
					}
					cout << "Wrong type\n";
					cout << "\n0) Back\n-> ";
					cin >> input;
					toNewTerminal(terminal);
					break;
				case 2:
					cout << "Enter the container type (C, CC, CF, CFC) and its characteristics (comp,num,len,wid,hei,cos,mass) + temp/maxmaxx for CC,CF,CFC:\n";
					cin >> t;
					if (t == "C") {
						try {
							cin >> co >> n >> l >> w >> h >> c >> m;
							Container cont(co, n, l, w, h, c, m);
							terminal.autoAddContainer(warehousenum, cont);
							cout << "Container added successfully\n";
							cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
						catch (std::exception& error) {
							cout << error.what(); cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
					}
					if (t == "CC") {
						try {
							cin >> co >> n >> l >> w >> h >> c >> m >> mt;
							ContainerCold cont(co, n, l, w, h, c, m, mt);
							terminal.autoAddContainer(warehousenum, cont);
							cout << "Container added successfully\n";
							cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
						catch (std::exception& error) {
							cout << error.what(); cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
					}
					if (t == "CF") {
						try {
							cin >> co >> n >> l >> w >> h >> c >> m >> mm;
							ContainerFragile cont(co, n, l, w, h, c, m, mm);
							terminal.autoAddContainer(warehousenum, cont);
							cout << "Container added successfully\n";
							cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
						catch (std::exception& error) {
							cout << error.what(); cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
					}
					if (t == "CFC") {
						try {
							cin >> co >> n >> l >> w >> h >> c >> m >> mt >> mm;
							ContainerFC cont(co, n, l, w, h, c, m, mt, mm);
							terminal.autoAddContainer(warehousenum, cont);
							cout << "Container added successfully\n";
							cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
						catch (std::exception& error) {
							cout << error.what(); cout << "\n0) Back\n-> ";
							cin >> input;
							toNewTerminal(terminal);
						}
					}
					cout << "Wrong type\n";
					cout << "\n0) Back\n-> ";
					toNewTerminal(terminal);
				case 3:
					cout << "Enter container number and turn side:\n";
					cin >> n >> si;
					try{ 
						terminal.rotCont(warehousenum, n, si);
						cout << "Container rotated successfully\n";
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					catch (std::exception& error) {
						cout << error.what();
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					break;
				case 4:
					cout << "Enter the container number and coordinates (x,y,z,orientation)\n";
					unsigned int x;
					unsigned int y;
					unsigned int z;
					char orient;
					cin >> n >> x >> y >> z >> orient;
					try {
						Coordinatios coord(x, y, z, orient);
						terminal.moveCont(warehousenum, n, coord);
						cout << "Container moved successfully\n";
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					catch (std::exception& error) {
						cout << error.what();
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					break;
				case 5:
					cout << "Enter the container number to be removed\n";
					cin >> n;
					try {
						terminal.delCont(warehousenum, n);
						cout << "Container deleted successfully\n";
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					catch (std::exception& error) {
						cout << error.what();
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					break;
				case 6:
					cout << "Enter the number and new dimensions of the warehouse (l,w,h):\n";
					cin >> n >> l >> w >> h;
					try {
						terminal.resizeWarehouse(n, l, w, h);
						cout << "Warehouse size changed successfully\n";
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					catch (std::exception& error) {
						cout << error.what();
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					break;
				case 7:
					cout << "Enter the container number:\n";
					cin >> n;
					try {
						terminal.getInformCont(warehousenum, n);
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					catch (std::exception& error) {
						cout << error.what();
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					break;
				case 8:
					cout << "Enter the floor number:\n";
					cin >> n;
					try {
						terminal.showSchema(warehousenum, n);
					}
					catch (std::exception& error) {
						cout << error.what();
						cout << "\n0) Back\n-> ";
						cin >> input;
						toNewTerminal(terminal);
					}
					break;
				default:
					break;

				}
			}
			catch (std::exception& error) { std::cout << error.what(); }
		}
		break;
	case 3:
		cout << "Enter the number and new dimensions of the warehouse (l,w,h):\n";
		cin >> num >> l >> w >> h;
		try {
			terminal.resizeWarehouse(num, l, w, h);
			cout << "Warehouse size changed successfully\n";
			cout << "\n0) Back\n-> ";
			cin >> input;
			toNewTerminal(terminal);
		}
		catch (std::exception& error) {
			cout << error.what();
			cout << "\n0) Back\n-> ";
			cin >> input;
			toNewTerminal(terminal);
		}
		break;
	case 4:
		cout << "Enter the warehouse number\n";
		cin >> num;
		try {
			terminal.delWarehouse(num);
			cout << "Warehouse successfully deleted\n";
			cout << "\n0) Back\n-> ";
			cin >> input;
			toNewTerminal(terminal);
		}
		catch (std::exception& error) {
			cout << error.what();
			cout << "\n0) Back\n-> ";
			cin >> input;
			toNewTerminal(terminal);
		}
		break;
	case 5:

		break;
	default: cout << "Wrong operation";
		cout << "\n0) Back\n-> ";
		cin >> input;
		toNewTerminal(terminal);
		break;
	}
}


int main() {
	system("cls");

	Container container1("US", 322, 2, 1, 1, 500, 100);
	Container container2("EU", 226, 2, 1, 1, 500, 100);
	ContainerFragile container3("RU", 431, 2, 2, 1, 500, 100, 20);
	Container test("test", 555, 1, 2, 1, 500, 100);

	Coordinatios pos1(0, 0, 0, FRONT);
	Coordinatios pos2(1, 2, 0, SIDE);
	Coordinatios pos3(3, 3, 0, FRONT);
	Coordinatios pos4(0, 0, 1, FRONT);
	
	Coordinatios testpos(5, 0, 1, FRONT);

	Warehouse sklad;

	sklad.addContainer(container1, pos1);
	sklad.addContainer(container2, pos2);
	sklad.addContainer(container3, pos3);


	Terminal terminal;

	terminal.addWarehouse(1,sklad);
	terminal.save();

	char input = ' ';
	cout << "1 - Upload terminal file\n";
	cout << "2 - Create a new terminal\n";
	cout << "3 - Exit\n-> ";
	cin >> input;
	switch (input) {
	case '1':		
		uploadTerminal();
		cin >> input;
		terminal.load(input);
		toNewTerminal(terminal);
		system("cls");
		delete &terminal;
		main();
	case '2':
		unsigned int number;
		cout << "Enter terminal number: ";
		cin >> number;
		terminal.setNum(number);
		toNewTerminal(terminal);
		main();
		break;
	case '3': return 0;
		break;
	default: cout << "Wrong operation";
		break;
	}

}
