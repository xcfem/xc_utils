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
//ArchivosES.h

#ifndef ARCHIVOSES_H
#define ARCHIVOSES_H

#include <string>
#include <map>
#include <vector>
#include <cstdlib>
#include <unistd.h>

//! @ingroup BASE
//
//! @brief Archivos para entrada y salida.
template <class S,class SF>
class ArchivosES
  {
  public:
    typedef std::map<std::string,SF *> map_files; //!< Tipo tabla de archivos.
    typedef typename map_files::iterator iterator;
    typedef typename map_files::const_iterator const_iterator;
  protected:
    S *def_file; //!< Archivo por defecto.
    inline S *DefFile(void)
      { return def_file; }
    map_files map_archivos; //! Contenedor de archivos.
    //Gestión archivos.
    friend class EntCmd;
    void NuevoArchivo(const std::string &nombre,const std::string &path,std::ios_base::openmode mode);
    std::string NuevoArchivoTemporal(const std::string &nombre,const std::string &path,const std::string &suffix,std::ios_base::openmode mode);
    virtual S *GetArchivo(const std::string &nombre);
    bool CierraArchivo(const std::string &nombre);

  private:
    ArchivosES(const ArchivosES &);
    ArchivosES &operator=(const ArchivosES &);

  public:
    ArchivosES(S *s);
    virtual ~ArchivosES(void);
    bool ExisteArchivo(const std::string &nombre) const;
  };

//! @brief Constructor.
template <class S,class SF>
ArchivosES<S,SF>::ArchivosES(S *s)
  :def_file(s)
  {
    if(!def_file)
      std::cerr << "Puntero nulo en archivos de entrada o salida." << std::endl;
  }
   
//! @brief Constructor de copia.
template <class S,class SF>
ArchivosES<S,SF>::ArchivosES(const ArchivosES &)
  {
    std::cerr << "Los objetos de esta clase no deben copiarse." << std::endl;
  }

//! @brief Constructor de copia.
template <class S,class SF>
ArchivosES<S,SF> &ArchivosES<S,SF>::operator=(const ArchivosES &)
  {
    std::cerr << "Los objetos de esta clase no deben llamar al operador asignación." << std::endl;
  }

//! @brief Crea un nuevo archivo de ES.
template <class S,class SF>
void ArchivosES<S,SF>::NuevoArchivo(const std::string &nombre,const std::string &path,std::ios_base::openmode mode)
  {
    const_iterator i= map_archivos.find(nombre);
    if(i==map_archivos.end()) //El archivo no existía con anterioridad.
      {
        SF *tmp= new SF(path.c_str(),mode);
        map_archivos[nombre]= tmp;
      }
  }

//! @brief Crea un nuevo archivo temporal.
template <class S,class SF>
std::string ArchivosES<S,SF>::NuevoArchivoTemporal(const std::string &nombre,const std::string &pth,const std::string &suffix,std::ios_base::openmode mode)
  {
    std::string retval;
    const_iterator i= map_archivos.find(nombre);
    if(i==map_archivos.end()) //El archivo no existía con anterioridad.
      {
        SF *tmp= NULL;
        retval= pth+"XXXXXX"+suffix;
        const int suffixlen= suffix.length();
        std::vector<char> dst_path(retval.begin(), retval.end());
        dst_path.push_back('\0');

        int fd = mkstemps(&dst_path[0],suffixlen);
        if(fd != -1)
          {
            retval.assign(dst_path.begin(), dst_path.end() - 1);
            tmp= new SF(retval.c_str(),mode);
            ::close(fd);
          }
        else
          std::cerr << "Error en NuevoArchivoTemporal pth= " 
                    << pth << " suffix= " << suffix
                    << " path= " << retval << std::endl;
        map_archivos[nombre]= tmp;
      }
    return retval;
  }

//! @brief Devuelve un puntero al stream que corresponde al nombre que se pasa
//! como parámetro, si tal stream no existe se devuelve el correspondiente al archivo
//! de ES por defecto.
template <class S,class SF>
bool ArchivosES<S,SF>::ExisteArchivo(const std::string &nombre) const
  {
    const_iterator i= map_archivos.find(nombre);
    return (i!=map_archivos.end());
  }

//! @brief Devuelve un puntero al stream que corresponde al nombre que se pasa
//! como parámetro, si tal stream no existe se devuelve el correspondiente al archivo
//! de ES por defecto.
template <class S,class SF>
S *ArchivosES<S,SF>::GetArchivo(const std::string &nombre)
  {
    S *retval= def_file;
    iterator i= map_archivos.find(nombre);
    if(i!=map_archivos.end())
      retval= (*i).second;
    else
      std::cerr << "ArchivosES::CierraArchivoES; no se encontró el archivo de nombre: '"
                << nombre << "'" << std::endl;
    return retval;
  }

//! @brief Crea un nuevo archivo de ES.
template <class S,class SF>
bool ArchivosES<S,SF>::CierraArchivo(const std::string &nombre)
  {
    bool retval= false;
    iterator i= map_archivos.find(nombre);
    if(i!=map_archivos.end())
      {
        SF *tmp= (*i).second;
        if(tmp)
          {
            tmp->close();
            delete tmp;
          }
        else
	  std::cerr << "Puntero nulo en archivos E/S." << std::endl;
        map_archivos.erase(i);
        retval= true;
      }
    else
      std::cerr << "ArchivosES::CierraArchivoES; no existe ningún archivo abierto con el nombre: '" 
                << nombre << "'\n";
    return retval;
  }

//! @brief Destructor.
template <class S,class SF>
ArchivosES<S,SF>::~ArchivosES(void)
  {
    //Cierra archivos de ES.
    iterator j= map_archivos.begin();
    for(;j!=map_archivos.end();j++)
      {
        SF *tmp= (*j).second;
        if(tmp)
          {
            tmp->close();
            delete tmp;
          }
        else
	  std::cerr << "Puntero nulo en archivos E/S." << std::endl;
      }
    map_archivos.erase(map_archivos.begin(),map_archivos.end());
  }


#endif
