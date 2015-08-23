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

const int MAXN	  = 8000;				//最多允许的图片总数
const int MAX_POS = 300;				//最多允许的地点个数
const int MAX_MAP = 2;					//地图总数

class iPhotoBook
{
public:
	iPhotoBook();
	~iPhotoBook();
	err_code intialize(string);							//初始化
	err_code add(ImageInfo);							//增加图片
	err_code del(ImageInfo);							//删除图片
	err_code update(ImageInfo,ImageInfo);				//更新图片信息
	err_code findByTittle(string, int&, list<int>&);	//按标题寻找
	err_code findByPosition(string, int&, list<int>&);	//按地点寻找
	err_code foodPrint(string, int&, list<int>&);		//足迹
	Graphlist graph(int);								//get Graphlist
	void timeTest();									//时间测试

	ImageInfo record(int);
	int next(int);
	int size(){ return n; }
	void set_fuzzy(bool);

	//扩展功能
	err_code findByFileName(string,int&);	//文件名寻找
	err_code findBySize(int);				//按文件大小寻找
	err_code findByRes(int);				//按分辨率寻找

	
private:
	int n;								//照片总数
	int npos;							//地点总数
	ImageInfo book[MAXN];				//所有照片的信息
	list<int>free;						//数组空闲情况
	map<string, int>key;				//建立文件名到数字的映射便于查找
	Trie tittle;						//英文描述构成的Trie
	set<int>pos[MAX_POS];				//地点构成的list
	map<string, int>mappos;				//地点到数字的映射
	Graphlist g[MAX_MAP];				//地图信息表

	bool fuzzy;
	string path;
};

void splitByHH(string str, char split, int &n, string s[]);//字符串分隔