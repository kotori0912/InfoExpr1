#include <stdio.h>

#define LEN 11

void input_str(char str1[], int n1, char str2[], int n2, char str0[], int n0);
void set_strs_ans(char str1[], char str2[], char str0[], int b1[], int b2[], int b0[]);
void set_str_id(char open[], int *op, char str[], int b[]);
int num_change(int b[], int n);
int calc_pow(int b, int n);
int dec_ans(int n1, int n2, int n0);
int search_str_ind(char str[], char ch);
void num_output(int a[], int b[], int n);

int n1, n2, n0;

int main(void) {
	char str1[LEN], str2[LEN], str0[LEN];
	int b1[LEN], b2[LEN], b0[LEN];
	int a[LEN];
	int k;
	
	for ( k = 0; k < LEN; k++ ) {
		a[k] = k;
	}
	
	scanf("%d %d %d ", &n1, &n2, &n0);
	input_str(str1, n1, str2, n2, str0, n0);
	puts("=============================");

  	set_strs_ans(str1, str2, str0, b1, b2, b0);

  	printf("%s %s %s\n", str1, str2, str0);
  	num_output(a, b1, n1);
  	num_output(a, b2, n2);
  	num_output(a, b0, n0);
  	puts("");

  	return 0;
}

void input_str(char str1[], int n1, char str2[], int n2, char str0[], int n0) {
  	char tmp[255];
  	char *p = tmp;
  	int i;

  	fgets(tmp, sizeof(tmp), stdin);

  	while ( *p == ' ' ) { p++; }
  	for ( i = 0; i < n1; i++ ) {
    	str1[i] = *p;
    	p++;
  	}
  	while ( *p == ' ' ) { p++; }
  	for ( i = 0; i < n2; i++ ) {
    	str2[i] = *p;
    	p++;
  	}
  	while ( *p == ' ' ) { p++; }
  	for ( i = 0; i < n0; i++ ) {
    	str0[i] = *p;
    	p++;
  	}
  	str1[n1] = '\0';
  	str2[n2] = '\0';
  	str0[n0] = '\0';
}

void set_strs_ans(char str1[], char str2[], char str0[], int b1[], int b2[], int b0[]) {
  	char open[LEN] = {'\0'};
  	int op = 0;
  	int k = 0;
  	int t1, t2, t0;
  	int jdg;

	while ( op < 9 ) {
  		set_str_id(open, &op, str1, b1);
  		set_str_id(open, &op, str2, b2);
  		set_str_id(open, &op, str0, b0);
  		
  		t1 = num_change(b1, n1);
  		t2 = num_change(b2, n2);
  		t0 = num_change(b0, n0);
  		jdg = dec_ans(t1, t2, t0);
  		
  		if ( jdg == 1 ) {
  			break;
  		}
  		
  		k++;
  		op = k; 
  		//printf("%d\n", op);
  	}
}

void set_str_id(char open[], int *op, char str[], int b[]) {
  	int p = 0;
  	int t;

  	while ( str[p] != '\0' ) {
    	t = search_str_ind(open, str[p]);
    	if ( *op == 10 ) { *op = 0; }
    	if ( t == -1 ) {
      		open[*op] = str[p];
      		b[p++] = (*op)++;
    	} else {
      		b[p++] = t;
    	}
  	}

}

int num_change(int b[], int n) {
	int k;
	int sum = 0;
	
	for ( k = 0; k < n; k++ ) {
		sum += calc_pow(b[k], k);
	}
	
	return sum;
}

int calc_pow(int b, int n) {
	int k;
	int res = b;
	
	for ( k = 0; k < n; k++ ) {
		res *= 10;
	}
	
	return res;
}

int dec_ans(int n1, int n2, int n0) {
	if ( n1 + n2 == n0 ) {
		return 1;
	}
	
	return -1;
}

int search_str_ind(char str[], char ch) {
  	int p = 0;
  	while ( str[p] != '\0' ) {
    	if ( str[p] == ch ) { return p; }
    	p++;
  	}
  	return -1;
}

void num_output(int a[], int b[], int n) {
  	int i;

  	for ( i = 0; i < n; i++ ) {
    	printf("%d", a[b[i]]);
  	}
  	
  	printf(" ");
}
