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
//Variacion.cxx

#include "Variacion.h"
#include "xc_utils/src/loadCombinations/actions/ListaVRAccion.h"

//! \fn void cmb_acc::Variacion::print(std::ostream &os) const
//! @brief Imprime la variación.
void cmb_acc::Variacion::print(std::ostream &os) const
  {
    if(size()<1) return;
    const_iterator i= begin();
    os << '[';
    os << *i; i++;
    for(;i!=end();i++)
      os << ',' << *i;
    os << ']';
  }

//! \fn cmb_acc::Variacion cmb_acc::Variacion::concat(const cmb_acc::Variacion &a,const cmb_acc::Variacion &b)
//! @brief Concatena a la variación a la variación b
cmb_acc::Variacion cmb_acc::Variacion::concat(const cmb_acc::Variacion &a,const cmb_acc::Variacion &b)
  {
    const size_t sz_a= a.size();
    const size_t sz_b= b.size();
    const size_t sz= sz_a+sz_b;
    Variacion retval(sz);
    for(size_t i=0;i<sz_a;i++)
      retval[i]= a[i];
    for(size_t i=0;i<sz_b;i++)
      retval[i+sz_a]= b[i];
    return retval;
  }


//! @brief Devuelve verdadero si las acciones que contiene la variaciónes son compatibles
bool cmb_acc::Variacion::compatible(const ListaVRAccion &lvr)
  {
    const size_t sz= size();
    for(register size_t i=0;i<sz;i++)
      for(register size_t j=i+1;j<sz;j++)
        if( ((*this)[i]!= 0.0) && ((*this)[j]!= 0.0) )
          if(incompatibles(lvr[i],lvr[j]))
            return false;
    return true;
  }

//! \fn std::ostream &cmb_acc::operator<<(std::ostream &os,const cmb_acc::Variacion &v)
//! @brief Operador salida.
std::ostream &cmb_acc::operator<<(std::ostream &os,const cmb_acc::Variacion &v)
  {
    v.print(os);
    return os;
  }
