//----------------------------------------------------------------------------
//  biblioteca xc_utils; bilioteca de comandos para el intérprete del lenguaje
//  de entrada de datos.
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
//TritrizPos.h
//Vector de matrices de puntos

#ifndef TRITRIZPOS_H
#define TRITRIZPOS_H

#include "MatrizPos.h"
#include "ConstRefCajaTritriz.h"
#include "ConstRefCapaICte.h"
#include "ConstRefCapaJCte.h"
#include "ConstRefCapaKCte.h"
#include "ConstRefFilaI.h"
#include "ConstRefFilaJ.h"
#include "ConstRefFilaK.h"
#include "VarRefCajaTritriz.h"
#include "VarRefCapaICte.h"
#include "VarRefCapaJCte.h"
#include "VarRefCapaKCte.h"
#include "VarRefFilaI.h"
#include "VarRefFilaJ.h"
#include "VarRefFilaK.h"



//! @ingroup GEOM
//
//! @brief Clase base para las «tritrices» de posiciones.
template <class POS>
class TritrizPos: public std::vector<MatrizPos<POS> >
  {
  public:
    typedef MatrizPos<POS> m_pos;
    typedef typename m_pos::reference reference;
    typedef typename m_pos::const_reference const_reference;

    typedef ConstRefCajaTritriz<TritrizPos<POS> > const_ref_caja;
    typedef ConstRefCapaICte<TritrizPos<POS> > const_ref_capa_i_cte;
    typedef ConstRefCapaJCte<TritrizPos<POS> > const_ref_capa_j_cte;
    typedef ConstRefCapaKCte<TritrizPos<POS> > const_ref_capa_k_cte;
    typedef ConstRefFilaI<TritrizPos<POS> > const_ref_fila_i;
    typedef ConstRefFilaJ<TritrizPos<POS> > const_ref_fila_j;
    typedef ConstRefFilaK<TritrizPos<POS> > const_ref_fila_k;

    typedef VarRefCajaTritriz<TritrizPos<POS> > var_ref_caja;
    typedef VarRefCapaICte<TritrizPos<POS> > var_ref_capa_i_cte;
    typedef VarRefCapaJCte<TritrizPos<POS> > var_ref_capa_j_cte;
    typedef VarRefCapaKCte<TritrizPos<POS> > var_ref_capa_k_cte;
    typedef VarRefFilaI<TritrizPos<POS> > var_ref_fila_i;
    typedef VarRefFilaJ<TritrizPos<POS> > var_ref_fila_j;
    typedef VarRefFilaK<TritrizPos<POS> > var_ref_fila_k;

  protected:
    inline m_pos &get_capa(const size_t &capa)
      { return (*this)[capa-1]; }
    inline const m_pos &get_capa(const size_t &capa) const
      { return (*this)[capa-1]; }
  public:
    TritrizPos(const size_t capas= 1): std::vector<m_pos>(capas) {}
    TritrizPos(const size_t capas,const m_pos &m): std::vector<m_pos>(capas,m) {}
    TritrizPos(const m_pos &,const m_pos &,const m_pos &,const m_pos &,const size_t &,const size_t &);
    inline size_t GetCapas(void) const
      { return this->size(); }
    size_t getNumFilas(void) const;
    size_t getNumCols(void) const;
    size_t NumPos(void) const;

    const_ref_caja GetConstRefCaja(size_t capa=1,size_t f=1, size_t c=1) const
      { return const_ref_caja(*this,capa,f,c); }
    const_ref_caja GetConstRefCaja(const RangoTritriz &rango) const
      { return const_ref_caja(*this,rango); }

    const_ref_capa_i_cte GetConstRefCapaICte(size_t capa=1,size_t f=1, size_t c=1) const
      { return const_ref_capa_i_cte(*this,capa,f,c); }
    const_ref_capa_i_cte GetConstRefCapaICte(size_t capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols) const
      { return const_ref_capa_i_cte(*this,capa,rango_filas,rango_cols); }
    const_ref_capa_j_cte GetConstRefCapaJCte(size_t f=1,size_t capa=1, size_t c=1) const
      { return const_ref_capa_j_cte(*this,capa,f,c); }
    const_ref_capa_j_cte GetConstRefCapaJCte(const RangoIndice &rango_capas,size_t f,const RangoIndice &rango_cols) const
      { return const_ref_capa_j_cte(*this,rango_capas,f,rango_cols); }
    const_ref_capa_k_cte GetConstRefCapaKCte(size_t c=1,size_t capa=1, size_t f=1) const
      { return const_ref_capa_k_cte(*this,c,capa,f); }
    const_ref_capa_k_cte GetConstRefCapaKCte(const RangoIndice &rango_capas,const RangoIndice &rango_filas,const size_t &c) const
      { return const_ref_capa_k_cte(*this,rango_capas,rango_filas,c); }

    const_ref_fila_i GetConstRefFilaI(size_t f=1,size_t c=1) const
      { return const_ref_fila_i(*this,f,c); }
    const_ref_fila_i GetConstRefFilaI(const RangoIndice &rango_capas,size_t f,size_t c) const
      { return const_ref_fila_i(*this,rango_capas,f,c); }
    const_ref_fila_j GetConstRefFilaJ(size_t capa=1,size_t c=1) const
      { return const_ref_fila_j(*this,capa,c); }
    const_ref_fila_j GetConstRefFilaJ(size_t capa,const RangoIndice &rango_filas,size_t c) const
      { return const_ref_fila_j(*this,capa,rango_filas,c); }
    const_ref_fila_k GetConstRefFilaK(size_t capa=1,size_t f=1) const
      { return const_ref_fila_k(*this,capa,f); }
    const_ref_fila_k GetConstRefFilaK(size_t capa,size_t f,const RangoIndice &rango_cols) const
      { return const_ref_fila_k(*this,capa,f,rango_cols); }

    var_ref_caja GetVarRefCaja(size_t capa=1,size_t f=1, size_t c=1)
      { return var_ref_caja(*this,capa,f,c); }
    var_ref_caja GetVarRefCaja(const RangoTritriz &rango)
      { return var_ref_caja(*this,rango); }

    var_ref_capa_i_cte GetVarRefCapaICte(size_t capa=1,size_t f=1, size_t c=1)
      { return var_ref_capa_i_cte(*this,capa,f,c); }
    var_ref_capa_i_cte GetVarRefCapaICte(size_t capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols)
      { return var_ref_capa_i_cte(*this,capa,rango_filas,rango_cols); }
    var_ref_capa_j_cte GetVarRefCapaJCte(size_t f=1,size_t capa=1, size_t c=1)
      { return var_ref_capa_j_cte(*this,capa,f,c); }
    var_ref_capa_j_cte GetVarRefCapaJCte(const RangoIndice &rango_capas,size_t f,const RangoIndice &rango_cols)
      { return var_ref_capa_j_cte(*this,rango_capas,f,rango_cols); }
    var_ref_capa_k_cte GetVarRefCapaKCte(size_t c=1,size_t capa=1, size_t f=1)
      { return var_ref_capa_k_cte(*this,c,capa,f); }
    var_ref_capa_k_cte GetVarRefCapaKCte(const RangoIndice &rango_capas,const RangoIndice &rango_filas,const size_t &c)
      { return var_ref_capa_k_cte(*this,rango_capas,rango_filas,c); }

    var_ref_fila_i GetVarRefFilaI(size_t f=1,size_t c=1)
      { return var_ref_fila_i(*this,f,c); }
    var_ref_fila_i GetVarRefFilaI(const RangoIndice &rango_capas,size_t f,size_t c)
      { return var_ref_fila_i(*this,rango_capas,f,c); }
    var_ref_fila_j GetVarRefFilaJ(size_t f=1,size_t c=1)
      { return var_ref_fila_j(*this,f,c); }
    var_ref_fila_j GetVarRefFilaJ(size_t capa,const RangoIndice &rango_filas,size_t c)
      { return var_ref_fila_j(*this,capa,rango_filas,c); }
    var_ref_fila_k GetVarRefFilaK(size_t f=1,size_t c=1)
      { return var_ref_fila_k(*this,f,c); }
    var_ref_fila_k GetVarRefFilaK(size_t capa,size_t f,const RangoIndice &rango_cols)
      { return var_ref_fila_k(*this,capa,f,rango_cols); }

    inline const m_pos &operator()(const size_t &capa) const
      { return get_capa(capa); }
    inline m_pos &operator()(const size_t &capa)
      { return get_capa(capa); }
    inline const POS &operator()(const size_t &i,const size_t &j,const size_t &k) const
      { return get_capa(i)(j,k); }
    inline POS &operator()(const size_t &i,const size_t &j,const size_t &k)
      { return get_capa(i)(j,k); }
    POS GetCentro(void) const;
  };

//! @brief Genera la tritriz de puntos a partir de los que se pasan como parámetro.
template <class POS>
TritrizPos<POS>::TritrizPos( const m_pos &puntos_l1,const m_pos &puntos_l2,
                             const m_pos &puntos_l3,const m_pos &puntos_l4,
                             const size_t &ndiv_12,const size_t &ndiv_14)
  : std::vector<m_pos>(puntos_l1.size())
  {
    const size_t ncapas= this->size();
    for(size_t i=1;i<=ncapas;i++) //Iteramos en las "capas" de puntos.
      {
        const POS &p1= puntos_l1(i); //1er. punto del cuadrilatero.
        const POS &p2= puntos_l2(i); //2o. punto del cuadrilatero.
        const POS &p3= puntos_l3(i); //3er. punto del cuadrilatero.
        const POS &p4= puntos_l4(i); //4o. punto del cuadrilatero.
        const m_pos lado1= m_pos(p1,p2,ndiv_12);
        const m_pos lado2= m_pos(p2,p3,ndiv_14);
        const m_pos lado3= m_pos(p4,p3,ndiv_12);
        const m_pos lado4= m_pos(p1,p4,ndiv_14);
        m_pos capa_i(lado1,lado2,lado3,lado4);
        (*this)(i)= capa_i;
      }
  }

//! @brief Devuelve el número de elementos de la tritriz.
template <class POS>
size_t TritrizPos<POS>::NumPos(void) const
  {
    const size_t sz= this->size();
    if(sz<1)
      return 0;
    else
      {
        const m_pos &capa= (*this)(1); 
        return sz*capa.getNumFilas()*capa.getNumCols();
      }
  }

template <class POS>
size_t TritrizPos<POS>::getNumFilas(void) const
  {
    size_t retval= 0;
    if(this->size())
      retval= (*this)[0].getNumFilas();
    return retval;
  }

template <class POS>
size_t TritrizPos<POS>::getNumCols(void) const
  {
    size_t retval= 0;
    if(this->size())
      retval= (*this)[0].getNumCols();
    return retval;
  }

template <class POS,class SEG>
POS get_centro(const TritrizPos<POS> t,const SEG &sg)
  {
    POS retval;
    const typename TritrizPos<POS>::m_pos &base= t(1);
    const typename TritrizPos<POS>::m_pos &tapa= t(t.GetCapas());
    SEG s(get_centro(base,SEG()),get_centro(tapa,SEG()));
    retval= s.Cdg();
    return retval;
  }

template <class POS>
inline std::ostream &operator<<(std::ostream &os,const TritrizPos<POS> &t)
  {
    const size_t ncapas= t.GetCapas();
    for(size_t i=1;i<=ncapas;i++)
      os << t(i);
    return os;
  }

#endif
