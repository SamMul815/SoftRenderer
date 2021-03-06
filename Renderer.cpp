
#include "stdafx.h"
#include "SoftRenderer.h"
#include "GDIHelper.h"
#include "Renderer.h"
#include "Vertex.h"
#include "Vector.h"
#include "IntPoint.h"
#include "QuadMesh.h"
#include "GameObject.h"
#include "Transform.h"
#include "Mesh.h"

bool IsInRange(int x, int y);
void PutPixel(int x, int y);
void DrawTriangle(const Vertex &p1, const Vertex &p2, const Vertex &p3);
void DrawTriangle(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3);

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

void DrawLine(const Vector3 &Start, const Vector3 &end)
{

	float length = Vector3::Dist(end, Start);
	float inc = 1.0f / length;
	float nLength = (int)(length+1);

	for (int i = 0; i <= nLength; i++)
	{
		float t = inc * i;
		if (t >= length) t = 1.0f;
		Vector3 pt = Start * (1.0f - t) + end * t;
		// l = (1-t)p + tQ p -> Q
		PutPixel(pt);
	}	
}

void DrawTriangle(const Vertex &v1, const Vertex &v2, const Vertex &v3)
{
	Vector2 minPos = Vector2(INFINITY, INFINITY);
	Vector2 maxPos = Vector2(-INFINITY, -INFINITY);

	if (v1.position.X < minPos.x) minPos.x = v1.position.X;
	if (v1.position.Y < minPos.y) minPos.y = v1.position.Y;
	if (v1.position.X > maxPos.x) maxPos.x = v1.position.X;
	if (v1.position.Y > maxPos.y) maxPos.y = v1.position.Y;

	if (v2.position.X < minPos.x) minPos.x = v2.position.X;
	if (v2.position.Y < minPos.y) minPos.y = v2.position.Y;
	if (v2.position.X > maxPos.x) maxPos.x = v2.position.X;
	if (v2.position.Y > maxPos.y) maxPos.y = v2.position.Y;

	if (v3.position.X < minPos.x) minPos.x = v3.position.X;
	if (v3.position.Y < minPos.y) minPos.y = v3.position.Y;
	if (v3.position.X > maxPos.x) maxPos.x = v3.position.X;
	if (v3.position.Y > maxPos.y) maxPos.y = v3.position.Y;

	Vector3 u = v2.position - v1.position;
	Vector3 v = v3.position - v1.position;

	float dotUU = Vector3::Dot(u, u);
	float dotUV = Vector3::Dot(u, v);
	float dotVV = Vector3::Dot(v, v);
	float invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

	IntPoint minpt(minPos);
	IntPoint maxPt(maxPos);

	for (int x = minpt.x; x < maxPt.x; x++)
	{
		for (int y = minpt.y; y < maxPt.y; y++)
		{
			IntPoint pt(x, y);
			Vector3 w = pt.ToVector3() - v1.position;
			float dotUW = Vector3::Dot(u, w);
			float dotVW = Vector3::Dot(v, w);
			float s = (dotVV * dotUW - dotUV * dotVW) * invDenom;
			float t = (dotUU * dotVW - dotUV * dotUW) * invDenom;
			if (s >= 0 && t >= 0 && ((s + t) <= 1))
			{
				BYTE RV1 = GetRValue(v1.color);
				BYTE RV2 = GetRValue(v2.color);
				BYTE RV3 = GetRValue(v3.color);

				BYTE GV1 = GetGValue(v1.color);
				BYTE GV2 = GetGValue(v2.color);
				BYTE GV3 = GetGValue(v3.color);

				BYTE BV1 = GetBValue(v1.color);
				BYTE BV2 = GetBValue(v2.color);
				BYTE BV3 = GetBValue(v3.color);

				BYTE FinalR = (BYTE)(RV1 * (1 - s - t) + RV2 * x + RV3 * t);
				BYTE FinalG = (BYTE)(GV1 * (1 - s - t) + GV2 * x + GV3 * t);
				BYTE FinalB = (BYTE)(BV1 * (1 - s - t) + BV2 * x + BV3 * t);

				SetColor(FinalR, FinalG, FinalB);

				PutPixel(pt);
			}
		}
	}
}

void DrawTriangle(const Vector3 &p1, const Vector3 &p2, const Vector3 &p3)
{
	Vector2 minPos = Vector2(INFINITY, INFINITY);
	Vector2 maxPos = Vector2(-INFINITY, -INFINITY);

	if (p1.X < minPos.x) minPos.x = p1.X;
	if (p1.Y < minPos.y) minPos.y = p1.Y;
	if (p1.X > maxPos.x) maxPos.x = p1.X;
	if (p1.Y > maxPos.y) maxPos.y = p1.Y;

	if (p2.X < minPos.x) minPos.x = p2.X;
	if (p2.Y < minPos.y) minPos.y = p2.Y;
	if (p2.X > maxPos.x) maxPos.x = p2.X;
	if (p2.Y > maxPos.y) maxPos.y = p2.Y;

	if (p3.X < minPos.x) minPos.x = p3.X;
	if (p3.Y < minPos.y) minPos.y = p3.Y;
	if (p3.X > maxPos.x) maxPos.x = p3.X;
	if (p3.Y > maxPos.y) maxPos.y = p3.Y;

	Vector3 u = p2 - p1;
	Vector3 v = p3 - p1;

	float dotUU = Vector3::Dot(u, u);
	float dotUV = Vector3::Dot(u, v);
	float dotVV = Vector3::Dot(v, v);
	float invDenom = 1.0f / (dotUU * dotVV - dotUV * dotUV);

	IntPoint minpt(minPos);
	IntPoint maxPt(maxPos);

	for (int x = minpt.x; x < maxPt.x; x++)
	{
		for (int y = minpt.y; y < maxPt.y; y++)
		{
			IntPoint pt(x, y);
			Vector3 w = pt.ToVector3() - p1;
			float dotUW = Vector3::Dot(u, w);
			float dotVW = Vector3::Dot(v, w);
			float s = (dotVV * dotUW - dotUV * dotVW) * invDenom;
			float t = (dotUU * dotVW - dotUV * dotUW) * invDenom;
			if (s >= 0 && t >= 0 && ((s + t) <= 1))
			{
				PutPixel(pt);
			}
		}
	}
}

void DrawTriangle(const Triangle &triangle)
{
	IntPoint minPt(triangle.minPos);
	IntPoint maxPt(triangle.maxPos);

	for (int x = minPt.x; x < maxPt.x; x++)
	{
		for (int y = minPt.y; y < maxPt.y; y++)
		{
			IntPoint pt(x, y);
			Vector2 baryValues = triangle.GetBaryCentricCoordinate(pt.ToVector3());
			if (baryValues.x >= 0 && baryValues.y >= 0 && ((baryValues.x + baryValues.y) <= 1))
			{
				ULONG finalColor = RGB32(255, 0, 0);
				if (g_Texture->IsLoaded())
				{
					finalColor = triangle.GetTextureColor(g_Texture, baryValues);
				}
				else
				{
					finalColor = triangle.GetInterpolatedColor(baryValues);
				}
				SetColor(finalColor);
				PutPixel(pt);
			}
		}
	}
}


void UpdateFrame(void)
{
	// Buffer Clear
	SetColor(32, 128, 255);
	Clear();
	
	static float theta = 0;
	static float pos = 0;
	static float scale = 1;

	// Input 
	if (GetAsyncKeyState(VK_LEFT)) theta -= 1;
	if (GetAsyncKeyState(VK_RIGHT)) theta += 1;
	if (GetAsyncKeyState(VK_UP)) pos += 1;
	if (GetAsyncKeyState(VK_DOWN)) pos -= 1;
	if (GetAsyncKeyState(VK_PRIOR)) scale += 0.01f;
	if (GetAsyncKeyState(VK_NEXT)) scale -= 0.01f;

	static Vector3 p1 = Vector3::Make2DPoint(-80, -80);
	static Vector3 p2 = Vector3::Make2DPoint(-80, 80);
	static Vector3 p3 = Vector3::Make2DPoint(80, 80);
	static Vector3 p4 = Vector3::Make2DPoint(80, -80);

	static Vertex v1(p1, RGB32(255, 0, 0), Vector2(0.125f, 0.25f));
	static Vertex v2(p2, RGB32(0, 255, 0), Vector2(0.125f, 0.125f));
	static Vertex v3(p3, RGB32(0, 0, 255), Vector2(0.25f, 0.125f));
	static Vertex v4(p4, RGB32(255, 255, 255), Vector2(0.25f, 0.25f));

	static Triangle tri1(v1, v2, v3);
	static Triangle tri2(v1, v3, v4);
	static QuadMesh mesh1(tri1, tri2);

	Transform2D transform1(Vector2(pos, pos), theta, Vector2(scale, scale));
	GameObject2D obj1(mesh1);
	obj1.SetTransform(transform1);

	for (int i = 0; i < 2; i++)
	{
		DrawTriangle(obj1.Mesh.Triangles[i]);
	}

	// Buffer Swap 
	BufferSwap();
}


//void UpdateFrame(void)
//{
//	// Buffer Clear
//	SetColor(32, 128, 255);
//	Clear();
//
//
//	static Vector3 rgb;
//	rgb.X += 0.5f;
//	rgb.Y += 1.0f;
//	rgb.Z += 2.0f;
//
//	rgb.X = fmodf(rgb.X, 255.0f);
//	rgb.Y = fmodf(rgb.Y, 255.0f);
//	rgb.Z = fmodf(rgb.Z, 255.0f);
//
//	// Draw
//	SetColor(rgb.X, rgb.Y, rgb.Z);
//	//PutPixel(0, 0);
//	//Draw Circle wih radius 100
//	Vector2 center(0.0f, 0.0f);
//	float radius = 100.0f;
//
//
//	static float degree = 0.0f;
//	degree += 0.5f;
//	degree = fmodf(degree, 360.0f);
//
//	static float scale = 1.0f;
//	scale += 0.5f;
//	float scaleSin = sinf(Deg2Rad(scale)) + 1.0f;
//	//scale = fmodf(scale, 2.0f);
//
//
//
//	Matrix3 rotMat;
//	rotMat.SetRotation(degree);
//
//	Matrix3 scaleMat;
//	scaleMat.SetScale(scaleSin, scaleSin);
//
//	Matrix3 transMat;
//	transMat.SetTranslation((sinf(Deg2Rad(degree)) + 1.0f) * 100.0f, 0.0f);
//
//	Matrix3 TSR = transMat * scaleMat * rotMat;
//
//	for (int x = -radius; x < radius; x++)
//	{
//		for (int y = -radius; y < radius; y++)
//		{
//			PutPixel(Vector3(x, y, 1) * TSR);
//		}
//	}
//
//
//	// Buffer Swap 
//	BufferSwap();
//}

