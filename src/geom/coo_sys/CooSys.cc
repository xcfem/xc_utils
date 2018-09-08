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
//CooSys.cc

#include "CooSys.h"
#include "../pos_vec/Pos3d.h"

#include "xc_basic/src/text/text_string.h"
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"


//! @brief Constructor.
CooSys::CooSys(const size_t &ne,const size_t &dim)
  : ProtoGeom(), rot(ne,dim) 
  { identidad(); }

//! @brief Row-normalize matrix.
void CooSys::normaliza(void)
  {
    if(!rot.Nulo())
      NormalizeRows(rot);
    else
      std::cerr << getClassName() << "::" << __FUNCTION__
                << rot << " es nula." << std::endl;
  }
//! @brief Make the base orthogonal.
void CooSys::ortogonaliza(void)
  {
    const size_t ne= numberOfAxis();
    if(ne==1)
      return;
    else //2 o 3 dimensions.
      {
        const FT_matrix i= rot.getRow(1);
        const FT_matrix j= rot.getRow(2);
        const GEOM_FT imod2= i.Abs2();
        if(imod2<geom_epsilon2)
          {
	    std::cerr << getClassName() << "::" << __FUNCTION__
	              << "; orthogonalize: unit vector i= " << i
                      << " is too small (" << imod2 << ")." << std::endl;
            return;
          }
        else
          {
            const GEOM_FT alpha= -(dot(j,i))/imod2;
            const FT_matrix nj= j+alpha*i;
            putRow(2,nj);
	  }
        if(ne>2) //3 dimensiones.
          {
            const FT_matrix nk= i ^ getRow(2);
            putRow(3,nk);
          }
      }
  }
//! @brief Makes the base orthonormal.
void CooSys::ortonormaliza(void)
  {
    ortogonaliza();
    normaliza();
  }
//! @brief Hace coincidir el sistema de coordenadas con el correspondiente global.
//! es decir:
//! - Si es un sistema de coordenadas unidimensional lo hace coincidir con el axis 1 of the global system.
//! - Si es bidimensional, lo hace coincidir con el formado by the axis 1 and 2 of the global system.
//! - Si es tridimensional, lo hace coincidir con el sistema global.
void CooSys::identidad(void)
  {
    rot.Con(0);
    for(size_t i=1;i<=rot.getNumberOfRows();i++)
      rot(i,i)= 1;
  }
//! @brief Assigns the (i,j) component of the matrix.
void CooSys::put(const size_t &i,const size_t &j,const GEOM_FT &rot_ij)
  { rot(i,j)= rot_ij; }

//! @brief Return the matrix i row.
FT_matrix CooSys::getRow(const size_t &i) const
  {
    assert(i<=numberOfAxis());
    return rot.getRow(i);
  }
//! @brief Return true if the vectors are normalized.
bool CooSys::EsNormal(void) const
  {
    const size_t ne= numberOfAxis();
    for(size_t i=1;i<=ne;i++)
      {
        const GEOM_FT imod= rot.getRow(i).Abs2();
        if((imod-1)> geom_epsilon)
          return false;
      }
    return true;
  }

//! @brief Return verdadero si el sistema de coordenadas es dextrógiro.
bool CooSys::EsDextrogiro(void) const
  {
    if(numberOfAxis()<3)
      return true;
    else
      {
        if(rot.getNumberOfColumns()<3)
          return true;
        else
          {
            const FT_matrix i= getRow(1).GetTrn();
            const FT_matrix j= getRow(2).GetTrn();
            const FT_matrix ivectj= i^j;
            return (dot(getRow(3),ivectj)>0);
          }
      }
  }

//! @brief Return verdadero si los vectores son ortogonales.
bool CooSys::EsOrtogonal(void) const
  {
    const size_t ne= numberOfAxis();
    if(ne<2)
      return true;
    else
      if(ne<3)
        return (::Abs(dot(rot.getRow(1),rot.getRow(2).GetTrn()))<geom_epsilon);
      else
        {
          if(::Abs(dot(rot.getRow(1),rot.getRow(2).GetTrn()))>geom_epsilon)
            return false;
          if(::Abs(dot(rot.getRow(1),rot.getRow(3).GetTrn()))>geom_epsilon)
            return false;
          if(::Abs(dot(rot.getRow(2),rot.getRow(3).GetTrn()))>geom_epsilon)
            return false;
        }
    return true;
  }

//! @brief Return verdadero si los vectores son unitarios y ortogonales.
bool CooSys::EsOrtonormal(void) const
  { return (EsOrtogonal() && EsNormal()); }

//! @brief Set the i row of the matrix.
void CooSys::putRow(const size_t &axis,const FT_matrix &v)
  { rot.putRow(axis,v); }
//! @brief Return the matrix que transforma un vector expresado
//! en locales al mismo vector expresado en globales.
FT_matrix CooSys::TransAGlobal(void) const
  { return rot.GetTrn(); }
//! @brief Return the matrix que transforma un vector expresado
//! en globales al mismo vector expresado en locales.
FT_matrix CooSys::TransDeGlobal(void) const
  { return rot; }
//! @brief Return the transformation matrix desde este sistema a dest.
FT_matrix CooSys::GetTransA(const CooSys &dest) const
  { return (dest.rot*TransAGlobal()); }

//! @brief Return las componentes en coordenadas globales del vector v 
//! being passed as parameter expresado en coordenadas locales.
FT_matrix CooSys::GetCooGlobales(const FT_matrix &v) const
  { return TransAGlobal()*v; }
//! @brief Return las componentes en coordenadas locales del vector v 
//! being passed as parameter expresado en coordenadas globales.
FT_matrix CooSys::GetCooLocales(const FT_matrix &v) const
  { return TransDeGlobal()*v; }

//! @brief Prints the matrix.
void CooSys::Print(std::ostream &os) const
  { os << rot; }

std::ostream &operator<<(std::ostream &os,const CooSys &sc)
  {
    sc.Print(os);
    return os;
  }
