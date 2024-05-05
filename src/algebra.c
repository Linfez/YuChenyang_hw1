#include "algebra.h"
#include <stdio.h>
#include <math.h>

Matrix create_matrix(int row, int col)
{
    Matrix m;
    m.rows = row;
    m.cols = col;
    return m;
}

/**
 * @brief 矩阵加法
 * @param a 矩阵a
 * @param b 矩阵b
 * @return a + b, 如果a和b的行数或列数不相等，会给出错误提示"Error: Matrix a and b must have the same rows and cols.\n"并返回一个空矩阵
 */

Matrix add_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.cols || a.rows != b.rows)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        int rows, cols;
        rows = a.rows;
        cols = a.cols;
        Matrix c = create_matrix(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                c.data[i][j] = a.data[i][j] + b.data[i][j];
            }
        }
        return c;
    }
}

Matrix sub_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.cols || a.rows != b.rows)
    {
        printf("Error: Matrix a and b must have the same rows and cols.\n");
        return create_matrix(0, 0);
    }
    else
    {
        int rows, cols;
        rows = a.rows;
        cols = a.cols;
        Matrix c = create_matrix(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                c.data[i][j] = a.data[i][j] - b.data[i][j];
            }
        }
        return c;
    }
}

/**
 * @brief 矩阵乘法
 * @param a 矩阵a
 * @param b 矩阵b
 * @return a * b，如果a的列数不等于b的行数，会给出错误提示"Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n"并返回一个空矩阵
 */

Matrix mul_matrix(Matrix a, Matrix b)
{
    if (a.cols != b.rows)
    {
        printf("Error: The number of cols of matrix a must be equal to the number of rows of matrix b.\n");
        return create_matrix(0, 0);
    }
    else
    {
        int rows, cols;
        rows = a.rows;
        cols = b.cols;
        Matrix c = create_matrix(rows, cols);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                c.data[i][j] = 0;
                for (int k = 0; k < a.cols; k++)
                {
                    c.data[i][j] += a.data[i][k] * b.data[k][j];
                }
            }
        }
        return c;
    }
}

Matrix scale_matrix(Matrix a, double k)
{
    int rows, cols;
    rows = a.rows;
    cols = a.cols;
    Matrix c = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            c.data[i][j] = a.data[i][j] * k;
        }
    }
    return c;
}

Matrix transpose_matrix(Matrix a)
{
    int rows, cols;
    rows = a.rows;
    cols = a.cols;
    Matrix c = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            c.data[i][j] = a.data[j][i];
        }
    }
    return c;
}

double power(double num, int i)
{
    if (i == 1)
        return num;
    else if (i == 0)
        return 1;
    else
    {
        return num * pow(num, i - 1);
    }
}

Matrix minor_matrix(Matrix a, int rows, int cols)
{
    Matrix minor = create_matrix(a.rows - 1, a.cols - 1);
    int mrows = 0;
    for (int i = 0; i < a.rows; i++)
    {
        if (i == rows)
            continue;
        int mcols = 0; // 初始化mcols变量
        for (int j = 0; j < a.cols; j++)
        {
            if (j == cols)
                continue;
            minor.data[mrows][mcols] = a.data[i][j];
            mcols++;
        }
        mrows++; // 更新mrows变量
    }
    return minor;
}

double det_matrix(Matrix a)
{
    if (a.cols != a.rows)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else
    {
        if (a.cols == 1)
        {
            return a.data[0][0];
        }
        else if (a.cols == 2)
        {
            double det = (a.data[0][0] * a.data[1][1] - a.data[0][1] * a.data[1][0]);
            return det;
        }
        else if (a.cols == 3)
        {
            double det = a.data[0][0] * a.data[1][1] * a.data[2][2] + a.data[0][1] * a.data[1][2] * a.data[2][0] + a.data[1][0] * a.data[2][1] * a.data[0][2] - a.data[0][2] * a.data[1][1] * a.data[2][0] - a.data[0][1] * a.data[1][0] * a.data[2][2] - a.data[1][2] * a.data[2][1] * a.data[0][0];
            return det;
        }
        else
        {
            double det = 0;
            int j = 0;
            for (int i = 0; i < a.cols; i++)
            {
                Matrix minor = minor_matrix(a, i, j);
                /*print_matrix(minor);
                printf("\n");
                检测minor函数*/
                if ((i + j) % 2 == 0)
                    det += a.data[i][j] * det_matrix(minor);
                else
                    det += (-1) * a.data[i][j] * det_matrix(minor);
                // printf("%.2f\n", det);
            }
            return det;
        }
    }
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    return create_matrix(0, 0);
}

int rank_matrix(Matrix a)
{
    // ToDo
    return 0;
}

double trace_matrix(Matrix a)
{
    if (a.cols != a.rows)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else
    {
        double tr = 0;
        for (int i = 0; i < a.rows; i++)
        {
            tr += a.data[i][i];
        }
        return tr;
    }
}

void print_matrix(Matrix a)
{
    for (int i = 0; i < a.rows; i++)
    {
        for (int j = 0; j < a.cols; j++)
        {
            // 按行打印，每个元素占8个字符的宽度，小数点后保留2位，左对齐
            printf("%-8.2f", a.data[i][j]);
        }
        printf("\n");
    }
}