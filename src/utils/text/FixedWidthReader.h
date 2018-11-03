//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//FixedWidthReader.h

#ifndef FIXEDWIDTHREADER_H
#define FIXEDWIDTHREADER_H

#include <string>
#include <vector>

//! @brief Lee campos de ancho fijo en una cadena de caracteres.
class FixedWidthReader
  {
  public:
    typedef std::vector<size_t> vector_indices;
    typedef vector_indices::iterator indices_iterator;
    typedef vector_indices::const_iterator const_indices_iterator;

    typedef std::vector<std::string> vector_campos;
    typedef vector_campos::iterator iterator;
    typedef vector_campos::const_iterator const_iterator;
  private:
    vector_indices fmt; //Posiciones <inicio,fin> de los campos a leer.
    vector_campos campos; //Valores leídos para cada uno de los campos.
    static const std::string &trata_campo(const std::string &);
  public:
    FixedWidthReader(const size_t &size);
    FixedWidthReader(const std::vector<size_t> &format);

    const size_t numCampos(void) const;
    const std::string &campo(const size_t &i) const;
    std::string &campo(const size_t &i);
    inline iterator campos_begin(void)
      { return campos.begin(); }
    inline const_iterator campos_begin(void) const
      { return campos.begin(); }
    inline iterator campos_end(void)
      { return campos.end(); }
    inline const_iterator campos_end(void) const
      { return campos.end(); }
    const std::string &get_csv_string(void) const;
    const std::string &get_csv_string(const std::string &);
    const std::string &get_indices_string(void) const;

    void set_num_campos(const size_t &nc);
    void set_vector_indices(const vector_indices &);
    void set_field_pair(const size_t &field, const size_t &ini,const size_t &fin);
    void set_string(const std::string &str);
  };

#endif
