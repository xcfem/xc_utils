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
//aux_any.cc

#include "aux_any.h"
#include "xc_utils/src/nucleo/EntCmd.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any_const_ptr.h"
#include <boost/any.hpp>

#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_basic/src/texto/tab_cod.h"
#include "VarTypes.h"

#include <boost/algorithm/string/trim.hpp>
#include "xc_utils/src/nucleo/InterpreteRPN.h"

const std::string str_desconocido= "desconocido";
const std::string str_empty= "empty";
const std::string str_bool= "bool";
const std::string str_int= "int";
const std::string str_long_int= "long_int";
const std::string str_vector_int= "vector_int";
const std::string str_vector_long_int= "vector_long_int";
const std::string str_vector_double= "vector_double";
const std::string str_vector_char= "vector_char";
const std::string str_vector_any= "vector_any";
const std::string str_size_t= "size_t";
const std::string str_string= "string";
const std::string str_char_ptr= "char_ptr";
const std::string str_path= "path";
const std::string str_float= "float";
const std::string str_double= "double";
const std::string str_expr_algebra= "expr_algebra";
const std::string str_m_int= "m_int";
const std::string str_m_sizet= "m_sizet";
const std::string str_m_double= "m_double";
const std::string str_matriz_expr= "matriz_expr";
const std::string str_matrizM= "matrizM";
const std::string str_matrizMExpr= "matrizMExpr";
const std::string str_matriz_FT= "matriz_FT";
const std::string str_vector2d= "vector2d";
const std::string str_pos2d= "pos2d";
const std::string str_listaPos2d= "listaPos2d";
const std::string str_polilinea2d= "polilinea2d";
const std::string str_listaPos3d= "listaPos3d";
const std::string str_Segmento2d= "segmento2d";
const std::string str_poligono2d= "poligono2d";
const std::string str_poligonoConAgujeros2d= "poligonoConAgujeros2d";
const std::string str_circulo2d= "circulo2d";
const std::string str_vector3d= "vector3d";
const std::string str_vdesliz3d= "vdesliz3d";
const std::string str_pos3d= "pos3d";
const std::string str_semiEspacio3d= "semiEspacio3d";
const std::string str_Poliedro3d= "poliedro3d";
const std::string str_Tetraedro3d= "tetraedro3d";
const std::string str_BlockPyramid= "blockPyramid";
const std::string str_sisCooRect2d3d= "sisCooRect2d3d";
const std::string str_ref2d3d= "ref2d3d";
const std::string str_Segmento3d= "segmento3d";
const std::string str_recta3d= "recta3d";
const std::string str_recta2d= "recta2d";
const std::string str_VDesliz2d= "vDesliz2d";
const std::string str_VDesliz3d= "vDesliz3d";
const std::string str_VFijo2d= "vFijo2d";
const std::string str_VFijo3d= "vFijo3d";
const std::string str_svd3d= "svd3d";
const std::string str_plano3d= "plano3d";
const std::string str_lista= "lista";
const std::string str_mapa= "mapa";
const std::string str_record= "record";
const std::string str_func_pts= "func_pts";
const std::string str_ent_cmd= "ent_cmd";
const std::string str_boost_any= "boost_any";
const std::string str_vector_boost_any= "vector_boost_any";
const std::string str_vector_size_t= "vector_size_t";

//! @brief Devuelve el tipo del operando.
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
const std::string &boost_any_tipo_operando(const boost::any &operand)
  {
    const std::string *retval= &str_desconocido;
    if(boost_any_is_empty(operand))
      retval= &str_empty;
    else if(boost_any_is_bool(operand))
      retval= &str_bool;
    else if(boost_any_is_int(operand))
      retval= &str_int;
    else if(boost_any_is_long_int(operand))
      retval= &str_long_int;
    else if(boost_any_is_size_t(operand))
      retval= &str_size_t;
    else if(boost_any_is_char_ptr(operand))
      retval= &str_char_ptr;
    else if(boost_any_is_string(operand))
      retval= &str_string;
    else if(boost_any_is_float(operand))
      retval= &str_float;
    else if(boost_any_is_double(operand))
      retval= &str_double;
    else if(boost_any_is_expr_algebra(operand))
      retval= &str_expr_algebra;
    else if(boost_any_is_m_int(operand))
      retval= &str_m_int;
    else if(boost_any_is_m_sizet(operand))
      retval= &str_m_sizet;
    else if(boost_any_is_m_double(operand))
      retval= &str_m_double;
    else if(boost_any_is_matriz_expr(operand))
      retval= &str_matriz_expr;
    else if(boost_any_is_matrizM(operand))
      retval= &str_matrizM;
    else if(boost_any_is_matrizMExpr(operand))
      retval= &str_matrizMExpr;
    else if(boost_any_is_matriz_FT(operand))
      retval= &str_matriz_FT;
    else if(boost_any_is_vector2d(operand))
      retval= &str_vector2d;
    else if(boost_any_is_vector3d(operand))
      retval= &str_vector3d;
    else if(boost_any_is_vdesliz3d(operand))
      retval= &str_vdesliz3d;
    else if(boost_any_is_svd3d(operand))
      retval= &str_svd3d;
    else if(boost_any_is_pos2d(operand))
      retval= &str_pos2d;
    else if(boost_any_is_pos3d(operand))
      retval= &str_pos3d;
    else if(boost_any_is_circulo2d(operand))
      retval= &str_circulo2d;
    else if(boost_any_is_recta2d(operand))
      retval= &str_recta2d;
    else if(boost_any_is_recta3d(operand))
      retval= &str_recta3d;
    else if(boost_any_is_plano3d(operand))
      retval= &str_plano3d;
    else if(boost_any_is_se3d(operand))
      retval= &str_semiEspacio3d;
    else if(boost_any_is_poliedro3d(operand))
      retval= &str_Poliedro3d;
    else if(boost_any_is_tetra3d(operand))
      retval= &str_Tetraedro3d;
    else if(boost_any_is_lista_pos2d(operand))
      retval= &str_listaPos2d;
    else if(boost_any_is_polilinea2d(operand))
      retval= &str_polilinea2d;
    else if(boost_any_is_lista_pos3d(operand))
      retval= &str_listaPos3d;
    else if(boost_any_is_poligono2d(operand))
      retval= &str_poligono2d;
    else if(boost_any_is_poligono_con_agujeros2d(operand))
      retval= &str_poligonoConAgujeros2d;
    else if(boost_any_is_lista(operand))
      retval= &str_lista;
    else if(boost_any_is_mapa(operand))
      retval= &str_mapa;
    else if(boost_any_is_record(operand))
      retval= &str_record;
    else if(boost_any_is_CmdFuncPorPuntos(operand))
      retval= &str_func_pts;
    else if(boost_any_is_vector_any(operand))
      retval= &str_vector_boost_any;
    else if(boost_any_is_vector_long_int(operand))
      retval= &str_vector_long_int;
    else if(boost_any_is_vector_double(operand))
      retval= &str_vector_double;
    else if(boost_any_is_vector_int(operand))
      retval= &str_vector_int;
    else if(boost_any_is_vector_char(operand))
      retval= &str_vector_char;
    else if(boost_any_is_vector_size_t(operand))
      retval= &str_vector_size_t;
    return *retval;
  }

//! @brief Devuelve verdadero si el objeto es de tipo any_const_ptr.
bool boost_any_is_any_const_ptr(const boost::any &operand)
  { return boost::any_cast<any_const_ptr>(&operand); }

const any_const_ptr &boost_any_to_any_const_ptr(const boost::any &operand)
  { return *(boost::any_cast<any_const_ptr>(&operand)); }


//! @brief Imprime el objeto any en el stream que se pasa como parámetro.
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
void boost_any_print(std::ostream &os,const boost::any &operand)
  {
    if(boost_any_is_empty(operand))
      std::cerr << "se intentó imprimir un operando vacío." << std::endl;
    else
      {
        if(boost_any_is_bool(operand))
          {
            const bool b= boost_any_to_bool(operand);
            if(b)
              os << "si";
            else
              os << "no";
          }
        else if(boost_any_is_int(operand))
          { os << boost_any_to_int(operand); }
        else if(boost_any_is_long_int(operand))
          { os << boost_any_to_long_int(operand); }
        else if(boost_any_is_vector_long_int(operand))
          {
            const std::vector<long int> &tmp= boost_any_to_vector_long_int(operand);
            os << '[';
            if(tmp.size())
              {
                std::vector<long int>::const_iterator i= tmp.begin();
                os << *i; i++;
                for(;i!=tmp.end();i++)
                  os << ',' << *i;
              }
            os << ']';
          }
        else if(boost_any_is_size_t(operand))
          { os << boost_any_to_size_t(operand); }
        else if(boost_any_is_char_ptr(operand))
          {
            os << *(boost::any_cast<const char *>(&operand));
          }
        else if(boost_any_is_string(operand))
          {
            //const std::string &nmb_locale= os.getloc().name();
            const std::string str= boost_any_to_string(operand);
            //Esto da problemas (mezcla de caracteres UTF
            // e ISO.
            //if(nmb_locale.find("UTF")!=std::string::npos)
            //  os << iso8859_1TO_utf8(str);
            //else
              os << str;
          }
        else if(boost_any_is_char(operand))
          { os << boost_any_to_char(operand); }
        else if(boost_any_is_float(operand))
          { os << boost_any_to_float(operand); }
        else if(boost_any_is_double(operand))
          { os << boost_any_to_double(operand); }
        else if(boost_any_is_long_double(operand))
          { os << boost_any_to_long_double(operand); }
        else if(boost_any_is_expr_algebra(operand))
          { os << boost_any_to_ExprAlgebra(operand); }
        else if(boost_any_is_m_int(operand))
          { os << boost_any_to_m_int(operand); }
        else if(boost_any_is_m_sizet(operand))
          { os << boost_any_to_m_sizet(operand); }
        else if(boost_any_is_m_double(operand))
          { os << boost_any_to_m_double(operand); }
        else if(boost_any_is_matriz_expr(operand))
          { os << boost_any_to_matrizExpr(operand); }
        else if(boost_any_is_matrizM(operand))
          { os << boost_any_to_matrizM(operand); }
        else if(boost_any_is_matrizMExpr(operand))
          { os << boost_any_to_matrizMExpr(operand); }
        else if(boost_any_is_matriz_FT(operand))
          { os << boost_any_to_matriz_FT(operand); }
        else if(boost_any_is_matriz_any(operand))
          { os << boost_any_to_matriz_any(operand); }
        else if(boost_any_is_vector2d(operand))
          { os << boost_any_to_vector2d(operand); }
        else if(boost_any_is_vector3d(operand))
          { os << boost_any_to_vector3d(operand); }
        else if(boost_any_is_vdesliz3d(operand))
          { os << boost_any_to_vdesliz3d(operand); }
        else if(boost_any_is_svd3d(operand))
          { os << boost_any_to_svd3d(operand); }
        else if(boost_any_is_pos2d(operand))
          { os << boost_any_to_pos2d(operand); }
        else if(boost_any_is_pos3d(operand))
          { os << boost_any_to_pos3d(operand); }
        else if(boost_any_is_recta2d(operand))
          { os << boost_any_to_recta2d(operand); }
        else if(boost_any_is_poligono2d(operand))
          { os << boost_any_to_poligono2d(operand); }
        else if(boost_any_is_poligono_con_agujeros2d(operand))
          { os << boost_any_to_poligono_con_agujeros2d(operand); }
        else if(boost_any_is_circulo2d(operand))
          { os << boost_any_to_circulo2d(operand); }
        else if(boost_any_is_recta3d(operand))
          { os << boost_any_to_recta3d(operand); }
        else if(boost_any_is_lista_pos2d(operand))
          { os << boost_any_to_lista_pos2d(operand); }
        else if(boost_any_is_polilinea2d(operand))
          { os << boost_any_to_polilinea2d(operand); }
        else if(boost_any_is_lista_pos3d(operand))
          { os << boost_any_to_lista_pos3d(operand); }
        else if(boost_any_is_poliedro3d(operand))
          { os << boost_any_to_poliedro3d(operand); }
        else if(boost_any_is_tetra3d(operand))
          { os << boost_any_to_tetra3d(operand); }
        else if(boost_any_is_ref2d3d(operand))
          { os << boost_any_to_ref2d3d(operand); }
        else if(boost_any_is_sisCooRect2d3d(operand))
          { os << boost_any_to_sisCooRect2d3d(operand); }
        else if(boost_any_is_blockPyramid(operand))
          { os << boost_any_to_blockPyramid(operand); }
        else if(boost_any_is_lista(operand))
          { os << boost_any_to_lista(operand); }
        else if(boost_any_is_record(operand))
          { os << boost_any_to_record(operand); }
        else if(boost_any_is_CmdFuncPorPuntos(operand))
          { os << boost_any_to_CmdFuncPorPuntos(operand); }
        else if(boost_any_is_vector_any(operand))
          {
	    const std::vector<boost::any> &tmp= boost_any_to_vector_any(operand);
            if(!tmp.empty())
              {
                std::vector<boost::any>::const_iterator i= tmp.begin();
                os << '[';
                boost_any_print(os,*i);
                i++;
                for(;i!=tmp.end();i++)
                  {
	        os << ',';
                    boost_any_print(os,*i);
                  }
                os << ']';
	      }
          }
        else if(boost_any_is_ent_cmd_ptr(operand))
          { os << boost_any_to_ent_cmd_ptr(operand).getPtr(); }
        else if(boost_any_is_any_const_ptr(operand))
          {
            const_ptr_print(os,boost_any_to_any_const_ptr(operand));
          }
        else
          std::cerr << "print(boost_any): No se ha definido la operación print para el objeto de tipo: "
                    << operand.type().name() << " que se pasa como parámetro." << std::endl;
      }
  }

//! @brief Convierte el argumento y se lo asigna a la propiedad prp.
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
bool convert_arg(boost::any &prp,const boost::any &arg,EntCmd *owner)
  {
    bool retval= true;
    if(boost_any_is_string(prp))
      prp= convert_to_string(arg);
    else if(boost_any_is_path(prp))
      prp= convert_to_path(arg);
    else if(boost_any_is_double(prp))
      prp= convert_to_double(arg);
    else if(boost_any_is_expr_algebra(prp))
      prp= convert_to_ExprAlgebra(arg);
    else if(boost_any_is_vector_any(prp))
      prp= convert_to_vector_any(arg);
    else if(boost_any_is_pos2d(prp))
      prp= convert_to_pos2d(arg);
    else if(boost_any_is_lista_pos2d(prp))
      prp= convert_to_lista_pos2d(arg);
    else if(boost_any_is_pos3d(prp))
      prp= convert_to_pos3d(arg);
    else if(boost_any_is_lista_pos3d(prp))
      prp= convert_to_lista_pos3d(arg);
    else if(boost_any_is_poliedro3d(prp))
      prp= convert_to_poliedro3d(arg);
    else if(boost_any_is_tetra3d(prp))
      prp= convert_to_tetra3d(arg);
    else if(boost_any_is_sisCooRect2d3d(prp))
      prp= convert_to_sisCooRect2d3d(arg);
    else if(boost_any_is_ref2d3d(prp))
      prp= convert_to_ref2d3d(arg);
    else if(boost_any_is_blockPyramid(prp))
      prp= convert_to_blockPyramid(arg);
    else if(boost_any_is_vector2d(prp))
      prp= convert_to_vector2d(arg);
    else if(boost_any_is_vector3d(prp))
      prp= convert_to_vector3d(arg);
    else if(boost_any_is_vdesliz3d(prp))
      prp= convert_to_vdesliz3d(arg);
    else if(boost_any_is_svd3d(prp))
      prp= convert_to_svd3d(arg);
    else if(boost_any_is_recta2d(prp))
      prp= convert_to_recta2d(arg);
    else if(boost_any_is_recta3d(prp))
      prp= convert_to_recta3d(arg);
    else if(boost_any_is_polilinea2d(prp))
      prp= convert_to_polilinea2d(arg);
    else if(boost_any_is_poligono2d(prp))
      prp= convert_to_poligono2d(arg);
    else if(boost_any_is_poligono_con_agujeros2d(prp))
      prp= convert_to_poligono_con_agujeros2d(arg);
    else if(boost_any_is_circulo2d(prp))
      prp= convert_to_circulo2d(arg);
    else if(boost_any_is_lista(prp))
      {
        Lista tmp= convert_to_lista(arg);
        tmp.set_owner(owner);
        prp= tmp;
      }
    else if(boost_any_is_record(prp))
      {
        Record tmp= convert_to_record(arg);
        tmp.set_owner(owner);
        prp= tmp;
      }
    else if(boost_any_is_number(prp))
      prp= boost_any_number_to_double(arg); //number_to_double(arg);
    else
      retval= false;
    return retval;
  }

//! @brief Asigna el propietario al objeto data (se emplea en MapParam::SetOwner).
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
void set_owner(boost::any *data, EntProp *owr)
  {
    if(Lista *ptr= boost::any_cast<Lista>(data))
      { ptr->set_owner(owr); }
    else if(Path *ptr_path= boost::any_cast<Path>(data))
      { ptr_path->set_owner(owr); }
    else if(CmdFuncPorPuntos *ptr_f= boost::any_cast<CmdFuncPorPuntos>(data))
      { ptr_f->set_owner(owr); }
    else if(MySqlConnection *ptr_dbconn= boost::any_cast<MySqlConnection>(data))
      { ptr_dbconn->set_owner(owr); }
    else if(CmdTimer *ptr_timer= boost::any_cast<CmdTimer>(data))
      { ptr_timer->set_owner(owr); }
    else if(Record *ptr_record= boost::any_cast<Record>(data))
      { ptr_record->set_owner(owr); }
    else if(BloqueBase *ptr_bloque= boost::any_cast<BloqueBase>(data))
      { ptr_bloque->set_owner(owr); }
    else if(BloqueSub *ptr_bloque_sub= boost::any_cast<BloqueSub>(data))
      { ptr_bloque_sub->set_owner(owr); }
    else if(Pos2d *ptr_pos2d= boost::any_cast<Pos2d>(data))
      { ptr_pos2d->set_owner(owr); }
    else if(Vector2d *ptr_vector2d= boost::any_cast<Vector2d>(data))
      { ptr_vector2d->set_owner(owr); }
    else if(Segmento2d *ptr_segmento2d= boost::any_cast<Segmento2d>(data))
      { ptr_segmento2d->set_owner(owr); }
    else if(Poligono2d *ptr_plg2d= boost::any_cast<Poligono2d>(data))
      { ptr_plg2d->set_owner(owr); }
    else if(PoligonoConAgujeros2d *ptr_poligonoConAgujeros2d= boost::any_cast<PoligonoConAgujeros2d>(data))
      { ptr_poligonoConAgujeros2d->set_owner(owr); }
    else if(Circulo2d *ptr_circulo2d= boost::any_cast<Circulo2d>(data))
      { ptr_circulo2d->set_owner(owr); }
    else if(ListaPos2d *ptr_lpos2d= boost::any_cast<ListaPos2d>(data))
      { ptr_lpos2d->set_owner(owr); }
    else if(Polilinea2d *ptr_polilinea2d= boost::any_cast<Polilinea2d>(data))
      { ptr_polilinea2d->set_owner(owr); }
    else if(ListaPos3d *ptr_lpos3d= boost::any_cast<ListaPos3d>(data))
      { ptr_lpos3d->set_owner(owr); }
    else if(Pos3d *ptr_pos3d= boost::any_cast<Pos3d>(data))
      { ptr_pos3d->set_owner(owr); }
    else if(Vector3d *ptr_vector3d= boost::any_cast<Vector3d>(data))
      { ptr_vector3d->set_owner(owr); }
    else if(Segmento3d *ptr_segmento3d= boost::any_cast<Segmento3d>(data))
      { ptr_segmento3d->set_owner(owr); }
    else if(Recta3d *ptr_recta3d= boost::any_cast<Recta3d>(data))
      { ptr_recta3d->set_owner(owr); }
    else if(Recta2d *ptr_recta2d= boost::any_cast<Recta2d>(data))
      { ptr_recta2d->set_owner(owr); }
    else if(Plano3d *ptr_plano3d= boost::any_cast<Plano3d>(data))
      { ptr_plano3d->set_owner(owr); }
    else if(SVD3d *ptr_svd3d= boost::any_cast<SVD3d>(data))
      { ptr_svd3d->set_owner(owr); }
  }

//! @brief obtiene una propiedad del objeto 'a'.
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
bool opera_rcl(const boost::any &a,const boost::any &b)
  {
    InterpreteRPN::PilaParciales &pila_parciales= InterpreteRPN::Pila();
    //En esta función llamamos a EntProp::GetProp en lugar de EntProp::Recall porque se trata de
    //recuperar una propiedad del objeto 'a', por lo que no debemos buscar el valor de la propiedad
    //en la pila de llamadas ni en otros objetos distintintos de 'a' o sus ancestros.
    bool error= false;
    if(boost_any_is_string(b))
      {
        const std::string cod=  boost::trim_copy_if(boost_any_to_string(b),boost::is_any_of("@"));
        if(boost_any_is_lista(a))
          {
            const Lista &lst= boost_any_to_lista(a);
            const any_const_ptr ptr= lst.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_path(a))
          {
            const Path &pth= boost_any_to_path(a);

            const any_const_ptr ptr= pth.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_record(a))
          {
            const Record &rec= boost_any_to_record(a);
            const any_const_ptr ptr= rec.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_CmdFuncPorPuntos(a))
          {
            const CmdFuncPorPuntos &fp= boost_any_to_CmdFuncPorPuntos(a);

            const any_const_ptr ptr= fp.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_pos2d(a))
          {
            const Pos2d &v2d= boost_any_to_pos2d(a);

            const any_const_ptr ptr= v2d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_pos3d(a))
          {
            const Pos3d &p3d= boost_any_to_pos3d(a);

            const any_const_ptr ptr= p3d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_vector2d(a))
          {
            const Vector2d &v2d= boost_any_to_vector2d(a);

            const any_const_ptr ptr= v2d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_segmento2d(a))
          {
            const Segmento2d &s2d= boost_any_to_segmento2d(a);

            const any_const_ptr ptr= s2d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_vector3d(a))
          {
            const Vector3d &v3d= boost_any_to_vector3d(a);

            const any_const_ptr ptr= v3d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_segmento3d(a))
          {
            const Segmento3d &s3d= boost_any_to_segmento3d(a);

            const any_const_ptr ptr= s3d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_vdesliz2d(a))
          {
            const VDesliz2d &vd2d= boost_any_to_vdesliz2d(a);

            const any_const_ptr ptr= vd2d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_vdesliz3d(a))
          {
            const VDesliz3d &vd3d= boost_any_to_vdesliz3d(a);

            const any_const_ptr ptr= vd3d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_vfijo2d(a))
          {
            const VFijo2d &vd2d= boost_any_to_vfijo2d(a);

            const any_const_ptr ptr= vd2d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_vfijo3d(a))
          {
            const VFijo3d &vd3d= boost_any_to_vfijo3d(a);

            const any_const_ptr ptr= vd3d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_svd3d(a))
          {
            const SVD3d &svd3d= boost_any_to_svd3d(a);

            const any_const_ptr ptr= svd3d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_circulo2d(a))
          {
            const Circulo2d &c2d= boost_any_to_circulo2d(a);

            const any_const_ptr ptr= c2d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_lista_pos2d(a))
          {
            const ListaPos2d &l2d= boost_any_to_lista_pos2d(a);

            const any_const_ptr ptr= l2d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_lista_pos3d(a))
          {
            const ListaPos3d &l3d= boost_any_to_lista_pos3d(a);

            const any_const_ptr ptr= l3d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_recta3d(a))
          {
            const Recta3d &r3d= boost_any_to_recta3d(a);

            const any_const_ptr ptr= r3d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_recta2d(a))
          {
            const Recta2d &r2d= boost_any_to_recta2d(a);

            const any_const_ptr ptr= r2d.GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else if(boost_any_is_ent_cmd_ptr(a))
          {
            const EntCmd *ent= boost_any_to_ent_cmd_ptr(a).getPtr();
            const any_const_ptr ptr= ent->GetProp(cod);
            if(!const_ptr_is_empty(ptr)) //Tiene chicha.
              pila_parciales.push(convert_to_boost_any(ptr));
          }
        else
          {
            std::cerr << "InterpreteRPN::OperaRcl; no se supo tratar al objeto: ";
            boost_any_print(std::cerr,a);
            std::cerr << " de tipo: " << boost_any_tipo_operando(a) << std::endl;
            error= true;
          }
      }
    else
      {
        std::cerr << "InterpreteRPN::OperaRcl; error, se esperaba un objeto de tipo string."
                  << " se obtuvo uno de tipo: " << boost_any_tipo_operando(b) << std::endl;
        error= true;
      }
    return error;
  }


//! @brief Devuelve un apuntador a EntCmd si le es posible.
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
EntCmd *boost_any_entcmd_cast(boost::any &data)
  {
    EntCmd *ptr_ent= nullptr;
    if(Lista *ptr= boost::any_cast<Lista>(&data))
      ptr_ent= ptr;
    else if(Mapa *ptr= boost::any_cast<Mapa>(&data))
      ptr_ent= ptr;
    else if(Path *ptr_path= boost::any_cast<Path>(&data))
      ptr_ent= ptr_path;
    else if(CmdFuncPorPuntos *ptr_f= boost::any_cast<CmdFuncPorPuntos>(&data))
      ptr_ent= ptr_f;
    else if(Poligono2d *ptr_pol2d= boost::any_cast<Poligono2d>(&data))
      ptr_ent= ptr_pol2d;
    else if(PoligonoConAgujeros2d *ptr_poligonoConAgujeros2d= boost::any_cast<PoligonoConAgujeros2d>(&data))
      ptr_ent= ptr_poligonoConAgujeros2d;
    else if(Polilinea2d *ptr_polilinea2d= boost::any_cast<Polilinea2d>(&data))
      ptr_ent= ptr_polilinea2d;
    else if(ListaPos2d *ptr_lpos2d= boost::any_cast<ListaPos2d>(&data))
      ptr_ent= ptr_lpos2d;
    else if(ListaPos3d *ptr_lpos3d= boost::any_cast<ListaPos3d>(&data))
      ptr_ent= ptr_lpos3d;
    else if(Pos2d *ptr_pos2d= boost::any_cast<Pos2d>(&data))
      ptr_ent= ptr_pos2d;
    else if(Vector2d *ptr_vector2d= boost::any_cast<Vector2d>(&data))
      ptr_ent= ptr_vector2d;
    else if(Segmento2d *ptr_segmento2d= boost::any_cast<Segmento2d>(&data))
      ptr_ent= ptr_segmento2d;
    else if(Pos3d *ptr_pos3d= boost::any_cast<Pos3d>(&data))
      ptr_ent= ptr_pos3d;
    else if(VDesliz2d *ptr_vdesliz2d= boost::any_cast<VDesliz2d>(&data))
      ptr_ent= ptr_vdesliz2d;
    else if(VDesliz3d *ptr_vdesliz3d= boost::any_cast<VDesliz3d>(&data))
      ptr_ent= ptr_vdesliz3d;
    else if(VFijo2d *ptr_vfijo2d= boost::any_cast<VFijo2d>(&data))
      ptr_ent= ptr_vfijo2d;
    else if(VFijo3d *ptr_vfijo3d= boost::any_cast<VFijo3d>(&data))
      ptr_ent= ptr_vfijo3d;
    else if(Vector3d *ptr_vector3d= boost::any_cast<Vector3d>(&data))
      ptr_ent= ptr_vector3d;
    else if(Segmento3d *ptr_segmento3d= boost::any_cast<Segmento3d>(&data))
      ptr_ent= ptr_segmento3d;
    else if(SVD3d *ptr_svd3d= boost::any_cast<SVD3d>(&data))
      ptr_ent= ptr_svd3d;
    else if(Circulo2d *ptr_circulo2d= boost::any_cast<Circulo2d>(&data))
      ptr_ent= ptr_circulo2d;
    else if(Recta3d *ptr_recta3d= boost::any_cast<Recta3d>(&data))
      ptr_ent= ptr_recta3d;
    else if(Recta2d *ptr_recta2d= boost::any_cast<Recta2d>(&data))
      ptr_ent= ptr_recta2d;
    else if(Plano3d *ptr_plano3d= boost::any_cast<Plano3d>(&data))
      ptr_ent= ptr_plano3d;
    else if(SemiEspacio3d *ptr_se3d= boost::any_cast<SemiEspacio3d>(&data))
      ptr_ent= ptr_se3d;
    else if(Tetraedro3d *ptr_tetra3d= boost::any_cast<Tetraedro3d>(&data))
      ptr_ent= ptr_tetra3d;
    else if(Poliedro3d *ptr_poliedro3d= boost::any_cast<Poliedro3d>(&data))
      ptr_ent= ptr_poliedro3d;
    else if(BlockPyramid *ptr_blockPyramid= boost::any_cast<BlockPyramid>(&data))
      ptr_ent= ptr_blockPyramid;
    else if(SisCooRect2d3d *ptr_blockSisCoo= boost::any_cast<SisCooRect2d3d>(&data))
      ptr_ent= ptr_blockSisCoo;
    else if(Ref2d3d *ptr_blockRef= boost::any_cast<Ref2d3d>(&data))
      ptr_ent= ptr_blockRef;
    else if(MySqlConnection *ptr_dbconn= boost::any_cast<MySqlConnection>(&data))
      ptr_ent = ptr_dbconn;
    else if(CmdTimer *ptr_timer= boost::any_cast<CmdTimer>(&data))
      ptr_ent= ptr_timer;
    else if(Record *ptr_record= boost::any_cast<Record>(&data))
      ptr_ent= ptr_record;
    else if(BloqueBase *ptr_bloque= boost::any_cast<BloqueBase>(&data))
      ptr_ent= ptr_bloque;
    else if(BloqueSub *ptr_bloque_sub= boost::any_cast<BloqueSub>(&data))
      ptr_ent= ptr_bloque_sub;
    return ptr_ent;
  }

//! @brief Crea un objeto boost::any a partir de:
//! @param tipo: Tipo del valor a crear (string, double,...).
//! @param valor: Cadena de caracteres de cuya interpretación se obtendrá el valor del objeto.
//! @def_args: Definición de los argumentos para los objetos de tipo función o subrutina.
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
boost::any convert_to_type(const std::string &tipo,const boost::any &obj)
  {
    boost::any retval;
    if(tipo=="string")
      retval= convert_to_string(obj);
    else if(tipo=="path")
      retval= Path(convert_to_string(obj));
    else if((tipo=="double") || (tipo=="float"))
      retval= convert_to_double(obj);
    else if((tipo=="expr") || (tipo=="expr_algebra"))
      retval= convert_to_ExprAlgebra(obj);
    else if(tipo=="vector")
      retval= convert_to_vector_any(obj);
    else if(tipo=="m_double")
      retval= convert_to_m_double(obj);
    else if(tipo=="m_string")
      retval= convert_to_m_string(obj);
    else if(tipo=="vector_boost_any")
      retval= convert_to_vector_any(obj);
    else if(tipo=="matriz")
      retval= convert_to_matriz_any(obj);
    else if((tipo=="map") || (tipo=="mapa"))
      retval= convert_to_mapa(obj);
    else if(tipo=="func_pts")
      retval= convert_to_CmdFuncPorPuntos(obj);
    else if(tipo=="pos2d")
      retval= convert_to_pos2d(obj);
    else if(tipo=="vector2d")
      retval= convert_to_vector2d(obj);
    else if(tipo=="segmento2d")
      retval= convert_to_segmento2d(obj);
    else if(tipo=="poligono2d")
      retval= convert_to_poligono2d(obj);
    else if(tipo=="poligono_con_agujeros2d")
      retval= convert_to_poligono_con_agujeros2d(obj);
    else if(tipo=="listaPos2d")
      retval= convert_to_lista_pos2d(obj);
    else if(tipo=="polilinea2d")
      retval= convert_to_polilinea2d(obj);
    else if(tipo=="listaPos3d")
      retval= convert_to_lista_pos3d(obj);
    else if(tipo=="pos3d")
      retval= convert_to_pos3d(obj);
    else if(tipo=="vector3d")
      retval= convert_to_vector3d(obj);
    else if(tipo=="segmento3d")
      retval= convert_to_segmento3d(obj);
    else if(tipo=="vdesliz2d")
      retval= convert_to_vdesliz2d(obj);
    else if(tipo=="vdesliz3d")
      retval= convert_to_vdesliz3d(obj);
    else if(tipo=="vfijo2d")
      retval= convert_to_vfijo2d(obj);
    else if(tipo=="vfijo3d")
      retval= convert_to_vfijo3d(obj);
    else if(tipo=="svd3d")
      retval= convert_to_svd3d(obj);
    else if(tipo=="recta2d")
      retval= convert_to_recta2d(obj);
    else if(tipo=="recta3d")
      retval= convert_to_recta3d(obj);
    else if(tipo=="circulo2d")
      retval= convert_to_circulo2d(obj);
    else if(tipo=="plano3d")
      retval= convert_to_plano3d(obj);
    else if(tipo=="semiEspacio3d")
      retval= convert_to_se3d(obj);
    else if(tipo=="tetraedro3d")
      retval= convert_to_tetra3d(obj);
    else if(tipo=="blockPyramid")
      retval= convert_to_blockPyramid(obj);
    else if(tipo=="sisCooRect2d3d")
      retval= convert_to_sisCooRect2d3d(obj);
    else if(tipo=="ref2d3d")
      retval= convert_to_ref2d3d(obj);
    else if(tipo=="poliedro3d")
      retval= convert_to_poliedro3d(obj);
    else if(tipo=="mySqlConn")
      retval= MySqlConnection(convert_to_int(obj));
    else
      std::cerr << "convert_to_type; no se reconoce el tipo de parámetro: '" << tipo << "'.\n";
    return retval;
  }

//! @brief Crea un objeto boost::any a partir de:
//! @param tipo: Tipo del valor a crear (string, double,...).
//! @param valor: Cadena de caracteres de cuya interpretación se obtendrá el valor del objeto.
//! @def_args: Definición de los argumentos para los objetos de tipo función o subrutina.
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
boost::any interpreta_string_to_boost_any(EntCmd &ent,const std::string &tipo,const std::string &valor,const std::string &def_args,const std::string &nombre)
  {
    boost::any retval;
    if(tipo=="bloque")
      retval= BloqueBase(&ent,nombre,valor);
    else if(tipo=="sub")
      retval= BloqueSub(&ent,nombre,valor,def_args);
    else if(tipo=="func")
      retval= BloqueFunc(&ent,nombre,valor,def_args);
    else if(tipo=="timer")
      retval= CmdTimer(ent.interpretaInt(valor));
    else if(tipo=="record")
      retval= Record(&ent,valor);
    else if((tipo=="list") || (tipo=="lista"))
      retval= Lista(&ent,valor);
    else
      {
        retval= convert_to_type(tipo,ent.interpretaAny(valor));
        EntCmd *e= boost_any_entcmd_cast(retval);
        if(e)
          e->set_owner(&ent);
      }
    return retval;
  }

//! @brief Devuelve el tipo del operando.
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
const std::string &const_ptr_tipo_operando(const any_const_ptr &operand)
  {
    const std::string *retval= &str_desconocido;
    if(const_ptr_is_empty(operand))
      retval= &str_empty;
    else if(is_const_ptr_to_bool(operand))
      retval= &str_bool;
    else if(is_const_ptr_to_int(operand))
      retval= &str_int;
    else if(is_const_ptr_to_vector_long_int(operand))
      retval= &str_vector_long_int;
    else if(is_const_ptr_to_vector_any(operand))
      retval= &str_vector_any;
    else if(is_const_ptr_to_size_t(operand))
      retval= &str_size_t;
//     else if(is_const_ptr_to_char_ptr(operand))
//       retval= &str_char_ptr;
    else if(is_const_ptr_to_string(operand))
      retval= &str_string;
    else if(is_const_ptr_to_path(operand))
      retval= &str_path;
    else if(is_const_ptr_to_float(operand))
      retval= &str_float;
    else if(is_const_ptr_to_double(operand))
      retval= &str_double;
    else if(is_const_ptr_to_expr_algebra(operand))
      retval= &str_expr_algebra;
    else if(is_const_ptr_to_m_int(operand))
      retval= &str_m_int;
    else if(is_const_ptr_to_m_sizet(operand))
      retval= &str_m_sizet;
    else if(is_const_ptr_to_m_double(operand))
      retval= &str_m_double;
    else if(is_const_ptr_to_matriz_expr(operand))
      retval= &str_matriz_expr;
    else if(is_const_ptr_to_matrizM(operand))
      retval= &str_matrizM;
    else if(is_const_ptr_to_matrizMExpr(operand))
      retval= &str_matrizMExpr;
    else if(is_const_ptr_to_matriz_FT(operand))
      retval= &str_matriz_FT;
    else if(is_const_ptr_to_vector2d(operand))
      retval= &str_vector2d;
    else if(is_const_ptr_to_pos2d(operand))
      retval= &str_pos2d;
    else if(is_const_ptr_to_polilinea2d(operand))
      retval= &str_polilinea2d;
    else if(is_const_ptr_to_lista_pos2d(operand))
      retval= &str_listaPos2d;
    else if(is_const_ptr_to_lista_pos3d(operand))
      retval= &str_listaPos3d;
    else if(is_const_ptr_to_segmento2d(operand))
      retval= &str_Segmento2d;
    else if(is_const_ptr_to_poligono2d(operand))
      retval= &str_poligono2d;
    else if(is_const_ptr_to_poligono_con_agujeros2d(operand))
      retval= &str_poligonoConAgujeros2d;
    else if(is_const_ptr_to_circulo2d(operand))
      retval= &str_circulo2d;
    else if(is_const_ptr_to_vector3d(operand))
      retval= &str_vector3d;
    else if(is_const_ptr_to_pos3d(operand))
      retval= &str_pos3d;
    else if(is_const_ptr_to_semiEspacio3d(operand))
      retval= &str_semiEspacio3d;
    else if(is_const_ptr_to_poliedro3d(operand))
      retval= &str_Poliedro3d;
    else if(is_const_ptr_to_tetraedro3d(operand))
      retval= &str_Tetraedro3d;
    else if(is_const_ptr_to_blockPyramid(operand))
      retval= &str_BlockPyramid;
    else if(is_const_ptr_to_sisCooRect2d3d(operand))
      retval= &str_sisCooRect2d3d;
    else if(is_const_ptr_to_ref2d3d(operand))
      retval= &str_ref2d3d;
    else if(is_const_ptr_to_segmento3d(operand))
      retval= &str_Segmento3d;
    else if(is_const_ptr_to_recta3d(operand))
      retval= &str_recta3d;
    else if(is_const_ptr_to_recta2d(operand))
      retval= &str_recta2d;
    else if(is_const_ptr_to_vdesliz2d(operand))
      retval= &str_VDesliz2d;
    else if(is_const_ptr_to_vdesliz3d(operand))
      retval= &str_VDesliz3d;
    else if(is_const_ptr_to_vfijo2d(operand))
      retval= &str_VFijo2d;
    else if(is_const_ptr_to_vfijo3d(operand))
      retval= &str_VFijo3d;
    else if(is_const_ptr_to_svd3d(operand))
      retval= &str_svd3d;
    else if(is_const_ptr_to_plano3d(operand))
      retval= &str_plano3d;
    else if(is_const_ptr_to_lista(operand))
      retval= &str_lista;
    else if(is_const_ptr_to_CmdFuncPorPuntos(operand))
      retval= &str_func_pts;
    else if(is_const_ptr_to_ent_cmd(operand))
      retval= &str_ent_cmd;
    else if(is_const_ptr_to_boost_any(operand))
      retval= &str_boost_any;
    return *retval;
  }

//! @brief Imprime el objeto any en el stream que se pasa como parámetro.
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
void const_ptr_print(std::ostream &os,const any_const_ptr &operand)
  {
    if(const_ptr_is_empty(operand))
      return;
    else if(is_const_ptr_to_any_const_ptr(operand))
      {
	std::cerr << "objeto any_const_ptr anidado." << std::endl;
      }
    else if(is_const_ptr_to_bool(operand))
      {
        const bool b= deref_to_bool(operand);
        if(b)
          os << "si";
        else
          os << "no";
	return;
      }
    else if(is_const_ptr_to_int(operand))
      {
        os << deref_to_int(operand);
        return;
      }
    else if(is_const_ptr_to_vector_long_int(operand))
      {
        const std::vector<long int> &tmp= deref_to_vector_long_int(operand);
        os << '[';
        if(tmp.size())
          {
            std::vector<long int>::const_iterator i= tmp.begin();
            os << *i; i++;
            for(;i!=tmp.end();i++)
              os << ',' << *i;
          }
        os << ']';
        return;
      }
    else if(is_const_ptr_to_vector_any(operand))
      {
        const std::vector<boost::any> &tmp= deref_to_vector_any(operand);
        os << '[';
        if(tmp.size())
          {
            std::vector<boost::any>::const_iterator i= tmp.begin();
            os << *i; i++;
            for(;i!=tmp.end();i++)
              os << ',' << *i;
          }
        os << ']';
        return;
      }
    else if(is_const_ptr_to_size_t(operand))
      {
        os << deref_to_size_t(operand);
        return;
      }
//     else if(is_const_ptr_to_char_ptr(operand))
//       {
//         os << *(any_const_ptr_cast<const char *>(operand));
//         return;
//       }
    else if(is_const_ptr_to_string(operand))
      {
        os << deref_to_string(operand);
        return;
      }
    else if(is_const_ptr_to_float(operand))
      {
        os << deref_to_float(operand);
        return;
      }
    else if(is_const_ptr_to_double(operand))
      {
        os << deref_to_double(operand);
        return;
      }
    if(is_const_ptr_to_geom_FT(operand))
      {
	os << deref_to_geom_FT(operand);
        return;
      }
    else if(is_const_ptr_to_expr_algebra(operand))
      {
        os << deref_to_ExprAlgebra(operand);
        return;
      }
    else if(is_const_ptr_to_m_int(operand))
      {
        os << deref_to_m_int(operand);
        return;
      }
    else if(is_const_ptr_to_m_sizet(operand))
      {
        os << deref_to_m_sizet(operand);
        return;
      }
    else if(is_const_ptr_to_m_double(operand))
      {
        os << deref_to_m_double(operand);
        return;
      }
    else if(is_const_ptr_to_matriz_expr(operand))
      {
        os << deref_to_matrizExpr(operand);
        return;
      }
    else if(is_const_ptr_to_matrizM(operand))
      {
        os << deref_to_matrizM(operand);
        return;
      }
    else if(is_const_ptr_to_matrizMExpr(operand))
      {
        os << deref_to_matrizMExpr(operand);
        return;
      }
    else if(is_const_ptr_to_matriz_FT(operand))
      {
        os << deref_to_matriz_FT(operand);
        return;
      }
    else if(is_const_ptr_to_pos2d(operand))
      {
	os << deref_to_pos2d(operand);
        return;
      }
    else if(is_const_ptr_to_pos3d(operand))
      {
	os << deref_to_pos3d(operand);
        return;
      }
    else if(is_const_ptr_to_lista_pos2d(operand))
      {
        os << deref_to_lista_pos2d(operand);
        return;
      }
    else if(is_const_ptr_to_polilinea2d(operand))
      {
        os << deref_to_polilinea2d(operand);
        return;
      }
    else if(is_const_ptr_to_lista_pos3d(operand))
      {
        os << deref_to_lista_pos3d(operand);
        return;
      }
    else if(is_const_ptr_to_vector2d(operand))
      {
        os << deref_to_vector2d(operand);
        return;
      }
    else if(is_const_ptr_to_segmento2d(operand))
      {
        os << deref_to_segmento2d(operand);
        return;
      }
    else if(is_const_ptr_to_vector3d(operand))
      {
        os << deref_to_vector3d(operand);
        return;
      }
    else if(is_const_ptr_to_vdesliz2d(operand))
      {
        os << deref_to_vdesliz2d(operand);
        return;
      }
    else if(is_const_ptr_to_vdesliz3d(operand))
      {
        os << deref_to_vdesliz3d(operand);
        return;
      }
    else if(is_const_ptr_to_vfijo2d(operand))
      {
        os << deref_to_vfijo2d(operand);
        return;
      }
    else if(is_const_ptr_to_vfijo3d(operand))
      {
        os << deref_to_vfijo3d(operand);
        return;
      }
    else if(is_const_ptr_to_svd3d(operand))
      {
        os << deref_to_svd3d(operand);
        return;
      }
    else if(is_const_ptr_to_poligono2d(operand))
      {
        os << deref_to_poligono2d(operand);
        return;
      }
    else if(is_const_ptr_to_poligono_con_agujeros2d(operand))
      {
        os << deref_to_poligono_con_agujeros2d(operand);
        return;
      }
    else if(is_const_ptr_to_circulo2d(operand))
      {
        os << deref_to_circulo2d(operand);
        return;
      }
    else if(is_const_ptr_to_recta3d(operand))
      {
        os << deref_to_recta3d(operand);
        return;
      }
    else if(is_const_ptr_to_recta2d(operand))
      {
        os << deref_to_recta2d(operand);
        return;
      }
    else if(is_const_ptr_to_plano3d(operand))
      {
        os << deref_to_plano3d(operand);
        return;
      }
    else if(is_const_ptr_to_semiEspacio3d(operand))
      {
        os << deref_to_semiEspacio3d(operand);
        return;
      }
    else if(is_const_ptr_to_poliedro3d(operand))
      {
        os << deref_to_poliedro3d(operand);
        return;
      }
    else if(is_const_ptr_to_tetraedro3d(operand))
      {
        os << deref_to_tetraedro3d(operand);
        return;
      }
    else if(is_const_ptr_to_sisCooRect2d3d(operand))
      {
        os << deref_to_sisCooRect2d3d(operand);
        return;
      }
    else if(is_const_ptr_to_ref2d3d(operand))
      {
        os << deref_to_ref2d3d(operand);
        return;
      }
    else if(is_const_ptr_to_blockPyramid(operand))
      {
        os << deref_to_blockPyramid(operand);
        return;
      }
    else if(is_const_ptr_to_lista(operand))
      {
        os << deref_to_lista(operand);
        return;
      }
    else if(is_const_ptr_to_CmdFuncPorPuntos(operand))
      {
        os << deref_to_CmdFuncPorPuntos(operand);
        return;
      }
    else if(is_const_ptr_to_ent_cmd(operand))
      {
        os << deref_to_ent_cmd(operand);
        return;
      }
    else if(is_const_ptr_to_boost_any(operand))
      {
        boost_any_print(os,deref_to_boost_any(operand));
        return;
      }
    std::cerr << "print(any_const_ptr): No se ha definido la operación print para el objeto de tipo: "
              << operand.type().name() << " que se pasa como parámetro." << std::endl;
  }

//! @brief Devuelve verdadero si el objeto es de tipo boost::any.
bool is_const_ptr_to_boost_any(const any_const_ptr &operand)
  {
    if(operand.empty())
      return false;
    else
      return is_type<boost::any>(operand);
  }

//! @brief Devuelve una referencia a boost::any.
const boost::any &deref_to_boost_any(const any_const_ptr &operand)
  { return *(any_const_ptr_cast<boost::any>(operand)); }

//! Convierte el operando en boost::any
//! INTERPRETE Para que un tipo de variable pueda
//! intervenir en expresiones debe tratarse aquí.
const boost::any &convert_to_boost_any(const any_const_ptr &operand)
  {
    static boost::any retval;
    retval= boost::any();
    if(const_ptr_is_empty(operand))
      return retval;
    else if(is_const_ptr_to_any_const_ptr(operand))
      {
	std::cerr << "objeto any_const_ptr anidado." << std::endl;
        return retval;
      }
    else if(is_const_ptr_to_bool(operand))
      retval= boost::any(deref_to_bool(operand));
    else if(is_const_ptr_to_int(operand))
      retval= boost::any(deref_to_int(operand));
    else if(is_const_ptr_to_long_int(operand))
      retval= boost::any(deref_to_long_int(operand));
    else if(is_const_ptr_to_size_t(operand))
      retval= boost::any(deref_to_size_t(operand));
    else if(is_const_ptr_to_string(operand))
      retval= boost::any(deref_to_string(operand));
    else if(is_const_ptr_to_float(operand))
      retval= boost::any(deref_to_float(operand));
    else if(is_const_ptr_to_double(operand))
      retval= boost::any(deref_to_double(operand));
    else if(is_const_ptr_to_long_double(operand))
      retval= boost::any(deref_to_long_double(operand));
    else if(is_const_ptr_to_expr_algebra(operand))
      retval= boost::any(deref_to_ExprAlgebra(operand));
    else if(is_const_ptr_to_vector_long_int(operand))
      retval= boost::any(deref_to_vector_long_int(operand));
    else if(is_const_ptr_to_vector_any(operand))
      retval= boost::any(deref_to_vector_any(operand));
    else if(is_const_ptr_to_m_int(operand))
      retval= boost::any(deref_to_m_int(operand));
    else if(is_const_ptr_to_m_sizet(operand))
      retval= boost::any(deref_to_m_sizet(operand));
    else if(is_const_ptr_to_m_double(operand))
      retval= boost::any(deref_to_m_double(operand));
    else if(is_const_ptr_to_matriz_expr(operand))
      retval= boost::any(deref_to_matrizExpr(operand));
    else if(is_const_ptr_to_matrizM(operand))
      retval= boost::any(deref_to_matrizM(operand));
    else if(is_const_ptr_to_matrizMExpr(operand))
      retval= boost::any(deref_to_matrizMExpr(operand));
    else if(is_const_ptr_to_matriz_FT(operand))
      retval= boost::any(deref_to_matriz_FT(operand));
    else if(is_const_ptr_to_matriz_any(operand))
      retval= boost::any(deref_to_matriz_any(operand));
    else if(is_const_ptr_to_pos2d(operand))
      retval= boost::any(deref_to_pos2d(operand));
    else if(is_const_ptr_to_lista_pos2d(operand))
      retval= boost::any(deref_to_lista_pos2d(operand));
    else if(is_const_ptr_to_polilinea2d(operand))
      retval= boost::any(deref_to_polilinea2d(operand));
    else if(is_const_ptr_to_pos3d(operand))
      retval= boost::any(deref_to_pos3d(operand));
    else if(is_const_ptr_to_lista_pos3d(operand))
      retval= boost::any(deref_to_lista_pos3d(operand));
    else if(is_const_ptr_to_vector2d(operand))
      retval= boost::any(deref_to_vector2d(operand));
    else if(is_const_ptr_to_segmento2d(operand))
      retval= boost::any(deref_to_segmento2d(operand));
    else if(is_const_ptr_to_vector3d(operand))
      retval= boost::any(deref_to_vector3d(operand));
    else if(is_const_ptr_to_vdesliz2d(operand))
      retval= boost::any(deref_to_vdesliz2d(operand));
    else if(is_const_ptr_to_vdesliz3d(operand))
      retval= boost::any(deref_to_vdesliz3d(operand));
    else if(is_const_ptr_to_vfijo2d(operand))
      retval= boost::any(deref_to_vfijo2d(operand));
    else if(is_const_ptr_to_vfijo3d(operand))
      retval= boost::any(deref_to_vfijo3d(operand));
    else if(is_const_ptr_to_svd3d(operand))
      retval= boost::any(deref_to_svd3d(operand));
    else if(is_const_ptr_to_recta2d(operand))
      retval= boost::any(deref_to_recta2d(operand));
    else if(is_const_ptr_to_poligono2d(operand))
      retval= boost::any(deref_to_poligono2d(operand));
    else if(is_const_ptr_to_poligono_con_agujeros2d(operand))
      retval= boost::any(deref_to_poligono_con_agujeros2d(operand));
    else if(is_const_ptr_to_circulo2d(operand))
      retval= boost::any(deref_to_circulo2d(operand));
    else if(is_const_ptr_to_recta3d(operand))
      retval= boost::any(deref_to_recta3d(operand));
    else if(is_const_ptr_to_plano3d(operand))
      retval= boost::any(deref_to_plano3d(operand));
    else if(is_const_ptr_to_semiEspacio3d(operand))
      retval= boost::any(deref_to_semiEspacio3d(operand));
    else if(is_const_ptr_to_poliedro3d(operand))
      retval= boost::any(deref_to_poliedro3d(operand));
    else if(is_const_ptr_to_tetraedro3d(operand))
      retval= boost::any(deref_to_tetraedro3d(operand));
    else if(is_const_ptr_to_blockPyramid(operand))
      retval= boost::any(deref_to_blockPyramid(operand));
    else if(is_const_ptr_to_sisCooRect2d3d(operand))
      retval= boost::any(deref_to_sisCooRect2d3d(operand));
    else if(is_const_ptr_to_ref2d3d(operand))
      retval= boost::any(deref_to_ref2d3d(operand));
    else if(is_const_ptr_to_lista(operand))
      retval= boost::any(deref_to_lista(operand));
    else if(is_const_ptr_to_CmdFuncPorPuntos(operand))
      retval= boost::any(deref_to_CmdFuncPorPuntos(operand));
    else if(is_const_ptr_to_ent_cmd(operand))
      retval= boost::any(EntCmdPtr(operand.getEntCmdPtr()));
    else if(is_const_ptr_to_boost_any(operand))
      retval= deref_to_boost_any(operand);
    else
      std::cerr << "convert_to_boost_any(any_const_ptr): No se ha definido la operación de conversión para el objeto de tipo: "
                << operand.type().name() << " que se pasa como parámetro." << std::endl;
    return retval;
  }
