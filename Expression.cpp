#include <string>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#define max 255
using namespace std;

///----------------------------------------------------------------------------------
/// Given an expression in infix-notation, converts it to a string in post-fix notation 
/// 
string Infix2Postfix(string &s) {

	vector<string>output; // for operands and operators popped from stack
	stack<string>stk; // stack for storing operations
	string result, temp;
	stringstream ss1(s); // stringstream for removing white space characters
	stringstream ss2(s); // for temporal storage and obtaining string length
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

			output.push_back(buff);
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

					output.push_back(stk.top());
					stk.pop();
				}
			}

			else
				stk.push("*");
		}

		// third precedence
		else if (ch == '+') {
			
			if (stk.top() == "/" || stk.top() == "*"|| stk.top() == "+") {

				while (stk.top() != "-" && stk.top() != "(" && stk.top() != ")") {

					output.push_back(stk.top());
					stk.pop();
				}
			}

			else
				stk.push("+");
		}

		// fourth precedence
		else if (ch == '-') {
			
			if (stk.top() == "/" || stk.top() == "*" || stk.top() == "+" || stk.top() == "-") {

				while (stk.top() != "(" && stk.top() != ")") {

					output.push_back(stk.top());
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

			while (1) {

				if (stk.top() != "(") {

					output.push_back(stk.top());
					stk.pop();
				}

				else if (stk.top() == "(") {

					stk.pop();

					if(stk.top() == "(")
						stk.pop();

					break;
				}
			}
		}

		i++;
	}

	int k = 0;
	while (k < output.size()) {

		result += output[k] + " ";
		k++;
	}

	return result;
} // end-Infix2Postfix

///----------------------------------------------------------------------------------
/// Given a string in post-fix notation, evaluates it and returns the result
/// 
int EvaluatePostfixExpression(string& s) {

	string temp, str;
	stringstream ss1(s); // stringstream for removing white space characters
	vector<string>newpostfix;
	stack<int>stk;
	getline(ss1, temp);

	// obtain sstream length 
	int len1 = ss1.str().size(), i = 0;

	// remove white space characters
	while (i < len1) {

		str = "";

		while (temp[i] != ' ' && temp[i] != '\0') {

			str += temp[i];
			i++;
		}

		newpostfix.push_back(str);
		i++;
	}// end-while
	
	int k = 0, num;

	while (k < newpostfix.size()) {

		string temp = newpostfix[k];

		if (temp != "/" && temp != "*" && temp != "+" && temp != "-") {

			stringstream ss2;

			ss2 << temp;
			ss2 >> num;
			stk.push(num);
		}

		// compute
		int num1, num2, result;

		if (temp == "/") {

			num1 = stk.top();
			stk.pop();
			num2 = stk.top();
			stk.pop();
			result = num2 / num1;
			stk.push(result);
		}
		else if (temp == "*") {

			num1 = stk.top();
			stk.pop();
			num2 = stk.top();
			stk.pop();
			result = num2 * num1;
			stk.push(result);
		}
		else if (temp == "+") {

			num1 = stk.top();
			stk.pop();
			num2 = stk.top();
			stk.pop();
			result = num2 + num1;
			stk.push(result);
		}   	
		else if (temp == "-") {

			num1 = stk.top();
			stk.pop();
			num2 = stk.top();
			stk.pop();
			result = num2 - num1;
			stk.push(result);
		}

		k++;
	}// end-while

	return stk.top();
} // end-EvaluatePostfixExpression
