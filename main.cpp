#include <iostream>
#include <assert.h>
#include <vector>
#include <map>

#include <iostream>
#include <map>

using matrix_storage = std::vector<std::tuple<int, int, int>> ;

template <typename T, T default_value>
class Matrix
{
public:
    struct MatrixContainer {
        matrix_storage m_container;
        void append_element(int h, int w, int val){
            if (find_element(h, w) == -1){
                m_container.emplace_back(h, w, val);
            }
        };
        int find_element(int h, int w){
            for (std::tuple<int, int, int> element : m_container){
                if ((std::get<0>(element) == h) and (std::get<1>(element) == w)){
                    return std::get<2>(element);
                }
            }
            return default_value;
        };
        size_t get_container_size(){
            return m_container.size();
        }
    };

    MatrixContainer m;

public:

    size_t size(){
        return m.get_container_size();
    }

    int get_element(int w, int h){
        return m.find_element(h, w);
    }

    void set_element(int h, int w, int val){
        m.append_element(h, w, val);
    }
};

int main(int, char *[])
{
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0);

    auto a = matrix.get_element(0, 0);
    assert(a == -1);
    assert(matrix.size() == 0);

    matrix.set_element(100, 100, 314);
    assert(matrix.get_element(100, 100) == 314);
    assert(matrix.size() == 1);

    return 0;
}
