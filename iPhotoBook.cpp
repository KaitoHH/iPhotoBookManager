//iPhotoBook.cpp
#include "iPhotoBook.h"
#include <fstream>
#include <list>
#include <iostream>

void splitByHH(string str,char split, int &n, string s[])
{
	n = 0;
	int len = str.length();
	bool end = false;
	while (str != ""){
		int pos = str.find(split);
		if (pos == string::npos){
			s[n++] = str;
			break;
		}
		s[n++] = str.substr(0, pos);
		str = str.substr(pos + 1, len);
	}
}

iPhotoBook::iPhotoBook()
{
	npos = 0;
	n = 0;
	g[0] = Graphlist("华师大");
	g[1] = Graphlist("中国");
}


iPhotoBook::~iPhotoBook()
{
	fstream fout(path + "\\info.csv",ios::out);
	int d = -1;
	for (int i = 1; i <= size(); i++){
		d = next(d);
		ImageInfo cur=record(d);
		fout << i << "," << cur;
	}
}

err_code iPhotoBook::add(ImageInfo item)
{
	//获取空位
	int no;
	if (free.empty()){
		no = n;
	}
	else{
		no = free.front();
		free.pop_front();
	}

	if (n >= MAXN)								return overflow;
	if (!key.insert(pair<string, int>(item.filename(), no)).second)
		return already_exist;
	
	item.set_used(true);
	//装入内存
	book[no] = item;
	n++;
	
	//维护地点
	if (mappos.insert(pair<string, int>(item.postion(), npos)).second)	npos++;
	pos[mappos[item.postion()]].insert(no);

	//维护trie 添加模糊搜索,智能模糊搜索
	int nwrd;
	string word[10];
	splitByHH(item.texten(), ' ', nwrd, word);
	err_code ret = success;
	for (int i = 0; i < nwrd; i++){
		ret = tittle.insert(no, word[i]);
		if (ret != success)	return ret;
	}
	return ret;
	//return tittle.insert(no, item.texten());
}

err_code iPhotoBook::findByTittle(string key,int &n,list<int>&item)
{
	set<int>s;
	err_code result;
	result = tittle.search(key, s, fuzzy);
	n = 0;
	set<int>::iterator it;
	for (it = s.begin(); it != s.end(); it++){
		item.push_back(*it);
		n++;
	}
	return result;
}

err_code iPhotoBook::findByPosition(string key, int &n, list<int>&item)
{
	n = 0;
	map<string, int>::iterator it;
	it = mappos.find(key);
	if (it == mappos.end()){
		return not_present;
	}
	int target = mappos[key];
	set<int>::iterator sit;
	for (sit = pos[target].begin(); sit != pos[target].end(); sit++){
		n++;
		item.push_back(*sit);
	}
	return success;
}

err_code iPhotoBook::intialize(string s)
{
	//初始化图片库
	path = s;
	fstream fin(path+"\\info.csv");
	if (!fin)		return open_info_file_error;
	string line;
	err_code result;
	while (getline(fin, line)){
		ImageInfo item;
		int n;
		string ans[13];
		splitByHH(line, ',', n, ans);
		item.set_filename(ans[1]);
		item.set_height(atoi(ans[2].c_str()));
		item.set_width(atoi(ans[3].c_str()));
		item.set_size(atoi(ans[4].c_str()));
		item.set_time(atoi(ans[5].c_str()));
		item.set_textcn(ans[6]);
		item.set_texten(ans[7]);
		item.set_map(ans[8]);
		item.set_postion(ans[9]);
		item.set_posl(ans[10]);
		item.set_lname(ans[11]);
		item.set_uper(ans[12]);
		result = add(item);
		if (result != success)	return result;
	}
	fin.close();
	
	//构建地图信息
	result = g[0].intialize(path);
	result = g[1].intialize(path);
	
	return result;
}

err_code iPhotoBook::foodPrint(string mapname,int &loc,list<int>&stat){
	if (mapname.find( "华师大")!=-1)		loc = 0;
	else if (mapname == "中国")			loc = 1;
	else								return no_map;

	stat.clear();
	n = g[loc].size();
	for (int i = 0; i < n; i++){
		int ans;
		list<int>l;
		findByPosition(g[loc].at(i).getName(), ans, l);
		stat.push_back(ans);
	}
	return success;
}

Graphlist iPhotoBook::graph(int index){
	return g[index];
}

ImageInfo iPhotoBook::record(int d){
	return book[d];
}

err_code iPhotoBook::del(ImageInfo item){
	map<string, int >::iterator it;
	it = key.find(item.filename());
	if (it == key.end())	return not_present;
	int d = it->second;
	n--;

	book[d].set_used(false);			//设置有效位
	key.erase(it);						//删除文件名
	free.push_back(d);					//添加空位
	it = mappos.find(item.postion());	//寻找地图索引
	pos[it->second].erase(d);			//删除地图中的结点
	int nwrd;
	string word[10];
	splitByHH(item.texten(), ' ', nwrd, word);
	for (int i = 0; i < nwrd; i++){
		tittle.del(d, word[i]);			//删除英文描述
	}
	return success;
}

int iPhotoBook::next(int i){
	while (!book[++i].used());
	return i;
}

void iPhotoBook::set_fuzzy(bool b){
	fuzzy = b;
}

err_code iPhotoBook::update(ImageInfo src, ImageInfo dest)
{
	map<string, int >::iterator it;
	it = key.find(src.filename());
	if (it == key.end())	return not_present;
	int d = it->second;

	free.push_front(d);
	del(src);
	return add(dest);

}

err_code iPhotoBook::findByFileName(string name, int &d)
{
	map<string, int >::iterator it;
	it = key.find(name);
	d = -1;
	if (it == key.end())	return not_present;
	d = it->second;
	return success;
}