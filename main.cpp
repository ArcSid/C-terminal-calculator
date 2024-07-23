#include <cctype>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Expression{
    string terminalInput;
    string computableExpression;
    double ans;
};

string terminalInputToComputableExpression(string terminalInput){
    string expression = "";
    for(int i = 0; i<terminalInput.length(); i++){
        if(isdigit(terminalInput[i])){
            expression += terminalInput[i];
            continue;
        }
        if(terminalInput[i] == '.'){
            expression += terminalInput[i];
            continue;
        }
        expression += " ";
        expression += terminalInput[i];
        expression += " ";
    }
    return expression;
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/'
           || c == '^' || c == '%';
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    if (op == '^') 
        return 3;
    return 0;
}

double applyOp(double a, double b, char op)
{
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    case '^':
        return pow(a, b);
    case '%':
        return int(a)%int(b);
    default:
        return 0;
    }
}

double evaluateExpression(const string& expression)
{
    stack<char> operators;
    stack<double> operands;

    stringstream ss(expression);

    string token;
    while (getline(
        ss, token,
        ' ')) {
        if (token.empty())
            continue;
        if (isdigit(token[0])) { 
            double num;
            stringstream(token)
                >> num; 
            operands.push(num); 
        }
        else if (isOperator(token[0])) {
            char op = token[0];
            while (!operators.empty()
                   && precedence(operators.top())
                          >= precedence(op)) {
                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                operands.push(applyOp(a, b, op));
            }
            operators.push(op);
        }
        else if (token[0] == '(') {
            operators.push('(');
        }
        else if (token[0] == ')') {
            while (!operators.empty()
                   && operators.top() != '(') {
                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();
                char op = operators.top();
                operators.pop();
                operands.push(applyOp(a, b, op));
            }
            operators.pop();
        }
    }

    while (!operators.empty()) {
        double b = operands.top();
        operands.pop();
        double a = operands.top();
        operands.pop();
        char op = operators.top();
        operators.pop();
        operands.push(applyOp(a, b, op));
    }

    return operands.top();
}

int main(int argCount, char* args[])
{
    vector<Expression> expressionList;
    for(int i = 1; i<argCount; i++){
        Expression tempExpression;
        tempExpression.terminalInput = args[i];
        tempExpression.computableExpression = terminalInputToComputableExpression(args[i]);
        tempExpression.ans = evaluateExpression(tempExpression.computableExpression);
        expressionList.push_back(tempExpression);
    }

    if(expressionList.size() == 0){
        cout << "\033[1;31mNO MATHS INPUT GIVEN\033[0m" << endl;
        return 0;
    }
    cout << endl;
    cout << "\033[1;35m------------- C++ terminal calculator -------------\033[0m" << endl;
    cout << endl;
    for(int i = 0; i<expressionList.size(); i++){
        cout << "\033[1;34m"<< expressionList[i].terminalInput << "\033[0m"
        << "\033[1;36m = \033[0m" <<
        "\033[1;32m"<< expressionList[i].ans<< "\033[0m" << endl;
    }
    cout << endl;
    return 0;
}
