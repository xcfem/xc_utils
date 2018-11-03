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
//NmbVars.cc

#include "NmbVars.h"

void NmbVars::PutStr(const std::string &str)
  {
    short unsigned int i,mx= std::min(this->size(),str.size());
    for(i=0;i<mx;i++) (*this).at(i)= str[i];
  }
NmbVars NmbVars::Combina(const NmbVars &n) const
//Devuelve la union de los conjuntos de variables
//de this y de n.
  {
    short unsigned int i,sz;
    std::set<char,std::less<char> > c(this->begin(),this->end());
    sz= n.size();
    for (i=0;i<sz;i++) c.insert(n[i]);
    NmbVars comb(c.size());
    i= 0;
    for(std::set<char,std::less<char> >::iterator j=c.begin();j!=c.end();j++)
      comb[i++]= *j;
    return comb;
  }
  
vZ_sui NmbVars::Indices(const NmbVars &n) const
//Devuelve los indices de las variables de n en this.
//Ejemplo:
// *this contiene [x,y,z,t,b,a]
// n contiene: [b,z,y,a]
// el mEtodo devuelve [4,2,1,5]
  {
    short unsigned int i,sz= n.size();
    int indice;
    vZ_sui v(sz);
    for (i=0;i<sz;i++)
      {
        indice = Busca(n[i]);
        if (indice == -1)
          {
	    std::cerr << "La variable: " << n[i] << " no figura en: " << *this;
            abort();
          }
        v.at(i)= indice;
      }
    return v;
  }
