//表达式求值--中缀表达式求值
//开发日志:
//1.搭建框架
//2.考虑表达式完全正确的情况下的转化并计算
//3.完成了加减乘除取模次方括号的框架
//4.完成了弹栈计算
//5.完成了所有功能，但是数字暂时不支持小数，不支持错误的表达式
//6.目前支持小数
//7.更改了输出精度
#include<iostream>
#include<string>
#include<stack>
#include<cmath>
#include<iomanip>
using namespace std;
void calculate(stack<double>& num, char ope) 
{
	if (ope == '+') {
		double temp1 = num.top();
		num.pop();
		double temp2 = num.top();
		num.pop();
		num.push(temp1 + temp2);
	}
	if (ope == '-') {
		double temp1 = num.top();
		num.pop();
		double temp2 = num.top();
		num.pop();
		num.push(temp2- temp1);
	}
	if (ope == '*') {
		double temp1 = num.top();
		num.pop();
		double temp2 = num.top();
		num.pop();
		num.push(temp1 * temp2);
	}
	if (ope == '/') {
		double temp1 = num.top();
		num.pop();
		double temp2 = num.top();
		num.pop();
		num.push(temp2 /temp1);
	}
	if (ope == '%') {
		int temp1 = num.top();
		num.pop();
		int temp2 = num.top();
		num.pop();
		num.push(temp2 % temp1);
	}
	if (ope == '^') {
		double temp1 = num.top();
		num.pop();
		double temp2 = num.top();
		num.pop();
		num.push(pow(temp2,temp1));
	}
}
double trasform_and_calculate(string s)//采用一边转化一边计算的方式
{
	stack<double>num;//数字栈
	stack<char>ope;//符号栈
	for (int i = 0; i < s.size(); i++)
	{
		//遇见数字加入数字栈--判断如果是连续的数，则整体为一个数
		if (s[i] >= '0' && s[i] <= '9')
		{
			stack<double>temp_num;
			int position_point = 0;
			temp_num.push(s[i] - '0');
			while (s[i + 1] >= '0' && s[i + 1] <= '9' || s[i + 1] == '.')
			{
				if (s[i + 1] >= '0' && s[i + 1] <= '9') {
					temp_num.push(s[i + 1] - '0');
					i++;
				}
				else {
					position_point = temp_num.size();
					i++;
				}
			} 
			double sum = 0;
			int digit = 1;
			if(position_point!=0)
			position_point = temp_num.size() - position_point;
			while (!temp_num.empty()) {
				sum += temp_num.top()*digit;
				temp_num.pop();
				digit *= 10;
			}
			sum = sum * pow(0.1, position_point);
			num.push(sum);
		}
		if (s[i] == '+') {
			if (ope.empty()) {
				ope.push(s[i]);
			}
			else {
				if (ope.top() == '(') {
					ope.push(s[i]);
				}
				else {
					while (!ope.empty() && ope.top() != '(') {
						calculate(num,ope.top());
						ope.pop();
					}//符号栈弹栈计算,然后再把‘+’放进去;
					ope.push(s[i]);
				}
			}
		}
		if (s[i] == '-') {
			if (ope.empty()) {
				ope.push(s[i]);
			}
			else {
				if (ope.top() == '(') {
					ope.push(s[i]);
				}
				else {
					while (!ope.empty() && ope.top() != '(') {
						calculate(num, ope.top());
						ope.pop();
					}//符号栈弹栈计算,然后再把‘-’放进去;
					ope.push(s[i]);
				}
			}
		}
		if (s[i] == '*') {
			if (ope.empty()) {
				ope.push(s[i]);
			}
			else {
				if (ope.top() == '(' || ope.top() == '+' || ope.top() == '-') {
					ope.push(s[i]);
				}
				else {
					while (!ope.empty() && ope.top() != '('&&ope.top() != '+' && ope.top() != '-') {
						calculate(num, ope.top());
						ope.pop();
					}
					ope.push(s[i]);
				}
			}
		}
		if (s[i] == '/') {
			if (ope.empty()) {
				ope.push(s[i]);
			}
			else {
				if (ope.top() == '(' || ope.top() == '+' || ope.top() == '-') {
					ope.push(s[i]);
				}
				else {
					while (!ope.empty() && ope.top() != '(' && ope.top() != '+' && ope.top() != '-') {
						calculate(num, ope.top());
						ope.pop();
					}
					ope.push(s[i]);
				}
			}
		}if (s[i] == '%') {
			if (ope.empty()) {
				ope.push(s[i]);
			}
			else {
				if (ope.top() == '(' || ope.top() == '+' || ope.top() == '-') {
					ope.push(s[i]);
				}
				else {
					while (!ope.empty() && ope.top() != '(' && ope.top() != '+' && ope.top() != '-') {
						calculate(num, ope.top());
						ope.pop();
					}
					ope.push(s[i]);
				}
			}
		}
		if (s[i] == '^') {
			if (ope.empty()) {
				ope.push(s[i]);
			}
			else {
				if (ope.top() == '(' || ope.top() == '+' || ope.top() == '-'||ope.top()=='*'||ope.top()=='/') {
					ope.push(s[i]);
				}
				else {
					while (!ope.empty() && ope.top() != '(' && ope.top() != '+' && ope.top() != '-' && ope.top() != '*'&& ope.top() != '/') {
						calculate(num, ope.top());
						ope.pop();
					}
					ope.push(s[i]);
				}
			}
		}
		
		if (s[i] == '(') {
			ope.push(s[i]);
		}
		if (s[i] == ')') {
			while (ope.top()!= '(') {
				calculate(num, ope.top());
				ope.pop();
			}
			ope.pop();//弹栈出左括号
		}
	}
	//结束所有后开始弹栈运算
	while (!ope.empty()) {
		calculate(num, ope.top());
		ope.pop();
	}
	return num.top();
}
void solve () {
	string s;
	cin >> s;
	double result=trasform_and_calculate(s);
	cout<<fixed<< setprecision(2) <<result;
}
int main() {
	solve();
	return 0;
}