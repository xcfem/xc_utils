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
//EntProp.h

#ifndef ENTPROP_H
#define ENTPROP_H

#include <string>

//! @ingroup NUCLEO
//
//! @brief Objeto capaz de devolver propiedades.
class EntProp
  {
  private:
    EntProp *owner; //! Objeto propietario de ESTE.
  protected:
    static int verbosity; //!< Verbosity level.
   public:
    EntProp(EntProp *owr= nullptr);
    EntProp(const EntProp &otro);
    EntProp &operator=(const EntProp &otro);
    static const int &getVerbosityLevel(void);
    static void setVerbosityLevel(const int &);
    virtual std::string nombre_clase(void) const;
    void set_owner(EntProp *owr);
    inline EntProp *Owner(void)
      { return owner; }
    inline const EntProp *Owner(void) const
      { return owner; }
  };

#endif
