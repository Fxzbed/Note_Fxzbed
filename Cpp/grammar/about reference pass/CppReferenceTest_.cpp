#include <iostream>
#include <algorithm>

using namespace std;

void process(int& v) {
  cout << "invoke process overload type int&\n";
}

void process(int&& v) {
  cout << "invoke process overload type int&&\n";
}

template <typename T>
void test(T&& v) {             //when value pass into test 
  process(v);                  
}
/*
 * instancing a template
 * void test(T& && v) {
 *  process(v);
 * }
 *
 * void test(T&& && v) {
 *  process(v);
 * }
 *
 * T& && editor will transform type  ----> T&
 * T&& && editor will transform type ----> T&&
*/

template<typename T>
void test_(T&& v) {
  process(static_cast<T> (v));  //we static_cast turn value type to V
                                //like std::forward
}

int main(void) {
  int i = 0;
  
  cout << "Test:\n";

  test(i);  //we pass a left-value
  test(1);  //we pass a right-value

  cout << "Test_:\n";

  test_(i);
  test_(1);

  return 0;
}
