#pragma once

#define CAMERA Camera::GetInstance()

class Camera : public SingleTon<Camera>
{
private:
    Camera();
    friend SingleTon;

public:
    ~Camera();  // singleTon�� �������� �̱⶧���� �ý��� ����� �ڵ�ȣ��ȴ�

public:
    void  PreUpdate();
    void  Update();
    void  Render();

public:
    void  WCtoVC(Vector2& InPos);
    void  VCtoWC(Vector2& InPos);
    Vector2& Pos() { return Position; }
    void  SetMoveCamera(Vector2 InDirection);
    bool  IsMoveCamera() { return bMoveCamera; }

private:
    void  UpdateView();
    void  UpdateProjection();
    bool  CheckCameraMove(Vector2& InPos);

public:
    void    SetCorner(Vector2 InLeft, Vector2 InRight)
    {
        CornerLeft = InLeft;
        CornerRight = InRight;
    }
    Vector2 GetMin() { return Min; }
    Vector2 GetMax() { return  Max; }

public:
    bool  ContainFrustum(Vector2 pos, Vector2 size);
    bool  ContainFrustum(Vector2 pos);

private:
    Vector2 Position = Vector2(0, 0);

private:
    class MatrixBuffer* ViewBuffer = nullptr;
    class MatrixBuffer* ProjectionBuffer = nullptr;
    XMMATRIX View = MatrixUtil::Identity();
    XMMATRIX Inverse = MatrixUtil::Identity();
    XMMATRIX Projection = MatrixUtil::Identity();
    XMMATRIX Convert = MatrixUtil::Identity();

private:
    Vector2  CornerLeft = Vector2(0, 0);     // ī�޶��̵��� Left��  MIN��
    Vector2  CornerRight = Vector2(0, 0);     // ī�޶��̵��� Right�� MAX��
    bool     bMoveCamera = false;
    Vector2  MoveDirection = Vector2(0, 0);

private:
    Vector2  Min = Vector2(0, 0);
    Vector2  Max = Vector2(0, 0);
};

