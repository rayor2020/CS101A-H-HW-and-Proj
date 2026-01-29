#include <algorithm>
#include <bits/stdc++.h>

class Node {
public:
    int s; // 值
    int height; // 以之为根的子树高度
    Node* parent;
    Node* child[2]; // 0左1右

    Node(int value)
        : s(value)
        , height(0)
        , parent(nullptr)
    {
        child[0] = child[1] = nullptr;
    }
};

class AVLTree {
    Node* root;

    int getNodeHeight(Node* node) // 获取节点高度
    {
        if (node) {
            return node->height;
        } else {
            return -1; // 空树是-1
        }
    }

    void updateNodeHeight(Node* node) // 更新节点高度为俩子树中最大+1
    {
        if (node) {
            node->height = std::max(getNodeHeight(node->child[0]), getNodeHeight(node->child[1])) + 1;
        }
    }

    int getNodeBalance(Node* node) // 获取平衡因子：左-右
    {
        if (node) {
            return getNodeHeight(node->child[0]) - getNodeHeight(node->child[1]);
        } else {
            return 0;
        }
    }

    // 结点旋转操作
    Node* rotateRight(Node* r) // 右旋转
    {
        Node* l = r->child[0];
        Node* lr = l->child[1];

        l->child[1] = r;
        r->child[0] = lr;

        // 更新父节点指针
        if (lr)
            lr->parent = r;
        l->parent = r->parent;
        r->parent = l;

        updateNodeHeight(r);
        updateNodeHeight(l);

        return l;
    }
    Node* rotateLeft(Node* l) // 左旋转
    {
        Node* r = l->child[1];
        Node* rl = r->child[0];

        r->child[0] = l;
        l->child[1] = rl;

        // 更新父节点指针
        if (rl)
            rl->parent = l;
        r->parent = l->parent;
        l->parent = r;

        updateNodeHeight(l);
        updateNodeHeight(r);

        return r;
    }

    Node* autoBalance(Node* node) // 按需进行平衡操作
    {
        int balance = getNodeBalance(node);

        // 如果节点不平衡，则有4种情况
        if (balance > 1 && getNodeBalance(node->child[0]) >= 0) { // 左左
            return rotateRight(node);
        }
        if (balance > 1 && getNodeBalance(node->child[0]) < 0) { // 左右
            node->child[0] = rotateLeft(node->child[0]); // 化为左左
            return rotateRight(node);
        }

        if (balance < -1 && getNodeBalance(node->child[1]) <= 0) { // 右右
            return rotateLeft(node);
        }
        if (balance < -1 && getNodeBalance(node->child[1]) > 0) { // 右左
            node->child[1] = rotateRight(node->child[1]); // 化为右右
            return rotateLeft(node);
        }

        return node; // 已经平衡，无需操作
    }

    Node* insertNode(Node* node, int value, Node* parent) // 插入节点
    {
        if (!node) { // 可以插入
            Node* newNode = new Node(value);
            newNode->parent = parent;
            return newNode;
        }

        if (value >= node->s) { // 稳定插入：相同当作更大处理
            node->child[1] = insertNode(node->child[1], value, node);
        } else {
            node->child[0] = insertNode(node->child[0], value, node);
        }

        updateNodeHeight(node);

        return autoBalance(node);
    }

    int getNodeDepth(Node* node) // 获取节点深度
    {
        int depth = 0;
        while (node && node->parent) {
            ++depth;
            node = node->parent;
        }
        return depth;
    }

    Node* findNode(Node* node, int value, Node* found = nullptr) // 查找最浅的节点
    {
        if (!node) // 到头都没找到
            return found;

        if (value == node->s) { // 找到了
            if (!found || getNodeDepth(node) < getNodeDepth(found)) // 避免意外找到非最浅的
                found = node;

            return found;
        } else if (value < node->s) {
            return findNode(node->child[0], value, found); // 去左边找
        } else {
            return findNode(node->child[1], value, found); // 去右边找
        }
    }

    Node* findRMin(Node* node) // 查找右边最小
    {
        while (node && node->child[0])
            node = node->child[0];
        return node;
    }

    /*
    删除操作部分喜提 Runtime Error，仅供思路参考
    */
    void removeNode(Node* to_remove) // 删除节点
    {
        if (!to_remove) // 防止试图删去不存在的节点
            return;

        if (!to_remove->child[0] || !to_remove->child[1]) { // 0/1个孩子
            Node* temp = nullptr;
            Node* currentNode = to_remove->parent;

            if (to_remove->child[0]) {
                temp = to_remove->child[0];
            } else {
                temp = to_remove->child[1];
            }

            if (temp) { // 有一个子节点
                temp->parent = to_remove->parent;
            }
            delete to_remove;

            while (currentNode != root) {
                updateNodeHeight(currentNode);

                currentNode = autoBalance(currentNode);
                currentNode = currentNode->parent;
            }
            updateNodeHeight(root);
            root = autoBalance(root);
            return;
        } else { // 有两个子节点，把右边最小的接上
            Node* RMin = findRMin(to_remove->child[1]); // 其实是数值替换然后删除右边最小
            to_remove->s = RMin->s;
            removeNode(RMin);
            return;
        }
    }

    void preOrderPrint(Node* node) // 前序遍历打印调试信息
    {
        if (!node)
            return;

        int parent_val;
        if (node->parent) {
            parent_val = node->parent->s;
        } else {
            parent_val = 0;
        }
        int left_val;
        if (node->child[0]) {
            left_val = node->child[0]->s;
        } else {
            left_val = 0;
        }
        int right_val;
        if (node->child[1]) {
            right_val = node->child[1]->s;
        } else {
            right_val = 0;
        }

        printf("%d %d %d %d\n", node->s, parent_val, left_val, right_val);
        preOrderPrint(node->child[0]);
        preOrderPrint(node->child[1]);
    }

    void inOrderTraversal(Node* node, std::vector<int>& values) // 中序遍历从小到大收集值
    {
        if (!node)
            return;

        // 左中右
        inOrderTraversal(node->child[0], values);
        values.push_back(node->s);
        inOrderTraversal(node->child[1], values);
    }

public:
    AVLTree()
        : root(nullptr)
    {
    }

    void insert(int value) // 插入操作
    {
        root = insertNode(root, value, nullptr);
    }

    Node* find(int value) // 查找操作
    {
        return findNode(root, value);
    }

    void remove(int value) // 删除操作
    {
        Node* to_remove = find(value); // 先查找要删除的最浅节点
        if (to_remove) {
            removeNode(to_remove);
        }
    }

    void printDebug() // 输出前序遍历调试信息

    {
        preOrderPrint(root);
    }

    int getNodeSubtreeHeight(Node* node) // 获取结点子树高度
    {
        if (node) {
            return node->height;
        } else {
            return 0;
        }
    }

    int kthSmallest(int k) // 查找第k小元素
    {
        std::vector<int> values;
        inOrderTraversal(root, values);

        if (k >= 1 && k <= (int)values.size()) {
            return values[k - 1];
        }
        return INT_MIN; // 无效查询
    }

    // 计算最优分割点
    long long findOptimalSplit(long long k)
    {
        if (!root)
            return INT_MIN; // 无效查询

        std::vector<int> values;
        inOrderTraversal(root, values);

        long long min_result = LLONG_MAX;
        bool found = false;
        int n = values.size();

        // 计算前缀和
        std::vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + values[i];
        }

        // 尝试每个分割点
        for (int t = 1; t <= n; t++) {
            long long left_sum = prefix[t];
            long long right_sum = prefix[n] - prefix[t];
            long long diff = k * left_sum - right_sum;

            if (diff >= 0) {
                found = true;
                min_result = std::min(min_result, diff);
            }
        }

        return found ? min_result : INT_MIN;
    }
};

void invalidQuery() { printf("Invalid query!\n"); }

int main()
{
    int n;
    std::cin >> n;

    AVLTree tree;

    for (int i = 1; i <= n; i++) {
        int opt, x;
        std::cin >> opt >> x;

        printf("----------#%d: %d %d----------\n", i, opt, x);

        switch (opt) {
        case 1: // 插入
            tree.insert(x);
            tree.printDebug();
            break;

        case 2: { // 查询节点最小高度
            Node* node = tree.find(x);
            if (node) {
                std::cout << tree.getNodeSubtreeHeight(node) << std::endl;
            } else {
                printf("Not found!\n");
            }
            break;
        }

        case 3: // 删除
            tree.remove(x); // 做不到TAT……
            tree.printDebug();
            break;

        case 4: { // 查询第k小元素
            int result = tree.kthSmallest(x);
            if (result != INT_MIN) {
                std::cout << result << std::endl;
            } else {
                invalidQuery();
            }
            break;
        }

        case 5: { // 计算最优分割
            long long result = tree.findOptimalSplit(x);
            if (result != INT_MIN) {
                std::cout << result << std::endl;
            } else {
                invalidQuery();
            }
            break;
        }
        }
    }
    return 0;
}