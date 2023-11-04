// #include <iostream>
// #include <utility>  

// using namespace std;

// void TestValue(int& a) {
//     cout << "left value: " << a << endl;
// }

// void TestValue(int&& a) {
//     cout << "right value: " << a << endl;
// }

// template <typename T>
// void proxyFunc(T&& v) {
//     TestValue(forward<T>(v));
// }

// int main(void) {
//     cout << "TestValue invok:" << endl;
//     int a = 1;
//     int& l_a = a; 
//     int&& r_a = 2;
//     TestValue(l_a);
//     TestValue(1);
//     TestValue(forward<int>(l_a));
//     TestValue(forward<int&>(l_a));
//     TestValue(forward<int&&>(l_a));

//     printf("\n");

//     TestValue(r_a);
//     TestValue(2);
//     TestValue(forward<int>(r_a));
//     TestValue(forward<int&>(r_a));
//     TestValue(forward<int&&>(r_a));

//     printf("\n");
//     cout << "Template proxyFunc invoke:" << endl;
//     proxyFunc(l_a);
//     proxyFunc(r_a);
//     proxyFunc(std::move(r_a));
//     return 0;
// }
#include <iostream>
using namespace std;

template<typename T>
void printValue(T& t)
{
    cout << "l-value: " << t << endl;
}

template<typename T>
void printValue(T&& t)
{
    cout << "r-value: " << t << endl;
}

template<typename T>
void testForward(T && v)
{
    printValue(v);
    printValue(move(v));
    printValue(forward<T>(v));
    cout << endl;
}

int main()
{
    testForward(520);
    int num = 1314;
    testForward(num);
    testForward(forward<int>(num));
    testForward(forward<int&>(num));
    testForward(forward<int&&>(num));

    return 0;
}