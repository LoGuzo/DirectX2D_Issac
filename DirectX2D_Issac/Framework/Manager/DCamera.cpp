#include "framework.h"
#include "DCamera.h"

Camera::Camera()
{
	ViewBuffer = new MatrixBuffer(1);
	ProjectionBuffer = new MatrixBuffer(2);
}

Camera::~Camera()
{
}

void Camera::PreUpdate()
{
	Vector2 pos = Pos();

	if (KEYBOARD->Press(VK_RIGHT))
		pos.x = pos.x + TIMER->Delta() * 1000.0f;
	if (KEYBOARD->Press(VK_UP))
		pos.y = pos.y + TIMER->Delta() * 1000.0f;
	if (KEYBOARD->Press(VK_LEFT))
		pos.x = pos.x - TIMER->Delta() * 1000.0f;
	if (KEYBOARD->Press(VK_DOWN))
		pos.y = pos.y - TIMER->Delta() * 1000.0f;

	Pos() = pos;
}

void Camera::Update()
{
	Vector2 pos = Pos();
	//	PreUpdate();
	//	UpdateProjection();
	//	UpdateView();
	//	return;

	if (bMoveCamera)
	{
		Vector2 pos = CAMERA->Pos();
		pos.x = pos.x + TIMER->Delta() * 4000.0f * MoveDirection.x;
		pos.y = pos.y + TIMER->Delta() * 4000.0f * MoveDirection.y;
		if (CheckCameraMove(pos) == false)
		{
			bMoveCamera = false;
			SCENEMGR->SetPrevScene("");
		};
		Pos() = pos;
	}
	UpdateProjection();
	UpdateView();
}

void Camera::Render()
{
}

void Camera::WCtoVC(Vector2& InPos)
{
	InPos.x = (InPos.x / MAIN->GetWidth()) * 2.0f - 1.0f;
	InPos.y = -((InPos.y / MAIN->GetHeight()) * 2.0f - 1.0f);

	InPos = InPos * Inverse;
}

void Camera::VCtoWC(Vector2& InPos)
{
	InPos = InPos * Convert;
}

void Camera::SetMoveCamera(Vector2 InDirection)
{
	bMoveCamera = true;
	MoveDirection = InDirection;
}

void Camera::UpdateView()
{
	FXMVECTOR eye = XMVectorSet(Position.x, Position.y, 0.0f, 0.0f);
	FXMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	FXMVECTOR at = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	FXMVECTOR temp = eye + at;

	View = XMMatrixLookAtLH(eye, temp, up);
	ViewBuffer->Set(View);


	Matrix vp = View * Projection;
	Inverse = MatrixUtil::Inverse(vp);

	Matrix S, T;
	S = MatrixUtil::Scaling(MAIN->GetWidth() * 0.5f, -MAIN->GetHeight() * 0.5f, 0.0f);
	T = MatrixUtil::Translation(MAIN->GetWidth() * 0.5f, MAIN->GetHeight() * 0.5f, 0.0f);
	Convert = View * Projection * S * T;

	// 윈도우기준으로 Min/Max값 정함
	Min = Vector2(0, MAIN->GetHeight());
	Max = Vector2(MAIN->GetWidth(), 0);

	WCtoVC(Min);
	WCtoVC(Max);

}

// scaleX   = 2.0/W
// scaleY   = 2.0/H
void Camera::UpdateProjection()
{
	Projection = XMMatrixOrthographicOffCenterLH(
		-(float)(MAIN->GetWidth()) * 0.5f,
		+(float)(MAIN->GetWidth()) * 0.5f,
		-(float)(MAIN->GetHeight()) * 0.5f,
		+(float)(MAIN->GetHeight()) * 0.5f, 0.0f, 1.0f);
	ProjectionBuffer->Set(Projection);
}

bool Camera::CheckCameraMove(Vector2& InPos)
{
	bool value = true;
	if (InPos.x <= CornerLeft.x)
	{
		InPos.x = CornerLeft.x;
		value = false;
	}
	if (InPos.x >= CornerRight.x)
	{
		InPos.x = CornerRight.x;
		value = false;
	}
	if (InPos.y <= CornerLeft.y)
	{
		InPos.y = CornerLeft.y;
		value = false;
	}
	if (InPos.y >= CornerRight.y)
	{
		InPos.y = CornerRight.y;
		value = false;
	}

	return value;
}

bool Camera::ContainFrustum(Vector2 pos, Vector2 size)
{
	float left = pos.x - size.x * 0.5f;
	float right = pos.x + size.x * 0.5f;
	float top = pos.y + size.y * 0.5f;
	float bottom = pos.y - size.y * 0.5f;

	if (right < Min.x) return false;
	if (left > Max.x) return false;
	if (top < Min.y) return false;
	if (bottom > Max.y) return false;

	return true;
}

bool Camera::ContainFrustum(Vector2 pos)
{
	if ((pos.x >= Min.x) && (pos.x <= Max.x) &&
		(pos.y >= Min.y) && (pos.y <= Max.y))
		return true;
	return false; return false;
}
