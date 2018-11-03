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
//Polinomio.h
#ifndef POLINOMIO_H
#define POLINOMIO_H

#include "function.h"
#include "IndPol.h"
#include <map>
#include "xc_utils/src/utils/misc_utils/matem.h"
#include "xc_utils/src/matrices/ZMatrix.h"


size_t GetNumCoefs(char m,short unsigned int n);
inline size_t GetNumCoefs(char m,const char *vars)
  { return GetNumCoefs(m,strlen(vars)); }


typedef std::map< IndPol, double, std::less<IndPol> > mapPol;
typedef vectorZ<double> vZ_double;
typedef ZMatrix<double> mZ_double;

class Polinomio : public Function, public mapPol
  {
  protected:
    inline void init(const double &d)
      {
        IndPol v= GetIndPol();
        mapPol::operator[](v)= d;
      }
    void PutSuma(const NmbVars &vars,const IndPol &v,const double &d)
    //Le suma al coeficiente que corresponde a IndoPol la cantidad d.
      {
        IndPol v2= Conv(this->Vars,vars,v);
        mapPol::iterator i= find(v2);
        if (i == end())
          mapPol::operator[](v2) = d;
        else
          mapPol::operator[](v2) += d;
      }
    void PutSuma(const IndPol &v,const Polinomio &p);
    void PutProd(const IndPol &v,const double &d)
    //Multiplica el coeficiente que corresponde a IndPol por la cantidad d.
      {
        mapPol::iterator i= find(v);
        if (i != end()) mapPol::operator[](v) *= d;
      }
    void OutSigno(std::ostream &stream,mapPol::const_iterator &i) const
    //Devuelve el signo del elemento al que se refiere i.
      {
        if ( (*i).second < 0 )
          stream << " - ";
        else
          stream << " + ";
      }
    void OutVars(std::ostream &stream,mapPol::const_iterator &i) const;
    Polinomio Reduce(short unsigned int j,const double &val) const;
  public:
    Polinomio(const double &d= 0.0): Function(), mapPol() 
      { init(d); }
    Polinomio(const NmbVars &vars): Function(vars), mapPol() 
      { init(0.0); }      
    Polinomio(const char *vars): Function(vars), mapPol() 
      { init(0.0); }
    Polinomio(const char var): Function(var), mapPol() 
      { init(0.0); }
    Polinomio(const Polinomio &otro): Function(otro), mapPol(otro) {}
    Polinomio &operator=(const Polinomio &p)
      {
        Function::operator=(p);
        mapPol::operator=(p);
        return *this;
      }
    IndPol GetIndPol(void) const
    //Devuelve un vector de indices adecuado para
    //el polinomio.
      {
        IndPol i(GetDim());
        return i;
      }
    int Grado(short unsigned int j) const;
    IndPol Grados(void) const;
    int Grado(void) const
    //Devuelve el grado del polinomio.
      {
        IndPol gs= Grados();
        return *max_element(gs.begin(),gs.end());  
      }
    void Neg(void);
    static Polinomio neutro_suma(void)
      { return Polinomio(0.0); }
    static Polinomio neutro_producto(void)
      { return Polinomio(1.0); }
    Polinomio Reduce(short unsigned int j,const Polinomio &val) const;
    Polinomio Eval(short unsigned int j,const double &val) const;
    //Devuelve el polinomio que resulta de sustituir la variable de indice j por
    //el valor que se pasa como parametro.
    Polinomio Eval(short unsigned int j,const Polinomio &val) const;
    //Devuelve el polinomio que resulta de sustituir la variable de indice j por
    //el polinomio que se pasa como parametro.
    double Eval(const vZ_double &v) const;
    //Devuelve el valor del polinomio en el punto v.
    double Eval(const mZ_double &v) const;
    //Devuelve el valor del polinomio en el punto v.
    Polinomio CompactaVar(unsigned short int j) const;
    double operator()(const vZ_double &x) const
    //Evalua el polinomio en el punto x.
      { return Eval(x); }
    friend bool operator ==(const Polinomio &p1,const Polinomio &p2)
      {
        if ((const Function &) p1 != (const Function &) p2) return 0;
        if ((const mapPol &) p1 != (const mapPol &) p2) return 0;
        return 1;
      }
    friend Polinomio operator -(const Polinomio &p)
      {
        Polinomio neg(p);
        neg.Neg();
        return neg;
      }
    Polinomio& operator+=(const Polinomio &p);
    Polinomio &operator-=(const Polinomio &m)
      {
        Polinomio p(*this);
        p+= -m;
        (*this)= p;
        return *this;
      }
    Polinomio &operator +=(const double &d)
      {
        IndPol v= GetIndPol();
        PutSuma(Vars,v,d);
        return *this;        
      }
    friend Polinomio operator +(const Polinomio &p1,const Polinomio &p2)
      {
        Polinomio p(p1);
        p+= p2;
        return p;
      }
    friend Polinomio operator -(const Polinomio &p1,const Polinomio &p2)
      { return p1 + (-p2); }
    friend Polinomio operator +(const Polinomio &p,const double &d)
      {
        Polinomio q(p);
        q+=d;
        return q;
      }
    friend Polinomio operator +(const double &d,const Polinomio &p)
      { return p+d; }
    friend Polinomio operator -(const Polinomio &p,const double &d)
      { return p + (-d); }
    friend Polinomio operator -(const double d,const Polinomio &p)
      { return d+(-p); }
    friend Polinomio operator *(const Polinomio &p1,const Polinomio &p2);
    Polinomio &operator*=(const double &d);
    Polinomio &operator*=(const Polinomio &p);
    inline friend Polinomio operator *(const Polinomio &p,const double &d)
      {
        Polinomio q(p);
        q*= d;
        return q;
      }
    inline friend Polinomio operator *(const double &d,const Polinomio &p)
      { return p*d; }
    Polinomio Parcial(short unsigned int j) const;
    Polinomio Derivada(short unsigned int j,const double &x) const
      {
        Polinomio p= Parcial(j);
        return p.Eval(j,x);
      }
    Polinomio Primitiva(short unsigned int j) const;
    Polinomio Integral(short unsigned int j,const double &x0,const double &x1) const
      {
        Polinomio p= Primitiva(j);
        return p.Eval(j,x1)-p.Eval(j,x0);
      }
    double Integral(const vZ_double &x0,const vZ_double &x1) const;
    friend std::ostream &operator <<(std::ostream &stream,const Polinomio &p);
  };

Polinomio operator *(const Polinomio &p1,const Polinomio &p2);
std::ostream &operator<<(std::ostream &stream,const Polinomio &p);
std::istream &operator>>(std::istream &stream,const Polinomio &p);

inline Polinomio sqr(const Polinomio &p)
//Calcula el cuadrado de un polinomio.
  { return p*p; }

Polinomio pow(const Polinomio &p,unsigned int n);
//Eleva el polinomio a la potencia entera n.

inline Polinomio neutro_suma(const Polinomio &)
  { return Polinomio::neutro_suma(); }
inline Polinomio neutro_producto(const Polinomio &)
  { return Polinomio::neutro_producto(); }

#endif








