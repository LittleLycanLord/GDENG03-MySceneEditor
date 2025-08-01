#pragma once
#include <cmath>
#include "Math/MyVector3.hpp"
#include "Math/MyVector4.hpp"
#include "memory"

namespace DX3D {
    class MyMatrix4x4 {
        //* ╔════════════╗
        //* ║ Attributes ║
        //* ╚════════════╝
    private:
    public:
        float matrix[4][4];

        //* ╔════════════════════════════╗
        //* ║ Constructors & Destructors ║
        //* ╚════════════════════════════╝
    public:
        MyMatrix4x4() {
            memset(this->matrix, 0, sizeof(float) * 16);
            this->matrix[0][0] = 1; this->matrix[1][1] = 1; this->matrix[2][2] = 1; this->matrix[3][3] = 1;
        }
        ~MyMatrix4x4() {}

        //* ╔═══════════╗
        //* ║ Functions ║
        //* ╚═══════════╝
    private:
    public:
        //* ╔═══════════════════════╗
        //* ║ Operator Overloading  ║
        //* ╚═══════════════════════╝
        void operator=(const MyMatrix4x4& returnMatrix) { memcpy(this->matrix, returnMatrix.matrix, sizeof(float) * 16); }
        MyMatrix4x4 operator*(const MyMatrix4x4& rhs) const {
            MyMatrix4x4 result;
            for (int row = 0; row < 4; ++row)
                for (int col = 0; col < 4; ++col) {
                    result.matrix[row][col] = 0.0f;
                    for (int k = 0; k < 4; ++k)
                        result.matrix[row][col] += this->matrix[row][k] * rhs.matrix[k][col];
                }
            return result;
        }
        MyMatrix4x4& operator*=(const MyMatrix4x4& rhs) {
            *this = *this * rhs;
            return *this;
        }

        //* ╔═══════════════════════════════╗
        //* ║ Matrix Transformation Methods ║
        //* ╚═══════════════════════════════╝
        void SetIdentity() {
            *this = MyMatrix4x4::GetIdentityMatrix();
        }
        void Transpose() {
            *this = MyMatrix4x4::GetTransposedMatrix(*this);
        }
        void Translate(const MyVector3& translation) {
            *this *= MyMatrix4x4::GetTranslationMatrix(translation);
        }
        void Scale(const MyVector3& scale) {
            *this *= MyMatrix4x4::GetScaleMatrix(scale);
        }
        void RotateX(float angle) {
            *this *= MyMatrix4x4::GetXRotationMatrix(angle);
        }
        void RotateY(float angle) {
            *this *= MyMatrix4x4::GetXRotationMatrix(angle);
        }
        void RotateZ(float angle) {
            *this *= MyMatrix4x4::GetXRotationMatrix(angle);
        }
        void Rotate(const MyVector3& eulerAngles) {
            *this *= MyMatrix4x4::GetRotationMatrix(eulerAngles);
        }
        void Invert() { *this = MyMatrix4x4::GetInverseMatrix(*this); }
        void SetOrthographicLeftHand(float width, float height, float nearPlane, float farPlane) {
            *this = MyMatrix4x4::GetOrthographicLeftHandMatrix(width, height, nearPlane, farPlane);
        }
        void SetPerspectiveLeftHand(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
            *this = MyMatrix4x4::GetPerspectiveLeftHandMatrix(fieldOfView, aspectRatio, nearPlane, farPlane);
        }

        //* ╔═════════════════════╗
        //* ║ Utility Functions   ║
        //* ╚═════════════════════╝
        const float GetDeterminant() const {
            MyVector4 minor;
            MyVector4 A = { this->matrix[0][0], this->matrix[0][1], this->matrix[0][2], this->matrix[0][3] };
            MyVector4 B = { this->matrix[1][0], this->matrix[1][1], this->matrix[1][2], this->matrix[1][3] };
            MyVector4 C = { this->matrix[2][0], this->matrix[2][1], this->matrix[2][2], this->matrix[2][3] };
            minor.Cross(A, B, C);
            return -(this->matrix[3][0] * minor.x
                + this->matrix[3][1] * minor.y
                + this->matrix[3][2] * minor.z
                + this->matrix[3][3] * minor.w);
        }
        MyVector3 GetDotProduct(const MyVector3& vector) const {
            float x = vector.x * this->matrix[0][0] + vector.y * this->matrix[1][0] + vector.z * this->matrix[2][0] + this->matrix[3][0];
            float y = vector.x * this->matrix[0][1] + vector.y * this->matrix[1][1] + vector.z * this->matrix[2][1] + this->matrix[3][1];
            float z = vector.x * this->matrix[0][2] + vector.y * this->matrix[1][2] + vector.z * this->matrix[2][2] + this->matrix[3][2];
            return MyVector3(x, y, z);
        }
        MyVector3 GetRightVector() { return MyVector3(this->matrix[0][0], this->matrix[0][1], this->matrix[0][2]); }
        MyVector3 GetUpVector() { return MyVector3(this->matrix[1][0], this->matrix[1][1], this->matrix[1][2]); }
        MyVector3 GetForwardVector() { return MyVector3(this->matrix[2][0], this->matrix[2][1], this->matrix[2][2]); }
        MyVector3 GetTranslation() { return MyVector3(this->matrix[3][0], this->matrix[3][1], this->matrix[3][2]); }

        //* ╔════════════════════════════════╗
        //* ║ Virtual / Overridden Functions ║
        //* ╚════════════════════════════════╝
    protected:
    public:

        //* ╔═══════════════════╗
        //* ║ Getters & Setters ║
        //* ╚═══════════════════╝
    public:

        //* ╔═══════════════════════════════════╗
        //* ║ Static Matrix Creation Functions  ║
        //* ╚═══════════════════════════════════╝
        //* Matrix Transformation Calculations
        static MyMatrix4x4 GetIdentityMatrix() {
            MyMatrix4x4 returnMatrix;
            returnMatrix.matrix[0][0] = 1; returnMatrix.matrix[1][1] = 1; returnMatrix.matrix[2][2] = 1; returnMatrix.matrix[3][3] = 1;
            return returnMatrix;
        }
        static MyMatrix4x4 GetTransposedMatrix(const MyMatrix4x4& matrix) {
            MyMatrix4x4 returnMatrix; returnMatrix = matrix;
            for (int row = 0; row < 4; ++row)
                for (int column = row + 1; column < 4; ++column)
                    std::swap(returnMatrix.matrix[row][column], returnMatrix.matrix[column][row]);
            return returnMatrix;
        }
        static MyMatrix4x4 GetTranslationMatrix(const MyVector3& translation) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            returnMatrix.matrix[3][0] = translation.x; returnMatrix.matrix[3][1] = translation.y; returnMatrix.matrix[3][2] = translation.z;
            return returnMatrix;
        }
        static MyMatrix4x4 GetScaleMatrix(const MyVector3& sinAngle) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            returnMatrix.matrix[0][0] = sinAngle.x; returnMatrix.matrix[1][1] = sinAngle.y; returnMatrix.matrix[2][2] = sinAngle.z;
            return returnMatrix;
        }
        static MyMatrix4x4 GetXRotationMatrix(float angle) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            float cosAngle = std::cos(angle), sinAngle = std::sin(angle);
            returnMatrix.matrix[1][1] = cosAngle; returnMatrix.matrix[1][2] = sinAngle;
            returnMatrix.matrix[2][1] = -sinAngle; returnMatrix.matrix[2][2] = cosAngle;
            return returnMatrix;
        }
        static MyMatrix4x4 GetYRotationMatrix(float angle) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            float cosAngle = std::cos(angle), sinAngle = std::sin(angle);
            returnMatrix.matrix[0][0] = cosAngle; returnMatrix.matrix[0][2] = -sinAngle;
            returnMatrix.matrix[2][0] = sinAngle; returnMatrix.matrix[2][2] = cosAngle;
            return returnMatrix;
        }
        static MyMatrix4x4 GetZRotationMatrix(float angle) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            float cosAngle = std::cos(angle), sinAngle = std::sin(angle);
            returnMatrix.matrix[0][0] = cosAngle; returnMatrix.matrix[0][1] = sinAngle;
            returnMatrix.matrix[1][0] = -sinAngle; returnMatrix.matrix[1][1] = cosAngle;
            return returnMatrix;
        }
        static MyMatrix4x4 GetRotationMatrix(const MyVector3& eulerAngles) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            returnMatrix = MyMatrix4x4::GetXRotationMatrix(eulerAngles.x) *
                MyMatrix4x4::GetYRotationMatrix(eulerAngles.y) *
                MyMatrix4x4::GetZRotationMatrix(eulerAngles.z);
            return returnMatrix;
        }
        static MyMatrix4x4 GetInverseMatrix(const MyMatrix4x4& matrix) {
            MyMatrix4x4 inverse;
            int a;
            MyVector4 vector, vectors[3];
            float determinant = matrix.GetDeterminant();
            if (determinant == 0.0f) return inverse; // Return identity if not invertible
            for (int row = 0; row < 4; row++) {
                for (int column = 0; column < 4; column++) {
                    if (column != row) {
                        a = column;
                        if (column > row) a--;
                        vectors[a].x = matrix.matrix[column][0];
                        vectors[a].y = matrix.matrix[column][1];
                        vectors[a].z = matrix.matrix[column][2];
                        vectors[a].w = matrix.matrix[column][3];
                    }
                }
                vector.Cross(vectors[0], vectors[1], vectors[2]);
                inverse.matrix[0][row] = (float)pow(-1.0f, row) * vector.x / determinant;
                inverse.matrix[1][row] = (float)pow(-1.0f, row) * vector.y / determinant;
                inverse.matrix[2][row] = (float)pow(-1.0f, row) * vector.z / determinant;
                inverse.matrix[3][row] = (float)pow(-1.0f, row) * vector.w / determinant;
            }
            return inverse;
        }
        static MyMatrix4x4 GetOrthographicLeftHandMatrix(float width, float height, float nearPlane, float farPlane) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            returnMatrix.matrix[0][0] = 2.0f / width;
            returnMatrix.matrix[1][1] = 2.0f / height;
            returnMatrix.matrix[2][2] = 1.0f / (farPlane - nearPlane);
            returnMatrix.matrix[3][2] = -(nearPlane / (farPlane - nearPlane));
            return returnMatrix;
        }
        static MyMatrix4x4 GetPerspectiveLeftHandMatrix(float fieldOfView, float aspectRatio, float nearPlane, float farPlane) {
            MyMatrix4x4 returnMatrix; returnMatrix.SetIdentity();
            float yScale = 1.0f / std::tan(fieldOfView / 2.0f);
            float xScale = yScale / aspectRatio;
            returnMatrix.matrix[0][0] = xScale;
            returnMatrix.matrix[1][1] = yScale;
            returnMatrix.matrix[2][2] = farPlane / (farPlane - nearPlane);
            returnMatrix.matrix[2][3] = 1.0f;
            returnMatrix.matrix[3][2] = (-nearPlane * farPlane) / (farPlane - nearPlane);
            return returnMatrix;
        }

    };
} // namespace DX3D

