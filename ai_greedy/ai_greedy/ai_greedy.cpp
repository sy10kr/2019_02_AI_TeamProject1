// 2-opt 1회적용, 초기 경로는 node순(랜덤 노드로 수정 고려), 방문노드 여부 체크도 아직안함
#define _CRT_SECURE_NO_WARNINGS
#define TIME_LIMIT 179.9
#define FILE_NAME "xmc10150.txt"

#include <stdio.h>
#include <stdlib.h>      // malloc, free 함수가 선언된 헤더 파일
#include <string.h>
#include <math.h> 
#include <time.h>
#include <vector>
#include<iostream>
#include<algorithm>
#include<random>
#include <fstream>

using namespace std;

double final_cost = 0;
clock_t start;
int size1[15020];
int size2[15020];

double distance_all[15000][15000];

typedef struct   // 연결 리스트의 노드 구조체
{
	int node_Num;          // 노드의 넘버
	int location_X;        // 노드의 X축 좌표
	int location_Y;        // 노드의 Y축 좌표
	int visit;             // 해당노드 방문 여부
	char* test; //구조체 테스트 
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
	double a = one.location_X - two.location_X;    // XÁÂÇ¥ °Å¸®
	double b = one.location_Y - two.location_Y;     // YÁÂÇ¥ °Å¸®

	double dis_Tn = sqrt((a * a) + (b * b));    // (a * a) + (b * b)ÀÇ Á¦°ö±ÙÀ» ±¸ÇÔ
												//printf("%.2f ", dis_Tn);
	return dis_Tn;
}

double calc_dist_total(NODE * n_Arr, vector<int> v)
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

int find_starting_point(NODE * n_Arr, int node_Total) // 1234 -> 2134 -> 3124 -> 4123 ÇüÅÂ·Î ¹Ù²ñ
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
	iter = v.begin();  // º¤ÅÍ ¹Ýº¹ÀÚ ½ÃÀÛÁöÁ¡

					   // ¾ÕÀÚ¸®¸¸ ¹Ù²î°í ³ª¸ÓÁö´Â ¿À¸§Â÷¼ø Á¤·Ä
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

int find_starting_point_shake(NODE * n_Arr, int node_Total) // 1234 -> 2134 -> 3214 -> 4321 ÇüÅÂ·Î ¹Ù²ñ
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
	iter = v.begin();  // º¤ÅÍ ¹Ýº¹ÀÚ ½ÃÀÛÁöÁ¡
					   // ¾ÕÀÚ¸®¸¸ ¹Ù²î°í ³ª¸ÓÁö´Â ¿À¸§Â÷¼ø Á¤·Ä
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
	}
	printf("Best Start point is : ");
	print_vector(min_v);
	printf("\nMin dist is: %d\n", min);
	return 0;
}

void bubble_sort(int* list, int n) {
	int i, j, temp;
	int c = 0;
	int prev = -1;
	int now;
	for (i = n - 1; i > 0; i--) {
		// 0 ~ (i-1)까지 반복
		for (j = 0; j < i; j++) {
			// j번째와 j+1번째의 요소가 크기 순이 아니면 교환
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
	printf("\n오류발생횟수%d", c);
}

double length(int x1, int y1, int x2, int y2) // 두 노드의 거리계산 
{
	double l;
	int a; int b;

	a = x1 - x2;    // X좌표 거리
	b = y1 - y2;     // Y좌표 거리

	l = sqrt((a * a) + (b * b));    // (a * a) + (b * b)의 제곱근을 구함

	return l;
}

double cost_Cal(NODE * n_Arr, int* route, int node_Total) // 루트 총 비용 개산
{
	double cost = 0;
	int i;

	for (i = 0; i < (node_Total - 1); i++)
	{
		cost = cost + length(n_Arr[route[i]].location_X, n_Arr[route[i]].location_Y, n_Arr[route[i + 1]].location_X, n_Arr[route[i + 1]].location_Y);
	}

	return cost;
}

double cost_Cal2(NODE * n_Arr, int* route, int node_Total, int z, int k) // 루트 총 비용 개산
{
	double cost = 0;
	int i;

	if (z == 0 && k != node_Total - 1) // 대형데이터 일땐 뒤 조건문 빼줘도 됨?
	{
		for (i = z; i < (k + 1); i++)
		{
			cost = cost + length(n_Arr[route[i]].location_X, n_Arr[route[i]].location_Y, n_Arr[route[i + 1]].location_X, n_Arr[route[i + 1]].location_Y);
		}
	}
	else if (k == node_Total - 1 && z != 0)  // 대형데이터 일땐 뒤 조건문 빼줘도 됨?
	{
		for (i = z - 1; i < k; i++)
		{
			cost = cost + length(n_Arr[route[i]].location_X, n_Arr[route[i]].location_Y, n_Arr[route[i + 1]].location_X, n_Arr[route[i + 1]].location_Y);
		}
	}
	else if (k == node_Total - 1 && z == 0) // 대형 데이터 에선 뺴줘도 됨
	{
		for (i = z; i < k; i++)
		{
			cost = cost + length(n_Arr[route[i]].location_X, n_Arr[route[i]].location_Y, n_Arr[route[i + 1]].location_X, n_Arr[route[i + 1]].location_Y);
		}
	}
	else
	{
		for (i = z - 1; i < k + 1; i++)
		{
			cost = cost + length(n_Arr[route[i]].location_X, n_Arr[route[i]].location_Y, n_Arr[route[i + 1]].location_X, n_Arr[route[i + 1]].location_Y);
		}
	}

	return cost;
}

void TSP_Greedy(NODE * n_Arr, int node_Total, int* route) // 초기 루트 bv greedy
{
	int i = 0;
	int j = 0;
	int z = 0;
	int now_Node = 0;//첫번째 노드 출발
	int next_Node = 0;
	double cost = 0;


	n_Arr[0].visit = 1; // 출발 노드 방문


	while (i < (node_Total - 1))
	{
		double min_Dis = 99999;
		double dis_Tn = 0; //두점사이의 거리
		double a = 0;
		double b = 0;

		for (j = 0; j < node_Total; j++)
		{

			if (now_Node != j && n_Arr[j].visit == 0)
			{
				a = 0;
				b = 0;

				a = n_Arr[now_Node].location_X - n_Arr[j].location_X;    // X좌표 거리
				b = n_Arr[now_Node].location_Y - n_Arr[j].location_Y;     // Y좌표 거리

				dis_Tn = sqrt((a * a) + (b * b));    // (a * a) + (b * b)의 제곱근을 구함

				if (dis_Tn < min_Dis)
				{
					min_Dis = dis_Tn;
					next_Node = j;
				}
			}

		}
		route[i] = now_Node;
		n_Arr[now_Node].visit = 1;
		now_Node = next_Node;
		i++;
	}
	route[i] = now_Node;
	n_Arr[now_Node].visit = 1;

	while (z < node_Total)
	{
		if (n_Arr[z].visit == 0)
			printf("\n전체방문실패\n");
		z++;
	}

}

double TSP_Greedy_has_starting(NODE * n_Arr, int node_Total, int* route, int start_index) // ÃÊ±â ·çÆ® bv greedy
{
	int i = 0;
	int j = 0;
	int z = 0;
	int now_Node = 0;//Ã¹¹øÂ° ³ëµå Ãâ¹ß
	int next_Node = 0;
	double cost = 0;

	now_Node = start_index;
	n_Arr[start_index].visit = 1; // Ãâ¹ß ³ëµå ¹æ¹®




	while (i < (node_Total - 1))
	{
		double min_Dis = 99999;
		double dis_Tn = 0; //µÎÁ¡»çÀÌÀÇ °Å¸®
		double a = 0;
		double b = 0;

		for (j = 0; j < node_Total; j++)
		{

			if (now_Node != j && n_Arr[j].visit == 0)
			{
				/*
				a = 0;
				b = 0;
				a = n_Arr[now_Node].location_X - n_Arr[j].location_X;    // XÁÂÇ¥ °Å¸®
				b = n_Arr[now_Node].location_Y - n_Arr[j].location_Y;     // YÁÂÇ¥ °Å¸®
				dis_Tn = sqrt((a * a) + (b * b));    // (a * a) + (b * b)ÀÇ Á¦°ö±ÙÀ» ±¸ÇÔ
				*/
				//dis_Tn = distance_all[now_Node][j];

				if (distance_all[now_Node][j] < min_Dis)
				{
					min_Dis = distance_all[now_Node][j];
					next_Node = j;
				}
			}

		}
		route[i] = now_Node;
		n_Arr[now_Node].visit = 1;
		now_Node = next_Node;
		cost += min_Dis;
		i++;
	}
	route[i] = now_Node;
	n_Arr[now_Node].visit = 1;

	/*
	while (z < node_Total)
	{
	if (n_Arr[z].visit == 0)
	printf("\nÀüÃ¼¹æ¹®½ÇÆÐ\n");
	z++;
	}
	*/

	return cost;

}

vector<vector<int>> find_good_greedy(vector<NODE> node_vector, int node_Total, int* route, vector<NODE> vec_node)
{
	int i = 0;
	vector<int> vec_index;
	vector<int> vec_cost;
	int min_distance = 1000000;

	vector<vector<int>> save_route_vec;
	vector<NODE> tmp_new_Arr = vec_node;
	NODE* new_Arr;
	new_Arr = &tmp_new_Arr[0];
	double res = 0;
	while (res < TIME_LIMIT)
	{

		clock_t end = clock();
		res = (double)(end - start) / CLOCKS_PER_SEC;


		//printf("%d\n", i);
		vector<NODE> vec_tmp = vec_node;
		NODE* n_Arr = &vec_tmp[0];
		int start_index = rand() % node_Total;
		//vector<int> cost_vec2(route, route + node_Total);
		double cost = TSP_Greedy_has_starting(n_Arr, node_Total, route, start_index);

		vector<int> cost_vec(route, route + node_Total);


		int new_cost = cost;
		//int new_cost = calc_dist_total(new_Arr, cost_vec);
		if (min_distance > new_cost)
		{
			min_distance = new_cost;
			//vec_index.insert(vec_index.begin(), start_index);
			//vec_cost.insert(vec_cost.begin(), new_cost);
			save_route_vec.insert(save_route_vec.begin(), cost_vec);
		}
		i++;
	}
	//printf("greedy 재시작 횟수 : %d\n", i);
	return save_route_vec;
}

void swap(int* temp, int i, int k)
{
	for (int a = i; a < k + 1; a++)
	{
		size1[a - i] = temp[a];
	}

	for (int c = i; c < k + 1; c++)
	{
		temp[c] = size1[k - c];
	}
}

void r_swap(int* temp, int i, int k)
{
	for (int a = i; a < k + 1; a++)
	{
		temp[a] = size1[a - i];
	}
}

void TSP_2Opt(NODE * n_Arr, int node_Total, int* route) // 2옵 알고리즘
{
	int i = 1, k, z;
	double now_cost = 0, new_cost = 0, cost1 = 0, cost2 = 0;
	double res, time = 0.0;
	clock_t end;





	int improve = 0;

	z = node_Total;
	now_cost = cost_Cal(n_Arr, route, node_Total); // 기존거랑 변경
	while (time < 60.0 && improve == 0) //수정
	{

		improve = 1;
		for (i = 1; time < 60.0 && i < z - 1; i++)
		{
			for (k = i + 1; time < 60.0 && k < z; k++)
			{
				if (k == z - 1)
				{
					cost1 = length(n_Arr[route[i - 1]].location_X, n_Arr[route[i - 1]].location_Y, n_Arr[route[i]].location_X, n_Arr[route[i]].location_Y);
					cost2 = length(n_Arr[route[i - 1]].location_X, n_Arr[route[i - 1]].location_Y, n_Arr[route[k]].location_X, n_Arr[route[k]].location_Y);
					new_cost = now_cost - cost1 + cost2;
				}
				else
				{
					cost1 = length(n_Arr[route[i - 1]].location_X, n_Arr[route[i - 1]].location_Y, n_Arr[route[i]].location_X, n_Arr[route[i]].location_Y)
						+ length(n_Arr[route[k]].location_X, n_Arr[route[k]].location_Y, n_Arr[route[k + 1]].location_X, n_Arr[route[k + 1]].location_Y);
					cost2 = length(n_Arr[route[i - 1]].location_X, n_Arr[route[i - 1]].location_Y, n_Arr[route[k]].location_X, n_Arr[route[k]].location_Y)
						+ length(n_Arr[route[i]].location_X, n_Arr[route[i]].location_Y, n_Arr[route[k + 1]].location_X, n_Arr[route[k + 1]].location_Y);
					new_cost = now_cost - cost1 + cost2;
				}

				if (new_cost < now_cost)
				{
					swap(route, i, k);  // 기존거랑 
					now_cost = new_cost;
					improve = 0;
				}
				end = clock();
				time = (double)(end - start) / CLOCKS_PER_SEC;
			}
		}
	}
	end = clock();
	res = (double)(end - start) / CLOCKS_PER_SEC;

	final_cost = now_cost;

	printf("\n소요된 시간 : %.3f \n", res);
	printf("\n최종비용: %f", final_cost);
}

int check_route(vector<int> route, int node_Total)
{
	int * tmp_route = (int*)malloc(sizeof(int) * node_Total);

	for (int i = 0; i < node_Total; i++)
	{
		tmp_route[i] = 0;
	}

	for (int i = 0; i < node_Total; i++)
	{
		int index = route[i];
		if (tmp_route[index] != 0)
		{
			printf("검사실패!!!중복입니다\n");
			return -1;
		}
		tmp_route[index] = 1;
	}

	for (int i = 0; i < node_Total; i++)
	{
		if (tmp_route[i] == 0)
		{
			printf("검사실패!!중복입니다\n");
			return -1;
		}

	}
	return 0;
}

int main() // 현재 노드의 개수는 코드에 입력, 추후 수정 필요
{
	char tmp;
	int node_Total = 1;
	int all_Node = 0;
	float res;
	clock_t start, end;

	srand((unsigned int)time(NULL));

	FILE* pFile = NULL;
	pFile = fopen(FILE_NAME, "r");


	if (pFile == NULL)
	{
		exit(0);
	}

	while (fscanf(pFile, "%c", &tmp) != EOF)  // 노드 개수 세기
	{
		if (tmp == '\n')
			node_Total++;
	}

	node_Total = node_Total - 10;
	// printf("노드의 개수=%d\n\n", node_Total);

	fseek(pFile, 0, SEEK_SET);


	if (pFile != NULL)
	{
		NODE* n_Arr = (NODE*)malloc(sizeof(NODE) * node_Total);
		int* route = (int*)malloc(sizeof(int) * node_Total);

		char strTemp[255];
		char* pStr;
		int i = 0;

		while (i < 8) // 앞에 텍스트들 읽어들이기
		{
			i++;

			pStr = fgets(strTemp, sizeof(strTemp), pFile);
			printf("%s", pStr);
		}

		while (i < (node_Total + 8)) // 노드 좌표 읽어들여서 구조체에 저장
		{
			char* ptr = NULL;
			int node_Count = 0;

			node_Count = i - 7; // 노드

			route[node_Count - 1] = node_Count - 1; //루트를 노드순으로 초기화

			n_Arr[node_Count - 1].test = fgets(strTemp, sizeof(strTemp), pFile);

			ptr = strtok(n_Arr[node_Count - 1].test, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
			n_Arr[node_Count - 1].node_Num = atoi(ptr);

			ptr = strtok(NULL, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
			n_Arr[node_Count - 1].location_X = atoi(ptr);

			ptr = strtok(NULL, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
			n_Arr[node_Count - 1].location_Y = atoi(ptr);

			n_Arr[node_Count - 1].visit = 0; // 방문여부 초기화

			i++;
		}

		fclose(pFile);

		for (int i = 0; i < node_Total; i++) {
			for (int j = 0; j < node_Total; j++) {
				distance_all[i][j] = calc_dist_node(n_Arr[i], n_Arr[j]);
			}
		}

		start = clock();

		vector<NODE> node_vec(n_Arr, n_Arr + node_Total);
		vector<int> route_vec(route, route + node_Total);

		//TSP_Greedy(n_Arr, node_Total, route);
		vector<int> save_ori_route(route_vec);

		route = &save_ori_route[0];

		vector<NODE> tmp_n_Arr = node_vec;
		n_Arr = &tmp_n_Arr[0];

		vector<vector<int>> route_list_vec(find_good_greedy(tmp_n_Arr, node_Total, route, node_vec));
		vector<int> tmp_v(route_list_vec[0]);
		route = &route_list_vec[0][0];

		int before_cost = calc_dist_total(n_Arr, tmp_v);
		printf("\ngreedy cost : %d\n", before_cost);
		//printf("\nafter 2opt\n");
		//TSP_2Opt(n_Arr, node_Total, route);

		end = clock();

		res = (float)(end - start) / CLOCKS_PER_SEC;

		string filePath = "greedy_path.txt";  //결과 루트 파일에 저장
		ofstream writeFile(filePath.data());
		i = 0;
		while (i < node_Total)
		{
			writeFile << tmp_v[i];
			writeFile << '\n';
			i++;
		}
		writeFile.close();
		check_route(tmp_v, node_Total);

		/*
		i = 0;
		while (i < node_Total)
		{
		printf("%d\n", route[i]); //루트 확인
		i++;
		}
		*/

		//bubble_sort(route, node_Total); // 오류검사

		printf("greedy time : %.3fs \n", res);
		//printf("\n최종비용: %d", final_cost);
		//printf("\n프로그램 정상종료!");
	}
	system("pause");
}