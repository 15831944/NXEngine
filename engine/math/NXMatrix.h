/*
 *  File:    Matrix.h
 *  author:  张雄
 *  date:    2016_02_23
 *  purpose: 用于定义3d数学的matrix，注意，此matrix只适合于存储简单的内置基本类型，存放class和struct类型，请不要使用
 */

#ifndef __ZX_NXENGINE_MATRIX_H__
#define __ZX_NXENGINE_MATRIX_H__

#include "NXNumeric.h"
#include "NXVector.h"
#include "NXMath.h"

namespace NX {
    template<typename T, int Row, int Col>
    class Matrix{
    public:
        template<typename U>
        inline Matrix(const Matrix<U, Row, Col> &rhs);
        inline Matrix(const Matrix &rhs);
        inline Matrix();
        inline Matrix(const T *ptr);
        template<typename U>
        inline Matrix(const vector<U, Col> *v);
        template<typename U>
        inline Matrix(const U (&ary)[Row][Col]);
    public:
        template<typename U>
        inline Matrix<T, Row, Col>& operator += (const Matrix<U, Row, Col> &rhs);
        
        template<typename U>
        inline Matrix<T, Row, Col>& operator -= (const Matrix<U, Row, Col> &rhs);
        
        inline Matrix<T, Row, Col>& operator += (const T &value);
        
        inline Matrix<T, Row, Col>& operator -= (const T &value);
        
        inline Matrix<T, Row, Col>& operator *= (const T &value);
        
        inline Matrix<T, Row, Col>& operator /= (const T &value);
        
        inline Matrix<T, Row, Col>& Transpose();
        
        template<typename U>
        inline Matrix<T, Row, Col>& MultiRow(int row, const U value);
        
        template<typename U>
        inline Matrix<T, Row, Col>& MultiCol(int col, const U value);
        
        template<typename U>
        inline Matrix<T, Row, Col>& AddRow(int row, const U value);
        
        template<typename U>
        inline Matrix<T, Row, Col>& AddCol(int col, const U value);
        
        //row[second] += row[first]
        inline Matrix<T, Row, Col>& AddOneRowToAnother(const int first, const int second);
        
        //row[second] += row[first] * factor;
        inline Matrix<T, Row, Col>& AddOneRowToAnotherByFactor(const int first, const int second, const T factor);
        
        //col[second] += col[first]
        inline Matrix<T, Row, Col>& AddOneColToAnother(const int first, const int second);
        
        //col[second] += col[first] * factor
        inline Matrix<T, Row, Col>& AddOneColToAnotherByFactor(const int first, const int second, const T factor);
        
        //row[second] = row[first] && clear(row[first])
        inline Matrix<T, Row, Col>& MoveOnRowToAnother(const int first, const int second);
        
        //col[second] = col[first] && clear(col[first])
        inline Matrix<T, Row, Col>& MoveOneColToAnother(const int first, const int second);
        
        //row[second] = row[first] but not clear(row[first])
        inline Matrix<T, Row, Col>& SetOneRowWithAnother(const int first, const int second);
        
        //col[second] = col[first] but not clear(col[first])
        inline Matrix<T, Row, Col>& SetOneColWithAnother(const int first, const int second);
        
        inline T (&operator [] (int index))[Col];
        inline const T (&operator [] (int index) const)[Col];
    public:
        inline T& GetElement(int row, int col);
        
        inline Matrix<T, Row, Col>& SwapRow(int first, int second);
        
        inline Matrix<T, Row, Col>& SwapCol(int first, int second);
        
        template<typename U, int Scale>
        inline Matrix<T, Row, Col>& SetRow(int row, const vector<U, Scale> &rhs);
        
        template<typename U>
        inline Matrix<T, Row, Col>& SetRow(int row, const U *ptr);
        
        inline Matrix<T, Row, Col>& SetRow(int row, const T value);
        
        template<typename U, int Scale>
        inline Matrix<T, Row, Col>& SetRow(int row, U (&ary)[Scale]);
        
        template<typename U, int Scale>
        inline Matrix<T, Row, Col>& SetCol(int col, const vector<U, Scale> &rhs);
        
        inline Matrix<T, Row, Col>& SetCol(int col, const T value);
        
        template<typename U>
        inline Matrix<T, Row, Col>& SetCol(int col, const U *ptr);
        
        template<typename U, int Scale>
        inline Matrix<T, Row, Col>& SetCol(int col, U (&ary)[Scale]);
        inline int GetRowCount(){
            return Row;
        }
        
        inline int GetColCount(){
            return Col;
        }
    public:
        T m_Element[Row][Col];
    };
    
    //==============================================begin nomember function=============================================
    
    template<typename T, int M, int N, typename U, int K, typename RT = T>
    inline Matrix<RT, M, K> operator * (const Matrix<T, M, N> &lhs, const Matrix<U, N, K> &rhs);
    
    template<typename T, int M, int N, typename U, typename RT = T>
    inline vector<RT, N> operator * (const vector<T, M> &lhs, const Matrix<U, M, N> &rhs);
    
    template<typename T, int M, int N, typename U, typename RT = T>
    inline Matrix<RT, M, 1> operator * (const Matrix<U, M, N> &lhs, const vector<T, N> &rhs);
    
    //==============================================end of nomember function============================================
#include "NXMatrix.inl"
    
}

#endif  //!__ZX_NXENGINE_MATRIX_H__