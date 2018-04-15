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
//Revolucion3d.cc

#include "Revolucion3d.h"
#include "../pos_vec/MatrizPos3d.h"
#include "../pos_vec/TritrizPos3d.h"
#include "Rotation3d.h"

//! @brief Constructor.
Revolucion3d::Revolucion3d(const Recta3d &e,const GEOM_FT &th,const size_t &nd)
  : eje(e), theta(th), ndiv(nd)
  {}

//! @brief Return the point row that results from apply the revolution
//! to the argument.
MatrizPos3d Revolucion3d::Aplica0d(const Pos3d &p) const
  {
    MatrizPos3d retval(1,ndiv+1);
    retval(1,1)= p;
    const GEOM_FT inc_angulo= theta/ndiv;
    GEOM_FT ang(inc_angulo);
    for(size_t i=2;i<=ndiv+1;i++)
      {
        const Rotation3d trf(eje,ang);
        retval(1,i)= trf(p);
        ang+= inc_angulo;
      }
    return retval;
  }

//! @brief Return the point matrix that results from apply the revolution
//! to the argument.
MatrizPos3d Revolucion3d::Aplica1d(const MatrizPos3d &m) const
  {
    const size_t nPoints= m.size();
    if(m.isColumn()) //Column matrix, put points by rows.
      {
        MatrizPos3d retval(nPoints,ndiv+1);
        for(size_t i=1;i<=nPoints;i++) //Points of the first column.
          retval(i,1)= m(i,1);
        const GEOM_FT inc_angulo= theta/ndiv;
        GEOM_FT ang(inc_angulo);
        for(size_t i=2;i<=ndiv+1;i++)
          {
            const Rotation3d trf(eje,ang);
            for(size_t j=1;j<=nPoints;j++)
              retval(i,j)= trf(m(i,1));
            ang+= inc_angulo;
          }
        return retval;
      }
    else if(m.isRow()) //Column matrix, put points by columns.
      {
        MatrizPos3d retval(ndiv+1,nPoints);
        for(size_t j=1;j<=nPoints;j++) //Points of the first row.
          retval(1,j)= m(1,j);
        const GEOM_FT inc_angulo= theta/ndiv;
        GEOM_FT ang(inc_angulo);
        for(size_t i=2;i<=ndiv+1;i++)
          {
            const Rotation3d trf(eje,ang);
            for(size_t j=1;j<=nPoints;j++)
              retval(i,j)= trf(m(1,i));
            ang+= inc_angulo;
          }
        return retval;
      }
    else
      {
	std::cerr << getClassName() << "::" << __FUNCTION__
	          << "; bi-dimensional matrix,"
                  << " the result is not a point matrix" 
                  << " use " << getClassName() << "::Aplica2d."
		  << std::endl;
        return MatrizPos3d();
      }
  }

//! @brief Return the point matrix that results from apply the revolution
//! to the bi-dimensional matrix passed as argument.
TritrizPos3d Revolucion3d::Aplica2d(const MatrizPos3d &m) const
  {
    if(!m.isRow() && !m.isColumn()) //bi-dimensional matrix.
      {
        const size_t n_layers= ndiv+1;
	TritrizPos3d retval(n_layers,m);
        const GEOM_FT inc_angulo= theta/ndiv;
        GEOM_FT ang(inc_angulo);
        for(size_t i=2;i<=n_layers;i++)
          {
            const Rotation3d trf(eje,ang);
            retval(i)= trf(m);
            ang+= inc_angulo;
	  }
        return retval;
      }
    else
      {
	std::cerr << getClassName() << "::" << __FUNCTION__
	          << "; uni-dimensional matrix,"
                  << " the result is a point matrix" 
                  << " use " << getClassName() << "::Aplica1d."
		  << std::endl;
        return TritrizPos3d();
      }
  }

MatrizPos3d Revolucion3d::operator()(const Pos3d &p) const
  { return Aplica0d(p); }

MatrizPos3d Revolucion3d::operator()(const MatrizPos3d &m) const
  { return Aplica1d(m); }
