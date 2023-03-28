#include <array>
#include <any>
#include <iostream>

template <size_t N>
class AnyArray {
public:
    template <typename T>
    void Set(size_t index, T value) {
        m_array[index] = value;
    }

    template <typename T>
    T Get(size_t index) const {
        return std::any_cast<T>(m_array[index]);
    }

private:
    std::array<std::any, N> m_array;
};

int main() {
    AnyArray<3> myArray;

    myArray.Set(0, 1);
    myArray.Set(1, 3.14);
    myArray.Set(2, "hello");

    std::cout << myArray.Get<int>(0) << ' '
              << myArray.Get<double>(1) << ' '
              << myArray.Get<const char*>(2) << '\n';

    return 0;
}

