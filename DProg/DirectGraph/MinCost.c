#include <stdio.h>

#define NUM 10
#define MAX 10000
#define NOT -1
#define START 0
#define OPEN 1
#define CLOSE 2

typedef enum { false, true } Bool;

typedef struct node {
	char label;
	char label_from;
	int cost;
	int open;
} Node;

int cost_arr[NUM][NUM];
Node label0_arr[NUM];
int  calcnum = 0;

void arr_input(int arr[][NUM], int n);
void arr_output(int arr[][NUM], int n);
void arr_copy(const int arr1[][NUM], int arr2[][NUM], int n);
Bool arr_match(const int arr1[][NUM], const int arr2[][NUM], int n);
int get_cost(char str1, char str2);
void init(int n, char start);
void dijkstra(char start, int n, char end);
Bool exist_open(int n);
int get_ind(char ch);
int min_open(int n);
void show_path(Node node, char start);

int main(void) {
	int n;
	char start, end;
	int i;
	
	scanf("%d", &n);
	arr_input(cost_arr, n);
	scanf(" %c %c", &start, &end);
	
	dijkstra(start, n, end);
	
	puts("");
	
	printf("計算回数 : %d\n", calcnum);
	
	return 0;
}

void arr_input(int arr[][NUM], int n) {
	int k1, k2;
	
	for ( k1= 0; k1 < n; k1++ ) {
		for ( k2 = 0; k2 < n; k2++ ) {
			scanf("%d", &arr[k1][k2]);
		}
	}
}

Bool arr_match(const int arr1[][NUM], const int arr2[][NUM], int n) {
	int k1, k2;
	
	for ( k1 = 0; k1 < n; k1++ ) {
		for ( k2 = 0; k2 < n; k2++ ) {
			if ( arr1[k1][k2] != arr2[k1][k2] ) {
				return false;
			}
		}
	}
	
	return true;
}

void arr_copy(const int arr1[][NUM], int arr2[][NUM], int n) {
	int k1, k2;

	for ( k1 = 0; k1 < n; k1++ ) {
		for ( k2 = 0; k2 < n; k2++ ) {
			arr2[k1][k2] = arr1[k1][k2];
		}
	}
}


void arr_output(int arr[][NUM], int n) {
	int k1, k2;

 	for ( k1 = 0; k1 < n; k1++ ) {
		for ( k2 = 0; k2 < n; k2++ ) {
			printf("%d ", arr[k1][k2]);
		}
		puts("");
	}
	puts("");
}

int get_cost(char str1, char str2) {
	return cost_arr[str1-'A'][str2-'A'];
}

void init(int n, char start) {
	int k;
	
	for ( k = 0; k < n; k++ ) {
		label0_arr[k].label = 'A' + k;
		
		if ( label0_arr[k].label == start ) {
			label0_arr[k].cost = 0;
			label0_arr[k].label_from = START;
			label0_arr[k].open = OPEN;
		} else {
			label0_arr[k].cost = MAX;
			label0_arr[k].label_from = NOT;
			label0_arr[k].open = NOT;
		}
	}
}

void dijkstra(char start, int n, char end) {
	Node *node;
	int ind;
	int min, posmin;
	int k;
	int t;
	char ch = start;
	
	init(n, start);
	
	ind = get_ind(ch);
	node = &(label0_arr[ind]);
	node->open = OPEN;
	
	while ( 1 ) {
		min = MAX;
		posmin = -1;
		if ( exist_open(n) == false ) {
			puts("失敗です。"); return;
		}
		
		ind = min_open(n);
		node = &label0_arr[ind];
		node->open = CLOSE;
		
		if ( node->label == end ) {
			printf("%d\n", label0_arr[k-1].cost);
			show_path(*node, start);
			return;
		}
		
		for ( k = 0; k < n; k++ ) {
			calcnum++;
			if ( cost_arr[ind][k] != 0 ) {
				if ( label0_arr[k].open == -1 ) {
					label0_arr[k].open = OPEN;
					label0_arr[k].cost = node->cost + cost_arr[ind][k];
					label0_arr[k].label_from = node->label;
				} else {
					t = node->cost + cost_arr[ind][k];
					if ( t < label0_arr[k].cost ) {
						label0_arr[k].cost = t;
						label0_arr[k].label_from = node->label;
					}
				}
				if ( min > label0_arr[k].cost ) {
					min = label0_arr[k].cost;
					posmin = k;
				}
			}
		}
	}
}

Bool exist_open(int n) {
	int k;
	
	for ( k = 0; k < n; k++ ) {
		if ( label0_arr[k].open == OPEN ) {
			return true;
		}
	}
	
	return false;
}

int get_ind(char ch) {
	return ch - 'A';
}

int min_open(int n) {
	int k;
	int min = MAX, posmin = -1;
	
	for ( k = 0; k < n; k++ ) {
		if ( label0_arr[k].open != OPEN ) { continue; }
		if ( label0_arr[k].cost < min ) {
			min = label0_arr[k].cost;
			posmin = k;
		}
	}
	
	return posmin;
}

void show_path(Node node, char start) {
	int ind;
	
	if ( node.label == start ) {
		printf("%c ", node.label);
		return;
	}
	ind = get_ind(node.label_from);
	show_path(label0_arr[ind], start);
	printf("%c ", node.label);
}
