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
//solver_gauss.h

#ifndef SOLVER_GAUSS_H
#define SOLVER_GAUSS_H

#include "xc_utils/src/matrices/solvers/solver.h"
#include <cmath>
#include <algorithm>

template<class M,class V>
class SolverGauss: public SolverM<M>
  {
    typedef typename SolverM<M>::tipo_val tipo_val;
    
    inline size_t busca_pivote(const size_t &k)
      {
        size_t l= 0;
        tipo_val smax= fabs((*A)(P(k),k));
        for(size_t i=k+1; i<=n; i++)
          {
            size_t ip= P(i);
            if(fabs((*A)(ip,k)) > smax)
              {
                l= i;
                smax = fabs((*A)(ip,k));
              }
          }
        return l;
      }

    virtual bool decomp(void)
      {
        inic_p();
        for(size_t k=1, l=0; k<=n; k++)
          {
            l= busca_pivote(k);

            if(l) std::swap(P(k),P(l));
            size_t pi= P(k);
            tipo_val r1= 1.0/(*A)(pi,k);
            for(size_t i=k+1; i<=n; i++)
              {
                size_t ip= P(i);
                tipo_val r= (*A)(ip,k)*r1;
                for(size_t j=k+1;j<=n;j++) (*A)(ip,j)-= r*(*A)(pi,j);
                (*A)(ip,k) = -r;
              }
          }
        desc= 1;
        return true;
      }
    inline void triang_inf(V &B) const
      {
        for(size_t k=1; k<=n; k++)
          {
            size_t ip= P(k);
            for(size_t i=k+1; i<=n; i++)
              {
                size_t pi= P(i);
                B(pi)+= (*A)(pi,k)*B(ip);
              }
          }
      }
    inline V atras(const V &B) const
      {
        V X(B);
        tipo_val c;
        X(n) = B(P(n))/(*A)(P(n),n);
        for(size_t i=n-1; i>=1; i--)
          {
            size_t pi=P(i);
            size_t j;
            for(j=i+1, c=B(pi); j<=n; j++) c-= (*A)(pi,j)*X(j);
            X(i)= c/(*A)(pi,i);
          }
        return X;
      }
    virtual V backsub(V &B) const
      {
        if(!check_backsub(B)) exit(1);
        triang_inf(B);
        return atras(B);
      }
  public:
    SolverGauss(void): SolverM<M>() {}
    V BackSub(V &B) const
      {
        if(!desc)
          std::cerr << "¡Ojo! Se ha llamado a Backsub sin llamar antes a Decomp."
               << std::endl;
        return backsub(B);
      }
    V BackSub(const V &B) const
      {
        if(!desc)
          std::cerr << "¡Ojo! Se ha llamado a Backsub sin llamar antes a Decomp."
               << std::endl;
        V C(B);
        return backsub(C);
      }
  };

#endif
