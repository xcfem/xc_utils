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
//CmdParser.h

#ifndef CMDPARSER_H
#define CMDPARSER_H

#include <string>
#include <deque>
#include <vector>

class EntProp;
namespace boost
  {
    class any;
  }

//! @ingroup NUCLEO
//
//! @brief Parser para lectura de comandos.
class CmdParser
  {
    std::string nmb_cmd;//!< Nombre del comando.
    std::string args; //!< Argumentos del comando.
    std::string indices; //!< Índices del comando.
    std::string nmb_miembro; //!< Nombre del miembro.
    std::string cmd; //!< Comando completo= nmb_cmd+"."+nmb_miembro;

    static std::string quita_parentesis(const std::string &,const char &,const char &);
    static std::string get_substr(const std::string &,const char &,const char &);
  protected:
    bool check_cmd_str(const std::string &) const;
    void parse(const std::string &);
  public:
    CmdParser(const std::string &str="");

    void ClearCmd(void);
    void Clear(void);

    const std::string &GetCmd(void) const;
    const std::string &GetNmbCmd(void) const;
    const std::string &GetArgs(void) const;
    const std::string &GetIndices(void) const;
    const std::string &GetMiembro(void) const;
    bool TieneIndices(void) const;
    bool TieneArgs(void) const;
    bool TieneMiembro(void) const;
    bool Simple(void) const;
    std::deque<boost::any> SeparaArgs(const EntProp *) const;
    std::deque<boost::any> SeparaIndices(const EntProp *) const;
    std::vector<std::string> getIndicesAsStrings(const EntProp *) const;
    std::vector<int> getIndicesAsInts(const EntProp *) const;
    std::vector<double> getIndicesAsDoubles(const EntProp *) const;
    std::vector<size_t> getIndicesAsSzts(const EntProp *) const;
    void Print(std::ostream &os) const;
  };

#endif
