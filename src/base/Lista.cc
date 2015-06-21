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
//Lista.cc

#include "Lista.h"
#include "CmdStatus.h"
#include <deque>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include "any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_utils/src/geom/d2/poligonos2d/Poligono2d.h"
#include "xc_utils/src/geom/d2/poligonos2d/bool_op_poligono2d.h"
#include "../nucleo/aux_any.h"

//! @brief Constructor por defecto.
Lista::Lista(EntCmd *owr,const std::string &str)
  : EntWOwner(owr), lista()
  {
    if(!str.empty())
      inserta_valores(str,true);
  }

//! @brief Inserta valores en la lista a partir de la lista LITERAL que se pasa como parámetro.
void Lista::inserta_valores(const std::string &str,bool asigna)
  {
    const dq_objetos tmp= crea_deque_boost_any(str);
    const size_t sz= tmp.size();
    if(sz>1) //Varios valores.
      for(dq_objetos::const_iterator i= tmp.begin();i!=tmp.end();i++)
        {
          if(boost_any_is_empty(*i))
	    std::cerr << "La expresión '" << str 
                      << "' da como resultado la inserción de un objeto vacío." << std::endl;
          lista.push_back(*i);
        }
    else //Un único valor.
      {
        const boost::any &valor= tmp[0];
        if(boost_any_is_lista(valor) && asigna) //Si se trata de una lista entendemos que queremos hacer la asignación.
          {
            lista= boost_any_to_lista(valor).lista;
          }
        else
          {
            if(boost_any_is_empty(valor))
	      std::cerr << "La expresión '" << str 
                        << "' da como resultado la inserción de un objeto vacío." << std::endl;
            lista.push_back(valor);
          }
      }
  }

//! @brief Inserta valores en la lista a partir de la lista LITERAL que se 
//! obtiene interpretando la cadena que se pasa como parámetro.
void Lista::fromString(const std::string &str)
  {
    std::string valores(str);
    if(has_char(str,'@')) //Si hay algo que interpretar, se interpreta.
      valores= interpretaString(str);
    inserta_valores(valores,true);
  }

//! @brief Inserta en la lista el entero que se pasa como parámetro.
void Lista::Inserta(const int &i)
  { lista.push_back(i); }

//! @brief Inserta en la lista el entero que se pasa como parámetro.
void Lista::Inserta(const long int &i)
  { lista.push_back(i); }

//! @brief Inserta en la lista el double que se pasa como parámetro.
void Lista::Inserta(const double &d)
  { lista.push_back(d); }

//! @brief Inserta en la lista la cadena de caracteres que se pasa como parámetro.
void Lista::Inserta(const std::string &s)
  { lista.push_back(s); }

//! @brief Inserta en la lista la expresión que se pasa como parámetro.
void Lista::Inserta(const ExprAlgebra &e)
  { lista.push_back(e); }

//! @brief Inserta en la lista el vector que se pasa como parámetro.
void Lista::Inserta(const Vector2d &v)
  { lista.push_back(v); }

void Lista::GenListaEnteros(const int &primero,const int &ultimo,const int &step)
  {
    for(int i= primero;i<=ultimo;i+=step)
      Inserta(i);
  }

//! @brief Borra los elementos de la lista.
void Lista::clear(void)
  { lista.clear(); }

//! @brief Borra las propiedades de usuario del objeto y los elementos de la lista.
void Lista::clearAll(void)
  {
    EntWOwner::clearProps();
    lista.clear();
  }

size_t Lista::size(void) const
  { return lista.size(); }
Lista::iterator Lista::begin(void)
  { return lista.begin(); }
Lista::iterator Lista::end(void)
  { return lista.end(); }
Lista::const_iterator Lista::begin(void) const
  { return lista.begin(); }
Lista::const_iterator Lista::end(void) const
  { return lista.end(); }
bool Lista::empty(void) const
  { return lista.empty(); }


//! @brief Evalúa los elementos de la lista.
void Lista::to_num(void)
  {
    dq_objetos::iterator i= lista.begin();
    for(;i!= lista.end();i++)
      {
        boost::any &data= *i;
        ExprAlgebra *ptr_expr= boost::any_cast<ExprAlgebra>(&data);
        if(ptr_expr)
          (*ptr_expr)= ExprAlgebra(ptr_expr->ToNum());
        Lista *ptr_lista= boost::any_cast<Lista>(&data);
        if(ptr_lista)
          ptr_lista->to_num();       
      }
  }

//! @brief Suma los elementos de la lista.
boost::any &Lista::sumatorio(void) const
  {
    static boost::any retval;
    retval= boost::any();
    if(!lista.empty())
      {
        dq_objetos::const_iterator i= lista.begin();
        retval= *i; i++;
        for(;i!= lista.end();i++)
          retval= suma_boost_any(retval,*i);
      }
    return retval;
  }

//! @brief Devuelve el máximo de los elementos de la lista.
boost::any &Lista::max(void) const
  {
    static boost::any retval;
    retval= boost::any();
    if(!lista.empty())
      {
        dq_objetos::const_iterator i= lista.begin();
        retval= *i; i++;
        for(;i!= lista.end();i++)
          retval= max_boost_any(retval,*i);
      }
    return retval;
  }

//! @brief Devuelve el mínimo de los elementos de la lista.
boost::any &Lista::min(void) const
  {
    static boost::any retval;
    retval= boost::any();
    if(!lista.empty())
      {
        dq_objetos::const_iterator i= lista.begin();
        retval= *i; i++;
        for(;i!= lista.end();i++)
          retval= min_boost_any(retval,*i);
      }
    return retval;
  }

//! @brief Reparte el área común entre los polígonos de la lista mediante
//! la técnica de Voronoi.
void Lista::particiona(void)
  {
    std::list<Poligono2d> &areas= castMembers<Poligono2d>();
    if(!areas.empty())
      {
        ::particiona(areas);
        clear();
        for(std::list<Poligono2d>::const_iterator i= areas.begin();i!=areas.end();i++)
          lista.push_back(*i);
      }
    else
      std::cerr << "La lista no contiene polígonos." << std::endl;
  }

void Lista::recorta(const Poligono2d &plg)
  {
    std::list<Poligono2d> &areas= castMembers<Poligono2d>();
    if(!areas.empty())
      {
        areas= ::recorta(areas,plg);
        clear();
        for(std::list<Poligono2d>::const_iterator i= areas.begin();i!=areas.end();i++)
          lista.push_back(*i);
      }
    else
      std::cerr << "La lista no contiene polígonos." << std::endl;
  }

//! @brief Lee un objeto Record desde archivo
//! Soporta los comandos:
bool Lista::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(Lista) Procesando comando: " << cmd << std::endl;
    if(cmd == "valores") //Lista de valores LITERAL
      {
        lista.clear();
        const std::string valores= status.GetBloque();
        inserta_valores(valores,true);
        return true;
      }
    else if(cmd == "from_string") //Lista de valores en cadena de caracteres.
      {
        lista.clear();
        fromString(status.GetBloque());
        return true;
      }
    else if(cmd == "inserta")
      {
        const std::string valor= status.GetBloque();
        inserta_valores(valor,false);
        return true;      
      }
    else if(cmd == "clear") //Borra todo.
      {
        status.GetString(); //Ignoramos entrada.
        lista.clear();
        return true;
      }
    else if(cmd == "tonum")
      {
        status.GetString(); //Ignoramos entrada.
        to_num();
        return true;
      }
    else if(cmd == "genera_lista_enteros")
      {
        std::vector<int> tmp= crea_vector_int(status.GetString());
        const int nc= tmp.size(); //No. de valores leídos.
        if(nc<3)
	  std::cerr << "(Lista) Procesando comando: '" << cmd
                    << "' se esperaban tres argumentos." << std::endl;
        else
          { GenListaEnteros(tmp[0],tmp[1],tmp[2]); }
        return true;
      }
    else if(cmd == "elem")
      {
        const CmdParser &parser= status.Parser();
        if(!parser.TieneIndices())
	  std::cerr << "uso: " << cmd << "[i]{comandos...}" << std::endl;
        else
          {
            const std::string bloque= status.GetBloque();
	    std::deque<boost::any> indices= crea_deque_boost_any(parser.GetIndices());
            const int i= boost_any_to_int(indices[0]); //Nombre del archivo.
            EntCmd *ptr= entcmd_cast((*this)[i]);
            if(ptr)
              ptr->EjecutaBloque(status,bloque,"lista:elem");
            else
              {
	        std::clog << "(Lista) Procesando comando: " << cmd 
                          << "; el objeto de tipo: " << boost_any_tipo_operando((*this)[i])
                          << ", no lee comandos, se ignora la entrada." << std::endl;
                status.GetBloque();
              }
          }
        return true;
      }
    else if(cmd == "for_each")
      {
        const std::string bloque= status.GetBloque();
	dq_objetos::iterator i= lista.begin();
	for(;i!= lista.end();i++)
          {
            EntCmd *ptr= entcmd_cast(*i);
            if(ptr)
              ptr->EjecutaBloque(status,bloque,"lista:for_each");
            else
              {
	        std::clog << "(Lista) Procesando comando: " << cmd << "; el objeto de tipo: " << boost_any_tipo_operando(*i) << ", no lee comandos, se ignora la entrada." << std::endl;
                status.GetBloque();
              }
          }
        return true;
      }
    else if(cmd == "particiona")
      {
        //Aplica a la lista el resultado de repartir
        //el área común entre los polígonos de la lista mediante
        //la técnica de Voronoi.
        status.GetBloque(); //Ignoramos entrada.
        particiona();
        return true;
      }
    else if(cmd == "recorta")
      {
        //Aplica a la lista el resultado de repartir
        //el área común entre los polígonos de la lista mediante
        //la técnica de Voronoi.
        const Poligono2d plg= interpretaPoligono2d(status.GetBloque()); //Ignoramos entrada.
        recorta(plg);
        return true;
      }
    else
      return EntWOwner::procesa_comando(status);
  }

void Lista::Print(std::ostream &os) const
  {
    if(lista.empty()) return;
    dq_objetos::const_iterator i=lista.begin();
    boost_any_print(os,*i); i++;
    for(;i!=lista.end();i++)
      {
        os << ',';
        boost_any_print(os,*i);
      }
  }

std::string Lista::sqlValues(void) const
  {
    std::string retval= "";
    if(lista.empty())
      return retval;
    dq_objetos::const_iterator i=lista.begin();
    retval= boost_any_to_sql_value(*i); i++;
    for(;i!=lista.end();i++)
      {
        retval+= ','+ boost_any_to_sql_value(*i);
      }
    return retval;
  }

//! @brief Devuelve una propiedad de un elemento de la lista (si es posible);
any_const_ptr Lista::get_prop_miembro(const std::string &nmb_miembro,const boost::any &elem_lista) const
  {
    if(boost_any_is_lista(elem_lista))
      return boost_any_to_lista(elem_lista).GetProp(nmb_miembro);
    else
      {
	std::cerr << "Lista::get_prop_miembro; No se pudo obtener la propiedad: '"
                  << nmb_miembro << "' porque ";
        boost_any_print(std::cerr,elem_lista);
        std::cerr << " no es una lista." << std::endl;
        return any_const_ptr();
      }
  }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr Lista::GetProp(const std::string &cod) const 
  {
    if(verborrea>4)
      std::clog << "(Lista::GetProp) Buscando propiedad: " << cod << std::endl;
    if(cod == "size")
      {
        tmp_gp_szt= lista.size();
        return any_const_ptr(tmp_gp_szt);
      }
    else if(cod == "sqlValues")
      {
        tmp_gp_str= sqlValues();
        return any_const_ptr(tmp_gp_str);
      }
    else if(cod == "sumatorio")
      {
        static boost::any tmp_gp_any;
        tmp_gp_any= sumatorio();
        return any_const_ptr(tmp_gp_any);
      }
    else if(cod == "getMin")
      {
        static boost::any tmp_gp_any;
        tmp_gp_any= min();
        return any_const_ptr(tmp_gp_any);
      }
    else if(cod == "getMax")
      {
        static boost::any tmp_gp_any;
        tmp_gp_any= max();
        return any_const_ptr(tmp_gp_any);
      }
    else
      return EntWOwner::GetProp(cod);
  }

//! @brief Devuelve una referencia al objeto cuyo
//! índice se pasa como parámetro.
boost::any &Lista::operator[](const size_t &i)
  {
    if(i<lista.size())
      return lista[i];
    else
      {
        const std::string posLectura= get_ptr_status()->getPosicionLecturaActual();
        std::cerr << "Lista; indice: " << i << " fuera de rango. "
                  << posLectura << std::endl;
        exit(0);
      }
  }

const boost::any &Lista::operator[](const size_t &i) const
  {
    if(i<lista.size())
      return lista[i];
    else
      {
        const std::string posLectura= get_ptr_status()->getPosicionLecturaActual();
        std::cerr << "Lista; indice: " << i << " fuera de rango. "
                  << posLectura << std::endl;
        exit(0);
      }
  }


std::ostream &operator<<(std::ostream &os,const Lista &l)
  {
    l.Print(os);
    return os;
  }
