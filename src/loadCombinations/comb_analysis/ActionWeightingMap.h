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
//ActionWeightingMap.h
//Contenedor de ponderaciones de acciones.

#ifndef MAPPONDACCIONES_H
#define MAPPONDACCIONES_H

#include "xc_utils/src/nucleo/EntCmd.h"
#include "xc_utils/src/loadCombinations/coeffs/PsiCoeffsMap.h"
#include <map>


namespace cmb_acc {

class Action;
class ActionRValue;
class ActionContainer;
class LoadCombinations;

//! @ingroup CMBACC
//
//! @brief Contenedor de ponderaciones de acciones.
class ActionWeightingMap: public EntCmd
  {
  public:
    typedef std::map<std::string,ActionContainer *> map_ponderaciones;
    typedef map_ponderaciones::iterator iterator;
    typedef map_ponderaciones::const_iterator const_iterator;

  private:
    map_ponderaciones ponderaciones; //!< Conjunto de ponderaciones.

    bool existe(const std::string &nmb) const;
    ActionContainer *crea_ponderacion(const std::string &nmb,const PsiCoeffsMap &coefs= PsiCoeffsMap());
    ActionContainer *busca_ponderacion(const std::string &nmb);
    const ActionContainer *busca_ponderacion(const std::string &nmb) const;
    void clear(void);
    void copia(const map_ponderaciones &pond);
  protected:
    friend class ActionContainer;
    void for_each(CmdStatus &,const std::string &);
    void for_each_accion(CmdStatus &,const std::string &);
    virtual bool procesa_comando(CmdStatus &);
  public:
    ActionWeightingMap(void);
    ActionWeightingMap(const ActionWeightingMap &otro);
    ActionWeightingMap &operator=(const ActionWeightingMap &otro);
    virtual ~ActionWeightingMap(void);
    cmb_acc::ActionContainer *defPonderacion(const std::string &,const PsiCoeffsMap &coefs= PsiCoeffsMap());

    ActionRValue &inserta(const std::string &pond,const std::string &,const Action &,const std::string &nmb_coefs_psi="",const std::string &subfamilia= "");

    size_t size(void) const;
    bool Vacia(void) const;
    iterator begin(void);
    const_iterator begin(void) const;
    iterator end(void);
    const_iterator end(void) const;
    LoadCombinations getLoadCombinations(void);
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

} // fin namespace cmb_acc

#endif
