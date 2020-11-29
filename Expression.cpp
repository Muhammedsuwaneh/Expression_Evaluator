#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stack>
#define max 255
using namespace std;

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string &s) {

	stack<string>output;
	stack<string>stk;
	string result = " ", temp;
	stringstream ss1(s);
	stringstream ss2(s);
	char* infix = new char[max];
	getline(ss2, temp);

	// obtain sstream length 
	int len1 = ss1.str().size(), len2, i = 0;
	
	len2 = len1;

	// remove white space characters
	for (int i = 0; i < len1; i++) {

		ss1 >> skipws >> infix[i];
		if (temp[i] == ' ')
			len2--;
	}

	// init stack
	stk.push(" ");

	// reverse polish notation 
	while(i < len2) {

		string buff = "";
        char ch;

		// get output items
		if (infix[i] != '/' && infix[i] != '*' &&
			infix[i] != '+' && infix[i] != '-' &&
			infix[i] != '(' && infix[i] != ')') {

			while (infix[i] != '/' && infix[i] != '*' &&
				infix[i] != '+' && infix[i] != '-' &&
				infix[i] != '(' && infix[i] != ')') {

				buff += infix[i];
				i++;
			}

			output.push(buff);
		}

		// get operators based on priority
		// apply some logic
		ch = infix[i];

		// highest precedence
		if (ch == '/') {

			stk.push("/");
		}

		// second precedence
		else if (ch == '*') {		
			
			if (stk.top() == "/") {

				while (stk.top() != "+" && stk.top() != "-" && stk.top() != "(" && stk.top() != ")") {

					output.push(stk.top());
					stk.pop();
				}
			}

			else
				stk.push("*");
		}

		// third precedence
		else if (ch == '+') {
			
			if (stk.top() == "/" || stk.top() == "*") {

				while (stk.top() != "-" && stk.top() != "(" && stk.top() != ")") {

					output.push(stk.top());
					stk.pop();
				}
			}

			else
				stk.push("+");
		}

		// fourth precedence
		else if (ch == '-') {
			
			if (stk.top() == "/" || stk.top() == "*" || stk.top() == "+") {

				while (stk.top() != "+" && stk.top() != "(" && stk.top() != ")") {

					output.push(stk.top());
					stk.pop();
				}
			}

			else
				stk.push("-");
		}

		// fourth precedence
		else if (ch == '(' ) {

			stk.push("(");
		}

		// fourth precedence
		else if (ch == ')') {

			if (stk.top() == "(")
				stk.pop();

			while (stk.top() != "(") {

				output.push(stk.top());
				stk.pop();
			}
		}

		i++;
	}

	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {
	return 0;
} // end-EvaluatePostfixExpression
