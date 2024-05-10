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
    Matrix c = create_matrix(cols, rows);
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            c.data[j][i] = a.data[i][j];
        }
    }
    return c;
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

/*
拉普拉斯展开求行列式，效率不高

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
                检测minor函数

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
*/

// 高斯消元法求解行列式
double det_matrix(Matrix mat)
{
    if (mat.cols != mat.rows || mat.cols == 0 || mat.rows == 0)
    {
        printf("Error: The matrix must be a square matrix.\n");
        return 0;
    }
    else
    {
        double det = 1.0;
        int n = mat.rows;
        int sign = 1; // 用于追踪行交换，初始为正号

        for (int i = 0; i < n; i++)
        {
            // 寻找第i行到第n行中绝对值最大的行
            int maxRow = i;
            for (int k = i + 1; k < n; k++)
            {
                if (fabs(mat.data[k][i]) > fabs(mat.data[maxRow][i]))
                {
                    maxRow = k;
                }
            }
            // 如果发现主元为零，则行列式为零
            if (mat.data[maxRow][i] == 0.0)
                return 0;

            // 如果最大元不在当前行，交换行，并更改符号
            if (i != maxRow)
            {
                for (int j = 0; j < mat.cols; j++)
                {
                    double temp = mat.data[i][j];
                    mat.data[i][j] = mat.data[maxRow][j];
                    mat.data[maxRow][j] = temp;
                }
                sign *= -1; // 改变行列式的符号
            }

            for (int k = i + 1; k < n; k++)
            {
                double factor = mat.data[k][i] / mat.data[i][i];
                for (int j = i + 1; j < n; j++)
                {
                    // 高斯消元操作
                    mat.data[k][j] -= factor * mat.data[i][j];
                }
                mat.data[k][i] = 0;
            }
        }

        // 行列式是对角线元素的乘积
        for (int i = 0; i < n; i++)
        {
            det *= mat.data[i][i];
        }
        det = det * sign; // 考虑交换行引起的符号变化
        return det;
        return 0;
    }
}

Matrix inv_matrix(Matrix a)
{
    // ToDo
    return create_matrix(0, 0);
}

/**
 * @brief 矩阵的秩
 * @param a 矩阵a
 * @return a的秩
 */

int rank_matrix(Matrix a)
{
    /*
    int n = a.rows; // 行数
    int m = a.cols; // 列数
    int rank = 0;
    int row, col;

    // 用于标记哪些列已经有了主元素
    int *row_has_pivot = (int *)calloc(m, sizeof(int));

    // 高斯消元法开始
    for (row = 0, col = 0; row < n && col < m; col++)
    {
        // 找到绝对值最大的元素
        int maxRow = row;
        for (int k = row + 1; k < n; k++)
        {
            if (fabs(a.data[k][col]) > fabs(a.data[maxRow][col]))
            {
                maxRow = k;
            }
        }
        // 如果这一列全部都是零，就继续处理下一列
        if (fabs(a.data[maxRow][col]) <= 1e-10)
        {
            continue;
        }
        // 如果行与最大行元素不在同一行，交换
        if (row != maxRow)
        {
            for (int j = 0; j < m; j++)
            {
                double temp = a.data[row][j];
                a.data[row][j] = a.data[maxRow][j];
                a.data[maxRow][j] = temp;
            }
        }
        // 进行行变换，清零当前列的其他位置
        for (int i = 0; i < n; i++)
        {
            if (i != row)
            {
                double factor = a.data[i][col] / a.data[row][col];
                for (int j = col; j < m; j++)
                {
                    a.data[i][j] -= factor * a.data[row][j];
                }
            }
        }
        row_has_pivot[col] = 1; // 这一列已经有主元素了
        row++;
    }

    // 根据row_has_pivot数组来统计秩
    for (int j = 0; j < m; j++)
    {
        if (row_has_pivot[j])
        {
            rank++;
        }
    }

    free(row_has_pivot);
    return rank;
    */
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
        double tr = 0.0;
        for (int i = 0; i < a.rows; i++)
        {
            tr += a.data[i][i];
        }
        return tr;
    }
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