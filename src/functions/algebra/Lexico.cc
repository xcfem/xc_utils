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
//Lexico.cc

#include "Lexico.h"

//Operadores binarios.
OpSuma Lexico::suma;
OpResta Lexico::resta;
OpProd Lexico::prodt;
OpDiv Lexico::divn;
OpDivEnt Lexico::dive;
OpMod Lexico::modulo;
OpPot Lexico::pot;
OpMenor Lexico::menor;
OpMenorIgual Lexico::menor_igual;
OpIgual Lexico::igual;
OpMayor Lexico::mayor;
OpMayorIgual Lexico::mayor_igual;
OpDistinto Lexico::distinto;
OpAnd Lexico::And;
OpOr Lexico::Or;
OpNot Lexico::Not;
OpMax Lexico::max;
OpMin Lexico::min;
OpMacaulay0 Lexico::F0;
OpMacaulayN Lexico::F1= OpMacaulayN(1);
OpMacaulayN Lexico::F2= OpMacaulayN(2);
OpMacaulayN Lexico::F3= OpMacaulayN(3);
OpMacaulayN Lexico::F4= OpMacaulayN(4);

//Operadores unarios.
OpNeg Lexico::neg;
OpInv Lexico::inv;
OpSign Lexico::sign;
OpAbs Lexico::abs;
OpSqr Lexico::sqr;
OpSqrt Lexico::raiz2;
OpExp Lexico::expn;
OpLn Lexico::ln;
OpLg Lexico::lg;
OpPi Lexico::pi;
OpSin Lexico::seno;
OpCos Lexico::cose;
OpTan Lexico::tang;
OpAtan Lexico::arctg;
OpSec Lexico::sec;
OpCosec Lexico::cosec;
OpCotg Lexico::cotg;
OpDeg2Rad Lexico::deg2rad;
OpRad2Deg Lexico::rad2deg;
OpRound Lexico::round;
OpTrunc Lexico::trunc;
OpToNum Lexico::to_num;

Lexico::Lexico(void)
  {}

//! @brief Devuelve un puntero al operador unario cuyo símbolo se pasa
//! como parámetro.
Segnal *Lexico::CalcDirOpUnario(const std::string &nmb)
  {
    if(nmb == neg.getName()) return &neg;
    if(nmb == inv.getName()) return &inv;
    if(nmb == abs.getName()) return &abs;
    if(nmb == sqr.getName()) return &sqr;
    if(nmb == raiz2.getName()) return &raiz2;
    if(nmb == expn.getName()) return &expn;
    if(nmb == ln.getName()) return &ln;
    if(nmb == lg.getName()) return &lg;
    if(nmb == pi.getName()) return &pi;
    if(nmb == seno.getName()) return &seno;
    if(nmb == cose.getName()) return &cose;
    if(nmb == tang.getName()) return &tang;
    if(nmb == sec.getName()) return &sec;
    if(nmb == cosec.getName()) return &cosec;
    if(nmb == cotg.getName()) return &cotg;
    if(nmb == deg2rad.getName()) return &deg2rad;
    if(nmb == rad2deg.getName()) return &rad2deg;
    if(nmb == arctg.getName()) return &arctg;
    if(nmb == round.getName()) return &round;
    if(nmb == trunc.getName()) return &trunc;
    if(nmb == to_num.getName()) return &to_num;
    return NULL;
  }

//! @brief Devuelve un puntero al operador binario cuyo símbolo se pasa
//! como parámetro.
Segnal *Lexico::CalcDirOpBinario(const std::string &nmb)
  {
    if(nmb == suma.getName()) return &suma;
    if(nmb == resta.getName()) return &resta;
    if(nmb == prodt.getName()) return &prodt;
    if(nmb == divn.getName()) return &divn;
    if(nmb == dive.getName()) return &dive;
    if(nmb == modulo.getName()) return &modulo;
    if(nmb == pot.getName()) return &pot;
    if(nmb == menor.getName()) return &menor;
    if(nmb == menor_igual.getName()) return &menor_igual;
    if(nmb == igual.getName()) return &igual;
    if(nmb == mayor.getName()) return &mayor;
    if(nmb == mayor_igual.getName()) return &mayor_igual;
    if(nmb == distinto.getName()) return &distinto;
    if(nmb == And.getName()) return &And;
    if(nmb == Or.getName()) return &Or;
    if(nmb == Not.getName()) return &Not;
    if(nmb == max.getName()) return &max;
    if(nmb == min.getName()) return &min;
    if(nmb == F0.getName()) return &F0;
    if(nmb == F1.getName()) return &F1;
    if(nmb == F2.getName()) return &F2;
    if(nmb == F3.getName()) return &F3;
    if(nmb == F4.getName()) return &F4;
    return NULL;
  }

//! @brief Devuelve un puntero a la variable cuyo nombre se pasa
//! como parámetro.
Variable *Lexico::CalcDirVar(const std::string &nmb)
  { return vars.CalcDir(nmb); }


//! @brief Devuelve un puntero al operador cuyo símbolo se pasa
//! como parámetro.
Segnal *Lexico::CalcDir(const std::string &nmb)
  {
    //Parentesis
    if(nmb == parenti.getName()) return &parenti;
    if(nmb == parentd.getName()) return &parentd;

    //Operadores binarios.
    Segnal *retval= CalcDirOpBinario(nmb);
    if(!retval) retval= CalcDirOpUnario(nmb);
    if(!retval) retval= CalcDirVar(nmb);
    return retval;
  }

void Lexico::PrintPrioridades(std::ostream &os) const
  {
    os << "Prioridad de los paréntesis:" << std::endl;
    os << parentd.getName() << ": " << parentd.GetPrioridad() << std::endl;
    os << parenti.getName() << ": " << parenti.GetPrioridad() << std::endl;

    os << "Prioridad de operadores binarios." << std::endl;
    os << suma.getName() << ": " << suma.GetPrioridad() << std::endl;
    os << resta.getName() << ": " << resta.GetPrioridad() << std::endl;
    os << prodt.getName() << ": " << prodt.GetPrioridad() << std::endl;
    os << divn.getName() << ": " << divn.GetPrioridad() << std::endl;
    os << dive.getName() << ": " << dive.GetPrioridad() << std::endl;
    os << modulo.getName() << ": " << modulo.GetPrioridad() << std::endl;
    os << pot.getName() << ": " << pot.GetPrioridad() << std::endl;
    os << menor.getName() << ": " << menor.GetPrioridad() << std::endl;
    os << menor_igual.getName() << ": " << menor_igual.GetPrioridad() << std::endl;
    os << igual.getName() << ": " << igual.GetPrioridad() << std::endl;
    os << mayor.getName() << ": " << mayor.GetPrioridad() << std::endl;
    os << mayor_igual.getName() << ": " << mayor_igual.GetPrioridad() << std::endl;
    os << distinto.getName() << ": " << distinto.GetPrioridad() << std::endl;
    os << And.getName() << ": " << And.GetPrioridad() << std::endl;
    os << Or.getName() << ": " << Or.GetPrioridad() << std::endl;
    os << Not.getName() << ": " << Not.GetPrioridad() << std::endl;
    os << max.getName() << ": " << max.GetPrioridad() << std::endl;
    os << min.getName() << ": " << min.GetPrioridad() << std::endl;
    os << F0.getName() << ": " << F0.GetPrioridad() << std::endl;
    os << F1.getName() << ": " << F1.GetPrioridad() << std::endl;
    os << F2.getName() << ": " << F2.GetPrioridad() << std::endl;
    os << F3.getName() << ": " << F3.GetPrioridad() << std::endl;
    os << F4.getName() << ": " << F4.GetPrioridad() << std::endl;

    os << "Prioridad de operadores unarios." << std::endl;
    os << neg.getName() << ": " << neg.GetPrioridad() << std::endl;
    os << inv.getName() << ": " << inv.GetPrioridad() << std::endl;
    os << sign.getName() << ": " << sign.GetPrioridad() << std::endl;
    os << abs.getName() << ": " << abs.GetPrioridad() << std::endl;
    os << sqr.getName() << ": " << sqr.GetPrioridad() << std::endl;
    os << raiz2.getName() << ": " << raiz2.GetPrioridad() << std::endl;
    os << expn.getName() << ": " << expn.GetPrioridad() << std::endl;
    os << ln.getName() << ": " << ln.GetPrioridad() << std::endl;
    os << lg.getName() << ": " << lg.GetPrioridad() << std::endl;
    os << pi.getName() << ": " << pi.GetPrioridad() << std::endl;
    os << seno.getName() << ": " << seno.GetPrioridad() << std::endl;
    os << cose.getName() << ": " << cose.GetPrioridad() << std::endl;
    os << tang.getName() << ": " << tang.GetPrioridad() << std::endl;
    os << arctg.getName() << ": " << arctg.GetPrioridad() << std::endl;
    os << sec.getName() << ": " << sec.GetPrioridad() << std::endl;
    os << cosec.getName() << ": " << cosec.GetPrioridad() << std::endl;
    os << cotg.getName() << ": " << cotg.GetPrioridad() << std::endl;
    os << deg2rad.getName() << ": " << deg2rad.GetPrioridad() << std::endl;
    os << rad2deg.getName() << ": " << rad2deg.GetPrioridad() << std::endl;
    os << round.getName() << ": " << round.GetPrioridad() << std::endl;
    os << trunc.getName() << ": " << trunc.GetPrioridad() << std::endl;
    os << to_num.getName() << ": " << to_num.GetPrioridad() << std::endl;

  }
