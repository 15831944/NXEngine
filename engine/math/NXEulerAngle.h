/*
 *  File:    NXEulerAngle.h
 *  author:  张雄
 *  date:    2016_05_27
 *  purpose: 欧拉角操作函数
 */

#ifndef __ZX_NXENGINE_EULER_ANGLE_H__
#define __ZX_NXENGINE_EULER_ANGLE_H__

namespace NX {
    template<typename T, int Scale> class vector;
    template<typename T, int Row, int Col> class Matrix;
    
    enum EulerAngleMode{
        INERTIA_SPACE_TO_OBJECT_SPACE,
        OBJECT_SPACE_TO_INERTIA_SPACE,
    };
    
    class EulerAngle{
    public:
        EulerAngle();
        EulerAngle(const Matrix<float, 3, 3> &rhs, const EulerAngleMode mode);
        EulerAngle(const Matrix<float, 4, 4> &rhs, const EulerAngleMode mode);
        EulerAngle(const float yAxisRotateAngle, const float xAxisRotateAngle, const float zAxisRotateAngle);
        ~EulerAngle();
    public:
        /**
         *  (heading, pitch, bank) = (yaw, pitch, roll) = (y, x, z) rotate angles
         */
        struct{
            union{
                float heading;
                float yaw;
            };
            float pitch;
            union{
                float bank;
                float roll;
            };
        };
    };
}

#endif