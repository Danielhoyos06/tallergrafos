#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <utility>
#include <limits>

template <typename TVertex, typename TCost>
class Grafo
{
public:
  using VertexType = TVertex;
  using CostType   = TCost;

  // agrega un vértice y devuelve su índice
  long AddVertex( const TVertex& v );

  // acceso de solo lectura a un vértice
  const TVertex& GetVertex( long id ) const;

  // agrega arista (u -> v) con costo
  void AddEdge( long from, long to, TCost cost );

  // Dijkstra: devuelve el camino mínimo (lista de índices)
  std::vector< long > Dijkstra( long start, long end ) const;

  long VertexCount( ) const { return static_cast<long>( vertices.size( ) ); }

private:
  std::vector< TVertex > vertices;
  // lista de adyacencia: (vecino, costo)
  std::vector< std::vector< std::pair< long, TCost > > > adj;
};

#include "Graph.cxx"   // implementación de los métodos plantilla

#endif
