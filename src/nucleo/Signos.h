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
//Signos.h

#ifndef SIGNOS_H
#define SIGNOS_H

#include <string>
#include <iostream>

//Clases de signos.

//! @ingroup NUCLEO
//
//! @brief Señal.
class Token
  {
  public:
    enum TipoToken {DIGIT, LETRA, IDENT, IDENT_WITH_MEMBER, INT_LIT, DBL_LIT, EXPR_LIT, STR_LIT, ERROR, POINT, COMA, SPACE, COMILLA, COMILLAS, FIN, PARENT_DCHO, PARENT_IZDO,CORCHETE_DCHO, CORCHETE_IZDO, VECTOR, OP_PREFIX, OP_NEG, OP_SUMA, OP_RESTA, OP_MULT, OP_DIV, OP_POW, OP_MENOR, OP_MAYOR, OP_IGUAL, OP_MENORIGUAL, OP_MAYORIGUAL, OP_DISTINTO, OP_STO, OP_AND, OP_OR, OP_NOT, BASERCL, OP_RCL, OP_AT};
    enum ClaseToken {CL_OPERANDO, CL_PARENT_IZDO, CL_PARENT_DCHO, CL_CORCHETE_IZDO, CL_CORCHETE_DCHO, CL_OPERADOR, CL_ERROR, CL_COMA, CL_FIN};
  private:
    std::string lexema;
    int tipo;
  public:
    Token(const std::string &l= "",const int &tipo= ERROR);
    static int tipoChar(const char &c);
    static const std::string &convertToken(int t);
    std::string &Lexema(void)
      { return lexema; }
    const std::string &Lexema(void) const
      { return lexema; }
    const int &Tipo(void) const
      { return tipo; }
    int &Tipo(void)
      { return tipo; }
    int Prioridad(void) const;
    int Clase(void) const;
    bool EsMiembro(void) const;
    const std::string &strTipo(void) const
      { return convertToken(tipo); }
  };

std::ostream &operator<<(std::ostream &os,const Token &t);


#endif
