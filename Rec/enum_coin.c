//====================================================================
//  情報環境実験I 再帰法
//  問題3-02 (2)
//  15T207 伊藤 拓海
//====================================================================

//====================================================================
//  前処理
//====================================================================

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define  LEN  1000          // 試行回数の最大数
#define  COINS  4           // コインの種類

//--------------------------------------------------------------------
//  関数宣言
//--------------------------------------------------------------------

int enum_money(int coin[], int len, int mny, int cnt, int seq[], int pos);
void out_money(int coin[], int seq[], int snum);

//====================================================================
//  本体関数
//====================================================================

int main(int argc, char *argv[]) {
    //----  宣言
    int coin[COINS] = { 1, 10, 50, -1};
    int money;    // 総額
    int cnt;         // 上限枚数 
    int len;         // 個数
    int seq[LEN];    // 試行列(空列に初期化)
    int s;           // 列挙された事象の数
    clock_t start, end;     // 時間測定
    double t0;    // 測定時間格納
    int k;    // 反復変数

    //----  入力
    
    printf("金額 = ?  "); scanf("%d", &money);
    printf("枚数 = ?  "); scanf("%d", &cnt);
    
    //----　実行時引数での入力
    //money = atoi(argv[1]);
    //cnt = atoi(argv[2]);
  
    len = COINS-1;    // lenはコインの種類分
  
    //----  表の出力
    fprintf(stderr, "  1  10  50  -1");
    //fprintf(stderr, "  1  10  25  50  -1");    // 問題指定
    //fprintf(stderr, "  1  5  10  50  -1");    // 日本円
    //fprintf(stderr, "  1  5  10  25  50  -1");    // アメリカ    
    fprintf(stderr, "\n---------------------\n");
  
    start = clock();
    //----  列挙の再帰的処理
    s = enum_money(coin, len, money, cnt, seq, 0);
    end = clock();
  
    t0 = (end - start + 0.0)/CLOCKS_PER_SEC;
  
    //----  数え上げ
    fprintf(stderr, "列挙総数 = %d\n", s);
    //----  CSV出力
    //printf("%d,", s);    
  
    return 0;
}

//====================================================================
//  関数定義
//====================================================================

//--------------------------------------------------------------------
//  硬貨の支払パターン
//--------------------------------------------------------------------

int enum_money(int coin[], int len, int mny, int cnt, int seq[], int pos) {
	int cn;    // コイン1種類
	int s = 0;    // 列挙総数
	int k;    // 反復変数
	
	//---- 事前処理 & 出力
	if ( mny < 0 ) { return 0; }    // お金がマイナスなら終了
	if ( mny == 0 || cnt == 0 ) { out_money(coin, seq, pos);  return 1; }    // お金が0になったら結果を出力し終了
	if ( len == 0 ) { return 0; }    // lenが0で終了
	cn = coin[len-1];    // コインの種類を格納
	
	//---- 計算再帰処理
	if ( cn == 1 ) {    // 1円の時
		if ( mny <= cnt ) {    // 枚数の上限までの処理
			for ( k = 0; k < mny; k++ ) {
				seq[pos++] = 1;
			}
			out_money(coin, seq, pos);
			return 1;
		} else {    // 上限を超えた時の処理
			return 0;
		}
	}
	
	if ( mny < cn ) {    // お金1種類だけで再帰
		s += enum_money(coin, len-1, mny, cnt, seq, pos);
	} else {    //分割法を用いて再帰
		seq[pos++] = cn;
		s += enum_money(coin, len, mny-cn, cnt-1, seq, pos);
		pos--;
		s += enum_money(coin, len-1, mny, cnt, seq, pos);
	}
	
	return s;
}

//---------------------------------------------------------------------------------------
// パターンを出力
//---------------------------------------------------------------------------------------
void out_money(int coin[], int seq[], int snum) {
	int k1, k2;    // 反復変数
	int out[LEN] = {0};    // 枚数格納配列
	int cnum;    // コインの枚数
	
	for ( k1 = 0; coin[k1] != -1; k1++ ) {}    // コインの枚数を調べる
	
	cnum = k1;    // 枚数をcnumに格納
	k2 = cnum-1;    // k2はcnum-1に設定
	
	//---- 配列の初期化
	for ( k1 = 0; k1 < k2; k1++ ) {
		out[k1] = 0;
	}
	k1 = 0;    // k1をゼロに初期化
	
	//---- snumを分けてoutへ格納
	while ( k1 < snum ) {
		while ( seq[k1] == coin[k2] ) {
			if ( k1 >= snum ) { break; }
			out[k2]++;
			k1++;
		}
		k2--;
	}
	
	//---- 出力処理
	for ( k2 = cnum-1; k2 >= 0; k2-- ) {
		fprintf(stderr, "%3d ", out[k2]);
	}
	fprintf(stderr, "%3d\n", snum);
}

