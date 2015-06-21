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
//CmdFixedWidthReader

#include "CmdFixedWidthReader.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "any_const_ptr.h"

//! @brief Constructor.
CmdFixedWidthReader::CmdFixedWidthReader(const size_t &num_campos)
  : reader(num_campos) {}

//! @brief Lectura de la FixedWidthReader desde archivo.
bool CmdFixedWidthReader::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(CmdFixedWidthReader) Procesando comando: " << cmd << std::endl;
    if(cmd == "setVectorIndices")
      {
	FixedWidthReader::vector_indices tmp= crea_vector_size_t(status.GetString());
        reader.set_vector_indices(tmp);
        return true;
      }
    else if(cmd == "setString")
      {
        reader.set_string(interpretaString(status.GetString()));
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr CmdFixedWidthReader::GetProp(const std::string &cod) const 
  {
    if(verborrea>4)
      std::clog << "(CmdFixedWidthReader::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod == "size")
      {
        tmp_gp_szt= reader.numCampos();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "getCsvString")
      {
        tmp_gp_str= reader.get_csv_string();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "getIndicesString")
      {
        tmp_gp_str= reader.get_indices_string();
        return any_const_ptr(tmp_gp_str);
      }
    else
      return EntCmd::GetProp(cod);
  }
