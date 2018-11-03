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
//pivote.h
//Procedimiento para la obtencion del pivote en los mEtodos
//de Gauss y de Jordan para la solucion de un sistema de ecuaciones lineal.

#ifndef PIVOTE_H
#define PIVOTE_H

#include <cmath>
#include "xc_utils/src/matrices/ZMatrix.h"
#include <set>
#include "xc_utils/src/matrices/solvers/gj_aux.h"

typedef std::set<size_t, std::less<size_t> > set_szt;

inline int In(const set_szt &fp,const size_t &i)
  {
    set_szt::iterator j;
    j = fp.find(i);
    if ( j == fp.end() )
        return 0;
    else
        return 1;
  }

template <class treal>
size_t pivote(const size_t &j,const ZMatrix<treal> &a,const set_szt &fp)
  {
    size_t i,k=0,n= a.getNumberOfRows();
    treal amax=zero;
    for(i= 1;i<=n;i++)
      if (!In(fp,i) && ( amax<gj_abs(a(i,j)) ) )
	{ k=i; amax=gj_abs(a(i,j)); }
    return k;
  }
#endif

