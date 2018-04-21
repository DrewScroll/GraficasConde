#include "IDVUtils\Camera.h"

Camera::Camera() {

}
Camera::~Camera() {

}
void Camera::Init(XVECTOR3 position, float fov, float ratio, float np, float fp, bool lf) {
	Eye = position;
	Fov = fov;
	AspectRatio = ratio;
	NPlane = np;
	FPlane = fp;
	LeftHanded = lf;
}
void Camera::CreatePojection() {

}
void Camera::SetLookAt(XVECTOR3 v) {
	Look = v;
}
void Camera::MoveForward(float dt) {
	Eye += Look * dt;
	XMatTranslation(Pos, Look * dt);
}
void Camera::MoveBackward(float dt) {
	Eye += -Look;
	XMatTranslation(Pos, -Look * dt);
}
void Camera::StrafeLeft(float dt) {
	Eye += -Right;
	XMatTranslation(Pos, -Right * dt);
}
void Camera::StrafeRight(float dt) {
	Eye += Right;
	XMatTranslation(Pos, Right * dt);
}
void Camera::MoveYaw(float f) {
	Yaw += f;
	XMatRotationYLH(RotY, f);
}
void Camera::MovePitch(float f) {
	if (Pitch >= -1.4835 || Pitch <= 1.4835) {
		Pitch += f;
		XMatRotationXLH(RotX, f);
	}
	Pitch += f;
}
void Camera::MoveRoll(float f) {
	Roll += f;
	XMatRotationZLH(RotZ, f);
}
void Camera::Update(float dt) {
	if (InputM.xDelta != 0) {
		if(InputM.xDelta>0)
			MoveYaw(dt);
		if (InputM.xDelta<0)
			MoveYaw(-dt);
	}
	if (InputM.xDelta != 0) {
		if (InputM.yDelta>0)
			MovePitch(dt);
		if (InputM.yDelta<0)
			MovePitch(-dt);
	}
	if (InputM.PressedKey(119))// Key pressed W
		MoveForward(dt);
	if (InputM.PressedKey(115))// Key pressed S
		MoveBackward(dt);
	if (InputM.PressedKey(97))// Key pressed A
		StrafeLeft(dt);
	if (InputM.PressedKey(100))// Key pressed D
		StrafeRight(dt);

}
void Camera::Reset() {

}
void Camera::SetFov(float f) {
	Fov = f;
}
void Camera::SetRatio(float r) {
	AspectRatio = r;
}
void Camera::SetPlanes(float n, float f) {
	NPlane = n;
	FPlane = f;
}
