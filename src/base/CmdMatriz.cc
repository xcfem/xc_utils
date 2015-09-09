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
//CmdMatriz

#include "CmdMatriz.h"
#include "xc_utils/src/base/CmdStatus.h"

//! @brief Constructor.
CmdMatriz::CmdMatriz(m_double &matriz,const std::string &id)
  : m(matriz), id_elem(id) {}

//! @brief Lectura de la matriz desde archivo.
bool CmdMatriz::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(CmdMatriz) Procesando comando: " << cmd << std::endl;
    if(cmd == "dims") //Establece las dimensiones de la matriz.
      {
        const std::string &args= status.Parser().GetArgs();
        std::vector<int> dims= crea_vector_int(args);
        const size_t nc= dims.size(); //dimension de la matriz.
        if(nc!=2)
	  std::cerr << "CmdMatriz::procesa_comando; error procesando comando: "
                    << cmd << " se leyeron " << nc
                    << " valores, se esperaban 2." << std::endl;
        const double v= interpretaDouble(status.GetString());
        m= m_double(dims[0],dims[1],v);
        return true;
      }
    else if(cmd == id_elem) //Asigna el valor de un elemento.
      {
        const std::string &args= status.Parser().GetArgs();
        std::vector<int> indices= crea_vector_int(args);
        const size_t nc= indices.size(); //no. de índices.
        if(nc!=2)
	  std::cerr << "CmdMatriz::procesa_comando; error procesando comando: "
                    << cmd << " se leyeron " << nc
                    << " índices, se esperaban 2." << std::endl;
        if(m.CheckIndices(indices[0],indices[1]))
          m(indices[0],indices[1])= interpretaDouble(status.GetString());
        else
          std::cerr << "CmdMatriz::procesa_comando; indices: '"
                    << args << "' fuera de rango." << std::endl;
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Devuelve una referencia a la matriz.
const m_double &CmdMatriz::GetMatriz(void) const
  { return m; }
