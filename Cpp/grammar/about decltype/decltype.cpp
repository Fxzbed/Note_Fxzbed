#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// template <typename T>
// class testTemplate {
//     public:
//         templatePrint(T& v) {
//             for (it = v.begin(); it != v.end(); it ++) 
//                 cout << "templatePrint: " << *it << endl;
//         }

//     private:
//         T::iterator it;
// };

template <typename T>
class testTemplate {
    public:
        // void templatePrint(T& v) {
        //     for (it = v.begin(); it != v.end(); it ++) 
        //         cout << "templatePrint: " << *it << endl;
        // }

        template<typename T_>
        void templatePrint(T_&& v) {
            for (it = v.begin(); it != v.end(); it ++) 
                cout << "templatePrint: " << *it << endl;
        }

    private:
        decltype(T().begin()) it;
};

int main(void) {
    vector<int> vec = {1, 2, 3, 4, 5};
    testTemplate<vector<int>> T;

    T.templatePrint(vec);
    return 0;
}