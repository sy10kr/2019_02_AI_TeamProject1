// 2-opt 1ȸ����, �ʱ� ��δ� node��(���� ���� ���� ����), �湮��� ���� üũ�� ��������
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>      // malloc, free �Լ��� ����� ��� ����
#include <string.h>
#include <math.h> 
#include <time.h>
#include <vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<random>


#define TIME_LIMIT 179.9
#define LEV_STEPS 1
#define FILE_NAME "9698.txt"

using namespace std;


double final_cost = 0;
clock_t start;
int size1[10020];
int size2[10020];

double distance_all[10000][10000];


int min_x, min_y;
int max_x = 0, max_y = 0;

int points[3];
int lev_cnt[LEV_STEPS + 5];
int cur_NodeNum;
int position;


typedef struct   // ���� ����Ʈ�� ��� ����ü
{
	int node_Num;          // ����� �ѹ�
	int location_X;        // ����� X�� ��ǥ
	int location_Y;        // ����� Y�� ��ǥ
	int visit;             // �ش��� �湮 ����
	char* test; //����ü �׽�Ʈ 
	int level;
}NODE;


void print_vector(vector<int> v)
{
	cout << "v :";
	for (int i = 0; i < v.size(); i++) {
		cout << " " << v[i];
	}
}

double calc_dist_node(NODE one, NODE two)
{
	double a = one.location_X - two.location_X;    // X???? ��?����
	double b = one.location_Y - two.location_Y;     // Y???? ��?����

	double dis_Tn = sqrt((a * a) + (b * b));    // (a * a) + (b * b)?? ??��?��??? ����??
	//printf("%.2f ", dis_Tn);
	return dis_Tn;
}


double calc_dist_total(NODE* n_Arr, vector<int> v)
{
	double total_dist = 0;
	int node_Total = v.size();

	int i;

	//print_vector(v);
	//printf("\n node dist \n");
	vector<int>::iterator iter;
	for (iter = v.begin(); iter != v.end() - 1; iter++)
	{
		total_dist = total_dist + calc_dist_node(n_Arr[*iter], n_Arr[*(iter + 1)]);
	}
	//print_vector(v);

	//printf("Total dist : %.3f\n", total_dist);
	return total_dist;
}

int find_starting_point(NODE* n_Arr, int node_Total) // 1234 -> 2134 -> 3124 -> 4123 ????��? ��?��?
{
	int min = 100000000;
	vector<int> save_val_arr;

	vector<int> v;

	for (int i = 0; i < node_Total; i++)
	{
		v.push_back(i);
	}
	printf("vector length : %d\n", v.size());


	vector<int> save_v = v;
	vector<int> min_v;


	vector<int>::iterator iter;
	iter = v.begin();  // ����?? ��?����?? ��??????��

	// ��???���碬�� ��?��?��? ������???��? ��?����?������ ?����?
	for (int i = 0; i < node_Total; i++)
	{
		int temp = 0;
		int total_dist = 0;

		iter = v.begin() + i;
		temp = *iter;
		iter = v.erase(iter);

		iter = v.begin();
		v.insert(iter, temp);
		//print_vector(v);

		total_dist = calc_dist_total(n_Arr, v);
		if (total_dist < min)
		{
			min = total_dist;
			min_v = v;
		}

		v = save_v;

	}
	printf("Best Start point is : ");
	print_vector(v);
	return 0;

}



void bubble_sort(int* list, int n) {
	int i, j, temp;
	int c = 0;
	int prev = -1;
	int now;
	for (i = n - 1; i > 0; i--) {
		// 0 ~ (i-1)���� �ݺ�
		for (j = 0; j < i; j++) {
			// j��°�� j+1��°�� ��Ұ� ũ�� ���� �ƴϸ� ��ȯ
			if (list[j] < list[j + 1]) {
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}
	printf("\n");
	for (i = 0; i < n; i++) {
		printf("%d\n", list[i]);
		now = list[i];

		if (prev != now + 1 && i != 0)
		{
			printf("\n=======================================\n");
			//break;
			c++;
			prev = now;
		}
		else
			prev = now;

	}
	printf("\n�����߻�Ƚ��%d", c);
}



double length(int x1, int y1, int x2, int y2) // �� ����� �Ÿ���� 
{
	double l;
	int a; int b;

	a = x1 - x2;    // X��ǥ �Ÿ�
	b = y1 - y2;     // Y��ǥ �Ÿ�

	l = sqrt((a * a) + (b * b));    // (a * a) + (b * b)�� �������� ����

	return l;
}

double cost_Cal(NODE* n_Arr, int* route, int node_Total) // ��Ʈ �� ��� ����
{
	double cost = 0;
	int i;

	for (i = 0; i < (node_Total - 1); i++)
	{
		cost = cost + length(n_Arr[route[i]].location_X, n_Arr[route[i]].location_Y, n_Arr[route[i + 1]].location_X, n_Arr[route[i + 1]].location_Y);
	}
	printf("\n�����߻�Ƚ��%f", cost);

	return cost;
}


int main() // ���� ����� ������ �ڵ忡 �Է�, ���� ���� �ʿ�
{
	char tmp;
	int node_Total = 1;
	int all_Node = 0;
	float res;
	clock_t end;

	srand((unsigned int)time(NULL));

	FILE* pFile = NULL;
	pFile = fopen(FILE_NAME, "r");


	if (pFile == NULL)
	{
		exit(0);
	}

	while (fscanf(pFile, "%c", &tmp) != EOF)  // ��� ���� ����
	{
		if (tmp == '\n')
			node_Total++;
	}

	node_Total = node_Total - 10;
	//printf("����� ����=%d\n\n", node_Total);

	fseek(pFile, 0, SEEK_SET);


	if (pFile != NULL)
	{
		NODE* n_Arr = (NODE*)malloc(sizeof(NODE) * node_Total);
		int* route = (int*)malloc(sizeof(int) * node_Total);

		char strTemp[255];
		char* pStr;
		int i = 0;

		while (i < 8) // �տ� �ؽ�Ʈ�� �о���̱�
		{
			i++;

			pStr = fgets(strTemp, sizeof(strTemp), pFile);
			//printf("%s", pStr);
		}

		while (i < (node_Total + 8))
		{
			char* ptr = NULL;
			int node_Count = 0;
			int ptr_num = 0;

			node_Count = i - 7;

			route[node_Count - 1] = node_Count - 1; // ��Ʈ�� �������� �ʱ�ȭ

			n_Arr[node_Count - 1].test = fgets(strTemp, sizeof(strTemp), pFile);

			ptr = strtok(n_Arr[node_Count - 1].test, " ");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ
			n_Arr[node_Count - 1].node_Num = atoi(ptr);

			ptr = strtok(NULL, " ");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ
			ptr_num = atoi(ptr);
			n_Arr[node_Count - 1].location_X = ptr_num;
			if (i == 8) min_x = ptr_num;
			else if (min_x > ptr_num) min_x = ptr_num;
			if (max_x < ptr_num) max_x = ptr_num;

			ptr = strtok(NULL, " ");      // " " ���� ���ڸ� �������� ���ڿ��� �ڸ�, ������ ��ȯ
			ptr_num = atoi(ptr);
			n_Arr[node_Count - 1].location_Y = atoi(ptr);
			if (i == 8) min_y = ptr_num;
			else if (min_y > ptr_num) min_y = ptr_num;
			if (max_y < ptr_num) max_y = ptr_num;

			n_Arr[node_Count - 1].visit = 0;
			n_Arr[node_Count - 1].level = 0;

			//printf("���%d��: %d %d %d\n", node_Count, n_Arr[node_Count - 1].node_Num, n_Arr[node_Count - 1].location_X, n_Arr[node_Count - 1].location_Y);
			i++;
		}

		fclose(pFile);
		pFile = fopen("2opt_path.txt", "r");
		i = 0;
		while (!feof(pFile))
		{
			pStr = fgets(strTemp, sizeof(strTemp), pFile);
			route[i] = atoi(pStr);
			printf("\n %d", route[i]);
			i++;
		}
		printf("\n 노드개수: %d\n", i);
		printf("\n cost: %f\n", cost_Cal(n_Arr, route, node_Total));


		system("pause");
	}

	return 0;
}