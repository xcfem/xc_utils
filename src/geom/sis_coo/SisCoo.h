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
#include "xc_utils/src/geom/FT_matrix.h"

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
    FT_matrix rot; //Basis vector matrix (as rows).
  protected:
    void identidad(void);
    void put(const size_t &i,const size_t &j,const GEOM_FT &);
    void normaliza(void);
    void ortogonaliza(void);
    void ortonormaliza(void);
    SisCoo(const size_t &,const size_t &);
    SisCoo(const SisCoo &other)
      : ProtoGeom(other), rot(other.rot) {}
    SisCoo &operator=(const SisCoo &other)
      {
	ProtoGeom::operator=(other);
        rot= other.rot;
        return *this;
      }
    virtual SisCoo *Copia(void) const= 0;
  public:
    virtual size_t numberOfAxis(void) const
      { return rot.getNumberOfRows(); }
    bool EsNormal(void) const;
    bool EsOrtogonal(void) const;
    bool EsOrtonormal(void) const;
    bool EsDextrogiro(void) const;
    FT_matrix getRow(const size_t &i) const;
    void putRow(const size_t &axis,const FT_matrix &v);

    virtual FT_matrix TransAGlobal(void) const;
      //Return the matrix que transforma un vector expresado
      // en locales al mismo vector expresado en globales.
    virtual FT_matrix TransDeGlobal(void) const;
      //Return the matrix que transforma un vector expresado
      // en globales al mismo vector expresado en locales.
    FT_matrix GetTransA(const SisCoo &dest) const;
      //Return the transformation matrix desde este sistema a dest.
    FT_matrix GetCooGlobales(const FT_matrix &v) const;
    FT_matrix GetCooLocales(const FT_matrix &v) const;

    virtual void Print(std::ostream &os) const;
    friend std::ostream &operator<<(std::ostream &os,const SisCoo &sc);
    inline friend bool operator==(const SisCoo &a,const SisCoo &b)
      { return (a.rot==b.rot); } 
    inline friend bool operator!=(const SisCoo &a,const SisCoo &b)
      { return !(a==b); }
  };

#endif
