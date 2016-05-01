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
//LoadCombinationVector.cxx

#include "LoadCombinationVector.h"
#include "xc_basic/src/texto/en_letra.h"



        
//! \fn bool cmb_acc::LoadCombinationVector::Nula(const double &tol) const
//! @brief Devuelve verdadero si todas las combinaciones del vector son nulas.
bool cmb_acc::LoadCombinationVector::Nula(const double &tol) const
  {
    for(size_t i=0;i<size();i++)
      if(!(*this)[i].Nula(tol)) return false;
    return true;
  }

//! \fn size_t cmb_acc::LoadCombinationVector::CuentaNulas(const double &tol) const
//! @brief Devuelve el número de combinaciones nulas que aparecen en las combinaciones.
size_t cmb_acc::LoadCombinationVector::CuentaNulas(const double &tol) const
  {
    size_t retval=0;
    for(size_t i=0;i<size();i++)
      if((*this)[i].Nula(tol)) retval++;
    return retval;
  }

        
//! \fn cmb_acc::LoadCombinationVector cmb_acc::LoadCombinationVector::GetNoNulas(const double &tol) const
//! @brief Devuelve las combinaciones no nulas.
const cmb_acc::LoadCombinationVector &cmb_acc::LoadCombinationVector::GetNoNulas(const double &tol) const
  {
    const size_t num_nulas= CuentaNulas(tol);
    if(num_nulas==0) return *this;
    const size_t sznn= size()-num_nulas;
    static LoadCombinationVector retval;
    retval.resize(sznn);
    size_t cont=0;
    for(size_t i=0;i<size();i++)
      if(!(*this)[i].Nula(tol))
        {
          retval[cont]= (*this)[i];
          cont++;
        }
    return retval;
  }

        
//! \fn bool cmb_acc::LoadCombinationVector::Existe(const Action &f) const
//! @brief Devuelve verdadero si la combinación f se encuentra en ESTE vector.
bool cmb_acc::LoadCombinationVector::Existe(const Action &f) const
  {
    bool retval= false;
    const std::string nmb_f= f.GetNombre();
    for(size_t i=0;i<size();i++)
      if((*this)[i].GetNombre()==nmb_f)
        {
          retval= true;
          break;
        }
    return retval;
  }
        
//! @brief Devuelve las combinaciones de ESTA filtrando las que estan repetidas.
const cmb_acc::LoadCombinationVector &cmb_acc::LoadCombinationVector::GetDistintas(void) const
  {
    static LoadCombinationVector retval;
    const size_t sz= size();
    if(sz<1)
      {
        retval.resize(0);
        return retval;
      }
    LoadCombinationVector tmp(sz);
    tmp[0]= (*this)[0]; //Colocamos la primera
    size_t cont=1;
    for(size_t i=1;i<sz;i++)
      if(!tmp.Existe((*this)[i])) //Si es distinta de las anteriores.
       {
         tmp[cont]= (*this)[i]; //La agregamos.
         cont++;
       }
    retval.resize(cont);
    for(size_t i=0;i<cont;i++)
      retval[i]= tmp[i];
    return retval;
  }
        
//! \fn size_t cmb_acc::LoadCombinationVector::CuentaDistintas(const LoadCombinationVector &s2) const
//! @brief Cuenta las combinaciones de s2 que no estan en ESTA.
size_t cmb_acc::LoadCombinationVector::CuentaDistintas(const LoadCombinationVector &s2) const
  {
    const size_t sz_s2= s2.size();
    size_t retval=0;
    for(size_t i=0;i<sz_s2;i++)
      if(!this->Existe(s2[i])) retval++;
    return retval;
  }
        
//! \fn cmb_acc::LoadCombinationVector cmb_acc::LoadCombinationVector::GetDistintas(const LoadCombinationVector &s2) const
//! @brief Devuelve las combinaciones de s2 que no estan en ESTA.
const cmb_acc::LoadCombinationVector &cmb_acc::LoadCombinationVector::GetDistintas(const LoadCombinationVector &s2) const
  {
    const size_t num_distintas= CuentaDistintas(s2);
    const size_t sz_s2= s2.size();
    if(num_distintas==sz_s2) return s2; //Todas son distintas.
    const size_t sznn= num_distintas;
    static LoadCombinationVector retval;
    retval.resize(sznn);
    size_t cont=0;
    for(size_t i=0;i<sz_s2;i++)
      if(!this->Existe(s2[i]))
        {
          retval[cont]= s2[i];
          cont++;
        }
    return retval;
  }

        
//! \fn cmb_acc::LoadCombinationVector cmb_acc::LoadCombinationVector::ProdCartesiano(const LoadCombinationVector &f1,const LoadCombinationVector &f2,const double &tol)
//! @brief Forma el producto cartesiano de las combinaciones del vector f1 con las del vector f2
//! Por ejemplo si:
//! LoadCombinations f1: f11,f12,f13
//! LoadCombinations f2: f21,f22
//! Devuelve: f11+f21,f12+f21,f13+f21,f11+f22,f12+f22,f13+f22
cmb_acc::LoadCombinationVector cmb_acc::LoadCombinationVector::ProdCartesiano(const LoadCombinationVector &f1,const LoadCombinationVector &f2,const double &tol)
  //
  {
    const LoadCombinationVector &ann= f1;
    const LoadCombinationVector &bnn= f2;
    const size_t sz_ann= ann.size();
    if(sz_ann==0) return bnn;
    const size_t sz_bnn= bnn.size();
    if(sz_bnn==0) return ann;
    const size_t sz= sz_ann*sz_bnn;
    LoadCombinationVector retval(sz);
    for(size_t i=0;i<sz_ann;i++)
      for(size_t j=0;j<sz_bnn;j++)
        {
          size_t ind_retval= i*sz_bnn+j;
          retval[ind_retval]= ann[i]+bnn[j];
        }
    return retval;
  }

//! @brief Concatena las combinaciones de los vectores que se pasan como parámetro
cmb_acc::LoadCombinationVector cmb_acc::LoadCombinationVector::Concat(const LoadCombinationVector &f1,const LoadCombinationVector &f2,const double &tol)
  {
    const LoadCombinationVector &ann= f1;
    const LoadCombinationVector bnn= f1.GetDistintas(f2); //Las de f2 que no esten en f1.
    const size_t sz_ann= ann.size();
    if(sz_ann==0) return bnn;
    const size_t sz_bnn= bnn.size();
    if(sz_bnn==0) return ann;
    const size_t sz= sz_ann+sz_bnn;
    LoadCombinationVector retval(sz);
    for(size_t i=0;i<sz_ann;i++)
      retval[i]= ann[i];
    for(size_t i=0;i<sz_bnn;i++)
      retval[i+sz_ann]= bnn[i];
    return retval;
  }
        
//! \fn void cmb_acc::LoadCombinationVector::Numera(const std::string &prefijo)
//! @brief Añade al nombre de cada uno de los elementos del vector el texto
//! "HNNN=" como prefijo siendo NNN el número de hipótesis
void cmb_acc::LoadCombinationVector::Numera(const std::string &prefijo)
  {
    size_t cont= 1;
    for(iterator i= begin(); i!=end();i++,cont++)
      (*i).SetNombre(prefijo + num2str(cont) + "= " + (*i).GetNombre());
  }

//! @brief Devuelve los coeficientes que corresponden a las acciones que se pasan como parámetro
//! en cada una de las combinaciones del vector.
m_double cmb_acc::LoadCombinationVector::getCoeficientes(const std::vector<std::string> &base) const
  {
    const size_t n_filas= size();
    const size_t n_cols= base.size();
    m_double retval(n_filas,n_cols);
    for(size_t i= 0;i<n_filas;i++)
      {
        const std::vector<double> coefs_i= (*this)[i].getCoeficientes(base);
        for(size_t j= 0;j<n_cols;j++)
          retval(i+1,j+1)= coefs_i[j];
      }
    return retval;
  }

void cmb_acc::LoadCombinationVector::Print(std::ostream &os) const
  {
    for(const_iterator i= begin(); i!=end();i++)
      os << (*i) << std::endl;
  }

std::ostream &cmb_acc::operator<<(std::ostream &os,const LoadCombinationVector &vc)
  {
    vc.Print(os);
    return os;
  }
