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
//FuncPorPuntosR_R.cc

#include "FuncPorPuntosR_R.h"
#include <set>

//! @brief Operador asignación.
FuncPorPuntosR_R &FuncPorPuntosR_R::operator=(const FuncPorPuntosR_R &otra)
  {
    FuncPorPuntosR_T<double>::operator=(otra);
    return *this;
  }

//! @brief Operador asignación. Iguala a una constante.
FuncPorPuntosR_R &FuncPorPuntosR_R::operator=(const double &c)
  {
    (*this)= asigna(*this,c);
    return *this;
  }

//! @brief Devuelve la posición del máximo.
FuncPorPuntosR_R::const_iterator FuncPorPuntosR_R::PosMax(void) const
  {
    const_iterator i= begin();
    const_iterator retval= i;
    double max= (*i).second;
    for(;i!=end();i++)
      if(max < (*i).second)
        {
          max= (*i).second;
          retval= i;
        }
    return retval;
  }
//! @brief Devuelve la posición del mínimo.
FuncPorPuntosR_R::const_iterator FuncPorPuntosR_R::PosMin(void) const
  {
    const_iterator i= begin();
    const_iterator retval= i;
    double min= (*i).second;
    for(;i!=end();i++)
      if(min > (*i).second)
        {
          min= (*i).second;
          retval= i;
        }
    return retval;
  }

//! @brief Devuelve el dominio en el que se define la función.
dq_double FuncPorPuntosR_R::Dominio(void) const
  {
    dq_double retval(2,0.0);
    retval[0]= begin()->first;
    retval[1]= rbegin()->first;
    return retval;
  }

//! @brief Devuelve las abcisas en las que se define la función.
dq_double FuncPorPuntosR_R::Abcisas(void) const
  {
    dq_double retval;
    const_iterator i= begin();
    for(;i!=end();i++)
      retval.push_back((*i).first);
    return retval;
  }

//! @brief Devuelve las ordenadas correspondientes a cada abcisa.
dq_double FuncPorPuntosR_R::Ordenadas(void) const
  {
    dq_double retval;
    const_iterator i= begin();
    for(;i!=end();i++)
      retval.push_back((*i).second);
    return retval;
  }

//! @brief Devuelve los puntos en los que se anula la función.
dq_double FuncPorPuntosR_R::Ceros(void) const
  {
    dq_double retval;
    const_iterator i= begin();
    const_iterator j= i;
    j++;
    for(;j!=end();i++,j++)
      {
        const double y0= (*i).second;
        const double y1= (*j).second;
        if(y0*y1<=0.0)
          {
            double x0= (*i).first;
            double x1= (*j).first;
            double a= (y1-y0)/(x1-x0);
            double b= y1-a*x1;
            retval.push_back(-(b/a));
          }
      }
    return retval;
  }

double FuncPorPuntosR_R::firstX(void) const
  {
    double retval= 0.0;
    if(!empty())
      retval= begin()->first;
    else
      std::cerr << "La función está sin definir." << std::endl;
    return retval;
  }
double FuncPorPuntosR_R::firstY(void) const
  {
    double retval= 0.0;
    if(!empty())
      retval= begin()->second;
    else
      std::cerr << "La función está sin definir." << std::endl;
    return retval;
  }
double FuncPorPuntosR_R::lastX(void) const
  {
    double retval= 0.0;
    if(!empty())
      retval= rbegin()->first;
    else
      std::cerr << "La función está sin definir." << std::endl;
    return retval;
  }
double FuncPorPuntosR_R::lastY(void) const
  {
    double retval= 0.0;
    if(!empty())
      retval= rbegin()->second;
    else
      std::cerr << "La función está sin definir." << std::endl;
    return retval;
  }


//! @brief Devuelve el área bajo la función.
double FuncPorPuntosR_R::Area(void) const
  {
    double retval= 0.0;
    const_iterator i= begin();
    const_iterator j= i;
    j++;
    double x0,y0,x1,y1;
    for(;j!=end();i++,j++)
      {
        x0= (*i).first; y0= (*i).second;
        x1= (*j).first; y1= (*j).second;
        retval+= (y0+y1)/2*(x1-x0); //Trapecio.
      }
    return retval;
  }

//! @brief Devuelve las abcisas entre x0 y x1 (ambas inclusive).
FuncPorPuntosR_R getSub(const FuncPorPuntosR_R &f1,const double &x0,const double &x1)
  {
    FuncPorPuntosR_R retval;
    double X0= x0;
    double X1= x1;
    if(X1<X0)
      std::swap(X1,X0);
    std::set<double> tmp;
    tmp.insert(X0);
    tmp.insert(X1);
    const dq_double a= f1.Abcisas();
    for(dq_double::const_iterator i= a.begin();i!=a.end();i++)
      if((X0<*i) && (*i<X1))
        tmp.insert(*i);
    for(std::set<double>::const_iterator i= tmp.begin();i!=tmp.end();i++)
        retval.Inserta(*i,f1.Valor(*i));
    return retval;
  }

//! @brief Devuelve la parte de la función entre x0 y x1.
FuncPorPuntosR_R FuncPorPuntosR_R::sub(const double &x0,const double &x1) const
  { return getSub(*this,x0,x1); }


//! @brief Devuelve la función cambiada de signo.
FuncPorPuntosR_R FuncPorPuntosR_R::getNeg(void) const
  { return (*this)*-1.0; }

//! @brief Cambia de signo la función.
FuncPorPuntosR_R &FuncPorPuntosR_R::Neg(void)
  {
    (*this)= getNeg();
    return *this;
  }

FuncPorPuntosR_R &FuncPorPuntosR_R::operator+=(const double &c)
  {
    (*this)= (*this)+c;
    return *this;
  }
FuncPorPuntosR_R &FuncPorPuntosR_R::operator+=(const FuncPorPuntosR_R &f)
  {
    (*this)= (*this)+f;
    return *this;
  }
FuncPorPuntosR_R &FuncPorPuntosR_R::operator-=(const double &c)
  {
    (*this)= (*this)+(-c);
    return *this;
  }
FuncPorPuntosR_R &FuncPorPuntosR_R::operator-=(const FuncPorPuntosR_R &f)
  {
    (*this)= (*this)-f;
    return *this;
  }
FuncPorPuntosR_R &FuncPorPuntosR_R::operator*=(const double &c)
  {
    (*this)= (*this)*c;
    return *this;
  }
FuncPorPuntosR_R &FuncPorPuntosR_R::operator*=(const FuncPorPuntosR_R &f)
  {
    (*this)= (*this)*f;
    return *this;
  }
FuncPorPuntosR_R &FuncPorPuntosR_R::operator/=(const double &c)
  {
    (*this)= (*this)*(1.0/c);
    return *this;
  }
FuncPorPuntosR_R &FuncPorPuntosR_R::operator/=(const FuncPorPuntosR_R &f)
  {
    (*this)= (*this)/f;
    return *this;
  }

//! @brief Devuelve la función que resulta de integrar entre x0 y x1.
FuncPorPuntosR_R FuncPorPuntosR_R::integra(const double &x0,const double &x1,const double &d) const
  {
    double delta(d);
    FuncPorPuntosR_R retval;
    const double longIntervalo= x1-x0;
    if(delta<0.0)
      delta= (x1-x0)/100;
    if(delta<=0.0)
      {
        std::cerr << "FuncPorPuntosR_R::integra() Attempting to integrate time step" 
                  << delta << "<= 0\n";
        return retval;
      }

    // Add one to get ceiling out of type cast
    const size_t numSteps = (int)(longIntervalo/delta + 1.0);

    retval.Inserta(x0,0.0);
    // Set the second point
    // Assuming initial condition is zero, i.e. F(0) = 0
    double previousValue= (*this)(x0); // Temporary storage to avoid accessing same value twice
	                             // through identical method calls
  
    double dummyX= x0+delta; // Dummy variable for integrating
    double currentValue= 0.0;
    double acum= 0.0;
    
    for(size_t i= 1;i<numSteps;i++,dummyX+=delta)
      {
        currentValue = (*this)(dummyX);
        // Apply the trapezoidal rule to update the integrated value
        acum+= delta*(currentValue+previousValue)/2.0;
        retval.Inserta(dummyX,acum);
        previousValue = currentValue;
      }
    return retval;
  }

//! @brief Asigna a la función una constante.
FuncPorPuntosR_R asigna(const FuncPorPuntosR_R &f,const double &c)
  {
    FuncPorPuntosR_R retval;
    for(FuncPorPuntosR_R::const_iterator i= f.begin();i!=f.end();i++)
      retval.Inserta((*i).first,c);
    return retval;
  }

//! @brief Suma a la función una constante.
FuncPorPuntosR_R operator+(const FuncPorPuntosR_R &f,const double &c)
  {
    FuncPorPuntosR_R retval;
    for(FuncPorPuntosR_R::const_iterator i= f.begin();i!=f.end();i++)
      retval.Inserta((*i).first,(*i).second+c);
    return retval;
  }

dq_double merge_abcisas(const FuncPorPuntosR_R &f1,const FuncPorPuntosR_R &f2)
  {
    dq_double retval;
    const dq_double a= f1.Abcisas();
    const dq_double b= f2.Abcisas();
    if(a==b)
      retval= a;
    else
      {
        std::set<double> tmp;
        tmp.insert(a.begin(),a.end());
        tmp.insert(b.begin(),b.end());
        for(std::set<double>::const_iterator i= tmp.begin();i!=tmp.end();i++)
          retval.push_back(*i);
      }
    return retval;
  }

//! @brief Suma dos funciones.
FuncPorPuntosR_R operator+(const FuncPorPuntosR_R &f1,const FuncPorPuntosR_R &f2)
  {
    FuncPorPuntosR_R retval;
    dq_double abcisas= merge_abcisas(f1,f2);
    for(dq_double::const_iterator i= abcisas.begin();i!=abcisas.end();i++)
      retval.Inserta((*i),f1.Valor(*i)+f2.Valor(*i));
    return retval;
  }

//! @brief Resta dos funciones.
FuncPorPuntosR_R operator-(const FuncPorPuntosR_R &f1,const FuncPorPuntosR_R &f2)
  {
    FuncPorPuntosR_R retval;
    dq_double abcisas= merge_abcisas(f1,f2);
    for(dq_double::const_iterator i= abcisas.begin();i!=abcisas.end();i++)
      retval.Inserta((*i),f1.Valor(*i)-f2.Valor(*i));
    return retval;
  }

//! @brief Multiplica dos funciones.
FuncPorPuntosR_R operator*(const FuncPorPuntosR_R &f1,const FuncPorPuntosR_R &f2)
  {
    FuncPorPuntosR_R retval;
    dq_double abcisas= merge_abcisas(f1,f2);
    for(dq_double::const_iterator i= abcisas.begin();i!=abcisas.end();i++)
      retval.Inserta((*i),f1.Valor(*i)*f2.Valor(*i));
    return retval;
  }

//! @brief Divide dos funciones.
FuncPorPuntosR_R operator/(const FuncPorPuntosR_R &f1,const FuncPorPuntosR_R &f2)
  {
    FuncPorPuntosR_R retval;
    dq_double abcisas= merge_abcisas(f1,f2);
    for(dq_double::const_iterator i= abcisas.begin();i!=abcisas.end();i++)
      retval.Inserta((*i),f1.Valor(*i)/f2.Valor(*i));
    return retval;
  }

//! @brief Multiplica la función por una constante.
FuncPorPuntosR_R operator*(const double &c,const FuncPorPuntosR_R &f)
  {
    FuncPorPuntosR_R retval;
    for(FuncPorPuntosR_R::const_iterator i= f.begin();i!=f.end();i++)
      retval.Inserta((*i).first,(*i).second*c);
    return retval;
  }

