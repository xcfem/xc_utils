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
//IndPol.h
#ifndef INDPOL_H
#define INDPOL_H

#include <iostream>
#include "NmbVars.h"
#include "xc_utils/src/matrices/vectorZ.h"

//Clase de tipo vector de enteros que se emplea para almacenar los exponentes de las
//variables de un polinomio. La correspondencia se establece como sigue:

//    x2 y3 z8 -----> [2,3,8]
typedef vectorZ<short unsigned int> vZ_sui; 

template std::ostream& operator<<(std::ostream &stream,const vZ_sui &v);

class IndPol : public vZ_sui
  {
  public:
    IndPol(void) : vZ_sui(1,(unsigned short int)0) {}
    IndPol(size_type n,const short unsigned int &value = 0) : vZ_sui(n,value) {}
    IndPol(const IndPol &otro) : vZ_sui(otro) {}
    IndPol(const vZ_sui &otro) : vZ_sui(otro) {}
    IndPol &operator =(const IndPol &otro)
      {
        vZ_sui::operator =(otro);
        return *this;
      }
    IndPol &operator =(const vZ_sui &otro)
      {
        vZ_sui::operator =(otro);
        return *this;
      }
    friend IndPol Conv(const NmbVars &dest,const NmbVars &srcVars, const IndPol &srcInd);
    friend IndPol operator +(const IndPol &i1,const IndPol &i2)
    //Devuelve la suma de las potencias.
      {
        assert(i1.size() == i2.size());
        IndPol suma(i1.size());
        suma.Suma(i1,i2);
        return suma;
      }
    friend IndPol operator -(const IndPol &i1,const IndPol &i2)
    //Devuelve la diferencia de las potencias.
      {
        assert(i1.size() == i2.size());      
        IndPol resta(i1.size());
        resta.Resta(i1,i2);
        return resta;
      }
    short unsigned int Grado(void) const
    //Devuelve el grado del termino que tiene por potencias las especificadas
    //en el IndPol.
      { return Sumatorio(0,size()); }
    short unsigned int Grado(size_type j) const
    //Devuelve el grado del termino en la varieble aue tiene por indice j.
      { return (*this)[j]; }
    friend bool operator < (const IndPol &i1,const IndPol &i2);
  };


bool operator < (const IndPol &i1,const IndPol &i2);

IndPol Conv(const NmbVars &destVars,const NmbVars &srcVars, const IndPol &srcInd);
//Convierte el indice Indpol referido al conjunto de variables
//srcVars al conjunto de variables destVars, devolviendo
//este ultimo.

#endif
