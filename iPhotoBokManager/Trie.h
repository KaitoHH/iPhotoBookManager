//Trie.h
#pragma once
#include<set>
#include<list>
#include"state.h"
using namespace std;
const int NNODE = 27;

struct node{
	int n;					//�����Ե�ǰ���Ϊǰ׺�Ľ�����
	node* child[NNODE];		//�ӽ��
	set<int>content;		//��ǰ�ڵ����ƬĿ¼
	node(){
		for (int i = 0; i < NNODE; i++){
			child[i] = nullptr;
		}
		n = 0;
	}
};

class Trie
{
public:

	Trie();
	~Trie();

	err_code insert(int,string);					//����tittle
	err_code del(int,string);						//ɾ�����
	err_code search(string, set<int>&, bool);		//Ѱ�ҽ��
	void visit(node*, set<int>&, bool);				//ģ������
private:
	node* head;

	node* find(string);						//�������������Ľ�㲢����ָ��
};

