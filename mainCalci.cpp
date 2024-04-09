#include <iostream>
#include <vector>
#include <memory>

using namespace std;

// Abstract base class
class Operation {
public:
    virtual double execute(double a, double b) = 0; // Pure virtual function for execution
    virtual ~Operation() {} // Virtual destructor
};

// Subtraction operation
class Subtraction : public Operation {
public:
    double execute(double a, double b) override {
        return a - b;
    }
};

// Addition operation
class Addition : public Operation {
public:
    double execute(double a, double b) override {
        return a + b;
    }
};


// Multiplication operation
class Multiplication : public Operation {
public:
    double execute(double a, double b) override {
        return a * b;
    }
};

// Division operation
class Division : public Operation {
public:
    double execute(double a, double b) override {
        if(b == 0) {
            throw std::runtime_error("Division by zero.");
        }
        return a / b;
    }
};

// Calculator class
class Calculator {
private:
    vector<unique_ptr<Operation>> operations; // Stores all operations

public:
    Calculator() {
        // Populate the operations vector with instances of operations
        operations.push_back(make_unique<Addition>());
        operations.push_back(make_unique<Subtraction>());
        operations.push_back(make_unique<Multiplication>());
        operations.push_back(make_unique<Division>());
    }

    double calculate(char op, double a, double b) {
        switch(op) {
            case '+':
                return operations[0]->execute(a, b); // Addition
            case '-':
                return operations[1]->execute(a, b); // Subtraction
            case '*':
                return operations[2]->execute(a, b); // Multiplication
            case '/':
                return operations[3]->execute(a, b); // Division
            default:
                throw std::invalid_argument("Invalid operation.");
                // cout<<"Invalid Operation";
        }
    }
};

int main() {
    Calculator calc;
    double a, b;
    char op;
    
    cout << "Enter expression (a op b): ";
    cin >> a >> op >> b;

    try {
        double result = calc.calculate(op, a, b);
        cout << "Result: " << result << endl;
    } catch (const std::exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
