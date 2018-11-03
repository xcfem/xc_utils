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
//RangoIndice.cc

#include "RangoIndice.h"
#include "xc_utils/src/utils/text/text_string.h"
#include <deque>

const char RangoIndice::sep=':';

//! @brief Constructor.
RangoIndice::RangoIndice(const std::vector<size_t> &v)
 :mn(1),mx(1)
  {
    if(v.size()>1)
      SetInfSup(v[0],v[1]);
    else
      std::cerr << "RangoIndice::RangoIndice; error: se pasó un vector"
                << " de dimensión inferior a 2." << std::endl;
  }

//! @brief Imprime el rango.
void RangoIndice::Print(std::ostream &os) const
  { os << mn << ':' << mx; }

void RangoIndice::SetInfSup(const size_t &imin,const size_t &imax)
  {
    mn= std::min(imin,imax);
    mx= std::max(imin,imax);
  }

//! @brief Reduce los valores del rango de manera que ambos sean menores que
//! el que se pasa como parámetro.
void RangoIndice::Clip(const size_t &imax)
  {
    mn= std::min(mn,imax);
    mx= std::min(mx,imax);
  }

//! @brief Asigna a ESTE la intersección de ambos rangos.
void RangoIndice::Intersec(const RangoIndice &otro)
  {
    mn= std::max(mn,otro.mn);
    mx= std::min(mx,otro.mx);
  }

//! @brief Devuelve la intersección de ambos rangos.
RangoIndice RangoIndice::Intersec(const RangoIndice &otro) const
  {
    RangoIndice retval(*this);
    retval.Intersec(otro);
    return retval;
  }

std::ostream &operator<<(std::ostream &os,const RangoIndice &rango)
  {
    rango.Print(os);
    return os;
  }

RangoIndice clip(const RangoIndice &r,const size_t &mx)
  {
    RangoIndice retval(r);
    retval.Clip(mx);
    return retval;
  }

//! @brief Devuelve la intersección de ambos rangos.
RangoIndice intersec(const RangoIndice &r1,const RangoIndice &r2)
  { return r1.Intersec(r2); }


