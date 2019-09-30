#include <iostream>
using namespace std;

//抽象類別 只能被繼承
class IRequest {
public:
    // 宣告虛擬函式
    virtual void execute() = 0;
};

class SomeObject {
public:
    virtual void someFunction() {
        cout << "do something" << endl;
    }

private:
    void otherFunction() {
        cout << "do other" << endl;
    }
};
//以下類別是以下的SomeObject類別的子類別

class Welcome : public SomeObject, public IRequest {
public:
    void execute() {
        cout << "Welcome!!" << endl;
    }
};

class Hello : public SomeObject, public IRequest {
public:
    void execute() {
        cout << "Hello!!" << endl;
    }
};

void doRequest1(IRequest *request) {
    request->execute();
}

void doRequest2(IRequest &request) {
    request.execute();
}

int main() { 
    Welcome welcome;
    Hello hello;
    //雖然不知道Hello與 Welcome是什麼型態
    //但它們都繼承了IRequest 所以doRequest()只要知道IRequest定義了什麼公開介面，就可以操作Hello與Welcome的實例
    doRequest1(&welcome);
    doRequest2(hello);

    return 0;
}