
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"

#include "Vector.h"
#include "IntPoint.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);

bool IsInRange(int x, int y)
{
	return (abs(x) < (g_nClientWidth / 2)) && (abs(y) < (g_nClientHeight / 2));
}

void PutPixel(const IntPoint InPt)
{
	PutPixel(InPt.x, InPt.y);
}

void PutPixel(int x, int y)
{
	if (!IsInRange(x, y)) return;

	ULONG* dest = (ULONG*)g_pBits;
	DWORD offset = g_nClientWidth * g_nClientHeight / 2 + g_nClientWidth / 2 + x + g_nClientWidth * -y;
	*(dest + offset) = g_CurrentColor;
}

void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();


	static Vector3 rgb;
	rgb.X += 0.5f;
	rgb.Y += 1.0f;
	rgb.Z += 2.0f;

	rgb.X = fmodf(rgb.X,255.0f);
	rgb.Y = fmodf(rgb.Y, 255.0f);
	rgb.Z = fmodf(rgb.Z, 255.0f);

	// Draw
	SetColor(rgb.X, rgb.Y, rgb.Z);
	//PutPixel(0, 0);
	//Draw Circle wih radius 100
	Vector2 center(0.0f, 0.0f);
	float radius = 100.0f;
	

	static float degree = 0.0f;
	degree += 0.5f;
	degree = fmodf(degree, 360.0f);

	static float scale = 1.0f;
	scale += 0.5f;
	float scaleSin = sinf(Deg2Rad(scale)) + 1.0f;
	//scale = fmodf(scale, 2.0f);



	Matrix3 rotMat;
	rotMat.SetRotation(degree);
	
	Matrix3 scaleMat;
	scaleMat.SetScale(scaleSin, scaleSin);

	Matrix3 transMat;
	transMat.SetTranslation((sinf(Deg2Rad(degree)) + 1.0f) * 100.0f, 0.0f);

	Matrix3 TSR = transMat * scaleMat * rotMat;
	
	for (int x = -radius; x < radius; x++)
	{
		for (int y = -radius; y < radius; y++)
		{
			PutPixel(Vector3(x, y, 1) * TSR);
		}
	}


	// Buffer Swap 
	BufferSwap();
}
