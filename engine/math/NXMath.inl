/*
 *  File:    NXMath.inl
 *  author:  张雄
 *  date:    2016_02_26
 *  purpose: 基本的数学库函数
 */

inline int    RandInt(){
    return std::rand();
}

template<typename T>
inline T DG2RD(const T angle){
    return angle * kfPi / 180.0f;
}

template<typename T>
inline T RD2DG(const T radian){
    return radian * 180.0f / kfPi;
}

template<>
inline double DG2RD<double>(const double angle){
    return angle * klfPi / 180.0;
}

template<>
inline double RD2DG<double>(const double radian){
    return radian * 180.0 / klfPi;
}

inline int RandIntInRange(int left, int right){
    NXAssert(left <= right);
    return left + RandInt() % (right - left + 1);
}

//如果不懂这代码，请先看明白IEEE754浮点数标准
inline float  RandUnitFloat(){
    static unsigned int seed = std::rand();
    float Result;
    unsigned int tmp;
    seed *= 16807;
    tmp = seed ^ (seed >> 4) ^ (seed << 15);
    *((unsigned int *) &Result) = (tmp >> 9) | 0x3F800000;
    return (Result - 1.0f);
}

inline float  RandFloatInRange(float left, float right){
    NXAssert(NXAbs(right - left) > FLOAT_EPSILON);
    return RandUnitFloat() * (right - left) + left;
}

double QuickSinWithAngle(const int Angle){
    return std::sin(DG2RD(Angle));
}

double QuickCosWithAngle(const int Angle){
    return std::cos(DG2RD(Angle));
}

//after clamp, we have ComparedValue >= NewValue
template<typename T, typename U>
inline T ClampFloor(T& ComparedValue, const U NewValue){
    T OldValue(ComparedValue);
    if(ComparedValue < NewValue){
        ComparedValue = NewValue;
    }
    return OldValue;
}

//after clamp, we have ComparedValue <= NewValue
template<typename T, typename U>
inline T ClampCeil(T& ComparedValue, const U NewValue){
    T OldValue(ComparedValue);
    if(ComparedValue > NewValue){
        ComparedValue = NewValue;
    }
    return OldValue;
}

//after clamp, we have FloorValue <= CompraedValue <= CeilValue
template<typename T, typename U, typename X>
inline T Clamp(T& ComparedValue, const U FloorValue, const X CeilValue){
    T OldValue(ComparedValue);
    if(OldValue > CeilValue){
        ComparedValue = CeilValue;
    }
    if(OldValue < FloorValue){
        ComparedValue = FloorValue;
    }
    return OldValue;
}

template<typename T>
T NXAbs(const T value){
    return value < 0 ? -value : value;
}

template<typename T, typename U>
T NXMin(const T l, const U r){
    return l < r ? l : r;
}

template<typename T, typename U>
T NXMax(const T l, const U r){
    return l > r ? l : r;
}

template<typename T, typename U>
T Wrap(T &value, const U mode){
    T OldValue = value;
    value += mode;
    Mode(value, mode * 2);
    value -= mode;
    return OldValue;
}

template<typename T, typename U>
T Mode(T &value, const U mode){
    T OldValue = value;
    int v      = value / mode;
    value     -= v * mode;
    return OldValue;
}
