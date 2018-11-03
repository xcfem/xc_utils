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
//ExprInfija.h

#ifndef EXPR_INFIJA_H
#define EXPR_INFIJA_H

//#include <iostream>
#include "Expresion.h"
#include <stack>
#include <string>

class OpBinario;

class ExprInfija: public Expresion
  {
  private:
    std::stack<std::string> op_bin_en_espera; //!< Operadores binarios prefijos en espera de encontrar la coma.
    
    void InsertaPalabra(const std::streampos &pos,Segnal *t);
    std::streampos EncontrarPalabra(const std::streampos &pos,std::istream &is);
    std::streampos EncontrarNumero(const std::streampos &pos,std::istream &is);
    std::streampos EncontrarSimbolo(const std::streampos &pos,std::istream &is,int &cta_parent);
    bool InsertaOpUnario(const std::streampos &pos,Segnal *t);
    void InsertaOpBinario(const std::streampos &pos,Segnal *t);
  protected:
    Segnal *InsertaNuevaPalabra(const std::streampos &pos,const std::string &palabra);
    Segnal *InsertaNeg(const std::streampos &pos,char op);
    void CompruebaParentesis( const std::streampos &pos, int &cta, const Segnal *t);
    virtual void Traduce(std::istream &is);
  public:
    //! @brief Constructor por defecto.
    ExprInfija(void)
      : Expresion(), op_bin_en_espera()
      {}
    //! @brief Constructor por defecto.
    ExprInfija(const std::string &str)
      : Expresion(), op_bin_en_espera()
      { Expresion::operator =(str); }
    //! @brief Constructor.
    ExprInfija(std::istream &is)
      : Expresion(), op_bin_en_espera()
      { Traduce(is); }
    //! @brief Constructor de copia.
    ExprInfija(const ExprInfija &otra)
      : Expresion(otra), op_bin_en_espera(otra.op_bin_en_espera) {}
    ExprInfija &operator=(const ExprInfija &otra);
    ExprInfija &operator=(const std::string &str);
  };

#endif
