#include <iostream>
#include <map>  
#include <algorithm>

using namespace std;

struct ListNode
{
	int l_key;          
	int l_value;
	ListNode* Pre;
	ListNode* Next;

	ListNode(int key, int value)//��ʼ��
	{
		l_key = key;
		l_value = value;
		Pre = NULL;
		Next = NULL;
	}
};

class LRU_Cache
{
public:
	LRU_Cache(int size)//���캯��
	{
		m_capacity = size;
		pHead == NULL;
		pTail == NULL;
	}

	~LRU_Cache()//��������
	{
		map<int, ListNode*>::iterator it = mp.begin();
		for (; it != mp.end();)
		{
			delete it->second;
			it->second = NULL;
			mp.erase(it++);  
		}
		delete pHead;
		pHead == NULL;
		delete pTail;
		pTail == NULL;

	}
	//�Ƴ��ڵ㣬����ɾ���ڵ�
	void Remove(ListNode* pNode)
	{
		// �����ͷ�ڵ�
		if (pNode->Pre == NULL)
		{
			pHead = pNode->Next;
			pHead->Pre = NULL;
		}

		// �����β�ڵ�
		if (pNode->Next == NULL)
		{
			pTail = pNode->Pre;
			pTail->Next = NULL;
		}

		else
		{
			pNode->Pre->Next = pNode->Next;
			pNode->Next->Pre = pNode->Pre;
		}

	}
	//  ������ù�������Ҫ���ڶ�ͷ��
	void SetHead(ListNode* pNode)
	{
		pNode->Next = pHead;
		pNode->Pre = NULL;
		if (pHead == NULL)
		{
			pHead = pNode;
		}
		else
		{
			pHead->Pre = pNode;
			pHead = pNode;

		}
		if (pTail == NULL)
		{
			pTail = pHead;
		}
	}
	//��������
	void Insert(int key, int value)
	{
		map<int, ListNode*>::iterator it = mp.find(key);//�����key���ھ�key�������value
		if (it != mp.end())
		{
			ListNode* Node = it->second;
			Node->l_value = value;
			Remove(Node);
			SetHead(Node);
		}
		else
		{
			ListNode* NewNode = new ListNode(key, value);
			if (mp.size() >= m_capacity)
			{
				cout << endl << "���棺�Ѿ������������:" << m_capacity << "������" << endl;
				int x = pTail->l_key;
				map<int, ListNode*>::iterator it = mp.find(x);
				Remove(pTail); //�Ƴ���βָ���ڴ�
				int y = it->second->l_value;
				delete it->second;//ɾ��value
				cout << endl << "Ϊ���Ƴ�keyΪ" << x << ",valueΪ" << y << "�Ľڵ�" << endl;
				mp.erase(it);
			}
			SetHead(NewNode);//�ŵ�ͷ��
			mp[key] = NewNode;
		}
	}

	int Get(int key)
	{
		map<int, ListNode*>::iterator it = mp.find(key);
		if (it != mp.end())
		{
			ListNode* Node = it->second;
			Remove(Node);
			SetHead(Node);
			return Node->l_value;
		}
		else
		{
			return -1;     //�д�����
		}
	}

	int GetSize()
	{
		return mp.size();
	}

	void show() {
		int i = 0;
		int n = mp.size();
		if (n == 0) cout << "empty task" << endl;
		else {
			map<int, ListNode*>::iterator it = mp.begin();
			cout << "��ǰһ����" << n << "������: " << endl;
			for (; it != mp.end(); ++it) 
			{
				cout << "keyֵΪ:" << it->first << ",valueֵΪ: " << it->second->l_value << endl;
				i++;
			}
		}
	}

private:
	int m_capacity;    
	ListNode* pHead;   
	ListNode* pTail;   
	map<int, ListNode*>  mp;  
};

