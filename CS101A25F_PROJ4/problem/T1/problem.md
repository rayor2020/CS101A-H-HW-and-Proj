# Master of Linear Algebra

There are $m$ vectors in $\mathbb{R}^n$, where each vector has a value $c_i$. Each vector consists of only a consecutive interval of standard basis vectors $\mathbf{e}_1,\mathbf{e}_2,\dots,\mathbf{e}_n$. In other words, there exist integers $l_i,r_i$ such that
$$
\mathbf{v}_i=\mathbf{e}_{l_i}+\mathbf{e}_{l_i+1}+\cdots+\mathbf{e}_{r_i},
$$
i.e.
$$
\mathbf{v}_i=(0,\dots,0,\underbrace{1,1,\dots,1}_{\text{from }l_i\text{ to }r_i},0,\dots,0).
$$
It means that the $l_i$-th entry to the $r_i$-th entry of $\mathbf{v}_i$ are $1$, and others are $0$.

You want to select a linearly independent subset $S$ of vectors, maximizing the sum of the values $\sum_{i\in S} c_i$.

**Linear independence:** A set of vectors $\{\mathbf{v}_i : i\in S\}$ is said to be linearly independent if there do not exist scalars $\{a_i : i\in S\}$, not all zero, such that
$$
\sum_{i\in S} a_i \mathbf{v}_i = \mathbf{0}.
$$

You are given $Q$ queries. Each query asks about one vector. For a queried vector $\mathbf{v}_k$, determine whether there exists **at least one** linearly independent subset $S$ that achieves the maximum possible total value and also satisfies $k\in S$. If such a subset exists, output `YES`; otherwise output `NO`.

---

## Input format

- The first line contains two integers $m, n$ separated by space, denoting there are $m$ vectors in $\mathbb{R}^n$. $(1\le m \le 600000, 1\le n\le 200000)$.
- Then follow $m$ lines, the $i$-th of which contains 3 integers $l_i$, $r_i$, $c_i$ separated by space, denoting the $i$-th vector is $\mathbf{v}_i$ and has value $c_i$. $(1\le c_i\le 10^9)$.
- It is guaranteed that for any $i$ and $j$, either $l_i\ne l_j$ or $r_i\ne r_j$ holds.
- The next line contains an integer $Q$, denoting the number of queries.
- The next $Q$ lines each contain one integer $k$, denoting a query on the $k$-th vector.

---

## Output format

Output $Q$ lines. For each query, output `YES` if the queried vector can appear in **some** maximum-value linearly independent subset, otherwise output `NO`.

---

## Examples


### Input

```text
6 4
1 1 10
2 3 15
4 4 5
3 4 30
2 4 21
2 2 31
3
1
4
5

```

### Output
```text
YES
YES
NO
```

### Sample 1 Explanation

The vectors are

$$
\begin{aligned}
\mathbf v_1&=(1,0,0,0),\\
\mathbf v_2&=(0,1,1,0),\\
\mathbf v_3&=(0,0,0,1),\\
\mathbf v_4&=(0,0,1,1),\\
\mathbf v_5&=(0,1,1,1),\\
\mathbf v_6&=(0,1,0,0).
\end{aligned}
$$

Choose four vectors $\left\{\mathbf v_1,\mathbf v_2,\mathbf v_4,\mathbf v_6\right\}$. The answer is $10 + 15 + 30 + 31 = 86$.


