
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

	// Draw
	SetColor(255, 0, 0);
	//PutPixel(0, 0);
	//Draw Circle wih radius 100
	Vector2 center(0.0f, 0.0f);
	float radius = 100.0f;
	
	//Matrix2 scaleMat;
	//scaleMat.SetScale(2.0f, 0.5f);

	//Matrix2 rotMat;
	//rotMat.SetRotation(30.0f);

	//Matrix2 SRMat = scaleMat * rotMat;
	//Matrix2 RSMat = rotMat * scaleMat;

	//for (int x = -radius; x < radius; x++)
	//{
	//	for (int y = 0; y < radius; y++)
	//	{
	//		IntPoint pt(x, y);
	//		Vector2 ptVec = pt.ToVector2();
	//		if (Vector2::DistSquared(Vector2(0, 0), ptVec) <= radius * radius)
	//		{		
	//			IntPoint SRPt(ptVec * SRMat);
	//			IntPoint RSPt(ptVec * RSMat);
	//			PutPixel(RSPt);
	//		}
	//	}
	//}

	//type 1
	//for (int x = 0; x < 360; x++)
	//{
	//	IntPoint pt(radius, 0);
	//	
	//	Matrix2 rotMat;
	//	rotMat.SetRotation((float) x);
	//	IntPoint rotpt(pt.ToVector2() * rotMat);
	//	PutPixel(rotpt);
	//}

	//Matrix2 scaleMat;
	//scaleMat.SetScale(0.95f,0.95f);

	////type2
	//for (int x = -radius; x < radius; x++)
	//{
	//	for (int y = -radius; y < radius; y++)
	//	{
	//		IntPoint pt(x, y);
	//		Vector2 ptVec = pt.ToVector2();
	//		if (Vector2::DistSquared(Vector2(0, 0), ptVec) <= radius * radius)
	//		{		
	//			SetColor(255, 0, 0);
	//			PutPixel(pt);
	//			
	//			IntPoint SPt(ptVec * scaleMat);
	//			SetColor(32, 128, 255);
	//			PutPixel(SPt);
	//		}
	//	}
	//}

	static float degree = 0.0f;
	degree += 0.1f;
	degree = fmodf(degree, 360.0f);

	Matrix2 rotMat;
	rotMat.SetRotation(degree);

	for (int x = -radius; x < radius; x++)
	{
		for (int y = -radius; y < radius; y++)
		{
			PutPixel(Vector2(x, y) * rotMat);
		}
	}



	// Buffer Swap 
	BufferSwap();
}
