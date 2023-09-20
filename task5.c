#include <stdio.h>

/**
 * @brief pdf 中的流程图采用的模拟法，时间复杂度 O(n)，
 * 空间复杂度 O(1)。
 *   
 * @param n 初始人数
 * @return int 留到最后未出局的胜者
 */
int solve_std(int n) {
    // 从剩余人数为 k 时的胜者
    // (剩余人数 1 时为 0 号) 反推剩余人数为 k + 1 时的胜者。
    // count 表示模拟情况的剩余人数。
    int count = 2;
    // pre_winner 表示当前剩余人数情况下的胜者编号，
    // 剩余人数为 1 时，胜者为 0 号，也就是初始值。
    int pre_winner = 0;
    // 当前要求的答案是剩余 count 个人时，从 0 号开始报数的胜者。
    while (count <= n) {
        // 若剩余人数为 k 时胜者为 p 号，
        // 则剩余人数为 k + 1 时的 (p + 2) 号
        // 在一次初始报数后就会成为 p 号，因此他将成为胜者。
        pre_winner = (pre_winner + 2) % count;
        count += 1;
    }
    return pre_winner;
}

/**
 * @brief 数组模拟，核心思路是用 out[i] 表示 i 是否出局，遍历到出局者时跳过。
 * 时间复杂度 O(n ^ 2)，空间复杂度 O(n)。
 *
 * @param n 游戏人数。
 * @param out 传入一个数组存储各个玩家是否出局。
 * @return int 答案。
 */
int solve_array(int n, int out[]) {
    // out[i] == 1 表示第 i 个人已经出局
    int pos = 0; // 当前报数者位置
    for (int num = n /*剩余人数*/; num >= 2; num--) {
        do {
            // 第一个报数者是 pos，所以寻找第二个报数者。
            pos = (pos + 1) % n;
            // 这里如果 pos 已经出局就跳过。
        } while (out[pos] == 1);
        out[pos] = 1; // 第二个报数者出局。
        do {
            // 寻找在下一轮第一个报数的人。
            pos = (pos + 1) % n;
        } while (out[pos] == 1);
    }
    // 只剩一个人时，"当前报数者"就是胜者
    return pos;
}

typedef struct NodeInner Node;
/**
 * @brief 定义了链表的结点，其中两个指针指向前后玩家
 */
struct NodeInner {
    int id; // 玩家序号
    Node* pre; // 前一个玩家
    Node* nxt; // 后一个玩家
};

/**
 * @brief 链表模拟法，时间复杂度 O(n)，空间复杂度 O(n)。
 * 
 * @param n 游戏人数。
 * @param list 传入一个无数据的链表，存储玩家信息。
 * @return int 答案。
 */
int solve_list(int n, Node list[]) {
    for (int i = 0; i < n; i++) {
        // for 循环初始化，记录玩家序号，并使所有玩家
        // 首尾相连，构成一个环。
        list[i].id = i;
        list[i].pre = &list[(i - 1 + n) % n];
        list[i].nxt = &list[(i + 1) % n];
    }
    // 从 0 号开始报数
    Node* cur = &list[0];
    for (int num = n; num >= 2; num--) {
        cur = cur->nxt; // 来到第二个报数的玩家
        Node* del = cur; // 该玩家即将出局
        cur = cur->nxt; // cur 指针来到下一回合开始报数的玩家
        del->pre->nxt = del->nxt; // 将被删除玩家的前一个人的 nxt 指针指向被删除者的后一个人
        del->nxt->pre = del->pre; // 将被删除玩家的后一个人的 pre 指针指向被删除者的前一个人
        // 如此一来 del 将从环中删除，不会再被遍历到捏。
    }
    return cur->id;
}

#define MAX_N 2000

// 算法需要的存储空间
int out[MAX_N];
Node nodes[MAX_N];

int main(int argc, char** argv) {
    int n = 0;
    scanf("%d", &n);
    int ans_std = solve_std(n);
    printf("%d\n", ans_std);
    return 0;
}
