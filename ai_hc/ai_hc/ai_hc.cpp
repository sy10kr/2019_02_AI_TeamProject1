// 2-opt 1회적용, 초기 경로는 node순(랜덤 노드로 수정 고려), 방문노드 여부 체크도 아직안함
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>      // malloc, free 함수가 선언된 헤더 파일
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
#define FILE_NAME "xmc10150.txt"

using namespace std;


double final_cost = 0;
clock_t start;
int size1[15020];
int size2[15020];

double distance_all[15000][15000];


int min_x, min_y;
int max_x = 0, max_y = 0;

int points[3];
int lev_cnt[LEV_STEPS + 5];
int cur_NodeNum;
int position;


typedef struct   // 연결 리스트의 노드 구조체
{
	int node_Num;          // 노드의 넘버
	int location_X;        // 노드의 X축 좌표
	int location_Y;        // 노드의 Y축 좌표
	int visit;             // 해당노드 방문 여부
	char* test; //구조체 테스트 
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

double TSP_Greedy(NODE *n_Arr, int node_All, int node_Total, int s_Node, int curLev, int* route)
{
	int i = 0;
	int j = 0;
	int z = 0;
	int now_Node = s_Node;
	int next_Node = 0;
	double cost = 0;
	int lev = curLev;

	n_Arr[s_Node].visit = 1; // 출발 노드 지정
							 //printf("%d레벨 탐색\n", lev);

	while (i < node_Total - 1)
	{
		double min_Dis = 99999;
		double dis_Tn = 0; //두점사이의 거리
		double a = 0;
		double b = 0;

		for (j = 0; j < node_All; j++)
		{

			if (now_Node != j && n_Arr[j].visit == 0 && n_Arr[j].level == lev)
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
		route[position] = now_Node;
		// printf("%d\n", route[position]);
		position++;
		now_Node = next_Node;
		n_Arr[now_Node].visit++;
		//printf("%d번째 --> %d\t", i+1, next_Node);
		cost = cost + min_Dis;
		i++;
	}
	route[position] = now_Node;

	while (z < node_All)
	{
		if (n_Arr[z].level == lev) {
			if (n_Arr[z].visit != 1)
				printf("\n%d레벨 전체방문실패\n", lev);
		}
		z++;
	}

	//printf("%d레벨 탐색 비용:%lld\n\n", lev, cost);
	cur_NodeNum = now_Node;
	return cost;
}


void route_prov(int* route, int node_total)
{
	double all_dist = 0;
	for (int i = 0; i < node_total - 1; i++)
	{
		all_dist = all_dist + distance_all[route[i]][route[i + 1]];
	}
	printf("\n루트비용검증 : %f \n", all_dist);
}

double TSP_Greedy_has_starting(NODE * n_Arr, int node_Total, int* route, int start_index) // ÃÊ±â ·çÆ® bv greedy
{
	int i = 0;
	int j = 0;
	int z = 0;
	int now_Node = 0;//Ã¹¹øÂ° ³ëµå Ãâ¹ß
	int next_Node = 0;
	double cost = 0;

	//start_index = 0;
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



// 최좌상단, 최우하단 꼭지점과 가장 가까운 노드 탐색
void findPoints(NODE* n_Arr, int node_Total, int min_x, int min_y, int max_x, int max_y)
{
	int i = 0;
	int distance;
	int mindis = 9999999, maxdis = 0;
	while (i < node_Total) {
		distance = sqrt(((n_Arr[i].location_X - min_x) * (n_Arr[i].location_X - min_x)) + ((n_Arr[i].location_Y - min_y) * (n_Arr[i].location_Y - min_y)));
		if (distance < mindis) {
			mindis = distance;
			points[1] = i;
		}
		i++;
	}
	i = 0;
	mindis = 999999;
	while (i < node_Total) {
		distance = sqrt(((n_Arr[i].location_X - max_x) * (n_Arr[i].location_X - max_x)) + ((n_Arr[i].location_Y - max_y) * (n_Arr[i].location_Y - max_y)));
		if (distance < mindis) {
			mindis = distance;
			points[2] = i;
		}
		i++;
	}


	//printf("\n%d %d %d\n%d %d %d\n\n", n_Arr[points[1]].node_Num, n_Arr[points[1]].location_X, n_Arr[points[1]].location_Y, n_Arr[points[2]].node_Num, n_Arr[points[2]].location_X, n_Arr[points[2]].location_Y);
}

double TSP_Greedy_LEVELING(NODE* n_Arr, int node_Total, int* route)
{
	int i;
	int left_top = points[1];
	int left_topx = n_Arr[left_top].location_X; int left_topy = n_Arr[left_top].location_Y;
	int right_bottom = points[2];
	int right_bottomx = n_Arr[right_bottom].location_X; int right_bottomy = n_Arr[right_bottom].location_Y;
	int difx = (left_topx - right_bottomx) * (left_topx - right_bottomx);
	int dify = (left_topy - right_bottomy) * (left_topy - right_bottomy);
	double main_dis = sqrt(difx + dify);
	double lev_step = main_dis / LEV_STEPS, total_dis = 0;
	double distance;
	int lev = 1;
	i = 0;
	for (i = 0; i < LEV_STEPS + 5; i++) lev_cnt[i] = 0;
	total_dis = total_dis + lev_step;
	while (total_dis < main_dis) {
		i = 0;
		while (i < node_Total) {
			if (n_Arr[i].level == 0) {
				difx = n_Arr[i].location_X - n_Arr[left_top].location_X;
				dify = n_Arr[i].location_Y - n_Arr[left_top].location_Y;
				distance = sqrt((difx * difx) + ((dify) * (dify)));
				if (distance <= total_dis) {
					n_Arr[i].level = lev;
					lev_cnt[lev]++;
				}
			}
			i++;
		}
		total_dis = total_dis + lev_step;
		lev++;
	}
	i = 0;
	/*
	while (i < node_Total) {
	if (n_Arr[i].level == 0) {
	difx = n_Arr[i].location_X - n_Arr[left_top].location_X;
	dify = n_Arr[i].location_Y - n_Arr[left_top].location_Y;
	distance = sqrt((difx * difx) + ((dify) * (dify)));
	if (distance <= total_dis) {
	n_Arr[i].level = lev;
	lev_cnt[lev]++;
	}
	}
	i++;
	}*/
	while (i < node_Total) {
		if (n_Arr[i].level == 0) {
			n_Arr[i].level = lev;
			lev_cnt[lev]++;
		}
		i++;
	}
	/*//레벨링 결과 출력
	i = 0;
	printf("%f %f\n", main_dis, lev_step);
	while (i < node_Total) {
	printf("%d %d %d %d\n", n_Arr[i].node_Num, n_Arr[i].location_X, n_Arr[i].location_Y, n_Arr[i].level);
	i++;
	}*/

	//Greedy 경로탐색
	i = 0;
	long long cost_fin = 0;
	int start_Node = left_top;
	position = 0;
	for (i = 1; i <= lev; i++) {
		if (i == 1) {
			cost_fin = cost_fin + TSP_Greedy(n_Arr, node_Total, lev_cnt[i], start_Node, i, route);
			start_Node = cur_NodeNum;
		}
		else {
			cost_fin = cost_fin + TSP_Greedy(n_Arr, node_Total, lev_cnt[i] + 1, start_Node, i, route);
			start_Node = cur_NodeNum;
		}
	}
	printf("\n------------------------------------------------\n");
	printf("Total:%d routes as %d steps\n", position + 1, LEV_STEPS);
	printf("최종 비용: %lld\n", cost_fin);
	return cost_fin;
}





vector<vector<int>> find_good_greedy(vector<NODE> node_vector, int node_Total, int* route, vector<NODE> vec_node)
{
	int i = 0;
	vector<int> vec_index;
	vector<int> vec_cost;
	double min_distance = 1000000;

	vector<vector<int>> save_route_vec;
	vector<NODE> tmp_new_Arr = vec_node;
	NODE* new_Arr;
	new_Arr = &tmp_new_Arr[0];



	while (i < 6)
	{

		//printf("%d\n", i);
		vector<NODE> vec_tmp = vec_node;
		NODE* n_Arr = &vec_tmp[0];
		int start_index = rand() % node_Total;
		double cost = 0;
		//vector<int> cost_vec2(route, route + node_Total);

		/*
		if (i == 0)
		{
		//꼭지점 노드와 가장 가까운 노드 탐색
		findPoints(n_Arr, node_Total, min_x, min_y, max_x, max_y);

		// 각 노드에 대한 레벨링 및 Greedy 탐색 시작
		cost = TSP_Greedy_LEVELING(n_Arr, node_Total, route);
		}
		else
		*/
		cost = TSP_Greedy_has_starting(n_Arr, node_Total, route, start_index);

		vector<int> cost_vec(route, route + node_Total);


		double new_cost = cost;
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

int check_route(int* route, int node_Total)
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



void TSP_2Opt(NODE * n_Arr, int node_Total, int* route) // 2옵 알고리즘
{
	int i = 1, k, z;
	double now_cost = 0, new_cost = 0, cost1 = 0, cost2 = 0;
	double res, time = 0.0;
	clock_t end;

	int improve = 0;

	z = node_Total;
	now_cost = cost_Cal(n_Arr, route, node_Total); // 기존거랑 변경
	while (time < TIME_LIMIT && improve == 0) //수정
	{

		improve = 1;
		for (i = 0; time < TIME_LIMIT && i < z - 1; i++)
		{
			for (k = i + 1; time < TIME_LIMIT && k < z; k++)
			{
				if (i != 0 && k != z - 1)
					new_cost = now_cost - (distance_all[route[i - 1]][route[i]] + distance_all[route[k]][route[k + 1]]) + (distance_all[route[i - 1]][route[k]] + distance_all[route[i]][route[k + 1]]);
				else if (i == 0 && k != z - 1)
					new_cost = now_cost - (distance_all[route[k]][route[k + 1]]) + (distance_all[route[i]][route[k + 1]]);
				else if (i != 0 && k == z - 1)
					new_cost = now_cost - (distance_all[route[i - 1]][route[i]]) + (distance_all[route[i - 1]][route[k]]);

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

	//printf("\n소요된 시간 : %.3f \n", res);
	//printf("\n최종비용: %f", final_cost);
}

int main() // 현재 노드의 개수는 코드에 입력, 추후 수정 필요
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

	while (fscanf(pFile, "%c", &tmp) != EOF)  // 노드 개수 세기
	{
		if (tmp == '\n')
			node_Total++;
	}

	node_Total = node_Total - 10;
	//printf("노드의 개수=%d\n\n", node_Total);

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
			//printf("%s", pStr);
		}

		while (i < (node_Total + 8))
		{
			char *ptr = NULL;
			int node_Count = 0;
			int ptr_num = 0;

			node_Count = i - 7;

			route[node_Count - 1] = node_Count - 1; // 루트를 노드순으로 초기화

			n_Arr[node_Count - 1].test = fgets(strTemp, sizeof(strTemp), pFile);

			ptr = strtok(n_Arr[node_Count - 1].test, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
			n_Arr[node_Count - 1].node_Num = atoi(ptr);

			ptr = strtok(NULL, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
			ptr_num = atoi(ptr);
			n_Arr[node_Count - 1].location_X = ptr_num;
			if (i == 8) min_x = ptr_num;
			else if (min_x > ptr_num) min_x = ptr_num;
			if (max_x < ptr_num) max_x = ptr_num;

			ptr = strtok(NULL, " ");      // " " 공백 문자를 기준으로 문자열을 자름, 포인터 반환
			ptr_num = atoi(ptr);
			n_Arr[node_Count - 1].location_Y = atoi(ptr);
			if (i == 8) min_y = ptr_num;
			else if (min_y > ptr_num) min_y = ptr_num;
			if (max_y < ptr_num) max_y = ptr_num;

			n_Arr[node_Count - 1].visit = 0;
			n_Arr[node_Count - 1].level = 0;

			//printf("노드%d번: %d %d %d\n", node_Count, n_Arr[node_Count - 1].node_Num, n_Arr[node_Count - 1].location_X, n_Arr[node_Count - 1].location_Y);
			i++;
		}

		fclose(pFile);

		for (int i = 0; i < node_Total; i++) {  //각 노드간 거리 다 계산해놓음
			for (int j = 0; j < node_Total; j++) {
				distance_all[i][j] = calc_dist_node(n_Arr[i], n_Arr[j]);
			}
		}

		start = clock();
		//start를 어디서 해야할 까?

		vector<NODE> node_vec(n_Arr, n_Arr + node_Total);
		vector<int> route_vec(route, route + node_Total);
		vector<int> save_ori_route(route_vec);

		route = &save_ori_route[0];
		vector<NODE> tmp_n_Arr = node_vec;
		n_Arr = &tmp_n_Arr[0];



		vector<vector<int>> route_list_vec(find_good_greedy(tmp_n_Arr, node_Total, route, node_vec));

		double res = 0;
		vector <int> save_route_vec;

		i = 0;
		double min_cost = 10000000;

		vector<int> tmp_save_vec;
		vector<int> tmp_vv;

		while (res < TIME_LIMIT)
		{
			end = clock();
			res = (float)(end - start) / CLOCKS_PER_SEC;

			int* tmp_route;

			if (route_list_vec.size() > i)
			{
				vector<int> tmp_v(route_list_vec[0]);
				tmp_save_vec = tmp_v;
				route = &route_list_vec[i][0];

				tmp_n_Arr = node_vec;
				n_Arr = &tmp_n_Arr[0];
				int before_cost = calc_dist_total(n_Arr, tmp_v);
				//printf("\Starting cost(Greedy) : %d\n", before_cost);
			}
			else
			{
				//printf("Random\n");
				tmp_vv = route_vec;
				tmp_n_Arr = node_vec;
				route = &tmp_vv[0];
				n_Arr = &tmp_n_Arr[0];
				TSP_Greedy_has_starting(n_Arr, node_Total, route, rand() % node_Total);
				int before_cost = calc_dist_total(n_Arr, tmp_vv);
				//printf("\Starting cost(Greedy) : %d\n", before_cost);
			}
			i++;


			vector<int> cost_vec(route, route + node_Total);
			vector<NODE> tmp_new_Arr = node_vec;
			NODE* new_Arr;
			new_Arr = &tmp_new_Arr[0];

			double new_cost = calc_dist_total(new_Arr, cost_vec);


			printf("\nDoing 2opt..\n");
			TSP_2Opt(n_Arr, node_Total, route);

			end = clock();
			res = (double)(end - start) / CLOCKS_PER_SEC;



			printf("\n unit time : %.3f ", res);
			printf("\n unit cost %f", final_cost);
			//printf("\n new cost %f\n", new_cost);

			if (final_cost < min_cost)
			{
				min_cost = final_cost;
				vector<int> tmp_vec(route, route + node_Total);
				save_route_vec = tmp_vec;
			}
			final_cost = 0;

		}

		int * final_route = (int*)malloc(sizeof(int) * node_Total);
		final_route = &save_route_vec[0];

		end = clock();
		res = (double)(end - start) / CLOCKS_PER_SEC;

		check_route(final_route, node_Total);
		printf("\n\ntotal time : %.3f ", res);
		printf("\nmin cost: %f", min_cost);
		printf("\nEND!");



		string filePath = "2opt_path.txt";  //결과 루트 파일에 저장
		ofstream writeFile(filePath.data());
		i = 0;
		while (i < node_Total)
		{
			writeFile << final_route[i];
			writeFile << '\n';
			i++;
		}
		writeFile.close();
		route_prov(final_route, node_Total);
		printf("\n프로그램 정상종료!");
		//bubble_sort(route, node_Total); // 오류검사

		system("pause");
	}

	return 0;
}