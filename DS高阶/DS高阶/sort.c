#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
void display(int* arr, int len)
{
	for (int i = 0; i < len; ++i)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void swap(int* i, int* j)
{
	int tmp = *i;
	*i = *j;
	*j = tmp;
}
/*
void insertsort(int* arr, int n)
{
	int i = 0;
	while (i < n-1)
	{
		// end：表示有序学列的最后一个位置
		int end = i;
		int key = arr[end + 1];
		//找到第一个小于key的位置
		while (end >= 0 && arr[end] >key){
			// 当前位置向后移动位置
			arr[end + 1] = arr[end];
			--end;
		}
		arr[end + 1] = key;
		++i;
	}
}

void isort(int* arr, int n)
{
	int i = 0;
	while (i < n - 1)
	{	
		// 已排序序列的最后位置
		int end = i; //[0,n-2]
		// 当前需要插入的数据，[1,n-1]
		int key = arr[end + 1];
		// 在有效范围内对已排序序列和当前数据进行比较，然后移动
		while (end >= 0 && arr[end] > key)
		{
			arr[end + 1] = arr[end];
			--end;
		}
		// 插入当前数据
		arr[end + 1] = key;
		++i;
	}
}


// 36min


void insert(int* arr, int n)
{
	int i = 0;
	int j = 0;
	for (i = 1; i < n ; ++i)
	{
		int key = arr[i];
		for ( j = i - 1; j >= 0 && key < arr[j]; --j)
		{
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}

int mainq(){

	//test();
	int i = 1;
	int j = 5;
	//i = i + (j - i) >> 1; // 等价于 i = (i + (j - i)) >> 1;	
	//i = i + ((j - i) >> 1);
	

	printf("%d\n", i);
	system("pause");
	return 0;
}

// 前奇后偶
void rst(int* a, int num)
{
	int left = 0;
	int right = num - 1;
	while (left < right)
	{
		while (left < right && (a[left] & 1))
		{
			left++;
		}
		while (left < right && !(a[right] & 1))
		{
			--right;
		}
		swap(a[left, right]);
	}
}
*/

/*
	时间复杂度：最坏O(n^1.3) 最好O(n) 平均O(n^1.3)
	不稳定
	敏感
*/
void shell(int arr[], int len)
{
	int step = len / 2;
	while (step > 1)
	{
		for (int i = step; i < len; i++)
		{
			int j = i - step;
			int cur = arr[i];
			while (j >= 0 && cur < arr[j])
			{
				arr[j + step] = arr[j];
				j -= step;
			}
			arr[j + step] = cur;
		}
		step =step/3+1;
	}
}

// 直接插入排序
/*
	时间复杂度：最坏：O(n^2)（一般关注最坏复杂度）
				最好：O(n)，有序的情况，里面的移动元素的循环不需要执行
				平均：O(n^2)
	空间复杂度：O(1)：开辟了常数个空间
	稳定性：此处用的>：相对稳定性并没有改变
	数据敏感：敏感
*/
void ist(int arr[], int len)
{
	int i = 1;
	while (i < len )
	{
		int tmp = arr[i];
		int j = i - 1;
		while (arr[j] > tmp && j >= 0)
		{
			arr[j + 1] = arr[j];
			--j;
		}
		arr[j + 1] = tmp;
		++i;
	}
}
void test(){
	int arr[] = { 34, 5, 63, 2, 33, 45, 6, 80, 0 };
	int n = sizeof(arr) / sizeof(arr[0]);
	shell(arr, n);
	display(arr, n);
}
#include <time.h>
void testTime()
{
	srand(time(NULL));
	int n;
	scanf("%d", &n);
	int* arr = (int*)malloc(sizeof(int)*n);
	for (int i = 0; i < n; ++i)
	{
		arr[i] = rand();
	}
	display(arr, n);
	size_t begin = clock();
	shell(arr, n);
	size_t end = clock();
	printf("is:%d\n", end - begin);
	display(arr, n);

	begin = clock();
	shell(arr, n);
	end = clock();
	printf("is:%d\n", end - begin);
}


// 堆排序
void shiftDown(int* arr, int parent,int len)
{
	// 向下调整，需要父节点
	// 在此处建大堆，排序从小到大
	int child = 2 * parent + 1;
	while (child<len)
	{
		if (child + 1 < len && arr[child + 1] > arr[child])
			++child;
		if (arr[parent] < arr[child]){
			swap(&arr[parent], &arr[child]);
			parent = child;
			child = 2 * parent + 1;
		}
		else
		{
			break;
		}
	}
}
void shiftUp(int* arr, int child, int len)
{
	// 向上排序，大堆
	int parent = (child - 1) / 2;
	while (parent >= 0)
	{
		if (arr[child] > arr[parent]){
			swap(&arr[child], &arr[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else
		{
			break;
		}
	}
}
// 建堆
void buildHeap(int* arr, int len)
{
	for (int parent = (len-2)/2; parent >=0;--parent)
	{
		shiftDown(arr, parent,len);
	}
}
// 推排序
void heapsort(int* arr, int len){
	buildHeap(arr, len);
	printf("建堆:>\n");
	display(arr, len);
	for (int i = 0; i < len; i++)
	{
		swap(&arr[0], &arr[len - 1 - i]);
		shiftDown(arr, 0, len-i-1);
	}
}
void test2(){
	int arr[] = { 23,9,32,8,70,197,481,24,130 };
	int len = sizeof(arr) / sizeof(arr[0]);
	display(arr, len);
	heapsort(arr, len);
	display(arr, len);
}

void shells(int* arr, int len)
{
	int step = len / 2;
	while (step >= 1)
	{
		for (int i = step; i < len; ++i)
		{
			int cur = arr[i];
			int j = i - step;
			while (j >= 0 && arr[j] > cur)
			{
				arr[j + step] = arr[j];
				j -= step;
			}
			arr[j + step] = cur;
		}
		step /= 2;
	}
}
void test3(){
	int arr[] = { 23, 9, 32, 8, 70, 197, 481, 24, 130 };
	int len = sizeof(arr) / sizeof(arr[0]);
	display(arr, len);
	shells(arr, len);
	display(arr, len);
}

