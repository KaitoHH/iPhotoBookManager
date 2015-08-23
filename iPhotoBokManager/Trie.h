//Trie.h
#pragma once
#include<set>
#include<list>
#include"state.h"
using namespace std;
const int NNODE = 27;

struct node{
	int n;					//所有以当前结点为前缀的结点个数
	node* child[NNODE];		//子结点
	set<int>content;		//当前节点的照片目录
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

	err_code insert(int,string);					//增加tittle
	err_code del(int,string);						//删除结点
	err_code search(string, set<int>&, bool);		//寻找结点
	void visit(node*, set<int>&, bool);				//模糊查找
private:
	node* head;

	node* find(string);						//查找满足条件的结点并返回指针
};

