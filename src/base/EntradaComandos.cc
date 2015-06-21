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
//EntradaComandos.cxx

#include "EntradaComandos.h"
#include <boost/algorithm/string/trim.hpp>
#include "boost/algorithm/string_regex.hpp"
#include "xc_basic/src/streams/prep.h"
#include <fstream>
#include <sstream>
#include "boost/lexical_cast.hpp"
#include "../nucleo/EntProp.h"

//Variables estáticas de EntradaComandos
//EntradaComandos::pila_streams_entrada EntradaComandos::streams_entrada;
//EntradaComandos::pila_archivos_entrada EntradaComandos::archivos_entrada;


//! @brief Constructor por defecto.
EntradaComandos::EntradaComandos(std::istream *input,const std::string &str)
  : input_file(input)
  { SetArchivoEntradaActual(str); }

//! @brief Destructor.
EntradaComandos::~EntradaComandos(void)
  {
    const size_t sz= streams_entrada.size();
    if(sz>0)
      {
	std::cerr << "Quedaron " << sz
                  << " streams sin usar." << std::endl;
        while(!streams_entrada.empty())
          {
            CierraArchivoEntrada();
            if((input_file==&std::cin))
              continue;
          }
      }
  }

bool EntradaComandos::Ok(void) const
  {
    bool retval= false;
    if(input_file)
      {
        retval= input_file->good();
      }
    else
      std::cerr << "No hay archivo de entrada." << std::endl;
    return retval;
  }

//! @brief Lee un nuevo comando del archivo actual.
//Sólo debe llamarla el metodo nuevo_comando de CmdStatus.
std::string EntradaComandos::get_comando(void)
  {
    std::string retval;
    getline(*input_file,retval,'{');
    boost::algorithm::trim(retval);//Quitamos todos los whitespace delante y detrás del comando.
    if(input_file->eof())
      {
        std::cerr << "EntradaComandos::get_comando; no se encontró la definición"
                  << " de los argumentos del comando: '" << retval 
                  << "' se ignora dicho comando." << getPosicionLecturaActual()
                  << std::endl;
        retval.clear();
      }
    if(EntProp::GetNivelVerborrea()>8)
      std::clog << "EntradaComandos::get_comando cmd= '" << retval << "'" << std::endl;
    return retval;
  }

//! @brief Lee un nuevo comando del archivo actual.
std::string EntradaComandos::get_linea(void)  //Sólo debe llamarla el metodo LeeCmd de EntCmd.
  {
    std::string retval;
    getline(*input_file,retval,'\n');
    return retval;
  }

void EntradaComandos::NuevoArchivoEntrada(const std::string &archivo)
  {
    streams_entrada.push(input_file);
    input_file= new std::ifstream(archivo.c_str());
    SetArchivoEntradaActual(archivo);
  }
void EntradaComandos::CierraArchivoEntrada(void)
  {
    delete input_file;
    input_file= streams_entrada.top();
    streams_entrada.pop();
    PopArchivoEntradaActual();
  }
void EntradaComandos::NuevoStringEntrada(const std::string &input,const std::string &nmb)
  {
    streams_entrada.push(input_file);
    input_file= new std::istringstream(input.c_str());
    SetArchivoEntradaActual(nmb);
  }
void EntradaComandos::CierraStringEntrada(void)
  { CierraArchivoEntrada(); }


//! @brief Cuenta el número de líneas hasta la posición
//! actual del stream que se pasa como parámetro.
size_t EntradaComandos::cuenta_lineas(void) const
  {
    size_t cont= 0;
    std::streampos pos_actual= input_file->tellg();
    if(!input_file->eof())
      {
        input_file->seekg(0);
        while(input_file->tellg()<pos_actual)
          if(input_file->get()=='\n') cont++;
        input_file->seekg(pos_actual);
        cont++;
      }
    return cont; //La primera línea debe ser la 1 no la 0.
  }

//! @brief Devuelve el archivo y número de línea que se ha leído.
std::string EntradaComandos::getPosicionLecturaActual(void) const
  {
    std::string retval;
    retval= "(archivo: " + GetArchivoEntradaActual() + ", línea: " +
      boost::lexical_cast<std::string>(cuenta_lineas()) + ")";
    return retval;
  }

std::string EntradaComandos::get_argumento(void) const
  {
    std::string arg;
    getline(*input_file,arg,'}');
    boost::algorithm::trim(arg);//Quitamos todos los whitespace delante y detrás del comando.
    return arg;
  }

//! @brief Devuelve una cadena de caracteres comprendida entre dos caracteres '"'
//!
//! Se diferencia de get_bloque_llaves en que carga todo
//! hasta que terminan las comillas.
std::string EntradaComandos::get_bloque_comillas(bool &error) const
  { return ::get_bloque_comillas(*input_file,error); }

//! @brief Devuelve una cadena de caracteres comprendida entre paréntesis '"'
//!
//! Se diferencia de get_bloque_llaves en que carga todo
//! hasta que terminan los parentesis.
std::string EntradaComandos::get_bloque_parentesis(bool &error) const
  { return ::get_bloque_parentesis(*input_file,error); }

//! @brief Devuelve un bloque de instrucciones en el archivo de entrada.
//!
//! Se diferencia de get_argumento en que ignora datos y comandos
//! contenidos en el bloque, devolviendo la cadena de caracteres
//! para una ejecución posterior.
//! El bloque comienza con '{' y termina con '}'
//!
//! @param ignora_esp: Si es verdadero se ignoran los espacios (tabuladores,...) dentro del bloque.
std::string EntradaComandos::get_bloque_llaves(bool &error,const bool &ignora_esp) const
  { return ::get_bloque_llaves(*input_file,error,ignora_esp); }

//! @brief Procesa un comentario en el archivo de entrada.
void EntradaComandos::procesa_comentario(bool &error)
  { get_bloque_llaves(error); }

