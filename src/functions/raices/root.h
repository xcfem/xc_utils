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
#ifndef ROOT_H
#define ROOT_H


/*
            Copyright (c) 1995 Namir C. Shammas

      Version 1.0                                Date 6/3/94

      Module: C root-finding routines which support the following
        general methods for a single real function:

            + Bisection method
            + Tangent method
            + Newton's method
            + Richmond's method
            + Brent's method
            + Combined method (Bisection and Newton)
            + Lin-Bairston method for polynomials
            + Newton's method for two equations
            + Newton's method for multiple equations

*/

#include "xc_utils/src/matrices/m_double.h"
#include "xc_utils/src/matrices/m_func.h"
#include "xc_utils/src/matrices/m_int.h"
#include "xc_utils/src/matrices/solvers/solver_lu.h"
#include "Metodo2Func.h"
#include "bisection.h"

#define ROOT_EPS 1.0e-30

typedef struct polyRootTag 
  {
    double real;
    double imag;
    bool isComplex;
  } polyRoot;


int NewtonApprox(double *root, double tolerance,
                 int maxIter, double* params,
                 double (*f)(double, double*));

int NewtonExact(double *root, double tolerance,
                int maxIter, double* params,
                double (*f)(double, double*),
                double (*fderiv)(double, double*));

int RichmondApprox(double *root, double tolerance,
                   int maxIter, double* params,
                   double (*f)(double, double*));

int RichmondExact(double *root, double tolerance,
                  int maxIter, double* params,
                  double (*f)(double, double*),
                  double (*f1stDeriv)(double, double*),
                  double (*f2ndDeriv)(double, double*));

int Combined(double low, double high, double tolerance,
             double* root, int maxIter, double* params,
             double (*f)(double, double*));

int Brent(double low, double high, double tolerance,
          double* root, int maxIter, double* params,
          double (*f)(double, double*));

int NewtonMultiRoots(double *roots, int* numRoots, int maxRoots,
                     double tolerance, int maxIter, double* params,
                     double (*f)(double, double*));

int DeflatePolyRoots(double* coeff, double initGuess,
                     double* roots, int* numRoots,
                     int polyOrder, int maxIter,
                     double tolerance);

int LBPolyRoots(double* coeff, polyRoot* roots,
                int polyOrder, double tolerance);

int Newton2Functions(double *rootX, double* rootY,
                     double tolerance, int maxIter,
                     double* paramsX, double* paramsY,
                     double (*fx)(double, double, double*),
                     double (*fy)(double, double, double*));

template<class MF>
int NewtonSimNLE(m_double &X, double tolerance,int maxIter, const MF &f)
  {
    int moreIter, iter= 0;
    double h;
    size_t numEqns= X.getNumberOfRows();

    m_double J(numEqns,numEqns);
    m_double Xdash(X);
    m_double Fvector(numEqns,1);
    m_int index(numEqns,1);

    do
      {
        iter++;
        // copy the values of array X into array Xdash
        Xdash= X;
        // calculate the array of function values
        Fvector= f.Eval(X);
	std::cout <<"F( " << X << ")= " << Fvector << std::endl;
        // calculate the J matrix
        for(size_t i= 1;i<=numEqns; i++)
          for(size_t j= 1;j<=numEqns;j++)
            {
              // calculate increment in variable number j
              //h = (fabs(X(j)) > 1) ? 0.01 * X(j) : 0.01; //xxx no se porqué hacía esto
              h= 0.01*X(j);
              Xdash(j)+= h;
	      std::cout << "h= " << h << std::endl;
/*               cout << "f= " << (f(i))(Xdash) << endl; */
/*               cout << "F= " << Fvector(i) << endl; */
              J(i,j) = ((f(i))(Xdash) - Fvector(i)) / h;
              // restore incremented value
              Xdash(j)= X(j);
            }
	//        cout << "J= " << J << endl;
        // solve for the guess refinement vector
        SolverLU<m_double,m_double> solver;
        solver.putMatrix(J);
        solver.Decomp();
        Fvector= solver.BackSub(Fvector);

        // clear the more-iteration flag
        moreIter = 0;
        // update guess and test for convergence
        for(size_t i= 1;i<= numEqns;i++)
          {
            X(i)-= Fvector(i);
            if(fabs(Fvector(i)) > tolerance) moreIter = 1;
          }
	std::cout << "iteración: " << iter << std::endl;
        if(moreIter)
          moreIter = (iter > maxIter) ? 0 : 1;
      }
    while (moreIter);

    return 1 - moreIter;
  }

#endif
