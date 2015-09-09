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
//Path.h
//Clase para leer cronometradores.

#ifndef PATH_H
#define PATH_H

#include "../nucleo/EntCmd.h"

#include <boost/filesystem.hpp>

//! @ingroup BASE
//
//!  @brief Clase para gestionar rutas de archivos.
class Path: public EntCmd
  {
    boost::filesystem::path pth; //!< path.
    Path(const boost::filesystem::path &);
  protected:
    bool procesa_comando(CmdStatus &status);
  public:
    Path(const std::string &s="");

    void clear();
    void swap(Path &);
    Path& remove_filename();
    Path& replace_extension(const std::string &new_extension= "");

    std::string root_name(void) const;
    std::string root_directory(void) const;
    Path root_path(void) const;
    Path relative_path(void) const;

    std::string string(void) const;
    Path parent_path(void) const;
    std::string filename(void) const;
    std::string stem(void) const;
    std::string extension(void) const;

    bool empty(void) const;
    bool is_complete() const;
    bool has_root_name() const;
    bool has_root_directory() const;
    bool has_root_path() const;
    bool has_relative_path() const;
    bool has_filename() const;
    bool has_parent_path() const;
    
    any_const_ptr GetProp(const std::string &) const;
  };
#endif
