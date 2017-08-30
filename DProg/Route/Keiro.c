//========================================================
// 情報環境実験I 動的計画法
// 15T207 伊藤拓海
//========================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//==== 大域変数
#define NUM 100

int arr[NUM][NUM];
int ans[NUM][NUM];

//==== 関数定義
void input_arr(int x, int y);
int max_arr(int i, int st, int fin);
void rt_search(int x, int y);
void output_arr(int x, int y);
void rt_max(int x, int y);

int calcnum = 0;

//==== メイン関数
int main(void) {
    int x, y;

    scanf("%d %d", &x, &y);

    input_arr(x, y);

    rt_search(x, y);
    
    printf("計算回数 : %d\n", calcnum);  
  
    return 0;
}

//==============================================
// 配列の入力関数
//==============================================

void input_arr(int x, int y) {
    int k1, k2;
  
    for ( k1 = 0; k1 < x; k1++ ) {
        for ( k2 = 0; k2 < y; k2++ ) {
            scanf("%d", &arr[k1][k2]);
        }
    }
}

//==============================================
// 前の要素から最大値を取り出す(値を返却する)
//==============================================

int max_arr(int i, int st, int fin) {
    int k;
    int max = 0;
  
    for ( k = st; k <= fin; k++ ) {
        if ( max < ans[k][i] ) {
            max = ans[k][i];
        }
    }

    return max;
}
//==============================================
// 前の要素から最大値を取り出す(要素の場所を返却する)
//==============================================

int max_ans(int i, int st, int fin) {
    int k;
    int max = 0;
    int mk;
  
    for ( k = st; k <= fin; k++ ) {
        if ( max < ans[k][i] ) {
            max = ans[k][i];
            mk = k;
        }
    }

    return mk;
}

//==============================================
// 経路表作成関数
//==============================================

void rt_search(int x, int y) {
  int k1, k2;
  int max;
  
    for ( k1 = 0; k1 < y; k1++ ) {
         for ( k2 = 0; k2 < x; k2++ ) {
             calcnum++;
             if ( k1 == 0 ) {      // 一番左の時
                 ans[k2][k1] = arr[k2][k1];
             } else {      // それ以外
                 if ( k2 == 0 ) {  max = max_arr(k1-1, k2, k2+1);  } 
                 else if ( k2 == x-1 ) {  max = max_arr(k1-1, k2-1, k2); }
                 else { max = max_arr(k1-1, k2-1, k2+1); }
                 ans[k2][k1] = arr[k2][k1] + max;    // 経路表用の配列に格納 
             }
         }
    }
    
    rt_max(x, y);
    puts("--------------------------------");
  
    output_arr(x, y);
}

//==============================================
// 最大経路を求め出力する
//==============================================
void rt_max(int x, int y) {
    int maxk;
    int max;
    int k;
    int ytmp;
    int mrt[NUM];
    
    ytmp = y-1;
    puts(""); 
    maxk = max_ans(ytmp, 0, x-1);
    max = ans[maxk][y-1];
    mrt[0] = maxk;

    for ( k = 1; k < y; k++ ) {
        ytmp--;
        if ( maxk == 0 ) { maxk = max_ans(ytmp, maxk, maxk+1); }
        else if ( maxk == x ) { maxk = max_ans(ytmp, maxk-1, maxk); }
        else { maxk = max_ans(ytmp, maxk-1, maxk+1); }
        mrt[k] = maxk;
    }
    
    for ( k = y-1; k >= 0; k-- ) {
        printf("%2d ", mrt[k]);
    }
    printf(": %d\n", max);
}

//==============================================
// 経路表出力関数
//==============================================

void output_arr(int x, int y) {
    int k1, k2;

    for ( k1 = 0; k1 < x; k1++ ) {
        for ( k2 = 0; k2 < y; k2++ ) {
            printf("%2d ", ans[k1][k2]);
        }
        printf("\n");
    }  
}
