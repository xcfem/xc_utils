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
//EntCmd.cxx

#include "EntCmd.h"
#include <boost/tokenizer.hpp>
#include "xc_basic/src/matrices/RangoIndice.h"
#include "xc_basic/src/matrices/matrizExpr.h"
#include "xc_utils/src/nucleo/MatrizAny.h"
#include <typeinfo>
#include "../base/CmdStatus.h"
#include <stack>
#include <map>
#include <cmath>
#include <sstream>
#include "../base/BloqueIf.h"
#include "../base/BloqueWhile.h"
#include "../base/BloqueFor.h"
#include "../base/BloqueSub.h"
#include "../base/BloqueFunc.h"
#include "../base/BloqueSwitchStr.h"
#include "../base/PilaLlamadas.h"



#include <boost/any.hpp>
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include "xc_utils/src/nucleo/aux_any.h"

#include <boost/algorithm/string.hpp>
#include "xc_basic/src/texto/cadena_carac.h"
#include <limits>
#include <cstdlib>
#include "xc_utils/src/nucleo/CmdParser.h"
#include "xc_utils/src/base/Locale.h"
#include "xc_utils/src/base/Lista.h"
#include "xc_utils/src/base/CmdTimer.h"
#include "xc_utils/src/sqlite/SqLiteObject.h"
#include "xc_utils/src/libplot/CmdPlotter.h"
#include "xc_utils/src/base/CmdFixedWidthReader.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"
#include "xc_utils/src/nucleo/PropParser.h"

//Variables estáticas de EntCmd.
CmdStatus *EntCmd::ptr_status= NULL; //Puntero a la entrada de comandos.
ErrLogFiles EntCmd::err_log_files; //!< Streams para errores y avisos.
std::deque<std::string> EntCmd::path; //Caminos de acceso a archivos.
SqLiteObject EntCmd::sqlite_interpreter; //Intérprete sqlite.
CmdPlotter EntCmd::psplot; //Gráficos postscript.
CmdFixedWidthReader EntCmd::fw_reader(0); //Lectura de campos de ancho fijo.
std::stack<std::string> EntCmd::pila_nombres_cmd_usuario; //! Contiene los nombres de los comandos de usuario en ejecución.
Locale EntCmd::locale;

//! @brief Constructor por defecto.
EntCmd::EntCmd(EntCmd *owr)
  : EntProp(owr) {}

//! @brief Crea un objeto boost::any a partir de:
//! @param tipo: Tipo del valor a crear (string, double,...).
//! @param valor: Cadena de caracteres de cuya interpretación se obtendrá el valor del objeto.
//! @def_args: Definición de los argumentos para los objetos de tipo función o subrutina.
boost::any EntCmd::string_to_boost_any(const std::string &tipo,const std::string &valor,const std::string &def_args,const std::string &nombre)
  { return interpreta_string_to_boost_any(*this,tipo,valor,def_args,nombre); }

//! @brief Devuelve verdadero si existe el parámetro definido por el usuario
//! cuyo nombre se pasa como parámetro.
bool EntCmd::existe_user_param(const std::string &nmbParamDes) const
  {
    bool retval= false;
    assert(ptr_status);
    const PilaLlamadas &pila= ptr_status->GetPilaLlamadas();
    PilaLlamadas::const_iterator iter_pila;
    if(params.ExisteUserParam(nmbParamDes))
      retval= true;
    else if(Owner() && (Owner()!=this))
      retval= Owner()->existe_user_param(nmbParamDes);
    else if((iter_pila= pila.has_user_param(nmbParamDes))!=pila.end())
      retval= true;
    return retval;
  }

//! @brief Devuelve verdadero si existe el argumento
//! cuyo nombre se pasa como parámetro.
bool EntCmd::existe_arg(const std::string &nmbParamDes) const
  {
    bool retval= false;
    if(sub)
      retval= sub->ExisteNombreArgumento(nmbParamDes);
    return retval;
  }

//! @brief Devuelve un iterador que apunta al parámetro definido por el usuario cuyo nombre se pasa como parametro.
MapParam::param_iterator EntCmd::get_user_param_iterator(const std::string &nmbParamDes)
  {
    if(verborrea>4)
      std::clog << nombre_clase() << "; buscando parámetro: '" << nmbParamDes << "'\n";
    MapParam::param_iterator retval;
    assert(ptr_status);
    const PilaLlamadas &pila= ptr_status->GetPilaLlamadas();
    PilaLlamadas::const_iterator iter_pila;
    if(existe_arg(nmbParamDes))
      {
        retval= sub->get_arg_iterator(nmbParamDes);
        if(verborrea>4)
          std::clog << "Se encontró el parámetro: '" << nmbParamDes 
                    << "' con valor << " << retval->second
                    << " en la rutina." << std::endl;
      }
    else if(params.ExisteUserParam(nmbParamDes))
      {
        retval= params.BuscaUserParam(nmbParamDes);
        if(verborrea>4)
          std::clog << "Se encontró el parámetro: '" << nmbParamDes 
                    << "' con valor << " << retval->second
                    << " en el propio objeto, de clase: '"
                    << nombre_clase() << "'\n";
      }
    else if(Owner() && (Owner()!=this))
      {
        retval= Owner()->get_user_param_iterator(nmbParamDes);
        if(verborrea>4)
          std::clog << "Se encontró el parámetro: '" << nmbParamDes 
                    << "' en el objeto propietario, de clase: '"  << nombre_clase() << "'\n";
      }
    else if((iter_pila= pila.has_user_param(nmbParamDes))!=pila.end())
      {
        retval= (*iter_pila)->get_user_param_iterator(nmbParamDes);
        if(verborrea>4)
          std::clog << "Se encontró el parámetro: '" << nmbParamDes 
                    << "' en la pila de llamadas.\n";
      }
    return retval;
  }

//! @brief Asigna un valor a un parámetro definido por el usuario.
MapParam::param_iterator EntCmd::asigna_param(const std::string &nmbParamDes,const std::string &valor)
  {
    if(verborrea>4)
      std::clog << "Asignando al parámetro '" << nmbParamDes << "' el valor: '"
                << valor << "'" << std::endl;
    boost::any valorAny= interpretaAny(valor);
    
    MapParam::param_iterator retval;
    if(existe_user_param(nmbParamDes))
      {        
	MapParam::param_iterator iterParamDes= get_user_param_iterator(nmbParamDes);
        EntCmd *ent= boost_any_entcmd_cast((*iterParamDes).second);
        if(ent!=this)
          retval= params.AsignaUserParam(iterParamDes,valorAny);
        else
          {
            const std::string posLectura= ptr_status->getPosicionLecturaActual();
            std::cerr << "Se intentó asignar el valor: '" << valor
                      << "' a la variable de nombre: '" << nmbParamDes
                      << "' desde dentro de la propia variable '" << nmbParamDes
                      << "'. " << posLectura << "." << std::endl;
          }
      }
    else
      {
        const std::string posLectura= ptr_status->getPosicionLecturaActual();
        std::cerr << "Se intentó asignar el valor: '" << valor
                  << "' a la variable de nombre: '" << nmbParamDes
                  << "' que no se ha definido "
                  << posLectura << "." << std::endl;
      }
    return retval;
  }

//! @brief Asigna un valor a un parámetro definido por el usuario.
void EntCmd::asigna_elem_param(const std::string &nmbParamDes,const std::string &indices,const std::string &valor)
  {
    if(verborrea>4)
      std::clog << "Asignando al parámetro '" << nmbParamDes 
                << "[" << indices << "]' el valor: '"
                << valor << "'" << std::endl;
    boost::any valorAny= interpretaAny(valor);
    boost::any indicesAny;
    if(has_char(indices,',')) //Varios índices.
      indicesAny= interpretaVectorAny("["+indices+"]");
    else
      indicesAny= interpretaAny(indices);

    if(existe_user_param(nmbParamDes))
      {        
	MapParam::param_iterator iterParamDes= get_user_param_iterator(nmbParamDes);
        EntCmd *ent= boost_any_entcmd_cast((*iterParamDes).second);
        if(ent!=this)
          params.AsignaElemUserParam(iterParamDes,indicesAny,valorAny);
        else
          {
            const std::string posLectura= ptr_status->getPosicionLecturaActual();
            std::cerr << "Se intentó asignar el valor: '" << valor
                      << "' a la variable de nombre: '" << nmbParamDes
                      << "' desde dentro de la propia variable '" << nmbParamDes
                      << "'. " << posLectura << "." << std::endl;
          }
      }
    else
      {
        const std::string posLectura= ptr_status->getPosicionLecturaActual();
        std::cerr << "Se intentó asignar el valor: '" << valor
                  << "' a la variable de nombre: '" << nmbParamDes
                  << "' que no se ha definido "
                  << posLectura << "." << std::endl;
      }
  }


std::string busca_archivo(const std::deque<std::string> &path,const std::string &FileName)
  {
    if(EntCmd::existe_archivo(FileName))
      return FileName;
    std::string retval= "";
    for(std::deque<std::string>::const_iterator i= path.begin();i!=path.end();i++)
      {
        const std::string full_name= (*i) + "/" + FileName;
        if(EntCmd::existe_archivo(full_name))
          {
            retval= full_name;
            break;
          }
      }
    return retval;
  }

//! @brief Ejecuta el bloque de código que se pasa como parámetro.
//! status:
//! @param strblq: Bloque de código a ejecutar.
//! @param nmbBlq: Nombre del bloque de código a ejecutar.
void EntCmd::ejecuta_bloque(CmdStatus &status,const std::string &strblq,const std::string &nmbBlq)
  {
    if(verborrea>2)
      std::clog << '(' << nombre_clase() << "): Ejecutando bloque...";
    status.GetEntradaComandos().NuevoStringEntrada(strblq,nmbBlq);
    const bool nuevo= (this!=ptr_status->GetPilaLlamadas().GetObjetoActual());
    if(nuevo)
      this->LeeCmd(status);
    else
      this->procesa_bloque(status);
    if(verborrea>2)
      std::clog << "ejecutado." << std::endl;
    status.GetEntradaComandos().CierraStringEntrada();
  }

//! @brief Ejecuta el bloque de código que se pasa como parámetro.
void EntCmd::EjecutaBloque(const std::string &strblq,const std::string &nmbBlq)
  {
    assert(ptr_status);
    ejecuta_bloque(*get_ptr_status(),strblq,nmbBlq);
  }

//! @brief Solicita al miembro que se pasa como parámetro que ejecute
//! el bloque de código que se le pasa como parámetro, previa inserción
//! de éste objeto en la pila de llamadas. Se emplea cuando llamamos a
void EntCmd::MiembroEjecutaBloque(EntCmd *ptr_miembro,const std::string &strblq, const std::string &nmbBlq)
  {
    assert(ptr_status);
    const size_t szPilaAntes= ptr_status->GetPilaLlamadas().size();
    if(ptr_miembro)
      {
        const bool nuevo= ptr_status->GetPilaLlamadas().SetObjetoActual(this); //Para que pueda encontrar parámetros.
        ptr_miembro->EjecutaBloque(strblq,nmbBlq);
        if(nuevo)
          if(!ptr_status->GetPilaLlamadas().PopObjetoActual()) //Devolvemos la pila al estado anterior.
            {
              const std::string posLectura= ptr_status->getPosicionLecturaActual();
              std::cerr << "ERROR en EntCmd::MiembroEjecutaBloque; pila vacía." << posLectura << std::endl;
            }
      }
    else
      std::cerr << "ERROR en EntCmd::MiembroEjecutaBloque; se pasó un puntero nulo." << std::endl;
    const size_t szPilaDespues= ptr_status->GetPilaLlamadas().size();
    if(szPilaDespues!=szPilaAntes)
      {
        const std::string posLectura= ptr_status->getPosicionLecturaActual();
        std::cerr << "ERROR en EntCmd::MiembroEjecutaBloque; " << nombre_clase()
                  << " la pila varía de tamaño (antes: " << szPilaAntes 
                 << " después: " << szPilaDespues << ")." << posLectura << std::endl;
      }
  }

//! @brief Devuelve un apuntador a EntCmd si le es posible.
EntCmd *EntCmd::entcmd_cast(boost::any &data)
  { return boost_any_entcmd_cast(data); }

bool EntCmd::ejecuta_comando_user_param(const std::string &cmd,boost::any &data,CmdStatus &status)
  {
    if(verborrea>2)
      std::clog << "EntCmd::ejecuta_comando_user_param (" << nombre_clase() 
                << "::ejecuta_comando_user_param) ejecutando comando usuario: " << cmd << std::endl;
    bool retval= false;
    if(BloqueBase *ptr_bloque= boost::any_cast<BloqueBase>(&data))
      {
        ptr_bloque->LeeCmd(status);
        ejecuta_bloque(status,ptr_bloque->Bloque(),ptr_bloque->getNombre());
        retval= true;
      }
    else if(BloqueSub *ptr_bloque_sub= boost::any_cast<BloqueSub>(&data))
      {
        ptr_bloque_sub->set_owner(this);
        ptr_bloque_sub->LeeCmd(status);
        const CmdParser &parser= status.Parser();
        const EntCmd *caller= status.GetPilaLlamadas().GetObjetoActual();
        if(caller)
          {
            if(parser.TieneArgs())
              {
                const size_t sz_pila1= InterpreteRPN::Pila().size();
                caller->interpreta(parser.GetArgs());
                const size_t sz_pila2= InterpreteRPN::Pila().size();
                ptr_bloque_sub->valores_parametros(sz_pila2-sz_pila1);
              }
            else
              if(ptr_bloque_sub->NumParametros()>0)
	        std::cerr << "Ojo se llamó a la rutina: '" << cmd << "' sin especificar parámetros." << std::endl;
            ptr_bloque_sub->Run(caller);
          }
        else
          {
            const std::string posLectura= status.getPosicionLecturaActual();
	    std::cerr << "Se llamó a la rutina: '" << cmd
                      << "' desde un objeto anónimo." << posLectura << std::endl;
          }
        retval= true;
      }
    else if(double *ptr_double= boost::any_cast<double>(&data))
      {
        *ptr_double= interpretaDouble(status.GetString());
        retval= true;
      }
    else if(std::string *ptr_string= boost::any_cast<std::string>(&data))
      {
        *ptr_string= interpretaString(status.GetString());
        retval= true;
      }
    else if(EntCmd *ptr= entcmd_cast(data)) //Resto de objetos derivados de EntCmd.
      {
        ptr->LeeCmd(status);
        retval= true;
      }
    else
      {
        std::clog << "El parámetro: '" << cmd << "' no lee comandos, se ignora la entrada." << std::endl;
        status.GetBloque();
      }
    return retval;
  }

//! @brief Procesa un comando de un parámetro definido por el usuario
bool EntCmd::procesa_comando_user_param(const std::string &cmd,CmdStatus &status)
  {
    bool retval= false;
    pila_nombres_cmd_usuario.push(cmd);
    boost::any *data= params.GetUserParamPtr(cmd);
    if(data)
      retval= ejecuta_comando_user_param(cmd,*data,status);
    pila_nombres_cmd_usuario.pop();
    return retval;
  }


//! @brief Ejecuta las instrucciones del archivo cuyo nombre se pasa
//! como parámetro.
void EntCmd::incluye_archivo(CmdStatus &status,const std::string &nmb_archivo)
  {
    if(verborrea>2)
      std::clog << "Cargando archivo: " << nmb_archivo << std::endl;
    status.GetEntradaComandos().NuevoArchivoEntrada(nmb_archivo);
    this->procesa_bloque(status);
    if(verborrea>2)
      std::clog << "Procesado archivo: " << nmb_archivo << std::endl;
    status.GetEntradaComandos().CierraArchivoEntrada();
  }

//! @brief Procesa comandos relativos a comandos de control (for,if,while,...)
bool EntCmd::procesa_comando_control(const std::string &cmd,CmdStatus &status)
  {
    const CmdParser &parser= status.Parser();
    if(cmd == "if") //Lee un bloque if then else.
      {
	std::string cnd= "";
        if(parser.TieneArgs())
          cnd= parser.GetArgs();
        BloqueIf bloque_if(this,cnd);
        bloque_if.LeeCmd(status);
        if(bloque_if.verdadero())
          ejecuta_bloque(status,bloque_if.BloqueThen(),"then");
        else
          ejecuta_bloque(status,bloque_if.BloqueElse(),"else");
        return true;
      }
    else if(cmd == "while") //Lee un bloque while.
      {
	std::string cnd= "";
        if(parser.TieneArgs())
          cnd= parser.GetArgs();
        BloqueWhile bloque_while(this,cnd);
        bloque_while.LeeCmd(status);
        while(bloque_while.verdadero())
          ejecuta_bloque(status,bloque_while.Bloque(),"while");
        return true;
      }
    else if(cmd == "for") //Lee un bloque for.
      {
	std::string ini= "";
	std::string cont= "";
	std::string incr= "";
        if(parser.TieneArgs())
          {
	    const std::deque<std::string> args= separa_cadena(parser.GetArgs(),";");
            const size_t sz= args.size();
            if(sz==3)
              {
                ini= "\\set{"+args[0]+"}";
                cont= args[1];
                incr= "\\set{"+args[2]+"}";
              }
            else
	      std::cerr << "Se esperaban 3 argumentos para el comando for,"
                        << " se obtuvieron " << sz << ".\n";
          }
        BloqueFor bloque_for(this,ini,cont,incr);
        bloque_for.LeeCmd(status);
        ejecuta_bloque(status,bloque_for.Inicio(),"inicio_for"); //Valor inicial.
        while(bloque_for.continua())
          {
            ejecuta_bloque(status,bloque_for.Bloque(),"for");
            ejecuta_bloque(status,bloque_for.Incremento(),"incremento_for");
          }
        return true;
      }
    if(cmd == "switch_str") //Lee un bloque switch.
      {
	std::string idx= "";
        if(parser.TieneArgs())
          idx= interpretaString(parser.GetArgs());
        else
          {
            const std::string posLectura= ptr_status->getPosicionLecturaActual();
            std::cerr << "Falta el argumento para switch_str "
                      << posLectura << "." << std::endl;
          }
        BloqueSwitchStr bloque_switch(this);
        bloque_switch.LeeCmd(status);
        if(bloque_switch.hasCase(idx))
          ejecuta_bloque(status,bloque_switch.Bloque(idx),"switch");
        return true;
      }
    else if(cmd == "bloque")    // Lee un bloque de código y lo ejecuta, no tiene más
      {                         // utilidad que comprobar que esto es posible.
        const std::string str= status.GetBloque();
        ejecuta_bloque(status,str,"bloque");
        return true;
      }
    else
      return false;
  }

//! @brief Devuelve la máscara de bits para el modo de apertura de un archivo.
std::ios_base::openmode get_openmode(bool salida,const size_t &offset,const std::deque<boost::any> &indices)
  {
     std::ios_base::openmode mode;//Máscara de bits para el modo de apertura.
     if(salida)
       mode= std::ios_base::out;
     else
       mode= std::ios_base::in;
     const size_t sz= indices.size();
     for(size_t i=offset;i<sz;i++)
       {
         const std::string str= boost_any_to_string(indices[i]);
         mode|= string_to_openmode(str);
       }
     return mode;
  }

//! @brief Procesa comandos relativos a archivos de entrada y salida.
void EntCmd::nuevo_archivo(bool salida,CmdStatus &status)
  {
     const std::string path= interpretaString(status.GetString());
     const CmdParser &parser= status.Parser();
     std::deque<boost::any> indices= crea_deque_boost_any(parser.GetIndices());
     const size_t sz= indices.size();
     std::string nombre= "def";
     if(sz>0) nombre= boost_any_to_string(indices[0]); //Nombre del archivo.
     const std::ios_base::openmode mode= get_openmode(salida,1,indices);
     if(salida)
       status.GetArchivosSalida().NuevoArchivo(nombre,path,mode);
     else
       {
         if(existe_archivo(path))
           { status.GetArchivosEntrada().NuevoArchivo(nombre,path,mode); }
         else
           std::cerr << "EntCmd::nuevo_archivo;  el archivo: "
                     << path << " no existe." << std::endl;
       }
  }

//! @brief Procesa comandos relativos a archivos de entrada y salida.
bool EntCmd::procesa_comando_archivos(const std::string &cmd,CmdStatus &status)
  {
    const CmdParser &parser= status.Parser();
    if(cmd == "incluye") //Inclusión de archivos.
      {
        std::string nmb_archivo= interpretaString(status.GetEntradaComandos().nombre_archivo());
        if(existe_archivo(nmb_archivo))
          {
            incluye_archivo(status,nmb_archivo);
            return true;
	  }
        else
          {
            const std::string full_name= busca_archivo(path,nmb_archivo);
            if(full_name!="")
              {
                incluye_archivo(status,full_name);
                return true;
              }
            else
              {
                const std::string posLectura= status.getPosicionLecturaActual();
	        std::cerr << "El archivo: " << nmb_archivo 
                          << " no existe. " << posLectura << std::endl;
              }
          }
        return true;      }
    else if(cmd == "archivo_log")
      {
        setLogFileName(interpretaString(status.GetString()));
        return true;
      }
    else if(cmd == "archivo_err")
      {
        setErrFileName(interpretaString(status.GetString()));
        return true;
      }
    else if(cmd == "nuevo_archivo_salida")
      {
        if(!parser.TieneIndices())
	  std::cerr << "uso: " << cmd << "[nombre,mode,mode,...]{path}" << std::endl;
        else
          nuevo_archivo(true,status);
        return true;
      }
    else if(cmd == "cierra_archivo_salida")
      {
        status.GetArchivosSalida().CierraArchivo(interpretaString(status.GetString()));
        return true;
      }
    else if(cmd == "nuevo_archivo_entrada")
      {
        if(!parser.TieneIndices())
	  std::cerr << "uso: " << cmd << "[nombre,mode,mode,...]{path}" << std::endl;
        else
          nuevo_archivo(false,status);
        return true;
      }
    else if(cmd == "cierra_archivo_entrada")
      {
        status.GetArchivosEntrada().CierraArchivo(interpretaString(status.GetString()));
        return true;
      }
    else if(cmd == "borra_archivo")
      {
        const std::string nombre= interpretaString(status.GetString());
        const std::string str_error= "Error al borrar el archivo: '"+nombre+"'";
        if(remove(nombre.c_str())!=0)
          perror(str_error.c_str());
        return true;
      }
    else if(cmd == "borra_archivo_si_existe")
      {
        const std::string nombre= interpretaString(status.GetString());
        const std::string str_error= "Error al borrar el archivo: '"+nombre+"'";
        if(existe_archivo(nombre))
          if(remove(nombre.c_str())!=0)
            perror(str_error.c_str());
        return true;
      }
    else
      return false;
  }

//! Lee un objeto EntCmd desde archivo
//! Soporta los comandos:
//! -if: Lee un bloque if.
//! -c: Comentario.
bool EntCmd::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd()); //Desreferencia comando.
    const std::string str_err= "(EntCmd) Procesando comando: '" + cmd + "'";
    if(verborrea>2)
      std::clog << str_err << std::endl;

    const CmdParser &parser= status.Parser();

    if(cmd == "def_prop") //Define una propiedad.
      {
        const std::string str_error= "uso: \\def_prop[nombre,tipo]{valor}.";
        const CmdParser &parser= status.Parser();
        if(parser.TieneIndices())
          {
            interpreta(parser.GetIndices());
            if(InterpreteRPN::HayArgumentos(2,cmd))
              {
                const std::string tipo= convert_to_string(InterpreteRPN::Pila().Pop());
                const std::string nombre= convert_to_string(InterpreteRPN::Pila().Pop());
                if(existe_user_param(nombre))
                  {
                    const std::string posLectura= status.getPosicionLecturaActual();
		    std::cerr << str_err 
                              << " ¡Ojo! ya existe un parámetro de nombre: '"
                              << nombre
                              << "' que es accesible desde el objeto. " 
                              << posLectura << '.' << std::endl;
                  }
                const std::string valor= status.GetBloque();
                if(parser.TieneArgs())
                  params.Props().CreaUserParam(nombre,string_to_boost_any(tipo,valor,parser.GetArgs(),nombre));
                else
                  params.Props().CreaUserParam(nombre,string_to_boost_any(tipo,valor,"",nombre));
              }
            else
	      std::cerr << str_error << std::endl;
          }
        else
	  std::cerr << str_error << std::endl;
        return true;
      }
    if(cmd == "def_var") //Define una variable.
      {
        const std::string str_error= "uso: \\def_var[nombre,tipo]{valor}.";
        const CmdParser &parser= status.Parser();
        if(parser.TieneIndices())
          {
            interpreta(parser.GetIndices());
            if(InterpreteRPN::HayArgumentos(2,cmd))
              {
                const std::string tipo= convert_to_string(InterpreteRPN::Pila().Pop());
                const std::string nombre= convert_to_string(InterpreteRPN::Pila().Pop());
                if(existe_user_param(nombre))
		  std::cerr << str_error 
                            << " ¡Ojo! ya existe un parámetro de nombre: '"
                            << nombre
                            << "' que es accesible desde el objeto." << std::endl;
                const std::string valor= status.GetBloque();
                if(parser.TieneArgs())
                  params.Vars().CreaUserParam(nombre,string_to_boost_any(tipo,valor,parser.GetArgs(),nombre));
                else
                  params.Vars().CreaUserParam(nombre,string_to_boost_any(tipo,valor,"",nombre));
              }
            else
	      std::cerr << str_error << std::endl;
          }
        else
	  std::cerr << str_error << std::endl;
        return true;
      }
    else if((cmd == "let") || (cmd == "set")) //Asigna un valor a una parámetro.
      {
        const std::string arg= status.GetString();
	std::deque<std::string> campos= split_at_first(arg,'=');
        if(campos.size()>1)
          {
            PropParser parser(campos[0]);
            const std::string nmb= parser.GetNmbProp();
            const std::string resto= campos[1];
            if(!parser.TieneIndices())
              asigna_param(nmb,resto);
            else
              {
                const std::string indices= parser.GetIndices();
                asigna_elem_param(nmb,indices,resto);
              }
          }
        else
	  std::cerr << str_err 
                    << "; se esperaba una expresión de asignación, se obtuvo: '"
                    << arg << "'\n";
        return true;
      }
    else if(cmd == "for_each_prop")
      {
        const std::string bloque= status.GetBloque();
        if(!params.Props().empty())
          {
	    MapParam::param_iterator i= params.Props().begin();
	    for(;i!= params.Props().end();i++)
              {
                boost::any &data= (*i).second;
                if(EntCmd *ptr= boost::any_cast<EntCmd>(&data))
                  ptr->LeeCmd(status);
                else
                  std::clog << str_err 
                            << "; la propiedad: " << (*i).first 
                            << " no lee comandos." << std::endl;
              }
          }
        return true;
      }
    else if(cmd == "for_each_var")
      {
        const std::string bloque= status.GetBloque();
        if(!params.Vars().empty())
          {
	    MapParam::param_iterator i= params.Vars().begin();
	    for(;i!= params.Vars().end();i++)
              {
                boost::any &data= (*i).second;
                if(EntCmd *ptr= boost::any_cast<EntCmd>(&data))
                  ptr->LeeCmd(status);
                else
                  std::clog << str_err
                            << "; la variable: " << (*i).first 
                            << " no lee comandos." << std::endl;
              }
          }
        return true;
      }
    else if(cmd == "clearProps") //Borra todos los parámetros.
      {
        const std::string tmp= status.GetString(); //Ignoramos entrada.
        clearProps();
        return true;
      }
    else if(cmd == "erase") //Borra los parámetros cuyos nombres se pasan como parámetro.
      {
        const std::vector<std::string> &nombres= crea_vector_string(status.GetBloque());
        params.BorraUserParams(nombres.begin(),nombres.end());
        return true;
      }
    else if(cmd == "c") //Comentario
      {
        bool error= false;
        status.GetEntradaComandos().procesa_comentario(error);
        if(error)
          {
            const std::string posLectura= status.getPosicionLecturaActual();
	    std::cerr << str_err  
                      << "'; error al procesar comentario. "
                      << posLectura << std::endl;
          }          
        return true;
      }
    else if(cmd == "nverborrea") //Nivel de verborrea.
      {
        verborrea= interpretaInt(status.GetString());
        return true;
      }
    else if(cmd == "print")
      {
        const std::string &str= status.GetBloque(true);
	std::string nombre= "";
        if(parser.TieneIndices()) //Salida en archivo por defecto.
          {
            std::deque<boost::any> indices= parser.SeparaIndices(this);
            nombre= convert_to_string(indices[0]);
          }
	std::ostream *os= status.GetArchivosSalida().GetArchivo(nombre);
        print(os,str);
        return true;
      }
    else if(cmd == "output_precision")
      {
        const streamsize prec= interpretaInt(status.GetString());
	std::string nombre= "";
        if(parser.TieneIndices()) //Salida en archivo por defecto.
          {
            std::deque<boost::any> indices= parser.SeparaIndices(this);
            nombre= convert_to_string(indices[0]);
          }
	std::ostream *os= status.GetArchivosSalida().GetArchivo(nombre);
        os->precision(prec);
        return true;
      }
    else if(cmd == "imbue")
      {
        const std::string &nombre= status.GetBloque(true);
	std::ostream *os= status.GetArchivosSalida().GetArchivo(nombre);
        os->imbue(locale.getLocale());
        return true;
      }
    else if(cmd == "locale")
      {
        locale.set_owner(this);
        locale.LeeCmd(status);
        return true;
      }
    else if(cmd == "comb_acciones")
      {
	std::cerr << "comb_acciones DEPRECATED; use Python" << std::endl;
        return true;
      }
    else if(cmd == "expr") //Intérprete de expresiones
      {
        const std::string arg= status.GetString();
	std::deque<std::string> campos= split_at_first(arg,'=');
        if(campos.size()>1)
          nueva_expr(campos[0],campos[1]);
        else
          {
            const std::string posLectura= status.getPosicionLecturaActual();
	    std::cerr << str_err  
                      << "'; se esperaba una expresión de asignación, se obtuvo: '"
                      << arg << "'. " << posLectura << std::endl;
          }
        return true;
      }
    else if(cmd == "var")
      {
	std::deque<std::string> campos= separa_cadena(status.GetString(),"=",2);
        const std::string &nmb= campos[0];
        const double d= interpretaDouble(campos[1]);
        nueva_var(nmb,d);
        return true;
      }
    else if(cmd == "eval")
      {
        const std::string str= interpretaString(status.GetString());
        bool ok= eval(str);
        if(!ok)
          {
            const std::string posLectura= status.getPosicionLecturaActual();
            std::cerr << str_err
                      << "; no se pudo evaluar la expresión: '"
                      << str << "'. " << posLectura << std::endl;
          }
        return true;
      }
    else if(cmd == "assert")
      {
        const std::string str= status.GetString();
        const bool tmp= interpretaBool(str);
        if(!tmp)
          {
            const std::string posLectura= ptr_status->getPosicionLecturaActual();
            std::clog << str_err
                      << "; no se cumplió la aserción: '"
                      << str << "'. " << posLectura << std::endl;
          }
        assert(tmp);
        return true;
      }
    else if(cmd == "sys")
      {
        const std::string str= boost::trim_copy_if(interpretaString(status.GetBloque()),boost::is_any_of("\""));
        if(verborrea>0)
	  std::clog << "Ejecutando comando del sistema: '" << str << "'\n";
        int result= system(str.c_str());
        if(result== -1)
	  std::cerr << str_err 
                    << "; error al ejecutar el comando del sistema: '" << str << "'\n";
        return true;
      }
    else if(cmd == "path")
      {
	const std::deque<boost::any> params= crea_deque_boost_any(status.GetString());
	std::string tmp;
        for(std::deque<boost::any>::const_iterator i= params.begin();i!=params.end();i++)
          {
            tmp= boost_any_to_string(*i);
            if(!EntCmd::existe_archivo(tmp))
	      std::cerr << str_err << "; el path: '" 
                        << tmp << "' no existe." << std::endl; 
            path.push_back(tmp);
          }
        return true;
      }
    else if(cmd == "sqlite")
      {
        sqlite_interpreter.set_owner(this);
        sqlite_interpreter.LeeCmd(status);
        return true;
      }
    else if(cmd == "psplot")
      {
        psplot.set_owner(this);
        psplot.LeeCmd(status);
        return true;
      }
    else if(cmd == "fixedWidthReader")
      {
        fw_reader.set_owner(this);
        fw_reader.LeeCmd(status);
        return true;
      }
    else if(procesa_comando_control(cmd,status))
      return true;
    else if(procesa_comando_archivos(cmd,status))
      return true;
    else if(procesa_comando_user_param(cmd,status))
      return true;
    else if(cmd.empty()) //Comando vacío.
      {
        const std::string posLectura= ptr_status->getPosicionLecturaActual();
        std::cerr << str_err << " se procesa un comando vacío."
                  << posLectura  << std::endl;
        return true;
      }
    else if(cmd == "fin") //Fin de programa.
      {
        status.GetBloque();
        exit(0);
        return true;
      }
    return false;
  }

//! @brief Devuelve los índices [a,b,c,...] de la línea de comando.
std::vector<size_t> EntCmd::GetIndicesNumericos(CmdStatus &status,const size_t &nmin) const
  {
    const CmdParser &parser= status.Parser();
    std::vector<size_t> indices;
    if(parser.TieneIndices())
      {
        const std::string &args= parser.GetIndices();
        indices= crea_vector_size_t(args);
        const size_t nc= indices.size(); //no. de índices.
        if(nc<nmin)
          std::cerr << nombre_clase() << "procesa_comando; error procesando comando: "
                    << deref_cmd(status.Cmd()) << " se leyeron " << nc
                    << " índices, se esperaban " << nmin << '.' << std::endl;
      }
    return indices;
  }

//! @brief Devuelve los argumentos (a,b,c,...) de la línea de comando.
std::vector<size_t> EntCmd::GetArgsNumericos(CmdStatus &status,const size_t &nmin) const
  {
    const CmdParser &parser= status.Parser();
    std::vector<size_t> args_num;
    if(parser.TieneArgs())
      {
        const std::string &args= parser.GetArgs();
        args_num= crea_vector_size_t(args);
        const size_t nc= args_num.size(); //no. de índices.
        if(nc<nmin)
          std::cerr << nombre_clase() << "procesa_comando; error procesando comando: "
                    << deref_cmd(status.Cmd()) << " se leyeron " << nc
                    << " argumentos, se esperaban " << nmin << '.' << std::endl;
      }
    return args_num;
  }

//! @brief Devuelve los índices [a,b,c,...] o argumentos (a,b,c,...) de la línea de comando.
std::vector<size_t> EntCmd::GetSubscriptsNumericos(CmdStatus &status,const size_t &nmin) const
  {
    std::vector<size_t> subscripts= GetIndicesNumericos(status,nmin);
    if(subscripts.empty())
      subscripts= GetArgsNumericos(status,nmin);
    return subscripts;
  }

void EntCmd::procesa_metodo(CmdStatus &status)
  {
    std::cerr << "Error: " << nombre_clase() 
              << "::procesa_metodo no implementada. " << std::endl;
  }

//! @brief Lee un caracter de la entrada de datos y, en su caso,
//! dispara la lectura de comandos.
resul_lectura EntCmd::procesa_caracter(CmdStatus &status)
  {
    char c= status.GetEntradaComandos().GetChar();
    if(!status.GetEntradaComandos().Ok()) return FALLO;
    if(c == '\\')
      {
        status.nuevo_comando();
        
        bool procesado= procesa_comando(status);
        if(sub && !procesado)
          {
            EntCmd *sub_no_const= const_cast<BloqueSub *>(sub);
            assert(sub_no_const);
            procesado= sub_no_const->procesa_comando(status);
          }
        if(Owner() && !procesado)
          procesado= Owner()->procesa_comando(status);
        if(!procesado) //El comando no es de éste objeto ni de sus ancestros.
          procesado= status.GetPilaLlamadas().procesa_comando(status,this); //Descendemos por la pila.
        if(!procesado)
          {
            status.cmd_desconocido(nombre_clase(),deref_cmd(status.Cmd()),verborrea);
            status.GetEntradaComandos().get_argumento();
            exit(1);
          }
      }
    else if(c == '}')
      {
        return COMPLETADO;
      }
    else if(isspace(c))
      return CONTINUA;
    else if(c == '#') //Comentario.
      {
        status.GetEntradaComandos().get_linea(); //Nos comemos el resto de la línea.
        return CONTINUA;
      }
    else if(c == '/') //Comentario de tipo C++.
      {
        const char c2= status.GetEntradaComandos().peek();
        if(c2 == '/') status.GetEntradaComandos().get_linea(); //Nos comemos el resto de la línea.
        return CONTINUA;
      }
    else
      {
        const std::string posLectura= ptr_status->getPosicionLecturaActual();
        std::clog << "EntCmd::procesa_caracter; no se esperaba el carácter: '" 
                  << c << "' (ASCII " << int(c) << ")." << posLectura << std::endl;
      }
    return CONTINUA;
  }

//! @brief Ejecuta un bloque de comandos.
void EntCmd::procesa_bloque(CmdStatus &status)
  {
    while(status.GetEntradaComandos().Ok())
      {
        resul_lectura r= procesa_caracter(status);
        if(r==FALLO)
          break;
        else if(r==COMPLETADO)
          {
            status.cmd_completado();
            params.clearVars(); //Borra las variables definidas dentro del bloque.
            if(verborrea>3)
	      std::clog << "EntCmd::procesa_bloque; terminó la lectura del objeto de tipo: " << nombre_clase() << std::endl;
            return;
          }
      } //Termina (o falla) la lectura del objeto desde archivo.
  }

//! @brief Lee comandos desde archivo.
void EntCmd::LeeCmd(CmdStatus &status)
  {
    ptr_status= &status;
    const size_t szPilaAntes= status.GetPilaLlamadas().size();
    inserta_buscadores(status);
    const bool nuevo= status.GetPilaLlamadas().SetObjetoActual(this); //Inserta el objeto en la pila de llamadas.
    if(!nuevo)
      {
        const std::string posLectura= status.getPosicionLecturaActual();
	std::cerr << "El objeto: '" << nombre_clase()
                  << "' se llama a sí mismo." << posLectura << std::endl;
      }
    procesa_bloque(status);
    if(nuevo) 
      if(!status.GetPilaLlamadas().PopObjetoActual()) //Devolvemos la pila al estado anterior.
        {
          const std::string posLectura= status.getPosicionLecturaActual();
          std::cerr << "ERROR en EntCmd::LeeCmd; pila vacía." << posLectura << std::endl;
        }
    const size_t szPilaDespues= status.GetPilaLlamadas().size();
    if(szPilaDespues!=szPilaAntes)
      {
        const std::string posLectura= status.getPosicionLecturaActual();
        std::cerr << "ERROR en EntCmd::LeeCmd; " << nombre_clase()
                  << " la pila varía de tamaño (antes: " << szPilaAntes 
                 << " después: " << szPilaDespues << ")." << posLectura << std::endl;
      }
  }


//! @brief Devuelve un parámetro definido por el usuario (si existe).
any_const_ptr EntCmd::get_user_param(const std::string &cod) const
  {
    if(params.empty())
      return any_const_ptr();
    if(params.ExisteUserParam(cod)) //El parámetro existe.
      {
        MapParam::param_const_iterator i= params.BuscaUserParam(cod);
        if(i->second.type() == typeid(BloqueFunc)) //Es una función.
          {
            pila_nombres_cmd_usuario.push(cod);
            const BloqueFunc *ptr_bloque_func= boost::any_cast<BloqueFunc>(&(i->second));
            BloqueFunc *ptr_bloque_func_no_const= const_cast<BloqueFunc *>(ptr_bloque_func);
            EntCmd *this_no_const= const_cast<EntCmd *>(this);
            ptr_bloque_func_no_const->set_owner(this_no_const);
            const size_t sz_pila= InterpreteRPN::Pila().size();// XXX Esto está mal. Deberíamos contar los
                                                               // argumentos entre paréntesis que haya obtenido el intérprete
            const size_t argc= ptr_bloque_func->NumParametros();
            if(argc<=sz_pila)
              ptr_bloque_func->valores_parametros(argc);
            else
	      std::cerr << "Faltan parámetros para la función, se necesitan: " << argc
                        << " y se dispone de: " << sz_pila << std::endl;
            
            const EntCmd *caller= ptr_status->GetPilaLlamadas().GetObjetoActual();

            if(caller)
              {
                const size_t tamPilaAntes= InterpreteRPN::Pila().size();
                ptr_bloque_func->Run(caller);
                pila_nombres_cmd_usuario.pop();
                const size_t numValores= InterpreteRPN::Pila().size()-tamPilaAntes;
                if(numValores==1) //La función devolvió un valor.
                  {
                    static boost::any tmp_gp_any;
                    tmp_gp_any= InterpreteRPN::Pila().Pop();
                    return any_const_ptr(tmp_gp_any);
		  }
                else
                  {
                    const std::string posLectura= ptr_status->getPosicionLecturaActual();
	            std::cerr << "La función: '" << cod
                              << "' devolvió " << numValores << " valores." << posLectura << std::endl;
                    return any_const_ptr();
                  }                  
              }
            else
              {
                const std::string posLectura= ptr_status->getPosicionLecturaActual();
	        std::cerr << "Se llamó a la función: '" << cod
                          << "' desde un objeto anónimo." << posLectura << std::endl;
                return any_const_ptr();
              }
          }
        else
          return any_const_ptr(i->second);
      }
    else
      return any_const_ptr();
  }

//! @brief Busca el parámetro cuyo código se pasa como parámetro en la pila de llamadas.
any_const_ptr EntCmd::GetPropPilaLlamadas(const std::string &cod) const
  {
    if(ptr_status)
      return ptr_status->GetPilaLlamadas().GetProp(cod);
    else
      return any_const_ptr();
  }

//! @brief Interpreta una cadena de caracteres y coloca los resultados en la pila.
bool EntCmd::interpreta(const std::string &str,const int &numValEsperados) const
  {
    bool ok= EntProp::interpreta(str,numValEsperados);
    if(!ok)
      {
        CmdStatus *ptr_status= get_ptr_status();
        const std::string posLectura= ptr_status->getPosicionLecturaActual();
        std::cerr << "clase: " << nombre_clase() << ' ' << posLectura << std::endl;
        
      }
    return ok;
  }

//! @brief Devuelve la propiedad o variable LOCAL del objeto cuyo código (de la propiedad) se pasa
//! como parámetro. Se entiende por propiedad LOCAL la que está definida en el propio objeto
//! y, por tanto, no requiere consultar a ningún otro (su propietario,pila de llamadas,...).
any_const_ptr EntCmd::GetPropLocal(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntCmd::GetPropLocal (" << nombre_clase() 
                << "::GetPropLocal) Buscando propiedad: " << cod << std::endl;
    if(params.ExisteUserParam(cod))
      {
        return get_user_param(cod);
      }
    else if(cod == "size_streams_entrada")
      {
        tmp_gp_szt= ptr_status->GetEntradaComandos().get_size_streams_entrada();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "path_size")
      {
        tmp_gp_szt= path.size();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod=="getRutaPilaLlamadas")
      {
        assert(ptr_status);
        const PilaLlamadas &pila= ptr_status->GetPilaLlamadas();
        tmp_gp_str= pila.getRuta();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "readln")
      {
        if((InterpreteRPN::Pila().size()>0) && ptr_status) //Se da el nombre del archivo.
          {
            const std::string &fName= convert_to_string(InterpreteRPN::Pila().Pop()); //Nombre del archivo.
	    std::istream *is= ptr_status->GetArchivosEntrada().GetArchivo(fName);
            getline(*is,tmp_gp_str);
            return any_const_ptr(tmp_gp_str);
          }
        else if(ptr_status)
          {
	    std::istream *is= ptr_status->GetArchivosEntrada().DefInputFile();
            getline(*is,tmp_gp_str);
            return any_const_ptr(tmp_gp_str);
          }
        else
          {
            std::cerr << "Error en EntCmd::GetPropLocal (" << nombre_clase() 
                      << "::GetPropLocal) Buscando propiedad: " << cod 
                      << " ptr_status es nulo." << std::endl;
            return any_const_ptr();
          }
      }
    else if(cod == "fixedWidth2Csv")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
	    boost::any tmp= InterpreteRPN::Pila().Pop();
            if(boost_any_is_string(tmp))
              {
                if(fw_reader.getReader().numCampos()< 1)
		  {
                    const std::string posLectura= ptr_status->getPosicionLecturaActual();
		    std::cerr << "Error en fixedWidth2Csv: " << posLectura
                              << " el lector de campos fijos no se inicializó (setVectorIndices)." << std::endl;
                  }
                tmp_gp_str= fw_reader.getReader().get_csv_string(boost_any_to_string(tmp));
                return any_const_ptr(tmp_gp_str);
              }
            else
              {
                err_tipo_argumento(std::cerr,1,"GetPropLocal",cod,"string",boost_any_tipo_operando(tmp));
                return any_const_ptr();
              }
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
            return any_const_ptr();
          } 
      }
    else if(cod == "csv2list")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
	    boost::any tmp= InterpreteRPN::Pila().Pop();
            if(boost_any_is_string(tmp))
              {
                EntCmd *this_no_const= const_cast<EntCmd *>(this);
                const std::string str= boost_any_to_string(tmp);
                tmp_gp_lista.set_owner(this_no_const);
                tmp_gp_lista.clearAll();
                tmp_gp_lista.fromString(str);
                return any_const_ptr(tmp_gp_lista);
              }
            else
              {
                err_tipo_argumento(std::cerr,1,"GetPropLocal",cod,"string",boost_any_tipo_operando(tmp));
                return any_const_ptr();
              }
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
            return any_const_ptr();
          } 
      }
    else if(cod == "separaCsv")
      {
        if(InterpreteRPN::Pila().size()>0)
          {
	    boost::any tmp= InterpreteRPN::Pila().Pop();
            if(boost_any_is_string(tmp))
              {
                EntCmd *this_no_const= const_cast<EntCmd *>(this);
                const std::string str= boost_any_to_string(tmp);
                tmp_gp_lista.set_owner(this_no_const);
                tmp_gp_lista.clearAll();
                const std::deque<std::string> valores= separa_csv(str);
                for(std::deque<std::string>::const_iterator i=valores.begin();i!=valores.end();i++)
                  tmp_gp_lista.Inserta(*i);
              }
            else
              {
                err_tipo_argumento(std::cerr,1,"GetPropLocal",cod,"string",boost_any_tipo_operando(tmp));
                return any_const_ptr();
              }
            return any_const_ptr(tmp_gp_lista);
          }
        else
          {
            err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
            return any_const_ptr();
          } 
      }
    else if(cod == "good")
      {
        if((InterpreteRPN::Pila().size()>0) && ptr_status) //Se da el nombre del archivo.
          {
            const std::string &fName= convert_to_string(InterpreteRPN::Pila().Pop()); //Nombre del archivo.
	    tmp_gp_bool= ptr_status->GetArchivosEntrada().good(fName);
            return any_const_ptr(tmp_gp_bool);
          }
        else if(ptr_status)
          {
	    std::istream *is= ptr_status->GetArchivosEntrada().DefInputFile();
            tmp_gp_bool= is->good();
            return any_const_ptr(tmp_gp_bool);
          }
        else
          {
            std::cerr << "Error en EntCmd::GetPropLocal (" << nombre_clase() 
                      << "::GetPropLocal) Buscando propiedad: " << cod 
                      << " ptr_status es nulo." << std::endl;
            return any_const_ptr();
          }
      }
    else if(cod == "argc")
      {
        if(ptr_status)
          {
            assert(ptr_status);
            tmp_gp_szt= ptr_status->getNumCmdArgs();
            return any_const_ptr(tmp_gp_szt);
          }
        else
          {
            if(!ptr_status)
              std::cerr << "Error en EntCmd::GetPropLocal (" << nombre_clase() 
                        << "::GetPropLocal) Buscando propiedad: " << cod 
                        << " ptr_status es nulo." << std::endl;
            return any_const_ptr();
          }
      }
    else if(cod == "argv")
      {
        if((InterpreteRPN::Pila().size()>0) && ptr_status) //Se da el nombre del archivo.
          {
            assert(ptr_status);
            tmp_gp_str= ptr_status->getCmdArg(convert_to_int(InterpreteRPN::Pila().Pop()));
            return any_const_ptr(tmp_gp_str);
          }
        else
          {
            if(!ptr_status)
              std::cerr << "Error en EntCmd::GetPropLocal (" << nombre_clase() 
                        << "::GetPropLocal) Buscando propiedad: " << cod 
                        << " ptr_status es nulo." << std::endl;
            else
              err_num_argumentos(std::cerr,1,"GetPropLocal",cod);
            return any_const_ptr();
          }
      }
    else if(cod == "nuevoArchivoTemporal")
      {
        if(InterpreteRPN::Pila().size()>1)
          {
            const std::string pth= convert_to_string(InterpreteRPN::Pila().Pop());
            const std::string nombre= convert_to_string(InterpreteRPN::Pila().Pop());
	    const std::ios_base::openmode mode= std::ios_base::trunc | std::ios_base::out;
            tmp_gp_str= ptr_status->GetArchivosSalida().NuevoArchivoTemporal(nombre,pth,".tmp",mode);
            return any_const_ptr(tmp_gp_str);
          }
        else
          {
            err_num_argumentos(std::cerr,2,"GetProp",cod);
            return any_const_ptr();
          }
      }
    else
      return EntProp::GetPropLocal(cod);
  }


//! \brief Devuelve la propiedad del objeto cuyo código (de la propiedad) se pasa
//! como parámetro.
//!
any_const_ptr EntCmd::GetProp(const std::string &cod) const
  {
    if(verborrea>4)
      std::clog << "EntCmd::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;

    if(cod=="sqlite")
      { return any_const_ptr(&sqlite_interpreter); }
    else if(cod=="psplot")
      { return any_const_ptr(&psplot); }
    else if(cod=="fixedWidthReader")
      { return any_const_ptr(&fw_reader); }
    any_const_ptr tmp= GetPropLocal(cod);
    if(tmp.empty())
      tmp= EntProp::GetProp(cod);
    if(tmp.empty())
      visita(this); //Si devuelve nada no le volvemos a consultar.
    return tmp; 
  }

//! @brief Devuelve un puntero al objeto propietario de ESTE.
EntCmd *EntCmd::Owner(void)
  {
    EntCmd *retval= NULL;
    EntProp *tmp= EntProp::Owner();
    if(tmp)
      retval= dynamic_cast<EntCmd *>(tmp);
    return retval;
  }

//! @brief Devuelve un puntero al objeto propietario de ESTE.
const EntCmd *EntCmd::Owner(void) const
  {
    const EntCmd *retval= NULL;
    const EntProp *tmp= EntProp::Owner();
    if(tmp)
      retval= dynamic_cast<const EntCmd *>(tmp);
    return retval;
  }

//! @brief Returns log file name.
const std::string &EntCmd::getLogFileName(void) const
  { return err_log_files.getLogFileName(); }

//! @brief Sets log file name.
void EntCmd::setLogFileName(const std::string &fname)
  {
    if(fname != "")
      err_log_files.setLogFileName(fname);
  }

//! @brief Returns err file name.
const std::string &EntCmd::getErrFileName(void) const
  { return err_log_files.getErrFileName(); }

//! @brief Sets log file name.
void EntCmd::setErrFileName(const std::string &fname)
  {
    if(fname != "")
      err_log_files.setErrFileName(fname);
  }

//! @brief Returns true if property exists.
bool EntCmd::hasPyProp(const std::string &str)
  { return (python_dict.find(str) != python_dict.end()); }

//! @brief Devuelve el objeto de Python cuyo nombre se pasa como parámetro.
//Python checks the class attributes before it calls __getattr__ so we don't have to do anything special here.
boost::python::object EntCmd::getPyProp(const std::string &str)
   {
     if(python_dict.find(str) == python_dict.end())
       {
         std::cerr << "No se encontró la propiedad: '" << str << "'" << std::endl;
         PyErr_SetString(PyExc_AttributeError, str.c_str());
         throw boost::python::error_already_set();
       }
     return python_dict[str];
   }

//! @brief Asigna al objeto de Python cuyo nombre se pasa como parámetro el valor «val».
//However, with __setattr__, python doesn't do anything with the class attributes first, it just calls __setattr__.
//Which means anything that's been defined as a class attribute won't be modified here - including things set with
//add_property(), def_readwrite(), etc.
void EntCmd::setPyProp(std::string str, boost::python::object val)
  {
    python_dict[str] = val;
  }

//! @brief Devuelve el objeto de Python que resulta de evaluar la expresión.
boost::python::object EntCmd::evalPy(boost::python::object dict,const std::string &str)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::eval(str.c_str(),main_namespace,dict);
   }


//! @brief Devuelve el objeto de Python que resulta de evaluar el bloque de código.
boost::python::object EntCmd::execPy(boost::python::object dict,const std::string &block)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::exec(block.c_str(),main_namespace,dict);
   }

//! @brief Devuelve el objeto de Python que resulta de evaluar el bloque de código.
boost::python::object EntCmd::execFilePy(boost::python::object dict,const std::string &fName)
   {
     boost::python::object main_module = boost::python::import("__main__");
     boost::python::object main_namespace = main_module.attr("__dict__");
     return boost::python::exec_file(fName.c_str(),main_namespace,dict);
   }
