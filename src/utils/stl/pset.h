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
//pset.h
#ifndef PSET_H
#define PSET_H

#include "puntero_srt.h"
#include <set>

template <class N>
struct ptr_menor
 {
   bool operator()(const puntero_srt<N> &s1,const puntero_srt<N> &s2) const
   {
     return s1<s2;
   }
 };

template <class N>
class pset : public std::set<puntero_srt<N>,ptr_menor<N> >
  {
  public:
    typedef puntero_srt<N> ps_N;
    typedef std::set<puntero_srt<N>,ptr_menor<N> > set_psN;
    typedef typename pset<N>::const_iterator c_iterator;
    pset(void): set_psN() {}
    pset(const pset<N> &otro): set_psN(otro) {}
    pset<N> &operator =(const pset<N> &otro)
      {
        set_psN::operator=(otro);
        return *this;
      }
    friend bool operator==(const pset<N> &pv1,const pset<N> &pv2)
      { return (( const set_psN &) pv1 == (const set_psN &)pv2); }
    //friend std::ostream &operator<<(std::ostream &os,const pset<N> &pl);
  };

template <class N>
std::ostream &operator<<(std::ostream &os,const pset<N> &pl)
  {
     typename pset<N>::c_iterator i;
     size_t j= 0,sz = pl.size();
     for (i= pl.begin();i != pl.end();i++)
       {
         os << (*(*i));
         j++;
         if (j < sz) os << ',';
       }
     return os;
  }

#endif
