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
//Lexico.h

#ifndef LEXICO_H
#define LEXICO_H

#include "OpUnario.h"
#include "OpBinario.h"
#include "Macaulay.h"
#include "OpComparacion.h"
#include "OpBooleano.h"
#include "OpTrigonometricas.h"
#include "Literal.h"
#include <string>
#include "TablaVariables.h"
#include "TablaLiterales.h"
#include "Variable.h"
#include <iostream>


class ArbolExpr;

class Lexico
  {
    friend class ArbolExpr;
  protected:
    TablaLiterales literales;
    TablaVariables vars; //Variables globales.
  public:
    //Paréntesis
    ParentDcho parentd;
    ParentIzdo parenti;

    //Operadores binarios.
    static OpSuma suma;
    static OpResta resta;
    static OpProd prodt;
    static OpDiv divn;
    static OpDivEnt dive;
    static OpMod modulo;
    static OpPot pot;
    static OpMenor menor;
    static OpMenorIgual menor_igual;
    static OpIgual igual;
    static OpMayor mayor;
    static OpMayorIgual mayor_igual;
    static OpDistinto distinto;
    static OpAnd And;
    static OpOr Or;
    static OpNot Not;
    static OpMax max;
    static OpMin min;
    static OpMacaulay0 F0;
    static OpMacaulayN F1;
    static OpMacaulayN F2;
    static OpMacaulayN F3;
    static OpMacaulayN F4;

    //Operadores unarios.
    static OpNeg neg;
    static OpInv inv;
    static OpSign sign;
    static OpAbs abs;
    static OpSqr sqr;
    static OpSqrt raiz2;
    static OpExp expn;
    static OpLn ln;
    static OpLg lg;
    static OpPi pi;
    static OpSin seno;
    static OpCos cose;
    static OpTan tang;
    static OpAtan arctg;
    static OpSec sec;
    static OpCosec cosec;
    static OpCotg cotg;
    static OpDeg2Rad deg2rad;
    static OpRad2Deg rad2deg;
    static OpRound round;
    static OpTrunc trunc;
    static OpToNum to_num;

/*   public: */
/*     friend class OpSqr; */
/*     friend class OpNeg; */
/*     friend class OpSign; */
/*     friend class OpInv; */
/*     friend class OpAbs; */
/*     friend class OpSqrt; */
/*     friend class OpExp; */
/*     friend class OpLn; */
/*     friend class OpLg; */
/*     friend class OpSin; */
/*     friend class OpCos; */
/*     friend class OpTan; */
/*     friend class OpAtan; */

/*     friend class OpProd; */
/*     friend class OpDiv; */

    Lexico(void);
    inline TablaLiterales &getTablaLiterales(void)
      { return literales; }
    virtual Variable *CalcDirVar(const std::string &nmb);
    Segnal *CalcDirOpUnario(const std::string &nmb);
    Segnal *CalcDirOpBinario(const std::string &nmb);
    virtual Segnal *CalcDir(const std::string &nmb);
    inline Segnal *CalcularDireccion(const std::string &nmb)
      {
        if (nmb.length() <= 0)
	  std::cerr << "Se intentó el cálculo de una"
                    << " dirección con un nombre vacío" << std::endl;
        else
          return CalcDir(nmb);
        return NULL;
      }
/*     inline const Literal *NuevoLiteral(const Literal &l) */
/*       { return literales.Nuevo(l); } */
    inline const Operando *NuevoLiteral(const double &d)
      { return literales.NuevoDbl(d); }
    inline void NuevaRefLiteral(const double &d)
      { literales.NuevaRef(d); }
    inline void NuevaRefLiteral(const Segnal *s)
      { literales.NuevaRef(s); }
    inline void BorraLiteral(const double &d)
      { literales.Borra(d); }
    inline void BorraSiLiteral(const Segnal *s)
      { literales.BorraSiLiteral(s); }
    inline OpndoConNombre *NuevaVar(const Variable &v)
      { return vars.Nueva(v); }
    inline OpndoConNombre *NuevaVar(const std::string &palabra)
      { return NuevaVar(Variable(palabra)); }
    void Asigna(const std::string &palabra,const double &d)
      {
        Variable *tmp= CalcDirVar(palabra);
        if(tmp) tmp->Asigna(d);
      }
    void DesAsigna(const std::string &palabra)
      {
        Variable *tmp= CalcDirVar(palabra);
        if(tmp) tmp->DesAsigna();
      }
    void PrintPrioridades(std::ostream &os) const;
    virtual ~Lexico(void) {}
  };

#endif






