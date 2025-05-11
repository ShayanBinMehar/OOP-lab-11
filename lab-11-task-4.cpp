#include <iostream>
#include <exception>
#include <string>

using namespace std;

class NegativeNumberException : public exception
{
    string message;

public:
    NegativeNumberException(const string &msg) : message(msg) {}
    const char *what() const noexcept override
    {
        return message.c_str();
    }
};

int sqrt_func(int num)
{
    if (num < 0)
        throw NegativeNumberException("Input must be non-negative!");

    if (num == 0)
        return 0;

    double x = num;
    double y = 1;
    double epsilon = 0.000001;

    while ((x - y > epsilon) || (y - x > epsilon))
    {
        x = (x + y) / 2;
        y = num / x;
    }

    return static_cast<int>(x);
}

float sqrt_func(float num)
{
    if (num < 0)
        throw NegativeNumberException("Input must be non-negative!");

    if (num == 0)
        return 0;

    float x = num;
    float y = 1;
    float epsilon = 0.000001f;

    while ((x - y > epsilon) || (y - x > epsilon))
    {
        x = (x + y) / 2;
        y = num / x;
    }

    return x;
}

double sqrt_func(double num)
{
    if (num < 0)
        throw NegativeNumberException("Input must be non-negative!");

    if (num == 0)
        return 0;

    double x = num;
    double y = 1;
    double epsilon = 0.000001;

    while ((x - y > epsilon) || (y - x > epsilon))
    {
        x = (x + y) / 2;
        y = num / x;
    }

    return x;
}

int main()
{
    try
    {
        int a = 16;
        cout << "sqrt(" << a << ") = " << sqrt_func(a) << endl;

        float b = 36.0f;
        cout << "sqrt(" << b << ") = " << sqrt_func(b) << endl;

        double c = 49.0;
        cout << "sqrt(" << c << ") = " << sqrt_func(c) << endl;

        int neg = -5;
        cout << "sqrt(" << neg << ") = ";
        cout << sqrt_func(neg) << endl;
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
