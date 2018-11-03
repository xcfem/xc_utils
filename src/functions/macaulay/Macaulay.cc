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
//Macaulay.cc

#include "Macaulay.h"
#include "xc_utils/src/utils/misc_utils/matem.h"

double Macaulay::Eval(const double &x) const
  {
    double retval= 0.0;
    if (x>=a) retval= coef * pow(x-a,n);
    return retval;
  }

Macaulay Macaulay::Primitiva(void) const
  {
    Macaulay retval(*this);
    retval.n++;
    retval.coef*= (1.0/(double)retval.n);
    return retval;
  }

Macaulay &Macaulay::operator*=(const Macaulay &m)
  {
    if(this->Vars != m.Vars)
      {
        std::cerr << "Error en Macaulay *=" << std::endl;
        abort();
      }
    this->n+= m.n;
    this->a= std::max(this->a,m.a);
    this->coef*= m.coef;
    return *this;
  }
Macaulay Macaulay::Diferencial(void) const
  {
    if(n < 1)
      {
        std::cerr << "La diferencial no existe." << std::endl;
        abort();
      }     
    Macaulay retval(*this);
    retval.coef*= n;
    retval.n--;
    return retval;
  }

double Macaulay::Integral(const double &a, const double &b) const
  {
    Macaulay m= this->Primitiva();
    return m(b)-m(a);
  }
double Macaulay::Derivada(const double &x) const
  {
    Macaulay m= this->Diferencial();
    return m(x);
  }

Macaulay operator *(const Macaulay &m1,const Macaulay &m2)
  {
    Macaulay retval(m1);
    retval *= m2;
    return retval;
  }

bool operator ==(const Macaulay &p1,const Macaulay &p2)
  {
    if ((const Function &) p1 != (const Function &) p2) return 0;
    if (p1.n != p2.n) return 0;
    if (p1.a != p2.a) return 0;
    if (p1.coef != p2.coef) return 0;
    return 1;
  }

std::ostream &operator <<(std::ostream &stream,const Macaulay &p)
  {
    stream << p.coef << "*<" << p.GetNmbVar(1) 
           << ',' << p.a << '>' << p.n;
    return stream;
  }

double dot(const Macaulay &m1,const Macaulay &m2, const double &a, const double &b)
  {
    Macaulay m= m1*m2;
    return m.Integral(a,b);
  }
