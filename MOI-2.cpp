#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "profile.h"
using namespace std;

class Prime {
	long long p;
	long long* ARR;
public:
	Prime() {
		p = 0;
		ARR = nullptr;
	}
	Prime(long long p) {
		this->p = p;
		ARR = new long long[p];
		for (long long i = 0; i < p; i++) {
			ARR[i] = i + 1;
		}
	}
	Prime(ifstream& in) {
		in.ignore();
		in >> p;
		//cout << p << endl;
		ARR = new long long[p];
		for (long long i = 0; i < p; i++) {
			ARR[i] = i + 1;
		}
		//in.ignore(2, '\n');
	}
	auto Even_type1() {
		long long* ARR1 = new long long[(p + 1) / 2];
		auto t = 0;
		{
			LogDuration log1 (0);
				for (long long i = 1; i < p;) {
					ARR1[(i - 1) / 2] = (ARR[i] / 2);
					i += 2;
				}
				t = log1.Time();
		}
		delete[] ARR1;
		return t;
	}
	auto Odd_type1() {
		long long* ARR1 = new long long[(p + 1) / 2];
		auto t = 0;
		{
			LogDuration log1(0);
			for (long long i = 0; i < p;) {
				ARR1[i / 2] = ((ARR[i] + p) / 2);
		
				i += 2;
			}
			t = log1.Time();
		}
		delete[] ARR1;
		return t;
	}
	auto Even_type2() {
		long long* ARR1 = new long long[(p + 1) / 2];
		auto t = 0;
		{
			LogDuration log1(0);
			for (long long i = 1; i < p;) {
				ARR1[(i - 1) / 2] = ((p + 1) / 2 * ARR[i]) % p;
				i += 2;
			}
			t = log1.Time();
		}
		delete[] ARR1;
		return t;
	}
	auto Odd_type2() {
		long long* ARR1 = new long long[(p + 1) / 2];
		auto t = 0;
		{
			LogDuration log1(0);
			for (long long i = 0; i < p;) {
				ARR1[i / 2] = ((p + 1) / 2 * ARR[i]) % p;

				i += 2;
			}
			t = log1.Time();
		}
		delete[] ARR1;
		return t;
	}
	~Prime() {
		delete[] ARR;
	}
	long long pr() {
		return this->p;
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	ifstream fin("primes1.txt");
	if (!fin) {
		cerr << "Error!\n";
		return 0;
	}

	long long even = 0, odd = 0, even_rez = 0, odd_rez = 0;
	for (int i = 0; i < 100000; i++) fin.ignore(2, '\n'); //Пропуск первых строк

	int number_of_iterations = 1000;

	char Ch;
	cout << "Выберите режим работы [0,1]: "; cin >> Ch;
	if (Ch == '0') {
		ofstream fou("rezult_0.txt");
		for (int j = 0; j < number_of_iterations; j++) {
			cout << j * 100 / number_of_iterations << "%";
			for (int i = 0; i < 100; i++) {
				Prime A(fin);
				long long e, o;
				e = A.Even_type1();
				o = A.Odd_type1();
				even += e;
				odd += o;
			}
			even_rez += even;
			odd_rez += odd;
			fou << even << " " << odd << endl;
			cout << "\b\b\b";
		}
		fou << "Overall: " << even_rez << "; " << odd_rez;
		fou.close();
	}

	else if (Ch == '1') {
		ofstream fou("rezult_1.txt");
		for (int j = 0; j < number_of_iterations; j++) {
			cout << j * 100 / number_of_iterations << "%";
			for (int i = 0; i < 100; i++) {
				Prime A(fin);
				long long e, o;
				e = A.Even_type2();
				o = A.Odd_type2();
				even += e;
				odd += o;
			}
			even_rez += even;
			odd_rez += odd;
			fou << even << " " << odd << endl;
			cout << "\b\b\b";
		}
		fou << "Overall: " << even_rez << "; " << odd_rez;
		fou.close();
	}

	else {
		cerr << "Error!\n";
		return 0;
	}	
}