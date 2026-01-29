# Strongly Connected Study Groups at ShanghaiTech 

Whenever group $u$ figures out a new homework trick, they immediately share it with group $v$ in WeChat.  
This forms a directed graph $G=(V,E)$ of study groups, where each vertex is a group chat and each directed edge $u\to v$ means information can be forwarded from $u$ to $v$.

We say two groups $u$ and $v$ are **strongly connected** if $u$ can eventually reach $v$ and $v$ can eventually reach $u$ by following directed edges. A **strongly connected component (SCC)** is a maximal set of vertices such that every pair of vertices in the set is strongly connected.

A beautiful high-level fact is: every directed graph can be decomposed into a DAG of SCCs (the **SCC-DAG**) by contracting each SCC into a single “super-node”.

To avoid ambiguity caused by labelling or the order of topological sort, you must output a **unique answer** as specified below.

---

## Task 

Given a directed graph $G=(V,E)$ with vertices labeled $1,2,\dots,n$:

1. Compute all SCCs of $G$.
2. For every vertex $v$, define its **representative**
   $$
   \mathrm{rep}[v] = \min\{x \mid x \text{ is in the same SCC as } v\}.
   $$
   (So each SCC is uniquely named by its smallest vertex.)
3. Build the SCC-DAG where each node is an SCC representative $r$ (i.e., one node per SCC), and there is an edge $r\to s$ if there exists an original edge $u\to v$ such that $\mathrm{rep}[u]=r$, $\mathrm{rep}[v]=s$, and $r\ne s$. Duplicate edges are ignored.
4. Output the **lexicographically smallest topological order** of the SCC-DAG’s nodes (the representatives), i.e., among all valid topological orders, output the one whose sequence is smallest in lexicographic order.

You must run in $O(n+m)$ time up to constant/log factors acceptable for typical SCC + topo implementations (e.g., SCC in $O(n+m)$, then topo with a priority queue).

---

## Input Format

- The first line contains two integers $n$ and $m$, the number of vertices and edges. $1\le n\le 10^5,1\le m\le 10^6$.
- The next $m$ lines each contain two integers $u$ and $v$, denoting a directed edge $u\to v$.

---

## Output Format (Unique)

Let the set of SCC representatives be $\{r_1,r_2,\dots,r_k\}$ (these are exactly the distinct values among $\mathrm{rep}[1..n]$). Output:

1. One integer $k$, the number of SCCs.
2. One line of $n$ integers:
   $$
   \mathrm{rep}[1]\ \mathrm{rep}[2]\ \cdots\ \mathrm{rep}[n].
   $$
3. One line of $k$ integers: the **lexicographically smallest** topological order of SCC representatives.

With this definition, the output is uniquely determined.

---

## Example

### Input
```text
7 9
1 2
2 3
3 1
3 4
4 5
5 6
6 4
6 7
2 4
```

### Output
```text
3
1 1 1 4 4 4 7
1 4 7

```