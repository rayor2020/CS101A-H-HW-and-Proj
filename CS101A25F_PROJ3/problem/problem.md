

# AVL Exercise

You've got a set, consisting of integers. Assume before each operation, the set contains $m$ integers, which are $s_1\le s_2\le s_3\le \ldots \le s_m$. You are allowed to perform five operations on this set:

1. Given $x$, insert $x$ into the set
2. Given $x$, query whether $x$ is in the set
3. Given $x$, erase $x$ from the set
4. Given $k$, query the k-th element of set i.e. $s_k$. 
5. Given $k$, you need to find a position $t$ such that $\left(k\sum\limits_{i=1}^ t s_i\right)- \sum\limits_{i=t+1}^m s_i\ge 0$, meanwhile minimize $\left(k\sum\limits_{i=1}^ t s_i\right) - \sum\limits_{i=t+1}^m s_i$. You should return the minimum ```ans```. In other words:
$$
\text{ans} = \min_{t\in [1,m]} \sum_{i=1}^t k\cdot s_i -  \sum_{i=t+1}^m s_i \\
\text{s.t.} \sum_{i=1}^t k\cdot s_i -  \sum_{i=t+1}^m s_i \ge 0
$$

Your task is maintaining an AVL tree that should support the above operations.

In order to check the correctness of your AVL tree structure, you are required to print some debugging information (see Output Format below). Therefore, some specifications are also required here:

- Multiple elements of the same value should be treated as multiple nodes in AVL.
- To specify the insertion behavior: Insertion is stable. In other words, the last inserted node should be **the last node in in-order traversal** among those who have the same value.
- To specify the query and erase behavior: If there are multiple nodes with value $x$, return/erase the node with **the smallest depth**.
- To specify the erase behavior: If the erased node has two children, replace it with the **first node of in-order traversal of its right subtree**.

# Format

## Input

The first line is an integer $n$, the number. $1\le n\le 10^3$.

For the following $n$ lines, each line is two integers ```opt``` and `x​`. $1\le \text{opt} \le 5,1\le x\le 10^3$.

## Output

For each operation, print debugging information first, where `i` is the ordinal number of this operation, and `opt, x` are the inputs.

```cpp
printf("----------#%d: %d %d----------\n", i, opt, x);
```

Then

- `opt=1`, after insertion, print debugging information about the AVL (four node values) using pre-order DFS like the pseudocode below

  ```cpp
  void preorder(Node* u) {
      if (u == nullptr)
          return;
      printf("%d %d %d %d\n", u->s, u->parent->s, u->child[0]->s, u->child[1]->s);
      preorder(u->child[0]);
      preorder(u->child[1]);
  }
  ```

  Note that there could be `nullptr`. Print `0` as the empty node value in this case.

- `opt=2`, print the height of the subtree rooted at that node.
  
  - If not found, `printf("Not found!\n");`
- `opt=3`, after erasing, print the same debugging information mentioned in `opt=1`.
- `opt=4`, print the result
  
  - If the input is invalid (less than $1$ or more than the number of nodes), `printf("Invalid query!\n");`
- `opt=5`, print the result
  
  - If the input is invalid (empty tree), `printf("Invalid query!\n");`

# Samples

```input1
10
1 1
1 2
1 5
1 3
1 4
1 2
1 5
1 3
1 4
1 1
```

```output1
----------#1: 1 1----------
1 0 0 0
----------#2: 1 2----------
1 0 0 2
2 1 0 0
----------#3: 1 5----------
2 0 1 5
1 2 0 0
5 2 0 0
----------#4: 1 3----------
2 0 1 5
1 2 0 0
5 2 3 0
3 5 0 0
----------#5: 1 4----------
2 0 1 4
1 2 0 0
4 2 3 5
3 4 0 0
5 4 0 0
----------#6: 1 2----------
3 0 2 4
2 3 1 2
1 2 0 0
2 2 0 0
4 3 0 5
5 4 0 0
----------#7: 1 5----------
3 0 2 5
2 3 1 2
1 2 0 0
2 2 0 0
5 3 4 5
4 5 0 0
5 5 0 0
----------#8: 1 3----------
3 0 2 5
2 3 1 2
1 2 0 0
2 2 0 0
5 3 4 5
4 5 3 0
3 4 0 0
5 5 0 0
----------#9: 1 4----------
3 0 2 5
2 3 1 2
1 2 0 0
2 2 0 0
5 3 4 5
4 5 3 4
3 4 0 0
4 4 0 0
5 5 0 0
----------#10: 1 1----------
3 0 2 5
2 3 1 2
1 2 0 1
1 1 0 0
2 2 0 0
5 3 4 5
4 5 3 4
3 4 0 0
4 4 0 0
5 5 0 0
```

```input2
See avl_sample2.in
```

```output2
See avl_sample2.out
```

## 评分标准

满分50pts

### Basic: OJ Subtasks (50pts)

- Subtask1: 10pts, $opt=1$
- Subtask2: 10pts, $opt\in\{1,2\}$, and you must first complete Subtask1.
- Subtask3: 10pts, $opt\in\{1,3\}$, and you must first complete Subtask1,2.
- Subtask4: 10pts, $opt\in\{1,4\}$, and you must first complete Subtask1.
- Subtask5: 10pts, $opt\in\{1,5\}$, and you must first complete Subtask1.

### Bonus可选择性完成

1. (5pts) 使用哨兵节点(dummy node)，帮助简化一些边界条件判断。
2. (10pts) 实现迭代器相关的内容，以便支持使用范围for循环的语法遍历AVL树中的每个节点。
3. (10pts) 借助template等语法，使AVL的基础功能（本题中操作1，2，3）和额外功能（如本题中4，5等一类借助树上二分实现的问题求解）分离，让使用者可以在class外自定义节点额外信息和更新策略等。

### 代码规范（-20pts）

此部分为扣分项，扣满 20% 为止。

1. (20%) 使用class或struct实现对AVL tree以及node的封装。
2. (10%) 动态分配内存，不直接使用静态数组。
3. (5%) 变量应在即将使用时才被声明，特别是不应随意使用全局变量（常量除外）。
4. (10%) 如果是属于“实现细节”的数据成员，应当设置为 private。
5. (5%) 使用构造函数初始值列表。
6. (10%) 正确使用 `static` 成员函数、 `const` 成员函数。

另外将在学术诚信方面进行检查，请确保熟悉自己的代码，否则会面临较严厉处罚。

# Compile Directive

```shellscript
g++ foo.cc -o foo -std=c++17 -Wall -Wpedantic -Wextra -Werror -DONLINE_JUDGE -fmax-errors=3 -fdiagnostics-color=always -fsanitize=undefined -fsanitize=address -O2
```
