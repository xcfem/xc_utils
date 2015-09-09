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
//MapFamiliasAcc.h
//Contenedor de familias de acciones.

#ifndef MAPFAMILIASACC_H
#define MAPFAMILIASACC_H

#include "xc_utils/src/base/EntConNmb.h"
#include <map>


namespace cmb_acc {

class FamiliaAcciones;
class VectorCombinaciones;
class MapCoefsPsi;
class Accion;
class VRAccion;
class AccionesClasificadas;

//! @ingroup CMBACC
//
//! @brief Contenedor de familias de acciones.
class MapFamiliasAcc: public EntConNmb
  {
  public:
    typedef std::map<std::string,FamiliaAcciones *> map_familias;
    typedef map_familias::iterator iterator;
    typedef map_familias::const_iterator const_iterator;

  private:
    map_familias familias; //!< Conjunto de familias.

    bool existe(const std::string &nmb) const;
    FamiliaAcciones *crea_familia_acc(const std::string &nmb);
    FamiliaAcciones *busca_familia_acc(const std::string &nmb);
    const FamiliaAcciones *busca_familia_acc(const std::string &nmb) const;
    void clear(void);
    MapFamiliasAcc(const MapFamiliasAcc &otro);
    MapFamiliasAcc &operator=(const MapFamiliasAcc &otro);
  protected:
    friend class AccionesClasificadas;
    void for_each_accion(CmdStatus &,const std::string &);
    virtual bool procesa_comando(CmdStatus &);
  public:
    MapFamiliasAcc(const std::string &nmb);
    VRAccion &inserta(const std::string &,const Accion &,const std::string &nmb_coefs_psi="");
    VectorCombinaciones GetCombinaciones(const bool &elu,const bool &sit_accidental) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
    size_t getNumAcciones(void) const;
    const MapCoefsPsi *getPtrCoefsPsi(void) const;
    bool Vacia(void) const;
    virtual ~MapFamiliasAcc(void);
  };
} // fin namespace cmb_acc

#endif
