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
//TokenList.h

#ifndef TOKENLIST_H
#define TOKENLIST_H

#include "Signos.h"
#include <deque>
#include <stack>

//! @ingroup NUCLEO
//
//! @brief Token list.
class TokenList: public std::deque<Token>
  {
    friend class AnalisisSintactico;
  private:
    void DetectaNeg(void);
    void DetectaOpPrefix(void);
    void DetectaOpIgual(void);
    void DetectaOpMenorOIgual(void);
    void DetectaOpMayorOIgual(void);
    void DetectaOpDistinto(void);
    void DetectaOpRcl(void);
    void DetectaOpRcl2(void);
    void DetectaOpAt(void);
    void InvierteOpRcl(void);
    void ProcesaSintaxis(void);
  public:
    bool TieneErroresLexicos(void) const;
    bool TieneErroresParentesis(void) const;
    bool TieneErroresCorchetes(void) const;
    TokenList Errores(void) const;
  };

std::ostream &operator<<(std::ostream &os,const TokenList &tl);

class TokenStack: public std::stack<Token>
  {
  public:
    Token Pop(void);
  };


#endif
