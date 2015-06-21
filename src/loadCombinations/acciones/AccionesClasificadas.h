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
//AccionesClasificadas.h
//Almacena todas las familias de acciones para la estructura o el elemento estructural.

#ifndef ACCIONESCLASIFICADAS_H
#define ACCIONESCLASIFICADAS_H

#include "FamiliaAcciones.h"
#include "MapFamiliasAcc.h"
#include "xc_utils/src/loadCombinations/coefs/MapCoefsPsi.h"

namespace cmb_acc{
//! @ingroup CMBACC
//
//! @brief Almacena todas las familias de acciones.
class AccionesClasificadas: public EntCmd
  {
  private:
    FamiliaAcciones G; //!< Acciones permanentes.
    MapFamiliasAcc G_aster; //!< Acciones permanentes de valor no constante.
    FamiliaAcciones Q; //!< Acciones variables.
    FamiliaAcciones A; //!< Acciones accidentales.
    FamiliaAcciones AS; //!< Acciones sísmicas.
    MapCoefsPsi coefs_psi; //!< Coeficientes de simultaneidad de las acciones.

    VectorCombinaciones GetCombinacionesG(const bool &elu,const bool &sit_accidental) const;
    VectorCombinaciones GetCombinacionesG_aster(const bool &elu,const bool &sit_accidental) const;
    VectorCombinaciones GetCombinacionesQ(const bool &elu,const bool &sit_accidental,short int r,int d=-1,short int rr=-1) const;
    VectorCombinaciones GetCombinacionesA(short int r,int d=-1,short int rr=-1) const;
    VectorCombinaciones GetCombinacionesAS(short int r,int d=-1,short int rr=-1) const;
    VectorCombinaciones GetPermanentes(const bool &elu,const bool &sit_accidental) const;
    VectorCombinaciones GetVariables(const VectorCombinaciones &permanentes,const bool &elu,const bool &sit_accidental,const short int &v) const;
    VectorCombinaciones GetAccSis(const VectorCombinaciones &previas,const FamiliaAcciones &Acc) const;

  protected:
    friend class MapPondAcciones;
    void for_each_accion(CmdStatus &,const std::string &);
    virtual bool procesa_comando(CmdStatus &status);
  public:
    AccionesClasificadas(const MapCoefsPsi &coefs= MapCoefsPsi());
    inline virtual ~AccionesClasificadas(void) {}

    VRAccion &inserta(const std::string &,const Accion &,const std::string &nmb_coefs_psi="",const std::string &subfamilia= "");

    const FamiliaAcciones &getAccionesPermanentes(void) const;
    void setAccionesPermanentes(const FamiliaAcciones &);
    const MapFamiliasAcc &getAccionesPermanentesNC(void) const;
    void setAccionesPermanentesNC(const MapFamiliasAcc &);
    const FamiliaAcciones &getAccionesVariables(void) const;
    void setAccionesVariables(const FamiliaAcciones &);
    const FamiliaAcciones &getAccionesAccidentales(void) const;
    void setAccionesAccidentales(const FamiliaAcciones &);
    const FamiliaAcciones &getAccionesSismicas(void) const;
    void setAccionesSismicas(const FamiliaAcciones &);

    //Estados límite últimos.
    VectorCombinaciones GetPersistentesOTransit(void) const;
    VectorCombinaciones GetAccidentales(void) const;
    VectorCombinaciones GetSismicas(void) const;
    VectorCombinaciones GetCombELU(void) const;
    //Estados límite de servicio.
    VectorCombinaciones GetPocoFrecuentes(void) const;
    VectorCombinaciones GetFrecuentes(void) const;
    VectorCombinaciones GetCuasiPermanentes(void) const;
    VectorCombinaciones GetCombELS(void) const;

    const MapCoefsPsi *getPtrCoefsPsi(void) const
      { return &coefs_psi; }
    const MapCoefsPsi &getCoefsPsi(void) const
      { return coefs_psi; }
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };
} //fin namespace nmb_acc.

#endif
