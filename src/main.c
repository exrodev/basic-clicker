#include "util.h"

#include <Windows.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

#define MIN_CPS 		15
#define MAX_CPS 		18

#define KEYBIND_TOGGLE 	VK_INSERT	// Toggle the auto-clicker
#define KEYBIND_HIDE	VK_DELETE	// Toggle the terminal's visibility

int main() {
	// Setup rand()
	srand(time(NULL));

	bool window_visible = true;
	bool clicker_enabled = false;
	bool first_click = true;
	HWND current_window;
	HWND console = GetConsoleWindow();
	POINT pt;

	printf("Toggle Clicker: %s\n", keybind_strings[KEYBIND_TOGGLE]);
	printf("Hide Window: %s\n", keybind_strings[KEYBIND_HIDE]);
	printf("%s", "-------------------------");
	printf("Clicker: %s\n", (clicker_enabled ? "true" : "false"));

	while (true) {
		if (GetAsyncKeyState(KEYBIND_TOGGLE)) {
			clicker_enabled = !clicker_enabled;
			printf("Clicker: %s\n", (clicker_enabled ? "true" : "false"));
			Sleep(150);
		}

		if (GetAsyncKeyState(KEYBIND_HIDE)) {
			window_visible = !window_visible;
			ShowWindow(console, window_visible);
			Sleep(150);
		}

		if (clicker_enabled) {
			while (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
				current_window = GetForegroundWindow();

				GetCursorPos(&pt);

				// Make sure we are not clicking on the console
				if (current_window == console) {
					continue;
				}

				// Make sure we are on the client area of the window
				if (SendMessage(current_window, WM_NCHITTEST, 0, MAKELPARAM(pt.x, pt.y)) != HTCLIENT) {
					continue;
				}

				if (!first_click) {
					// Do down click
					SendMessage(current_window, WM_LBUTTONDOWN, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));
				}

				// Sleep
				Sleep(gen_num(500 / MAX_CPS, 500 / MIN_CPS));

				// Do up click
				SendMessage(current_window, WM_LBUTTONUP, MK_LBUTTON, MAKELPARAM(pt.x, pt.y));

				// Sleep again
				Sleep(gen_num(500 / MAX_CPS, 500 / MIN_CPS));

				first_click = false;
			}
		}

		Sleep(1);
	}

	return 0;
}