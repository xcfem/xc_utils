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
//SVD2d.h
//Sistema de vectores deslizantes.

#ifndef SVD2D_H
#define SVD2D_H

#include "../ProtoGeom.h"
#include "Vector2d.h"
#include "Pos2d.h"

class VDesliz2d;
class Recta2d;
class Plano2d;
class Ref2d2d;

//! @ingroup GEOM
//
//! @brief Sistema de vectores deslizantes.
class SVD2d: public ProtoGeom
  {
    Pos2d org; //Punto al que se refiere el momento.
    Vector2d resul; //Resultante.
    GEOM_FT mom; //Momento respecto a org;
  public:
    SVD2d(const Pos2d &O= Pos2d(),const Vector2d &R= Vector2d(),const GEOM_FT &Mo= 0.0)
      : org(O), resul(R), mom(Mo) {}
    SVD2d(const SVD2d &otro)
      : org(otro.org),resul(otro.resul),mom(otro.mom) {}
    SVD2d(const VDesliz2d &v);
    const SVD2d &operator=(const SVD2d &otro)
      {
        org= otro.org;
        resul= otro.resul;
        mom= otro.mom;
        return *this;
      }
    Pos2d GetOrg(void) const
      { return org; }
    //Resultante y momento.
    Vector2d getResultante(void) const
      { return resul; }
    Vector2d getResultante(const Ref2d2d &ref) const;
    GEOM_FT getMomento(void) const
      { return mom; }
    GEOM_FT getMomento(const Pos2d &P) const;
    bool Nulo(void) const;
    void Neg(void)
      {
        resul= -resul;
        mom= -mom;
      }
    SVD2d ReduceA(const Pos2d &Q);

    SVD2d &operator+=(const VDesliz2d &v);
    SVD2d &operator-=(const VDesliz2d &v);
    SVD2d &operator+=(const SVD2d &s);
    SVD2d &operator-=(const SVD2d &s);
    SVD2d &operator*=(const GEOM_FT &d);
    friend SVD2d operator+(const SVD2d &s1,const SVD2d &s2)
      {
        SVD2d retval(s1);
        retval+=s2;
        return retval;
      }
    friend SVD2d operator-(const SVD2d &s1,const SVD2d &s2)
      {
        SVD2d retval(s1);
        retval-=s2;
        return retval;
      }
    friend SVD2d operator*(const GEOM_FT &d, const SVD2d &s)
      {
        SVD2d retval(s);
        return retval*=d;
      }
    friend SVD2d operator*(const SVD2d &s,const GEOM_FT &d)
      { return d*s; }
    void Print(std::ostream &os) const;
    void PrintLtx(std::ostream &,const std::string &ud_long= " m",const GEOM_FT &f_long=1.0, const std::string &ud_f= " N",const GEOM_FT &f_f=1.0) const;
    friend std::ostream &operator<<(std::ostream &os, const SVD2d &svd2d)
      {
        svd2d.Print(os);
        return os;
      }
  };

inline SVD2d operator+(const VDesliz2d &v1,const VDesliz2d &v2)
  {
    SVD2d suma(v1);
    suma+=v2;
    return suma;
  }
inline SVD2d operator+(const SVD2d &s,const VDesliz2d &v)
  {
    SVD2d suma(s);
    suma+=v;
    return suma;
  }
inline SVD2d operator+(const VDesliz2d &v,const SVD2d &s)
  { return s+v; }
inline SVD2d operator-(const SVD2d &svd2d)
  {
    SVD2d retval(svd2d);
    retval.Neg();
    return retval;
  }

#endif
