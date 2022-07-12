// delenie polinomov.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <string>
#include <vld.h>
using namespace std;
vector<float> strToVec(string str)
{
	//преобразование строки вида [ 0.1 0 1 3 2 ] в вектор
	vector<float> returnVector;
	string buff;
	bool sep = false;
	for (int i = 0; i < str.size(); i++)
	{
		
		if ((str[i] != '[') && (str[i] != ']'))
		{
			if ((str[i] == ' ')&&(buff.size()>0))
			{
				//buff -> vec[i]
				returnVector.push_back(stof(buff));
				buff.clear();
			}
			else if (str[i] == ' ') { continue; }
			else
				buff += str[i];
		}
		
		
	}
	return 2; //returnVector;
}
class polinom : public vector<float> {
public:
	polinom(vector<float> init) { for (int i = 0; i < init.size(); i++) { this->push_back(init[i]); } };
};
const polinom operator+(polinom& left, polinom& right) 
{
	vector<float> newKoeffs;
	int newInt = 0;
	if (left.size() >= right.size())
	{
		for (int i = 0; i < left.size(); i++)
		{
			newInt = right[i] + left[i];
			newKoeffs.push_back(newInt);
			newInt = 0;
		}
		polinom newPoli(newKoeffs);
		return newPoli;

	}
	else {
		for (int i = 0; i < right.size(); i++)
		{
			newInt = right[i] + left[i];
			newKoeffs.push_back(newInt);
			newInt = 0;
		}
		polinom newPoli(newKoeffs);
		return newPoli;
	}

}
const polinom operator/(const polinom& left, polinom& right) {
	polinom r1 = left;
	polinom t1 = right;
	//шаг 0. поиск delta
	int delta = r1.size() - right.size();
	//шаг 0.5. инициализация q1 - quotient
	vector<float> q1Vec;
	for (int i = 0; i < delta+1; i++) { q1Vec.push_back(0.f); }
	polinom q1(q1Vec);
	int q1Ptr = delta;
	while (r1.size() >= right.size()) {
		//шаг 1. поиск kDelta
		float kDelta = r1[r1.size() - 1] / right[right.size() - 1];
		//шаг 2. умножение kDelta * right
		for (int i = 0; i < right.size(); i++)
		{
			t1[i] = right[i] * kDelta;
		}
		//шаг 3. r1 = r1 - kDelta * right ^ delta
		for (int i = 0; i < right.size(); i++)
		{
			r1[r1.size() - 1 - i] = r1[r1.size() - 1 - i] - t1[t1.size() - 1 - i];
		}
		//шаг 4. q1 + t1
		q1[q1Ptr] = kDelta;
		q1Ptr--;
		//шаг 5. удаление пустых старших степеней.
		while (r1[r1.size() - 1] == 0)
		{
			r1.pop_back();
		}
	}
	return q1;

}
const polinom operator%(const polinom& left, const polinom& right) {
	polinom r1 = left;
	polinom t1 = right;
	//шаг 0. поиск delta
	int delta = r1.size() - right.size();
	//шаг 0.5. инициализация q1 - quotient
	vector<float> q1Vec;
	for (int i = 0; i < delta+1; i++) { q1Vec.push_back(0.f); }
	polinom q1(q1Vec);
	int q1Ptr = delta;
	while (r1.size() >= right.size()) {
		//шаг 1. поиск kDelta
		float kDelta = r1[r1.size() - 1] / right[right.size() - 1];
		//шаг 2. умножение kDelta * right
		for (int i = 0; i < right.size(); i++)
		{
			t1[i] = right[i] * kDelta;
		}
		//шаг 3. r1 = r1 - kDelta * right ^ delta
		for (int i = 0; i < right.size(); i++)
		{
			r1[r1.size() - 1 - i] = r1[r1.size() - 1 - i] - t1[t1.size() - 1 - i];
		}
		//шаг 4. q1 + t1
		q1[q1Ptr] = kDelta;
		q1Ptr--;
		//шаг 5. удаление пустых старших степеней.
		while (r1[r1.size() - 1] == 0)
		{
			r1.pop_back();
		}
	}
	return r1;
}
const polinom operator*(const polinom& left, polinom& right) {
	int delta = left.size() + right.size() - 1;
	vector<float> resVec;
	for (int i = 0; i < delta; i++) { resVec.push_back(0.f); }
	polinom res(resVec);
	for (int i = 0; i < left.size(); i++)
	{
		for (int j = 0; j < right.size(); j++)
		{
			res[i + j] += left[i] * right[j];
		}
	}
	return res;
}
int main()
{
	vector<float> tmp1;
	string a;
	a = "[ 1 2 3 ]";
	tmp1 = strToVec(a);
	polinom mn1(tmp1);
	a = "[ -3 1 ]";
	tmp1 = strToVec(a);
	polinom mn2(tmp1);
	polinom res = mn1 * mn2;

	a = "[ -42 0 -12 1 ]";
	tmp1 = strToVec(a);
	polinom divd(tmp1);
	a = "[ -3 1 ]";
	tmp1 = strToVec(a);
	polinom divs(tmp1);
	polinom quot = divd / divs;
	polinom rem = divd % divs;
	//a + b;
	//a / b;
	//a * b;
	//a % b;
	//a[0];
    std::cout << "Hello World!\n";
	system("pause");
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
