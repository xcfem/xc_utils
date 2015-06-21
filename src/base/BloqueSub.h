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
//BloqueSub.h
//Subrutina.

#ifndef BLOQUESUB_H
#define BLOQUESUB_H

#include "BloqueBase.h"
#include <vector>

//! @ingroup BASE
//
//!  @brief Bloque de instrucciones para Peell.
class BloqueSub: public BloqueBase
  {
    friend class EntCmd;
    friend boost::any interpreta_string_to_boost_any(EntCmd &,const std::string &,const std::string &,const std::string &,const std::string &);
  public:
    typedef std::vector<MapParam::param_iterator> vector_orden_argumentos;
    typedef vector_orden_argumentos::iterator orden_argumentos_iterator;
    typedef vector_orden_argumentos::const_iterator orden_argumentos_const_iterator;
    typedef vector_orden_argumentos::reverse_iterator orden_argumentos_reverse_iterator;
    typedef vector_orden_argumentos::const_reverse_iterator orden_argumentos_const_reverse_iterator;
  private:
    void copia_orden_argumentos(const vector_orden_argumentos &);
  protected:
    vector_orden_argumentos orden_argumentos; //!< Orden de los argumentos de la función.
    void procesa_def_parametros(const std::string &str);
    void valores_parametros(const size_t &argc) const;

    orden_argumentos_const_iterator get_iterator(const std::string &) const;
    MapParam::param_iterator get_arg_iterator(const std::string &) const;

    virtual bool procesa_comando(CmdStatus &status);

    //! @brief Constructor.
    BloqueSub(EntCmd *owner,const std::string &nmb);
    BloqueSub(EntCmd *owner,const std::string &nmb,const std::string &b,const std::string &def_args);
  public:
    BloqueSub(const BloqueSub &otro);
    BloqueSub &operator=(const BloqueSub &otro);
    size_t NumParametros(void) const;
    void Run(const EntCmd *caller) const;
    bool ExisteNombreArgumento(const std::string &) const;
    any_const_ptr GetValorArg(const std::string &cod) const;
    any_const_ptr GetPropLocal(const std::string &cod) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

#endif
