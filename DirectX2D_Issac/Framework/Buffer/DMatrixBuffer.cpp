#include "framework.h"
#include "DMatrixBuffer.h"

MatrixBuffer::MatrixBuffer(int InSlot)
{
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0
	// 0 0 0 1
	Data.matrix = XMMatrixIdentity();
	// 상수버퍼 생성
	this->SetData(&Data, sizeof(FData));
	Slot = InSlot;
}

//  Pojection,View,World
//  위치 메트릭스
//  1   0   0  0           1   0   0  Tx
//  0   1   0  0     ===>  0   1   0  Ty
//  0   0   1  0           0   0   1  Tz 
//  Tx  Ty  Tz 1           0   0   0  1
void MatrixBuffer::Set(Matrix InValue)
{
	// XNA 라이브러리를 사용 : 전치행렬로 변환
	Data.matrix = XMMatrixTranspose(InValue);
	this->SetVS(Slot);
}

//////////////////////////////////////////////////////////////////////
//   위치/이동             X축               Y축             Z축
//====================================================================
//   Sx  0  0  0       1   *  *  *     c   *  -s  0     c   s  *  0
//   0   Sy 0  0       *   c  s  0     *   *   *  *     -s  c  *  0
//   0   0  Sz 0       *  -s  c  0     s   *   c  0     0   0  *  0
//   Tx  Ty Tz W       *   0  0  1     0   *   0  1     *   *  *  1 
/////////////////////////////////////////////////////////////////////
void MatrixBuffer::Show(Matrix InMatrix)
{
	XMFLOAT4X4  matWorld;
	XMStoreFloat4x4(&matWorld, InMatrix);
	printf("--------------------------------\n");
	printf("%f %f %f %f\n", matWorld._11, matWorld._12, matWorld._13, matWorld._14);
	printf("%f %f %f %f\n", matWorld._21, matWorld._22, matWorld._23, matWorld._24);
	printf("%f %f %f %f\n", matWorld._31, matWorld._32, matWorld._33, matWorld._34);
	printf("%f %f %f %f\n", matWorld._41, matWorld._42, matWorld._43, matWorld._44);
}

// 3D--> 2D보기위해
void MatrixBuffer::MakeProjection()
{
	Matrix perspective = XMMatrixPerspectiveFovLH(XM_PIDIV4,
		(float)MAIN->GetWidth() / (float)MAIN->GetHeight(), 0.1f, 1000.0f);
	Show(perspective);
	Set(perspective);
	Show(Data.matrix);
}

// UI -->  2D
void MatrixBuffer::MakeOrthoGraphic()
{
	Matrix orthographic = XMMatrixOrthographicOffCenterLH(
		0.0f, (float)MAIN->GetWidth(), 0.0f, (float)MAIN->GetHeight(), -1.0f, 1.0f);
	Set(orthographic);
}

void MatrixBuffer::MakeView()
{
	Vector4 eye = XMVectorSet(3, 3, -7, 0);  // Camer위치점
	Vector4 focus = XMVectorSet(0, 0, 0, 0);  // Camer에서 보는 위치점
	Vector4 up = XMVectorSet(0, 1, 0, 0);

	Matrix view = XMMatrixLookAtLH(eye, focus, up);
	Set(view);
}