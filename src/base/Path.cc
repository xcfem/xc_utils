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
//Path

#include "Path.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "any_const_ptr.h"


//! @brief Constructor.
Path::Path(const std::string &str)
  : pth(str) {}

//! @brief Constructor.
Path::Path(const boost::filesystem::path &p)
  : pth(p) {}

//! @brief Lectura del comandos desde archivo.
bool Path::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(Path) Procesando comando: " << cmd << std::endl;
    if(cmd=="clear")
      {
        status.GetBloque(); //Ignora entrada.
        clear();
        return true;
      }
    else if(cmd=="remove_filename")
      {
        status.GetBloque(); //Ignora entrada.
        remove_filename();
        return true;
      }
    else if(cmd=="replace_extension")
      {
        const std::string ext= interpretaString(status.GetString());
        replace_extension(ext);
        return true;
      }
    else      
      return EntCmd::procesa_comando(status);
  }

//! @brief Borra la ruta.
void Path::clear()
  { pth.clear(); }

//! @brief Intercambia la ruta con la que se pasa como parámetro.
void Path::swap(Path &otra)
  { pth.swap(otra.pth); }

//! @brief Elimina el nombre del archivo.
Path &Path::remove_filename(void)
  {
    pth.remove_filename();
    return *this;
  }

//! @brief Reemplaza la extensión.
Path &Path::replace_extension(const std::string &new_extension)
  {
    pth.replace_extension(new_extension);
    return *this;
  }

//! @brief Devuelve una referencia a la Timer.
std::string Path::string(void) const
  { return pth.string(); }

//! @brief Devuelve el directorio en el que se aloja el archivo.
Path Path::parent_path(void) const
  {
    Path retval(pth.parent_path());
    return retval;
  }

std::string Path::root_name(void) const
  { return pth.root_name().string(); }

std::string Path::root_directory(void) const
  { return pth.root_directory().string(); }

Path Path::root_path(void) const
  { return Path(pth.root_path()); }

Path Path::relative_path(void) const
  { return Path(pth.relative_path()); }

//! @brief Devuelve el nombre del archivo.
std::string Path::filename(void) const
  { return pth.filename().string(); }

//! @brief Devuelve el nombre del archivo sin extensión.
std::string Path::stem(void) const
  { return pth.stem().string(); }

//! @brief Devuelve la extensión  del archivo.
std::string Path::extension(void) const
  { return pth.extension().string(); }

//! @brief Devuelve verdadero si está vacío.
bool Path::empty(void) const
  { return pth.empty(); }

//! @brief Devuelve verdadero si está completo.
bool Path::is_complete() const
  { return pth.is_complete(); }

//! @brief Devuelve verdadero si ¿?.
bool Path::has_root_name() const
  { return pth.has_root_name(); }

//! @brief Devuelve verdadero si ¿?.
bool Path::has_root_directory() const
  { return pth.has_root_directory(); }

//! @brief Devuelve verdadero si ¿?.
bool Path::has_root_path() const
  { return pth.has_root_path(); }

//! @brief Devuelve verdadero si tiene una ruta relativa.
bool Path::has_relative_path() const
  { return pth.has_relative_path(); }

//! @brief Devuelve verdadero si tiene nombre de archivo.
bool Path::has_filename() const
  { return pth.has_filename(); }

//! @brief Devuelve verdadero si tiene ruta «madre».
bool Path::has_parent_path() const
  { return pth.has_parent_path(); }

//! Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa 
//! como parámetro. 
any_const_ptr Path::GetProp(const std::string &cod) const 
  {
    if(cod == "getString")
      {
        tmp_gp_str= string();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "isEmpty")
      {
        tmp_gp_bool= empty();
        return any_const_ptr(tmp_gp_bool);
      }
    else if(cod == "hasFileName")
      {
        tmp_gp_bool= has_filename();
        return any_const_ptr(tmp_gp_bool);
      }
    else if(cod == "hasParentPath")
      {
        tmp_gp_bool= has_filename();
        return any_const_ptr(tmp_gp_bool);
      }
    else if(cod == "getParentPath")
      {
        tmp_gp_path= parent_path();
        return any_const_ptr(tmp_gp_path);
      }
    else if(cod == "getFileName")
      {
        tmp_gp_str= filename();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "getStem")
      {
        tmp_gp_str= stem();
        return any_const_ptr(tmp_gp_str);
      }
     else if(cod == "getRootName")
      {
        tmp_gp_str= root_name();
        return any_const_ptr(tmp_gp_str);
      }
     else if(cod == "getRootDirectory")
      {
        tmp_gp_str= root_directory();
        return any_const_ptr(tmp_gp_str);
      }
     else if(cod == "getRootPath")
      {
        tmp_gp_path= root_path();
        return any_const_ptr(tmp_gp_path);
      }
     else if(cod == "getRelativePath")
      {
        tmp_gp_path= relative_path();
        return any_const_ptr(tmp_gp_path);
      }
    else
      return EntCmd::GetProp(cod);
  }
