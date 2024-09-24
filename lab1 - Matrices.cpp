#include <iostream>
#include <chrono>
#include <math.h>
#define MAX 6000
using namespace std::chrono;

void fill(int matrix[][MAX], bool zero)
{
    for(int i = 0; i < MAX;i++)
    {
        for(int j = 0;j < MAX;j++)
        {
            if(zero)
            {
                matrix[i][j] = 0;
            }
            else if(!zero)
            {
                matrix[i][j] = rand() % 30;
            }
        }
    }
}
void print(int  matrix[][MAX])
{
    for(int i = 0;i < MAX;i++)
    {
        for(int j = 0;j < MAX;j++)
        {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}
void blockMatrixMultiplication(int  mat1[][MAX],
    int  mat2[][MAX], int  result[][MAX], int blockSize)
{
    for(int i = 0; i < MAX; i += blockSize)
        for(int j = 0; j < MAX; j += blockSize)
            for(int k = 0; k < MAX; k += blockSize)
                for(int x = i; x < std::min(i + blockSize, MAX); x++)
                    for(int y = j; y < std::min(j + blockSize, MAX); y++)
                        for(int z = k; z < std::min(k + blockSize, MAX); z++)
                            result[x][y] += mat1[x][z] * mat2[z][y];
}
void matrix_multiplication(int  mat1[][MAX], int  mat2[][MAX],
    int  result[][MAX])
{
    for(int i = 0; i < MAX; i++)
    {
        for(int j = 0; j < MAX; j++)
        {
            for(int k = 0;k < MAX; k++)
            {
                result[i][j] += mat1[i][k]
                    * mat2[k][j];
            }
        }

    }
}
int matrix1[MAX][MAX];
int matrix2[MAX][MAX];
int result[MAX][MAX];
int main()
{
    srand(time(0));
    fill(matrix1, false);
    fill(matrix2, false);
    fill(result, true);
    int blockSize = round(sqrt(MAX));

    auto start = high_resolution_clock::now();
    matrix_multiplication(matrix1, matrix2, result);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    std::cout << "Test using matrix of size " << MAX << std::endl;
    std::cout << "Time taken by classic multiplication algorithm: "
        << duration.count() << " microseconds" << std::endl;

    fill(result, true);
    start = high_resolution_clock::now();
    blockMatrixMultiplication(matrix1, matrix2, result, blockSize);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    std::cout << "Time taken by block multiplication algorithm: "
        << duration.count() << " microseconds" << std::endl;
}