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
//TablaSegnales.h

#ifndef TABLASEGNALES_H
#define TABLASEGNALES_H

#include <map>
#include <string>


template<class T>
class TablaSegnales : public std::map<std::string,T,std::less<std::string> >
  {
  public:
    typedef std::map<std::string,T,std::less<std::string> > tabla_segnales;
    typedef typename tabla_segnales::iterator iterator;
    typedef typename tabla_segnales::const_iterator const_iterator;

    TablaSegnales(void) : tabla_segnales() {}
    inline T *CalcDir(const std::string &nmb)
      {
        iterator i= tabla_segnales::find(nmb);
        T *retval= (i != this->end()) ? &((*i).second) : NULL;
        return retval;
      }
    inline T *Nueva(const T &t)
      { return &((*this)[t.getName()]= t); }
  };
#endif
