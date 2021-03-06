#include "pch.h"
#include <iostream>
#include "Windows.h"
#include <cstdlib>
#include "CUESDK/include/CUESDK.h"

#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \
	on line %d\n", __FILE__, GetLastError(), api, __LINE__);}


bool toggleKey = false;
unsigned short globalDown = 10; // used for pull down
unsigned short globalOffset = 5; // randomness factor

class virtualMove {
private:
	// random int for cursor offset
	virtual int randOffset() {

		int offset = std::rand() % globalOffset;

		if (std::rand() % 2) {

			offset = 0 - offset;

		}
		return offset;
	}
public:
	// move cursor
	virtual void move() {
		if (toggleKey) {
			auto offsetY = randOffset();
			auto offsetX = randOffset();

			mouse_event(1, offsetX, globalDown + offsetY, 0, 0);
			Sleep(25);
		}
	}
};

class movement: public virtualMove {
private:
	// random int for cursor offset
	virtual int randOffset() {

		int offset = std::rand() % 5;

		if (std::rand() % 2) {

			offset = 0 - offset;

		}
		return offset;
	}
public:
	// move cursor
	virtual void move() {
		if (toggleKey) {
			auto offsetY = randOffset();
			auto offsetX = randOffset();

			mouse_event(1, offsetX, globalDown + offsetY, 0, 0);
			Sleep(25);
		}
	}
};

void setHeader() {

	puts("--------------------------------------------------");
	puts("-------WELCOME TO VALENCE'S LEGIT GAMESENSE-------");
	puts("--------------------------------------------------");
	puts("");
	puts("Press F1 to QUIT");
	puts("Press F2 to TOGGLE ON/OFF");
	puts("Press F3 to decrease RECOIL MANAGEMENT FACTOR (RMF)");
	puts("Press F4 to increase RECOIL MANAGEMENT FACTOR (RMF)");
	puts("Press F5 to decrease RANDOMNESS SEED (RS)");
	puts("Press F6 to increase RANDOMNESS SEED (RS)");
	puts("");
	puts("Current settings");
	puts("----------------");
	std::cout << "RMF: " << globalDown << std::endl;
	std::cout << "RS: " << globalOffset << std::endl;
	if (toggleKey) {
		std::cout << "Recoil management is ENABLED" << std::endl;
	}
	else {
		std::cout << "Recoil management is DISABLED" << std::endl;
	}

}

void refresh() {

	system("CLS");
	setHeader();

}

void getCtrlInput() {

	if (GetAsyncKeyState(VK_F1)) // close application
		exit(EXIT_SUCCESS);

	if (GetAsyncKeyState(VK_F2)) { // toggle on/off
		toggleKey = !toggleKey;
		refresh();
		Sleep(250);
	}

	if (GetAsyncKeyState(VK_F3)) { // decrement globalDown on VK_F3
		
		globalDown--;
		refresh();
		Sleep(250);
	}

	if (GetAsyncKeyState(VK_F4)) { // increment globalDown on VK_F4

		globalDown++;
		refresh();
		Sleep(250);

	}

	if (GetAsyncKeyState(VK_F5)) { // decrement offset on VK_F5

		globalOffset--;
		refresh();
		Sleep(250);
	}

	if (GetAsyncKeyState(VK_F6)) { // increment offset on VK_F5

		globalOffset++;
		refresh();
		Sleep(250);
	}
}

int main(int argc, char *argv[]) {

	setHeader();

	while (1) { // keep mouse hook alive

		virtualMove* mptr;
		movement _mptr;
		mptr = &_mptr;

		getCtrlInput();

		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // move function activate on left mouse down
			mptr->move();

	}

	return 0;
}