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
//CmdVectorDenso.cc

#include "CmdVectorDenso.h"
#include "xc_utils/src/base/CmdMatriz.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "any_const_ptr.h"

//! @brief Obtiene la componente del vector a la que se refiere
//! la cadena de caracteres que se pasa como parámetro.
int CmdVectorDenso::get_componente(const std::string &str)
  {
    std::string tmp= q_car_i(str,'v'); //Quita la v.
    tmp= q_car_i(tmp,'(');
    tmp= q_car_d(tmp,')');
    return atoi(tmp);
  }

//! @brief Carga un objeto CmdVectorDenso desde archivo.
bool CmdVectorDenso::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(CmdVectorDenso) Procesando comando: " << cmd << std::endl;
    if(cmd == "dims") //Establece las dimensiones de la matriz.
      {
        const std::string &args= status.Parser().GetArgs();
        std::vector<int> dims= crea_vector_int(args);
        const size_t nc= dims.size(); //dimension de la matriz.
        if(nc!=2)
	  std::cerr << "CmdVectorDenso::procesa_comando; error procesando comando: "
                    << cmd << " se leyeron " << nc
                    << " valores, se esperaban 2." << std::endl;
        const double v= interpretaDouble(status.GetString());
        *this= m_double(dims[0],dims[1],v);
        return true;
      }
    else if(cmd == "v") //Asigna el valor de un elemento.
      {
        set_comp(cmd,status);
        return true;
      }
    else
      return CmdVectorBase::procesa_comando(status);
  }
//! @brief Devuelve un vector cuyos elementos son los indicados por los indices
//! del vector de enteros que se pasa como parámetro.
CmdVectorDenso CmdVectorDenso::operator()(const m_sizet &indices) const
  { return ExtraeValores((const m_double &)(*this),indices,1); }

//! @brief Devuelve el producto del vector por un escalar.
CmdVectorDenso operator*(const double &d,const CmdVectorDenso &v)
  { return (d*(const m_double &)v); }

//! @brief Devuelve el producto del vector por un escalar.
CmdVectorDenso operator*(const CmdVectorDenso &v,const double &d)
  { return d*v; }


//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr CmdVectorDenso::GetProp(const std::string &cod) const 
  { return CmdVectorBase::GetProp(cod); }
