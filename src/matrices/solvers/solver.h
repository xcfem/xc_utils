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
//solver.h

#ifndef SOLVER_H
#define SOLVER_H

#include "xc_utils/src/matrices/m_sizet.h"

class Solver
  {
  private:
    m_sizet PP;
  protected:
    size_t verbosity; //0: No mostrar ningún mensaje de error o aviso.
                      //1: Mostrar sólo los importantes.
                      //2: Mostrar todos los mensajes.
    size_t n;
    int desc;

    inline const size_t &P(size_t i) const
      { return PP(i); }
    inline size_t &P(size_t i)
      { return PP(i); }

    void inic_p(void);
    int check_pp(const size_t n_rows) const;
  public:
    Solver(const size_t &vrbrr= 1): PP(0,0), verbosity(vrbrr), n(0), desc(0) {}
    void SetVerbosity(const size_t &v)
      { verbosity= v; }
  };

template<class M>
class SolverM: public Solver
  {
  protected:
    M *A;

    typedef typename M::value_type tipo_val;
    static const tipo_val CERO;

    virtual bool decomp(void)= 0;

    inline int check_matrix(void) const
      {
        if(A->getNumberOfColumns() != A->getNumberOfRows())
          {
	    if(verbosity)
              std::cerr << "Not a square matrix" << std::endl;
	    return 0;
          }
        return 1;
      }

    template <class V>
    inline int check_backsub(const V &B) const
      {
        if(!check_matrix()) return 0;
        if(B.getNumberOfRows()!=A->getNumberOfRows() || B.getNumberOfColumns()!=1)
          {
	    if(verbosity)
	      std::cerr << "Matrix " << B
			<< " has a different row number than "
			<< A << std::endl;
	    return 0;
          }
        return check_pp(A->getNumberOfRows());
      }
  public:
    SolverM(const size_t &vrbrr= 1): Solver(vrbrr), A(NULL) {}
    void putMatrix(M &m)
      {
        A= &m;
        n= A->getNumberOfColumns();
        desc= 0;
      }
    bool Decomp(void)
      {
        if(!A)
          {
	    if(verbosity)
	      std::cerr << "There is no matrix to decompose." << std::endl;
            return false;
          }
        if(!desc)
          return decomp();
        else
          return true;
      }
    virtual ~SolverM(void) {}
  };


template<class M>
const typename SolverM<M>::tipo_val SolverM<M>::CERO= neutro_suma(typename SolverM<M>::tipo_val());


#endif
