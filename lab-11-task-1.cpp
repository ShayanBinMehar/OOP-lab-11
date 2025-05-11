#include <iostream>
#include <exception>
#include <string>

using namespace std;

class InvalidValueException : public exception
{
public:
    InvalidValueException(const string &message) : message_(message) {}

    const char *what() const noexcept override
    {
        return message_.c_str();
    }

private:
    string message_;
};

void validateAge(int age)
{
    if (age < 0 || age > 120)
    {
        throw InvalidValueException("Age cannot be negative or exceed 120.");
    }
    cout << "Age is valid: " << age << endl;
}

int main()
{
    int age;

    cout << "Enter age: ";
    cin >> age;
    try
    {
        validateAge(age);
    }
    catch (const InvalidValueException &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    cout << "Enter age: ";
    cin >> age;
    try
    {
        validateAge(age);
    }
    catch (const InvalidValueException &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}
