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
//Rejilla2d.cpp

#include "Rejilla2d.h" 



#include "xc_utils/src/geom/d2/poligonos2d/Cuadrilatero2d.h"
#include "xc_utils/src/geom/matriz_FT.h"
#include "xc_utils/src/geom/trf/Trf2d.h"


//! @brief Constructor.
Rejilla2d::Rejilla2d(void)
  : Superficie2d(), points(1,1) {}

Rejilla2d::Rejilla2d(int numSubdivIJ, int numSubdivJK)
  : Superficie2d(), points(numSubdivIJ,numSubdivJK) {}

Rejilla2d::~Rejilla2d(void)
  {}

//! @brief Return the area of the grid.
GEOM_FT Rejilla2d::getArea(void) const
  { return points.GetArea();  }

//! @briefMoment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Rejilla2d::Ix(void) const
  { return points.Ix(); }

//! @brief Moment of inertia with respect to the center of mass in local coordinates.
GEOM_FT Rejilla2d::Iy(void) const
  { return points.Iy(); }

//! @brief product of inertia with respect to the center of mass in local coordinates.
GEOM_FT Rejilla2d::Pxy(void) const
  { return points.Pxy(); }

//! @brief Return el centro de gravedad de la rejilla.
Pos2d Rejilla2d::getCenterOfMass(void) const
  { return points.getCenterOfMass(); }

//! @brief Return las coordenadas of point i,j.
const matriz_FT &Rejilla2d::GetVertCoords(const size_t &i,const size_t &j) const
  { return points.GetVertCoords(i,j); }

//! @brief Return the point i,j.
Pos2d Rejilla2d::getPoint(const size_t &i,const size_t &j) const
  { return points.getPoint(i,j); }

//! @brief Return el cuadrilátero correspondiente a la celda i,j:
Cuadrilatero2d Rejilla2d::GetQuad(const size_t &i,const size_t &j) const
  { return points.GetQuad(i,j); }

//! @brief Return true if the point belongs to the grid.
bool Rejilla2d::In(const Pos2d &p, const double &tol) const
  { return points.In(p,tol); }

//! @brief Return the maximum value of the i coordinate.
GEOM_FT Rejilla2d::GetMax(unsigned short int i) const
  { return points.GetMax(i); }

//! @brief Return the minimum value of the i coordinate.
GEOM_FT Rejilla2d::GetMin(unsigned short int i) const
  { return points.GetMin(i); }


//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void Rejilla2d::Transforma(const Trf2d &trf2d)
  { points.Transforma(trf2d); }

void Rejilla2d::Print(std::ostream &os) const
  {
    std::cerr << getClassName() << "::" << __FUNCTION__
	      << "; not implemented." << std::endl;
  }
