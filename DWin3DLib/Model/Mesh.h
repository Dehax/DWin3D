#pragma once

#include "../DWin3DLib_global.h"
#include <vector>
#include <cmath>
#include "Vertex.h"
#include "Face.h"

class DWIN3DLIB_API Mesh
{
public:
    explicit Mesh();
    explicit Mesh(const Mesh &mesh);
    
    inline int numVertices() const
    {
        return m_vertices.size();
    }
    
    inline int numFaces() const
    {
        return m_faces.size();
    }
    
    inline Vertex getVertex(const int index) const
    {
        return m_vertices[index];
    }
    
    inline Face getFace(const int index) const
    {
        return m_faces[index];
    }
    
    void addVertex(const Vertex &vertex);
    void addFace(const Face &face);
    void clearVertices();
    void clearFaces();
    
    inline long double maxLocalScale() const
    {
        return m_maxLocalScale;
    }
    
private:
    std::vector<Vertex> m_vertices;
    std::vector<Face> m_faces;
    long double m_maxLocalScale;
};
