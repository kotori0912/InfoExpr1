
#include <stdio.h>
#include <string.h>

#define NUM 100
#define MAX 1000000

void create_wtb(int wtb[][NUM], int h, int w, const char *s1, const char *s2);
int min_search(int wtb[][NUM], int k1, int k2);
void arr_output(int arr[][NUM], int h, int w);

int roopnum = 0;    // 総反復量

int main(void) {
	char *str1, *str2;
	char s1[NUM], s2[NUM];
	int wtb[NUM][NUM];
	int h,w;
	
	//printf("レーベンシュタイン距離を求めます。\n");
	scanf("%s %s", s1, s2);
	
	str1 = s1;
	str2 = s2;
	
	h = strlen(str1)+1;
	w = strlen(str2)+1;
	
	create_wtb(wtb, h, w, str1, str2);
	//printf("%d\n", wtb[h-1][w-1]);
	//arr_output(wtb, h, w);
	
	printf("反復回数 : %d\n", roopnum);
	
	return 0;
} 

//=========================================================
// ワークテーブルを求める
//=========================================================

void create_wtb(int wtb[][NUM], int h, int w, const char *s1, const char *s2) {
	int k1, k2;
	
	for ( k1 = 0; k1 < h; k1++ ) {
		wtb[k1][0] = k1;
	}
	
	for ( k2 = 0; k2 < w; k2++ ) {
		wtb[0][k2] = k2;
	}
	
	for ( k1 = 1; k1 < h; k1++ ) {
		for ( k2 = 1; k2 < w; k2++ ) {
			wtb[k1][k2] = min_search(wtb, k1, k2);
			
			if ( s1[k1-1] == s2[k2-1] && wtb[k1][k2] == wtb[k1-1][k2-1] ) {    // 効率化
				continue;
			}
/*      
      if ( k2-k1 >= 4 || k2-k1 <= -4 ) {
        wtb[k1][k2]++;
        continue;
      }
*/    
			
			wtb[k1][k2]++;
			roopnum++;
		}
	}
}

//========================================================
// 最小距離を求める
//========================================================

int min_search(int wtb[][NUM], int k1, int k2) {
	int min = MAX;
	
	if ( wtb[k1-1][k2] < min ) { min = wtb[k1-1][k2]; }
	if ( wtb[k1-1][k2-1] < min ) { min = wtb[k1-1][k2-1]; }
	if ( wtb[k1][k2-1] < min ) { min = wtb[k1][k2-1]; }
	
	return min;
}

//=========================================================
// 配列の出力
//=========================================================

void arr_output(int arr[][NUM], int h, int w) {
	int k1, k2;
	
	for ( k1 = 0; k1 < h; k1++ ) {
		for ( k2 = 0; k2 < w; k2++ ) {
			printf("%2d ", arr[k1][k2]);
		}
		puts("");
	}
}
