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
//BoxConstRef.h 

#ifndef BOXCONSTREF_H
#define BOXCONSTREF_H

#include "ProtoMatrix.h"
#include "RangoIndice.h"

//! @brief Base class for the references to a matrix box.
class BoxBaseRef: public ProtoMatrix
  {
  protected:
    size_t offset_f; //!< row offset.
    size_t offset_c; //!< column offset.
  public:
    BoxBaseRef(const ProtoMatrix &m,const size_t &f1= 1,const size_t &c1= 1);
    BoxBaseRef(const ProtoMatrix &m,const size_t &,const size_t &,const size_t &,const size_t &);
    BoxBaseRef(const ProtoMatrix &mat,const RangoIndice &row_range,const RangoIndice &column_range);
    BoxBaseRef(const ProtoMatrix &mat,const RangoIndice &,const size_t &);
    BoxBaseRef(const ProtoMatrix &mat,const size_t &,const RangoIndice &);
    RangoIndice getRowRange(void) const;
    RangoIndice getColumnRange(void) const;
  };

//! @brief Reference to a matrix box.
template <class MAT>
class BoxConstRef: public BoxBaseRef
  {
    const MAT &m;
  public:
    typedef typename MAT::const_reference const_reference;

    BoxConstRef(const MAT &m,const size_t &f1= 1,const size_t &c1= 1);
    BoxConstRef(const MAT &m,const size_t &,const size_t &,const size_t &,const size_t &);
    BoxConstRef(const MAT &mat,const RangoIndice &row_range,const RangoIndice &column_range);
    BoxConstRef(const MAT &mat,const RangoIndice &,const size_t &);
    BoxConstRef(const MAT &mat,const size_t &,const RangoIndice &);
    virtual const_reference operator()(size_t iRow=1,size_t col=1) const
      { return m(iRow+offset_f,col+offset_c); }
    void Print(std::ostream &) const;
  };

//! @brief Constructor por defecto.
template<class MAT>
BoxConstRef<MAT>::BoxConstRef(const MAT &mat,const size_t &f1,const size_t &c1)
  : BoxBaseRef(mat,f1,c1), m(mat) {}

//! @brief Constructor.
template<class MAT>
BoxConstRef<MAT>::BoxConstRef(const MAT &mat,const size_t &f1,const size_t &c1,const size_t &f2,const size_t &c2)
  : BoxBaseRef(mat,f1,c1,f2,c2), m(mat)
  {}

//! @brief Constructor.
template<class MAT>
BoxConstRef<MAT>::BoxConstRef(const MAT &mat,const RangoIndice &row_range,const RangoIndice &column_range)
  : BoxBaseRef(mat,row_range,column_range), m(mat) {}

//! @brief Column alone constructor.
template<class MAT>
BoxConstRef<MAT>::BoxConstRef(const MAT &mat,const RangoIndice &row_range,const size_t &col)
  : BoxBaseRef(mat,row_range,col), m(mat) {}

//! @brief Row alone constructor.
template<class MAT>
BoxConstRef<MAT>::BoxConstRef(const MAT &mat,const size_t &iRow,const RangoIndice &column_range)
  : BoxBaseRef(mat,iRow,column_range), m(mat) {}

template<class MAT>
void BoxConstRef<MAT>::Print(std::ostream &os) const
  {
    os << '[';
    size_t n_rows= this->getNumberOfRows(),n_columns= this->getNumColumns();
    for(register size_t i= 1;i<=n_rows;i++)
      {
        os << '[';
        if(n_columns > 0) os << (*this)(i,1);
	for(register size_t j= 2;j<=n_columns;j++)
	  os << ',' << (*this)(i,j);
        os << ']';
      }
    os << ']';
  }

template <class MAT>
inline std::ostream &operator<<(std::ostream &os,const BoxConstRef<MAT> &c)
  {
    c.Print(os);
    return os;
  }

#endif
