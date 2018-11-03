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
//NmbVars.h

#ifndef NMBVARS_H
#define NMBVARS_H

#include "assert.h"
#include <set>
#include <string>
#include "xc_utils/src/matrices/vectorZ.h"

typedef vectorZ<char> vZ_char;
typedef vectorZ<short unsigned int> vZ_sui;

//! @brief Stores the names of the function variables.
//! Each name occupies one character.
class NmbVars : public vZ_char
  {
  protected:
    void PutStr(const std::string &str);
    void PutChar(const char c)
      { (*this)[0]= c; }
  public:
    NmbVars(const size_t &sz=1,const char &c='x') : vZ_char(sz,'x') {}
    NmbVars(const std::string &vars) : vZ_char(vars.size(),'x') 
    //Inicializa los nombres de las n primeras variables a partir de una
    //cadena de caracteres.
      { PutStr(vars); }
    NmbVars(const char c) : vZ_char(1)
    //Ojo! este es el que utiliza cuando se da un solo parámetro. 
      { PutChar(c); }
    NmbVars( const NmbVars &otro) : vZ_char(otro) {}
    NmbVars( const vZ_char &otro) : vZ_char(otro) {}
    NmbVars &operator=(const NmbVars &otro)
      {
        vZ_char::operator =(otro);
        return *this;
      }
    NmbVars &operator=(const vZ_char &otro)
      {
        vZ_char::operator =(otro);
        return *this;
      }
    NmbVars QuitaVar(short unsigned int j) const
    //Devuelve un conjunto de nombres de variables al que le falta
    //la de índice j.
      { return GetMenor(j); }    
    NmbVars Combina(const NmbVars &n2) const;
    vZ_sui Indices(const NmbVars &n) const;
    NmbVars CambioVar(short unsigned int j,const NmbVars &v) const
      {
         NmbVars c= GetMenor(j);
         c= v.Combina(c);
         return c;
      }
    friend NmbVars PutVars(const char var);
    friend NmbVars PutVars(const std::string &var);
    friend NmbVars operator +(const NmbVars &v1,const NmbVars &v2);
    friend std::ostream &operator << (std::ostream &stream, const NmbVars &n)
      { return operator << (stream, (const vZ_char &) n); }
  };



NmbVars PutVars(const char var)
//Devuelve el conjunto de variables
//correspondiente al caracter
//que se le pasa como parámetro.
  {
    NmbVars n(size_t(1));
    n.PutChar(var);
    return n;
  }

NmbVars PutVars(const std::string &vars)
//Devuelve el conjunto de variables
//correspondiente a la cadena de caracteres
//que se le pasa como parámetro.
  {
    NmbVars n(vars.size());
    n.PutStr(vars);
    return n;
  }

inline NmbVars operator +(const NmbVars &v1,const NmbVars &v2)
  { return v1.Combina(v2); }

#endif

