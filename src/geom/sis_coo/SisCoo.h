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
//SisCoo.h
//Sistema de coordenadas (abstracto).

#ifndef SIS_COO_H
#define SIS_COO_H

#include "../ProtoGeom.h"
#include "xc_utils/src/geom/matriz_FT.h"

//! @ingroup GEOM
//
//!  @defgroup SisCoo Sistemas de coordenadas.
//
//!  @ingroup SisCoo
//! 
//!  @brief Clase base para los sistemas de coordenadas.
//!  
class SisCoo: public ProtoGeom
  {
    matriz_FT rot; //Matriz cuyas filas son los vectores básicos.
  protected:
    virtual bool procesa_comando(CmdStatus &status);
    void identidad(void);
    void put(const size_t &i,const size_t &j,const GEOM_FT &);
    void normaliza(void);
    void ortogonaliza(void);
    void ortonormaliza(void);
    SisCoo(const size_t &,const size_t &);
    SisCoo(const SisCoo &otro)
      : ProtoGeom(otro), rot(otro.rot) {}
    SisCoo &operator=(const SisCoo &otro)
      {
	ProtoGeom::operator=(otro);
        rot= otro.rot;
        return *this;
      }
    virtual SisCoo *Copia(void) const= 0;
  public:
    virtual size_t NumEjes(void) const
      { return rot.getNumFilas(); }
    bool EsNormal(void) const;
    bool EsOrtogonal(void) const;
    bool EsOrtonormal(void) const;
    bool EsDextrogiro(void) const;
    matriz_FT GetFila(const size_t &i) const;
    void PutFila(const size_t &eje,const matriz_FT &v);

    virtual matriz_FT TransAGlobal(void) const;
      //Devuelve la matriz que transforma un vector expresado
      // en locales al mismo vector expresado en globales.
    virtual matriz_FT TransDeGlobal(void) const;
      //Devuelve la matriz que transforma un vector expresado
      // en globales al mismo vector expresado en locales.
    matriz_FT GetTransA(const SisCoo &dest) const;
      //Devuelve la matriz de transformación desde este sistema a dest.
    matriz_FT GetCooGlobales(const matriz_FT &v) const;
    matriz_FT GetCooLocales(const matriz_FT &v) const;

    virtual void Print(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os,const SisCoo &sc);
    virtual any_const_ptr GetProp(const std::string &cod) const;
    inline friend bool operator==(const SisCoo &a,const SisCoo &b)
      { return (a.rot==b.rot); } 
    inline friend bool operator!=(const SisCoo &a,const SisCoo &b)
      { return !(a==b); }
  };

#endif
