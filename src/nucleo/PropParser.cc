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
//PropParser.cc

#include "PropParser.h"
#include "xc_basic/src/texto/cadena_carac.h"

//! @brief Constructor por defecto.
PropParser::PropParser(void)
  : CmdParser() {}

//! @brief Constructor.
PropParser::PropParser(const std::string &str)
  : CmdParser(str) {}

//! @brief Devuelve el nombre de la propiedad.
const std::string &PropParser::GetNmbProp(void) const
  { return GetNmbCmd(); }

//! @brief Devuelve el miembro raíz (el primero).
const std::string &PropParser::GetMiembroRaiz(void) const
  { return copia_hasta(GetMiembro(),'.'); }

//! @brief Devuelve los miembros que cuelgan del raíz.
const std::string &PropParser::GetMiembrosRama(void) const
  { return copia_desde(GetMiembro(),'.'); }


//! @brief Imprime los miembros.
void PropParser::Print(std::ostream &os) const
  {
    os << "nombre propiedad: '" << GetNmbProp() << "'" << std::endl
       << "argumentos: '" << GetArgs() << "'" << std::endl
       << "indices: '" << GetIndices() << "'" << std::endl
       << "nombre miembro: '" << GetMiembro() << "'" << std::endl
       << "  miembro raíz: '" << GetMiembroRaiz() << "'"  << std::endl
       << "  resto miembros: '" << GetMiembrosRama() << "'"  << std::endl;
  }
