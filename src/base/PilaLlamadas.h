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
//PilaLlamadas.h

#ifndef PILALLAMADAS_H
#define PILALLAMADAS_H

#include <deque>
#include <set>
#include <ostream>

class EntProp;
class prop_iterator;
class EntCmd;
class CmdStatus;
class any_const_ptr;
namespace boost
  {
    class any;
  }

//! @ingroup BASE
//
//! @brief Pila de punteros que almacena la secuencia de llamadas
//! al método LeeCmd del CmdStatus hasta el objeto que se está leyendo
//! actualmente.
class PilaLlamadas: private std::deque<EntCmd *>
  {
    static std::string last_cod;
  public:
    typedef std::deque<EntCmd *> stk_llamadas;
    typedef stk_llamadas::iterator iterator;
    typedef stk_llamadas::const_iterator const_iterator;
    
    PilaLlamadas(void);
    bool SetObjetoActual(EntCmd *ptr);
    inline const EntCmd *GetObjetoActual(void) const
      { return front(); }
    bool PopObjetoActual(void);
    inline size_t empty(void) const
      { return stk_llamadas::empty(); }
    inline size_t size(void) const
      { return stk_llamadas::size(); }
    inline const_iterator begin(void) const
      { return stk_llamadas::begin(); }
    inline const_iterator end(void) const
      { return stk_llamadas::end(); }
    inline iterator begin(void)
      { return stk_llamadas::begin(); }
    inline iterator end(void)
      { return stk_llamadas::end(); }

    std::string getRuta(void) const;

    const_iterator has_user_param(const std::string &) const;
    bool existe_user_param(const std::string &) const;

    any_const_ptr GetProp(const std::string &cod) const;
    bool procesa_comando(CmdStatus &status,EntCmd *owr);
    virtual void imprime_ruta(std::ostream &os) const;
    virtual ~PilaLlamadas(void) {};
  };

#endif
