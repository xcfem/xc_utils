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
//Polinomio.cc

#include "Polinomio.h"
#include "xc_utils/src/functions/estadisticas/combinatoria.h"

const Polinomio polinomio_uno= Polinomio::neutro_producto();
const Polinomio polinomio_cero= Polinomio::neutro_suma();


size_t GetNumCoefs(char m,short unsigned int n)
  {
    if (m<0) return 0;
    short unsigned int i;
    size_t t= 1;
    for(i=1;i<=n;i++)
      t= t * (m + i);
    t= t / factorial(n);
    return t;
  }
void Polinomio::PutSuma(const IndPol &v,const Polinomio &p)
//Le suma al coeficiente que corresponde a IndoPol la cantidad d.
  {
    mapPol::const_iterator i;
    IndPol ip1= p.GetIndPol();
    for (i= p.begin();i != p.end();i++)
      {
        ip1= Conv(this->Vars,p.Vars,(*i).first);
        PutSuma(this->Vars,v+ip1,(*i).second);
      }
  }
IndPol Polinomio::Grados(void) const
//Devuelve los grados del polinomio para cada una 
//de sus variables.
  {
    IndPol gs= GetIndPol();
    size_t i,sz= gs.size();
    for (i= 0; i < sz;i++)
      gs[i]= Grado(i+1);
    return gs;
  }
int Polinomio::Grado(short unsigned int j) const
//Devuelve el grado del polinomio en la variable de indice j.
  {
    int g= 0;
    mapPol::const_iterator i;
    for (i= begin();i != end();i++)
      g= std::max((int)(*i).first.Grado(j-1),g);
    return g;
  }
void Polinomio::Neg(void)
//Cambia el signo del polinomio.
  {
    mapPol::iterator i;
    for (i= begin();i != end();i++) (*i).second= -(*i).second;
  }
Polinomio Polinomio::Eval(short unsigned int j,const double &val) const
//Devuelve el polinomio que resulta de sustituir la variable de indice j por
//el valor que se pasa como parametro.
  {
    Polinomio q= *this;
    while (q.Grado(j) > 0) q= q.Reduce(j,val);
    q= q.CompactaVar(j); //El polinomio ya no depende de esta variable.
    return q;
  }
Polinomio Polinomio::Eval(short unsigned int j,const Polinomio &val) const
//Devuelve el polinomio que resulta de sustituir la variable de indice j por
//el polinomio que se pasa como parametro.
  {
    Polinomio q= *this;
    Polinomio q2= val;
    while (q.Grado(j) > 0) q= q.Reduce(j,q2);
    q= q.CompactaVar(j); //El polinomio ya no depende de esta variable.
    return q;
  }
double Polinomio::Eval(const vZ_double &v) const
//Devuelve el valor del polinomio en el punto v.
  {
    Polinomio q= *this;
    size_t i,sz= v.size();
    for (i=0;i<sz;i++) q= q.Eval(i+1,v[i]);
    return (*q.begin()).second;
  }
double Polinomio::Eval(const mZ_double &v) const
//Devuelve el valor del polinomio en el punto v.
  {
    Polinomio q= *this;
    size_t i,sz= v.size();
    for (i=1;i<=sz;i++) q= q.Eval(i,v(i,1));
    return (*q.begin()).second;
  }
Polinomio Polinomio::Parcial(short unsigned int j) const
//Devuelve la derivada parcial del polinomio respecto a la variable de 
//indice j.
  {
    j--; //El indice de IndPol empieza en 0;
    Polinomio q(Vars);
    if (Grado() == 0) return q;
    IndPol ip1= GetIndPol();
    IndPol ip2= GetIndPol();
    ip1[j]=1;    
    for ( mapPol::const_iterator i= begin(); i != end(); i++)
      {
        ip2= (*i).first;
        if (ip2[j] > 0) q[ip2-ip1]= ip2[j] * (*i).second;
      }
    return q;
  }
Polinomio Polinomio::Primitiva(short unsigned int j) const
//Devuelve la primitiva del polinomio para la variable
//de indice j.
  {
    j--; //El indice de las variables empieza en 0;
    Polinomio q(Vars);
    if (Grado() == 0) return q;
    IndPol ip1= GetIndPol();
    IndPol ip2= GetIndPol();
    ip1[j]=1;    
    for ( mapPol::const_iterator i= begin(); i != end(); i++)
      {
        ip2= (*i).first;
        q[ip2+ip1]= (1.0/(ip2[j]+1)) * (*i).second;
      }
    return q;
  }
Polinomio Polinomio::Reduce(short unsigned int j,const double &val) const
//Devuelve el polinomio que resulta de sustituir UNA VEZ la variable j por el valor
//que se pasa como parametro.
//La rutina se llama Reduce porque el polinomio resultante tiene un grado menos en
//la variable j.
  {
    j--; //El indice de IndPol empieza en 0;
    Polinomio result(Vars);
    IndPol ip1= GetIndPol();
    if (Grado() == 0) return result;
    IndPol ip2= ip1;
    ip1[j]=1;
    for ( mapPol::const_iterator i= begin();i != end() ;i++)
      {
        ip2= (*i).first;
        if (ip2[j] > 0)
          result.PutSuma(result.Vars,ip2-ip1,val * (*i).second);
        else
          result.PutSuma(result.Vars,ip2,(*i).second);
      }
    return result;    
  }
Polinomio Polinomio::Reduce(short unsigned int j,const Polinomio &val) const
//Devuelve el polinomio que resulta de sustituir UNA VEZ la variable j por el polinomio
//que se pasa como parametro.
//La rutina se llama reduce por similitud con la anterior.
  {
    j--; //El indice de IndPol empieza en 0;
    //El polinomio tendra por variables la union de los conjuntos de variables
    //del polinomio que se evalua y del que se pasa como parametro.
    Polinomio result(this->Vars + val.Vars);
    if (Grado() == 0) return result;
    IndPol ip1= result.GetIndPol();
    IndPol ip2= ip1;
    ip1[j]=1;
    for ( mapPol::const_iterator i= begin();i != end();i++)
      {
        ip2= Conv(result.Vars,this->Vars,(*i).first);
        if (ip2[j] > 0)
          result.PutSuma(ip2-ip1,val * (*i).second);
        else
          result.PutSuma(result.Vars,ip2,(*i).second);
      }
    return result;    
  }
Polinomio Polinomio::CompactaVar(unsigned short int j) const
//Elimina la variable j del polinomio.
//Si se elimina una variable cuyo grado en el polinomio no es nulo
//el resultado puede ser un desastre.
  {
    NmbVars Vars= GetVars();
    //Vars.erase(&Vars.at(j-1)); Doesn't works.
    NmbVars::iterator ij= Vars.begin() + (j-1);
    Vars.erase(ij);
    Polinomio result(Vars);
    IndPol ip1= GetIndPol();
    for ( mapPol::const_iterator i= begin();i != end();i++)
      {
        ip1= (*i).first;
        //ip1.erase(&ip1[j-1]); Doesn't works.
        IndPol::iterator ij= ip1.begin() + (j-1);
        ip1.erase(ij);
        result[ip1] = (*i).second;
      }
    return result;
  }
double Polinomio::Integral(const vZ_double &x0,const vZ_double &x1) const
//Devuelve la integral del polinomio en el dominio delimitado por los puntos
//x0 y x1.
  {
    Polinomio q= *this;
    size_t i,sz= x0.size();
    for (i=0;i<sz;i++) q= q.Integral(i+1,x0[i],x1[i]);
    return (*q.begin()).second;  
  }
void Polinomio::OutVars(std::ostream &stream,mapPol::const_iterator &i) const
//Imprime las variebales elevadas a sus correspondientes potencias.
  {
    int j,d= GetDim();  
    for (j=1;j<=d;j++)
      {
        int pot= (*i).first[j-1];
        if (pot > 0)
          stream << GetNmbVar(j);
        if (pot > 1)
          stream << '^' << pot;
      }
  }

Polinomio& Polinomio::operator+=(const Polinomio &p)
  {
    Polinomio s(Vars + p.Vars);
    mapPol::const_iterator i;
    for (i= begin();i != end();i++) 
      s.PutSuma(Vars,(*i).first,(*i).second);    
    for (i= p.begin();i != p.end();i++) 
      s.PutSuma(p.Vars,(*i).first,(*i).second);
    (*this)= s;
    return *this;
  }

std::ostream &operator<<(std::ostream &stream,const Polinomio &p)
  {
    for ( mapPol::const_iterator i= p.begin() ; 
          i != p.end() ; 
          i++)
      { 
        if (i==p.begin()) 
          stream << (*i).second << ' ';
        else
          {
            p.OutSigno(stream,i);
            if (fabs((*i).second) != 1) stream << fabs((*i).second) << ' ';
          }
        p.OutVars(stream,i);
      }
    return stream;
  }

std::istream &operator>>(std::istream &stream,const Polinomio &p)
  {
    std::cerr << "Polinomio; lectura desde stream no implementada." << std::endl;
    return stream;
  }

Polinomio &Polinomio::operator*=(const double &d)
  {
    if(d == 1) return *this;
    if(d == 0) 
      {
        (*this)= polinomio_cero;
        return *this;
      }
    for ( mapPol::iterator i= begin() ; i != end() ; i++)
       (*i).second*= d;
    return *this;
  }
Polinomio &Polinomio::operator*=(const Polinomio &p)
  {
    if(p == polinomio_uno) return *this;
    if(p == polinomio_cero) 
      {
        (*this)= polinomio_cero;
        return *this;
      }
    (*this)= (*this) * p;
    return *this;
  }
Polinomio operator *(const Polinomio &p1,const Polinomio &p2)
  {
    if(p1 == polinomio_uno) return p2;
    if(p2 == polinomio_uno) return p1;
    if( (p1 == polinomio_cero) || (p2 == polinomio_cero) )
      return polinomio_cero;
    Polinomio p(p1.Vars + p2.Vars);
    mapPol::const_iterator i,j;
    for(i=p1.begin();i!= p1.end();i++)
      for(j=p2.begin();j!= p2.end();j++)
        {
          IndPol ip= p.GetIndPol();
          ip= Conv(p.Vars,p1.Vars,(*i).first) + Conv(p.Vars,p2.Vars,(*j).first);
          p.PutSuma(p.Vars,ip,(*i).second * (*j).second);
        }
    return p;
  }

Polinomio pow(const Polinomio &p,unsigned int n)
//Eleva el polinomio a la potencia entera n.
  {
    Polinomio q= p;
    unsigned int i;
    for(i=1;i<n;i++) q= q*p;
    return q;
  }
