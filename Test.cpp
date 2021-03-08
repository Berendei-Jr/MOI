#include <iostream>
#include <math.h>
using namespace std;

bool Prime(unsigned int& p) {
	if (p >= 2) {
		for (int i = 2; i < p; i++) {
			if (p % i == 0) {
				cout << "Введенное число не является простым!\n";
				return false;
			}
		}
	}
	return true;
}

void Check(unsigned int& p, int index, int length, unsigned int* ARR1, unsigned int* ARR2) {
	unsigned int k = 0;
	for (int i = index; i < (index + length); i++) {
		for (int j = 0; j < floor((p + 1) / 2); j++) {
			if (ARR1[i] == ARR2[j]) {
				//cout << "Chislo " << ARR1[i] << endl;
				k++;
				break;
			}
		}
	}
	if (k > (length - k)) {
		cout << "Операция завершена. Больше плюсов (на " << k - (length - k) << ")\n";
	}
	else if (k == (length - k)) { cout << "Плюсов и минусов равное количество\n"; }
	else cout << "Операция завершена. Больше минусов (на " << (length - k) - k << ")\n";
	cout << "Плюсов: " << k << endl;
	cout << "Минусов: " << (length - k) << endl;
}

int Count_pluses(unsigned int& p, unsigned int* ARR1, unsigned int* ARR2) {
	int k = 0, s;
	cout << "Расчет количества 'плюсов'..." << endl;
	for (int i = 0; i < ((p + 1) / 2); i++) {
		for (int j = 0; j < ((p + 1) / 2); j++) {
			if (ARR1[i] == ARR2[j]) {
				k++;
				break;
			}
		}
		if (i == ((p + 1) / 8)) {
			cout << "Завершено на 25%...\n";
		}
		if (i == ((p + 1) / 4)) {
			cout << "Завершено на 50%...\n";
		}
		if (i == ((p + 1) / 8 * 3)) {
			cout << "Завершено на 75%...\n";
		}
		if (i == ((p + 1) / 2)) {
			cout << "Завершено на 100%...\n";
		}
	}
	return k * 2;
}

int Move(unsigned int& p, int index, int length, unsigned int* ARR1, unsigned int* ARR2) {
label0:
	char Ch;
	cout << "\n\nПеремещаемся вправо или влево? [R, L]  "; cin >> Ch;
	if (Ch == 'R' || Ch == 'r') {
		int index_0 = index + length;
		if ((index_0 + length) > p) {
			cout << "Выход за границу справа!\n";
			goto label0;
		}
		Check(p, index_0, length, ARR1, ARR2);
		cout << "index = " << index_0;
		return index_0;
	}

	else {
		int index_0 = index - length;
		if ((index_0 - length) < 0) {
			cout << "Выход за границу слева!\n";
			goto label0;
		}
		Check(p, index_0, length, ARR1, ARR2);
		return index_0;
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	unsigned int p;
label:
	p = 0;
	cout << "Введите простое число Р: "; cin >> p;
	if (Prime(p) == false)goto label;

	unsigned int* ARR1 = new unsigned int[p];
	cout << "Расчет первого массива" << endl;
	for (int i = 1; i < p; i++) {
		ARR1[i - 1] = i;
	}

	unsigned int* ARR2 = new unsigned int[p];
	cout << "Расчет квадратов чисел массива по модулю P" << endl;
	for (int i = 1; i < p; i++) {
		ARR2[i - 1] = ((i * i) % p);
	}

	int c ;
	c = 0;
	cout << "\n   Введите значение константы С: "; cin >> c;
	const int length = floor(c * (log(p) / log(2) + log((log(p) / log(2)) / log(2))));  //C(Log2(p) +log2(log2(p)))
	cout << "L = " << length << endl;

label1:
	int index;
	cout << "Введите индекс начального положения: "; cin >> index;
	if ((index + length) > p) {
		cout << "Выход за границу справа!\n";
		goto label1;
	}

	Check(p, index, length, ARR1, ARR2);

	for (int i = 0; i < 20; i++)index = Move(p, index, length, ARR1, ARR2);

	return 0;
}