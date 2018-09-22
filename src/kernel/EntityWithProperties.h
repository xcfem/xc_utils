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
//EntityWithProperties.h

#ifndef ENTPROP_H
#define ENTPROP_H

#include <string>

//! @ingroup NUCLEO
//
//! @brief Object that can return properties as Python objects.
class EntityWithProperties
  {
  private:
    EntityWithProperties *owner; //! Objeto propietario de ESTE.
  protected:
    static int verbosity; //!< Verbosity level.
   public:
    EntityWithProperties(EntityWithProperties *owr= nullptr);
    EntityWithProperties(const EntityWithProperties &);
    EntityWithProperties &operator=(const EntityWithProperties &);
    static const int &getVerbosityLevel(void);
    static void setVerbosityLevel(const int &);
    virtual std::string getClassName(void) const;
    void set_owner(EntityWithProperties *owr);
    inline EntityWithProperties *Owner(void)
      { return owner; }
    inline const EntityWithProperties *Owner(void) const
      { return owner; }
  };

#endif
