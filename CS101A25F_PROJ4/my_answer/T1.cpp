#include <algorithm>
#include <cstdio>
#include <vector>

const int MAX_M = 600000 + 5;
const int MAX_N = 200000 + 5;

class Edge {
public:
    int idx, l, r, c;
    bool operator<(const Edge& other) const
    {
        return c > other.c; // 核心技术
    }
};

Edge edges[MAX_M];
int father[MAX_N]; // 并查集根节点索引
int h[MAX_N];

// 更新根节点的位置
int find(int x)
{
    return father[x] == x ? x : father[x] = find(father[x]);
}

// 合并生成树
void unite(int x, int y)
{
    x = find(x);
    y = find(y);
    if (x != y)
        father[x] = y; // 合并根节点

    int a = find(x);
    int b = find(y);
    if (a != b) {
        if (h[a] < h[b]) {
            father[a] = b;
        } else {
            father[b] = a;
            if (h[a] == h[b])
                h[a]++;
        }
    }
}

int main()
{
    int m, n;
    scanf("%d %d", &m, &n);

    for (int i = 0; i <= n; i++)
        father[i] = i;

    std::vector<bool> isEdgeSelected(m, false); // 记录每条边是否选了

    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &edges[i].l, &edges[i].r, &edges[i].c);
        edges[i].idx = i;
        edges[i].l--;
    }
    std::sort(edges, edges + m); // 从大到小排序

    for (int i = 0; i < m;) {
        int j = i;
        std::vector<Edge> group;

        while (j < m && edges[j].c == edges[i].c) { // 权值相同的边放一起
            group.push_back(edges[j]);
            j++;
        }

        for (const Edge& e : group) {
            if (find(e.l) != find(e.r)) { // 如果两条边根节点不同，那么合并到一颗生成树中
                isEdgeSelected[e.idx] = true;
                unite(e.l, e.r);
            }
        }

        i = j; // 跳过已经处理的重复部分
    }

    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int k;
        scanf("%d", &k);
        printf("%s\n", isEdgeSelected[k - 1] ? "YES" : "NO");
    }
    return 0;
}