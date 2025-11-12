#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Grafo.h"

// -------------------------------------------------------------------------
// Estructura que representa un punto 3D
struct Point
{
  float X, Y, Z;

  float distanceTo(const Point& b) const
  {
    float x = X - b.X;
    float y = Y - b.Y;
    float z = Z - b.Z;
    return std::sqrt((x * x) + (y * y) + (z * z));
  }
};

// -------------------------------------------------------------------------
// TODO 1: Definir el tipo de dato del grafo
typedef Grafo<Point, float> TGrafo;

// -------------------------------------------------------------------------
int main(int argc, char* argv[])
{
  if (argc < 4)
  {
    std::cerr << "Uso: " << argv[0] << " archivo_malla punto_inicio punto_fin" << std::endl;
    return 1;
  }

  long inicio_id = std::atoi(argv[2]);
  long fin_id = std::atoi(argv[3]);

  // TODO 2: Declarar variable de tipo grafo
  TGrafo g;

  // -----------------------------------------------------------------------
  // Cargar el archivo de malla
  std::ifstream in_mesh_stream(argv[1], std::ifstream::binary);
  if (!in_mesh_stream)
  {
    std::cerr << "Error al leer el archivo \"" << argv[1] << "\"" << std::endl;
    return 1;
  }

  in_mesh_stream.seekg(0, in_mesh_stream.end);
  unsigned long file_length = in_mesh_stream.tellg();
  in_mesh_stream.seekg(0, in_mesh_stream.beg);
  char* buffer = new char[file_length];
  in_mesh_stream.read(buffer, file_length);
  in_mesh_stream.close();
  std::istringstream in_mesh(buffer);

  // -----------------------------------------------------------------------
  // Lectura de vértices (puntos 3D)
  long nPuntos;
  in_mesh >> nPuntos;

  for (long i = 0; i < nPuntos; i++)
  {
    Point p;
    in_mesh >> p.X >> p.Y >> p.Z;

    // TODO 3: Agregar cada punto como vértice del grafo
    g.AddVertex(p);
  }

  // -----------------------------------------------------------------------
  // Lectura de aristas
  long nAristas;
  in_mesh >> nAristas;

  for (long eId = 0; eId < nAristas; eId++)
  {
    long inicio, fin;
    in_mesh >> inicio >> fin;

    // TODO 4: Calcular costo (distancia euclidiana) y agregar arista
    float costo = g.GetVertex(inicio).distanceTo(g.GetVertex(fin));
    g.AddEdge(inicio, fin, costo);
    g.AddEdge(fin, inicio, costo); // Grafo no dirigido
  }

  delete[] buffer;

  // -----------------------------------------------------------------------
  // Verificar índices válidos
  if (
    inicio_id < 0 || inicio_id >= g.VertexCount() ||
    fin_id < 0 || fin_id >= g.VertexCount()
  )
  {
    std::cerr << "Puntos de inicio o fin inválidos." << std::endl;
    return 1;
  }

  // -----------------------------------------------------------------------
  // TODO 5: Encontrar la ruta de costo mínimo e imprimir coordenadas
  std::vector<long> ruta = g.Dijkstra(inicio_id, fin_id);

  if (ruta.empty())
  {
    std::cerr << "No existe un camino entre los puntos dados." << std::endl;
    return 1;
  }

  std::cout << ruta.size() << std::endl;

  for (unsigned int i = 0; i < ruta.size(); ++i)
  {
    const Point& p = g.GetVertex(ruta[i]);
    std::cout << p.X << " " << p.Y << " " << p.Z << std::endl;
  }

  return 0;
}

// eof -
