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
//aux_any.h
//funciones auxiliares para interpretar variables de tipo boost::any.

#ifndef VAR_TYPES_H
#define VAR_TYPES_H

//Matrices.
#include "xc_basic/src/matrices/ExpressionMatrix.h"
#include "xc_basic/src/matrices/m_double.h"
#include "xc_basic/src/matrices/m_int.h"
#include "xc_basic/src/matrices/m_sizet.h"
#include "xc_basic/src/matrices/Mmatrix.h"
#include "xc_basic/src/matrices/ExpressionMatrix.h"

//Geometría.
#include "xc_utils/src/geom/FT_matrix.h"
#include "xc_utils/src/geom/pos_vec/Vector2d.h"
#include "xc_utils/src/geom/d1/Line2d.h"
#include "xc_utils/src/geom/d1/Segment2d.h"
#include "xc_utils/src/geom/d1/Segment3d.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/pos_vec/VDesliz2d.h"
#include "xc_utils/src/geom/pos_vec/VDesliz3d.h"
#include "xc_utils/src/geom/pos_vec/VFijo2d.h"
#include "xc_utils/src/geom/pos_vec/VFijo3d.h"
#include "xc_utils/src/geom/pos_vec/SVD3d.h"
#include "xc_utils/src/geom/d2/2d_polygons/Polygon2d.h"
#include "xc_utils/src/geom/d2/2d_polygons/PolygonWithHoles2d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos2d.h"
#include "xc_utils/src/geom/d1/Polyline2d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos3d.h"
#include "xc_utils/src/geom/pos_vec/Pos2d.h"
#include "xc_utils/src/geom/pos_vec/Pos3d.h"
#include "xc_utils/src/geom/d1/Line3d.h"
#include "xc_utils/src/geom/d2/Plane.h"
#include "xc_utils/src/geom/d2/Circle2d.h"
#include "xc_utils/src/geom/d3/HalfSpace3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/Poliedro3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/Tetraedro3d.h"
#include "xc_utils/src/geom/d3/3d_polyhedrons/BlockPyramid.h"
#include "xc_utils/src/geom/sis_coo/SisCooRect2d3d.h"
#include "xc_utils/src/geom/sis_ref/Ref2d3d.h"

#endif
