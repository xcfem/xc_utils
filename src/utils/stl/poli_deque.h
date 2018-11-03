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
//poli_deque.h
#ifndef POLI_DQUEUE_H
#define POLI_DQUEUE_H

#include "poli_puntero.h"
#include <deque>

template <class N>
class poli_deque : public std::deque< poli_puntero<N> >
  {
  public:
    typedef std::deque< poli_puntero<N> > deque_pN;
    typedef typename deque_pN::size_type sz_type;
    typedef poli_puntero<N> pN;

    poli_deque(void): deque_pN() {}
    poli_deque(sz_type n,const pN &value = pN())
      :deque_pN(n,value) {}
    poli_deque(const poli_deque<N> &otro): deque_pN(otro) {}
    poli_deque<N> &operator =(const poli_deque<N> &otro)
      {
        deque_pN::operator=(otro);
        return *this;
      }
    void push_back(N *const x)
      { 
        pN p;
        p.put(x);
        deque_pN::push_back(p);
       }
    void push_back(const N &n)
      {
        pN p;
        p.put(n);
        deque_pN::push_back(p);
      }
    friend bool operator==(const poli_deque<N> &pv1,const poli_deque<N> &pv2)
      { return ((const deque_pN &) pv1 == (const deque_pN &)pv2);}
  };

template <class N>
std::ostream &operator << (std::ostream &stream,const poli_deque<N> &pv)
  {
    typename poli_deque<N>::const_iterator i;
    for (i= pv.begin();i != pv.end();i++)
      {
       	stream << *i;
	      if (i < (pv.end()-1)) stream << ',';
      }
    return stream;
  }

#endif

