#include <iostream>
#include <exception>
#include <string>

using namespace std;

class StackOverflowException : public exception
{
public:
    StackOverflowException(const string &message) : message_(message) {}
    const char *what() const noexcept override
    {
        return message_.c_str();
    }

private:
    string message_;
};

class StackUnderflowException : public exception
{
public:
    StackUnderflowException(const string &message) : message_(message) {}
    const char *what() const noexcept override
    {
        return message_.c_str();
    }

private:
    string message_;
};

template <typename T>
class Stack
{
public:
    Stack(int capacity = 100) : capacity_(capacity), top_(-1)
    {
        stack_ = new T[capacity_];
    }

    ~Stack()
    {
        delete[] stack_;
    }

    void push(const T &value)
    {
        if (top_ >= capacity_ - 1)
        {
            throw StackOverflowException("Stack is full!");
        }
        stack_[++top_] = value;
    }

    T pop()
    {
        if (top_ < 0)
        {
            throw StackUnderflowException("Stack is empty!");
        }
        return stack_[top_--];
    }

    bool isEmpty() const
    {
        return top_ < 0;
    }

    bool isFull() const
    {
        return top_ >= capacity_ - 1;
    }

    int getSize() const
    {
        return top_ + 1;
    }

private:
    T *stack_;
    int capacity_;
    int top_;
};

int main()
{
    Stack<int> intStack(5);

    try
    {
        cout << "Pushing elements onto the stack:\n";
        intStack.push(10);
        cout << "Pushed 10\n";
        intStack.push(20);
        cout << "Pushed 20\n";
        intStack.push(30);
        cout << "Pushed 30\n";
        intStack.push(40);
        cout << "Pushed 40\n";
        intStack.push(50);
        cout << "Pushed 50\n";
        intStack.push(60);
    }
    catch (const StackOverflowException &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    try
    {
        cout << "\nPopping elements from the stack:\n";
        while (!intStack.isEmpty())
        {
            cout << "Popped " << intStack.pop() << endl;
        }
        intStack.pop();
    }
    catch (const StackUnderflowException &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
