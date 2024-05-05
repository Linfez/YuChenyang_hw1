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

double det_matrix(Matrix a)
{
    // ToDo
    return 0;
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
    // ToDo
    return 0;
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