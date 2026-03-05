#include <iostream>
#include <cmath>

using namespace std;

double calc(); 
//Main code block
int main() {
    char continueCalc;
    
    do {
        cout << "Result: " << calc() << endl;
        cout << "Do you want to calculate another expression? (y/n): ";
        cin >> continueCalc;
    } while (continueCalc == 'y' || continueCalc == 'Y');
    
    return 0;
}
//Function to handle the arithmetic and scientific calculations
double calc() {
    double num1, num2, result = 0;
    char op;

    cout << "\n--- Calculator ---\n";
    cout << "Operations: + - * / ^ (power) % (modulo)\n";
    cout << "Scientific: s (sin) c (cos) t (tan) q (sqrt)\n";
    cout << "Enter first number: ";
    cin >> num1;
    cout << "Enter operator: ";
    cin >> op;
    
    // Handle unary scientific functions
    if (op == 's') {
        result = sin(num1);
        cout << "sin(" << num1 << ") = ";
        return result;
    } else if (op == 'c') {
        result = cos(num1);
        cout << "cos(" << num1 << ") = ";
        return result;
    } else if (op == 't') {
        result = tan(num1);
        cout << "tan(" << num1 << ") = ";
        return result;
    } else if (op == 'q') {
        if (num1 < 0) {
            cout << "Error: Cannot calculate square root of negative number!" << endl;
            return 0;
        }
        result = sqrt(num1);
        cout << "sqrt(" << num1 << ") = ";
        return result;
    }
    
    // Binary operations
    cout << "Enter second number: ";
    cin >> num2;

    switch (op) {
        case '+':
            result = num1 + num2;
            break;
        case '-':
            result = num1 - num2;
            break;
        case '*':
            result = num1 * num2;
            break;
        case '/':
            if (num2 == 0) {
                cout << "Error: Cannot divide by zero!" << endl;
                return 0;
            }
            result = num1 / num2;
            break;
        case '^':
            result = pow(num1, num2);
            break;
        case '%':
            if ((int)num2 == 0) {
                cout << "Error: Cannot perform modulo with zero!" << endl;
                return 0;
            }
            result = (int)num1 % (int)num2;
            break;
        default:
            cout << "Invalid Operator" << endl;
    }

    return result;
}


