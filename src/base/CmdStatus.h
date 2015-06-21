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
//CmdStatus.h

#ifndef CMDSTATUS_HXX
#define CMDSTATUS_HXX

#include <string>
#include <map>
#include <deque>
#include <iostream>
#include <sstream>
#include "EntradaComandos.h"
#include "ArchivosSalida.h"
#include "ArchivosEntrada.h"
#include "MapAuxData.h"
#include "xc_utils/src/nucleo/CmdParser.h"

class ExprAlgebra;
class PilaLlamadas;
class Buscadores;
class BuscadorPtros;

//! @ingroup BASE
//
//! @brief Estado para procesa comando
class CmdStatus
  {
    friend class EntCmd;
  public:
    typedef std::deque<std::string> dq_indices; //!< Pila de cadenas de caracteres.
  private:
    static Buscadores b;
    MapAuxData auxData; //!< Tabla de punteros a datos auxiliares.
   
    EntradaComandos entrada_comandos; //Entrada de comandos.
    static PilaLlamadas pila_llamadas; //!< Pila de llamadas.
    ArchivosSalida archivos_salida; //Salida.
    ArchivosEntrada archivos_entrada; //Entrada datos.
    std::deque<std::string> cmd_args; //!< Argumentos de línea de comandos.

    CmdParser parser; //!< Comando, argumentos e índices leídos tras la ejecución de get_comando.

    void nuevo_comando(void);
  public:
    //! @brief Constructor por defecto.
    CmdStatus(int argc= 0, char* argv[]= NULL);
    CmdStatus(std::istream *input,const std::string &str="", std::ostream *output=NULL,int argc= 0, char* argv[]= NULL);
    virtual ~CmdStatus(void);

    inline const CmdParser &Parser(void) const
      { return parser; }
    inline const std::string &Cmd(void) const
      { return parser.GetCmd(); }
    inline const EntradaComandos &GetEntradaComandos(void) const
     { return entrada_comandos; }
    inline EntradaComandos &GetEntradaComandos(void)
     { return entrada_comandos; }
    inline std::string getPosicionLecturaActual(void) const
      { return entrada_comandos.getPosicionLecturaActual(); }

    inline const ArchivosSalida &GetArchivosSalida(void) const
      { return archivos_salida; }
    inline ArchivosSalida &GetArchivosSalida(void)
      { return archivos_salida; }
    inline const ArchivosEntrada &GetArchivosEntrada(void) const
      { return archivos_entrada; }
    inline ArchivosEntrada &GetArchivosEntrada(void)
      { return archivos_entrada; }

    inline const MapAuxData &AuxData(void) const
      { return auxData; }
    inline MapAuxData &AuxData(void)
      { return auxData; }

    inline const PilaLlamadas &GetPilaLlamadas(void) const
      { return pila_llamadas; }
    inline PilaLlamadas &GetPilaLlamadas(void)
      { return pila_llamadas; }

    static void InsertaBuscador(const std::string &clave,BuscadorPtros *bsc);
    static Buscadores &GetBuscadores(void);

    size_t getNumCmdArgs(void) const;
    const std::deque<std::string> &getCmdArgs(void) const;
    const std::string &getCmdArg(const size_t &i) const;

    inline std::string GetString(void) const
      { return entrada_comandos.get_argumento(); }
    std::string GetBloque(const bool &ignora_esp= true) const;

    long int GetInt(void) const;
    double GetFloat(void) const;
    ExprAlgebra GetExpr(void) const;
    void cmd_completado(void);
    virtual void cmd_desconocido(const std::string &,const std::string &,const int &nverb= 0) const;
  };

#endif
