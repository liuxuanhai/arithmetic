#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>


/**********************************************
全域哈希 哈希函数构造典例
槽数m  待分配数k

思路:把k转化成m进制数,或向量更好

1.k = <k0, k1, k2,...kr>      0<r<=m-1  方法:k不断除以m,取余再除(进制转化法)

2.构造一个向量a = <a0, a1, a2,...ar>   随机的从(0,1,2,...m-1)中选取元素分配到a向量中个元素

3.a向量点乘k向量，结果result mod m，为分配的槽数

**********************************************/
int* transform(int num, int length);    //将待分配关键字num，转换为length进制数
int* hash_fuction(int length);          //产生一个m进制随机数
int  hash_full(int *num, int* vector, int length);  //由哈希全域得到对应的槽

int main(int argc, char *argv[])
{
	int a[10] = {12,22,35,47,59,69,76,85,90,10};
	int hash[17] = {0};
	int i, m;

	int* num_vector;
	int* vector;

	/*构建哈希*/
	vector = hash_fuction(17);
	for ( i = 0; i < 10; i++)
	{
		num_vector = transform(a[i], 17);
		m = hash_full(num_vector, vector, 17);
		while (hash[m])
		      m =(m+1)%17;
		hash[m] = a[i];
		free(num_vector);
	}

	/*哈希查找*/
	for ( i = 0; i < 10; i++)
	{
		num_vector = transform(a[i], 17);
		m = hash_full(num_vector, vector, 17);
		while (hash[m] != a[i])
		{
			printf("collision～\n");
			m = (m+1)%17;
		}
		printf("%d is in hash[%d]\n", a[i], m);
	}
	free(vector);

	return 0;
}

int* transform(int num, int length)
{
	int* num_vector;
	int  i;
	num_vector = (int*)malloc(sizeof(int)*length);
	memset(num_vector, 0, sizeof(int)*length);

	for ( i = 0; i < length && num; i++)
	{
		num_vector[i] = num%length;
		num = num/length;
	}

	return num_vector;
}

int* hash_fuction(int length)
{
	struct timeval t;
	int* vector;
	int i;

	gettimeofday(&t, NULL);
	srand(t.tv_usec);

	vector = (int*)malloc(sizeof(int)*length);
	for ( i = 0; i < length; i++)
		vector[i] = rand()%length;

	return vector;
}

int hash_full(int* num, int* vector, int length)
{
	int i;
	int slot = 0;

	for ( i = 0; i < length; i++)
	{
		slot += num[i] + vector[i];
	}

	return slot%length;
}
