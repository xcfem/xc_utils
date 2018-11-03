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
//vcolM.h

#ifndef VCOLM_H
#define VCOLM_H

#include "MMatrix.h"


//! column vector with components are matrix.
class vcolM: public MMatrix
  {
  private:
    inline m_double &operator()(const size_t &iRow,const size_t &)
      { return MMatrix::operator()(iRow,1); }
    inline const m_double &operator()(const size_t &iRow,const size_t &) const
      { return MMatrix::operator()(iRow,1); }
  public:
    //! Constructor por defecto.
    vcolM(const size_type &n_rows= 1)
      : MMatrix(n_rows,1) {}
    //! Constructor.
    vcolM(const size_type &n_rows,const m_double &val)
      : MMatrix(n_rows,1,val) {}
    vcolM(const std::vector<size_t> &dim);
    vcolM(const MMatrix &m,const size_type &c);
    //! Constructor de copia.
    vcolM(const vcolM &otra) 
      : MMatrix(otra) {}
    //! Operador asignacion.
    vcolM &operator=(const vcolM &m)
      {
	MMatrix::operator=(m);
        return *this;
      }
    m_double &operator()(const size_t &iRow=1)
      { return MMatrix::operator()(iRow,1); }
    const m_double &operator()(const size_t &iRow=1) const
      { return MMatrix::operator()(iRow,1); }

    vcolM &operator*=(const m_double &m);
    vcolM &operator*=(const double &d);
    friend vcolM operator+(const vcolM &m1,const vcolM &m2);
    friend vcolM operator-(const vcolM &m1,const vcolM &m2);
    friend vcolM operator*(const vcolM &m,const double &d);
    friend vcolM operator*(const double &d,const vcolM &m)
      { return m*d; }
    friend vcolM operator*(const m_double &m,const vcolM &mM);
    friend vcolM operator*(const vcolM &mM, const m_double &m)
      { return m*mM; }
  };
#endif

vcolM operator*(const MMatrix &a,const vcolM &b);
