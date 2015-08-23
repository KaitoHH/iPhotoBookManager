//iPhotoBook.h
#pragma once
#include "ImageInfo.h"
#include "Graphlist.h"
#include "Trie.h"
#include "state.h"
#include <list>
#include <map>
#include <set>
using namespace std;

const int MAXN	  = 8000;				//��������ͼƬ����
const int MAX_POS = 300;				//�������ĵص����
const int MAX_MAP = 2;					//��ͼ����

class iPhotoBook
{
public:
	iPhotoBook();
	~iPhotoBook();
	err_code intialize(string);							//��ʼ��
	err_code add(ImageInfo);							//����ͼƬ
	err_code del(ImageInfo);							//ɾ��ͼƬ
	err_code update(ImageInfo,ImageInfo);				//����ͼƬ��Ϣ
	err_code findByTittle(string, int&, list<int>&);	//������Ѱ��
	err_code findByPosition(string, int&, list<int>&);	//���ص�Ѱ��
	err_code foodPrint(string, int&, list<int>&);		//�㼣
	Graphlist graph(int);								//get Graphlist
	void timeTest();									//ʱ�����

	ImageInfo record(int);
	int next(int);
	int size(){ return n; }
	void set_fuzzy(bool);

	//��չ����
	err_code findByFileName(string,int&);	//�ļ���Ѱ��
	err_code findBySize(int);				//���ļ���СѰ��
	err_code findByRes(int);				//���ֱ���Ѱ��

	
private:
	int n;								//��Ƭ����
	int npos;							//�ص�����
	ImageInfo book[MAXN];				//������Ƭ����Ϣ
	list<int>free;						//����������
	map<string, int>key;				//�����ļ��������ֵ�ӳ����ڲ���
	Trie tittle;						//Ӣ���������ɵ�Trie
	set<int>pos[MAX_POS];				//�ص㹹�ɵ�list
	map<string, int>mappos;				//�ص㵽���ֵ�ӳ��
	Graphlist g[MAX_MAP];				//��ͼ��Ϣ��

	bool fuzzy;
	string path;
};

void splitByHH(string str, char split, int &n, string s[]);//�ַ����ָ�