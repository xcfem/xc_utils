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
//prep.cc

#include "prep.h"
#include "imanip.h"

//! @brief Quita los comentarios de c++ de la entrada y los escribe en la salida.
void quita_comentarios(std::istream &in,std::ostream &out)
  {
    char c;
    int escribe= 1;
    while(!in.eof())
      {
        in.get(c);
        if((c=='/') && escribe)
          {
            c= char(in.peek());
            if(c=='/')
              escribe= 0;
            else
              in.putback('/');               
          }
        if(escribe) out.put(c);
        if((c=='\n') && !escribe)
          escribe= 1;
      }
  }

//! @brief Escribe en os lo mismo que haya en is HASTA a_sust luego escribe en os sust.
int busca_y_sust1(std::istream &is,const std::string &a_sust,std::ostream &os,const std::string &sust)
  {
    char c;
    const std::streampos start= is.tellg(); //Punto de comienzo de la busqueda.
    int encontrada= busca_inicio(is,a_sust);
    std::streampos ini= is.tellg(); 
    is.seekg(start);
    if(encontrada)
      {
        encontrada= 1;
        while(is.tellg()<=ini) //El uno es para que no se coma los blancos.
          {
            c= is.get();
            if(is)
              os << c;
            else
              break;
          }
        os << sust;
        is.ignore(a_sust.length());
      }
    else
      vuelca_stream(is,os);
    return encontrada;
  }

//! @brief Escribe en os lo mismo que haya en is sustituyendo a_sust por sust.
int busca_y_sust(std::istream &is,const std::string &a_sust,std::ostream &os,const std::string &sust)
  {
    int encontrada= 0;
    while(is)
      encontrada= busca_y_sust1(is,a_sust,os,sust);
    vuelca_stream(is,os);
    return encontrada;
  }

//! @brief Devuelve una cadena de caracteres comprendida entre dos caracteres '"'
std::string get_bloque_comillas(std::istream &is, bool &error)
  {
    std::string retval;
    bool backslash= false;
    while(is)
      {
        char c= is.get();
        if(!(is)) break;
        if(c == '\n')
          {
	    std::cerr << "get_bloque_comillas; ERROR, no se cerraron comillas en: '"
                      << retval << "'\n";
            error= true;
            break;
          }
        retval+=c;
        if(c == '"' && !backslash)
          break;
        if(c == '\\')
          backslash= !backslash;
        else
          backslash= false;
      }
    retval= '"' + retval;
    return retval;
  }

//! @brief Devuelve una cadena de caracteres comprendida entre paréntesis '"'
//!
//! Se diferencia de get_bloque_llaves en que carga todo
//! hasta que terminan los parentesis.
std::string get_bloque_parentesis(std::istream &is,bool &error)
  {
    std::string retval;
    size_t cuenta_parentesis(1);  //Ya se leyó el primer paréntesis (
    while(cuenta_parentesis && (is))
      {
        const char c= is.get();
        if(!(is)) break;
        if(c == '"')
          {retval+= get_bloque_comillas(is,error);}
        else
          {
            if(c == '(')
              cuenta_parentesis++;
            else if(c == ')')
              cuenta_parentesis--;
            if(cuenta_parentesis) //El último paréntesis se ignora.
              retval+= c;
          }
      }
    retval= '(' + retval +')';
    if(error)
      std::cerr << "get_bloque_parentesis; ERROR, al interpretar la expresión: '"
                << retval << "'\n";
    return retval;
  }

//! @brief Devuelve un bloque del archivo de entrada.
//!
//! El bloque comienza con '{' y termina con '}'
//!
//! @param ignora_esp: Si es verdadero se ignoran los espacios (tabuladores,...) dentro del bloque.
std::string get_bloque_llaves(std::istream &is,bool &error,const bool &ignora_esp)
  {
    std::string retval;
    size_t cuenta_llaves(1); //Ya se leyó la primera llave {
    while(cuenta_llaves && (is))
      {
        const char c= is.get();
        if(!(is)) break;
        if(c == '{') cuenta_llaves++;
        if(c == '}') cuenta_llaves--;
        if(cuenta_llaves) //La última llave se ignora.
          {
            if(isspace(c) && ignora_esp)
              continue;  //Ignora espacios.
            else
              {
                if(c == '"')
                  { retval+= get_bloque_comillas(is,error); }
                else if(c=='(')
                  {retval+= get_bloque_parentesis(is,error); } 
                else                                  
                  retval+=c;
              }
          }
      }
    if(error)
      std::cerr << "get_bloque_llaves; ERROR, al interpretar la expresión: '"
                << retval << "'\n";
    return retval;
  }
