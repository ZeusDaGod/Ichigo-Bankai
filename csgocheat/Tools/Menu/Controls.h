#pragma once
#include "../../stdafx.h"

extern CColor LightGray;
extern CColor Gray;
extern CColor DarkGray;
extern CColor MainColor;
extern CColor MiddleGray;
extern CColor Black;

inline void DrawRect(int x1, int y1, int x2, int y2, CColor clr)
{
	Interfaces.pSurface->DrawSetColor1(clr);
	Interfaces.pSurface->DrawFilledRect(x1, y1, x2, y2);
}

inline void DrawFade(int x1, int y1, int x2, int y2, int alpha, int alpha2, CColor clr, bool horiz = false)
{
	Interfaces.pSurface->DrawSetColor1(clr);
	Interfaces.pSurface->DrawFilledRectFade(x1, y1, x2, y2, alpha, alpha2, horiz);
}

inline void DrawLine(int x1, int y1, int x2, int y2, CColor clr)
{
	int width = 0;
	int height = 0;
	Interfaces.pEngine->GetScreenSize(width, height);
	if (!(x1 < width && x1 > 0 && y1 < height && y1 > 0) || !(x2 < width && x2 > 0 && y2 < height && y2 > 0))
		return;
	Interfaces.pSurface->DrawSetColor1(clr);
	Interfaces.pSurface->DrawLine(x1, y1, x2, y2);
}

inline void DrawOutlinedRect(int x1, int y1, int x2, int y2, CColor clr)
{
	Interfaces.pSurface->DrawSetColor1(clr);
	Interfaces.pSurface->DrawOutlinedRect(x1, y1, x2, y2);
}

inline void DrawCircle(int x, int y, float Radius, CColor Color)
{
	int Points = Radius * 2;
	Vertex_t* Circle = new Vertex_t[Points];

	for (int i = 0; i < Points; ++i)
	{
		float Theta = 2 * PI * i / Points;
		Circle[i].Init(x + cosf(Theta) * Radius, y + sinf(Theta) * Radius);
	}

	static int Texture = NULL;

	if (!Texture)
		Texture = Interfaces.pSurface->CreateNewTextureID(true);

	unsigned char buffer[4] = { Color._color[0], Color._color[1], Color._color[2], Color._color[3] };

	Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1);
	Interfaces.pSurface->DrawSetTexture(Texture);
	Interfaces.pSurface->DrawSetColor1(Color);
	Interfaces.pSurface->DrawTexturedPolygon(Points, Circle);
	//delete[]Circle;
}

inline bool CheckCirlce(int MouseX, int MouseY, int x, int y, float Radius)
{
	if (24 >= sqrt(pow(MouseX - x, 2) + pow(MouseY - y, 2)))
	{
		return true;
	}
	return true;
}

inline RECT GetTextSize(DWORD font, const char* text)
{
	char Buffer[1024] = { '\0' };

	/* set up varargs*/
	va_list Args;

	va_start(Args, text);
	vsprintf_s(Buffer, text, Args);
	va_end(Args);

	size_t Size = strlen(Buffer) + 1;
	wchar_t* WideBuffer = new wchar_t[Size];

	mbstowcs_s(nullptr, WideBuffer, Size, Buffer, Size - 1);

	RECT rect;
	int x, y;
	Interfaces.pSurface->GetTextSize(font, WideBuffer, x, y);
	rect.left = x;
	rect.bottom = y;
	rect.right = x;
	return rect;
}

inline RECT GetTextSize1(DWORD font, const wchar_t* text)
{
	RECT rect;
	int x, y;
	Interfaces.pSurface->GetTextSize(font, text, x, y);
	rect.left = x;
	rect.bottom = y;
	rect.right = x;
	return rect;
}

inline bool IsMousePressed()
{
	return (GetAsyncKeyState(0x01));
}

inline bool IsMousePressedRight()
{
	return (GetAsyncKeyState(0x02));
}


