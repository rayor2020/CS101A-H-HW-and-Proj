#include "graph.hpp"

auto Graph::dijkstra(VertexID source) const -> std::vector<Weight>
{
    // FIXME: This is a naive O(V^2) implementation. Overwrite it to make it run
    // within O(ElogV) time, which is more efficient when E = o(V^2/logV).
    std::vector<Weight> distance(numVertices(), infinity);
    // std::vector<bool> done(numVertices(), false);
    distance[source] = 0;
    /*for (auto rest = numVertices(); rest > 0; --rest) {
        VertexID current = -1;
        Weight mindistance = infinity;
        for (VertexID i = 0; i != numVertices(); ++i)
          if (!done[i] && distance[i] < mindistance) {
            current = i;
            mindistance = distance[i];
          }
        done[current] = true;
        for (auto [to, weight] : mAdjacent[current])
          if (distance[current] + weight < distance[to])
            distance[to] = distance[current] + weight;
      }*/
    std::priority_queue<std::pair<Weight, VertexID>, std::vector<std::pair<Weight, VertexID>>, std::greater<std::pair<Weight, VertexID>>> priorQ;
    priorQ.push({ 0, source });

    while (!priorQ.empty()) {
        auto [cost, u] = priorQ.top();
        priorQ.pop();

        for (const auto& [v, w] : mAdjacent[u]) {
            if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                priorQ.push({ distance[v], v });
            }
        }
    }
    return distance;
}

auto Graph::bellmanFord(VertexID source) const
    -> std::optional<std::vector<Weight>>
{
    // TODO: Implement this.
    std::vector<Weight> distance(numVertices(), infinity);
    distance[source] = 0;

    for (size_t i = 1; i < numVertices(); ++i) { // 循环 |V|-1 次
        for (VertexID u = 0; u < numVertices(); ++u) {
            if (distance[u] != infinity) {
                for (const auto& [v, w] : mAdjacent[u]) {
                    if (distance[u] + w < distance[v]) {
                        distance[v] = distance[u] + w;
                    }
                }
            }
        }
    }

    for (VertexID u = 0; u < numVertices(); ++u) { // 检查负环
        if (distance[u] != infinity) {
            for (const auto& [v, w] : mAdjacent[u]) {
                if (distance[u] + w < distance[v]) {
                    return std::nullopt;
                }
            }
        }
    }

    return distance;
}