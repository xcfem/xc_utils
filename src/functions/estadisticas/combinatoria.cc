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
//Combinatoria.cc

#include "combinatoria.h"

unsigned long long factorial(const unsigned int &n)
  {
    register unsigned long long i,f=1;
    for(i= 2;i<=n;i++)
      f*=i;
    return f;
  }

unsigned long long coeficiente_binomial(const unsigned int &n,const unsigned int &k)
  //Devuelve el valor del coeficiente binomial C(n,k):
  //              n!
  //  C(n,k)= -----------
  //           k!.(n-k)!
  {
    if((n==k) || (k==0)) return 1;
    register unsigned long long i,num=n,denom;
    denom= factorial(n-k);
    for(i=n-1;i>k;i--)
      num*=i;
    return num/denom;
  }

