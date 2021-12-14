#include <iostream>
#include <string>  
#include <random>
#include <sstream> 
#include "SingleLinkedList.h"

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
    std::random_device rd;  // ������Ϊ���������������
    std::mt19937 gen(rd()); // �Բ��ֱ�׼ mersenne_twister_engine
    uniform_int_distribution <int> dis(MIN, MAX);
    // �� dis �任 gen �����ɵ���� unsigned int �� [MIN, MAX] �е� int
    return dis(gen);
}
string *gendata(int n = 1) {
    string* datalist= new string[n]();
    for (int i = 0; i < n; ++i) {
        datalist[i] = std::to_string(keyRand()) + strRand();
     
    }
    return datalist;

}
string writevalue(int n) { 
    string* b;
    b = gendata(n);
        for (int i = 0; i < n; i++)
        {
            *(b + i) = 'w' + *(b + i);
           
            cout  << *(b + i) << endl;
        }
        return *b;
     }

    

template<typename T>
SingleLinkedList<T>::SingleLinkedList() {
    this->head = new Node<T>();//����Ĭ�Ϲ�����
    this->size = 0;//��ʼ������Ϊ0
    this->head->next = NULL;
}

template<typename T>
SingleLinkedList<T>::~SingleLinkedList() {

}

template<typename T>
int SingleLinkedList<T>::length() {
    return this->size;
}


template<typename T>
bool SingleLinkedList<T>::checkIndex(int index) {
    return index >= 0 && index <= size;
}


template<typename T>
Node<T> * SingleLinkedList<T>::node(int index) {
    checkIndex(index);
    Node<T>* n = this->head;
    for (int i = 0; i < index; i++) {
        n = n->next;
    }
    return n;
}


template<typename T>
bool SingleLinkedList<T>::append(T value , T address) {
    Node<T>* newNode = new Node<T>( value,  address);//����ڵ����

    
    if (this->size == 0) {
        this->head = newNode;
    }
       
    Node<T>* temp = this->head;
    while (temp->next != NULL) {//��ͷ�ڵ㿪ʼ���ҵ����һ���ڵ㣬�ж������б�����n->next����������n
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = NULL;

    size++;

    return true;
}


template<typename T>
bool SingleLinkedList<T>::insert(int index, T value, T address) {
    checkIndex(index);

    Node<T>* newNode = new Node<T>( value, address);

    if (index == 0) {//�����½ڵ���Ϊ����ͷ�ڵ�
        newNode->next = this->head;
        this->head = newNode;
    }
    else if (index == size) {//�����½ڵ���Ϊβ���ڵ�
        append(value, address);
    }
    else {//����λ���½ڵ㵽index����֮��
        //��ȡindex�����ϵĽڵ�
        Node<T>* nIndex_pre = node(index - 1);//��ȡindex-1λ���ϵĽڵ�
        Node<T>* nIndex = node(index);//��ȡindex�����ϵĽڵ�
        nIndex_pre->next = newNode;
        newNode->next = nIndex;
    }
    size++;
    return true;
}


template<typename T>
void SingleLinkedList<T>::print() {
    //�������Ϊ��
    if (NULL == this->head) {
        cout << "This list is empty.";
        return;//����������У�����Ĵ��벻��ִ��
    }
    //����Ϊ��
    Node<T>* n = this->head;
    while (NULL != n) {//�˴����ж������У�ֻ����n����������n->next
        cout << n->value << "--"<<n->address;
        cout << endl;
        n = n->next;
    }
    cout << '\n';//����
}
template<typename T>
T SingleLinkedList<T>::get(int index) {
    return node(index)->address;
}
template<typename T>
bool SingleLinkedList<T>::remove(int index) {
    checkIndex(index);

    if (index == 0) {//ɾ����ͷ�ڵ�
        Node<T>* nHead = this->head;
        Node<T>* nHead_next = nHead->next;

        this->head = nHead_next;
    }
    else if (index == size) {//ɾ�������������һ���ڵ�
        Node<T>* nIndex_pre = node(index - 1);
        nIndex_pre->next = NULL;
    }
    else {//ɾ�������м�ڵ�
        Node<T>* nPre = node(index - 1);
        Node<T>* nNext = node(index + 1);
        nPre->next = nNext;
    }
    size--;
    return true;
}
template<typename T>
void SingleLinkedList<T>::freeList() {

    Node<T>* n1 = this->head, * n2;
    while (NULL != n1) {
        n2 = n1->next;
        delete n1;
        n1 = n2;
    }
}





    int main(){
        
        SingleLinkedList<string> list;
        list.append(*gendata(1), "1");
        list.append(*gendata(1), "1");
        list.append(*gendata(1), "2");
        list.append(*gendata(1), "3");
        list.append(*gendata(1), "0");
        list.print();
        cout << list.length() << endl;
       

        return 0;

    }