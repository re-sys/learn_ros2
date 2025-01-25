#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto is_even = [](int x) { return x % 2 == 0; };
    auto is_odd = [](int x) { return x % 2 == 1; };

    std::cout << "Even numbers: ";
    std::copy_if(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "), is_even);
    std::cout << std::endl;

    std::cout << "Odd numbers: ";
    std::copy_if(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "), is_odd);
    std::cout << std::endl;

    return 0;
}
