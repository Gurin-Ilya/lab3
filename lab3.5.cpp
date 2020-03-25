#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <math.h>

using namespace std;
const int SIZE = 180;
const int n = 6;

void FillArray(double X[], double Y[])
{

	// Создаем файловый указатель
	fstream fin;

	// Открываем существующий файл
	fin.open("19.csv", ios::in);
	int count = 0, j = 0;
	double v;
	// Считываем данные из файла в виде строкового вектора 
	vector<string> row;
	string line, word, temp;
	// Пропускаем заголовок (первую строку без данных)
	getline(fin, line);

	while (count < 203) {

		row.clear();

		getline(fin, line);
		stringstream s(line);

		while (getline(s, word, ',')) {
			row.push_back(word);
		}

		//запись в массив температуры в августе без 999.9
		for (int i = 0; i < 13; i++) {
			if ((i == 0) && (stod(row[i]) != 999.9)) {
				X[j] = stod(row[i]);
			}
			if ((i == 8) && (stod(row[i]) != 999.9)) {
				Y[j] = stod(row[i]);
				j++;
			}
		}
		count++;
	}

}


double* gauss(double a[][n], double* y, int n)
{
	double* x, max;
	int k, index;
	const double eps = 0.00001; // точность
	x = new double[n];
	k = 0;
	while (k < n)
	{
		// Поиск строки с максимальным a[i][k]
		max = abs(a[k][k]);
		index = k;
		for (int i = k + 1; i < n; i++)
		{
			if (abs(a[i][k]) > max)
			{
				max = abs(a[i][k]);
				index = i;
			}
		}
		// Перестановка строк
		if (max < eps)
		{
			// нет ненулевых диагональных элементов
			cout << "0 collumn ";
			cout << index << " matrix A" << endl;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			double temp = a[k][j];
			a[k][j] = a[index][j];
			a[index][j] = temp;
		}
		double temp = y[k];
		y[k] = y[index];
		y[index] = temp;
		// Нормализация уравнений
		for (int i = k; i < n; i++)
		{
			double temp = a[i][k];
			if (abs(temp) < eps) continue; // для нулевого коэффициента пропустить
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] / temp;
			y[i] = y[i] / temp;
			if (i == k) continue; // уравнение не вычитать само из себя
			for (int j = 0; j < n; j++)
				a[i][j] = a[i][j] - a[k][j];
			y[i] = y[i] - y[k];
		}
		k++;
	}
	// обратная подстановка
	for (k = n - 1; k >= 0; k--)
	{
		x[k] = y[k];
		for (int i = 0; i < k; i++)
			y[i] = y[i] - a[i][k] * x[k];
	}
	return x;
}

int main() {
	ofstream fout;
	double year[SIZE];
	double temper[SIZE];
	FillArray(year, temper);
	/*//Показать массивы
	for (int i = 0; i < SIZE; i++) {
		cout << year[i] << "\t" << temper[i] << endl;
	}
	*/
	fout.open("Cloud.txt");
	for (int i = 0; i < SIZE; i++) {
		fout << year[i] << "\t" << temper[i] << endl;
	}
	fout.close();
	
	double x[n][n] = {{},{},{},{},{},{}};
	double X = 0;//сумма всех лет
	double Y = 0;//сумма всех температур в августе
	double y[n] = {};
	double* a;
	system("chcp 1251");
	system("cls");

	
	//Заполнение x
	x[0][0] = SIZE;
	for (int i = 0; i < SIZE; i++)
	{
		x[0][1] += year[i];
		x[1][0] += year[i];
	}
	for (int i = 0; i < SIZE; i++)
	{
		x[0][2] += year[i] * year[i];
		x[2][0] += year[i] * year[i];
		x[1][1] += year[i] * year[i];
	}
	for (int i = 0; i < SIZE; i++)
	{
		x[0][3] += pow(year[i], 3);
		x[3][0] += pow(year[i], 3);
		x[1][2] += pow(year[i], 3);
		x[2][1] += pow(year[i], 3);
	}
	for (int i = 0; i < SIZE; i++)
	{
		x[0][4] += pow(year[i], 4);
		x[4][0] += pow(year[i], 4);
		x[1][3] += pow(year[i], 4);
		x[3][1] += pow(year[i], 4);
		x[2][2] += pow(year[i], 4);
	}
	for (int i = 0; i < SIZE; i++)
	{
		x[0][5] += pow(year[i], 5);
		x[5][0] += pow(year[i], 5);
		x[1][4] += pow(year[i], 5);
		x[4][1] += pow(year[i], 5);
		x[2][3] += pow(year[i], 5);
		x[3][2] += pow(year[i], 5);
	}
	for (int i = 0; i < SIZE; i++)
	{
		x[1][5] += pow(year[i], 6);
		x[5][1] += pow(year[i], 6);
		x[2][4] += pow(year[i], 6);
		x[4][2] += pow(year[i], 6);
		x[3][3] += pow(year[i], 6);
	}
	for (int i = 0; i < SIZE; i++)
	{
		x[2][5] += pow(year[i], 7);
		x[5][2] += pow(year[i], 7);
		x[3][4] += pow(year[i], 7);
		x[4][3] += pow(year[i], 7);
	}
	for (int i = 0; i < SIZE; i++)
	{
		x[3][5] += pow(year[i], 8);
		x[5][3] += pow(year[i], 8);
		x[4][4] += pow(year[i], 8);
	}
	for (int i = 0; i < SIZE; i++)
	{
		x[4][5] += pow(year[i], 9);
		x[5][4] += pow(year[i],9);
	}
	for (int i = 0; i < SIZE; i++)
	{
		x[5][5] += pow(year[i],10);
	}

	//заполнение y
	for (int i = 0; i < SIZE; i++)
	{
		y[0] += temper[i];
		y[1] += year[i] * temper[i];
		y[2] += year[i] * year[i] * temper[i];
		y[3] += pow(year[i], 3) * temper[i];
		y[4] += pow(year[i], 4) * temper[i];
		y[5] += pow(year[i], 5) * temper[i];
	}
	
	/*
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << x[i][j] << endl;
		}
	} cout << "================"<<endl;
	for (int i = 0; i < n; i++) {		
		cout << y[i] << endl;
	}
	*/
	


	a = gauss(x, y, 6);
	/*
	
	for (int i = 0; i < n; i++)
		cout << "x[" << i << "]=" << x[i] << endl;
	cin.get(); cin.get();
	*/
	
	/*
	for (int i = 0; i < n; i++) {
		cout << a[i] << endl;
	}
	*/

	
	fout.open("Koordin.txt");
	for (int i = 0; i < SIZE; i++) {
		cout << year[i] << "\t" << (a[0] + a[1] * year[i] + a[2] * pow(year[i], 2) + a[3] * pow(year[i], 3)
			+ a[4] * pow(year[i], 4) + a[5] * pow(year[i], 5)) << endl;
		fout << year[i] << "\t" << (a[0] + a[1] * year[i] + a[2] * pow(year[i], 2) + a[3] * pow(year[i], 3)
			+ a[4] * pow(year[i], 4) + a[5] * pow(year[i], 5)) << endl;
	}
	fout.close();
	system("python3 Lab3_5.py");
	return 0;
}
