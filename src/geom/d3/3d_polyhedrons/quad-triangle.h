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
/***************************************************************************
quad-triangle.h  -  quad/triangle subdivision
----------------------------------------------------------------------------
begin                : march 2003
copyright            : (C) 2003 by Pierre Alliez - INRIA
email                : pierre.alliez@sophia.inria.fr
***************************************************************************/

#ifndef QUAD_TRIANGLE
#define QUAD_TRIANGLE

#include "modifier_quad_triangle.h"

// Implemented from:
// Stam and Loop. Quad/Triangle Subdivision. 
// Computer Graphics Forum.
// Volume 22, Issue 1, March 2003.

// Another reference is:
// Levin. Polynomial Generation and Quasi-Interpolation 
// in Stationary Non-Uniform Subdivision.
// Computer Aided Geometric Design.
// pages 41-60, volume 20(1), 2003.


template <class Polyhedron,class kernel>
class CSubdivider_quad_triangle
  {
  public:
    typedef typename Polyhedron::HalfedgeDS HalfedgeDS;
    CSubdivider_quad_triangle() {}
    ~CSubdivider_quad_triangle() {}

  public:
    void subdivide_no_smooth(Polyhedron &OriginalMesh,Polyhedron &NewMesh)
      {
        //subdivide
        CModifierQuadTriangle<HalfedgeDS,Polyhedron,kernel> builder(&OriginalMesh);
        NewMesh.delegate(builder);
      }
    void subdivide(Polyhedron &OriginalMesh,
                   Polyhedron &NewMesh,
                   const bool smooth_boundary = true)
      {
        // subdivide, then smooth
        CModifierQuadTriangle<HalfedgeDS,Polyhedron,kernel> builder(&OriginalMesh);
        NewMesh.delegate(builder);
        builder.smooth(&NewMesh,smooth_boundary);
      }
  };


#endif // QUAD_TRIANGLE
