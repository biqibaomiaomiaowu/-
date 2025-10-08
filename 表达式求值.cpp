//���ʽ��ֵ--��׺���ʽ��ֵ
//������־:
//1.����
//2.���Ǳ��ʽ��ȫ��ȷ������µ�ת��������
//3.����˼Ӽ��˳�ȡģ�η����ŵĿ��
//4.����˵�ջ����
//5.��������й��ܣ�����������ʱ��֧��С������֧�ִ���ı��ʽ
//6.Ŀǰ֧��С��
//7.�������������
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
double trasform_and_calculate(string s)//����һ��ת��һ�߼���ķ�ʽ
{
	stack<double>num;//����ջ
	stack<char>ope;//����ջ
	for (int i = 0; i < s.size(); i++)
	{
		//�������ּ�������ջ--�ж����������������������Ϊһ����
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
					}//����ջ��ջ����,Ȼ���ٰѡ�+���Ž�ȥ;
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
					}//����ջ��ջ����,Ȼ���ٰѡ�-���Ž�ȥ;
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
			ope.pop();//��ջ��������
		}
	}
	//�������к�ʼ��ջ����
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