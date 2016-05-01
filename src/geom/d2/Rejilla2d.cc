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
  : Superficie2d(), puntos(1,1) {}

Rejilla2d::Rejilla2d(int numSubdivIJ, int numSubdivJK)
  : Superficie2d(), puntos(numSubdivIJ,numSubdivJK) {}

Rejilla2d::~Rejilla2d(void)
  {}

//! @brief Devuelve el área de la rejilla.
GEOM_FT Rejilla2d::Area(void) const
  { return puntos.GetArea();  }

//! @briefMomento de inercia respecto al CDG en ejes locales.
GEOM_FT Rejilla2d::Ix(void) const
  { return puntos.Ix(); }

//! @brief Momento de inercia respecto al CDG en ejes locales.
GEOM_FT Rejilla2d::Iy(void) const
  { return puntos.Iy(); }

//! @brief Producto de inercia respecto al CDG en ejes locales.
GEOM_FT Rejilla2d::Pxy(void) const
  { return puntos.Pxy(); }

//! @brief Devuelve el centro de gravedad de la rejilla.
Pos2d Rejilla2d::Cdg(void) const
  { return puntos.GetCdg(); }

//! @brief Devuelve las coordenadas del punto i,j.
const matriz_FT &Rejilla2d::GetVertCoords(const size_t &i,const size_t &j) const
  { return puntos.GetVertCoords(i,j); }

//! @brief Devuelve el punto i,j.
Pos2d Rejilla2d::GetPunto(const size_t &i,const size_t &j) const
  { return puntos.GetPunto(i,j); }

//! @brief Devuelve el cuadrilátero correspondiente a la celda i,j:
Cuadrilatero2d Rejilla2d::GetQuad(const size_t &i,const size_t &j) const
  { return puntos.GetQuad(i,j); }

//! @brief Devuelve verdadero si el punto está dentro de la rejilla.
bool Rejilla2d::In(const Pos2d &p, const double &tol) const
  { return puntos.In(p,tol); }

//! @brief Devuelve el valor maximo de la coordenada i.
GEOM_FT Rejilla2d::GetMax(unsigned short int i) const
  { return puntos.GetMax(i); }

//! @brief Devuelve el valor minimo de la coordenada i.
GEOM_FT Rejilla2d::GetMin(unsigned short int i) const
  { return puntos.GetMin(i); }


//! @brief Aplica al objeto la transformación que se
//! pasa como parámetro.
void Rejilla2d::Transforma(const Trf2d &trf2d)
  { puntos.Transforma(trf2d); }

void Rejilla2d::Print(std::ostream &os) const
  {
    std::cerr << "Rejilla2d::Print, no implementada." << std::endl;
  }
