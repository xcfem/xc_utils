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
//CmdVectorBase.h

#ifndef CMD_VECTOR_BASE_H
#define CMD_VECTOR_BASE_H

#include "xc_utils/src/nucleo/EntCmd.h"

//! @ingroup BASE
//
//!  \brief Clase base para leer vectores.
//!  
class CmdVectorBase: public EntCmd
  {
  protected:
    void set_comp(const std::string &cmd,CmdStatus &status);
    virtual bool procesa_comando(CmdStatus &status);
  public:
    //! @brief Constructor por defecto.
    CmdVectorBase(void)
      : EntCmd() {}
    //! @brief Devuelve el elemento cuya fila se pasa como parámetro.
    virtual double &at(const size_t &f)= 0;
    //! @brief Devuelve el elemento cuya fila se pasa como parámetro.
    virtual const double &at(const size_t &f) const= 0;
    //! @brief Chequea el índice que se le pasa como parámetro.
    virtual bool CheckIndice0(const size_t &i) const= 0;
    any_const_ptr GetProp(const std::string &) const;
    //! @brief Destructor.
    virtual ~CmdVectorBase(void) {}
  };

#endif
