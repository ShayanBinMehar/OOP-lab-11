#include <iostream>
#include <exception>
#include <string>

using namespace std;

template <typename T>
class InsufficientFundsException : public exception {
public:
    InsufficientFundsException(const string& message, T deficit) : message_(message), deficit_(deficit) {}
    const char* what() const noexcept override {
        return message_.c_str();
    }
    T getDeficit() const { return deficit_; }
private:
    string message_;
    T deficit_;
};

template <typename T>
class BankAccount {
public:
    BankAccount(T initialBalance = 0.0) : balance_(initialBalance) {}

    void deposit(T amount) {
        if (amount > 0) {
            balance_ += amount;
            cout << "Deposited " << amount << ". New balance: " << balance_ << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(T amount) {
        if (amount > balance_) {
            T deficit = amount - balance_;
            throw InsufficientFundsException<T>("Insufficient funds", deficit);
        }
        balance_ -= amount;
        cout << "Withdrew " << amount << ". New balance: " << balance_ << endl;
    }

    T getBalance() const {
        return balance_;
    }

private:
    T balance_;
};

void printDoubleWith2Decimals(double value) {
    long long intPart = static_cast<long long>(value);
    long long fracPart = static_cast<long long>((value - intPart) * 100 + 0.5);
    if (fracPart >= 100) {
        intPart++;
        fracPart -= 100;
    }
    cout << intPart << ".";
    if (fracPart < 10)
        cout << "0";
    cout << fracPart;
}

int main() {
    BankAccount<double> account(500.00);

    cout << "Initial Balance: $";
    printDoubleWith2Decimals(account.getBalance());
    cout << endl;

    try {
        cout << "Attempting to withdraw $600.00" << endl;
        account.withdraw(600.00);
    }
    catch (const InsufficientFundsException<double>& e) {
        cerr << "Error: " << e.what() << ". Deficit: $";
        printDoubleWith2Decimals(e.getDeficit());
        cerr << endl;
    }

    try {
        cout << "Attempting to withdraw $100.00" << endl;
        account.withdraw(100.00);
    }
    catch (const InsufficientFundsException<double>& e) {
        cerr << "Error: " << e.what() << ". Deficit: $";
        printDoubleWith2Decimals(e.getDeficit());
        cerr << endl;
    }

    cout << "Final Balance: $";
    printDoubleWith2Decimals(account.getBalance());
    cout << endl;

    return 0;
}
