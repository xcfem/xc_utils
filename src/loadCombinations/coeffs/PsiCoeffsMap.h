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
//PsiCoeffsMap.h
//Contenedor de coeficientes de simultaneidad de acciones.

#ifndef PSICOEFFSMAP_H
#define PSICOEFFSMAP_H

#include "xc_utils/src/nucleo/EntCmd.h"
#include "PsiCoeffs.h"
#include <map>


namespace cmb_acc {

class LoadCombinationVector;

//! @ingroup CMBACC
//
//! @brief Contenedor de coeficientes de simultaneidad de acciones.
class PsiCoeffsMap: public EntCmd
  {
  public:
    typedef std::map<std::string,PsiCoeffs> map_coefs;
    typedef map_coefs::iterator iterator;
    typedef map_coefs::const_iterator const_iterator;

  private:
    static PsiCoeffs coefs_por_defecto; //!< Coeficientes por defecto (todos =1.0).
    map_coefs coefs; //!< Conjunto de coefs.

    bool existe(const std::string &nmb) const;
    PsiCoeffs *getPtrCoefs(const std::string &nmb);
    PsiCoeffs *crea_coefs(const std::string &nmb);
  protected:
    friend class ActionContainer;
  public:
    PsiCoeffsMap(void);
    size_t size(void) const;
    static inline const PsiCoeffs &getCoefsPorDefecto(void)
      { return coefs_por_defecto; }
    const PsiCoeffs *getPtrCoefs(const std::string &nmb) const;
    const PsiCoeffs &BuscaCoefs(const std::string &nmb) const;
    void insert(const std::string &,const PsiCoeffs &);
  };
} // fin namespace cmb_acc

#endif
