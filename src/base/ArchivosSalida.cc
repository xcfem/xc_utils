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
//ArchivosSalida.cxx

#include "ArchivosSalida.h"


//! @brief Constructor.
ArchivosSalida::ArchivosSalida(std::ostream *output)
  :ArchivosES<std::ostream,std::ofstream>(output)
  {
    if(!def_file)
      std::cerr << "Puntero nulo en archivos de salida." << std::endl;
  }



//! @brief Devuelve un puntero al stream que corresponde al nombre que se pasa
//! como parámetro, si tal stream no existe se devuelve el correspondiente al archivo
//! de salida por defecto.
std::ostream *ArchivosSalida::GetArchivo(const std::string &nombre)
  {
    std::ostream *retval= DefFile();
    if(!nombre.empty())
      {
        iterator i= map_archivos.find(nombre);
        if(i!=map_archivos.end())
          retval= (*i).second;
        else if(nombre == "out")
          retval= &std::cout;
        else if(nombre == "err")
          retval= &std::cerr;
        else if(nombre == "log")
          retval= &std::clog;
        else
          std::cerr << "ArchivosSalida::GetArchivoSalida; no se encontró el archivo de salida de nombre: '"
                    << nombre << "'" << std::endl;
      }
    return retval;
  }

