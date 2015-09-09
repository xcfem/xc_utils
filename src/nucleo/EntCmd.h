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
//EntCmd.h

#ifndef ENTCMD_H
#define ENTCMD_H

#include "EntProp.h"
#include <set>
#include <deque>
#include <stack>
#include "boost/tuple/tuple.hpp"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_basic/src/funciones/algebra/ExprAlgebra.h"
#include "xc_utils/src/base/ErrLogFiles.h"
#include <boost/python.hpp>

class CmdStatus;
class Lista;
class any_const_ptr;
class SqLiteObject;
class CmdPlotter;
class CmdFixedWidthReader;
class MEDObject;
class Locale;

namespace boost
  {
    class any;
  }

typedef enum{FALLO,CONTINUA,COMPLETADO} resul_lectura;

//! @ingroup NUCLEO
//
//! @brief Objeto capaz de procesar comandos.
class EntCmd: public EntProp
  {
  private:
    static CmdStatus *ptr_status; //!< Puntero a la entrada de comandos.
    static ErrLogFiles err_log_files; //!< Streams para errores y avisos.
    static SqLiteObject sqlite_interpreter; //<! Intérprete sqlite.
    static CmdPlotter psplot; //<! Gráficos postscript.
    static CmdFixedWidthReader fw_reader; //! Para leer líneas de campos de ancho fijo.
    static MEDObject med; //<! Archivos MED de intercambio de datos.
    static Locale locale;
    friend class BloqueSub;
    friend class BloqueFunc;
    bool ejecuta_comando_user_param(const std::string &cmd,boost::any &data,CmdStatus &status);
    bool procesa_comando_user_param(const std::string &,CmdStatus &);
    bool procesa_comando_control(const std::string &,CmdStatus &);
    void nuevo_archivo(bool ,CmdStatus &);
    bool procesa_comando_archivos(const std::string &,CmdStatus &);
    void procesa_bloque(CmdStatus &status);

    static std::deque<std::string> path; //!< Caminos de acceso a archivos.

    void incluye_archivo(CmdStatus &status,const std::string &);

    std::map<std::string, boost::python::object> python_dict; //!< Variables de Python.
  protected:
    static std::stack<std::string> pila_nombres_cmd_usuario; //! Contiene los nombres de los comandos de usuario en ejecución.
    friend class InterpreteRPN;
    //! @brief Devuelve un puntero al objeto CmdStatus.
    inline static CmdStatus *get_ptr_status(void)
      { return ptr_status; }

    //Parámetros.
    bool existe_user_param(const std::string &) const;
    bool existe_arg(const std::string &) const;
    MapParam::param_iterator get_user_param_iterator(const std::string &);
    MapParam::param_iterator asigna_param(const std::string &,const std::string &);
    void asigna_elem_param(const std::string &,const std::string &,const std::string &);    
    static EntCmd *entcmd_cast(boost::any &data);

    virtual void inserta_buscadores(CmdStatus &status) {}
    resul_lectura procesa_caracter(CmdStatus &status);
    void ejecuta_bloque(CmdStatus &status,const std::string &,const std::string &);
    friend class PilaLlamadas;
    virtual bool procesa_comando(CmdStatus &status);
    virtual void procesa_metodo(CmdStatus &status);

    boost::any string_to_boost_any(const std::string &tipo,const std::string &valor,const std::string &def_args,const std::string &nombre= "");


    template <class T>
    void string_to(T &,const std::string &) const;
    template <class TUPLA>
    TUPLA string_to_tuple1(const TUPLA &,const std::string &) const;
    template <class TUPLA>
    TUPLA string_to_tuple2(const TUPLA &,const std::string &) const;
    template <class TUPLA>
    TUPLA string_to_tuple3(const TUPLA &,const std::string &) const;
    template <class TUPLA>
    TUPLA string_to_tuple4(const TUPLA &,const std::string &) const;
    template <class TUPLA>
    TUPLA string_to_tuple5(const TUPLA &,const std::string &) const;
    template <class TUPLA>
    TUPLA string_to_tuple6(const TUPLA &,const std::string &) const;
    template <class TUPLA>
    TUPLA string_to_tuple7(const TUPLA &,const std::string &) const;
    template <class TUPLA>
    TUPLA string_to_tuple8(const TUPLA &,const std::string &) const;
    template <class TUPLA>
    TUPLA string_to_tuple9(const TUPLA &,const std::string &) const;

    bool interpreta(const std::string &,const int &numValEsperados= -1) const;
  public:
    EntCmd(EntCmd *owr= NULL);
    void LeeCmd(CmdStatus &status);
    any_const_ptr get_user_param(const std::string &cod) const;
    any_const_ptr GetPropLocal(const std::string &cod) const;
    any_const_ptr GetPropPilaLlamadas(const std::string &cod) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
    inline void EjecutaBloque(CmdStatus &status,const std::string &strblq,const std::string &nmb)
      { ejecuta_bloque(status,strblq,nmb); }
    void EjecutaBloque(const std::string &,const std::string &);
    void MiembroEjecutaBloque(EntCmd *,const std::string &,const std::string &);

    std::vector<size_t> GetIndicesNumericos(CmdStatus &status,const size_t &nmin) const;
    std::vector<size_t> GetArgsNumericos(CmdStatus &status,const size_t &nmin) const;
    std::vector<size_t> GetSubscriptsNumericos(CmdStatus &status,const size_t &nmin) const;

    EntCmd *Owner(void);
    const EntCmd *Owner(void) const;

    const std::string &getLogFileName(void) const;
    void setLogFileName(const std::string &);
    const std::string &getErrFileName(void) const;
    void setErrFileName(const std::string &);    

    bool hasPyProp(const std::string &);
    boost::python::object getPyProp(const std::string &str);
    void setPyProp(std::string str, boost::python::object val);
    boost::python::object evalPy(boost::python::object dict,const std::string &);
    boost::python::object execPy(boost::python::object dict,const std::string &);
    boost::python::object execFilePy(boost::python::object dict,const std::string &);
  };

#include "EntCmd.ih"

#endif
