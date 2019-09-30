#include <iostream>
#include <stack>        // std::stack<>

class MinStack{
private:
    std::stack<int> data;
    std::stack<int> minstack;
public:
    MinStack(){};
    void Push(int x);
    void Pop();
    bool IsEmpty();
    int Top();
    int getSize();
    int getMin();
};
void MinStack::Push(int x){

    data.push(x);
    if (minstack.empty() || x < minstack.top()) {
        minstack.push(x);
    }
    else {
        minstack.push(minstack.top());
    }
}

void MinStack::Pop(){

    if (data.empty()) {
        std::cout << "Stack is empty.\n";
        return;
    }
    data.pop();
    minstack.pop();
}

int MinStack::getMin(){

    if (data.empty()) {
        std::cout << "Stack is empty.\n";
        return -1;
    }

    return minstack.top();
}

bool MinStack::IsEmpty(){

    return data.empty();
}

int MinStack::Top(){

    if (data.empty()) {
        std::cout << "Stack is empty.\n";
        return -1;                          
    }

    return data.top();
}

int MinStack::getSize(){

    if (data.empty()) {
        std::cout << "Stack is empty.\n";
        return -1;
    }

    return (int)data.size();
}

int main(){

    MinStack s;
    s.Pop();
    s.Push(6);
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    s.Push(13);
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    s.Push(4);
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    s.Push(9);
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    s.Push(1);
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    s.Pop();
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    s.Pop();
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    s.Pop();
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    s.Pop();
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    s.Pop();
    std::cout << "\ntop: " << s.Top() << "\nmin: " << s.getMin() << std::endl;

    return 0;
}
