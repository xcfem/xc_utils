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
//MatrizAny.cc

#include "MatrizAny.h"
#include "../base/utils_any.h"
#include "xc_utils/src/nucleo/aux_any.h"

//! @brief Constructor.
MatrizAny::MatrizAny(const size_t &f,const size_t &c,const boost::any &p)
  : m_boost_any(f,c,p) {}

//! @brief Constructor.
MatrizAny::MatrizAny(const size_t &f,const v_boost_any &v)
  : m_boost_any(f,v.size())
  {
    const size_t c= v.size();
    for(size_t i=1;i<=f;i++)
      for(size_t j=1;j<=c;j++)
        (*this)(i,j)= v[j-1];
  }

//! @brief Constructor.
MatrizAny::MatrizAny(const m_double &md)
  : m_boost_any(md.getNumFilas(),md.getNumCols())
  {
    const size_t fls= getNumFilas();
    const size_t cls= getNumCols();
    for(size_t i= 1;i<=fls;i++)
      for(size_t j= 1;j<=cls;j++)
        ((*this)(i,j))= md(i,j);
  }

//! @brief Constructor.
MatrizAny::MatrizAny(const m_sizet &mszt)
  : m_boost_any(mszt.getNumFilas(),mszt.getNumCols())
  {
    const size_t fls= getNumFilas();
    const size_t cls= getNumCols();
    for(size_t i= 1;i<=fls;i++)
      for(size_t j= 1;j<=cls;j++)
        ((*this)(i,j))= mszt(i,j);
  }

//! @brief Constructor.
MatrizAny::MatrizAny(const m_int &mi)
  : m_boost_any(mi.getNumFilas(),mi.getNumCols())
  {
    const size_t fls= getNumFilas();
    const size_t cls= getNumCols();
    for(size_t i= 1;i<=fls;i++)
      for(size_t j= 1;j<=cls;j++)
        ((*this)(i,j))= mi(i,j);
  }

MatrizAny &MatrizAny::operator=(const m_double &m)
  { return MatrizAny::operator=(MatrizAny(m)); }
MatrizAny &MatrizAny::operator=(const m_int &m)
  { return MatrizAny::operator=(MatrizAny(m)); }
MatrizAny &MatrizAny::operator=(const m_sizet &m)
  { return MatrizAny::operator=(MatrizAny(m)); }

//! @brief Devuelve la «caja» comprendida entre los índices que se pasan como parámetro.
MatrizAny MatrizAny::GetCaja(size_t f1, size_t c1, size_t f2, size_t c2) const
  {
    this->check_get_caja(f1,c1,f2,c2);
    MatrizAny caja(f2-f1+1,c2-c1+1);
    for(register size_type i=1;i<=caja.fls;i++)
      for(register size_type j=1;j<=caja.cls;j++)
        caja(i,j)= MatrizAny::operator()(i+f1-1,j+c1-1);
    return caja;
  }

void MatrizAny::Print(std::ostream &os) const
  {
    os << '[';
    const size_t fls= getNumFilas();
    const size_t cls= getNumCols();
    for(size_t i= 1;i<=fls;i++)
      {
        os << '[';
        if(cls > 0) boost_any_print(os,(*this)(i,1));
	for(size_t j= 2;j<=cls;j++)
          {
	    os << ',';
            boost_any_print(os,(*this)(i,j));
          }
        os << ']';
      }
    os << ']';
  }

MatrizAny convert_from_vector(const std::vector<boost::any> &v)
  {
    MatrizAny retval;
    if(boost_any_is_vector_any(v[0]))
      {
        const size_t f= v.size();
        std::vector<boost::any> fila= convert_to_vector_any(v[0]);
        const size_t c= fila.size();
        retval= MatrizAny(f,c);
        for(size_t i=1;i<=f;i++)
          {
	    fila= convert_to_vector_any(v[i-1]);
            for(size_t j=1;j<=c;j++)
              retval(i,j)= fila[j-1];
          }
      }
    return retval;
  }
