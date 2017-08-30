#include <stdio.h>
#include <stdlib.h>

#define NUM 10
#define LEN 255

void set_label(char label[]);
void set_relation(int rel[][NUM], char t[]);
void graph_output(int rel[][NUM], char label[], int n);

int calcnum = 0;

int main(void) {
	char label[NUM];
	char tmp[LEN];
	int rel[NUM][NUM] = { {0} };
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
	printf("計算回数 : %d\n", calcnum);
	
	return 0;
}

//=================================================================
// ラベルのセット
//=================================================================

void set_label(char label[]) {
	int k;
	
	for ( k = 0; k < NUM; k++ ) {
		label[k] = 'A' + k;
	}
}

//=================================================================
// グラフをセットする
//=================================================================

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

//=================================================================
// グラフの出力
//=================================================================

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
