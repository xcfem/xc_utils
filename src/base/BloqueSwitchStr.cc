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
//BloqueSwitchStr.cc

#include "BloqueSwitchStr.h"
#include "xc_utils/src/base/CmdStatus.h"

//! @brief Constructor.
BloqueSwitchStr::BloqueSwitchStr(EntCmd *owner)
  : BloqueCond(owner) {}

//! @brief Constructor.
BloqueSwitchStr::BloqueSwitchStr(EntCmd *owner,const std::string &cnd,const std::string &por_defecto)
  : BloqueCond(owner,cnd,por_defecto) {}

//! Lee un objeto BloqueSwitchStr desde archivo
//! Soporta los comandos:
//! -case["idx"]: Lee el bloque de código asociado a la clave «idx».
bool BloqueSwitchStr::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "BloqueSwitchStr; procesando comando: " << cmd << std::endl;
    if(cmd == "case")
      {
        const std::string &indices= status.Parser().GetIndices();
        std::vector<std::string> ind= crea_vector_string(indices);
        const size_t nc= ind.size(); //no. de índices.
        if(nc!=1)
	  std::cerr << "(BloqueSwitchStr) Procesando comando: " << cmd
                    << "; error, se leyeron " << nc
                    << " índices, se esperaba 1." << std::endl;
        const std::string bloque= status.GetBloque();
        bloques[ind[0]]= bloque;
        return true;
      }
    else
      return BloqueCond::procesa_comando(status);
  }

//! @brief Devuelve verdadero si existe el índice que se pasa
//! como parámetro.
bool BloqueSwitchStr::hasCase(const std::string &idx) const
  {
    std::map<std::string,std::string>::const_iterator i= bloques.find(idx);
    return (i!=bloques.end());
  }


//! @brief Devuelve (si existe) el bloque de código que corresponde
//! al índice que se pasa como parámetro.
const std::string &BloqueSwitchStr::Bloque(const std::string &idx) const
  {
    static const std::string malo="nil";
    std::map<std::string,std::string>::const_iterator i= bloques.find(idx);
    if(i!=bloques.end())
      return (*i).second;
    else
      return malo;
  }
