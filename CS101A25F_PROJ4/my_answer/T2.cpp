#include <climits>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <stack>
#include <vector>

const int MAXM = 1000000 + 5;
const int MAXN = 100000 + 5;

std::vector<int> neighbors[MAXN], neighbors_rev[MAXN]; // 每个结点的邻居，我不知道怎么用矩阵来实现……
bool visited[MAXN] { false }, visited_rev[MAXN] { false };
std::stack<int> dfs_stack; // 正向dfs访问顺序
int rep[MAXN];
int rep_id[MAXN];
std::vector<int> scc[MAXN]; // 每个scc包含的结点
int scc_count = 0;

// 正向dfs
void dfs(int u)
{
    visited[u] = true;
    for (int v : neighbors[u]) {
        if (!visited[v]) {
            dfs(v);
        }
    }
    dfs_stack.push(u);
}

// 反向dfs，找出scc，id是scc编号
void dfs_rev(int u, int id)
{
    visited_rev[u] = true;
    rep_id[u] = id;
    scc[id].push_back(u);
    for (int v : neighbors_rev[u]) {
        if (!visited_rev[v]) {
            dfs_rev(v, id);
        }
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; ++i) {
        int u, v;
        scanf("%d %d", &u, &v);
        neighbors[u].push_back(v);
        neighbors_rev[v].push_back(u);
    }

    for (int i = 1; i <= n; ++i) { // 正向dfs
        if (!visited[i]) {
            dfs(i);
        }
    }

    while (!dfs_stack.empty()) { // 反向dfs
        int u = dfs_stack.top();
        dfs_stack.pop();
        if (!visited_rev[u]) {
            scc_count++;
            dfs_rev(u, scc_count);
        }
    }

    std::vector<int> scc_rep(scc_count + 1, INT_MAX); // 每个rep_id的rep
    for (int i = 1; i <= scc_count; ++i) { // 为每个scc选择rep
        for (int u : scc[i]) {
            scc_rep[i] = std::min(scc_rep[i], u);
        }
    }
    for (int i = 1; i <= n; ++i) {
        rep[i] = scc_rep[rep_id[i]];
    }

    std::set<std::pair<int, int>> dag_edges; // 新dag的边
    for (int u = 1; u <= n; ++u) { // 压缩去除scc后的dag的边
        for (int v : neighbors[u]) {
            int rep_u = rep[u], rep_v = rep[v];
            if (rep_u != rep_v) {
                dag_edges.insert({ rep_u, rep_v });
            }
        }
    }
    std::vector<std::vector<int>> dag(MAXN);
    std::vector<int> inDegree(MAXN, 0);
    for (auto& p : dag_edges) { // 构建新dag和对应的inDegree
        int u = p.first, v = p.second;
        dag[u].push_back(v);
        inDegree[v]++;
    }

    std::priority_queue<int, std::vector<int>, std::greater<int>> reps; // rep
    for (int i = 1; i <= scc_count; ++i) { // 先存入inDegree为0的rep
        int r = scc_rep[i];
        if (inDegree[r] == 0) {
            reps.push(r);
        }
    }
    std::vector<int> topo_order;
    while (!reps.empty()) { // 边拓扑排序边存新的inDegree为0的rep
        int u = reps.top();
        reps.pop();
        topo_order.push_back(u);
        for (int v : dag[u]) {
            inDegree[v]--;
            if (inDegree[v] == 0) {
                reps.push(v);
            }
        }
    }

    printf("%d\n", scc_count);
    for (int i = 1; i <= n; ++i) {
        if (i > 1)
            printf(" ");
        printf("%d", rep[i]);
    }
    printf("\n");
    for (std::size_t i = 0; i < topo_order.size(); ++i) {
        if (i > 0)
            printf(" ");
        printf("%d", topo_order[i]);
    }
    printf("\n");
    return 0;
}