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
//MapAuxData.h

#ifndef MAPAUXDATA_HXX
#define MAPAUXDATA_HXX

#include <string>
#include <map>


//! @ingroup BASE
//
//! @brief Estado para procesa comando
class MapAuxData
  {
  public:
    typedef std::map<std::string,void *> map_aux_data; //!< Tabla de datos auxiliares.
    typedef map_aux_data::const_iterator const_iterator;
    typedef map_aux_data::iterator iterator;
    typedef map_aux_data::reference reference;
    typedef map_aux_data::const_reference const_reference;
  private:
    map_aux_data aux_data; //!< Tabla de punteros a datos auxiliares.
    
  public:
    //! @brief Constructor por defecto.
    MapAuxData(void);
    void ListaAuxData(std::ostream &os) const;
    void BorraAuxData(void);
    void BorraAuxData(const std::string &clave);
    void *inserta(const std::string &,void *);
    void *operator[](const std::string &);
    const void *operator[](const std::string &) const;
  };

#endif
