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
//CmdStatus.cxx

#include "CmdStatus.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"
#include "xc_basic/src/util/cmd_args.h"
#include "PilaLlamadas.h"
#include "Buscadores.hxx"
#include "../nucleo/EntProp.h"
#include <cmath>

//Variables estáticas de CmdStatus
Buscadores CmdStatus::b;
PilaLlamadas CmdStatus::pila_llamadas;

//! @brief Constructor por defecto.
CmdStatus::CmdStatus(int argc, char* argv[])
  {
    if(argc>0 && argv)
      cmd_args= get_cmd_args(argc,argv);
  }

//! @brief Constructor.
CmdStatus::CmdStatus(std::istream *input,const std::string &str, std::ostream *output,int argc, char* argv[])
  :entrada_comandos(input,str)
  {
    if(argc>0 && argv)
      cmd_args= get_cmd_args(argc,argv);
  }

//! @brief Destructor.
CmdStatus::~CmdStatus(void)
  {
    //Libera buscadores
    Buscadores::iterator i= b.begin();
    for(;i!=b.end();i++)
      {
        delete (*i).second;
        b.erase(i);
      }
  }


//! @brief Devuelve el número de argumentos de la línea de comando.
size_t CmdStatus::getNumCmdArgs(void) const
  { return cmd_args.size(); }

//! @brief Devuelve una referencia a la cola de argumentos de la línea de comando.
const std::deque<std::string> &CmdStatus::getCmdArgs(void) const
  { return cmd_args; }

//! @brief Devuelve un elemento de la cola de argumentos de la línea de comando.
const std::string &CmdStatus::getCmdArg(const size_t &i) const
  {
    assert(i<cmd_args.size());
    return cmd_args[i];
  }


//! @brief Actualiza los valores del comando y de los índices.
void CmdStatus::nuevo_comando(void)
  { parser= CmdParser(entrada_comandos.get_comando()); }

//! @brief A ejecutar una vez completada la lectura del comando.
void CmdStatus::cmd_completado(void)
  {
    parser.ClearCmd();
  }


//! @brief Devuelve (si le es posible) un argumento en forma de número en coma flotante.
double CmdStatus::GetFloat(void) const
  { 
    ExprAlgebra a= GetExpr();
    return a.ToNum();
  }

//! @brief Devuelve (si le es posible) un argumento en forma de entero largo.
long int CmdStatus::GetInt(void) const
  { return lrint(GetFloat()); }


//! @brief Devuelve (si le es posible) un argumento en forma de expresión.
ExprAlgebra CmdStatus::GetExpr(void) const
  {
    const std::string arg= entrada_comandos.get_argumento();
    ExprAlgebra retval;
    if(arg.size())
      retval= ExprAlgebra(arg.c_str());
    else
      retval= ExprAlgebra("0.0");
    return retval;
  }

//! @brief Devuelve el bloque de instrucciones que corresponde al comando.
std::string CmdStatus::GetBloque(const bool &ignora_esp) const
  {
    bool error= false;
    const std::string retval= entrada_comandos.get_bloque_llaves(error,ignora_esp);
    if(error)
      {
        const std::string posLectura= getPosicionLecturaActual();
        std::cerr << "CmdStatus::GetBloque; error al interpretar la expresión: '"
                  << retval << "'. " << posLectura << std::endl;
      }
    return retval;
  }

//! @brief Muestra un mensaje de error indicando el comando que no ha podido procesarse.
void CmdStatus::cmd_desconocido(const std::string &nmb_clase,const std::string &deref_cmd,const int &nverb) const
  {
    const size_t nl= entrada_comandos.cuenta_lineas();
    std::cerr << nmb_clase 
	      << ": el comando: '" << deref_cmd << "' (obtenido de '" << parser.GetNmbCmd()
         << "') en la línea " << nl
         << " del archivo: '" << entrada_comandos.GetArchivoEntradaActual()
         << "' es desconocido." << std::endl;
    if(nverb>4)
      {
        std::cerr << "Codigos ascii: " << '"';
        deletrea_ascii(deref_cmd,std::cerr);
        std::cerr << '"' << std::endl;
      }
    if(nverb>2)
      {
        pila_llamadas.imprime_ruta(std::cerr);
        std::cerr << std::endl;
      }
  }

void CmdStatus::InsertaBuscador(const std::string &clave,BuscadorPtros *bsc)
  { 
    Buscadores::iterator i= b.find(clave);        
    if(i!=b.end()) delete (*i).second;
    b[clave]= bsc;
  }

Buscadores &CmdStatus::GetBuscadores(void)
  { return b; }

