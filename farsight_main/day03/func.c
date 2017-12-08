#include <stdio.h>
#include <stdlib.h>
typedef int (* func)(int a,int b);

int add(int a, int b){
    return a+b;
}

int minus(int a , int b){
    return a-b;
    
}

int deal_num(int a, int b, func c){

    return (*c)(a, b);
}
int main(){

/*callback function
    int a = 100;
    int b = 110;

    printf("%d\n", deal_num(a, b, add) );
    printf("%d\n", deal_num(a, b, minus));

*/

/*function pointer array
    func z[2];

    z[1] = add;
    z[2] = minus;

 printf("%d, %d\n",z[1](1,2), z[2](123,99) );

*/

// two_arr();
//    char a[10] = "kang chao";
//    char b[]   = "zzzzz";
//    my_strcpy(a,b);
//    printf("a:%s\n", a);

//    printf("%d\n",my_atoi("11232i3"));
//    array_test();
//    int a[][4] = {{1,2,3,3},{2,3,2,12},{1,2}};
//    find_max(a, 3, 4);

}

int find_max(int (*p)[4],int n, int m){

    int i, j ,row = 0, line =0;
    for (i = 0; i <n ; i++) {
        for (j = 0; j < m ; j++) {
            if(p[row][line] < p[i][j]){
                row = i;
                line = j;
            }
        }
    }
    printf("max:%d row:%d line:%d\n",p[row][line], row, line );
}


int test_sizeof(){

    int a[2][3]= {{1,2,3},{7,8,9}};
    int (*p)[3] = a;

    printf("%ld %ld %ld\n", sizeof(a), sizeof(a+1), sizeof(a[0]) );
    printf("%ld %ld %ld\n", sizeof(p), sizeof(p+1), sizeof(p[0]) );
    printf("%ld\n", sizeof(NULL) );
}


int array_test(){
    int c[2][2] = {{1,2},{3,4}};
    int (*b)[2];

    b = c;
    int i;
    int j;
    for(i = 0; i <2; i++){
        for(j = 0; j <2; j++){
            printf("%d", b[i][j]);
        }
    }
    return 0;
}



/*
int find_two_array_max(int **z, int a, int b){


}
*/


int my_atoi(char *a){

    int sum = 0;
    while (*a >= '0' && *a <= '9') {
//        printf("%c--\n", *a);
        sum = sum * 10 + (*a - '0') ;
        a++;
    }
    return sum;
}

char *my_strcpy(char *a, char *b){
    char *tmp = a;
    
    *a = *b;

    do{
        a++;
        b++;
        *a = *b;
    }while(*b != '\0');

    return tmp;
}

int two_arr(){
    int a[3][3] = {{1,2},{6},{7,8,9}};
    int i,j;


    for (i = 0; i < 3; i++){
        for (j = 0; j < 3; j++){
            printf("[%d][%d]:%d\n", i, j ,a[i][j]); 
        }
    }
    return 0;
}

