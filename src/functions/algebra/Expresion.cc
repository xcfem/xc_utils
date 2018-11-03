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
//Expresion.cc

#include "Expresion.h"
#include "Lexico.h"
#include <sstream>

void Expresion::borra_lista(void)
  {
    l_Expr::const_iterator i;
    for(i= lista.begin();i!= lista.end();i++)
      Lex().BorraSiLiteral(*i);
    lista.erase(lista.begin(),lista.end());
  }

void Expresion::update_nueva_lista(void)
  {
    l_Expr::const_iterator i;
    for(i= lista.begin();i!= lista.end();i++)
      Lex().NuevaRefLiteral(*i);
  }

//! @brief Inserta un literal en la lista, esta función existe para evitar pasar por PonerSegnal
//! y que aumente erróneamente el contador de referencias a literales.
void Expresion::PonerDouble(const double &d)
  { lista.push_back(const_cast<Operando *>(Lex().NuevoLiteral(d))); }

//! @brief Inserta una señal en la lista.
void Expresion::PonerSegnal(const Segnal *s)
  {
    if(s)
      {
        lista.push_back(const_cast<Segnal *>(s)); //Chapucilla.
        Lex().NuevaRefLiteral(s);
      }
    else
      std::cerr << "Se intento insertar señal nula." << std::endl;
  }

//! Devuelve verdadero si
//! -La expresión está vacía.
//! -El último valor es una de estas dos cosas
//!       - un paréntesis izquierdo.
//!       - un operador.
bool Expresion::Inicial(void)
 {
   if(lista.empty())
     return true;
   else
     {
       Clase k= lista.back()->GetClase();
       return ( (k == parent_izdo) || (k == op_unitario) || (k == op_binario) );
     }
 }


Expresion::~Expresion(void)
  {  borra_lista(); }

//! @brief Crea la expresión a partir de la cadena de caracteres que se pasa como parámetro.
void Expresion::Traduce(const std::string &str)
  {
    if(!str.empty())
      {
        std::istringstream iss_traduce(str);
        Traduce(iss_traduce);
        if(ErrorTraduccion())
          std::cerr << "Expresion::Traduce; se produjo un error al interpretar la expresión: '"
                    << str << "'\n";
      }
  }

//! @brief Operador salida.
std::ostream &operator <<(std::ostream &stream,const Expresion &expr)
  {
    Expresion::l_Expr::const_iterator i;
    for(i= expr.lista.begin();i!= expr.lista.end();i++)
      stream << **i << ' ';
    return stream;
  }
