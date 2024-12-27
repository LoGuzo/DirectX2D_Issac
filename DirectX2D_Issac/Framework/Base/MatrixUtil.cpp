#include "framework.h"
#include "MatrixUtil.h"

Matrix MatrixUtil::Transpose(Matrix matrix)
{
    Matrix mat = XMMatrixTranspose(matrix);
    return mat;
}

Matrix MatrixUtil::Identity()
{
    Matrix mat = XMMatrixIdentity();   // 1,0,0,0
    // 0,1,0,0
    // 0,0,1,0
    // x,y,z,1
    return mat;
}

Matrix MatrixUtil::Scaling(float x, float y, float z)
{

    Matrix mat = XMMatrixScaling(x, y, x);
    return mat;
}

Matrix MatrixUtil::Translation(float x, float y, float z)
{
    Matrix mat = XMMatrixTranslation(x, y, z);
    return mat;
}

Matrix MatrixUtil::RotationRollPitchYaw(float x, float y, float z)
{
    const float TO_RADIAN = 3.141592f / 180.0f;
    Matrix mat = XMMatrixRotationRollPitchYaw(y * TO_RADIAN,
        x * TO_RADIAN, z * TO_RADIAN);
    return mat;
}

Matrix MatrixUtil::Inverse(Matrix matrix)
{
    Matrix mat = XMMatrixInverse(nullptr, matrix);
    return mat;
}

Matrix MatrixUtil::LoadFloat4(MatrixF matrix)
{
    Matrix mat = XMLoadFloat4x4(&matrix);
    return mat;
}

MatrixF MatrixUtil::StoreFloat4(Matrix matrix)
{
    MatrixF mat;
    XMStoreFloat4x4(&mat, matrix);
    return mat;
}