#include <iostream>
#include <math.h>
using namespace std;

bool Check_Prime(unsigned long long& p) {
    if (p >= 2) {
        for (unsigned long long i = 2; i < p; i++) {
            if (p % i == 0) {
                cout << "Введенное число не является простым!\n";
                return false;
            }
        }
    }
    return true;
}

class Prime {
    unsigned long long p;
    unsigned long long *ARR1 = nullptr;
    unsigned long long *ARR2 = nullptr;
public:
    Prime(unsigned long long p) {
        this->p = p;
        ARR1 = new unsigned long long[p];
        for (unsigned long i = 1; i < p; i++) {
            ARR1[i - 1] = i;
        }
        ARR2 = new unsigned long long[p];
        for (unsigned long long i = 1; i < p; i++) {
            ARR2[i - 1] = (i * i) % p;
        }
    }

    long Count_pluses() {
        long k = 0, s;
        cout << "Ход выполнения операции:\n";
        for (unsigned long i = 0; i < (p-1)/2; i++) {
            for (unsigned long j = 0; j < (p-1)/2; j++) {
                if (ARR1[i] == ARR2[j]) {
                    k++;
                    break;
                }
            }
        cout << "\b\b\b\b" << ((i+1) * 100 / ((p - 1) / 2))<<"%";
        }
        return 2 * k;
    }

    long Count_quarter(){
        return floor((p-1)/4);
    }

    void Check(long index, long length) {
        long k = 0;
        for (long i = index; i < (index + length); i++) {
            for ( long j = 0; j < floor((p + 1) / 2); j++) {
                if (ARR1[i] == ARR2[j]) {
                    //cout << "Chislo " << ARR1[i] << endl;
                    k++;
                    break;
                }
            }
        }
        if (2*k > length) {
            cout << "РЕЗУЛЬТАТ: Больше плюсов (на " << abs(length - (2*k)) << ")\n";
        }
        else if (2*k == length) { cout << "РЕЗУЛЬТАТ: плюсов и минусов равное количество\n"; }
        else cout << "РЕЗУЛЬТАТ: Больше минусов (на " << abs(length - (2*k)) << ")\n";
        cout << "Плюсов: " << k << endl;
        cout << "Минусов: " << (length - k) << endl;
        cout << "Текущий диапазон: " << index+1 << " - " << index+length << endl;
    }

    long Move(long index, long length) {
        label0:
        char Ch;
        cout << "\n\n   Перемещаемся вправо или влево? [R, L]  ";
        cin >> Ch;
        if (Ch == 'R' || Ch == 'r') {
            cout << "   Выберите режим сдвига:\n";
            cout << "1) На длину отрезка\n";
            cout << "2) Ввести длину сдвига вручную\n";
            char Ch;
            cin >> Ch;
            if (Ch == '1') {
                long index_0 = index + length;
                if ((index_0 + length) > p) {
                    cout << "Выход за границу справа!\n";
                    goto label0;
                }
                Check(index_0, length);
                return index_0;
            }
            if (Ch == '2') {
                long delta_length;
                cout << " Введите длину сдвига: ";
                cin >> delta_length;
                long index_0 = index + delta_length + length;
                if (index_0 > p) {
                    cout << "Выход за границу справа!\n";
                    goto label0;
                }
                Check(index + delta_length, length);
                return index + delta_length;
            }
        }
            else {
                cout << "   Выберите режим сдвига:\n";
                cout << "1) На длину отрезка\n";
                cout << "2) Ввести длину сдвига вручную\n";
                char Ch;
                cin >> Ch;
                if (Ch == '1') {
                    long index_0 = index - length;
                    if (index_0 < 0) {
                        cout << "Выход за границу слева!\n";
                        goto label0;
                    }
                    Check(index_0, length);
                    return index_0;
                }
                if (Ch == '2') {
                    cout << " Введите длину сдвига: ";
                    long delta_length; cin >> delta_length;
                    long index_0 = index-delta_length - length;
                    if (index-delta_length < 0) {
                        cout << "Выход за границу справа!\n";
                        goto label0;
                    }
                    Check(index-delta_length, length);
                    return index-delta_length;
                }
            }
    }
};

int main() {
    unsigned long long p;
    label:
    p = 0;
    cout << "Введите простое число Р: "; cin >> p;
    if (Check_Prime(p) == false)goto label;
    Prime P (p);
   // cout << P.Count_pluses() << endl;

   cout << "   Выберите режим работы:\n";
   cout << "1) Ввести константу\n";
   cout << "2) Ввести длину отрезка\n";
   cout << "3) Рассчитать первую четверть\n";
   char Ch; cin >> Ch;

   long length, index;
   if(Ch == '1') {
       double c;
       c = 0;
       cout << "\n   Введите значение константы С: ";
       cin >> c;
       length = floor(c * (log(p) / log(2) + log((log(p) / log(2)) / log(2))));  //C(Log2(p) +log2(log2(p)))
       label1:
       cout << "   Введите индекс начального положения: "; cin >> index;
       if ((index + length) > p) {
           cout << "Выход за границу справа!\n";
           goto label1;
       }
   }
   else if(Ch == '2'){
       cout << "\n   Введите значение длины: ";
       cin >> length;
       label2:
       cout << "   Введите индекс начального положения: "; cin >> index;
       if ((index + length) > p) {
           cout << "Выход за границу справа!\n";
           goto label2;
       }
   }
   else if(Ch == '3'){
        length = P.Count_quarter();
        index = 0;
   }
    cout << "Длина отрезка = " << length << endl;

    P.Check(index, length);

    for (int i = 0; i < 20; i++)index = P.Move(index, length);

    return 0;

}
