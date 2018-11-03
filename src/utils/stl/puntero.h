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
//puntero.h
#ifndef PUNTERO_H
#define PUNTERO_H

#include <cstdlib>
#include <cassert>
#include <functional>

template <class N>
class puntero
  {
  private:
    N *ptr;
  public:
    puntero(void): ptr(NULL) {}
    puntero(N *const p): ptr(p) {}
    puntero(const puntero<N> &otro): ptr(otro.ptr) {}
    puntero<N> &operator =(N *const p)
       { 
        ptr= p;
        return *this;
      }
    puntero<N> &operator =(const puntero<N> &otro)
      { 
        ptr= otro.ptr;
        return *this;
      }
    ~puntero(void) { ptr= NULL; }
    inline bool nulo(void) const
      { return (ptr==NULL); }
    N &operator *(void) const
      {
        assert(!nulo());
        return *ptr;
      }
    inline operator const N *(void) const
      { return ptr; }
    inline operator N *const(void) const
      { return ptr; }
    inline operator N*(void)
      { return ptr; }
    inline operator const bool(void) const
      { return ptr; }
    inline void put(N *const p)
      { ptr= p; }
    inline N* operator->(void)
      { return ptr; }
    inline const N* operator->(void) const
      { return ptr; }
    inline N *get_ptr(void) const
      { return ptr; }
    inline N *const get_const_ptr(void) const
      { return ptr; }  
    inline bool operator==(const puntero<N> &p2) const
      { return (ptr == p2.ptr); }
    inline bool operator==(const N *const p2) const
      { return (ptr == p2); }
    bool operator!=(const N *const p2) const
      { return (ptr != p2); }      
    friend bool operator ==(const N *const p1,const puntero<N> &p2)
      { return (p1 == p2.ptr); }
    friend bool operator !=(const N *const p1,const puntero<N> &p2)
      { return (p1 == p2.ptr); }
  };

#endif
