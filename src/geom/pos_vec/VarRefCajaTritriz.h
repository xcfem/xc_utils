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
//VarRefCajaTritriz.h 

#ifndef VARREFCAJATRITRIZ_H
#define VARREFCAJATRITRIZ_H

#include "BaseRefCajaTritriz.h"


//! @ingroup GEOM
//
//! @brief Referencia a una "subtritriz".
template <class TRITRIZ>
class VarRefCajaTritriz: public BaseRefCajaTritriz
  {
    TRITRIZ &ttz;
  public:
    typedef typename TRITRIZ::const_reference const_reference;
    typedef typename TRITRIZ::reference reference;

    explicit VarRefCajaTritriz(TRITRIZ &m,const size_t &capa=1,const size_t &f= 1,const size_t &c= 1);
    VarRefCajaTritriz(TRITRIZ &m,const RangoTritriz &rango);
    VarRefCajaTritriz(TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols);
    VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &rango_capas,const size_t &fila,const RangoIndice &rango_cols);
    VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &rango_capas,const RangoIndice &rango_filas,const size_t &col);
    VarRefCajaTritriz(TRITRIZ &t,const size_t &capa,const size_t &fila,const RangoIndice &rango_cols);
    VarRefCajaTritriz(TRITRIZ &t,const size_t capa,const RangoIndice &rango_filas,const size_t &col);
    VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &rango_capas,const size_t &fila,const size_t &col);
    inline virtual ~VarRefCajaTritriz(void) {}
    inline virtual const_reference operator()(size_t capa=1,size_t fila=1,size_t col=1) const
      { return ttz(capa+offset_cp,fila+offset_f,col+offset_c); }
    inline virtual reference operator()(size_t capa=1,size_t fila=1,size_t col=1)
      { return ttz(capa+offset_cp,fila+offset_f,col+offset_c); }
  };

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const size_t &capa,const size_t &f,const size_t &c)
  : BaseRefCajaTritriz(capa,f,c,t.GetCapas(),t.getNumFilas(),t.getNumCols()),ttz(t) {}

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const RangoTritriz &rango)
  : BaseRefCajaTritriz(recorta(rango,t)),ttz(t) {}

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const size_t &capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols)
  : BaseRefCajaTritriz(capa,recorta(rango_filas,t.getNumFilas()),recorta(rango_cols,t.getNumCols())),ttz(t) 
  {
    if(capa>ttz.GetCapas())
      std::clog << "Aviso; índice de capa: " << capa << " fuera de rango en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &rango_capas,const size_t &fila,const RangoIndice &rango_cols)
  : BaseRefCajaTritriz(recorta(rango_capas,t.GetCapas()),fila,recorta(rango_cols,t.getNumCols())),ttz(t)
  {
    if(fila>ttz.getNumFilas())
      std::clog << "Aviso; índice de fila: " << fila << " fuera de rango en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &rango_capas,const RangoIndice &rango_filas,const size_t &col)
  : BaseRefCajaTritriz(recorta(rango_capas,t.GetCapas()),recorta(rango_filas,t.getNumFilas()),col),ttz(t)
  {
    if(col>ttz.getNumCols())
      std::clog << "Aviso; índice de columna: " << col << " fuera de rango en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const size_t &capa,const size_t &fila,const RangoIndice &rango_cols)
  : BaseRefCajaTritriz(capa,fila,recorta(rango_cols,t.getNumCols())),ttz(t)
  {
    if(capa>ttz.GetCapas())
      std::clog << "Aviso; índice de capa: " << capa << " fuera de rango en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
    if(fila>ttz.getNumFilas())
      std::clog << "Aviso; índice de fila: " << fila << " fuera de rango en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const size_t capa,const RangoIndice &rango_filas,const size_t &col)
  : BaseRefCajaTritriz(capa,recorta(rango_filas,t.getNumFilas()),col),ttz(t)
  {
    if(capa>ttz.GetCapas())
      std::clog << "Aviso; índice de capa: " << capa << " fuera de rango en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
    if(col>ttz.getNumCols())
      std::clog << "Aviso; índice de columna: " << col << " fuera de rango en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
  }

template<class TRITRIZ>
VarRefCajaTritriz<TRITRIZ>::VarRefCajaTritriz(TRITRIZ &t,const RangoIndice &rango_capas,const size_t &fila,const size_t &col)
  : BaseRefCajaTritriz(recorta(rango_capas,t.GetCapas()),fila,col),ttz(t)
  {
    if(fila>ttz.getNumFilas())
      std::clog << "Aviso; índice de fila: " << fila << " fuera de rango en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
    if(col>ttz.getNumCols())
      std::clog << "Aviso; índice de columna: " << col << " fuera de rango en tritriz de rangos: " << RangoTritriz(ttz) << std::endl;
  }

template <class TRITRIZ>
inline std::ostream &operator<<(std::ostream &os,const VarRefCajaTritriz<TRITRIZ> &c)
  {
    PrintTritriz(c,os);
    return os;
  }

template <class TRITRIZ, class TRF>
const VarRefCajaTritriz<TRITRIZ> &transforma(const VarRefCajaTritriz<TRITRIZ> &caja,const TRF &trf)
  {
    static VarRefCajaTritriz<TRITRIZ> retval;
    retval= caja;
    const size_t ncapas= caja.GetCapas();
    const size_t nfilas= caja.getNumFilas();
    const size_t ncols= caja.getNumCols();
    for(size_t k=1;k<=ncapas;k++) //Para cada capa.
      for(size_t i=1;i<=nfilas;i++) //Para cada fila.
        for(size_t j=1;j<=ncols;j++) //Para cada columna.
          retval(i,j,k)= Transforma(caja(i,j,k));
    return retval;
  }

#endif
