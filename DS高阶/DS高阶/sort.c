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
		// end����ʾ����ѧ�е����һ��λ��
		int end = i;
		int key = arr[end + 1];
		//�ҵ���һ��С��key��λ��
		while (end >= 0 && arr[end] >key){
			// ��ǰλ������ƶ�λ��
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
		// ���������е����λ��
		int end = i; //[0,n-2]
		// ��ǰ��Ҫ��������ݣ�[1,n-1]
		int key = arr[end + 1];
		// ����Ч��Χ�ڶ����������к͵�ǰ���ݽ��бȽϣ�Ȼ���ƶ�
		while (end >= 0 && arr[end] > key)
		{
			arr[end + 1] = arr[end];
			--end;
		}
		// ���뵱ǰ����
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
	//i = i + (j - i) >> 1; // �ȼ��� i = (i + (j - i)) >> 1;	
	//i = i + ((j - i) >> 1);
	

	printf("%d\n", i);
	system("pause");
	return 0;
}

// ǰ���ż
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
	ʱ�临�Ӷȣ��O(n^1.3) ���O(n) ƽ��O(n^1.3)
	���ȶ�
	����
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

// ֱ�Ӳ�������
/*
	ʱ�临�Ӷȣ����O(n^2)��һ���ע����Ӷȣ�
				��ã�O(n)������������������ƶ�Ԫ�ص�ѭ������Ҫִ��
				ƽ����O(n^2)
	�ռ临�Ӷȣ�O(1)�������˳������ռ�
	�ȶ��ԣ��˴��õ�>������ȶ��Բ�û�иı�
	�������У�����
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


// ������
void shiftDown(int* arr, int parent,int len)
{
	// ���µ�������Ҫ���ڵ�
	// �ڴ˴�����ѣ������С����
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
	// �������򣬴��
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
// ����
void buildHeap(int* arr, int len)
{
	for (int parent = (len-2)/2; parent >=0;--parent)
	{
		shiftDown(arr, parent,len);
	}
}
// ������
void heapsort(int* arr, int len){
	buildHeap(arr, len);
	printf("����:>\n");
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

