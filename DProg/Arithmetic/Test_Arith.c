
#include <stdio.h>
#include <stdbool.h>

#define N 10

int  nums[N];
bool used[N];

void check(void) {
	int send = nums[1] * 1000 + nums[2] * 100 + nums[3] * 10 + nums[4];
	int more = 1000 + nums[5] * 100 + nums[6] * 10 + nums[2];
	int money = 10000 + nums[5] * 1000 + nums[3] * 100 + nums[2] * 10 + nums[7];
	if (send + more == money) {
		printf("%d + %d = %d\n", send, more, money);
	}
}

// 順列の生成
// n から m までの数字の中から k 個を選ぶ
void permutations(int n, int m, int k, int x) {
	if (x == k) {
		check();
	} else {
		for (int i = n; i <= m; i++) {
			if (!used[i]) {
      			used[i] = true;
				nums[x] = i;
				permutations(n, m, k, x + 1);
				used[i] = false;
			}
		}
	}
}

int main(void) {
	nums[0] = 1;
	used[1] = true;
	permutations(0, 9, 8, 1);
	return 0;
}