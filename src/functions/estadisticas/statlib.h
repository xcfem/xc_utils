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
//Statlib.h
#ifndef STATLIB_H
#define STATLIB_H

double Q(const double &x);
// Function that returns the "Normal"
// probability distribution integral

double QInv(double x);
//  calculate the inverse normal.

double T(const double &x, double df);
/* Function will return the probability of
  obtaining a student-t statistic, x, at
  df degrees of freedom.                       */

double TInv(double x, double df);
/* double will return the value of student-t statistic for a
	given probability, x, and df degrees of freedom.          */

double Chi(const double &x, double df);
/* Function will return the probability of obtaining a
  chi-squared statistic, x, at df degrees of freedom.  */

double ChiInv(double x, double df);
/* double will return the value of chi-squared statistic for a */
/* given probability, x, and df degrees of freedom.              */

double F(const double &x, double df1, double df2);
/* Function will return the probability of obtaining an
	F statistic, x, at df degrees of freedom.             */

double FInv(double x, double df1, double df2);
/* Function will return the value of the F statistic for a
  given probability, x, and df degrees of freedom.        */


#endif
