#include "stdafx.h"
#include "incl\IDV_Maths.h"

void XMatViewLookAtLH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = lookAt - camPos;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatViewLookAtRH(XMATRIX44 &mpout, const XVECTOR3 &camPos, const XVECTOR3 &lookAt, const XVECTOR3 &upAxis) {
	XVECTOR3 zaxe = camPos - lookAt;
	zaxe.Normalize();

	XVECTOR3 xaxe;
	XVecCross(xaxe, upAxis, zaxe);
	xaxe.Normalize();

	XVECTOR3 yaxe;
	XVecCross(yaxe, zaxe, xaxe);

	mpout.m[0][0] = xaxe.x;
	mpout.m[0][1] = yaxe.x;
	mpout.m[0][2] = zaxe.x;
	XVecDot(mpout.m[3][0], xaxe, camPos);
	mpout.m[3][0] = -mpout.m[3][0];

	mpout.m[1][0] = xaxe.y;
	mpout.m[1][1] = yaxe.y;
	mpout.m[1][2] = zaxe.y;
	XVecDot(mpout.m[3][1], yaxe, camPos);
	mpout.m[3][1] = -mpout.m[3][1];

	mpout.m[2][0] = xaxe.z;
	mpout.m[2][1] = yaxe.z;
	mpout.m[2][2] = zaxe.z;
	XVecDot(mpout.m[3][2], zaxe, camPos);
	mpout.m[3][2] = -mpout.m[3][2];

	mpout.m[0][3] = 0.0f;
	mpout.m[1][3] = 0.0f;
	mpout.m[2][3] = 0.0f;
	mpout.m[3][3] = 1.0f;
}

void XMatPerspectiveLH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane) {
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (FarPlane - NearPlane);
	mpout.m[2][3] = 1.0;
	mpout.m[3][2] = -(NearPlane*FarPlane) / (FarPlane - NearPlane);
	mpout.m[3][3] = 0.0f;

}

void XMatPerspectiveRH(XMATRIX44 &mpout, const float &FOV, const float &Aspect, const float &NearPlane, const float &FarPlane)
{
	float x, y;
	float ang = FOV / 2.0f;

	y = cos(ang) / sin(ang);
	x = y / Aspect;

	mpout.m[0][0] = x;
	mpout.m[1][1] = y;
	mpout.m[2][2] = FarPlane / (NearPlane - FarPlane);
	mpout.m[2][3] = -1.0;
	mpout.m[3][2] = (NearPlane*FarPlane) / (NearPlane - FarPlane);
	mpout.m[3][3] = 0.0f;
}

void XMatOrthoLH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zf - zn);
	m.m[3][2] = -zn / (zf - zn);
	m.m[3][3] = 1.0f;
}

void XMatOrthoRH(XMATRIX44 &m, const float &w, const float &h, const float &zn, const float &zf) {
	m.m[0][0] = 2.0f / w;
	m.m[1][1] = 2.0f / h;
	m.m[2][2] = 1.0f / (zn - zf);
	m.m[3][2] = zn / (zn - zf);
	m.m[3][3] = 1.0f;
}

void XMatRotationAxisRH(XMATRIX44 &, const XVECTOR3 &, const float &)
{
}

void XMatRotationAxisLH(XMATRIX44 &, const XVECTOR3 &, const float &)
{
}

void XVecTransformLH(XVECTOR3 &, const XVECTOR3 &, const XMATRIX44 &)
{
}

void XVecTransformNormalLH(XVECTOR3 &output, const XVECTOR3 &inputV, const XMATRIX44 &inputM)
{
	output.x = inputV.x*inputM.m[0][0] + inputV.y*inputM.m[1][0] + inputV.z*inputM.m[2][0];
	output.y = inputV.x*inputM.m[0][1] + inputV.y*inputM.m[1][1] + inputV.z*inputM.m[2][1];
	output.z = inputV.x*inputM.m[0][2] + inputV.y*inputM.m[1][2] + inputV.z*inputM.m[2][2];
	output.w = 1.0f;
}

void XVecTransformRH(XVECTOR3 &, const XVECTOR3 &, const XMATRIX44 &)
{
}

void XVecTransformNormalRH(XVECTOR3 &output, const XVECTOR3 &inputV, const XMATRIX44 &inputM)
{
	output.x = inputV.x*inputM.m[0][0] + inputV.y*inputM.m[0][1] + inputV.z*inputM.m[0][2];
	output.y = inputV.x*inputM.m[1][0] + inputV.y*inputM.m[1][1] + inputV.z*inputM.m[1][2];
	output.z = inputV.x*inputM.m[2][0] + inputV.y*inputM.m[2][1] + inputV.z*inputM.m[2][2];
	output.w = 1.0f;
}

void XVecDot(float &output, const XVECTOR3 &inputA, const XVECTOR3 &inputB)
{
	output = inputA.x*inputB.x + inputA.y*inputB.y + inputA.z*inputB.z + inputA.w*inputB.w;
}

void XVecLength(float &output, const XVECTOR3 & v)
{
	float res;
	XVecDot(res, v, v);
	output = sqrtf(res);
}

void XVecCross(XVECTOR3 &output, const XVECTOR3 &inputA, const XVECTOR3 &inputB)
{
	output.x = inputA.y*inputB.z - inputA.z*inputB.y;
	output.y = inputA.z*inputB.x - inputA.x*inputB.z;
	output.z = inputA.x*inputB.y - inputA.y*inputB.x;
}

void XVec3Normalize(XVECTOR3 &output, const XVECTOR3 &v)
{
	float inv;
	XVecLength(inv, v);
	inv = 1.0f / inv;
	output = { v.x*inv,v.y*inv,v.z*inv,v.w*inv };
}

void PrintMatrix(const XMATRIX44 & Matrix)
{
	std::cout << "( " << Matrix.m11 << ", " << Matrix.m12 << ", " << Matrix.m13 << ", " << Matrix.m14 << ")" << std::endl;
	std::cout << "( " << Matrix.m21 << ", " << Matrix.m22 << ", " << Matrix.m23 << ", " << Matrix.m24 << ")" << std::endl;
	std::cout << "( " << Matrix.m31 << ", " << Matrix.m32 << ", " << Matrix.m33 << ", " << Matrix.m34 << ")" << std::endl;
	std::cout << "( " << Matrix.m41 << ", " << Matrix.m42 << ", " << Matrix.m43 << ", " << Matrix.m44 << ")" << std::endl;
}

XVECTOR3 operator*(float f, const XVECTOR3 &v)
{
	XVECTOR3 Res;
	Res.x = v.x*f;
	Res.y = v.y*f;
	Res.z = v.z*f;
	return Res;
}

void XMATRIX44::Inverse(XMATRIX44 *o) {
#if DOUBLE_FOR_INVERSE
	XMATRIX44_64 tmp64 = XMATRIX44_64(this);
	double det =
#else
	XMATRIX44 tmp64 = *this;
	float det =
#endif
		tmp64.m11*tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m11*tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m11*tmp64.m24*tmp64.m32*tmp64.m43
		+ tmp64.m12*tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m12*tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m33*tmp64.m41
		+ tmp64.m13*tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m13*tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m13*tmp64.m24*tmp64.m31*tmp64.m42
		+ tmp64.m14*tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m14*tmp64.m23*tmp64.m32*tmp64.m41
		- tmp64.m11*tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m11*tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m11*tmp64.m24*tmp64.m33*tmp64.m42
		- tmp64.m12*tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m12*tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m12*tmp64.m24*tmp64.m31*tmp64.m43
		- tmp64.m13*tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m13*tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m32*tmp64.m41
		- tmp64.m14*tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m14*tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m14*tmp64.m23*tmp64.m31*tmp64.m42;
#if DOUBLE_FOR_INVERSE
	if (det == 0.0) {
#else
	if (det == 0.0f) {
#endif
		printf("\n\nThe Universe stopped, no det for Matrix, all ends here.\n\n");
		exit(666);
	}
#if DOUBLE_FOR_INVERSE
	det = 1.0 / det;
	XMATRIX44_64 out;
#else
	det = 1.0f / det;
	XMATRIX44 out;
#endif

	out.m11 = tmp64.m22*tmp64.m33*tmp64.m44 + tmp64.m23*tmp64.m34*tmp64.m42 + tmp64.m24*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m34*tmp64.m43 - tmp64.m23*tmp64.m32*tmp64.m44 - tmp64.m24*tmp64.m33*tmp64.m42;
	out.m12 = tmp64.m12*tmp64.m34*tmp64.m43 + tmp64.m13*tmp64.m32*tmp64.m44 + tmp64.m14*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m33*tmp64.m44 - tmp64.m13*tmp64.m34*tmp64.m42 - tmp64.m14*tmp64.m32*tmp64.m43;
	out.m13 = tmp64.m12*tmp64.m23*tmp64.m44 + tmp64.m13*tmp64.m24*tmp64.m42 + tmp64.m14*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m24*tmp64.m43 - tmp64.m13*tmp64.m22*tmp64.m44 - tmp64.m14*tmp64.m23*tmp64.m42;
	out.m14 = tmp64.m12*tmp64.m24*tmp64.m33 + tmp64.m13*tmp64.m22*tmp64.m34 + tmp64.m14*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m23*tmp64.m34 - tmp64.m13*tmp64.m24*tmp64.m32 - tmp64.m14*tmp64.m22*tmp64.m33;
	out.m21 = tmp64.m21*tmp64.m34*tmp64.m43 + tmp64.m23*tmp64.m31*tmp64.m44 + tmp64.m24*tmp64.m33*tmp64.m41 - tmp64.m21*tmp64.m33*tmp64.m44 - tmp64.m23*tmp64.m34*tmp64.m41 - tmp64.m24*tmp64.m31*tmp64.m43;
	out.m22 = tmp64.m11*tmp64.m33*tmp64.m44 + tmp64.m13*tmp64.m34*tmp64.m41 + tmp64.m14*tmp64.m31*tmp64.m43 - tmp64.m11*tmp64.m34*tmp64.m43 - tmp64.m13*tmp64.m31*tmp64.m44 - tmp64.m14*tmp64.m33*tmp64.m41;
	out.m23 = tmp64.m11*tmp64.m24*tmp64.m43 + tmp64.m13*tmp64.m21*tmp64.m44 + tmp64.m14*tmp64.m23*tmp64.m41 - tmp64.m11*tmp64.m23*tmp64.m44 - tmp64.m13*tmp64.m24*tmp64.m41 - tmp64.m14*tmp64.m21*tmp64.m43;
	out.m24 = tmp64.m11*tmp64.m23*tmp64.m34 + tmp64.m13*tmp64.m24*tmp64.m31 + tmp64.m14*tmp64.m21*tmp64.m33 - tmp64.m11*tmp64.m24*tmp64.m33 - tmp64.m13*tmp64.m21*tmp64.m34 - tmp64.m14*tmp64.m23*tmp64.m31;
	out.m31 = tmp64.m21*tmp64.m32*tmp64.m44 + tmp64.m22*tmp64.m34*tmp64.m41 + tmp64.m24*tmp64.m31*tmp64.m42 - tmp64.m21*tmp64.m34*tmp64.m42 - tmp64.m22*tmp64.m31*tmp64.m44 - tmp64.m24*tmp64.m32*tmp64.m41;
	out.m32 = tmp64.m11*tmp64.m34*tmp64.m42 + tmp64.m12*tmp64.m31*tmp64.m44 + tmp64.m14*tmp64.m32*tmp64.m41 - tmp64.m11*tmp64.m32*tmp64.m44 - tmp64.m12*tmp64.m34*tmp64.m41 - tmp64.m14*tmp64.m31*tmp64.m42;
	out.m33 = tmp64.m11*tmp64.m22*tmp64.m44 + tmp64.m12*tmp64.m24*tmp64.m41 + tmp64.m14*tmp64.m21*tmp64.m42 - tmp64.m11*tmp64.m24*tmp64.m42 - tmp64.m12*tmp64.m21*tmp64.m44 - tmp64.m14*tmp64.m22*tmp64.m41;
	out.m34 = tmp64.m11*tmp64.m24*tmp64.m32 + tmp64.m12*tmp64.m21*tmp64.m34 + tmp64.m14*tmp64.m22*tmp64.m31 - tmp64.m11*tmp64.m22*tmp64.m34 - tmp64.m12*tmp64.m24*tmp64.m31 - tmp64.m14*tmp64.m21*tmp64.m32;
	out.m41 = tmp64.m21*tmp64.m33*tmp64.m42 + tmp64.m22*tmp64.m31*tmp64.m43 + tmp64.m23*tmp64.m32*tmp64.m41 - tmp64.m21*tmp64.m32*tmp64.m43 - tmp64.m22*tmp64.m33*tmp64.m41 - tmp64.m23*tmp64.m31*tmp64.m42;
	out.m42 = tmp64.m11*tmp64.m32*tmp64.m43 + tmp64.m12*tmp64.m33*tmp64.m41 + tmp64.m13*tmp64.m31*tmp64.m42 - tmp64.m11*tmp64.m33*tmp64.m42 - tmp64.m12*tmp64.m31*tmp64.m43 - tmp64.m13*tmp64.m32*tmp64.m41;
	out.m43 = tmp64.m11*tmp64.m23*tmp64.m42 + tmp64.m12*tmp64.m21*tmp64.m43 + tmp64.m13*tmp64.m22*tmp64.m41 - tmp64.m11*tmp64.m22*tmp64.m43 - tmp64.m12*tmp64.m23*tmp64.m41 - tmp64.m13*tmp64.m21*tmp64.m42;
	out.m44 = tmp64.m11*tmp64.m22*tmp64.m33 + tmp64.m12*tmp64.m23*tmp64.m31 + tmp64.m13*tmp64.m21*tmp64.m32 - tmp64.m11*tmp64.m23*tmp64.m32 - tmp64.m12*tmp64.m21*tmp64.m33 - tmp64.m13*tmp64.m22*tmp64.m31;

	for (int i = 0; i < 16; i++) {
#if DOUBLE_FOR_INVERSE
		double val = det * out.mat[i];
		(*o).mat[i] = static_cast<float>(val);
#else
		(*o).mat[i] = det * out.mat[i];
#endif
	}
	}

void XMatMultiply(XMATRIX44 &output, const XMATRIX44 &inputA, const XMATRIX44 &inputB)
{
	memset(&output.m[0], 0, sizeof(output));
	output.m11 = (inputA.m11*inputB.m11 + inputA.m12*inputB.m21 + inputA.m13*inputB.m31 + inputA.m14*inputB.m41);
	output.m12 = (inputA.m11*inputB.m12 + inputA.m12*inputB.m22 + inputA.m13*inputB.m32 + inputA.m14*inputB.m42);
	output.m13 = (inputA.m11*inputB.m13 + inputA.m12*inputB.m23 + inputA.m13*inputB.m33 + inputA.m14*inputB.m43);
	output.m14 = (inputA.m11*inputB.m14 + inputA.m12*inputB.m24 + inputA.m13*inputB.m34 + inputA.m14*inputB.m44);

	output.m21 = (inputA.m21*inputB.m11 + inputA.m22*inputB.m21 + inputA.m23*inputB.m31 + inputA.m24*inputB.m41);
	output.m22 = (inputA.m21*inputB.m12 + inputA.m22*inputB.m22 + inputA.m23*inputB.m32 + inputA.m24*inputB.m42);
	output.m23 = (inputA.m21*inputB.m13 + inputA.m22*inputB.m23 + inputA.m23*inputB.m33 + inputA.m24*inputB.m43);
	output.m24 = (inputA.m21*inputB.m14 + inputA.m22*inputB.m24 + inputA.m23*inputB.m34 + inputA.m24*inputB.m44);
	
	output.m31 = (inputA.m31*inputB.m11 + inputA.m32*inputB.m21 + inputA.m33*inputB.m31 + inputA.m34*inputB.m41);
	output.m32 = (inputA.m31*inputB.m12 + inputA.m32*inputB.m22 + inputA.m33*inputB.m32 + inputA.m34*inputB.m42);
	output.m33 = (inputA.m31*inputB.m13 + inputA.m32*inputB.m23 + inputA.m33*inputB.m33 + inputA.m34*inputB.m43);
	output.m34 = (inputA.m31*inputB.m14 + inputA.m32*inputB.m24 + inputA.m33*inputB.m34 + inputA.m34*inputB.m44);

	output.m41 = (inputA.m41*inputB.m11 + inputA.m42*inputB.m21 + inputA.m43*inputB.m31 + inputA.m44*inputB.m41);
	output.m42 = (inputA.m41*inputB.m12 + inputA.m42*inputB.m22 + inputA.m43*inputB.m32 + inputA.m44*inputB.m42);
	output.m43 = (inputA.m41*inputB.m13 + inputA.m42*inputB.m23 + inputA.m43*inputB.m33 + inputA.m44*inputB.m43);
	output.m44 = (inputA.m41*inputB.m14 + inputA.m42*inputB.m24 + inputA.m43*inputB.m34 + inputA.m44*inputB.m44);

}

void XMatTranslation(XMATRIX44 &output, const float &inputX, const float &inputY, const float &inputZ)
{
	output.m41 += inputX;
	output.m42 += inputY;
	output.m43 += inputZ;
}

void XMatTranslation(XMATRIX44 &output, XVECTOR3 &input)
{
	output.m41 += input.x;
	output.m42 += input.y;
	output.m43 += input.z;
}

void XMatScaling(XMATRIX44 &output, const float &inputX, const float &inputY, const float &inputZ)
{
	output.m11 *= inputX;
	output.m22 *= inputY;
	output.m33 *= inputZ;
}

void XMatRotationXLH(XMATRIX44 &output, const float &theta)
{
	output.m22 = output.m33 = cosf(theta);
	output.m23 = sinf(theta);
	output.m32 = -output.m23;
}

void XMatRotationXRH(XMATRIX44 &output, const float &theta)
{
	output.m22 = output.m33 = cosf(theta);
	output.m23 = -sinf(theta);
	output.m32 = -output.m23;
}

void XMatRotationYLH(XMATRIX44 &output, const float &theta)
{
	output.m11 = output.m33 = cosf(theta);
	output.m31 = sinf(theta);
	output.m13 = -output.m31;
}

void XMatRotationYRH(XMATRIX44 &output, const float &theta)
{
	output.m11 = output.m33 = cosf(theta);
	output.m31 = -sinf(theta);
	output.m13 = -output.m31;
}

void XMatRotationZLH(XMATRIX44 &output, const float &theta)
{
	output.m11 = output.m22 = cosf(theta);
	output.m12 = sinf(theta);
	output.m21 = -output.m12;
}

void XMatRotationZRH(XMATRIX44 &output, const float &theta)
{
	output.m11 = output.m22 = cosf(theta);
	output.m12 = -sinf(theta);
	output.m21 = -output.m12;
}

void XMatTranspose(XMATRIX44 &output, XMATRIX44 input)
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
			output.m[i][j] = input.m[j][i];
}

void XMatIdentity(XMATRIX44 &output)
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			output.m[j][i] = (i == j) ? 1.0f : 0.0f;
}

//XVECTOR2::operator float*()
//{
//	//TODO 
//}
//
//XVECTOR2::operator const float*() const
//{
//	//TODO
//}

XVECTOR2 & XVECTOR2::operator+=(const XVECTOR2 &v)
{
	XVECTOR2 Res;
	Res.x = this->x + v.x;
	Res.y = this->y + v.y;
	return Res;
}

XVECTOR2 & XVECTOR2::operator-=(const XVECTOR2 &v)
{
	XVECTOR2 Res;
	Res.x = this->x - v.x;
	Res.y = this->y - v.y;
	return Res;
}

XVECTOR2 & XVECTOR2::operator*=(float f)
{
	XVECTOR2 Res;
	Res.x = this->x*f;
	Res.y = this->y*f;
	return Res;
}

XVECTOR2 & XVECTOR2::operator/=(float f)
{
	XVECTOR2 Res;
	Res.x = this->x / f;;
	Res.y = this->y / f;
	return Res;
}

//XVECTOR2 XVECTOR2::operator+() const
//{
//	return XVECTOR2();
//}
//
//XVECTOR2 XVECTOR2::operator-() const
//{
//	return XVECTOR2();
//}

XVECTOR2 XVECTOR2::operator+(const XVECTOR2 &v) const
{
	XVECTOR2 Res;
	Res.x = this->x + v.x;
	Res.y = this->y + v.y;
	return Res;
}

XVECTOR2 XVECTOR2::operator-(const XVECTOR2 &v) const
{
	XVECTOR2 Res;
	Res.x = this->x - v.x;
	Res.y = this->y - v.y;
	return Res;
}

XVECTOR2 XVECTOR2::operator*(float f) const
{
	XVECTOR2 Res;
	Res.x = this->x*f;
	Res.y = this->y*f;
	return Res;
}

XVECTOR2 XVECTOR2::operator/(float f) const
{
	XVECTOR2 Res;
	Res.x = this->x / f;
	Res.y = this->y / f;
	return Res;
}

bool XVECTOR2::operator==(const XVECTOR2 &v) const
{
	if (this->x == v.x && this->y == v.y)
		return true;
	else
		return false;
}

bool XVECTOR2::operator!=(const XVECTOR2 &v) const
{
	if (this->x != v.x || this->y != v.y)
		return true;
	else
		return false;
}

void XVECTOR2::Normalize()
{
	float inv = 1.0f / this->Length();
	this->x = this->x*inv;
	this->y = this->y*inv;
}

float XVECTOR2::Length()
{
	return sqrt((this->x*this->x)+(this->y*this->y));
}

//XVECTOR3::operator float*()
//{
//}
//
//XVECTOR3::operator const float*() const
//{
//}

XVECTOR3 & XVECTOR3::operator+=(const XVECTOR3 &v)
{
	XVECTOR3 Res;
	Res.x = this->x + v.x;
	Res.y = this->y + v.y;
	Res.z = this->z + v.z;
	return Res;
}

XVECTOR3 & XVECTOR3::operator-=(const XVECTOR3 &v)
{
	XVECTOR3 Res;
	Res.x = this->x - v.x;
	Res.y = this->y - v.y;
	Res.z = this->z - v.z;
	return Res;

}

XVECTOR3 & XVECTOR3::operator*=(float f)
{
	XVECTOR3 Res;
	Res.x = this->x*f;
	Res.y = this->y*f;
	Res.z = this->z*f;	
	return Res;
}

XVECTOR3 & XVECTOR3::operator/=(float f)
{
	XVECTOR3 Res;
	Res.x = this->x / f;
	Res.y = this->y / f;
	Res.z = this->z / f;
	return Res;
}

//XVECTOR3 XVECTOR3::operator+() const
//{
//	return XVECTOR3();
//}
//
//XVECTOR3 XVECTOR3::operator-() const
//{
//	return XVECTOR3();
//}

XVECTOR3 XVECTOR3::operator+(const XVECTOR3 &v) const
{
	XVECTOR3 Res;
	Res.x = this->x + v.x;
	Res.y = this->y + v.y;
	Res.z = this->z + v.z;
	return Res;
}

XVECTOR3 XVECTOR3::operator-(const XVECTOR3 &v) const
{
	XVECTOR3 Res;
	Res.x = this->x - v.x;
	Res.y = this->y - v.y;
	Res.z = this->z - v.z;
	return Res;
}

XVECTOR3 XVECTOR3::operator*(float f) const
{
	XVECTOR3 Res;
	Res.x = this->x*f;
	Res.y = this->y*f;
	Res.z = this->z*f;
	return Res;
}

XVECTOR3 XVECTOR3::operator/(float f) const
{
	XVECTOR3 Res;
	Res.x = this->x/f;
	Res.y = this->y/f;
	Res.z = this->z/f;
	return Res;
}

XVECTOR3 XVECTOR3::operator*(const XVECTOR3 &v)
{
	XVECTOR3 Res;
	Res.x = this->x*v.x;
	Res.y = this->y*v.y;
	Res.z = this->z*v.z;
	Res.w = this->w*v.w;
	return Res;
}

bool XVECTOR3::operator==(const XVECTOR3 &v) const
{
	if (this->x == v.x && this->y == v.y && this->z == v.z && this->w == v.w)
		return true;
	else
		return false;
}

bool XVECTOR3::operator!=(const XVECTOR3 &v) const
{
	if (this->x != v.x || this->y != v.y || this->z != v.z || this->w != v.w)
		return true;
	else
		return false;
}

void XVECTOR3::Normalize()
{
	float inv;
	inv = 1 / this->Length();
	this->x = this->x*inv;
	this->y = this->y*inv;
	this->z = this->z*inv;
}

float XVECTOR3::Length()
{
	return sqrt((this->x*this->x)+(this->y*this->y)+(this->z*this->z));
}

//XMATRIX44_64::XMATRIX44_64()
//{
//}

//XMATRIX44_64::XMATRIX44_64(XMATRIX44 * Mi)
//{
//	for (int j = 0; j < 4; ++j)
//		for (int i = 0; i < 4; ++i)
//			this->m[j][i] = Mi->m[j][i];
//}

XMATRIX44 & XMATRIX44::operator*=(const XMATRIX44 &M)
{
	XMATRIX44 Res;
	XMatMultiply(Res, *this, M);
	return Res;
}

XMATRIX44 & XMATRIX44::operator+=(const XMATRIX44 &M)
{
	XMATRIX44 Res;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
				Res.m[j][i] = this->m[j][i] + M.m[j][i];
	return Res;
	// TODO: insertar una instrucción return aquí
}

XMATRIX44 & XMATRIX44::operator-=(const XMATRIX44 &M)
{
	XMATRIX44 Res;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
			Res.m[j][i] = this->m[j][i] - M.m[j][i];
	return Res;
	// TODO: insertar una instrucción return aquí
}

XMATRIX44 & XMATRIX44::operator*=(float f)
{
	XMATRIX44 Res;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
			Res.m[j][i] = this->m[j][i] * f;
	return Res;
	// TODO: insertar una instrucción return aquí
}

XMATRIX44 & XMATRIX44::operator/=(float f)
{
	XMATRIX44 Res;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
			Res.m[j][i] = this->m[j][i] / f;
	return Res;
	// TODO: insertar una instrucción return aquí
}

XMATRIX44 XMATRIX44::operator*(const XMATRIX44 &M) const
{
	XMATRIX44 Res;
	XMatMultiply(Res, *this, M);
	return Res;
}

XMATRIX44 XMATRIX44::operator+(const XMATRIX44 &M) const
{
	XMATRIX44 Res;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
			Res.m[j][i] = this->m[j][i] + M.m[j][i];
	return Res;
}

XMATRIX44 XMATRIX44::operator-(const XMATRIX44 &M) const
{
	XMATRIX44 Res;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
			Res.m[j][i] = this->m[j][i] - M.m[j][i];
	return Res;
}

XMATRIX44 XMATRIX44::operator*(float f) const
{
	XMATRIX44 Res;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
			Res.m[j][i] = this->m[j][i] * f;
	return Res;
}

XMATRIX44 XMATRIX44::operator/(float f) const
{
	XMATRIX44 Res;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
			Res.m[j][i] = this->m[j][i] / f;
	return Res;
}

bool XMATRIX44::operator==(const XMATRIX44 &M) const
{
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
			if (this->m[j][i] != M.m[j][i])
				return false;
	return true;
}

bool XMATRIX44::operator!=(const XMATRIX44 &M) const
{
	bool right = true;
	for (int j = 0; j < 4; ++j)
		for (int i = 0; i < 4; ++i)
			if (this->m[j][i] == M.m[j][i])
				right = false;
	if (right)
		return true;
	if(!right)
		return false;
}
