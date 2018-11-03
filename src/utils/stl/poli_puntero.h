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
//poli_puntero.h
#ifndef POLI_PUNTERO_H
#define POLI_PUNTERO_H

#include "xc_utils/src/utils/stl/puntero.h"

template <class N>
class poli_puntero: public puntero<N>
  {
  private:
    typedef puntero<N> pN;

    operator N*(void)
      { return pN::get_ptr(); }
    N *get_ptr(void) const
      { return pN::get_ptr(); }
    inline void libera(void)
      {
        if(!pN::nulo()) delete get_ptr();
        pN::put(NULL);
      }
    void copia(N *const p)
      {
        libera();
        if(p!=NULL) pN::put(p->Copia());
      }
    void copia(const poli_puntero<N> &otro)
      { copia(otro.get_ptr()); }
    void copia(const N &n)
      {
        libera();
        copia(n.Copia());
      }
  public:

    poli_puntero(void): pN() {}
/*     poli_puntero(const N &n): pN() { copia(n); } */
/*     poli_puntero(N *const p): pN() { copia(p); } */
    poli_puntero(const poli_puntero<N> &otro)
      : pN() { copia(otro); }
    poli_puntero<N> &operator =(N *const p) 
      {
        copia(p);
        return *this;
      }
/*     poli_puntero<N> &operator =(const N &n)  */
/*       { */
/*         copia(n); */
/*         return *this; */
/*       } */
/*     poli_puntero<N> &operator =(const pN &otro) */
/*       { */
/*         copia(otro); */
/*         return *this; */
/*       } */
    poli_puntero<N> &operator =(const poli_puntero<N> &otro)
      { 
        copia(otro);
        return *this;
      }
    inline void put(N *const p)
      { copia(p); }
    inline void put(const N &n)
      { copia(n); }
    ~poli_puntero() { libera(); }
  };

template <class N>
class poli_var: public poli_puntero<N>
  {
  };

#endif





