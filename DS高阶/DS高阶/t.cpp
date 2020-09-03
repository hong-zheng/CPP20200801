#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <string.h>
#include <unordered_map>
#include <map>
#include <set>
using namespace std;


template<class K,class V,int M>
struct BTreeNode
{
	pair<K, V> kvs[M - 1];
	BTreeNode<K, V, M>* _children[M]; //存指向孩子指针的数组
	BTreeNode<K, V, M>* _parent; // 寻找父节点
};

template<class K,class V,int M>
class BTree
{

private:
	BTreeNode<K, V, M>* _root;
};
