#include <string>
#include <vector>
#include <iostream>
#include <iterator>

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    copy(v.begin(), v.end(), std::ostream_iterator<T>(os, ", "));
    return os;
}

int main(void)
{
    std::vector<int> a{1, 2, 3, 4, 5, 6};
    std::cout << "my vec: " << a << std::endl;
}

// output "my vec: 1, 2, 3, 4, 5, 6,"
