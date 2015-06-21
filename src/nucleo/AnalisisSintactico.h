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
// AnalisisSintactico.h: interface for the AnalisisSintactico class.
//
//////////////////////////////////////////////////////////////////////
#ifndef ANALISISSINTACTICO_H
#define ANALISISSINTACTICO_H


#include <iostream>
#include <string>
#include "AnalisisLexico.h"
#include "TokenList.h"

//! @ingroup NUCLEO
//
//! @brief Analizador sintáctico.
class AnalisisSintactico
  {
  private:
    AnalisisLexico LA;
    TokenList input; //!< Signos de entrada.
    std::stack<size_t> num_entradas; //!< Número de entradas entre paréntesis o corchetes separadas por comas.
    static void TrataParentDcho(TokenStack &pila,TokenList &lista,const size_t &);
    static void TrataCorcheteDcho(TokenStack &,TokenList &,const size_t &);
    static void TrataOperador(TokenStack &pila,const Token &t,TokenList &lista);
    static void TrataComa(TokenStack &pila,TokenList &lista);
    static void TrataFinExpr(TokenStack &pila,TokenList &lista);
  public:
    AnalisisSintactico(const std::string &in= "");
    void setNewInput(const std::string &in);
    TokenList Analiza(void);
    const std::string &Input(void) const
      { return LA.Input(); }
  };

#endif
