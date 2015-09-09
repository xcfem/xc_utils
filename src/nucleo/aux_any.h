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
//aux_any.h
//funciones auxiliares para interpretar variables de tipo boost::any.

#ifndef AUX_ANY_H
#define AUX_ANY_H

#include <string>
#include <iostream>

namespace boost
  {
    class any;
  }
class any_const_ptr;
class EntCmd;
class EntProp;

const std::string &boost_any_tipo_operando(const boost::any &);
void boost_any_print(std::ostream &os,const boost::any &); 
bool convert_arg(boost::any &,const boost::any &,EntCmd *);
void set_owner(boost::any *data, EntProp *owr);
bool opera_rcl(const boost::any &a,const boost::any &b);
EntCmd *boost_any_entcmd_cast(boost::any &);
boost::any convert_to_type(const std::string &,const boost::any &);
boost::any interpreta_string_to_boost_any(EntCmd &,const std::string &,const std::string &,const std::string &,const std::string &);

const std::string &const_ptr_tipo_operando(const any_const_ptr &operand);
void const_ptr_print(std::ostream &os,const any_const_ptr &operand); 
bool is_const_ptr_to_boost_any(const any_const_ptr &operand);
const boost::any &deref_to_boost_any(const any_const_ptr &operand);
const boost::any &convert_to_boost_any(const any_const_ptr &operand);

bool boost_any_is_any_const_ptr(const boost::any &);
const any_const_ptr &boost_any_to_any_const_ptr(const boost::any &);

#endif
