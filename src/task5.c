#include "lib.h"
#include <stdio.h>

#define MAX_N 2000

// 算法需要的存储空间
int out[MAX_N];
Node nodes[MAX_N];

int main(int argc, char** argv) {
    printf(
        "\
This program will the answers from 3 different methods.\n\
Input the number of players:\n"
    );

    int n = 0;
    scanf("%d", &n);
    int ans_std = solve_std(n);
    int ans_array = solve_array(n, out);
    int ans_list = solve_list(n, nodes);
    printf(
        "\
The standard method from pdf gives: %d\n\
The array method gives: %d\n\
The list method gives: %d\n",
        ans_std,
        ans_array,
        ans_list
    );
    return 0;
}
