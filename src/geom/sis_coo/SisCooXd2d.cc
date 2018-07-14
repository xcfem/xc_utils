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
//SisCooXd2d.cc

#include "SisCooXd2d.h"
#include "../pos_vec/Vector2d.h"
#include "../pos_vec/Dir2d.h"
#include "../pos_vec/Pos2d.h"


//! @brief Define un sistema de coordenadas de dimensión ne
//! en un espacio de dimensión 2.
//! The axis are those of the global system.
SisCooXd2d::SisCooXd2d(const size_t &ne)
  : SisCoo(ne,2) { identidad(); }
//! @brief Define un sistema de coordenadas de dimensión ne
//! en un espacio de dimensión 2. ver SisCooXd2d::XAxisVector.
SisCooXd2d::SisCooXd2d(const size_t &ne,const VGlobal &vX)
  : SisCoo(ne,2) //Axis 1 paralelo a Vx.
  { XAxisVector(vX); }
//! @brief Define un sistema de coordenadas de dimensión ne
//! en un espacio de dimensión 2. ver SisCooXd2d::XAxisVector.
SisCooXd2d::SisCooXd2d(const size_t &ne,const PGlobal &o,const PGlobal &p)
  : SisCoo(ne,2)
  { XAxisVector(p-o); }

void SisCooXd2d::putRow(const size_t &axis,const VGlobal &v)
  { SisCoo::putRow(axis,traspuesta(v.getMatrix())); }
SisCooXd2d::DGlobal SisCooXd2d::getAxisDir(const size_t &axis) const
  { return DGlobal(getAxisVDir(1)); }
//! @brief Return the direction vector of the axis being passed as parameter.
SisCooXd2d::VGlobal SisCooXd2d::getAxisVDir(const size_t &axis) const
  { 
    const FT_matrix row= getRow(axis);
    return VGlobal(row(1,1),row(1,2));
  }
SisCooXd2d::VGlobal SisCooXd2d::GetCooGlobales(const FT_matrix &v) const
//Return las componentes del vector v 
//being passed as parameter expresado en coordenadas locales
//expresado en coordenadas globales.
  {
    const FT_matrix tmp= SisCoo::GetCooGlobales(v);
    return VGlobal(tmp(1),tmp(2)); 
  }
FT_matrix SisCooXd2d::GetCooLocales(const SisCooXd2d::VGlobal &v) const
  { return SisCoo::GetCooLocales(v.getMatrix()); }

//! @brief Hace que el vector básico 1 tenga la dirección
//! y sentido del being passed as parameter. Si el sistema es
//! de dimensión 2 el vector básico 2 es perpendicular al
//! primero en sentido antihorario.
void SisCooXd2d::XAxisVector(const VGlobal &vX)
  {
    if(vX.Nulo())
      {
	std::cerr << "SisCooXd2d::XAxisVector: El vector: " 
             << vX << " es nulo. No se hicieron cambios"
             << std::endl;
        return;
      }
    const VGlobal i_= vX.Normalizado();
    putRow(1,i_);
    if(numberOfAxis()>1)
      putRow(2,i_.Perpendicular(CGAL::COUNTERCLOCKWISE));
  }
