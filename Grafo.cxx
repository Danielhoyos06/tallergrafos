// Grafo.cxx
#ifndef GRAFO_CXX
#define GRAFO_CXX

#include <queue>
#include <algorithm>

// ---------------- Métodos de Grafo ----------------

template <typename TVertex, typename TCost>
long Grafo<TVertex,TCost>::AddVertex(const TVertex& v)
{
  vertices.push_back(v);
  adj.emplace_back();
  return static_cast<long>(vertices.size() - 1);
}

template <typename TVertex, typename TCost>
const TVertex& Grafo<TVertex,TCost>::GetVertex(long id) const
{
  return vertices[id];
}

template <typename TVertex, typename TCost>
void Grafo<TVertex,TCost>::AddEdge(long from, long to, TCost cost)
{
  adj[from].push_back(std::make_pair(to, cost));
}

template <typename TVertex, typename TCost>
std::vector<long> Grafo<TVertex,TCost>::Dijkstra(long start, long end) const
{
  const TCost INF = std::numeric_limits<TCost>::infinity();
  std::vector<TCost> dist(vertices.size(), INF);
  std::vector<long> parent(vertices.size(), -1);

  using Node = std::pair<TCost, long>;
  std::priority_queue<Node, std::vector<Node>, std::greater<Node>> pq;

  dist[start] = 0;
  pq.push(std::make_pair(0, start));

  while (!pq.empty())
  {
    Node cur = pq.top();
    pq.pop();
    TCost d = cur.first;
    long u = cur.second;

    if (d > dist[u]) continue;
    if (u == end) break;

    for (const auto& edge : adj[u])
    {
      long v = edge.first;
      TCost w = edge.second;
      if (dist[u] + w < dist[v])
      {
        dist[v] = dist[u] + w;
        parent[v] = u;
        pq.push(std::make_pair(dist[v], v));
      }
    }
  }

  std::vector<long> path;
  if (dist[end] == INF) return path;

  for (long v = end; v != -1; v = parent[v])
    path.push_back(v);
  std::reverse(path.begin(), path.end());
  return path;
}

#endif // GRAFO_CXX
