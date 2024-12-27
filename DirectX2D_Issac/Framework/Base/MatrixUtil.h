#pragma once
class MatrixUtil
{
public:
    static  Matrix  Transpose(Matrix matrix);
    static  Matrix  Identity();
    static  Matrix  Scaling(float x, float y, float z);
    static  Matrix  Translation(float x, float y, float z);
    static  Matrix  RotationRollPitchYaw(float x, float y, float z);
    static  Matrix  Inverse(Matrix matrix);
    static  Matrix  LoadFloat4(MatrixF matrix);
    static  MatrixF StoreFloat4(Matrix matrix);
};

