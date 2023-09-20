/**
 * @brief pdf 中的流程图采用的模拟法，时间复杂度 O(n)，
 * 空间复杂度 O(1)。
 *   
 * @param n 初始人数
 * @return int 留到最后未出局的胜者
 */
int solve_std(int n);

/**
 * @brief 数组模拟，核心思路是用 out[i] 表示 i 是否出局，遍历到出局者时跳过。
 * 时间复杂度 O(n ^ 2)，空间复杂度 O(n)。
 *
 * @param n 游戏人数。
 * @param out 传入一个数组存储各个玩家是否出局。
 * @return int 答案。
 */
int solve_array(int n, int out[]);

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
int solve_list(int n, Node list[]);
