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
//InterpreteRPN.h

#ifndef INTERPRETERPN_H
#define INTERPRETERPN_H

#include "AnalisisSintactico.h"
#include "BoostAnyStack.h"
#include <vector>

namespace boost
  {
    class any;
  }

class EntProp;
class ExprAlgebra;

//! @ingroup NUCLEO
//
//! @brief Intérprete de expresiones en notación polaca inversa.
class InterpreteRPN
  {
  public:
    typedef BoostAnyStack PilaParciales;
  private:
    AnalisisSintactico AS;
    TokenList input; //!< Signos de entrada.
    static PilaParciales pila_parciales; //!< Resultados parciales.
    bool error; //!< Verdadero si se produce un error en la interpretación.

    void OperaIdent(const Token &t,const EntProp *);
    void OperaSuma(const Token &t);
    void OperaResta(const Token &t);
    void OperaMult(const Token &t);
    void OperaDiv(const Token &t);
    void OperaPow(const Token &t);
    void OperaNeg(const Token &t);
    void OperaMenor(const Token &t);
    void OperaMayor(const Token &t);
    void OperaIgual(const Token &t);
    void OperaMenorOIgual(const Token &t);
    void OperaMayorOIgual(const Token &t);
    void OperaDistinto(const Token &t);
    void OperaAnd(const Token &t);
    void OperaOr(const Token &t);
    void OperaNot(const Token &t);
    void OperaAsigna(const Token &t);
    void CreaVector(const Token &t);
    void OperaRcl(const Token &t);
    void OperaAt(const Token &t);
    void setNewInput(const std::string &in);
    friend class EntProp;
    friend class EntCmd;
    void Interpreta(const EntProp *,const int &numValEsperados= -1);
    void Interpreta(const EntProp *,const std::string &);
  public:
    InterpreteRPN(const std::string &in= "");
    static PilaParciales &Pila(void)
      { return pila_parciales; }
    static bool HayArgumentos(const size_t narg,const std::string &);
    const std::string &Input(void) const
      { return AS.Input(); }
    inline bool getError(void) const
      { return error; }
    inline bool good(void) const
      { return !error; }
  };

#endif
