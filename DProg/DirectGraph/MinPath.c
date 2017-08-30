#include <stdio.h>
#include <stdlib.h>

#define NUM 10
#define LEN 255
#define MAX 10000

typedef enum { true, false } Bool;

void set_label(char label[]);
void set_relation(int rel[][NUM], char t[]);
void graph_output(int rel[][NUM], char label[], int n);
void arr_copy(const int arr1[][NUM], int arr2[][NUM], int n);
Bool arr_match(const int arr1[][NUM], const int arr2[][NUM], int n);
void relation_own(int relation[][NUM], int n);
void floyd(const int rel[][NUM], int arr0[][NUM], int n);

int calcnum = 0;

int main(void) {
	char label[NUM];
	char tmp[LEN];
	int rel[NUM][NUM] = { {0} };
	int table[NUM][NUM];
	int n;
	int k;
	
	fgets(tmp, sizeof(tmp), stdin);
	sscanf(tmp, "%d", &n);
	set_label(label);
	
	for ( k = 0; k < n; k++ ) {
		if ( fgets(tmp, sizeof(tmp), stdin) == NULL ) { puts("入力エラー"); return 0; }
		set_relation(rel, tmp);
	}
	
	graph_output(rel, label, n);
	
	puts("==========================");
	
	relation_own(rel, n);
	floyd(rel, table, n);
	
	graph_output(table, label, n);
	printf("計算回数 : %d\n", calcnum);
	
	return 0;
}


void set_label(char label[]) {
	int k;
	
	for ( k = 0; k < NUM; k++ ) {
		label[k] = 'A' + k;
	}
}


void set_relation(int rel[][NUM], char t[]) {
	int  p = 0;
	int label;
	
	while ( t[p] == ' ' ) { p++; }
	if ( t[p] >= 'A' && t[p] < 'A' + NUM ) {
		label = t[p++] - 'A';
	}
	
	while ( t[p] != '\0' ) {
		calcnum++;
		while ( t[p] == ' ' ) { p++; }
		if ( t[p] >= 'A' && t[p] < 'A' + NUM ) {
			rel[label][t[p++] - 'A'] = 1;
		}
		while ( t[p] == ' ' ) { p++; }
		if ( t[p] == '\n' ) { break; }
	}
}


void graph_output(int rel[][NUM], char label[], int n) {
	int k1, k2;
	
	printf("  ");
	for ( k1 = 0; k1 < n; k1++ ) {
		printf("%c ", label[k1]);
	}
	puts("");
	
	for ( k1 = 0; k1 < n; k1++ ) {
		printf("%c ", label[k1]);
		for ( k2 = 0; k2 < n; k2++ ) {
			printf("%d ", rel[k1][k2]);
		} 
		puts("");
	}	
}

void arr_copy(const int arr1[][NUM], int arr2[][NUM], int n) {
	int k1, k2;

	for ( k1 = 0; k1 < n; k1++ ) {
		for ( k2 = 0; k2 < n; k2++ ) {
			arr2[k1][k2] = arr1[k1][k2];
		}
	}
}

Bool arr_match(const int arr1[][NUM], const int arr2[][NUM], int n) {
	int k1, k2;
	
	for ( k1 = 0; k1 < n; k1++ ) {
		for ( k2 = 0; k2 < n; k2++ ) {
			if ( arr1[k1][k2] != arr2[k1][k2] ) { return false; }
		}
	}
	
	return true;
}

void relation_own(int relation[][NUM], int n) {
	int i;

	for ( i = 0; i < n; i++ ) {
		calcnum++;
		relation[i][i] = 1;
	}
}

void floyd(const int rel[][NUM], int arr0[][NUM], int n) {
	int arr1[NUM][NUM];
	int i, j, k;
	int tmp;
	
	for ( i = 0; i < n; i++ ) {
		for ( j = 0; j < n; j++ ) {
			calcnum++;
			arr0[i][j] = rel[i][j] == 0 ? MAX : rel[i][j];
		}
	}
	
	for ( i = 0; i < n; i++ ) {
		for ( j = 0; j < n; j++ ) {
			for ( k = 0; k < n; k++ ) {
				calcnum++;
				tmp = arr0[i][k] + arr0[k][j];
				if ( arr0[i][j] > tmp ) { arr0[i][j] = tmp; }
			}
		}
	}
	
	for ( i = 0; i < n; i++ ) {
		for ( j = 0; j < n; j++ ) {
			calcnum++;
			arr0[i][j] = arr0[i][j] == MAX ? 0 : arr0[i][j];
		}
	}
}
