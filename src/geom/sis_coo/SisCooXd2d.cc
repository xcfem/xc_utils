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
//! Los ejes corresponden con los del sistema global.
SisCooXd2d::SisCooXd2d(const size_t &ne)
  : SisCoo(ne,2) { identidad(); }
//! @brief Define un sistema de coordenadas de dimensión ne
//! en un espacio de dimensión 2. ver SisCooXd2d::VectorEjeX.
SisCooXd2d::SisCooXd2d(const size_t &ne,const VGlobal &vX)
  : SisCoo(ne,2) //Eje 1 paralelo a Vx.
  { VectorEjeX(vX); }
//! @brief Define un sistema de coordenadas de dimensión ne
//! en un espacio de dimensión 2. ver SisCooXd2d::VectorEjeX.
SisCooXd2d::SisCooXd2d(const size_t &ne,const PGlobal &o,const PGlobal &p)
  : SisCoo(ne,2)
  { VectorEjeX(p-o); }

void SisCooXd2d::PutFila(const size_t &eje,const VGlobal &v)
  { SisCoo::PutFila(eje,traspuesta(v.GetMatriz())); }
SisCooXd2d::DGlobal SisCooXd2d::GetDirEje(const size_t &eje) const
  { return DGlobal(GetVDirEje(1)); }
//! @brief Devuelve el vector dirección del eje que se pasa como parámetro.
SisCooXd2d::VGlobal SisCooXd2d::GetVDirEje(const size_t &eje) const
  { 
    const matriz_FT fila= GetFila(eje);
    return VGlobal(fila(1,1),fila(1,2));
  }
SisCooXd2d::VGlobal SisCooXd2d::GetCooGlobales(const matriz_FT &v) const
//Devuelve las componentes del vector v 
//que se pasa como parámetro expresado en coordenadas locales
//expresado en coordenadas globales.
  {
    const matriz_FT tmp= SisCoo::GetCooGlobales(v);
    return VGlobal(tmp(1),tmp(2)); 
  }
matriz_FT SisCooXd2d::GetCooLocales(const SisCooXd2d::VGlobal &v) const
  { return SisCoo::GetCooLocales(v.GetMatriz()); }

//! @brief Hace que el vector básico 1 tenga la dirección
//! y sentido del que se pasa como parámetro. Si el sistema es
//! de dimensión 2 el vector básico 2 es perpendicular al
//! primero en sentido antihorario.
void SisCooXd2d::VectorEjeX(const VGlobal &vX)
  {
    if(vX.Nulo())
      {
	std::cerr << "SisCooXd2d::VectorEjeX: El vector: " 
             << vX << " es nulo. No se hicieron cambios"
             << std::endl;
        return;
      }
    const VGlobal i_= vX.Normalizado();
    PutFila(1,i_);
    if(NumEjes()>1)
      PutFila(2,i_.Perpendicular(CGAL::COUNTERCLOCKWISE));
  }
