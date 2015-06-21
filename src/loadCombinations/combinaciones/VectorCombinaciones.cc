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
//VectorCombinaciones.cxx

#include "VectorCombinaciones.h"
#include "xc_basic/src/texto/en_letra.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

        
//! \fn bool cmb_acc::VectorCombinaciones::Nula(const double &tol) const
//! @brief Devuelve verdadero si todas las combinaciones del vector son nulas.
bool cmb_acc::VectorCombinaciones::Nula(const double &tol) const
  {
    for(size_t i=0;i<size();i++)
      if(!(*this)[i].Nula(tol)) return false;
    return true;
  }

//! \fn size_t cmb_acc::VectorCombinaciones::CuentaNulas(const double &tol) const
//! @brief Devuelve el número de combinaciones nulas que aparecen en las combinaciones.
size_t cmb_acc::VectorCombinaciones::CuentaNulas(const double &tol) const
  {
    size_t retval=0;
    for(size_t i=0;i<size();i++)
      if((*this)[i].Nula(tol)) retval++;
    return retval;
  }

        
//! \fn cmb_acc::VectorCombinaciones cmb_acc::VectorCombinaciones::GetNoNulas(const double &tol) const
//! @brief Devuelve las combinaciones no nulas.
const cmb_acc::VectorCombinaciones &cmb_acc::VectorCombinaciones::GetNoNulas(const double &tol) const
  {
    const size_t num_nulas= CuentaNulas(tol);
    if(num_nulas==0) return *this;
    const size_t sznn= size()-num_nulas;
    static VectorCombinaciones retval;
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

//! \fn cmb_acc::VectorCombinaciones::procesa_comando(CmdStatus &status)
//! @brief Lee el objeto desde archivo.
bool cmb_acc::VectorCombinaciones::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    if(verborrea>2)
      std::clog << "(VectorCombinaciones) Procesando comando: " << cmd << std::endl;
    if(cmd == "for_each")
      {
        const std::string bloque= status.GetBloque();
        for(iterator i=begin();i!=end();i++)
          {
            Accion &data= *i;
            data.set_owner(this);
            data.EjecutaBloque(status,bloque,"VectorCombinaciones:for_each");
          }
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

        
//! \fn bool cmb_acc::VectorCombinaciones::Existe(const Accion &f) const
//! @brief Devuelve verdadero si la combinación f se encuentra en ESTE vector.
bool cmb_acc::VectorCombinaciones::Existe(const Accion &f) const
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
const cmb_acc::VectorCombinaciones &cmb_acc::VectorCombinaciones::GetDistintas(void) const
  {
    static VectorCombinaciones retval;
    const size_t sz= size();
    if(sz<1)
      {
        retval.resize(0);
        return retval;
      }
    VectorCombinaciones tmp(sz);
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
        
//! \fn size_t cmb_acc::VectorCombinaciones::CuentaDistintas(const VectorCombinaciones &s2) const
//! @brief Cuenta las combinaciones de s2 que no estan en ESTA.
size_t cmb_acc::VectorCombinaciones::CuentaDistintas(const VectorCombinaciones &s2) const
  {
    const size_t sz_s2= s2.size();
    size_t retval=0;
    for(size_t i=0;i<sz_s2;i++)
      if(!this->Existe(s2[i])) retval++;
    return retval;
  }
        
//! \fn cmb_acc::VectorCombinaciones cmb_acc::VectorCombinaciones::GetDistintas(const VectorCombinaciones &s2) const
//! @brief Devuelve las combinaciones de s2 que no estan en ESTA.
const cmb_acc::VectorCombinaciones &cmb_acc::VectorCombinaciones::GetDistintas(const VectorCombinaciones &s2) const
  {
    const size_t num_distintas= CuentaDistintas(s2);
    const size_t sz_s2= s2.size();
    if(num_distintas==sz_s2) return s2; //Todas son distintas.
    const size_t sznn= num_distintas;
    static VectorCombinaciones retval;
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

        
//! \fn cmb_acc::VectorCombinaciones cmb_acc::VectorCombinaciones::ProdCartesiano(const VectorCombinaciones &f1,const VectorCombinaciones &f2,const double &tol)
//! @brief Forma el producto cartesiano de las combinaciones del vector f1 con las del vector f2
//! Por ejemplo si:
//! Combinaciones f1: f11,f12,f13
//! Combinaciones f2: f21,f22
//! Devuelve: f11+f21,f12+f21,f13+f21,f11+f22,f12+f22,f13+f22
cmb_acc::VectorCombinaciones cmb_acc::VectorCombinaciones::ProdCartesiano(const VectorCombinaciones &f1,const VectorCombinaciones &f2,const double &tol)
  //
  {
    const VectorCombinaciones &ann= f1;
    const VectorCombinaciones &bnn= f2;
    const size_t sz_ann= ann.size();
    if(sz_ann==0) return bnn;
    const size_t sz_bnn= bnn.size();
    if(sz_bnn==0) return ann;
    const size_t sz= sz_ann*sz_bnn;
    VectorCombinaciones retval(sz);
    for(size_t i=0;i<sz_ann;i++)
      for(size_t j=0;j<sz_bnn;j++)
        {
          size_t ind_retval= i*sz_bnn+j;
          retval[ind_retval]= ann[i]+bnn[j];
        }
    return retval;
  }

//! @brief Concatena las combinaciones de los vectores que se pasan como parámetro
cmb_acc::VectorCombinaciones cmb_acc::VectorCombinaciones::Concat(const VectorCombinaciones &f1,const VectorCombinaciones &f2,const double &tol)
  {
    const VectorCombinaciones &ann= f1;
    const VectorCombinaciones bnn= f1.GetDistintas(f2); //Las de f2 que no esten en f1.
    const size_t sz_ann= ann.size();
    if(sz_ann==0) return bnn;
    const size_t sz_bnn= bnn.size();
    if(sz_bnn==0) return ann;
    const size_t sz= sz_ann+sz_bnn;
    VectorCombinaciones retval(sz);
    for(size_t i=0;i<sz_ann;i++)
      retval[i]= ann[i];
    for(size_t i=0;i<sz_bnn;i++)
      retval[i+sz_ann]= bnn[i];
    return retval;
  }
        
//! \fn void cmb_acc::VectorCombinaciones::Numera(const std::string &prefijo)
//! @brief Añade al nombre de cada uno de los elementos del vector el texto
//! "HNNN=" como prefijo siendo NNN el número de hipótesis
void cmb_acc::VectorCombinaciones::Numera(const std::string &prefijo)
  {
    size_t cont= 1;
    for(iterator i= begin(); i!=end();i++,cont++)
      (*i).SetNombre(prefijo + num2str(cont) + "= " + (*i).GetNombre());
  }

//! @brief Devuelve los coeficientes que corresponden a las acciones que se pasan como parámetro
//! en cada una de las combinaciones del vector.
m_double cmb_acc::VectorCombinaciones::getCoeficientes(const std::vector<std::string> &base) const
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

void cmb_acc::VectorCombinaciones::Print(std::ostream &os) const
  {
    for(const_iterator i= begin(); i!=end();i++)
      os << (*i) << std::endl;
  }

//! \fn any_const_ptr cmb_acc::VectorCombinaciones::GetProp(const std::string &cod) const
//! @brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa como parámetro.
any_const_ptr cmb_acc::VectorCombinaciones::GetProp(const std::string &cod) const
  {
    if(cod == "num_combinaciones")
      {
        tmp_gp_szt= size();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "comb")
      {
        const size_t i= popSize_t(cod);
        return any_const_ptr(&((*this)[i]));
      }
    else if(cod == "getCoeficientes")
      {
        const std::vector<std::string> base= popVectorString(cod);
        tmp_gp_mdbl= getCoeficientes(base);
        return any_const_ptr(tmp_gp_mdbl);
      }
    else
      return EntCmd::GetProp(cod);
  }

std::ostream &cmb_acc::operator<<(std::ostream &os,const VectorCombinaciones &vc)
  {
    vc.Print(os);
    return os;
  }
