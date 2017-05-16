#include <iostream>
#include <vector>
#include <thread>

using namespace std;

// Класс матрица n на n
class Matrix{
public:
    unsigned n; // Размер матрицы
    unsigned numWorkers;  // Количество рабочих для вычисления детермината
    vector<vector<double>*> m; // Сама матрица
    Matrix(unsigned, unsigned = 1); // Конструктор
    ~Matrix(); // Деструктор
    void dump(); // Печать
    double determinant(); // Вычисление детерминанта
    int find_not_null(int i); // Поиск не нулевого элемента в i-ом столбце
    void swap_lines(int, int); // Переставление двух столбцов
    void sub_lines(int, int, int, int, double = 1); // вычитание двух строк
};

Matrix::Matrix(unsigned n, unsigned numWorkers): n(n), numWorkers(numWorkers){
  for (int i = 0; i < n; ++i) {
    m.push_back(new vector<double>(n));
    for (int j = 0; j < n; ++j) {
      (*m[i])[j] = rand()%5; // Инициализируем матрицу случайными хначениями от 0 до 5
    }
  }
}

void Matrix::dump() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cout<<(*m[j])[i]<<" ";  // Выводим на экран элементы матрицы через пробел
    }
    cout<<endl;
  }
}

Matrix::~Matrix() {
  for (int i = 0; i < n; ++i) {
    delete m[i];  // Чистим память
  }

}

double Matrix::determinant() {
  double res = 1;

  for (int i = 0; i < n; ++i) { // Идём по столбцам
    int t = find_not_null(i); // Ищем номер ненулевого элемента в i-ом столбце
    if(t >= n)  // Если такого элемента нет, значит детерминант 0
      return 0;
    if(i != t) {  // Если же он не i-ой строчке
      res *= -1;
      swap_lines(i, t); // Меняем местами строки i и t
    }

    res *= (*m[i])[i];  // Домножаем дерерминант на элемент (i, i)
    for (int j = n - 1; j > -1; --j) {
      (*m[i])[j] = (*m[i])[j]/(*m[i])[i]; // И делим на него всю i-ую строку
    }

    // Для всех строк ниже i-ой делим их на numWorkers частей и раздаём потокам
    // Они отнимают от l-ой строки i-ую умноженную на (*m[i])[l], тем самым обнуляя все значения
    // на i-ом столбце ниже i-ой строки
    for (int l = i+1; l < n; ++l) {
      vector<thread> workers(0);
      double value  = (*m[i])[l];
      for (int k = 0; k < numWorkers - 1; ++k) {
        workers.push_back(thread([this, k, l, i, value](){sub_lines(i, l, k*n/numWorkers, (k+1)*n/numWorkers, value);}));
      }
      workers.push_back(thread([this, l, i, value](){sub_lines(i, l, (numWorkers-1)*n/numWorkers, n, value);}));

      for (int j = 0; j < numWorkers; ++j) {
        workers[j].join();
      }
    }
  }
  return res;
}

int Matrix::find_not_null(int i) {
  for (int j = i; j < n; ++j) {
    if((*m[i])[j] != 0)
      return j; // Возвращаем номер не нулевого элемента в i-ом столбце
  }
  return n; // Если его нет возвращаем n
}

void Matrix::swap_lines(int i, int j) { // Меняем строчки местами
  vector<double>* temp = m[i];
  m[i] = m[j];
  m[j] = temp;
}

// Вычитаем от j-ой строки i-ую умноженную на value
void Matrix::sub_lines(int i, int j, int start, int finish, double value) {
  for (int k = start; k < finish; ++k) {
    (*m[k])[j] -= value*(*m[k])[i];
  }
}

int main(){

  Matrix m(3, 2); // Создаём матрицу размена 3 на 3, с 2мя потоками для вычисления детерминанта

  m.dump(); // Печатаем матрицу

  cout<<endl<<endl<<m.determinant()<<endl<<endl; // выводим детерминант на экран

  m.dump(); // снова печатаем матрицу

  return 0;
}