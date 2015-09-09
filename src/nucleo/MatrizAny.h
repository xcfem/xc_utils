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
//MatrizAny.h
//Matriz de boost::any

#ifndef MATRIZANY_H
#define MATRIZANY_H

#include "xc_basic/src/matrices/matrizT.h"
#include <vector>
#include "boost/any.hpp"
#include "xc_basic/src/matrices/m_int.h"
#include "xc_basic/src/matrices/m_sizet.h"
#include "xc_basic/src/matrices/m_double.h"

namespace boost
  {
    class any;
  }

//! @ingroup NUCLEO
//
//! @brief Matriz de posiciones.
class MatrizAny: public MatrizT<boost::any,std::vector<boost::any> >
  {
  public:
    typedef std::vector<boost::any> v_boost_any;
    typedef MatrizT<boost::any,std::vector<boost::any> > m_boost_any;
  public:
    MatrizAny(const size_t &f=1,const size_t &c=1,const boost::any &p= boost::any());
    MatrizAny(const size_t &f,const v_boost_any &v);
    explicit MatrizAny(const m_double &);
    explicit MatrizAny(const m_sizet &);
    explicit MatrizAny(const m_int &);
    
    MatrizAny &operator=(const m_double &);
    MatrizAny &operator=(const m_int &);
    MatrizAny &operator=(const m_sizet &);
    MatrizAny GetCaja(size_t f1, size_t c1, size_t f2, size_t c2) const;
    inline MatrizAny GetFila(size_type fila) const
      { return GetCaja(fila,1,fila,this->cls); }
    inline MatrizAny GetCol(size_type col) const
      { return GetCaja(1,col,this->fls,col); }
    void Print(std::ostream &) const;
  };

MatrizAny convert_from_vector(const std::vector<boost::any> &v);


#endif
