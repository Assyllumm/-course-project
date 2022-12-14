#include<cmath>
#include <iomanip>
#ifndef SHABL_KLASS_MATRIX_H
#define SHABL_KLASS_MATRIX_H
using namespace std;

/* Шаблон класса расширенной матрицы системы линейных алгебраических
 * уравнений
 * Поля класса (глобальные переменные класса):
 * M - квадратная матрица коэффициентов системы;
 * Y - массив свободных членов системы;
 * X - массив корней системы;
 * L - матрица, элементы которой рассчитаны по формулам разложения Холецкого;
 * Tr - транспонированная матрица;
 * Ly - массив значений y из уравнения Ly = b, где b - свободные члены системы;
 * n - размерность матрицы M.
 * Методы объекта класса:
 * SetElements - метод заполнения матрицы;
 * Print - метод вывода матрицы;
 * calculateGauss - метод, возвращающий корни системы, рассчитанные по методу
 * Гаусса;
 * Gauss - метод, выводящий результаты, рассчитанные по методу Гаусса;
 * SquareRoot - метод, выводящий корни системы, рассчитанные по методу
 * квадратных корней. */

template <class T>
class Matrix
{
private:                                        		// Объявление приватных переменных
			                                            // класса
    T **M;
    T *Y;
    T *X;
    T **L;
    T **Tr;
    T *Ly;
    int n;

public:                                     	// Описание публичных методов класса

    Matrix()                                	// Конструктор без параметров
    {
        n = 0;
        M = nullptr;                        	// Заполнение матрицы нулевыми
		// значениями
    };

    /* Конструктор с параметром, выделяющий память для квадратной матрицы M,
     * массива свободных членов Y и массива корней системы X
     * Формальный параметр:
     * _n - размерность формируемой матрицы
     * Локальные переменные:
     * i, j – счетчики.  */
    Matrix(int _n)
    {
        n = _n;
        M = (T**) new T *[n];               	// Формирование вектора указателей
        for (int i = 0; i <= n; i++){
            M[i] = (T*) new T [n];
        }

        Y = (T*) new T*[n];
    }

    /* Метод, заполняющий расширенную матрицу значениями
     * Локальные переменные:
     * value - значение, которое нужно записать в матрицу;
     * i, j - счетчики циклов.  */
    void SetElements()
    {
        cout << "Введите коэффициенты (в диапазоне от -100 до 100) : " << endl;
        T value;
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                cout << "m[" << i << "][" << j << "] = " ;
                cin >> value;
                if ((value < -100.0) or (value > 100.0))
                {
                    cout << "Ошибка: Вы вышли за границы диапазона значений" << endl;
                    abort();
                }
                M[i][j] = value;
            }
        }
        for (int i = 0; i < n; i++){
            cout << "y[" << i << "] = " ;
            cin >> value;
            if ((value < -100.0) or (value > 100.0))
            {
                cout << "Ошибка: Вы вышли за границы диапазона значений";
                abort();
            }
            Y[i] = value;
        }
        cout << endl << endl;
    }

    /* Метод, выводящий объект класса на экран
     * Формальный параметр:
     * ObjName - имя объекта класса, который нужно вывести.
     * Локальные переменные:
     * i, j - счетчики циклов.  */
    void Print(const char * ObjName)
    {
        cout << "Матрица " << ObjName <<" : " << endl;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << M[i][j] << "\t";
            cout << "| " << Y[i] << endl;
        }
        cout << "---------------------" << endl;
    }

    /* Метод, возвращающий значения корней СЛАУ, рассчитанных по методу
     * Гаусса
     * Локальные переменные:
     * max - максимальный элемент в соответствующем столбце матрицы;
     * k - счетчик цикла, обеспечивающий движение по диагонали в матрице;
     * index - переменная, позволяющая запоминать индекс строки с максимумом;
     * eps - точность вычислений;
     * temp - переменная, позволяющая произвести замену строк. */
    T * calculateGauss()
    {
        T max;
        int k, index;
        const double eps = 0.00001;
        k = 0;
        while (k < n)                               	// Цикл, обеспечивающий движение по
		// диагонали в матрице
        {
            max = fabs(M[k][k]);
            index = k;
            for (int i = k + 1; i < n; i++)         	// Цикл нахождения максимума в
		// соответствующем столбце
            {
                if (fabs(M[i][k]) > max)
                {
                    max = fabs(M[i][k]);
                    index = i;
                }
            }
            if (max < eps)                          	// Проверка матрицы на нулевой столбец
            {
                cout << "Решение невозможно получить из-за нулевого столбца ";
                cout << index << endl;
                return 0;
            }
            for (int j = 0; j < n; j++)             	// Перестановка строки с максимумом
            {
                T temp = M[k][j];
                M[k][j] = M[index][j];
                M[index][j] = temp;
            }
            T temp = Y[k];
            Y[k] = Y[index];
            Y[index] = temp;

            for (int i = k; i < n; i++)             	// Нормализация уравнений
            {
                T temp = M[i][k];
                if (fabs(temp) < eps) continue;     	// Предотвращение деления на ноль
                for (int j = 0; j < n; j++)
                    M[i][j] = M[i][j] / temp;
                Y[i] = Y[i] / temp;
                if (i == k)  continue;              	// Предотвращение деления уравнения
		// само на себя
                for (int j = 0; j < n; j++)
                    M[i][j] = M[i][j] - M[k][j];
                Y[i] = Y[i] - Y[k];
            }
            k++;
        }

        X = (T*) new T[n];
        for (k = n - 1; k >= 0; k--)                		// Обратный ход метода Гаусса
        {
            X[k] = Y[k];
            for (int i = 0; i < k; i++)
                Y[i] = Y[i] - M[i][k] * X[k];
        }
        return X;
    }

    /* Метод, обеспечивающий вывод результатов, рассчитанных по методу Гаусса
     * Локальная переменная:
     * i - счетчик цикла.
     * Подпрограммы, используемые в методе:
     * calculateGauss() – функция класса, представляющая собой вычислительную
     * часть метода Гаусса. */
    void Gauss(){
        cout << endl << "Корни системы :" << endl;
        X = calculateGauss();
        for (int i = 0; i < n; i++)
            cout << "x[" << i << "]=" << X[i] << endl;

        delete [] X;
    }

    /* Метод, выводящий корни СЛАУ, рассчитанные согласно методу квадратных
     * корней.
     * Локальные переменные:
     * i, j, p1, p2 - счетчики циклов;
     * sum - переменная для накопления сумм рядов, стоящих в формулах
     * разложения Холецкого;
     * L - матрица, сформированная по разложению Холецкого;
     * Tr - транспонированная матрица;
     * Ly - вектор, состоящий из значений y, найденных из уравнения Ly = b;
     * S - переменная, используемая для накопления значений в рядах.  */
    void SquareRoot(){
        L = (T**) new T *[n];
        for (int i = 0; i <= n; i++){
            L[i] = (T*) new T [n];
        }
        
        L[0][0] = sqrt(M[0][0]);                    	// Вычисление первого элемента матрицы
        for (int j = 1; j < n; j++)                 	// Цикл вычисления элементов L[i][j]
        {
            L[j][0] = M[j][0] / L[0][0];
        }
        for (int i = 1; i < n; i++)                 	// Цикл вычисления элементов L[i][i]
			// и L[j][i]
        {
            double sum = 0.0;
            for (int p1 = 0; p1 <= i - 1; p1++)   // Цикл накопления суммы ряда
            {
                sum = sum + L[i][p1] * L[i][p1];
            }
            L[i][i] = sqrt(abs(M[i][i] - sum));
            for (int j = i + 1; j < n; j++)
            {
                sum = 0.0;
                for (int p2 = 0; p2 <= i - 1; p2++) // Цикл накопления суммы ряда
                {
                    sum = sum + L[i][p2] * L[j][p2];
                }
                L[j][i] = (M[j][i] - sum) / L[i][i];
            }
        }

        cout << "Разложение Холецкого : " << endl;
        for (int i = 0; i < n; i++)                 	// Цикл вывода матрицы L
        {
            for (int j = 0; j < n; j++)
                cout << setw(8)<< L[i][j] << "\t";
            cout << "| " << Y[i] << endl;
        }
        cout << endl;

        Tr = (T**) new T *[n];
        for (int i = 0; i <= n; i++){
            Tr[i] = (T*) new T [n];
        }
        for(int i = 0; i < n; i++){                 	// Цикл, транспонирующий матрицу L
            for (int j = 0; j < n; j++){
                Tr[j][i] = L[i][j];
            }
        }
        cout << "Транспонированная матрица : " << endl;
        for (int i = 0; i < n; i++)                 	// Цикл вывода матрицы Tr
        {
            for (int j = 0; j < n; j++)
                cout << setw(8) << Tr[i][j] << "\t";
            cout << "| " << Y[i] << endl;
        }
        cout << endl;

        Ly = (T*) new T[n];
        Ly[0] = Y[0] / L[0][0];                     	// Вычисление y1 из уравнения Ly = b
        for (int i = 1; i < n; i++){                	// Цикл, вычисляющий остальные y
            T S = Y[i];
            for (int j = 0; j < i; j++){
                S -= L[i][j] * Ly[j];
            }
            Ly[i] = S / L[i][i];
        }

        cout << endl << " Решение уравнения Ly = b " << endl;
        for (int i = 0; i < n; i++){
            cout << "Y[" << i << "] = "<< setw(8) << Ly[i] << "   ";
        }
        cout << endl << endl;


       X = (T*) new T[n];
        X[n-1] = Ly[n-1] / Tr[n-1][n-1];
        for (int i = n - 2; i >= 0; i--){
            T S = Ly[i];
            for (int j = n - 1; j > i; j--){
                S -= Tr[i][j] * X[j];
            }
            X[i] = S / Tr[i][i];
        }

        cout << " Корни системы: " << endl;
        for (int i = 0; i < n; i++){
            cout << "X[" << i << "] = " << setw(8) << X[i] << endl;
        }
        cout << endl ;


        /* Освобождение выделенной памяти для динамических матриц и массивов */
        if (n > 0)
        {for (int i = 0; i < n; i++)
                delete[] L[i];
        }
        if (n > 0)
            delete[] L;

        if (n > 0)
        {for (int i = 0; i < n; i++)
                delete[] Tr[i];
        }
        if (n > 0)
            delete[] Tr;

        delete [] Ly;
        delete [] X;
    }

    /* Деструктор, удаляющий объект класса и освобождающий выделенную под
     * него память */
    ~Matrix()
    {
        if (n > 0)
        {for (int i = 0; i < n; i++)
                delete[] M[i];
        }
        if (n > 0)
            delete[] M;
        delete [] Y;
    }
};

#endif //SHABL_KLASS_MATRIX_H
