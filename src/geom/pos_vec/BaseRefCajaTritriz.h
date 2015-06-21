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
//BaseRefCajaTritriz.h 

#ifndef BASEREFCAJATRITRIZ_H
#define BASEREFCAJATRITRIZ_H

#include <ostream>

class RangoIndice;
class RangoTritriz;

//! @ingroup GEOM
//
//! @brief Indices que definen una caja de una tritriz.
class BaseRefCajaTritriz
  {
  protected:
    size_t ncapas; //!< Número de capas.
    size_t nfls; //!< Número de filas.
    size_t ncls; //!< Número de columnas.
    size_t offset_cp; //!< Offset capa.
    size_t offset_f; //!< Offset fila.
    size_t offset_c; //!< Offset columna.
  public:
    BaseRefCajaTritriz(const size_t &,const size_t &,const size_t &,const size_t &,const size_t &,const size_t &);
    BaseRefCajaTritriz(const RangoTritriz &rango);
    BaseRefCajaTritriz(const size_t &capa,const RangoIndice &rango_filas,const RangoIndice &rango_cols);
    BaseRefCajaTritriz(const RangoIndice &rango_capas,const size_t &fila,const RangoIndice &rango_cols);
    BaseRefCajaTritriz(const RangoIndice &rango_capas,const RangoIndice &rango_filas,const size_t &col);
    BaseRefCajaTritriz(const size_t &capa,const size_t &fila,const RangoIndice &rango_cols);
    BaseRefCajaTritriz(const size_t capa,const RangoIndice &rango_filas,const size_t &col);
    BaseRefCajaTritriz(const RangoIndice &rango_capas,const size_t &fila,const size_t &col);
    inline const size_t &GetCapas(void) const
      { return ncapas; }
    inline const size_t &getNumFilas(void) const
      { return nfls; }
    inline const size_t &getNumCols(void) const
      { return ncls; }
    inline const size_t Size(void) const
      { return ncapas*nfls*ncls; }
    bool Empty(void) const;
    RangoIndice RangoCapas(void) const;
    RangoIndice RangoFilas(void) const;
    RangoIndice RangoCols(void) const;
  };

template <class TRITRIZ>
inline void PrintTritriz(const TRITRIZ &t,std::ostream &os)
  {
    os << '[';
    const size_t ncapas= t.GetCapas();
    for(size_t i=1;i<=ncapas;i++)
      {
        os << '[';
        const size_t nfls= t.getNumFilas();
        for(register size_t j= 1;j<=nfls;j++)
          {
            os << '[';
            const size_t ncls= t.getNumCols();
            if(ncls > 0) os << t(i,j,1);
	    for(register size_t k= 2;k<=ncls;k++)
	      os << ',' << t(i,j,k);
            os << ']';
          }
        os << ']';
      }
    os << ']';
  }

#endif
