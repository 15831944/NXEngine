/*
 *  File:    NXQuaternion.h
 *  author:  张雄
 *  date:    2016_05_05
 *  purpose: 四元数操作函数
 */

#ifndef __ZX_NXENGINE_QUATERNION_H__
#define __ZX_NXENGINE_QUATERNION_H__

namespace NX {
    template<typename T, int iScale> class vector;
    template<typename T, int iRow, int iCol> class Matrix;
    
    class Quaternion{
    public:
        friend  Quaternion operator * (const Quaternion &lhs, const Quaternion &rhs);
    public:
        Quaternion();
        Quaternion(const float w,  const float x, const float y, const float z);
        Quaternion(const float *v, int len = 4);
        Quaternion(const float radian, const vector<float, 3> &Axis);
        Quaternion(const vector<float, 4> &rhs);
        Quaternion(const Quaternion &rhs);
        ~Quaternion();
    public:
        Quaternion& SetRotateAboutX(const float radian);
        Quaternion& SetRotateAboutY(const float radian);
        Quaternion& SetRotateAboutZ(const float radian);
        Quaternion& SetRotateAboutAxis(const float radian, const vector<float, 3> &axis);
    public:
        float& operator[] (const int idx);
        const float operator[] (const int idx) const;
        bool operator == (const Quaternion &rhs) const;
        Quaternion& operator *= (const Quaternion &rhs);
        Quaternion& operator *= (const float value);
        Quaternion& operator += (const Quaternion &rhs);
        Quaternion& operator += (const float value);
        Quaternion& operator -= (const Quaternion &rhs);
        Quaternion& operator -= (const float value);
        Quaternion& operator /= (const float value);
        friend  Quaternion operator * (const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion operator * (const Quaternion &lhs, const float value);
        friend  Quaternion operator * (const float value, const Quaternion &lhs);
        friend  Quaternion operator - (const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion operator - (const Quaternion &lhs, const float value);
        friend  Quaternion operator + (const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion operator + (const Quaternion &lhs, const float value);
        friend  Quaternion operator / (const Quaternion &lhs, const float value);
    public:
        float Length();

        Matrix<float, 4, 4> GetRotateMatrix() const;
        Quaternion GetConjugate() const;
        Quaternion GetInverse() const;
        Quaternion GetNormalized() const;
        Quaternion GetPow(float e) const;
        
        Quaternion& Pow(float e);
        Quaternion& Inverse();
        Quaternion& Conjugate();
        vector<float, 3> Rotate(const vector<float, 3> &rhs);
        Quaternion& Normalize();
        
        /**
         *  获取四元数的旋转轴和旋转角，请保证四元数是单位四元数（可调用normalize函数将其转化为四元数)
         */
        vector<float, 3> GetRotateAxis();
        float GetRotateRadian();
        float GetRotateAngle();
    private:
         float LengthSquare();
        
    public:
        friend  float Dot(const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion Cross(const Quaternion &lhs, const Quaternion &rhs);
        friend  Quaternion Lerp(const Quaternion &lhs, const Quaternion &rhs, const float t);

    public:
        union{
            struct{
                float w;
                union{
                    struct{
                        float x;
                        float y;
                        float z;
                    };
                    float v[3];
                };
            };
            float m_V[4];
            float m_Ele[4];
        };
    };
    extern const Quaternion kQuanternionIndentity;
}


#endif