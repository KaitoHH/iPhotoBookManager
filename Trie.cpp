//Trie.cpp
#include "Trie.h"
#include <string>
using namespace std;

Trie::Trie()
{
	head = new node;
}


Trie::~Trie()
{
}

err_code Trie::insert(int no,string tittle)
{
	node * p = head;
	int len = tittle.length();
	for (int i = 0; i < len; i++){
		tittle[i] = tolower(tittle[i]);

		//Â³°ôÐÔ
		if (tittle[i] < 0){
			i++;
			tittle[i] = ' ';
		}

		int cur = (!islower(tittle[i])) ? NNODE - 1 : tittle[i] - 'a';
		if (p->child[cur] == nullptr){
			p->child[cur] = new node();
		}
		if (p->child[cur] == nullptr)	return overflow;
		p = p->child[cur];
	}
	(p->n)++;
	p->content.insert(no);
	return success;
}

err_code Trie::del(int no, string tittle)
{
	node *p = find(tittle);
	if (p == nullptr)	return not_exist;
	set<int>::iterator it;
	it = p->content.find(no);
	if (it == p->content.end()){
		return not_exist;
	}
	p->content.erase(no);
	return success;
}

node* Trie::find(string tittle)
{
	node *p = head;
	int len = tittle.length();
	for (int i = 0; i < len; i++){
		tittle[i] = tolower(tittle[i]);

		//Â³°ôÐÔ
		if (tittle[i] < 0){
			i++;
			tittle[i] = ' ';
		}

		int cur = (!islower(tittle[i])) ? NNODE - 1 : tittle[i] - 'a';

		if (p->child[cur] == nullptr){
			return nullptr;
		}
		p = p->child[cur];
	}
	return p;
}

err_code Trie::search(string tittle, set<int>&item, bool fuzzy)
{
	node *p = find(tittle);
	if (p == nullptr)	return not_present;
	visit(p, item, fuzzy);
	return success;
}

void Trie::visit(node *cur, set<int>&item, bool fuzzy)
{
	if (cur != nullptr){
		set<int>::iterator it;
		for (it = cur->content.begin(); it != cur->content.end(); it++){
			item.insert(*it);
		}
		if (fuzzy)
			for (int i = 0; i < NNODE; i++){
				visit(cur->child[i], item, fuzzy);
			}
	}
}