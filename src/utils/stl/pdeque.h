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
//pdeque.h
#ifndef PDQUEUE_H
#define PDQUEUE_H

#include "puntero.h"
#include <deque>
#include <ostream>

template <class N>
class pdeque : public std::deque< puntero<N> >
  {
  public:
    typedef std::deque< puntero<N> > deque_pN;
    typedef typename deque_pN::size_type sz_type;
    typedef puntero<N> pN;

    pdeque(void): deque_pN() {}
    pdeque(sz_type n,const pN &value = pN())
      :deque_pN(n,value) {}
    pdeque(const pdeque<N> &otro): deque_pN(otro) {}
    pdeque<N> &operator =(const pdeque<N> &otro)
      {
        deque_pN::operator=(otro);
        return *this;
      }
    void push_back(N *const x)
      { deque_pN::push_back(pN(x)); }
    friend bool operator==(const pdeque<N> &pv1,const pdeque<N> &pv2)
      { return ((const deque_pN &) pv1 == (const deque_pN &)pv2);}
  };

template <class N>
std::ostream &operator<<(std::ostream &os,const pdeque<N> &pv)
  {
    if(pv.empty())
      return os;
    typename pdeque<N>::const_iterator i= pv.begin();
    os << *i; i++;
    for(;i!=pv.end();i++)
      os << ',' << *i;
    return os;
  }

#endif

