//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  Este software es libre: usted puede redistribuirlo y/o modificarlo 
//  bajo los términos de la Licencia Pública General GNU publicada 
//  por la Fundación para el Software Libre, ya sea la versión 3 
//  de la Licencia, o (a su elección) cualquier versión posterior.
//
//  Este software se distribuye con la esperanza de que sea útil, pero 
//  SIN GARANTÍA ALGUNA; ni siquiera la garantía implícita 
//  MERCANTIL o de APTITUD PARA UN PROPÓSITO DETERMINADO. 
//  Consulte los detalles de la Licencia Pública General GNU para obtener 
//  una información más detallada. 
//
// Debería haber recibido una copia de la Licencia Pública General GNU 
// junto a este programa. 
// En caso contrario, consulte <http://www.gnu.org/licenses/>.
//----------------------------------------------------------------------------
//Triang3dMesh.h

#ifndef TRIANG3D_MESH_H
#define TRIANG3D_MESH_H

#include "../d3/poliedros3d/Poliedro3d.h"

class Triangulo3d;
class SoGroup;
class GTSSurface;
class Pos3d;


//! @ingroup GEOM
//
//! @brief 3D Triange mesh.
class Triang3dMesh: public Poliedro3d
  {
    GTSSurface get_gts_surface(void) const;

    friend class Poliedro3d;

  public:
    typedef Poliedro3d::Vertex Vertex;
    typedef Poliedro3d::Facet Facet;
    typedef Poliedro3d::Point_iterator Point_iterator;
    typedef Poliedro3d::Point_const_iterator Point_const_iterator;
    typedef Poliedro3d::Vertex_iterator Vertex_iterator;
    typedef Poliedro3d::Vertex_const_iterator Vertex_const_iterator;
    typedef Poliedro3d::Facet_iterator Facet_iterator;
    typedef Poliedro3d::Facet_const_iterator Facet_const_iterator;
    typedef Poliedro3d::Edge_iterator Edge_iterator;
    typedef Poliedro3d::Halfedge_iterator Halfedge_iterator;
    typedef Poliedro3d::Halfedge_around_facet_circulator Halfedge_around_facet_circulator;
    typedef Poliedro3d::Halfedge_around_vertex_circulator Halfedge_around_vertex_circulator;
    typedef Poliedro3d::Vertex_handle Vertex_handle;
    typedef Poliedro3d::Facet_handle Facet_handle;
    typedef Poliedro3d::Halfedge_handle Halfedge_handle;

  protected:
    Facet_const_iterator find_trihedron(const Pos3d &org,const Pos3d &p,const double &tol) const;

  public:

    Triang3dMesh(void): Poliedro3d() {}
    explicit Triang3dMesh(const Poliedro3d &p)
      : Poliedro3d(p) {}
    Triang3dMesh(const GTSSurface &gts_surf);
    Triang3dMesh(const Triang3dMesh &otro) 
      : Poliedro3d(otro) {}
    Triang3dMesh &operator=(const Triang3dMesh &otro)
      {
	Poliedro3d::operator=(otro);
        return *this;
      }
    virtual GeomObj *clon(void) const
      { return new Triang3dMesh(*this); }

    Triangulo3d GetTrianguloCara(const Facet_const_iterator &f) const;

    Facet_const_iterator findTrihedron(const Pos3d &org,const Pos3d &p,const double &tol) const;

    friend Triang3dMesh GTSSurface2Triang3dMesh(const GTSSurface &gts_surf);
  };

#endif
