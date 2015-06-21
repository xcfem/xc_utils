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
//CmdVectorBase.cc

#include "CmdVectorBase.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/nucleo/CmdParser.h"
#include "any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"

//! @brief Asigna el valor de una de sus componentes.
void CmdVectorBase::set_comp(const std::string &cmd,CmdStatus &status)
  {
    const CmdParser &parser= status.Parser();
    if(parser.TieneArgs())
      {
        const std::string &args= parser.GetArgs();
        std::vector<int> indices= crea_vector_int(args);
        const size_t nc= indices.size(); //no. de índices.
        if(nc!=1)
          std::cerr << nombre_clase() << "procesa_comando; error procesando comando: "
                    << cmd << " se leyeron " << nc
                    << " índices, se esperaban 1." << std::endl;
        if(CheckIndice0(indices[0]-1))
          at(indices[0]-1)= interpretaDouble(status.GetString());
        else
          std::cerr << nombre_clase() << "procesa_comando; índice: '"
                    << args << "' fuera de rango." << std::endl;
      }
    if(parser.TieneIndices())
      {
        const std::string &idx= parser.GetIndices();
        std::vector<int> indices= crea_vector_int(idx);
        const size_t nc= indices.size(); //no. de índices.
        if(nc!=1)
          std::cerr << nombre_clase() << "procesa_comando; error procesando comando: "
                    << cmd << " se leyeron " << nc
                    << " índices, se esperaban 1." << std::endl;
        if(CheckIndice0(indices[0]))
          at(indices[0])= interpretaDouble(status.GetString());
        else
          std::cerr << nombre_clase() << "procesa_comando; índice: '"
                    << idx << "' fuera de rango." << std::endl;
      }
  }

//! @brief Carga un objeto CmdVectorBase desde archivo.
bool CmdVectorBase::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(CmdVectorBase) Procesando comando: " << cmd << std::endl;
    if(cmd == "comp") //Asigna el valor de una componente del vector.
      {
        set_comp(cmd,status);
        return true;
      }
    else if(cmd == "coo") //Coordenadas del vector.
      {
        std::vector<double> tmp= crea_vector_double(status.GetString());
        const int nc= tmp.size(); //No. de valores leídos.
        for(int i= 0;i<nc;i++)
          at(i)= tmp[i];
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr CmdVectorBase::GetProp(const std::string &cod) const 
  { 
    return EntCmd::GetProp(cod);
  }
