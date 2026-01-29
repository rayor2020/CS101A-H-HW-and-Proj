#include <cassert>
#include <optional>

#include "graph.hpp"
#include "problem.hpp"

/// @brief Solve the given difference constraints problem.
/// @param problem
/// @return The solution, or @c std::nullopt if the problem has no solutions.
std::optional<Problem::Solution> solve(const Problem& problem)
{
    // TODO: Your code here.
    if (!problem.hasNegativeConstant()) {
        return Problem::Solution(problem.getNumVars(), 0); // 0 - 0 \leq 任意正数
    }

    // 有负边，使用bf
    size_t numVar = problem.getNumVars();
    Graph g(numVar + 1);

    for (const auto& constraint : problem.getConstraints()) { // 添加边
        g.addEdge(constraint.var2, constraint.var1, constraint.constant);
    }

    for (size_t i = 0; i < numVar; ++i) { // 新增虚拟节点，确保bf能跑
        g.addEdge(numVar, i, 0);
    }

    auto result = g.bellmanFord(numVar);
    if (!result) {
        return std::nullopt; // 负环
    }

    Problem::Solution solution(result->begin(), result->begin() + numVar);
    return solution;
}

int main()
{
    Problem p1(5, { { 0, 1, 0 }, { 0, 4, -1 }, { 1, 4, 1 }, { 2, 0, 5 }, { 3, 0, 4 }, { 3, 2, -1 }, { 4, 2, -3 }, { 4, 3, -3 } });

    // This is a possible solution.
    assert(p1.isFeasible({ -5, -3, 0, -1, -4 }));

    auto sol = solve(p1);
    assert(sol); // The problem has a solution.
    assert(p1.isFeasible(sol.value())); // The solution is correct.

    return 0;
}