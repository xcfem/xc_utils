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
//MapCoefsPsi.h
//Contenedor de coeficientes de simultaneidad de acciones.

#ifndef MAPCOEFSPSI_H
#define MAPCOEFSPSI_H

#include "xc_utils/src/nucleo/EntCmd.h"
#include "CoefsPsi.h"
#include <map>


namespace cmb_acc {

class LoadCombinationVector;

//! @ingroup CMBACC
//
//! @brief Contenedor de coeficientes de simultaneidad de acciones.
class MapCoefsPsi: public EntCmd
  {
  public:
    typedef std::map<std::string,CoefsPsi> map_coefs;
    typedef map_coefs::iterator iterator;
    typedef map_coefs::const_iterator const_iterator;

  private:
    static CoefsPsi coefs_por_defecto; //!< Coeficientes por defecto (todos =1.0).
    map_coefs coefs; //!< Conjunto de coefs.

    bool existe(const std::string &nmb) const;
    CoefsPsi *getPtrCoefs(const std::string &nmb);
    CoefsPsi *crea_coefs(const std::string &nmb);
  protected:
    friend class AccionesClasificadas;
    void for_each(CmdStatus &,const std::string &);
    virtual bool procesa_comando(CmdStatus &);
  public:
    MapCoefsPsi(void);
    size_t size(void) const;
    static inline const CoefsPsi &getCoefsPorDefecto(void)
      { return coefs_por_defecto; }
    const CoefsPsi *getPtrCoefs(const std::string &nmb) const;
    const CoefsPsi &BuscaCoefs(const std::string &nmb) const;
    void insert(const std::string &,const CoefsPsi &);
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };
} // fin namespace cmb_acc

#endif
