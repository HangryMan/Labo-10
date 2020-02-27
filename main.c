#include <stdio.h>
#include <stdlib.h>

//ПРОТОТИПЫ==========================================================================
void printMatrix(void);
unsigned int normal(unsigned int);
unsigned int sum(unsigned int);
unsigned int notZeroIndex(unsigned int);
void convertToTriangularMatrix(void);
void calcVars(void);
short getYesNoVariant(void);
//ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ==============================================================
unsigned int numOfEquations = 3, numOfVars = 4;
short debugInfo = 0;
float matrix[3][4] =    {{0.14, 0.24, -0.84, 1.11},
                         {1.07, -0.83, 0.56, 0.48},
                         {0.64, 0.43, -0.38, -0.83}};
//MAIN===============================================================================
int main(int argc, char const *argv[]) {
    puts("Выводить промежуточные значения матрицы для ручной проверки? (y/n)");
    if (getYesNoVariant()) debugInfo = 1;
    system("cls");

    puts("\tДанная матрица:");
    printMatrix();

    convertToTriangularMatrix();
    calcVars();

    for (int i = 1; i < numOfVars; ++i) {
        printf("Var#%d = %.4f\n", i, matrix[i-1][numOfVars - 1]);
    }
    system("pause");
    return 0;
}
//ФУНКЦИИ============================================================================
void printMatrix(void) {
    for (int i = 0; i < numOfEquations; ++i) {
        for (int j = 0; j < numOfVars; ++j) {
            printf("%8.4f", matrix[i][j]);
        }
        puts("");
    }
    puts("");
//    getchar();
}
unsigned int normal(unsigned int indexOfEquation) {
    float div = matrix[indexOfEquation][notZeroIndex(indexOfEquation)];

    for (unsigned int j = notZeroIndex(indexOfEquation); j < numOfVars; ++j) {
        matrix[indexOfEquation][j] /= div;
    }
}
unsigned int sum(unsigned int indexOfEquation) {
    for (unsigned int i = indexOfEquation + 1; i < numOfEquations; ++i) {
        float multipr = matrix[i][notZeroIndex(i)];
        for (unsigned int j = notZeroIndex(indexOfEquation); j < numOfVars; ++j) {
            matrix[i][j] += matrix[indexOfEquation][j] * -multipr;
        }
    }
}
unsigned int notZeroIndex(unsigned int indexOfEquation) {
    for (int j = 0; j < numOfVars; ++j) {
        if (matrix[indexOfEquation][j] != 0) return j;
    }
}
void convertToTriangularMatrix(void) {

    normal(0);
    if (debugInfo) puts(" Привидение к треугольной матрице:");
    if (debugInfo) printMatrix();
    for (int q = 0; matrix[numOfEquations - 1][numOfVars - 2] != 1; ++q) {
        sum(q);
        if (debugInfo) printMatrix();
        normal(q + 1);
        if (debugInfo) printMatrix();
    }
}
void calcVars(void) {
    if (debugInfo) puts("   Рассчёт значений переменных:");
    for (int i = (int)numOfEquations - 2; i >= 0 ; --i) {
        for (unsigned int j = numOfVars - 2; j > 0 ; --j) {
            if (matrix[i][j] == 1 && matrix[i][j - 1] == 0) break;
            matrix[i][numOfVars - 1] -= matrix[i][j] * matrix[j][numOfVars - 1];
            matrix[i][j] = 0;
            if (debugInfo) printMatrix();
        }
    }
}
short getYesNoVariant(void) {
    char variant = 0;
    while (1) {
        variant = (char)getchar();
        fflush(stdin);
        if (variant == 'y' || variant == 'Y' || variant == '+') {
            return 1;
        } else if (variant == 'n' || variant == 'N' || variant == '-') {
            return 0;
        } else puts("Неверный ввод. Допустимые значения: y, Y, Yes, yes; n, N, No, no; +, -");
    }
}