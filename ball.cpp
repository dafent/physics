#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include "resource.h"

int x, dx;

int WINAPI fn (HWND hwnd, int cmd, WPARAM wp, LPARAM lp)
{
switch (cmd)
{
case WM_TIMER:
{
RECT rt;
GetClientRect (hwnd, &rt);
int w = rt.right;
int h = rt.bottom;
x+=dx;
if (x >= w) dx = -abs(dx);
if (x <= 0) dx = abs (dx);
InvalidateRect (hwnd, NULL, false);
return 1;
}
case WM_INITDIALOG:
// editable and static elements
x = 50; dx = 1;
SetDlgItemInt (hwnd, IDC_R, 50, true);
// buttons
CheckDlgButton (hwnd, IDC_CHECK2, BST_CHECKED);
return 1;
case WM_CLOSE:
EndDialog (hwnd, 2);
return 1;
case WM_SIZE:
InvalidateRect (hwnd, NULL, true);
return 1;
case WM_COMMAND:
switch (LOWORD (wp))
{
case IDOK:
EndDialog (hwnd, 1);
return 1;
case IDC_START:
x = 0;
dx = 5;
SetTimer (hwnd, 99, 25, NULL);
return 1;
case IDC_STOP:
KillTimer (hwnd, 99);
InvalidateRect (hwnd, NULL, true);
return 1;
}
return 0;
case WM_PAINT:
{
PAINTSTRUCT ps;
HDC hdc = BeginPaint (hwnd, &ps);

		RECT rt;
		GetClientRect (hwnd, &rt);
		int w = rt.right; int h = rt.bottom; // lenght and hight of working space (window)

		HBRUSH b1, b2, b0;
		b1 = CreateSolidBrush (RGB (255, 0, 0)); //brushes
		b2 = CreateSolidBrush (RGB (0, 255, 0));

		HPEN p1, p2, p0;
		p1 = CreatePen (PS_SOLID, 2, RGB (0, 0, 255)); // feathers
		p2 = CreatePen (PS_SOLID, 4, RGB (0, 0, 0));

		p0 = (HPEN)SelectObject (hdc, p1); // working pen
		b0 = (HBRUSH)SelectObject (hdc, b1); // working feather

		if (IsDlgButtonChecked (hwnd, IDC_CHECK1)) // button "colour"
		{
			SelectObject (hdc, b2);
		}
		if (IsDlgButtonChecked (hwnd, IDC_CHECK2)) // button "oval"
		{
			int R = GetDlgItemInt (hwnd, IDC_R, NULL, false);
			Ellipse (hdc, x-R, h/2-R, x+R, h/2+R); // oval
		}

		SelectObject (hdc, p1);
		MoveToEx (hdc, 0, 40, NULL); // feather is at the line's begginig
		LineTo (hdc, w, 40);         // line
		TextOut (hdc, 110, 13,"Ball moving...", 13);

		SelectObject (hdc, p0); // return old feather and pen
		SelectObject (hdc, b0);

		DeleteObject (p1);
		DeleteObject (p2);
		DeleteObject (p1);
		DeleteObject (p2);

		EndPaint (hwnd, &ps);
	}
	return 1;
}
return 0;

}

int WINAPI WinMain (HINSTANCE hi, HINSTANCE, LPSTR, int)
{
return DialogBox (hi, MAKEINTRESOURCE (SIMPLE), NULL, (DLGPROC) fn);
getch ();
}
