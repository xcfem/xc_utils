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
//ArchivosEntrada.cxx

#include "ArchivosEntrada.h"
#include <cassert>


//! @brief Constructor.
ArchivosEntrada::ArchivosEntrada(std::istream *input)
  :ArchivosES<std::istream,std::ifstream>(input)
  {
    if(!def_file)
      std::cerr << "Puntero nulo en archivos de entrada." << std::endl;
  }

//! @brief Devuelve verdadero si se puede seguir leyendo del archivo.
bool ArchivosEntrada::good(const std::string &nombre) const
  {
    const_iterator i= map_archivos.find(nombre);
    if(i!=map_archivos.end())
      {
        std::ifstream *tmp= (*i).second;
        assert(tmp);
        return tmp->good();
      }
    else
      {
        std::cerr << "ArchivosEntrada::good; no existe ningún archivo abierto con el nombre: '" 
                  << nombre << "'\n";
        return false;
      }
  }
