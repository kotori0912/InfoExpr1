//====================================================================
//  情報環境実験I 再帰法
//  問題3-02 (1)
//  15T207 伊藤 拓海
//====================================================================

//====================================================================
//  仕様
//====================================================================

/*--------------------------------------------------------------------

正整数numをmax以下の正整数のlen個の総和の形を求める

---------------------------------------------------------------------*/


//====================================================================
//  前処理
//====================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define  LEN  100          // 試行回数の最大数
#define  MAX  100         // 分割上限  

int recnum = 0;    // 再帰の回数を調べる

//--------------------------------------------------------------------
//  関数宣言
//--------------------------------------------------------------------

int enum_parti1(int seq[], int num, int len, int pos, int max);
int enum_parti1_ex(int seq[], int num, int len, int pos, int max);
void output_arr(int arr[], int n);


//====================================================================
//  本体関数
//====================================================================

int main(int argc, char *argv[]) {
  //----  宣言
  int num;         // 総和
  int max;         // 上限
  int len;         // 個数
  int seq[LEN];    // 試行列(空列に初期化)
  int s;           // 列挙された事象の数
  int sel;        // 効率非効率の選択用
  clock_t start, end;
  double t0;

  //----  入力
  printf("総和 = ?  "); scanf("%d", &num);
  printf("個数 = ?  "); scanf("%d", &len);
  
  sel = atoi(argv[1]);
  //num = atoi(argv[2]);
  //len = atoi(argv[3]);
  
  max = num;
  
  start = clock();
  //----  列挙の再帰的処理
  if ( sel == 0 ) {
    s = enum_parti1(seq, num, len, 0, max);
  } else {
    s = enum_parti1_ex(seq, num, len, 0, max);
  }
  end = clock();
  
  t0 = (end - start + 0.0)/CLOCKS_PER_SEC;
  
  //----  標準出力
  
  printf("列挙総数 = %d\n", s);
  printf("処理時間 : %f\n", t0);
  printf("再帰回数 : %d\n", recnum);
  
  //---- CSV吐き出し
  //printf("%d, ", s);
  //printf("%f, ", t0);
  //printf("%d, ", recnum);
  
  return 0;
}

//====================================================================
//  関数定義
//====================================================================

//--------------------------------------------------------------------
//  事象の列挙
//--------------------------------------------------------------------

int enum_parti1(int seq[], int num, int len, int pos, int max) {
  int s = 0;
  
  recnum++;
	
  if ( num < 0 || max < 0 || pos < 0 ) { return 0; }     // num, max, pos が0以下は論外
	
  if ( max%2 == 0 ) { max--; }     // maxが偶数なら1減らす
	
  if ( num == 0 ) { 
     // output_arr(seq, pos); 
     return 1;
  }    // n = 0 で終了
  if ( max == 0 || len == 0 ) { return 0; }    // m = 0 return 0;
  //if ( max > num ) { max = num%2 == 0 ? num-1:num; }     // numをmaxに代入と同時に偶奇判定
  if ( len > num ) { len = num; }    
  // seq[pos++] = max;    // 配列への代入
  s += enum_parti1(seq, num-max, len-1, pos, max);    // 再帰処理1 len を更新する
  // pos--;    // pos の更新
  s += enum_parti1(seq, num, len, pos, max-2);    // 再帰処理2 maxを更新する
	
  return s;
}

//------------------------------------------------------------------------------------------
// 効率化
//------------------------------------------------------------------------------------------

int enum_parti1_ex(int seq[], int num, int len, int pos, int max) {
  int s = 0;
  
  recnum++;
	
  if ( num < 0 || max < 0 || pos < 0 ) { return 0; }     // num, max, pos が0以下は論外
	
  if ( max%2 == 0 ) { max--; }     // maxが偶数なら1減らす
	
  if ( num == 0 ) { 
     // output_arr(seq, pos); 
     return 1;
  }    // n = 0 で終了
  if ( max == 0 || len == 0 ) { return 0; }    // m = 0 return 0;
  if ( num > max*len ) { return 0; }    // 不可能だから return 0;
  if ( max > num ) { max = num%2 == 0 ? num-1:num; }     // numをmaxに代入と同時に偶奇判定
  if ( len > num ) { len = num; }    
  // seq[pos++] = max;    // 配列への代入
  s += enum_parti1_ex(seq, num-max, len-1, pos, max);    // 再帰処理1 len を更新する
  // pos--;    // pos の更新
  s += enum_parti1_ex(seq, num, len, pos, max-2);    // 再帰処理2 maxを更新する
	
  return s;
}

//--------------------------------------------------------------------
//  配列の出力
//--------------------------------------------------------------------

void output_arr(int arr[], int n) {
  int k;
  for ( k = 0; k < n; k++ ) { printf("%2d ", arr[k]); }
  puts("");
}
