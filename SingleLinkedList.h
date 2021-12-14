using namespace std;

template<typename T>

class Node {
public:
    /*�ڵ�洢������*/
    T value;
    T address;
    /*ָ����һ���ڵ��ָ��*/
    Node* next;

public:
    /*�չ�����*/
    Node() {}

    /*������*/
    Node(T a ,T b) {
        value = a;
        address = b;
    }
};

template<typename T>
class SingleLinkedList {
private:
    /*�����ȣ��洢�Ľ�����*/
    int size;

    /*��ͷ�ڵ㣬�ڵ��д洢�����ݵ�����ΪT*/
    Node<T>* head;

    /*��ȡ������ָ�������ϵĽڵ㣬�����ڲ�����*/
    Node<T>* node(int index);

public:
    /*������*/
    SingleLinkedList();

    /*��������*/
    ~SingleLinkedList();

    /*��ȡ�����ȣ�����ǰ�����н��ĸ���*/
    int length();

    /*���������Χ*/
    bool checkIndex(int index);

    /*���ָ�������ݵ�����β��*/
    bool append(T value,T address);

    /*���ָ�������ݵ�ָ��������λ��*/
    bool insert(int index, T value, T address);

    /*ɾ��ָ��λ���ϵ�����*/
    bool remove(int index);

    /*��ȡָ�������ϵ�����*/
    T get(int index);

    /*��ȡָ�����ݵ�������������ʱ����0*/
    int getIndex(T value, T address);

    /*��ָ��λ�õ������޸�Ϊ����������element*/
    void set(int index, T value, T address);

    /*��ӡ��������*/
    void print();

    /*�ͷ���������*/
    void freeList();
};