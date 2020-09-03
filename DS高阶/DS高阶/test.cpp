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


void select(vector<int>& tmp)
{
	int len = tmp.size();
	for (int i = 0; i < len; ++i)
	{
		int mini = i;
		for (int j = i + 1; j < len; ++j)
		{
			if (tmp[mini] > tmp[j])
			{
				mini = j;
			}
		}
		swap(tmp[mini], tmp[i]);
	}
}

void display(vector<int>&  tmp)
{
	int len = tmp.size();
	for (int i = 0; i < len; ++i)
		cout << tmp[i] << " ";
	cout << endl;
}

void insert(vector<int>& tmp)
{
	int i = 1;
	int n = tmp.size();
	while (i < n)
	{
		int cur = tmp[i];
		int j = i - 1;
		for (; j >= 0 && tmp[j] > cur; j--)
		{
			tmp[j + 1] = tmp[j];
		}
		tmp[j + 1] = cur;
		++i;
	}
}

void shell(vector<int>& tmp)
{
	int len = tmp.size();
	int step = len / 2;
	while (step >= 1)
	{
		for (int i = step; i < len; ++i)
		{
			int cur = tmp[i];
			int j = i - step;
			for (; j >= 0 && tmp[j] > cur; j -= step)
			{
				tmp[j + step] = tmp[j];
			}
			tmp[j + step] = cur;
		}
		step /= 2;
	}
}

void merge(vector<int>& ret, int begin, int mid, int end,vector<int>& tmp)
{
	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
	int tmpidx = begin;
	while (begin1 <= mid && begin2 <= end)
	{
		if (ret[begin1] < ret[begin2])
		{
			tmp[tmpidx++] = ret[begin1++];
		}
		else if (ret[begin1] >= ret[begin2])
		{
			tmp[tmpidx++] = ret[begin2++];
		}
	}
	while(begin1 <= end1)
	{
		tmp[tmpidx++] = ret[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[tmpidx++] = ret[begin2++];
	}
	tmpidx = begin;
	while (tmpidx <= end)
	{
		ret[tmpidx++] = tmp[tmpidx++];
	}
}

void mergecf(vector<int>& ret, int begin, int end, vector<int>& tmp)
{
	if (begin >= end) return;
	int mid = begin + (end - begin) / 2;
	mergecf(ret, begin, mid,tmp);
	mergecf(ret, mid+1, end, tmp);
	merge(ret, begin, mid, end, tmp);
}

void mergesort(vector<int>& ret)
{
	int sz = ret.size() ;
	vector<int> tmp;
	tmp.resize(sz);

	mergecf(ret, 0, sz - 1, tmp);
}1
void test()
{
	srand(time(NULL));
	while (1)
	{
		int num;
		cout << "输入需要整的个数" << endl;
		cin >> num;
		if (!num) break;
		vector<int> tmp;
		tmp.resize(num);
		for (int i = 0; i < num; ++i)
		{
			tmp[i] = rand() % 100;
		}
		display(tmp);
		//insert(tmp);
		//select(tmp);
		//shell(tmp);
		mergesort(tmp);
		display(tmp);
	}
}
/*
// AVL树
template<class T>
struct AVLNode
{
	T _val;
	AVLNode<T>* _left;
	AVLNode<T>* _right;s
	AVLNode<T>* _parent;
	int _bf;// 平衡因子

	AVLNode(const T& val=new T())
		:_val(val)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _bf(0)
	{}
};

template<class T>
class AVLTree
{
public:
	typedef AVLNode<T> Node;

	AVLTree()
	{
		_root = nullptr;
	}

	bool insert(const T& val)
	{
		// 根为空
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		// 根为非空
		else
		{
			// 找寻需要插入的位置
			Node* cur = _root;
			Node* parent = nullptr;
			while (cur)
			{
				parent = cur;
				if (cur->_val == val)
				{
					return false;
				}
				else if (cur->_val < val)
				{
					cur = cur->_right;
				}
				else if (cur->_val > val)
				{
					cur = cur->_left;
				}
			}
			cur = new Node(val);
			cur->_parent = parent;

			// 插入结点
			if (parent->_val < val)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}


			// 更新+调整
			while (parent)
			{
				// 更新
				if (parent->_right == cur)
				{
					++parent->_bf;
				}
				else
				{
					--parent->_bf;
				}

				// 调整
				if (parent->_bf == 0)
				{
					// 此时的高度并没有增加
					break;
				}
				else if (parent->_bf == 1 || parent->_bf == -1)
				{
					// 更新之后子树高度出现变化则需要继续向上更新
					cur = parent;
					parent = parent->_parent;
				}
				else if (parent->_bf == 2 || parent->_bf == -2)
				{
					// 右边的右边高，左转
					if (parent->_bf == 2 && cur->_bf == 1)
					{
						RotateL(parent);
					}
					else if (parent->_bf == -2 && cur->_bf == -1)
					{
						RotateR(parent);
					}
					else if (parent->_bf == 2 && cur->_bf == -1)
					{
						Node* subR = parent->_right;
						Node* subRL = subR->_left;
						int bf = subRL->_bf;
						RotateL(parent);
						RotateR(cur);

						if (bf == 1)
						{
							subR->_bf = 0;
							parent->_bf = -1;
						}
						else if (bf == -1)
						{
							parent->_bf = 0;
							subR->_bf = 1;
						}
					}
					else if (parent->_bf == -2 && cur->_bf == 1)
					{
						Node* subL = parent->_left;
						Node* subLR = subL->_right;
						int bf = subLR->_bf;
						RotateR(parent);
						RotateL(cur);

						if (bf == 1)
						{
							parent->_bf = 0;
							subL->_bf = -1;
						}
						else if (bf == -1)
						{
							parent->_bf = 1;
							subL->_bf = 0;
						}
					}
					break;
				}

			}

		}

	}

	void inorder()
	{
		_inorder(_root);
		cout << endl;
	}
private:
	void _inorder(Node* root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_val << " ";
			_inorder(root->_right);
		}
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;
		if (parent == _root)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			Node* g = parent->_parent;
			if (g->_left == parent)
			{
				g->_left = subR;
			}
			else if (g->_right == parent)
			{
				g->_right = subR;
			}
			subR->_parent = g;
		}
		parent->_parent = subR;
		parent->_bf = subR->_bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			Node* g = parent->_parent;
			if (g->_left == parent)
			{
				g->_left = subL;
			}
			else if (g->_right == parent)
			{
				g->_right = subL;
			}
			subL->_parent = g;
		}
		parent->_parent = subL;
		subL->_bf = parent->_bf = 0;
	}
private:
	Node* _root;
};
void test1()
{
	AVLTree<int> avl;
	avl.insert(1);
	avl.insert(91);
	avl.insert(17);
	avl.insert(15);
	avl.insert(41);
	avl.insert(12);
	avl.inorder();
}


enum Color{
	RED ,
	BLACK
};
template<class K,class V>
struct RBNode
{
	pair<K, V> _val;

	RBNode<K, V>* _left;
	RBNode<K, V>* _right;
	RBNode<K, V>* _parent;
	Color _color;
	
	RBNode(const pair<K, V>& val = pair<K,V>())
		:_val(val)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _color(RED)

	{}
};

template<class K,class V>
class RBTree{
public:
	typedef RBNode<K, V> Node;

	RBTree()
		:_header(new Node)
	{
		_header->_parent = nullptr;
		_header->_left = _header->_right = _header;
	}

	bool insert(const pair<K, V>& val)
	{
		Node* root = _header->_parent;
		if (root == nullptr)
		{
			root = new Node(val);
			root->_color = BLACK;
			_header->_parent = root;
			root->_parent = _header;

			_header->_left = _header->_right = root;
			return true;
		}
		else
		{
			Node* cur = root;
			Node* parent = nullptr;
			while (cur)
			{
				parent = cur;
				if (cur->_val.first == val.first)
				{
					return false;
				}
				else if (cur->_val.first < val.first)
				{
					cur = cur->_right;
				}
				else if (cur->_val.first > val.first)
				{
					cur = cur->_left;
				}
			}

			cur = new Node(val);
			cur->_parent = parent;
			if (parent->_val.first < val.first)
			{
				parent->_right = cur;
			}
			else if (parent->_val.first > val.first)
			{
				parent->_left = cur;
			}

			// 更新+调整
			while (cur != _header->_parent && parent->_parent->_color == RED)
			{
				Node* parent = cur->_parent;
				Node* g = parent->_parent;
				if (g->_left == parent)
				{
					Node* u = g->_right;
					if (u && u->_color == RED)
					{
						parent->_color = u->_color = BLACK;
						g->_color = RED;
						cur = g;
					}
					else
					{
						// 没有u或者有u但是为黑色
						if (parent->_right == cur)
						{
							RotateL(parent);
							swap(parent, cur);
						}
						RotateR(g);
						g->_color = RED;
						parent->_color = BLACK;

						break;
					}
				}
				else if (g->_right == parent)
				{
					Node* u = g->_left;
					if (u && u->_color == RED)
					{
						parent->_color = u->_color = BLACK;
						g->_color = RED;
						cur = g;
					}
					else
					{
						// 没有u或者有u但是为黑色
						if (parent->_left== cur)
						{
							RotateR(parent);
							swap(parent, cur);
						}
						RotateL (g);
						g->_color = RED;
						parent->_color = BLACK;

						break;
					}
				}
			}
		}

		_header->_parent->_color = BLACK;
		_header->_left = leftMost();
		_header->_right = rightMost();
		return true;
	}

private:
	Node& leftMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}

	Node& rightMost()
	{
		Node* cur = _header->_right;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
	}
private:
	Node* _header;
};

void test()
{
	RBTree<int, int> rbt;

}

*/


//class MyString
//{
//public:
//	MyString()
//		:m_str(new char[1])
//	{
//		m_str[0] = 0;
//	}
//
//	~MyString()
//	{
//		delete[] m_str;
//	}
//
//	MyString& operator=(const char* str)
//	{
//		if (m_str)
//			delete[]  m_str;
//		m_str = new char[strlen(str) + 1];
//		memcpy(m_str, str, strlen(str) + 1);
//		return *this;
//	}
//
//	const char* c_str()
//	{
//		return m_str;
//	}
//
//	MyString(const char* s)
//	{
//		m_str = new char[strlen(s) + 1];
//		memcpy(m_str, s, strlen(s) + 1);
//	}
//	
//	// 拷贝构造函数
//	MyString(MyString& mys)
//	{
//		if (m_str)
//			delete[] m_str;
//		m_str = new char[strlen(mys.c_str()) + 1];
//		strcpy(m_str, mys.m_str);
//		//memcpy(m_str, mys.c_str(), strlen(mys.c_str())+1);
//	}
//private:
//	char* m_str;
//};
//
//void test()
//{
//	MyString s;
//	s = "hong"; // 赋值重载函数
//	cout << s.c_str() << endl;
//
//	MyString s1 = "p";
//	s1 = s;
//	cout << s1.c_str() << endl;
//	//MyString s1 = "hongzheng";
//	//cout << s1.c_str() << endl;
//}
//int main(){
//	test();
//	//cout << "hongzheng" << endl;
//	system("pause");
//	return 0;
//}
/*
template<class K,class V,class M>
class BTreeNode
{
	pair<K, V> kvs[M - 1];
	// 存指向孩子指针的数组
	BTreeNode<K, V, M>* _children[M];
	BTreeNode<K, V, M>* _parent;
};

template<class K,class V>
class BTree{

private:
	BTreeNode<K, V>* _root;
};
/*
template<class T>
struct AVLNode{
	T _value;
	int _bf;
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;

	AVLNode(const T& val = T())
		:_value(val)
		, _bf(0)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr){}
};

template<class T>
class AVLTree{
public:
	typedef AVLNode<T> Node;

	AVLTree()
		:_root(nullptr){}

	bool insert(const T& val)
	{
		// 搜索树的插入
		//Node* cur = _root;
		//Node* prev = nullptr;
		//while (cur)
		//{
		//	prev = cur;
		//	if (cur->value == val)
		//	{
		//		return false;
		//	}
		//	else if (cur->_value < val)
		//	{
		//		cur = cur->_right;
		//	}
		//	else {
		//		cur = cur->_left;
		//	}
		//}
		//cur = new Node(val);
		//if (cur->_value < val)
		//{
		//	prev->_right = cur;
		//}
		//else if (cur->_value > val)
		//{
		//	prev->_left = cur;
		//}

		// 搜索树的插入
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			// 相同结点不能插入二叉搜索树
			if (cur->_value == val)
			{
				return false;
			}
			else if (cur->_value < val)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}
		}
		// 插入当前元素
		cur = new Node(val);
		if (parent->_value < val)
			parent->_right = cur;
		else
			parent->_left = cur;
		// 当前结点的父节点就是上一个结点
		cur->_parent = parent;

		// 更新+调整
		while (parent)
		{
			//0、插入完之后，对父节点肯定有影响
			//	1、更新parent平衡因子
			if (parent->_left == cur)
			{
				// 左边插入一个结点
				--parent->_bf;
			}
			else if (parent->_right == cur)
			{
				// 插入父节点的右边，因此平衡因子需要++
				++parent->_bf;
			}

			// 2、更新完之后，判断是否需要继续更新
			if (parent->_bf == 0)
			{// 表示短的子树被补齐，则
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				// 表示parent子树的高度发生了改变，需要继续向上更新
				cur = parent;
				parent = parent->_parent;
			}
			else if (parent->_bf == -2 || parent->_bf == 2)
			{
				// 此时就不能只靠更新获得平衡，需要对结构进行调整，但是调整完之后就直接结束，不必再向上更新
				// 调整
				if (parent->_bf == -2 && cur->_bf == -1)
				{
					// 左边的左边高，右旋
					// 以父亲为轴，进行右旋
					RotateR(parent);
					cout << val << "-->右旋" << ",parent-->" << parent->_value << endl;
				}
				else if (parent->_bf == 2 && cur->_bf == 1)
				{
					// 右边的右边高，需要进行左旋
					RotateL(parent);
					cout << val << "-->左旋" << ",parent-->" << parent->_value << endl;
				}
				// 右边的左边高：先右旋再左旋
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					Node* subR = parent->_right;
					Node* subRL = subR->_left;
					int bf = subRL->_bf;
					// parent , subR(cur) , subRL
					// 右边的左边高：右左双旋
					RotateR(cur); // 以subR为轴右旋
					RotateL(parent); // 以parent为轴左旋
					cout << val << "-->右左双旋"  <<",parent-->" << parent->_value << endl;
					
					// 对结点的平衡因子进行调整
					if (bf == 1)
					{
						// subRL右子树高
						subR->_bf = 0;
						parent->_bf = -1;
					}
					else if (bf == -1)
					{
						parent->_bf = 0;
						subR->_bf = 1;
					}
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					Node* subL = parent->_left;
					Node* subLR = subL->_right;
					int bf = subLR->_bf;

					// 左边的右边高：左右双旋
					RotateL(cur);
					RotateR(parent);
					cout << val << "-->左右双旋" << ",parent-->" << parent->_value << endl;
					
					// 对本结构平衡因子进行调整
					if (bf == 1)
					{
						subL->_bf = 0;
						parent->_bf = 1;
					}
					else if (bf == -1)
					{
						subL->_bf = -1;
						parent->_bf = 0;
					}
				}
				break;
			}
		}
		return true;
	}

	void RotateR(Node* parent)
	{
		//Node* subL = parent->_left;
		//Node* subLR = subL->_right;
		//subL->_right = parent;
		//parent->_left = subLR;
		//if (subLR)
		//	subLR->_parent = parent;

		//if (_root == subL){
		//	_root = subL;
		//	subL->_parent = nullptr;
		//}
		//else
		//{
		//	subL->_parent = parent->_parent;
		//	if (parent->_parent->_left == parent)
		//	{
		//		parent->_parent->_left = subL;
		//	}
		//	else if (parent->_parent->_right == parent)
		//	{
		//		parent->_parent->_right = subL;
		//	}
		//}
		//parent->_parent = subL;
		//parent->_bf = subL->_bf = 0;

		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		if (parent == _root)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			Node* g = parent->_parent;
			subL->_parent = g;
			if (g->_left == parent)
			{
				g->_left = subL;
			}
			else
			{
				g->_right = subL;
			}
		}
		parent->_parent = subL;
		parent->_bf = subL->_bf = 0;
	}

	void RotateL(Node* parent)
	{
		//Node* subR = parent->_right;
		//Node* subRL = subR->_right;

		//subR->_right = parent;
		//parent->_right = subRL;
		//if (subRL)
		//	subRL->_parent = parent;

		//if (parent == _root)
		//{
		//	_root = subR;
		//	subR->_parent = nullptr;
		//}
		//else
		//{
		//	Node* g = parent->_parent;
		//	if (g->_left == parent)
		//	{
		//		g->_left = subR;
		//	}
		//	else if (g->_right == parent)
		//	{
		//		g->_right = subR;
		//	}
		//	subR->_parent = g;
		//}
		//parent->_parent = subR;
		//subR->_bf = parent->_bf = 0;


		// 右边的右边高，取右边的孩子
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;
		if (parent == _root)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			Node* g = parent->_parent;
			subR->_parent = g;
			if (g->_left == parent)
			{
				g->_left = subR;
			}
			else
			{
				g->_right = subR;
			}
		}
		parent->_parent = subR;
		parent->_bf = subR->_bf = 0;
	}

	// 中序遍历
	void inorder()
	{
		_inorder(_root);
		cout << endl;
	}

	void _inorder(Node* _root)
	{
		if (!_root)
			return;
		_inorder(_root->_left);
		cout << _root->_value << " ";
		_inorder(_root->_right);
	}

	// 判断是否为平衡因子
	bool isBalance()
	{
		return _isBalance(_root);
	}

	bool _isBalance(Node* root)
	{
		if (root == nullptr)
			return true;
		//左右子树的高度差是否和平衡因子相等
		int subL = Height(root->_left);
		int subR = Height(root->_right);
		if (root->_bf != subR - subL)
		{
			cout << "结点" << root->_value << "异常: bf" << root->_bf << "高度差-->" << subR - subL << endl;
			return false;
		}
		
		return abs(root->_bf) < 2
			&& _isBalance(root->_left)
			&& _isBalance(root->_right);
	}

	int Height(Node* root)
	{
		if (root == nullptr)
			return 0;
		int left = Height(root->_left);
		int right = Height(root->_right);
		return left > right ? (left + 1) : (right + 1);
	}
private:
	Node* _root;
};
void testAVL(){
	int arr[] = { 0,9,1,4,3,5,6,8,7,2 };
	AVLTree<int> avl;
	for (const auto& e : arr){
		avl.insert(e);
	}
	avl.inorder();
	//cout << endl;
	cout << "是否为平衡树-->"<<avl.isBalance() << endl;
}
int mainAVL(){
	testAVL();
	//testMap();
	//test21();
	system("pause");
	return 0;
}
// 定义红黑树的结点颜色为枚举类型
enum Color{
	BLACK,
	RED
};

// 定义红黑树的结点且缺省颜色为红色
template<class K,class V>
struct RBNode{
	pair<K, V> _value;

	Color _color;
	RBNode<K, V>* _parent;
	RBNode<K, V>* _left;
	RBNode<K, V>* _right;

	RBNode(const pair<K,V>& value = pair<K,V>())
		: _value(value)
		, _color(RED) // 缺省插入结点为红色
		, _parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
	{}
};
*/

/*
template<class K,class V>
class RBTree
{
public:
	typedef RBNode<K, V> Node;

//	 创建一颗空树
	RBTree()
		:_header(new Node)
	{
		//空树父节点_parent指向nullptr
		_header->_left = _header->_right = _header;
	}


	bool insert(const pair<K, V>& val)
	{
		//空树
		if (_header->_parent == nullptr)
		{
			// 创建一个根节点
			Node* root = new Node(val);
			//根结点的颜色更改为黑色
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;

			_header->_left = root;
			_header->_right = root;
			return true;
		}
		//非空树
		// 当前的cur为root
		Node* cur = _header->_parent;
		Node* parent = nullptr;

		while (cur)
		{
			parent = cur;
			// 按照key进行比较：pair.first
			if (cur->_value.first == val.first)
				return false;
			if (cur->_value.first < val.first)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}

			cur = new Node(val);
			if (parent->_value.first < val.first)
			{
				parent->_right = cur;
			}
			else
			{
				parent->_left = cur;
			}
			cur->_parent = parent;

			// 调整：修改颜色+旋转
			// 当前结点不为root结点且父节点为RED
			while (cur != _header->_parent && cur->_parent->_color == RED)
			{
				// 由于parent不是root，因此会有g结点
				Node* p = cur->_parent;

				Node* g = p->_parent;

				//if (g->_left == p)
				if (g->_left == p)
				{
					Node* u = g->_right;
					if (u && u->_color == RED)
					{
						//修改颜色
						u->_color = p->_color = BLACK;
						g->_color = RED;
						//继续向上查看
						cur = g;
					}
					else if (!u || u->_color == BLACK)
					{
						// u不存在或者u存在且为黑

						// 如果cur在p的右边
						// 旋转完成之后又到了左边的场景
						if (cur == p->_right)
						{
							RotateL(p);
							swap(cur, p);
						}
						//cur在p的左边,右旋
						RotateR(g);

						// 修改颜色
						p->_color = BLACK;
						g->_color = RED;

						break;
					}
					// 父节点在祖父结点的右边
					else if (p == g->_right)
					{
						// p在g的右边
						Node* u = g->_left;
						if (u && u->_color == RED)
						{
							//修改颜色
							u->_color = p->_color = BLACK;
							g->_color = RED;
							//继续向上查看
							cur = g;
						}
						else if (!u || u->_color == BLACK)
						{
							// u不存在或者u存在且为黑

							// 如果cur在p的右边
							// 旋转完成之后又到了左边的场景
							if (cur == p->_left)
							{
								RotateR(p);
								swap(cur, p);
							}
							//cur在p的左边,右旋
							RotateL(g);

							// 修改颜色
							p->_color = BLACK;
							g->_color = RED;

							break;
						}
					}
				}
			}
		}
		// 根颜色置为黑色
		_header->_parent->_color = BLACK;
		//更新_header的左、右
		_header->_left = leftMost();
		_header->_right = rightMost();

		return true;
	}

	void inorder()
	{
		_inorder(_header->_parent);
		cout << endl;
	}
private:
	void _inorder(Node* root)
	{
		if (root == nullptr)
			return;
		_inorder(root->_left);
		cout << root->_value.first << "->" << root->_value.second << endl;
		_inorder(root->_right);
	}
	Node* leftMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}

	Node* rightMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		if (parent == _header->_parent)
		{
			_header->_parent = subL;
			subL->_parent = _header;
		}
		else
		{
			Node* g = parent->_parent;
			subL->_parent = g;
			if (g->_left == parent)
			{
				g->_left = subL;
			}
			else
			{
				g->_right = subL;
			}
		}
		parent->_parent = subL;
	}

	void RotateL(Node* parent)
	{
		// 右边的右边高，取右边的孩子
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;
		if (parent == _header->_parent)
		{
			_header->_parent = subR;
			subR->_parent = _header;
		}
		else
		{
			Node* g = parent->_parent;
			subR->_parent = g;
			if (g->_left == parent)
			{
				g->_left = subR;
			}
			else
			{
				g->_right = subR;
			}
		}
		parent->_parent = subR;
	}
private:
	Node* _header;
};

*/

/*
template <class K, class V>
class RBTree
{
public:
	typedef RBNode<K, V> Node;

	RBTree()
		:_header(new Node)
	{
		_header->_left = _header->_right = _header;
	}

	bool insert(const pair<K, V>& val)
	{
		//¿ÕÊ÷
		if (_header->_parent == nullptr)
		{
			//´´½¨µÚÒ»¸ö¸ù½Úµã
			Node* root = new Node(val);
			//¸ù½ÚµãÎªºÚÉ«
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;

			_header->_left = root;
			_header->_right = root;

			return true;
		}
		//·Ç¿ÕÊ÷
		Node* cur = _header->_parent;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			//°´ÕÕkeyÖµ½øÐÐ±È½Ï£º pair.first
			if (cur->_value.first == val.first)
				return false;
			if (cur->_value.first < val.first)
				cur = cur->_right;
			else
				cur = cur->_left;
		}

		cur = new Node(val);
		if (parent->_value.first < val.first)
			parent->_right = cur;
		else
			parent->_left = cur;

		cur->_parent = parent;

		//µ÷Õû£º ÐÞ¸ÄÑÕÉ«, Ðý×ª
		while (cur != _header->_parent && cur->_parent->_color == RED)
		{
			Node* p = cur->_parent;
			Node* g = p->_parent;
			if (g->_left == p)
			{
				Node* u = g->_right;
				if (u && u->_color == RED)
				{
					//ÐÞ¸ÄÑÕÉ«
					u->_color = p->_color = BLACK;
					g->_color = RED;
					//¼ÌÐøÏòÉÏ²é¿´
					cur = g;
				}
				else
				{
					//u²»´æÔÚ/u´æÔÚÇÒÎªºÚ
					if (cur == p->_right)
					{
						RotateL(p);
						swap(cur, p);
					}
					//curÔÚpµÄ×ó±ß,ÓÒÐý
					RotateR(g);
					//ÐÞ¸ÄÑÕÉ«
					p->_color = BLACK;
					g->_color = RED;

					break;
				}
			}
			else
			{
				Node* u = g->_left;
				if (u && u->_color == RED)
				{
					//ÐÞ¸ÄÑÕÉ«
					u->_color = p->_color = BLACK;
					g->_color = RED;
					//¼ÌÐøÏòÉÏ²é¿´
					cur = g;
				}
				else
				{
					//u²»´æÔÚ/u´æÔÚÇÒÎªºÚ
					if (cur == p->_left)
					{
						RotateR(p);
						swap(cur, p);
					}
					//curÔÚpµÄ×ó±ß,ÓÒÐý
					RotateL(g);
					//ÐÞ¸ÄÑÕÉ«
					p->_color = BLACK;
					g->_color = RED;

					break;
				}
			}
		}

		//¸ùÑÕÉ«ÖÃÎªºÚÉ«
		_header->_parent->_color = BLACK;
		//¸üÐÂ_headerµÄ×ó£¬ÓÐ
		_header->_left = leftMost();
		_header->_right = rightMost();
		return true;
	}
	void inorder()
	{
		_inorder(_header->_parent);
		cout << endl;
	}
 
	void _inorder(Node* root)
	{
		if (root == nullptr)
		return;
		_inorder(root->_left);
		cout << root->_value.first << "->" << root->_value.second << endl;
		_inorder(root->_right);
	}
	Node* leftMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}

	Node* rightMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;

		if (subLR)
			subLR->_parent = parent;

		if (parent == _header->_parent)
		{
			_header->_parent = subL;
			subL->_parent = _header;
		}
		else
		{
			Node* g = parent->_parent;
			subL->_parent = g;
			if (g->_left == parent)
				g->_left = subL;
			else
				g->_right = subL;
		}

		parent->_parent = subL;

	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		if (parent == _header->_parent)
		{
			_header->_parent = subR;
			subR->_parent = _header;
		}
		else
		{
			Node* g = parent->_parent;
			subR->_parent = g;
			if (g->_left == parent)
				g->_left = subR;
			else
				g->_right = subR;
		}
		parent->_parent = subR;

	}
private:
	Node* _header;
};


void testRBTree()
{
	RBTree<int, int> rbt;
	rbt.insert(make_pair(3, 4));
	rbt.insert(make_pair(93, 4));
	rbt.insert(make_pair(36, 4));
	rbt.insert(make_pair(53, 4));
	rbt.insert(make_pair(34, 4));
	rbt.insert(make_pair(43, 4));
	rbt.insert(make_pair(0, 4));
	rbt.insert(make_pair(4, 4));
	rbt.insert(make_pair(8, 4));
	rbt.insert(make_pair(90, 4));

	rbt.inorder();
}
int main(){
	testRBTree();
	cout << "hongzheng" << endl;
	system("pause");
	return 0;
}
*/


//void test21(){
//	// 遍历是有序的
//	multiset<int> s;
//	s.insert(1);
//	s.insert(1);
//	s.insert(51);
//	s.insert(41);
//	s.insert(31);
//	s.insert(121);
//	s.insert(2);
//
//	for (auto e : s)
//	{
//		cout << e << endl;
//	}
//}
//void testMap(){
//	multimap<int, int> mmp;
//	mmp.insert(make_pair(32, 3));
//	mmp.insert(make_pair(2, 73));
//	mmp.insert(make_pair(3, 63));
//	mmp.insert(make_pair(132, 43));
//	mmp.insert(make_pair(322, 33));
//	mmp.insert(make_pair(332, 23));
//	mmp.insert(make_pair(332, 13));
//
//	for (const auto& e : mmp)
//	{
//		cout << e.first << "-" << e.second << endl;
//	}
//	cout << endl;
//
//	// 找到所有的等于key的迭代器
//	pair<multimap<int, int>::iterator, multimap<int, int>::iterator> p = mmp.equal_range(332);
//	multimap<int, int>::iterator it = p.first;
//	while (it != p.second)
//	{
//		cout << it->first << "--->" << it->second << endl;
//		++it;
//	}
//}







//void display(vector<int>& ret)
//{
//	int len = ret.size();
//	for (int i = 0; i < len; ++i)
//	{
//		printf("%d ", ret[i]);
//	}
//	printf("\n");
//}
//void swap(int* i, int* j)
//{
//	int tmp = *i;
//	*i = *j;
//	*j = tmp;
//}
//
//
////希尔排序
//// 分组插入排序
//void shell1(vector<int>& ret)
//{
//	int len = ret.size();
//	int gap = len / 2;
//
//	while (gap >= 1)
//	{
//		for (int i = gap; i < len; ++i)
//		{
//			int cur = ret[i];
//			int j = i - gap;
//			while (j>=0 && cur < ret[j])
//			{
//				ret[j + gap] = ret[j];
//				j -= gap;
//			}
//			ret[j + gap] = cur;
//		}
//		gap /= 2;
//	}
//}
//
//void select(vector<int>& ret)
//{
//	int len = ret.size();
//	for (int i = 0; i < len; ++i)
//	{
//		int cur = ret[i];
//		int midx = i;
//		for (int j = i + 1; j < len; ++j)
//		{
//			if (ret[j] < cur)
//			{
//				cur = ret[j];
//				midx = j;
//			}
//		}
//		if (midx != i)
//		{
//			swap(&ret[midx], &ret[i]);
//		}
//	}
//}
//
//void gechao()
//{
//	vector<int> ret{ 34, 523, 633, 2, 333, 45, 6, 80, 0 };
//	// 找出最大值
//	int maxnum = ret[0];
//	int len = ret.size();
//	for (int i = 1; i < len; ++i)
//	{
//		if (ret[i] > maxnum)
//			maxnum = ret[i];
//	}
//	vector<int> tmp(maxnum+1,0);
//	for (int i = 0; i < len; ++i)
//	{
//		tmp[ret[i]]++;
//	}
//	for (int i = 0; i < maxnum+1; ++i)
//	{
//		while (tmp[i]--)
//			cout << i << " ";
//	}
//	cout << endl;
//}
//
///*
//	时间复杂度：O(n^2) (遍历）
//	空间复杂度：O(1)
//	稳定
//	不敏感
//*/
//void ss(vector<int>& ret)
//{
//	int len = ret.size();
//	for (int i = 0; i < len; ++i)
//	{
//		int start = i;
//		int min = i;
//		//从未排序的数据中找最小值
//		for (int j = start + 1; j < len; ++j)
//		{
//			if (ret[j] < ret[min])
//			{
//				min = j;
//			}
//		}
//		if (min != i)
//			swap(&ret[i], &ret[min]);
//	}
//}
//
///*
//	不稳定
//
//*/
//void select2(vector<int>& ret)
//{
//	int begin = 0;
//	int end = ret.size() - 1;
//	while (begin < end)
//	{
//		// 每次选择最大值和最小值
//		int min = begin, max = begin;
//		for (int i = begin + 1; i <= end; ++i)
//		{
//			// 大的在后面，前面再找到等数就不再改变，因此不稳定
//			if (ret[i] > ret[max])
//				//if (ret[i] >= ret[max])//稳定
//				max = i;
//			// 小的在前面，是稳定的
//			if (ret[i] < ret[min])
//				min = i;
//			// 综合可得不稳定
//		}
//		// 交换的过程中，max发生变化，max == begin，位置发生易位
//		// 当 max==begin,则max=min;
//		swap(&ret[begin], &ret[min]);
//		if (max == begin)
//			max = min;
//		swap(&ret[end], &ret[max]);
//		begin++;
//		end--;
//	}
//}
//
///*
//	时间复杂度：最坏O(n2) , 最好O(n) , 平均O(n^2)
//	空间复杂度：O(1)
//	对数据敏感
//	稳定：遇到相等的元素并没有发生变化
//*/
//// 冒泡排序
//void bubblesort(vector<int>& ret)
//{
//	int n = ret.size();
//	while (n)
//	{
//		// 对于有序的序列，可以通过标签可以提前结束排序过程
//		// flag --> 1 --> 排序过程中没有发生元素交换
//		// flag --> 0 : 说明排序过程中发生了数据交换
//		int end = n;
//		// 优化，当前轮的情况，如果没有发生交换，则flag=1，则表示剩下的部分序列都是有序的
//		int flag = 1;
//		// 一轮冒泡排序
//		for (int i = 0; i < end-1; ++i)
//		{
//			// 相邻两个元素进行比较
//			if (ret[i] > ret[i + 1])
//			{
//				swap(ret[i], ret[i + 1]);
//				flag = 0;
//			}
//		}
//		// 没有发生元素交换，数据已经有序
//		if (flag) break;
//		n--;
//	}
//}
//
//
//// 快速排序
//// 划分
//int piv(vector<int>& ret, int l, int r)
//{
//	int indx = ret[l];
//	while (l < r)
//	{
//		while (l < r&&ret[r] >= indx)
//		{
//			r--;
//		}
//		ret[l] = ret[r];
//		while (l < r&&ret[l] < indx){
//			l++;
//		}
//		ret[r] = ret[l];
//	}
//	ret[l] = indx;
//	return l;
//}
//void QSort(vector<int>& ret, int l, int r)
//{
//	if (l < r)
//	{
//		int m = piv(ret, l, r);
//		QSort(ret, l, m - 1);
//		QSort(ret, m + 1, r);
//	}
//}
//void QSORT(vector<int>& ret)
//{
//	QSort(ret, 0, ret.size()-1);
//}
//
///*
//	时间复杂度：O(nlogn)
//	空间复杂度：O(1)
//	数据不敏感
//	不稳定
//*/
//
//// 堆排序
//void shiftDown1(vector<int>& ret, int parent,int len)
//{
//	int child = 2 * parent + 1;
//	while (child < len)
//	{
//		if (child + 1 < len && ret[child + 1] < ret[child])
//			child++;
//		if (ret[parent] > ret[child])
//		{
//			swap(ret[child], ret[parent]);
//			parent = child;
//			child = 2 * parent + 1;
//		}
//		else
//		{
//			break;
//		}
//	}
//}
//void swap(int& i, int& j)
//{
//	int tmp = i;
//	i = j;
//	j = tmp;
//}
//void heapSort(vector<int>& ret)
//{
//	int len = ret.size() ;
//	// 建堆
//	// 从最后一个非叶子节点开始
//	for (int parent = (len - 2) / 2; parent >= 0; --parent)
//	{
//		shiftDown1(ret, parent,len);
//	}
//	display(ret);
//	// 排序
//	// 实质是一个循环删除的过程
//	for (int i = 0; i < len; ++i)
//	{
//		swap(ret[0], ret[len - 1 - i]);
//		shiftDown1(ret, 0,len-i-1);
//	}
//}
//
//
///*
//
//	快排：
//	时间复杂度：nlogn，最坏O(n^2)，平均情况O(nlogn)
//		：最坏的时间复杂度及其空间复杂度都是理论上的，基本上不会出现
//	空间复杂度：栈空间也算,O(nlogn) -- > O(n^2)（调用的栈空间，函数调用栈）
//	稳定性：不稳定
//	数据敏感：敏感
//*/
//
//// 三数取中的函数，每次在划分的时候都进行一次三数取中，然后再将begin和mid位置的元素进行交换，再进行后面的操作
//int getMid(vector<int>& ret,int begin,int end)
//{
//	// 中间位置
//	int mid = begin + (end - begin) / 2;
//	// begin , mid , end
//	// 在以上三个位置中对应的数中选取中间值
//	if (ret[begin] < ret[mid])
//	{
//		// begin < mid 
//		if (ret[mid] < ret[end]){
//			return mid;
//		}
//		else{
//			// begin < mid  && end<=mid
//			if (ret[begin] > ret[end])
//			{
//				return begin;
//			}
//			else{
//				return end;
//			}
//		}
//	}
//	else
//	{
//		//begin >= mid
//		if (ret[mid] >= ret[end])
//		{
//			return mid;
//		}
//		else
//		{
//			// mid<end && begin>=mid
//			if (ret[begin] > ret[end])
//			{
//				return end;
//			}
//			else{
//				return begin;
//			}
//		}
//	}
//}
//int partionfr(vector<int>& ret, int begin, int end)
//{
//	//最后一个小于基准值的位置
//	int prev = begin;
//	//下一个小于基准值的位置
//	int cur = prev + 1;
//	// 基准值
//	int key = ret[begin];
//	// 寻找下一个需要划分的值还没有越界
//	while (cur <= end){
//		// 当前数据小于基准值
//		// 且最后一个小于基准值的位置和当前小于基准值的位置不连续
//		// 再做交换
//		if (ret[cur] < key && ++prev != cur)
//			swap(ret[cur], ret[prev]);
//		// 寻找下一个满足条件的数据
//		++cur;
//	}
//	swap(ret[begin], ret[prev]);
//	return prev;
//}
//// 返回当前轮划分之后，基准值所存的位置
//int horapartion(vector<int>& ret, int begin, int end)
//{
//	// 选择基准值
//	int key = ret[begin];
//	int start = begin;
//	// 划分
//	while (begin < end)
//	{
//		//从后向前找第一个小于key的位置
//		while (begin < end && ret[end] >= key)
//			--end;
//		//从前向后找第一个大于key的值
//		while (begin < end && ret[begin] <= key)
//			++begin;
//		// 交换begin,end的数据
//		swap(ret[begin], ret[end]);
//	}
//	// key与相遇位置的数据进行交换
//	swap(ret[start], ret[begin]);
//
//	// 返回最后基准值的位置
//	return begin;	
//}
//
//int horapartionMid(vector<int>& ret, int begin, int end)
//{
//	// 三数取中，每一次都三数取中
//	int mid = getMid(ret, begin, end);
//	// 交换 mid -- begin
//	swap(ret[begin],ret[mid]);
//
//	// 选择基准值
//	int key = ret[begin];
//	int start = begin;
//	// 划分
//	while (begin < end)
//	{
//		//从后向前找第一个小于key的位置
//		while (begin < end && ret[end] >= key)
//			--end;
//		//从前向后找第一个大于key的值
//		while (begin < end && ret[begin] <= key)
//			++begin;
//		// 交换begin,end的数据
//		swap(ret[begin], ret[end]);
//	}
//	// key与相遇位置的数据进行交换
//	swap(ret[start], ret[begin]);
//
//	// 返回最后基准值的位置
//	return begin;
//}
//
//int partion1(vector<int>& ret, int begin, int end)
//{
//	int first = ret[begin];
//	while (begin < end)
//	{
//		while (begin<end && ret[end]>first)
//			end--;
//		ret[begin] = ret[end];
//		while (begin < end && ret[begin] <= first)
//			++begin;
//		ret[end] = ret[begin];
//	}
//	ret[begin] = first;
//	return begin;
//}
//
//// 挖坑
//int partion2(vector<int>& ret, int begin, int end)
//{
//	int key = ret[begin];
//	while (begin < end)
//	{
//		// 从后向前找
//		while (begin < end && ret[end] >= key)
//			--end;
//		//填坑:begin
//		ret[begin] = ret[end];
//		while (begin < end && ret[begin] <= key)
//			begin++;
//		// 填坑:end
//		ret[end] = ret[begin];
//	}
//	// 最后一个坑：相遇的位置--> 填充基准值
//	ret[begin] = key;
//	// 返回最后的基准值位置，以此位置进行左右划分
//	// 再对左右的序列进行划分
//	return begin;
//}
//
//// 前后指针法
//int partion3(vector<int>& ret, int begin, int end)
//{
//	// 最后一个小于基准值的位置
//	int prev = begin;
//	// 新发现的下一个小于基准值的位置
//	int cur = prev + 1;
//	int key = ret[begin];
//	while (cur <= end)
//	{
//		// 找到下一个小于基准值的数据，且中间有大于基准值的数据
//		// 则此时小于基准值的数据就应该向前挪
//		//if (ret[cur] < key && prev + 1 != cur){
//		if (ret[cur] < key && ++prev != cur){
//			//++prev;//第一个大于基准值的位置
//			swap(ret[prev], ret[cur]);
//		}
//		// 如果当前数据直接大于key基准值，则只需要哦直接向后寻找
//		++cur;
//	}
//	swap(ret[begin], ret[prev]);
//	return prev;
//}
//
//int part(vector<int>& ret, int begin, int end)
//{
//	int prev = begin;
//	int cur = prev + 1;
//	int key = ret[begin];
//	while (cur <= end)
//	{
//		while (ret[cur] < key && ++prev != cur)
//			swap(ret[cur], ret[prev]);
//		++cur;
//	}
//	swap(ret[prev], ret[begin]);
//	return prev;
//}
//void quicksort(vector<int>& ret, int begin, int end)
//{
//	if (begin >= end)
//		return;
//	//划分当前区间
//	int keyPos = horapartionMid(ret, begin, end);
//	//划分子区间
//	quicksort(ret, begin, keyPos - 1);
//	quicksort(ret, keyPos + 1, end);
//}
//
//// 小区间是划分大区间保存下来的
//#include <stack>
//// 栈实现快排的非递归
//void quickSortNoR(vector<int>& ret)
//{
//	// 保存待划分区间
//	int begin = 0;
//	int end = ret.size() - 1;
//	stack<int> st; 
//	st.push(end);
//	st.push(begin);
//	// 遍历栈，划分栈中的每一个区间
//	while (!st.empty())
//	{
//		// 获取栈顶区间
//		begin = st.top();
//		st.pop();
//		end = st.top();
//		st.pop();
//		// 划分，得到基准值的位置
//		int keyPos = partion1(ret, begin, end);
//		// 子区间入栈，先入右边的区间，再入左边的区间
//		// 右:keyPos +1 ,end
//		if (keyPos + 1 < end) // 至少有两个值,才有必要进行下一轮的划分
//		{
//			st.push(end);
//			st.push(keyPos + 1);
//		}
//		// 左:beign , keyPos-1
//		if (begin < keyPos - 1)
//		{
//			st.push(keyPos - 1);
//			st.push(begin);
//		}
//	}
//}
//
//
//void quickNoR(vector<int>& ret)
//{
//	// 递归就是用函数栈空间存储了对应变量的值
//	// 此处就用栈来存储变量的值
//	stack<int>  st;
//	int begin = 0;
//	int end = ret.size() - 1;
//	if (end > 0){
//		st.push(end);
//		st.push(begin);
//	}
//	//如果栈中区间利用完全，则表示区间划分完成
//	while (!st.empty())
//	{
//		// 得到需要划分的区间
//		begin = st.top();
//		st.pop();
//		end = st.top();
//		st.pop();
//		// 对当前区间进行划分
//		int keyPos = horapartionMid(ret, begin, end);
//		// 对当前划分的区间进行存储，以便下一次再划分
//		//区间中至少得有两个元素才能继续划分
//		
//		// 先对后面的区间进行压栈，先对前面的区间进行划分
//		if (keyPos + 1 < end){
//			st.push(end);
//			st.push(keyPos + 1);
//		}
//		if (begin < keyPos - 1)
//		{
//			st.push(keyPos - 1);
//			st.push(begin);
//		}
//	}
//}
//
//#include <queue>
//// 用队列实现快排
//void quickNoRQ(vector<int>& ret)
//{
//	queue<int> q;
//	int begin = 0;
//	int end = ret.size() - 1;
//	if (end > 0)
//	{
//		q.push(begin);
//		q.push(end);
//	}
//	while (!q.empty())
//	{
//		begin = q.front();
//		q.pop();
//		end = q.front();
//		q.pop();
//
//		int keyPos = horapartionMid(ret, begin, end);
//		if (keyPos - 1 > begin)
//		{
//			q.push(begin);
//			q.push(keyPos - 1);
//		}
//		if (keyPos + 1 < end)
//		{
//			q.push(keyPos + 1);
//			q.push(end);
//		}
//	}
//}
///*
//	快排：
//		划分：hora，挖坑，前后指针
//		优化：基准值的选择（三数取中），小区间优化
//		非递归：栈、队列 保存区间值
//		最坏情况：数据有序，时间复杂度：优化之前n^ 2，优化之后：nlogn-->基准值选择方法
//				  如果是递归：优化之前：栈溢出
//*/
//
//void p(int n)
//{
//	if (n <= 0)
//		return;
//	cout << n << endl;
//	p(n - 1);
//}
//
///*
//	时间复杂度：O(nlogn)
//	空间复杂度：O(n+logn)-->O(n)
//	稳定排序
//	对数据不敏感：无论有序还是无序都需要划分
//*/
//// 合并：需要知道两个有序子序列的区间
//// 相邻区间进行合并：因此只需要begin,mid,end即可
//// [begin,mid],[mid+1,end]
//void merge(vector<int>& ret, int begin, int mid, int end, vector<int>& tmp)
//{
//	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
//	int idx = begin;
//	// 两个区间都有值的时候进行合并
//	while (begin1 <= end1&& begin2 <= end2)
//	{
//		if (ret[begin1] <= ret[begin2])
//		{
//			tmp[idx++] = ret[begin1++];
//		}
//		else
//		{
//			tmp[idx++] = ret[begin2++];
//		}
//	}
//	// 如果有剩余的元素
//	while (begin1 <= end1)
//	{
//		tmp[idx++] = ret[begin1++];
//	}
//	while (begin2 <= end2)
//	{
//		tmp[idx++] = ret[begin2++];
//	}
//	// 将已经合并的有序序列，拷贝到原始空间当中
//	for (int i = begin; i <= end; ++i)
//	{
//		ret[i] = tmp[i];
//	}
//}
////归并排序
//void mergeSort(vector<int>& ret,int begin, int end,vector<int>& tmp)
//{
//	// 只有一个元素，不需要归并
//	if (begin >= end)
//		return;
//	int mid = begin + (end - begin) / 2;
//	//首先保证子区间有序
//	// 先对子区间进行排序
//	mergeSort(ret, begin, mid,tmp);
//	mergeSort(ret, mid + 1, end,tmp);
//	//合并子区间
//	merge(ret, begin, mid, end,tmp);
//}
//void mergesort(vector<int>& ret)
//{
//	int len = ret.size();
//	vector<int> tmp(len);
//	mergeSort(ret, 0, len - 1, tmp);
//}
//
//
//
////归并的非递归
//// 不需要分解：直接合并
//// 合并
//void mergeSortNoR(vector<int>& ret)
//{
//	// 待合并区间的元素个数
//	int  k = 1;
//	int n = ret.size();
//	vector<int> tmp(n);
//	while (k < n)
//	{
//		// 一轮的合并
//		for (int i = 0; i < n; i += 2 * k){
//			// [begin,mid] [mid+1,end]
//			int begin = i;
//			// 判断mid是否越界
//			int mid = i + k - 1;
//			// 只有一个子区间，无需再合并
//			if (mid >= n - 1)
//				continue;
//			// 判断end是否越界
//			int end = i + 2 * k - 1;
//			// 更新end
//			if (end >= n)
//				end = n - 1;
//			merge(ret, begin, mid, end, tmp);
//		}
//		k *= 2;
//	}
//}
//
//
//
//void mergeNoR(vector<int>& ret)
//{
//
//	int k = 1;
//	int n = ret.size();
//	vector<int> tmp;
//	tmp.resize(n);
//	while (k < n)
//	{
//		for (int i = 0; i < n; i += 2*k)
//		{
//			int begin = i;
//			int mid = i +  k - 1;
//			if (mid >= n - 1)
//				continue;
//			int end = i + 2 * k - 1;
//			if (end >= n)
//				end = n - 1;
//			merge(ret, begin, mid, end, tmp);
//		}
//		k *= 2;
//	}
//}
//
//
//
//// 命名空间解决定义相同变量名的相同的问题
//namespace N1
//{
//	int a;
//	int add(int left, int right)
//	{
//		return left + right;
//	}
//}
//
//#include <string>
//
//
//void test10(){
//	string str; //""
//	// 用C字符串创建一个C++字符串对象
//	string str2("123");// "123"
//	string str3 = "abc";//"abc"
//	string str4("0123456789", 5);//"01234"
//	string cpy(str2);//"123"
//
//	string str5(str4, 2, 2); //"23"
//	string str6(3, 'a');// "aaa"
//	//cout << str6 << endl;
//
//	str6 = str5; //对象已经存在，给存在的对象赋值
//	str6 = 'A';
//	str6 = "A";
//
//}
//
///*
//	迭代器：访问容器的元素的一种通用方式
//	所有支持迭代器的容器，其迭代器的使用方式完全相同
//	begin迭代器：第一个元素的位置；
//	end迭代器：最后一个元素的下一个位置
//	迭代器的范围是左闭右开:[begin,end)
//	迭代器的使用方式：类似于指针的使用方式，可以通过解引用获取元素内容，可以通过++，--进行位置的移动
//	迭代器是可读可写的接口
//
//	反向迭代器：迭代器有错位实现的情况，防止越界问题
//
//	可读可写的迭代器：iterator , reverse_iterator
//	只读迭代器：const_iterator , const_reverse_iterator
//
//*/
//// string1：2：06
//void test11(){
//	string str("01233456789");
//	//迭代器的遍历方式
//	string::iterator it = str.begin();
//	while (it != str.end())
//	{
//		cout << *it <<" ";
//		++it;
//	}
//	cout << endl;
//
//	vector<int> ret{ 10,2,0,8,0,74,87,2,387,4,39,8,2 };
//	vector<int>::iterator vit = ret.begin();
//	while (vit != ret.end())
//	{
//		cout << *vit << " ";
//		++vit;
//	}
//	cout << endl;
//
//	vector<int>::reverse_iterator rvit = ret.rbegin();
//	while (rvit != ret.rend())
//	{
//		cout << *rvit << " ";
//		++rvit;
//	}
//	cout << endl;
//
//	// 返回一个const迭代器
//	// 只读迭代器：不支持写操作
//	vector<int>::const_iterator cit = ret.cbegin();
//}
///*
//	线程池中，上来不同的业务，客户端传上来的业务里面有不同的业务代号
//	线程池解析后，根据不同的业务代号，回调不同的执行函数
//*/
//
//void merge1(vector<int>& ret, int begin, int mid , int end, vector<int>& tmp)
//{
//	int begin1 = begin, end1 = mid, begin2 = mid + 1, end2 = end;
//	int idx = begin;
//	while (begin1 <= end1 && begin2 <= end2)
//	{
//		if (ret[begin1] <= ret[begin2])
//		{
//			tmp[idx++] = ret[begin1++];
//		}
//		else
//		{
//			tmp[idx++] = ret[begin2++];
//		}
//	}
//	while (begin1 <= end1)
//	{
//		tmp[idx++] = ret[begin1++];
//	}
//	while (begin2 <= end2)
//	{
//		tmp[idx++] = ret[begin2++];
//	}
//	for (int i = begin; i <= end; ++i)
//	{
//		ret[i] = tmp[i];
//	}
//}
//void mst(vector<int>& ret,int begin , int end , vector<int>& tmp)
//{
//	if (begin >= end) return;
//	int mid = begin + (end - begin) / 2;
//	mst(ret, begin, mid,tmp);
//	mst(ret, mid + 1, end,tmp);
//	merge1(ret, begin, mid, end, tmp);
//}
//void m1(vector<int>& ret)
//{
//	int sz = ret.size();
//	vector<int> tmp(sz);
//	mst(ret, 0, sz-1, tmp);
//}
//
//// 归并排序非递归
//void m1NoR(vector<int>& ret)
//{
//	int k = 1;
//	int n = ret.size();
//	vector<int> tmp(n);
//	// k ： 为间隔个数
//	while (k < n)
//	{
//		for (int i = 0; i < n; i += 2 * k)
//		{
//			int begin = i;
//			int mid = i + k - 1;
//			// 当mid为n-1的时候表示只有一个区间，前段序列，没有后端序列
//			if (mid >= n - 1)
//				continue;
//			int end = i + 2 * k - 1;
//			// 后端序列中有部分数据
//			if (end >= n)
//				end = n - 1;
//			merge1(ret, begin, mid, end, tmp);
//		}
//		k *= 2;
//	}
//}
//
//void testTime()
//{
//	srand(time(NULL));
//	int n;
//	scanf("%d", &n);
//	//int* arr = (int*)malloc(sizeof(int)*n);
//	vector<int> arr;
//	arr.resize(n);
//	for (int i = 0; i < n; ++i)
//	{
//		arr[i] = rand() % 100;
//	}
//	cout << "data:" << endl;
//	display(arr);
//	size_t begin = clock();
//	m1NoR(arr);
//	size_t end = clock();
//	printf("is:%d\n", end - begin);
//	cout << "after sort:" << endl;
//	display(arr);
//	//begin = clock();
//	//heapSort(arr);
//	//end = clock();
//	//printf("is:%d\n", end - begin);
//}
//
//int mainw(){
//	//test11();
//	//test10();
//	//p(10);
//	//gechao();
//	//testTime();
//	//test2();
//	testTime();
//	//test();
//	system("pause");
//	return 0;
//}

//void t(){ 
//	vector<int> a{ 3, 4, 5, 62 };
//	reverse(a.begin(),a.end());
//}
//
//class CStudent//学生类
//{
//public:
//	// 构造函数
//	CStudent(int id = 0, int age = 0, string name = "")
//		:m_age(age)
//		, m_id(id)
//		, m_name(name)
//	{}
//
//	// 将该函数声明成友元函数
//	// 目的是使得函数可以访问CStudent类的私有成员函数
//	friend ostream& operator<<(ostream& o, const CStudent& s);
//
//	// 将该输入函数声明为友元函数
//	// 使得函数体可以访问CStudent类的私有成员变量进行赋值
//	friend istream& operator>>(istream& o,  CStudent& s);
//private:
//	int m_age;//年龄
//	int m_id; //ID号
//	string m_name;//名字
//};
//
//// 重载ostream对象的流插入<<运算符函数
//// 目的是使得可以打印输出CStudent对象的信息
//ostream& operator<<(ostream& o, const CStudent& s)
//{
//	o << s.m_name << "-" << s.m_id << "-" << s.m_age << endl;
//	return o;
//}
//
//// 重载istream对象的流提取>>运算符函数
//// 目的是使得初始化CStudent对象的内容
//istream& operator>>(istream& is, CStudent& s)
//{
//	// 输入一个字符串，再对字符串的内容进行裁剪
//	string inputStr;
//	is >> inputStr;
//
//	// 查找首次出现逗号的位置
//	int pos = inputStr.find("-", 0); 
//	// 截取从0到pos位置的字符串
//	string tmpStr = inputStr.substr(0, pos);
//
//	s.m_name = tmpStr.c_str();
//
//	// 查找第二次出现"-"的位置
//	int pos2 = inputStr.find("-", pos + 1);
//	tmpStr = inputStr.substr(pos + 1, pos2 - pos - 1);
//	// atoi ： 可以将char*类型的内容转成int类型
//	s.m_id = atoi(tmpStr.c_str());
//
//	tmpStr = inputStr.substr(pos2 + 1, inputStr.length() - pos2 - 1);
//	s.m_age = atoi(tmpStr.c_str());
//
//	return is;
//}
//
//void test(){
//	CStudent s;
//	cin >> s;
//	cout << s;
//}




//并查集，本质就是一个森林


//class UnionFindSet{
//public:
//	//  初始化并查集结构
//	// 其中 n 表示节点范围
//	UnionFindSet(size_t n)
//	{
//		// 初始化每一个节点都是双亲
//		// 当初始化每一个节点都是双亲，且为一棵树的时候，自身是根节点且这棵树上只有一个节点
//		_v.resize(n, -1);
//	}
//
//	// 找当前节点的根
//	// 给一个元素的编号，找到该元素所在集合的名称
//	int FindRoot(int el)
//	{
//		// 如果数组中存储的是负数，找到，否则一直找
//		while (_v[el] >= 0)
//		{
//			el = _v[el];
//		}
//		return el;
//	}
//
//	// 并查集的合并
//	bool Union(int el1, int el2)
//	{
//		int root1 = FindRoot(el1);
//		int root2 = FindRoot(el2);
//
//		// 两个元素在同一个集合，还合并个屁
//		if (root1 == root2)
//		{
//			return false;
//		}
//		// 将两个集合中的元素合并，因此可以得到一棵树下的元素总和
//		_v[root1] += _v[root2];
//		// 将其中一个集合名称改变为另外一个
//		_v[root2] = root1;
//		return true;
//	}
//
//	// 数组中的负数的个数，即为集合的个数
//	size_t size() const
//	{
//		int cnt = 0;
//		for (auto& e : _v)
//		{
//			if (e < 0)
//				++cnt;
//		}
//		return cnt;
//	}
//
//	// 判断两个节点是否在一个集合
//	// 根据是否是同一个根，如果是则是同一个集合，否则不是
//	bool isSameUnion(int el1, int el2)
//	{
//		return FindRoot(el1) == FindRoot(el2);
//	}
//private:
//	vector<int> _v;
//};
//
//
//void test(){
//
//
//	unordered_map<int, int> _hashmap;
//	_hashmap.insert(make_pair(1, 2));
//	_hashmap.insert(make_pair(8, 992));
//	_hashmap.insert(make_pair(6, 21));
//	_hashmap.insert(make_pair(5, 22));
//	_hashmap.insert(make_pair(4, 12));
//	_hashmap.insert(make_pair(91, 42));
//
//	auto hashIt = _hashmap.find(1);
//	cout << hashIt->first << "-" << hashIt->second << endl;
//}
//void insertsosrt(vector<int>& ret)
//{
//
//}
//int maisn(){
//
//	//test();
//	system("pause");
//	return 0;
//}