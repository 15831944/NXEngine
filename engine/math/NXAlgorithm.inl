/*
 *  File:    NXAlgorithm.inl
 *  author:  张雄
 *  date:    2016_05_27
 *  purpose: 一些与matrix，vector，quaternion相关的算法
 */
#ifndef __ZX_NXENGINE_ALGORITHM_INL__
#define __ZX_NXENGINE_ALGORITHM_INL__

template<typename T, typename U, int Scale, typename RT>
inline RT Dot (const vector<T, Scale> &lhs, const vector<U, Scale> &rhs){
    RT sum = 0;
    for(int i = 0; i < Scale; ++i){
        sum += lhs.v[i] * rhs.v[i];
    }
    return sum;
}

template<typename T, typename U, typename RT>
inline vector<RT, 3> Cross(const vector<T, 3> &lhs, const vector<U, 3> &rhs){
    return vector<RT, 3>(lhs.v[1] * rhs.v[2] - lhs.v[2] * rhs.v[1],
                         lhs.v[2] * rhs.v[0] - lhs.v[0] * rhs.v[2],
                         lhs.v[0] * rhs.v[1] - rhs.v[0] * lhs.v[1]);
}


template<typename T, int Scale, typename RT>
inline RT Length(const vector<T, Scale> &lhs){
    return std::sqrt(LengthSquare(lhs));
}

template<typename T, int Scale, typename RT>
inline RT LengthSquare(const vector<T, Scale> &lhs){
    RT Sum = 0.0;
    for(int i = 0; i < Scale; ++i){
        Sum += (lhs.v[i] * lhs.v[i]);
    }
    return Sum;
}

template<typename T, int Scale>
inline vector<T, Scale> GetNormalize(const vector<T, Scale> &lhs){
    vector<T, Scale> n(lhs);
    return Normalize(n);
}

template<typename T, int Scale>
vector<T, Scale>& Normalize(vector<T, Scale> &lhs){
    T v = Length(lhs);
    for(int i = 0; i < Scale; ++i){
        lhs.v[i] /= v;
    }
    return lhs;
}

template<typename TA, typename TB, int Scale, typename RT>
inline vector<RT, Scale> Lerp(const vector<TA, Scale> &lhs, const vector<TB, Scale> &rhs, const float t){
    vector<RT, Scale> result;
    RT a = 1 - t, b = t;
    for(int i = 0; i < Scale; ++i){
        result[i] = lhs[i] * a + rhs[i] * b;
    }
    return result;
}

template<typename T, int Scale>
inline vector<T, Scale> GetNegative(const vector<T, Scale> &lhs){
    return Negative(vector<T, Scale>(lhs));
}

template<typename T, int Scale>
inline vector<T, Scale>& Negative(vector<T, Scale> &lhs){
    return -lhs;
}

template<typename T, typename U>
inline vector<T, 2>& Project(vector<T, 2> &lhs, const vector<U, 2> &normal){
    vector<T, 2> n(normal);
    Normalize(n);
    T nxx = 1 - n.x * n.x, nyy = 1 - n.y * n.y, nxy = -n.x * n.y;
    return lhs = vector<T, 2>(
                              nxx * lhs[0] + nxy * lhs[1],
                              nxy * lhs[0] + nyy * lhs[1]);
}

template<typename T, typename U>
inline vector<T, 3>& Project(vector<T, 3> &lhs, const vector<U, 3> &normal){
    vector<T, 3> n(normal);
    Normalize(n);
    T nxx = 1 - n.x * n.x, nyy = 1 - n.y * n.y, nzz = 1 - n.z * n.z, nxy = -n.x * n.y, nyz = -n.y * n.z, nzx = -n.z * n.x;
    return lhs = vector<T, 3>(
                              nxx * lhs[0] + nxy * lhs[1] + nzx * lhs[2],
                              nxy * lhs[0] + nyy * lhs[1] + nyz * lhs[2],
                              nzx * lhs[0] + nyz * lhs[1] + nzz * lhs[2]
                              );
}

template<typename  T, typename U, typename RT>
inline vector<RT, 2> GetProject(const vector<T, 2> &lhs, const vector<U, 2> &normal){
    return Project(vector<RT, 2>(lhs), normal);
}

template<typename  T, typename U, typename RT>
inline vector<RT, 3> GetProject(const vector<T, 3> &lhs, const vector<U, 3> &normal){
    return Project(vector<RT, 3>(lhs), normal);
}

/**
 *   求点位于沿直线方向上的缩放(其中direction是方向向量，且默认直线或平面过原点）
 */
template<typename T, typename U>
inline vector<T, 2>& Scale(vector<T, 2> &lhs, const vector<U, 2> &direction, const float s){
    vector<T, 2> n(direction);
    Normalize(n);
    T nxx = 1 + (s - 1) * n.x * n.x, nxy = (s - 1) * n.x * n.y, nyy = 1 + (s - 1) * n.y * n.y;
    return lhs = vector<T, 2>(
                              nxx * lhs[0] + nxy * lhs[1],
                              nxy * lhs[0] + nyy * lhs[1]
                              );
}

template<typename T, typename U>
inline vector<T, 3>& Scale(vector<T, 3> &lhs, const vector<U, 3> &direction, const float s){
    vector<T, 3> n(direction);
    Normalize(n);
    T nxx = 1 + (s - 1) * n.x * n.x,  nyy = 1 + (s - 1) * n.y * n.y, nzz = 1 + (s - 1) * n.z * n.z;
    T nxy = (s - 1) * n.x * n.y, nyz = (s - 1) * n.y * n.z, nzx = ( s - 1) * n.z * n.x;
    return lhs = vector<T, 3>(
                              nxx * lhs[0] + nxy * lhs[1] + nzx * lhs[2],
                              nxy * lhs[0] + nyy * lhs[1] + nyz * lhs[2],
                              nzx * lhs[0] + nyz * lhs[1] + nzz * lhs[2]
                              );
}

template<typename T, typename U, typename RT>
inline vector<RT, 2> GetScale(const vector<T, 2> &lhs, const vector<U, 2> &direction, const float s){
    return Scale(vector<RT, 2>(lhs), direction, s);
}

template<typename T, typename U, typename RT>
inline vector<RT, 3> GetScale(const vector<T, 3> &lhs, const vector<U, 3> &direction, const float s){
    return Scale(vector<RT, 3>(lhs), direction, s);
}

template<typename T, int M>
inline Matrix<T, M, M>& Transpose(Matrix<T, M, M> &lhs){
    for(int i = 0; i < M; ++i){
        for(int j = 0; j < M; ++j){
            std::swap(lhs[i][j], lhs[j][i]);
        }
    }
}

template<typename T, int Row, int Col>
inline Matrix<T, Col, Row> GetTranspose(const Matrix<T, Row, Col> &lhs){
    Matrix<T, Col, Row> result;
    for(int i = 0; i < Row; ++i){
        result.SetCol(i, lhs[i]);
    }
    return result;
}

template<typename U, typename T>
inline Matrix<T, 4, 4> LookAt(const vector<U, 3> &eye, const vector<U, 3> &look, const vector<U, 3> &up){
    vector<T, 3> oz = look - eye;
    Normalize(oz);
    vector<T, 3> ox = Cross(up, oz);
    Normalize(ox);
    vector<T, 3> oy = Cross(oz, ox);
    Normalize(oy);
    vector<T, 3> oo = eye;
    
    Matrix<T, 4, 4> result;
    result.SetRow(0, ox);
    result.SetRow(1, oy);
    result.SetRow(2, oz);
    result[0][3] = -Dot(oo, ox);
    result[1][3] = -Dot(oo, oy);
    result[2][3] = -Dot(oo, oz);
    result[3][3] = T(1);
    return result;
}

template<typename T>
inline Matrix<T, 4, 4> Translate(const T dx, const T dy, const T dz){
    Matrix<T, 4, 4> result;
    result[0][0] = result[1][1] = result[2][2] = result[3][3] = T(1);
    result[0][3] = dx;
    result[1][3] = dy;
    result[2][3] = dz;
    return result;
}

template<typename T, int Scale>
inline Matrix<T, Scale, Scale> RotateX(const T radian){
    NXAssert(Scale == 3 || Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CosValue(std::cos(radian));
    T SinValue(std::sin(radian));
    result.m_Element[Scale - 1][Scale - 1] = T(1);
    result.m_Element[0][0] = T(1);
    result.m_Element[1][1] = CosValue, result.m_Element[1][2] = -SinValue;
    result.m_Element[2][1] = SinValue, result.m_Element[2][2] = CosValue;
    return result;
}

template<typename T, int Scale>
inline Matrix<T, Scale, Scale> RotateY(const T radian){
    NXAssert(Scale == 3 || Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CosValue(std::cos(radian));
    T SinValue(std::sin(radian));
    result.m_Element[Scale - 1][Scale - 1] = T(1), result.m_Element[1][1] = T(1);
    result.m_Element[0][0] = CosValue, result.m_Element[0][2]  = SinValue;
    result.m_Element[2][0] = -SinValue, result.m_Element[2][2] = CosValue;
    return result;
}

template<typename T, int Scale>
inline Matrix<T, Scale, Scale> RotateZ(const T radian){
    NXAssert(Scale == 3 || Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CosValue(std::cos(radian));
    T SinValue(std::sin(radian));
    result.m_Element[Scale - 1][Scale - 1] = T(1), result.m_Element[2][2] = T(1);
    result.m_Element[0][0] = CosValue, result.m_Element[0][1] = -SinValue;
    result.m_Element[1][0] = SinValue, result.m_Element[1][1] = CosValue;
    return result;
}

template<typename T, int Scale>
inline Matrix<T, Scale, Scale> Scalar(const T sx, const T sy, const T sz){
    Matrix<T, Scale, Scale> result;
    result.m_Element[Scale - 1][Scale - 1] = T(1);
    result.m_Element[0][0] = sx;
    result.m_Element[1][1] = sy;
    result.m_Element[2][2] = sz;
    return result;
}

template<typename T, int Scale, typename U>
inline Matrix<T, Scale, Scale> RotateAix(const vector<U, 3> &Aix, const T radian){
    vector<T, 3> ax(Aix);
    Normalize(ax);
    T nxx = ax.x * ax.x;
    T nyy = ax.y * ax.y;
    T nzz = ax.z * ax.z;
    T nxy = ax.x * ax.y;
    T nyz = ax.y * ax.z;
    T nzx = ax.z * ax.x;
    T CosValue  = std::cos(radian);
    T SinValue  = std::sin(radian);
    T OneMinCos = T(1) - CosValue;
    Matrix<T, Scale, Scale> result;
    result.m_Element[Scale -1 ][Scale - 1] = T(1);
    result.m_Element[0][0] = nxx * OneMinCos + CosValue;
    result.m_Element[1][0] = nxy * OneMinCos + ax.z * SinValue;
    result.m_Element[2][0] = nzx * OneMinCos - ax.y * SinValue;
    result.m_Element[0][1] = nxy * OneMinCos - ax.z * SinValue;
    result.m_Element[1][1] = nyy * OneMinCos + CosValue;
    result.m_Element[2][1] = nyz * OneMinCos + ax.x * SinValue;
    result.m_Element[0][2] = nzx * OneMinCos + ax.y * SinValue;
    result.m_Element[1][2] = nyz * OneMinCos - ax.x * SinValue;
    result.m_Element[2][2] = nzz * OneMinCos + CosValue;
    return result;
}

//x/w: [-1, 1]
//y/w: [-1, 1]
//z/w: [0, 1]
//w: z
template<typename T, int Scale>
inline Matrix<T, Scale, Scale> Perspective(const T FovAngle, const T aspect, const T near, const T far){
    NXAssert(Scale == 4);
    Matrix<T, Scale, Scale> result;
    T CotValue = 1 / std::tan(DG2RD(FovAngle) / 2);
    T dif = near - far;
    T a = -far / dif;
    T b = near * far / dif;
    result.m_Element[0][0] = 1 / aspect * CotValue;
    result.m_Element[1][1] = CotValue;
    result.m_Element[2][2] = a;
    result.m_Element[2][3] = b;
    result.m_Element[3][2] = T(1);
    return result;
}

//x: [-1, 1]
//y: [-1, 1]
//z: [0, 1]
//w: 1
template<typename T, int Scale>
inline Matrix<T, Scale, Scale> Orthogonal(const T Width, const T Height, const T near, const T far){
    NXAssert(Scale == 4);
    Matrix<T, Scale, Scale> result;
    result.m_Element[Scale - 1][Scale - 1] = T(1);
    result.m_Element[0][0] = 2 / Width;
    result.m_Element[1][1] = 2 / Height;
    const T dif = far - near;
    const T a   = 1 / dif;
    const T b   = -near / dif;
    result.m_Element[2][2] = a;
    result.m_Element[2][3] = b;
    return result;
}

template<typename T, typename RT>
inline RT Detaminate(const Matrix<T, 2, 2>& matrix){
    RT result(matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    return result;
}

template<typename T, typename RT>
inline RT Detaminate(const Matrix<T, 3, 3>& matrix){
    NX::vector<T, 3> a(matrix[0][0], matrix[0][1], matrix[0][2]);
    NX::vector<T, 3> b(matrix[1][0], matrix[1][1], matrix[1][2]);
    NX::vector<T, 3> c(matrix[2][0], matrix[2][1], matrix[2][2]);
    return RT(Dot(c, Cross(a, b)));
}

template<typename T, int Scale, typename RT>
inline RT Detaminate(const Matrix<T, Scale, Scale> &matrix){
    Matrix<RT, Scale, Scale> M(matrix);
    unsigned int iSwapCount = 0;
    {//gauss - jordan method
        int iSelRow = 0;
        for(int c = 0; c < Scale; ++c){
            iSelRow = c;
            for(int i = c + 1; i < Scale; ++i){//select pivot row for numeric stability
                if(NX::NXAbs(M[iSelRow][c]) < NX::NXAbs(M[i][c])){
                    iSelRow = i;
                }
            }
            if(iSelRow != c){
                M.SwapRow(iSelRow, c);
                ++iSwapCount;
            }
            if(NXAbs(M[c][c]) < Epsilon<RT>::m_Epsilon){
                return RT(0);
            }
            for(int i = c+ 1; i < Scale; ++i){
                M.AddOneRowToAnotherByFactor(c, i, -M[i][c] / M[c][c]);
            }
        }
    }
    RT result(1);
    for(int i = 0; i < Scale; ++i){
        result *= M[i][i];
    }
    return iSwapCount & 1 ? -result : result;
}

template<typename T, typename RT>
inline RT Detaminate(const Matrix<T, 4, 4> &matrix){
    RT result(0);
    {//M{0, 0}
        Matrix<T, 3, 3> m;
        m.SetRow(0, &matrix[1][1]);
        m.SetRow(1, &matrix[2][1]);
        m.SetRow(2, &matrix[3][1]);
        result += matrix[0][0] * Detaminate(m);
    }
    
    {//M{1, 0}
        Matrix<T, 3, 3> m;
        m.SetRow(0, &matrix[0][1]);
        m.SetRow(1, &matrix[2][1]);
        m.SetRow(2, &matrix[3][1]);
        result -= matrix[1][0] * Detaminate(m);
    }
    
    {//M{2, 0}
        Matrix<T, 3, 3> m;
        m.SetRow(0, &matrix[0][1]);
        m.SetRow(1, &matrix[1][1]);
        m.SetRow(2, &matrix[3][1]);
        result += matrix[2][0] * Detaminate(m);
    }
    
    {//M{3, 0}
        Matrix<T, 3, 3> m;
        m.SetRow(0, &matrix[0][1]);
        m.SetRow(1, &matrix[1][1]);
        m.SetRow(2, &matrix[2][1]);
        result -= matrix[3][0] * Detaminate(m);
    }
    return result;
}

template<typename T, typename RT>
inline Matrix<RT, 2, 2> Reverse(const Matrix<T, 2, 2>& matrix){
    Matrix<RT, 2, 2> result = matrix;
    RT det = Detaminate<T, RT>(matrix);
    result[0][1] = - result[0][1];
    result[1][0] = - result[1][0];
    result /= det;
    return result;
}

template<typename T, typename RT>
inline Matrix<RT, 3, 3> Reverse(const Matrix<T, 3, 3>& matrix){
    Matrix<RT, 3, 3> result;
    RT det = Detaminate(matrix);
    if(NX::NXAbs(det) < Epsilon<T>::m_Epsilon){//to small
        return result;
    }
    
    {//first row
        result[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
        result[0][1] = matrix[1][2] * matrix[2][0] - matrix[1][0] * matrix[2][2];
        result[0][2] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
    }
    
    {//second row
        result[1][0] = matrix[0][2] * matrix[2][1] - matrix[0][1] * matrix[2][2];
        result[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
        result[1][2] = matrix[0][1] * matrix[2][0] - matrix[0][0] * matrix[2][1];
    }
    
    {//third row
        result[2][0] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
        result[2][1] = matrix[0][2] * matrix[1][0] - matrix[0][0] * matrix[1][2];
        result[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }
    result /= det;
    Transpose(result);
    return result;
}


template<typename T, typename RT>
inline Matrix<RT, 4, 4> Reverse(const Matrix<T, 4, 4> &matrix){
    Matrix<RT, 4, 8> m;
    {//init m = {matrix, I};
        m[0][4] = 1, m[1][5] = 1, m[2][6] = 1, m[3][7] = 1;
        m.template SetRow<T, 4>(0, matrix[0]);
        m.template SetRow<T, 4>(1, matrix[1]);
        m.template SetRow<T, 4>(2, matrix[2]);
        m.template SetRow<T, 4>(3, matrix[3]);
    }
    
    if(NX::NXAbs(Detaminate(matrix)) < Epsilon<T>::m_Epsilon){
        return matrix;
    }
    
    {//gauss - jordan method
        int iSelRow = 0;
        for(int c = 0; c < 4; ++c){
            iSelRow = c;
            for(int i = c + 1; i < 4; ++i){//select pivot row
                if(NX::NXAbs(m[iSelRow][c]) < NX::NXAbs(m[i][c])){
                    iSelRow = i;
                }
            }
            if(iSelRow != c){
                m.SwapRow(iSelRow, c);
            }
            for(int i = 0; i < 4; ++i){
                if(i == c){
                    continue;
                }
                m.AddOneRowToAnotherByFactor(c, i, -m[i][c] / m[c][c]);
            }
            m.MultiRow(c, 1 / m[c][c]);
        }
    }
    
    Matrix<RT, 4, 4> result;
    {//copy back
        result.SetRow(0, &m[0][4]);
        result.SetRow(1, &m[1][4]);
        result.SetRow(2, &m[2][4]);
        result.SetRow(3, &m[3][4]);
    }
    return result;
}

template<typename T, int Scale, typename RT>
inline Matrix<RT, Scale, Scale> Reverse(const Matrix<T, Scale, Scale> &matrix){
    Matrix<RT, Scale, (Scale << 1)> M;
    for(int i = 0; i < Scale; ++i){
        M.template SetRow<T, Scale>(i, matrix[i]);
        M[i][i + Scale] = 1;
    }
    {//gauss - jordan method
        int iSelRow = 0;
        for(int c = 0; c < Scale; ++c){
            iSelRow = c;
            for(int i = c + 1; i < Scale; ++i){//select pivot row
                if(NX::NXAbs(M[iSelRow][c]) < NX::NXAbs(M[i][c])){
                    iSelRow = i;
                }
            }
            if(iSelRow != c){
                M.SwapRow(iSelRow, c);
            }
            for(int i = 0; i < Scale; ++i){
                if(i == c){
                    continue;
                }
                M.AddOneRowToAnotherByFactor(c, i, -M[i][c] / M[c][c]);
            }
            M.MultiRow(c, 1 / M[c][c]);
        }
    }
    
    Matrix<RT, Scale, Scale> result;
    {//copy back
        for(int i = 0; i < Scale; ++i){
            result.SetRow(i, &M[i][Scale]);
        }
    }
    return result;
}

template<typename T, int Scale, typename RT>
inline std::pair<bool, Matrix<RT, Scale, Scale> > ReverseSafe(const Matrix<T, Scale, Scale> &matrix){
    Matrix<RT, Scale, (Scale << 1)> M;
    for(int i = 0; i < Scale; ++i){
        M.template SetRow<T, Scale>(i, matrix[i]);
        M[i][i + Scale] = 1;
    }
    {//gauss - jordan method
        int iSelRow = 0;
        for(int c = 0; c < Scale; ++c){
            iSelRow = c;
            for(int i = c + 1; i < Scale; ++i){//select pivot row
                if(NX::NXAbs(M[iSelRow][c]) < NX::NXAbs(M[i][c])){
                    iSelRow = i;
                }
            }
            if(iSelRow != c){
                M.SwapRow(iSelRow, c);
            }
            if(NXAbs(M[c][c]) < Epsilon<RT>::m_Epsilon){
                return std::make_pair(true, Matrix<RT, Scale, Scale>());
            }
            for(int i = 0; i < Scale; ++i){
                if(i == c){
                    continue;
                }
                M.AddOneRowToAnotherByFactor(c, i, -M[i][c] / M[c][c]);
            }
            M.MultiRow(c, 1 / M[c][c]);
        }
    }
    
    std::pair<bool, Matrix<RT, Scale, Scale> >result;
    {//copy back
        result.first = true;
        for(int i = 0; i < Scale; ++i){
            result.second.SetRow(i, &M[i][Scale]);
        }
    }
    return result;
}

/**
 *  zero some small elements such as 0.0000001
 */
template<typename T, int iScale>
inline Matrix<T, iScale, iScale>& SimplifyMatrix(Matrix<T, iScale, iScale> &matrix, const T EpsilonValue){
    for(int r = 0; r < iScale; ++r){
        for(int c = 0; c < iScale; ++c){
            if(NXAbs(matrix[r][c] < EpsilonValue)){
                matrix[r][c] = T(0);
            }
        }
    }
    return matrix;
}

/**
 *  返回点投影到直线(2维)或平面(3维)上的投影方程（其中normal是法线，且默认直线或平面过原点)
 */
template<typename  T, typename U, typename RT>
inline Matrix<RT, 2, 2> GetProjectMatrix(const vector<T, 2> &lhs, const vector<U, 2> &normal){
    Matrix<RT, 2, 2> result;
    vector<RT, 2> n(normal);
    Normalize(n);
    result[0][0] = 1 - n.x * n.x,    result[0][1] =    -n.x * n.y;
    result[1][0] =    -n.y * n.x,    result[1][1] = 1 - n.y * n.y;
    return result;
}

template<typename  T, typename U, typename RT>
inline Matrix<RT, 3, 3> GetProjectMatrix(const vector<T, 3> &lhs, const vector<U, 3> &normal){
    Matrix<RT, 3, 3> result;
    vector<RT, 3> n(normal);
    Normalize(n);
    result[0][0] = 1 - n.x * n.x,    result[0][1] =    -n.x * n.y,    result[0][2] =   -n.x * n.z;
    result[1][0] =    -n.y * n.x,    result[1][1] = 1 - n.y * n.y,    result[1][2] =   -n.y * n.z;
    result[2][0] =    -n.z * n.x,    result[2][1] =    -n.z * n.y,    result[2][2] = 1 -n.z * n.z;
    return result;
}

template<typename T, typename U, typename RT>
inline Matrix<RT, 2, 2> GetScaleMatrix(const vector<T, 2> &lhs, const vector<U, 2> &direction, const float s){
    Matrix<RT, 2, 2> result;
    vector<RT, 2> n(direction);
    Normalize(n);
    result[0][0] = 1 + (s - 1) * n.x * n.x,  result[0][1] = (s - 1) * n.x * n.y;
    result[1][0] =     (s - 1) * n.x * n.y,  result[1][1] = 1 + (s - 1) * n.y * n.y;
    return result;
}

template<typename T, typename U, typename RT>
inline Matrix<RT, 3, 3> GetScaleMatrix(const vector<T, 3> &lhs, const vector<U, 3> &direction, const float s){
    Matrix<RT, 3, 3> result;
    vector<RT, 3> n(direction);
    Normalize(n);
    result[0][0] = 1 + (s - 1) * n.x * n.x, result[0][1] =     (s - 1) * n.x * n.y, result[0][2] =     (s - 1) * n.x * n.z;
    result[1][0] =     (s - 1) * n.y * n.x, result[1][1] = 1 + (s - 1) * n.y * n.y, result[1][2] =     (s - 1) * n.y * n.z;
    result[2][0] =     (s - 1) * n.z * n.x, result[2][1] =     (s - 1) * n.z * n.y, result[2][2] = 1 + (s - 1) * n.z * n.z;
    return result;
}
#endif //!__ZX_NXENGINE_ALGORITHM_INL__