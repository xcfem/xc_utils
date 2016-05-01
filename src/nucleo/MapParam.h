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
//MapParam.h

#ifndef MAPPARAM_H
#define MAPPARAM_H

#include <string>
#include <map>
#include <vector>
#include <set>

class EntProp;
namespace boost
  {
    class any;
  }

//! @ingroup NUCLEO
//
//! @brief Objeto capaz de almacenar parámetros.
class MapParam
  {
  public:
    typedef std::map<std::string,boost::any> map_params;//!< Tipo contenedor de parametros.
    typedef map_params::iterator param_iterator;//!< Tipo iterador a parámetros.
    typedef map_params::const_iterator param_const_iterator;//!< Tipo iterador a parámetros.
  private:
    typedef map_params::value_type param_value_type; //!< Tipo de los valores del contenedor de parámetros.
    map_params *params;//!< Contenedor de parámetros.
    void libera(void);
    void alloc(const map_params *p= nullptr);
  protected:
    inline map_params *get_map_params(void)
      { return params; }
    inline const map_params *get_map_params(void) const
      { return params; }
   public:
    MapParam(void);
    MapParam(const MapParam &otro);
    MapParam &operator=(const MapParam &otro);
    virtual ~MapParam(void);
    void clear(void);
    size_t size(void) const;
    bool empty(void) const;
    std::string ListaNmbParams(void) const;
    std::set<std::string> SetNombresParams(void) const;
    void SetOwner(EntProp *owr);

    param_iterator begin(void);
    param_iterator end(void);
    param_const_iterator begin(void) const;
    param_const_iterator end(void) const;

    bool ExisteUserParam(const std::string &) const;
    param_iterator BuscaUserParam(const std::string &) const;
    size_t BorraUserParam(const std::string &);
    template <class InputIterator>
    size_t BorraUserParams(InputIterator begin, InputIterator end);
    param_iterator CreaUserParam(const std::string &,const boost::any &);
    param_iterator AsignaUserParam(const param_iterator &,const boost::any &);
    std::string SqlUserParamNames(void) const;
    std::string SqlUserParamValues(void) const;

    void Print(std::ostream &os) const;

    boost::any *GetUserParamPtr(const std::string &cod) const;
  };

template <class InputIterator>
size_t MapParam::BorraUserParams(InputIterator begin, InputIterator end)
  {
    size_t retval= 0;
    if(params)
      {
        if(!params->empty())
          {
            for(InputIterator i=begin;i!=end;i++)
              retval+= params->erase(*i);
          }
      }
    return retval;
  }

#endif
