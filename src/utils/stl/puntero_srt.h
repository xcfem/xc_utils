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
//puntero_srt.h
#ifndef PUNTERO_SRT_H
#define PUNTERO_SRT_H

#include "puntero.h"
#include <iostream>

//Puntero con operador menor por defecto.
template <class N>
class puntero_srt : public puntero<N>
  {
  public:
    typedef puntero<N> pN;
    puntero_srt(void): pN() {}
    puntero_srt(N *const p): pN(p) {}
    puntero_srt(const puntero_srt<N> &otro): pN(otro) {}
    puntero_srt<N> &operator =(N *const p)
      {
        pN::operator=(p);
        return *this;
      }
    puntero_srt<N> &operator =(const puntero_srt<N> &otro)
      { 
        pN::operator=(otro);
        return *this;
      }
    ~puntero_srt(void) {}
    bool menor_que(const puntero_srt<N> &p2) const
      {
        if(!this->nulo())
          if(!p2.nulo())
            return (*(this->get_const_ptr()) < *p2.get_const_ptr());
          else
            return false;
        else
          if(!p2.nulo())
            return true;
          else
            return false;
      }
    inline bool operator<(const puntero_srt<N> &p2) const
      { return this->menor_que(p2); }
    inline friend std::ostream &operator <<(std::ostream stream, const puntero_srt<N> &p)
      {
        if (p.ptr != 0)
          stream << *p.ptr;
        else
          stream << '#';
        return stream;
      }
  };

template <class N>
inline bool operator<(const puntero_srt<N> &p1,const puntero_srt<N> &p2)
  { return p1.menor_que(p2); }

#endif

