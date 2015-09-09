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
//MapPropVar.h

#ifndef MAPPROPVAR_H
#define MAPPROPVAR_H

#include "MapParam.h"

//! @ingroup NUCLEO
//
//! @brief Objeto encargado de almacenar propiedades y variables.
class MapPropVar
  {
    MapParam props;//!< Contenedor de propiedades.
    MapParam vars;//!< Contenedor de variables.
   public:
    MapPropVar(void);
    void clearProps(void);
    void clearVars(void);
    size_t size(void) const;
    bool empty(void) const;
    const std::set<std::string> &SetNombresParams(void) const;
    void SetOwner(EntProp *owr);

    const MapParam &Vars(void) const;
    MapParam &Vars(void);
    const MapParam &Props(void) const;
    MapParam &Props(void);

    bool ExisteUserParam(const std::string &) const;
    MapParam::param_iterator BuscaUserParam(const std::string &) const;
    size_t BorraUserParam(const std::string &);
    template <class InputIterator>
    size_t BorraUserParams(InputIterator begin, InputIterator end);
    MapParam::param_iterator AsignaUserParam(const MapParam::param_iterator &,const boost::any &);
    void AsignaElemUserParam(const MapParam::param_iterator &,const boost::any &,const boost::any &);

    void Print(std::ostream &os) const;

    boost::any *GetUserParamPtr(const std::string &cod) const;
  };

template <class InputIterator>
size_t MapPropVar::BorraUserParams(InputIterator begin, InputIterator end)
  {
    size_t retval= 0;
    for(InputIterator i=begin;i!=end;i++)
      retval+= BorraUserParam(*i);
    return retval;
  }

#endif
