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
//RangoIndice.h

#ifndef RANGOINDICE_H
#define RANGOINDICE_H

#include <ostream>
#include <vector>

//! @brief Rango de variación de un índice, se emplea en BoxConstRef.
class RangoIndice
  {
    size_t mn; //!< Valor mínimo del índice.
    size_t mx; //!< Valor máximo del índice.
    static const char sep; //!< Carácter de separación.
  public:
    RangoIndice(const size_t &imin= 1,const size_t &imax= 1)
      :mn(std::min(imin,imax)),mx(std::max(imin,imax)) {}
    explicit RangoIndice(const std::vector<size_t> &);
    void SetInfSup(const size_t &imin,const size_t &imax);
    const size_t &Inf(void) const
      { return mn; }
    size_t &Inf(void)
      { return mn; }
    const size_t &Sup(void) const
      { return mx; }
    size_t &Sup(void)
      { return mx; }
    size_t Size(void) const
      { return std::max(mx-mn+1,size_t(0)); }
    size_t Offset(void) const
      { return mn-1; }
    //! @brief Devuelve verdadero si el rango no contiene ningún índice.
    bool Vacio(void) const
      { return (mx<mn); }
    inline static const char &Separador(void)
      { return sep; }
    void Clip(const size_t &imax);
    void Intersec(const RangoIndice &otro);
    RangoIndice Intersec(const RangoIndice &otro) const;
    void Print(std::ostream &os) const;
  };

RangoIndice clip(const RangoIndice &,const size_t &);
RangoIndice intersec(const RangoIndice &,const RangoIndice &);

std::ostream &operator<<(std::ostream &os,const RangoIndice &rango);

#endif
