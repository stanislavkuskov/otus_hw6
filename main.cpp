#include <iostream>
#include <assert.h>
#include <vector>
#include <map>

using matrix_storage = std::map<std::pair<int, int>, int> ;

template <typename T, T default_value>
class Matrix
{
private:
    struct MatrixContainer {
        matrix_storage m_container;
        void append_element(int h, int w, T val){
            if (val != default_value){
                m_container.insert({{h, w}, val});
            } else {
                if (m_container.count({h, w}) > 0){
                    m_container.erase({h, w});
                }
            }

        };

        int get_value(int h, int w){
            T res = default_value;
            if (m_container.count({h, w}) > 0){
                res = m_container.find({h, w}) -> second;
            }
            return res;
        }

        size_t get_container_size(){
            return m_container.size();
        }

        void print_container(){
            for (auto element: m_container){
                std::cout << "value: " << element.second
                << ", h: " << element.first.first << ", w: "
                << element.first.second << std::endl;
            }
        }
    };

    MatrixContainer m;

public:

    size_t size(){
        return m.get_container_size();
    }

    int get_element(int h, int w){
        return m.get_value(h, w);
    }

    void set_element(int h, int w, T val){
        m.append_element(h, w, val);
    }

    void print(){
        m.print_container();
    }
};

int main(int, char *[])
{
//    Matrix<int, -1> matrix;
//    assert(matrix.size() == 0);
//
//    auto a = matrix.get_element(0, 0);
//    assert(a == -1);
//    assert(matrix.size() == 0);
//
//    matrix.set_element(100, 100, 314);
//    assert(matrix.get_element(100, 100) == 314);
//    assert(matrix.size() == 1);

    int const default_value = 0;
    Matrix<int, default_value> m;

    /*  1. создать матрицу с пустым значением 0, заполнить диагонали матрицы
     * выражением m[i][i] = m[N - 1 - i][i] = i; // N = 10, i = (0 .. N)
    */

    int N = 10;

    for (int i = 0; i < N; ++i){
        m.set_element(i, i, i);
        m.set_element(N - 1 - i, i, i);
    }

    /*  2. Начиная с ячейки [0, 0] в шахматном порядке заполнить матрицу 10x10
     * значением по умолчанию.
     */
    for (int i = 0; i <= N; ++i){
        for (int j = 0; j <= N; ++j){
            if (i%2 == 0){
                if (j%2 == 0){
                    m.set_element(i, j, default_value);
                }
            } else{
                if (j%2 != 0){
                    m.set_element(i, j, default_value);
                }
            }
        }
    }

    /*  3. Необходимо вывести фрагмент матрицы от [1,1] до [8,8]. Между столбцами пробел.
     * Каждая строка матрицы на новой строке.
     */
// вывод элементов по списку, отображение 0 на пустых местах. Для этго нужен упорядоченный список
    for (int h = 1; h <= 8; ++h){
        for (int w = 1; w <= 8; ++w){
            std::cout << m.get_element(h, w) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    /*  4. Вывести количество занятых ячеек.*/
    std::cout << m.size() << std::endl;
    std::cout << std::endl;
    /*  5. Вывести все занятые ячейки вместе со своими позициями.*/
    m.print();
    std::cout << std::endl;

    return 0;
}
