#include <iostream>
#include <algorithm>

using namespace std;

class KeywordTest {
private:
    /* data */
public:     //use virtual function let child class can override this function
    virtual void overrideTestFunc() {
        cout << "Class<finnalKeywordTest>: This is a TestFunction named overrideTestFunc" << endl;
        return;
    }
};

class overrideKeywordTest_child : public KeywordTest {
public:     //override overrideTestFunc cross class KeywordTest
    void overrideTestFunc() override {
        cout << "Class<overrideKeywordTest_child>: This is a TestFunction named overrideTestFunc" << endl;
        return;
    }
};

class finnalKeywordTest_child : public KeywordTest {
public:     //rewrite finnalTestFunc() next time we can't override this func
    virtual void finnalTestFunc() final {
        cout << "Class<finnalKeywordTest_child>: This is a TestFunction named finnalTestFunc" << endl;
    }
};

// class finnalKeywordTest_child_child : public finnalKeywordTest_child {
// public:     //rewrite finnalTestFunc() next time we can't override this func
//     virtual void finnalTestFunc() {
//         cout << "Class<finnalKeywordTest_child>: This is a TestFunction named finnalTestFunc" << endl;
//     }
// };

int main(void) {
    return 0;
}