// #include <iostream>
#include <random>
// #include <sstream> 
// #include <thread>
#include <cstring>

#include "client.h"

//using namespace std;
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
    std::random_device rd;  // ������Ϊ���������������
    std::mt19937 gen(rd()); // �Բ��ֱ�׼ mersenne_twister_engine
    uniform_int_distribution <int> dis(MIN, MAX);
    // �� dis �任 gen �����ɵ���� unsigned int �� [MIN, MAX] �е� int
    return dis(gen);
}
// string *gendata(int n = 1) {
//     string* datalist= new string[n]();
//     for (int i = 0; i < n; ++i) {
//         datalist[i] = std::to_string(keyRand()) + strRand();
     
//     }
//     return datalist;

// }
// string writevalue(int n) { 
//     string* b;
//     b = gendata(n);
//         for (int i = 0; i < n; i++)
//         {
//             *(b + i) = 'w' + *(b + i);
           
//             cout  << *(b + i) << endl;
//         }
//         return *b;
//      }

std::pair<std::string, int>  gendata() {
    return make_pair(strRand(), keyRand());
    //return std::to_string(keyRand()) + strRand();
}

std::pair<char*, int> Client::request_master(std::string sendline){
    auto recvline = socket_client.send_line(master_ip, master_port, sendline.c_str());
    if (recvline != nullptr){
        strncpy(cache_ip, recvline, 16);
        cache_port = atoi(recvline + 16);
        return make_pair(cache_ip, cache_port);
    }
    return make_pair(nullptr, -1);
}

bool Client::write_local(std::string key, std::pair<char*, int> cache){
    list.append(key, cache.first + std::to_string(cache.second));
    return true;
}


char* Client::request_cache(const char* ip, int port, std::string data){
    auto recvline = socket_client.send_line(master_ip, master_port, data.c_str());
    return recvline;
}

void Client::run_client(){
    std::pair<char*, int> cache;
    std::pair<std::string, int> data;
    string sendline;
    while(true){
        data = gendata();
        cache = request_master(data.first); // send key to master
        write_local(data.first, cache);
        if (is_write){
            sendline = 'w' + data.first + std::to_string(data.second);
        }
        else {
            sendline = 'r' + data.first + std::to_string(data.second);
        }
        request_cache(cache.first, cache.second, sendline);
        sleep(1);
    }
}

Client::Client(const char* ip, int port){
    master_ip = new char[20];
    cache_ip = new char[20];
    buff = new char[MAXLEN];
    
    strcpy(master_ip, ip);
    master_port = port;
    is_write = true;
}

Client::~Client(){
    delete master_ip;
    delete cache_ip;
}

int main(int argc, char** argv){
    if (argc <= 4){
        printf("Usage: ./cache $IP1 $PORT1 $IP2 $PORT2\n");
        return 0;
    }
    
    char* ip1 = argv[1];
    int port1 = atoi(argv[2]);
    // char* ip2 = argv[3];
    // int port2 = atoi(argv[4]);
    Client client(ip1, port1);
    return 0;
}





// int main(){
    
//     SingleLinkedList<string> list;
//     list.append(*gendata(1), "1");
//     list.append(*gendata(1), "1");
//     list.append(*gendata(1), "2");
//     list.append(*gendata(1), "3");
//     list.append(*gendata(1), "0");
//     list.print();
//     cout << list.length() << endl;
    

//     return 0;

// }