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
//CmdFixedWidthReader.h
//Entidad para leer matrices.

#ifndef CMDFIXEDWIDTHREADER_H
#define CMDFIXEDWIDTHREADER_H

#include "../nucleo/EntCmd.h"
#include "xc_basic/src/texto/FixedWidthReader.h"

//! @ingroup BASE
//
//!  @brief Clase para leer cronometradores.
class CmdFixedWidthReader: public EntCmd
  {
    FixedWidthReader reader; //!< FixedWidthReader a leer.
    friend class EntCmd;
    inline FixedWidthReader &getReader(void)
      { return reader; }
    inline const FixedWidthReader &getReader(void) const
      { return reader; }
  protected:
    bool procesa_comando(CmdStatus &status);
  public:
    CmdFixedWidthReader(const size_t &);
    any_const_ptr GetProp(const std::string &) const;
  };
#endif
