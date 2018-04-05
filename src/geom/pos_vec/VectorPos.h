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
//VectorPos.h
//Positions vector.

#ifndef VECTORPOS_H
#define VECTORPOS_H

#include "MatrizPos.h"


//! @ingroup GEOM
//
//! @brief Clase base para los vectores de posiciones.
template <class POS>
class VectorPos: public MatrizPos<POS>
  {
  public:
    typedef MatrizPos<POS> m_pos;
  public:
    VectorPos(const size_t &f=1): m_pos(f,1) {}
    VectorPos(const POS &p1,const POS &p2,const size_t &num,const GEOM_FT &ratio);
    VectorPos(const POS &p1,const POS &p2,const size_t &ndiv);
    inline VectorPos<POS> GetCaja(size_t f1, size_t f2) const
      { return VectorPos(*this,f1,1,f2,1); }
    inline const POS &GetFila(size_t fila) const
      { return m_pos::operator()(fila,1); }
    inline VectorPos<POS> GetCol(size_t col) const
      { return m_pos::GetCol(1); }
  };

template <class POS>
VectorPos<POS>::VectorPos(const POS &p1,const POS &p2,const size_t &num,const GEOM_FT &ratio)
  : m_pos(p1,p2,num,ratio) {}

template <class POS>
VectorPos<POS>::VectorPos(const POS &p1,const POS &p2,const size_t &ndiv)
  : m_pos(p1,p2,ndiv) {}

#endif
