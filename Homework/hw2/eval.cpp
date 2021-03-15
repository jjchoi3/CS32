//
//  eval.cpp
//  Homework 2
//
//  Created by Junho Choi on 1/31/21.
//

#include <iostream>
#include <string>
#include <stack>
using namespace std;

string infixToPostfix(string ifix);
bool validInfix(string ifix);
int precedence(char c);

int evaluate(string infix, const bool values[], string& postfix, bool& result){
    postfix = ""; // initialize postfix string
    
    stack<char> optorStack;
    
    if(!validInfix(infix))
        return 1;
    postfix = infixToPostfix(infix);
    
    /* evaluate postfix */
    stack<bool> opandStack;
    for(int i = 0; i < postfix.length(); ++i){
        if(isdigit(postfix[i]))
            opandStack.push(values[postfix[i] - '0']);
        else if (postfix[i] == '!'){
            bool operand = opandStack.top();
            opandStack.pop();
            opandStack.push(!operand);
        }else{
            bool operand2 = opandStack.top();
            opandStack.pop();
            bool operand1 = opandStack.top();
            opandStack.pop();
            switch(postfix[i]){
                case '&':
                    opandStack.push(operand1 && operand2);
                    break;
                case '|':
                    opandStack.push(operand1 || operand2);
                    break;
            }
        }
    }
    result = opandStack.top();
    return 0;
}

int precedent(char c){
    switch(c){
        case '!':
            return 3;
        case '&':
            return 2;
        case '|':
            return 1;
    }
    return 0;
}
bool validInfix(string ifix){
    stack<char> ifixStack;
    int parenCount = 0; // counts # of parentheses
    for(int i = 0; i < ifix.length(); ++i){
        switch(ifix[i]){
            case ' ':
                break;
            case '!':
                if(!ifixStack.empty() && isdigit(ifixStack.top())) // there must be an operator before ! unless first
                    return false;
                break;
            case '&':
            case '|':
                if(ifixStack.empty() || (!ifixStack.empty() && !(isdigit(ifixStack.top()) || ifixStack.top() == ')'))) // there must be a digit or close paren before & or !
                   return false;
                break;
            case '(':
                parenCount++;
                if(!ifixStack.empty() && isdigit(ifixStack.top())) // must be operator before paren unless first char
                    return false;
                break;
            case ')':
                if(ifixStack.top() == '(') // must be something between parens
                    return false;
                parenCount--;
                break;
            default:
                if(isdigit(ifix[i])){
                    if(!ifixStack.empty() && (isdigit(ifixStack.top()) ||  ifixStack.top() == ')')) // cannot be two digits in a row and cannot be digit after closing paren
                        return false;
                }else // if it is an invalid char
                    return false;
        }
        if(parenCount < 0) // if there are more closing parens than opening
            return false;
        if(ifix[i] != ' ')
            ifixStack.push(ifix[i]);
        
    }
    if(parenCount != 0 || ifixStack.empty() || (!isdigit(ifixStack.top()) && ifixStack.top() != ')') ) // if all parens aren't closed or if (last num isn't digit nor closing paren)
        return false;
    return true;

}

string infixToPostfix(string ifix){
    string pfix = "";
    stack<char> optorStack;
    
    for(int i = 0; i < ifix.length(); ++i){
        switch(ifix[i]){
            case '!':
            case '(':
                optorStack.push(ifix[i]);
                break;
            case ')':
                while(optorStack.top() != '('){
                    pfix += optorStack.top();
                    optorStack.pop();
                }
                optorStack.pop();
                break;
            case ' ':
                break;
            case '&': // 38
            case '|': // 124
                while(!optorStack.empty() && optorStack.top() != '(' && precedent(ifix[i]) <= precedent(optorStack.top())){
                    pfix += optorStack.top();
                    optorStack.pop();
                }
                optorStack.push(ifix[i]);
                break;
            default:
                if(isdigit(ifix[i]))
                    pfix += ifix[i];
        }
    }
    while(!optorStack.empty()){
        pfix += optorStack.top();
        optorStack.pop();
    }
    return pfix;
}
