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
//SisCoo.cc

#include "SisCoo.h"
#include "../pos_vec/Pos3d.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"
#include "xc_utils/src/base/any_const_ptr.h"

//! @brief Define un sistema de coordenadas de ne dimensiones
//! en un espacio de dimensión dim.
SisCoo::SisCoo(const size_t &ne,const size_t &dim)
  : ProtoGeom(), rot(ne,dim) 
  { identidad(); }
//! @brief Hace que las filas de la matriz sean vectores unitarios.
void SisCoo::normaliza(void)
  {
    if(!rot.Nulo())
      NormalizaFilas(rot);
    else
      std::cerr << "SisCoo::normaliza; la matriz de transformación: "
                << rot << " es nula." << std::endl;
  }
//! @brief Hace que la base sea ortogonal
void SisCoo::ortogonaliza(void)
  {
    const size_t ne= NumEjes();
    if(ne==1)
      return;
    else //2 o 3 dimensiones.
      {
        const matriz_FT i= rot.GetFila(1);
        const matriz_FT j= rot.GetFila(2);
        const GEOM_FT imod2= i.Abs2();
        if(imod2<geom_epsilon2)
          {
	    std::cerr << " SisCoo::ortogonaliza; el vector unitario i= " << i
                      << " es demasiado pequeño (" << imod2 << ")." << std::endl;
            return;
          }
        else
          {
            const GEOM_FT alpha= -(dot(j,i))/imod2;
            const matriz_FT nj= j+alpha*i;
            PutFila(2,nj);
	  }
        if(ne>2) //3 dimensiones.
          {
            const matriz_FT nk= i ^ GetFila(2);
            PutFila(3,nk);
          }
      }
  }
//! @brief Hace que la base sea ortonormal
void SisCoo::ortonormaliza(void)
  {
    ortogonaliza();
    normaliza();
  }
//! @brief Hace coincidir el sistema de coordenadas con el correspondiente global.
//! es decir:
//! - Si es un sistema de coordenadas unidimensional lo hace coincidir con el eje 1 del sistema global.
//! - Si es bidimensional, lo hace coincidir con el formado por los ejes 1 y 2 del sistema global.
//! - Si es tridimensional, lo hace coincidir con el sistema global.
void SisCoo::identidad(void)
  {
    rot.Con(0);
    for(size_t i=1;i<=rot.getNumFilas();i++)
      rot(i,i)= 1;
  }
//! @brief Asigna un valor al elemento (i,j) de la matriz.
void SisCoo::put(const size_t &i,const size_t &j,const GEOM_FT &rot_ij)
  { rot(i,j)= rot_ij; }
//! @brief Lee los miembros desde archivo.
bool SisCoo::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(SisCoo) Procesando comando: " << cmd << std::endl;
    if(cmd == "rot")
      {
        const std::string &args= status.Parser().GetArgs();
        std::vector<int> indices= crea_vector_int(args);
        const size_t nc= indices.size(); //no. de índices.
        if(nc!=2)
	  std::cerr << "SisCoo::procesa_comando; error procesando comando: "
                    << cmd << " se leyeron " << nc
                    << " índices, se esperaban 2." << std::endl;
        if(rot.CheckIndices(indices[0],indices[1]))
          rot(indices[0],indices[1])= double_to_FT(interpretaDouble(status.GetString()));
        else
          std::cerr << "SisCoo::procesa_comando; indices: '"
                    << args << "' fuera de rango." << std::endl;
        return true;
      }
    else
      return ProtoGeom::procesa_comando(status);
  }
//! @brief Devuelve la fila i de la matriz.
matriz_FT SisCoo::GetFila(const size_t &i) const
  {
    assert(i<=NumEjes());
    return rot.GetFila(i);
  }
//! @brief Devuelve verdadero si los vectores son unitarios.
bool SisCoo::EsNormal(void) const
  {
    const size_t ne= NumEjes();
    for(size_t i=1;i<=ne;i++)
      {
        const GEOM_FT imod= rot.GetFila(i).Abs2();
        if((imod-1)> geom_epsilon)
          return false;
      }
    return true;
  }

//! @brief Devuelve verdadero si el sistema de coordenadas es dextrógiro.
bool SisCoo::EsDextrogiro(void) const
  {
    if(NumEjes()<3)
      return true;
    else
      {
        if(rot.getNumCols()<3)
          return true;
        else
          {
            const matriz_FT i= GetFila(1).GetTrn();
            const matriz_FT j= GetFila(2).GetTrn();
            const matriz_FT ivectj= i^j;
            return (dot(GetFila(3),ivectj)>0);
          }
      }
  }

//! @brief Devuelve verdadero si los vectores son ortogonales.
bool SisCoo::EsOrtogonal(void) const
  {
    const size_t ne= NumEjes();
    if(ne<2)
      return true;
    else
      if(ne<3)
        return (::Abs(dot(rot.GetFila(1),rot.GetFila(2).GetTrn()))<geom_epsilon);
      else
        {
          if(::Abs(dot(rot.GetFila(1),rot.GetFila(2).GetTrn()))>geom_epsilon)
            return false;
          if(::Abs(dot(rot.GetFila(1),rot.GetFila(3).GetTrn()))>geom_epsilon)
            return false;
          if(::Abs(dot(rot.GetFila(2),rot.GetFila(3).GetTrn()))>geom_epsilon)
            return false;
        }
    return true;
  }

//! @brief Devuelve verdadero si los vectores son unitarios y ortogonales.
bool SisCoo::EsOrtonormal(void) const
  { return (EsOrtogonal() && EsNormal()); }

//! @brief Asigna la fila i de la matriz.
void SisCoo::PutFila(const size_t &eje,const matriz_FT &v)
  { rot.PutFila(eje,v); }
//! @brief Devuelve la matriz que transforma un vector expresado
//! en locales al mismo vector expresado en globales.
matriz_FT SisCoo::TransAGlobal(void) const
  { return rot.GetTrn(); }
//! @brief Devuelve la matriz que transforma un vector expresado
//! en globales al mismo vector expresado en locales.
matriz_FT SisCoo::TransDeGlobal(void) const
  { return rot; }
//! @brief Devuelve la matriz de transformación desde este sistema a dest.
matriz_FT SisCoo::GetTransA(const SisCoo &dest) const
  { return (dest.rot*TransAGlobal()); }

//! @brief Devuelve las componentes en coordenadas globales del vector v 
//! que se pasa como parámetro expresado en coordenadas locales.
matriz_FT SisCoo::GetCooGlobales(const matriz_FT &v) const
  { return TransAGlobal()*v; }
//! @brief Devuelve las componentes en coordenadas locales del vector v 
//! que se pasa como parámetro expresado en coordenadas globales.
matriz_FT SisCoo::GetCooLocales(const matriz_FT &v) const
  { return TransDeGlobal()*v; }

//! @brief Imprime la matriz.
void SisCoo::Print(std::ostream &os) const
  { os << rot; }

//! \brief Devuelve la propiedad del objeto que tiene por código la cadena que se pasa
//! como parámetro.
//!
//! Soporta los códigos:
//! matriz: Devuelve la matriz cuyas filas son los vectores unitarios del sistema de coordenadas.
any_const_ptr SisCoo::GetProp(const std::string &cod) const
  {
    static bool tmp_gp_bool= false;
    if(cod=="matriz")
      return any_const_ptr(rot);
    if(cod=="es_normal")
      {
        tmp_gp_bool= EsNormal();
        return any_const_ptr(tmp_gp_bool);
      }
    if(cod=="es_ortogonal")
      {
        tmp_gp_bool= EsOrtogonal();
        return any_const_ptr(tmp_gp_bool);
      }
    if(cod=="es_ortonormal")
      {
        tmp_gp_bool= EsOrtonormal();
        return any_const_ptr(tmp_gp_bool);
      }
    if(cod=="es_dextrogiro")
      {
        tmp_gp_bool= EsDextrogiro();
        return any_const_ptr(tmp_gp_bool);
      }
    else
      return ProtoGeom::GetProp(cod);
  }


std::ostream &operator<<(std::ostream &os,const SisCoo &sc)
  {
    sc.Print(os);
    return os;
  }
