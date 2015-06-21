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
//CmdFuncPorPuntos.h
//Entidad para leer matrices.

#ifndef CMDFUNCPORPUNTOS_H
#define CMDFUNCPORPUNTOS_H

#include "EntWOwner.h"
#include "xc_utils/src/geom/d1/func_por_puntos/FuncPorPuntosR_R.h"

//! @ingroup BASE
//
//!  @brief Clase para leer funciones definidas por puntos.
class CmdFuncPorPuntos: public EntWOwner
  {
    FuncPorPuntosR_R f; //!< Función definida por puntos.
  protected:
    void inserta_valores(const std::string &str);
    bool procesa_comando(CmdStatus &status);
  public:
    CmdFuncPorPuntos(EntCmd *owr);
    CmdFuncPorPuntos(EntCmd *owr,const std::string &);
    void fromString(const std::string &);
    void append(const double &x,const double &y); 

    CmdFuncPorPuntos sub(const double &x0,const double &x1) const;
    CmdFuncPorPuntos getNeg(void) const;
    CmdFuncPorPuntos &Neg(void);
    CmdFuncPorPuntos &operator+=(const double &);
    CmdFuncPorPuntos &operator+=(const CmdFuncPorPuntos &);
    CmdFuncPorPuntos &operator-=(const double &);
    CmdFuncPorPuntos &operator-=(const CmdFuncPorPuntos &);
    CmdFuncPorPuntos &operator*=(const double &);
    CmdFuncPorPuntos &operator*=(const CmdFuncPorPuntos &);
    CmdFuncPorPuntos &operator/=(const double &);
    CmdFuncPorPuntos &operator/=(const CmdFuncPorPuntos &);
    CmdFuncPorPuntos integra(const double &x0,const double &x1,const double &delta) const;

    inline double operator()(const double &z) const
      { return f(z); }

    void clear(void);

    any_const_ptr GetProp(const std::string &) const;
  };

CmdFuncPorPuntos operator+(const CmdFuncPorPuntos &,const double &);
CmdFuncPorPuntos operator+(const CmdFuncPorPuntos &,const CmdFuncPorPuntos &);
inline CmdFuncPorPuntos operator+(const double &c,const CmdFuncPorPuntos &f)
  { return f+c;}
inline CmdFuncPorPuntos operator-(const CmdFuncPorPuntos &f,const double &c)
  { return f+(-c); }
inline CmdFuncPorPuntos operator-(const double &c,const CmdFuncPorPuntos &f)
  { return c+f.getNeg();}
CmdFuncPorPuntos operator-(const CmdFuncPorPuntos &,const CmdFuncPorPuntos &);
CmdFuncPorPuntos operator*(const double &,const CmdFuncPorPuntos &);
inline CmdFuncPorPuntos operator*(const CmdFuncPorPuntos &f,const double &c)
  { return c*f; }
CmdFuncPorPuntos operator*(const CmdFuncPorPuntos &,const CmdFuncPorPuntos &);
inline CmdFuncPorPuntos operator/(const CmdFuncPorPuntos &f,const double &c)
  { return (1.0/c)*f; }
CmdFuncPorPuntos operator/(const CmdFuncPorPuntos &,const CmdFuncPorPuntos &);


#endif
