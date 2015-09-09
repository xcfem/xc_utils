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
//Record.cc

#include "Record.h"
#include "CmdStatus.h"
#include "any_const_ptr.h"

//! @brief Constructor.
Record::Record(EntCmd *owr, const std::string &b)
  :EntWOwner(owr) 
  { if(!b.empty()) EjecutaBloque(b,"record:constructor"); }

//! @brief Lee un objeto Record desde archivo
//! Soporta los comandos:
bool Record::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(Record) Procesando comando: " << cmd << std::endl;
    return EntWOwner::procesa_comando(status);
  }

MapParam::param_iterator Record::crea_user_prop(const std::string &nmb,const boost::any &v)
  { return params.Props().CreaUserParam(nmb,v); }

std::string Record::sqlNames(void) const
  { return params.Props().SqlUserParamNames(); }

std::string Record::sqlValues(void) const
  { return params.Props().SqlUserParamValues(); }

//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
//!
//! 
any_const_ptr Record::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "Record::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    any_const_ptr retval;
    if(cod == "sqlValues")
      {
        tmp_gp_str= sqlValues();
        retval= any_const_ptr(tmp_gp_str);
      }
    else if(cod == "sqlNames")      
      {
        tmp_gp_str= sqlNames();
        retval= any_const_ptr(tmp_gp_str);
      }
    else
      retval= EntWOwner::GetProp(cod);
    if(verborrea>4)
      std::cout << "Sale Record::GetProp:" << cod << std::endl;
    return retval;
  }

std::ostream &operator<<(std::ostream &os,const Record &r)
  {
    r.params.Props().Print(os);
    return os;
  }
