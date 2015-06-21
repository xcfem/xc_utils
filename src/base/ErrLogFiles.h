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
//log_file.h
//Arhivo para imprimir errores y avisos.

#ifndef LOG_FILE_H
#define LOG_FILE_H

#include <iostream>
#include <fstream>
#include <string>

//! @ingroup BASE
//
//! @brief Archivos para imprimir errores y avisos.
class ErrLogFiles
  {
    std::string nmbErrFile;
    std::ofstream *salida_err_file;
    std::string nmbLogFile;
    std::ofstream *salida_log_file;
  public:
    ErrLogFiles(void);
    std::ostream &getErrFile(void);
    std::ostream &getLogFile(void);
    inline const std::string &getErrFileName(void) const
      { return nmbErrFile; }
    void setErrFileName(const std::string &filename);
    inline const std::string &getLogFileName(void) const
      { return nmbLogFile; }
    void setLogFileName(const std::string &filename);
  };

#endif
