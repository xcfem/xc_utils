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
//SisCooXd3d.cc

#include "SisCooXd3d.h"
#include "../pos_vec/Vector3d.h"
#include "../pos_vec/Dir3d.h"
#include "../pos_vec/Pos3d.h"


//! @brief Define un sistema de coordenadas de dimensión i
//! el x axis tendrá la dirección y sentido del vector que
//! se pasa como parámetro.
SisCooXd3d::SisCooXd3d(const size_t &i,const VGlobal &v)
  : SisCoo(i,3)
  { VectorEjeX(v); }

//! @brief Define un sistema de coordenadas de dimensión i
//! el x axis tendrá la dirección y sentido del vector v1
//! se pasa como parámetro.
SisCooXd3d::SisCooXd3d(const size_t &i,const VGlobal &v1,const VGlobal &v2)
  : SisCoo(i,3)
  { vectores_unitarios(v1,v2,v1 ^ v2); }

SisCooXd3d::SisCooXd3d(const size_t &i,const PGlobal &o,const PGlobal &p)
  : SisCoo(i,3)
  { TwoPoints(o,p); }

SisCooXd3d::SisCooXd3d(const size_t &i,const PGlobal &p1,const PGlobal &p2, const PGlobal &p3)
  : SisCoo(i,3)
  { ThreePoints(p1,p2,p3); }
SisCooXd3d::SisCooXd3d(const size_t &i,const VGlobal &v1,const VGlobal &v2,const VGlobal &v3)
  : SisCoo(i,3)
  { vectores_unitarios(v1,v2,v3); }

void SisCooXd3d::putRow(const size_t &eje,const VGlobal &v)
  { SisCoo::putRow(eje,traspuesta(v.GetMatriz())); }

//! @brief Return the dirección del eje being passed as parameter.
SisCooXd3d::DGlobal SisCooXd3d::GetDirEje(const size_t &eje) const
  { return DGlobal(GetVDirEje(1)); }

//! @brief Return the direction vector del eje being passed as parameter.
SisCooXd3d::VGlobal SisCooXd3d::GetVDirEje(const size_t &eje) const
  { 
    const matriz_FT row= getRow(eje);
    return VGlobal(row(1,1),row(1,2),row(1,3));
  }
//! Return las componentes del vector v 
//! being passed as parameter expresado en coordenadas locales
//! expresado en global coordinates.
SisCooXd3d::VGlobal SisCooXd3d::GetCooGlobales(const matriz_FT &v) const
  {
    const matriz_FT tmp= SisCoo::GetCooGlobales(v);
    return VGlobal(tmp(1),tmp(2),tmp(3)); 
  }
matriz_FT SisCooXd3d::GetCooLocales(const SisCooXd3d::VGlobal &v) const
  { return SisCoo::GetCooLocales(v.GetMatriz()); }
//! Hace que el sistema de coordenadas tenga por vectores unitarios:
//! - El versor correspondiente al vector i_, being passed as parameter.
//! - El versor correspondiente al vector j_, being passed as parameter.
//! - El versor correspondiente al vector k_, being passed as parameter.
//!
//! Comprueba que los tres vectores no sean coplanarios ni paralelos 2 a 2.
void SisCooXd3d::vectores_unitarios(const VGlobal &i_,const VGlobal &j_,const VGlobal &k_)
  {
    if(coplanarios(i_,j_,k_))
      {
        std::cerr << "SisCooXd3d::vectores_unitarios: Los tres vectores: " 
                  << i_ << ' ' << j_ << ' ' << k_ 
                  << " son coplanarios. No se hicieron cambios" << std::endl;
        return;
      }
    if(paralelos(i_,j_))
      {
        std::cerr << "SisCooXd3d::vectores_unitarios: Los vectores: " 
		  << " i= " << i_ << " y j= " << j_
                  << " son paralelos. No se hicieron cambios" << std::endl;
        return;
      }
    if(paralelos(i_,k_))
      {
        std::cerr << "SisCooXd3d::vectores_unitarios: Los vectores: " 
		  << " i= " << i_ << " y k= " << k_
                  << " son paralelos. No se hicieron cambios" << std::endl;
        return;
      }
    if(paralelos(j_,k_))
      {
        std::cerr << "SisCooXd3d::vectores_unitarios: Los vectores: " 
		  << " j= " << j_ << " y k= " << k_
                  << " son paralelos. No se hicieron cambios" << std::endl;
        return;
      }
    const size_t ne= NumEjes();
    const VGlobal e1= Normaliza(i_);
    putRow(1,e1);
    if(ne>1)
      {
        const VGlobal e2= Normaliza(j_);
        putRow(2,e2);
      }
    if(ne>2)
      {
        const VGlobal e3= Normaliza(k_);
        putRow(3,e3);
      }
  }

//! @brief Construye el sistema de coordenadas formado por los vectores:
//! i_ el being passed as parameter.
//! j_ el horizontal perpendicular a i_ (si es único).
//! k_ el producto vectorial de ambos.
void SisCooXd3d::VectorEjeX(const VGlobal &i_)
  {
    if(i_.Nulo())
      {
        std::cerr << getClassName() << "::" << __FUNCTION__
		  << "; vector: " << i_ << " is zero."
	          << " System parallel to global axis will be returned."
                  << std::endl;
        identidad();
      }
    else
      {
        const GEOM_FT imod= Abs2(i_); //Módulo de i.
        //const GEOM_FT tol= imod/1e8;
        VGlobal k_;
        //if( (fabs(i_(1))<tol) && (fabs(i_(2))<tol) ) //Si i es casi paralelo al z axis global.
        if(paralelos(i_,Vector3d(0,0,1))) //Si i es paralelo al z axis global.
          k_= imod*J_3d; //k paralelo a y axis global.
        else
          k_= imod*K_3d; //k paralelo a z axis global.
        const VGlobal j_= k_ ^ i_;
        k_= i_ ^ j_;
        vectores_unitarios(i_,j_,k_); //Normalizamos.
      }
  }

//! @brief Construye el sistema de coordenadas formado por los vectores:
//! i_ el vector op (ver VectorEjeX).
void SisCooXd3d::TwoPoints(const PGlobal &o,const PGlobal &p)
  { VectorEjeX(p-o); }

//! @brief Create the coordinate system with axis oriented as follows:
//! x axis: from o to p1;
//! y axis: normal to x and contained in the plane defined 
//! by the three points and pointing to p2.
void SisCooXd3d::ThreePoints(const PGlobal &o,const PGlobal &p1,const PGlobal &p2)
  {
    if(colineales(o,p1,p2))
      {
        std::cerr << getClassName() << "::" << __FUNCTION__ 
             << o << ' ' << p1 << ' ' << p2 
             << " are collinear. Doing nothing."
             << std::endl;
        return;
      }
    const VGlobal i_= p1 - o;
    VGlobal j_= p2 - o;
    const VGlobal k_= i_ ^ j_;
    j_= k_ ^ i_;
    vectores_unitarios(i_,j_,k_);
  }
