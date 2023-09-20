#include "lib.h"

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
