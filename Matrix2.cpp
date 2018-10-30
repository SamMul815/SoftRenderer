#include "stdafx.h"
#include "Matrix2.h"

Matrix2 Matrix2::operator*(const Matrix2 & mat) const
{
	Matrix2 retMat;
	retMat._11 = _11 * mat._11 + _12 * mat._21;
	retMat._12 = _11 * mat._12 + _12 * mat._22;
	retMat._21 = _21 * mat._11 + _22 * mat._21;
	retMat._22 = _21 * mat._12 + _22 * mat._22;
	return retMat;
}
