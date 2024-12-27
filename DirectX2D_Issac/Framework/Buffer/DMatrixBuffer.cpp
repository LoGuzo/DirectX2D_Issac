#include "framework.h"
#include "DMatrixBuffer.h"

MatrixBuffer::MatrixBuffer(int InSlot)
{
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0
	// 0 0 0 1
	Data.matrix = XMMatrixIdentity();
	// ������� ����
	this->SetData(&Data, sizeof(FData));
	Slot = InSlot;
}

//  Pojection,View,World
//  ��ġ ��Ʈ����
//  1   0   0  0           1   0   0  Tx
//  0   1   0  0     ===>  0   1   0  Ty
//  0   0   1  0           0   0   1  Tz 
//  Tx  Ty  Tz 1           0   0   0  1
void MatrixBuffer::Set(Matrix InValue)
{
	// XNA ���̺귯���� ��� : ��ġ��ķ� ��ȯ
	Data.matrix = XMMatrixTranspose(InValue);
	this->SetVS(Slot);
}

//////////////////////////////////////////////////////////////////////
//   ��ġ/�̵�             X��               Y��             Z��
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

// 3D--> 2D��������
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
	Vector4 eye = XMVectorSet(3, 3, -7, 0);  // Camer��ġ��
	Vector4 focus = XMVectorSet(0, 0, 0, 0);  // Camer���� ���� ��ġ��
	Vector4 up = XMVectorSet(0, 1, 0, 0);

	Matrix view = XMMatrixLookAtLH(eye, focus, up);
	Set(view);
}