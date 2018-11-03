//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//OpTrigonometricas.h

#ifndef OPTRIGONOMETRICAS_H
#define OPTRIGONOMETRICAS_H

#include "OpUnario.h"
#include "nombres_operadores.h"

class OpPi : public OpUnario
  {
    
  public:
    OpPi(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpPi; }
    virtual const Operando &Opera(const Operando *v1= NULL,const Operando *v2= NULL) const;
  };

class OpSin : public OpUnario
  {
    
  public:
    OpSin(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpSin; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpCos : public OpUnario
  {
    
  public:
    OpCos(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpCos; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpTan : public OpUnario
  {
    
  public:
    OpTan(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpTan; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

class OpAtan : public OpUnario
  {
    
  public:
    OpAtan(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpAtan; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };

//! @brief Función secante sec(x)= 1/cos(x)
class OpSec : public OpUnario
  {
    
  public:
    OpSec(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpSec; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
  };

//! @brief Función cosecante cosec(x)= 1/sin(x)
class OpCosec : public OpUnario
  {
    
  public:
    OpCosec(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpCosec; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
  };

//! @brief Función cotangente cotg(x)= 1/tan(x)
class OpCotg : public OpUnario
  {
    
  public:
    OpCotg(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpCotg; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
  };

//! @brief Función que convierte grados sexagesimales en radianes deg2rad(x)= pi/180*x
class OpDeg2Rad : public OpUnario
  {
    
  public:
    OpDeg2Rad(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpDeg2Rad; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };


//! @brief Función que convierte radianes en grados sexagesimales rad2deg(x)= 180/pi*x
class OpRad2Deg : public OpUnario
  {
    
  public:
    OpRad2Deg(void) : OpUnario() {}
    inline virtual const std::string &getName(void) const
      { return nmbOpRad2Deg; }
    virtual const Operando &Opera(const Operando *,const Operando *v2= NULL) const;
    virtual Rama Diferencia(const Variable &,const Rama &r) const;
  };


#endif
