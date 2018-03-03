#include <IDVScene/IDVPrimitiveInstance.h>

void PrimitiveInst::TranslateAbsolute(float x, float y, float z){
	XMatTranslation(Position, x, y, z);
}

void PrimitiveInst::RotateXAbsolute(float ang) {
	XMatRotationXLH(RotationX, Deg2Rad(ang));
}

void PrimitiveInst::RotateYAbsolute(float ang) {
	XMatRotationYLH(RotationY, Deg2Rad(ang));
}

void PrimitiveInst::RotateZAbsolute(float ang) {
	XMatRotationZLH(RotationZ, Deg2Rad(ang));
}

void PrimitiveInst::ScaleAbsolute(float sc) {
	XMatScaling(Scale,sc,sc,sc);
}

void PrimitiveInst::TranslateRelative(float x, float y, float z) {
	XMATRIX44 tmp;
	XMatTranslation(tmp, x, y, z);
	Position *= tmp;
}

void PrimitiveInst::RotateXRelative(float ang) {
	XMATRIX44 tmp;
	XMatRotationXLH(tmp, Deg2Rad(ang));
	RotationX *= tmp;
}

void PrimitiveInst::RotateYRelative(float ang) {
	XMATRIX44 tmp;
	XMatRotationYLH(tmp, Deg2Rad(ang));
	RotationY *= tmp;
}

void PrimitiveInst::RotateZRelative(float ang) {
	XMATRIX44 tmp;
	XMatRotationZLH(tmp, Deg2Rad(ang));
	RotationZ *= tmp;
}

void PrimitiveInst::ScaleRelative(float sc) {
	XMATRIX44 tmp;
	XMatScaling(tmp, sc, sc, sc);
	Scale *= tmp;
}

void PrimitiveInst::Update() {
	Final = Scale*RotationX*RotationY*RotationZ*Position;
}

void PrimitiveInst::Draw(){
	if (!Visible)
		return;
	pBase->Draw(&Final.m[0][0],&Final.m[0][0]);
}

void PrimitiveInst::SetSignature(unsigned int f){
	pBase->SetGlobalSignature(f);
}
