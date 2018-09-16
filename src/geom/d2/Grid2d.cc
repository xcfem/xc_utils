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
//Grid2d.cpp

#include "Grid2d.h" 



#include "xc_utils/src/geom/d2/2d_polygons/Quadrilateral2d.h"
#include "xc_utils/src/geom/FT_matrix.h"
#include "xc_utils/src/geom/trf/Trf2d.h"


//! @brief Constructor.
Grid2d::Grid2d(void)
  : Surface2d(), points(1,1) {}

//! @brief Constructor.
Grid2d::Grid2d(int numSubdivIJ, int numSubdivJK)
  : Surface2d(), points(numSubdivIJ,numSubdivJK) {}

Grid2d::~Grid2d(void)
  {}

//! @brief Return the area of the grid.
GEOM_FT Grid2d::getArea(void) const
  { return points.GetArea();  }

//! @briefMoment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Grid2d::Ix(void) const
  { return points.Ix(); }

//! @brief Moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Grid2d::Iy(void) const
  { return points.Iy(); }

//! @brief product of inertia with respect to the center of mass in local coordinates.
GEOM_FT Grid2d::Pxy(void) const
  { return points.Pxy(); }

//! @brief Return the center of mass.
Pos2d Grid2d::getCenterOfMass(void) const
  { return points.getCenterOfMass(); }

//! @brief Return las coordenadas of point i,j.
const FT_matrix &Grid2d::GetVertCoords(const size_t &i,const size_t &j) const
  { return points.GetVertCoords(i,j); }

//! @brief Return the point i,j.
Pos2d Grid2d::getPoint(const size_t &i,const size_t &j) const
  { return points.getPoint(i,j); }

//! @brief Return the i,j cell quad:
Quadrilateral2d Grid2d::GetQuad(const size_t &i,const size_t &j) const
  { return points.GetQuad(i,j); }

//! @brief Return true if the point belongs to the grid.
bool Grid2d::In(const Pos2d &p, const double &tol) const
  { return points.In(p,tol); }

//! @brief Return the maximum value of the i coordinate.
GEOM_FT Grid2d::GetMax(unsigned short int i) const
  { return points.GetMax(i); }

//! @brief Return the minimum value of the i coordinate.
GEOM_FT Grid2d::GetMin(unsigned short int i) const
  { return points.GetMin(i); }


//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void Grid2d::Transforma(const Trf2d &trf2d)
  { points.Transforma(trf2d); }

void Grid2d::Print(std::ostream &os) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
  }
