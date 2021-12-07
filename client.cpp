#include <iostream>
#include <map> 
#include <string>  
#include <random>

using namespace std;
using std::string;
using std::random_device;
using std::default_random_engine;

string strRand(int length = 8) {			// length: �����ַ����ĳ���
    char tmp;							// tmp: �ݴ�һ�������
    string buffer;						// buffer: ���淵��ֵ

   
    random_device rd;					// ����һ�� std::random_device ���� rd
    default_random_engine random(rd());	// �� rd ��ʼ��һ������������� random

    for (int i = 0; i < length; i++) {
        tmp = random() % 36;	// ���һ��С�� 36 ��������0-9��A-Z �� 36 ���ַ�
        if (tmp < 10) {			// ��������С�� 10���任��һ�����������ֵ� ASCII
            tmp += '0';
        }
        else {				// ���򣬱任��һ����д��ĸ�� ASCII
            tmp -= 10;
            tmp += 'A';
        }
        buffer += tmp;
    }
    return buffer;
}

int keyRand() {

    constexpr int MIN = 10000000;
    constexpr int MAX = 99999999;
    random_device rd;
    std::default_random_engine eng(rd());
    uniform_int_distribution<int> distr(MIN, MAX);
    return distr(eng);
}



int main() {

    cout << keyRand();


         return 0;
 }


    













