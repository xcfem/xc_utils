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
//Variaciones.cxx

#include "Variaciones.h"
#include "xc_utils/src/loadCombinations/acciones/ListaVRAccion.h"

//! @brief Constructor.
cmb_acc::Variaciones::Variaciones(const size_t &sz,const Variacion &v)
  : std::vector<Variacion>(sz,v) {}

//! \fn void cmb_acc::Variaciones::print(std::ostream &os) const
//! @brief Imprime las variaciones.
void cmb_acc::Variaciones::print(std::ostream &os) const
  {
    if(size()<1) return;
    const_iterator i= begin();
    os << '[';
    os << *i; i++;
    for(;i!=end();i++)
      os << ' ' <<*i;
    os << ']';
  }

//! \fn cmb_acc::Variaciones cmb_acc::Variaciones::primera_combinacion(const Variacion &v)
//! @brief Devuelve la primera combinación.
cmb_acc::Variaciones cmb_acc::Variaciones::primera_combinacion(const Variacion &v)
  {
    const size_t sz= v.size();
    Variaciones retval(sz);
    for(size_t i=0;i<sz;i++)
      retval[i]= Variacion(1,v[i]);
    return retval;
  }

//! \fn cmb_acc::Variaciones cmb_acc::Variaciones::prod_cartesiano(const Variaciones &a,const Variaciones &b)
//! @brief Devuelve el producto cartesiano de las variaciones que se pasan como parámetro.
cmb_acc::Variaciones cmb_acc::Variaciones::prod_cartesiano(const Variaciones &a,const Variaciones &b,const ListaVRAccion &lvr)
  {
    const size_t sz_a= a.size();
    const size_t sz_b= b.size();
    std::deque<Variacion> tmp;
    for(size_t i=0;i<sz_a;i++)
      for(size_t j=0;j<sz_b;j++)
        {
          Variacion tmp_var= Variacion::concat(a[i],b[j]);
          tmp.push_back(tmp_var);
        }
    const size_t sz= tmp.size();
    Variaciones retval(sz);
    for(size_t i= 0;i<sz;i++)
      retval[i]= tmp[i];
    return retval;
  }

//! \fn cmb_acc::Variaciones cmb_acc::Variaciones::n_esima_combinacion(const Variacion &v,const size_t &n)
//! @brief Devuelve la enésima combinación.
cmb_acc::Variaciones cmb_acc::Variaciones::n_esima_combinacion(const Variacion &v,const int &d,const ListaVRAccion &lvr)
  {
    const size_t n= lvr.size();
    if(n<1) return Variaciones();
    Variaciones primera= primera_combinacion(v);
    Variaciones retval(primera);
    if(n==1) return retval;
    if(primera.size()>1) //Hay más de un coeficiente para combinar.
      {
        for(size_t i=2;i<=n;i++)
          retval= prod_cartesiano(primera,retval,lvr);
        if(d>=0) //Seleccionamos aquellos cuya acción dominante tiene coeficiente no nulo.
          {
            std::deque<Variacion> tmp;
            const std::size_t sz= retval.size();
            for(size_t i=0;i<sz;i++)
              {
                if(retval[i].at(d)!=0.0)
                  tmp.push_back(retval[i]);
              }
            const size_t sz2= tmp.size();
            retval.resize(sz2);
            for(size_t i= 0;i<sz2;i++)
              retval[i]= tmp[i];
          }
      }
    else //Sólo hay un coeficiente para combinar.
      {
        if(d>=0) //Hay una acción dominante.
          {
            retval= Variaciones(1,Variacion(n,0.0));
            retval[0][d]= primera[0][0];
          }
        else
          retval= Variaciones(1,Variacion(n,primera[0][0]));
      }
    if(retval.empty())
      std::cerr << "¡Ojo! cmb_acc::Variaciones::n_esima_combinacion: no se obtuvieron combinaciones." << std::endl;
    return retval;
  }

//! @brief Calculas las variaciones que pueden formarse.
cmb_acc::Variaciones cmb_acc::Variaciones::Calcula(const Variacion &v,const int &d,const ListaVRAccion &lvr)
  { return n_esima_combinacion(v,d,lvr); }

//! @brief Operador salida.
std::ostream &cmb_acc::operator<<(std::ostream &os,const Variaciones &vs)
  {
    vs.print(os);
    return os;
  }
