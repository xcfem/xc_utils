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
//CmdFuncPorPuntos

#include "CmdFuncPorPuntos.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"
#include "xc_utils/src/base/Lista.h"
#include "xc_basic/src/texto/cadena_carac.h"
#include "xc_utils/src/nucleo/InterpreteRPN.h"

//! @brief Constructor.
CmdFuncPorPuntos::CmdFuncPorPuntos(EntCmd *owr)
  : EntWOwner(owr), f() {}

//! @brief Constructor.
CmdFuncPorPuntos::CmdFuncPorPuntos(EntCmd *owr,const std::string &valor)
  : EntWOwner(owr), f()
  { inserta_valores(valor); }


//! @brief Inserta valores en la función a partir de la cadena de caracteres que se pasa como parámetro.
void CmdFuncPorPuntos::inserta_valores(const std::string &str)
  {
    const Lista::dq_objetos tmp= crea_deque_boost_any(str);
    const size_t sz= tmp.size();
    if(sz>1) //Varios valores.
      {
        Lista::dq_objetos::const_iterator i= tmp.begin();
        Lista::dq_objetos::const_iterator j= i;
        j++;
        for(;j!=tmp.end();i++,j++)
          f.Inserta(convert_to_double(*i),convert_to_double(*j));
      }
    else //Un único valor.
      {
        const boost::any &valor= tmp[0];
        if(boost_any_is_CmdFuncPorPuntos(valor)) //Si se trata de una función entendemos que queremos hacer la asignación.
          {
            (*this)= boost_any_to_CmdFuncPorPuntos(valor);
          }
        else
	  std::cerr << "Error en CmdFuncPorPuntos::inserta_valores" << std::endl;
      }
  }

//! @brief Inserta valores en la función a partir de la cadena que se 
//! obtiene interpretando la cadena que se pasa como parámetro.
void CmdFuncPorPuntos::fromString(const std::string &str)
  {
    std::string valores(str);
    if(has_char(str,'@')) //Si hay algo que interpretar, se iterpreta.
      valores= interpretaString(str);
    inserta_valores(valores);
  }

void CmdFuncPorPuntos::append(const double &x,const double &y)
  { f.Inserta(x,y); }

//! @brief Lectura de la FuncPorPuntos desde archivo.
bool CmdFuncPorPuntos::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    if(verborrea>2)
      std::clog << "(CmdFuncPorPuntos) Procesando comando: " << cmd << std::endl;
    if(cmd == "inserta") //Inserta punto.
      {
        const std::string &args= status.Parser().GetArgs();
        std::vector<double> indices= crea_vector_double(args);
        const size_t nc= indices.size(); //no. de índices.
        if(nc!=1)
	  std::cerr << "(CmdFuncPorPuntos) Procesando comando: " << cmd
                    << "; error, se leyeron " << nc
                    << " índices, se esperaba 1." << std::endl;
        f.Inserta(indices[0],interpretaDouble(status.GetString()));
        return true;
      }
    else if(cmd == "punto") //Vector posición del punto.
      {
        std::vector<double> tmp= crea_vector_double(status.GetString());
        const int nc= tmp.size(); //No. de valores leídos.
        if(nc>=2)
          f.Inserta(tmp[0],tmp[1]);
        else
	  std::cerr << "(CmdFuncPorPuntos) Procesando comando: " << cmd
                    << "; error, se esperaban dos coordenadas, se obtuvieron: " << nc
                    << "." << std::endl;
        return true;
      }
    else if(cmd == "asignaCte") //Asigna una constante.
      {
        const double d= interpretaDouble(status.GetString());
        f=d;
        return true;
      }
    else if(cmd == "sumaCte") //Suma una constante.
      {
        const double d= interpretaDouble(status.GetString());
        f+=d;
        return true;
      }
    else if(cmd == "restaCte") //Resta una constante.
      {
        const double d= interpretaDouble(status.GetString());
        f-=d;
        return true;
      }
    else if(cmd == "multiplicaCte") //Multiplica por una constante.
      {
        const double d= interpretaDouble(status.GetString());
        f*=d;
        return true;
      }
    else if(cmd == "divideCte") //Divide por una constante.
      {
        const double d= interpretaDouble(status.GetString());
        f/=d;
        return true;
      }
    else if(cmd == "suma") //Suma a ésta otra función.
      {
        const CmdFuncPorPuntos f2= interpretaFuncPorPuntos(status.GetString());
        f+=f2.f;
        return true;
      }
    else if(cmd == "resta") //Resta a ésta otra función.
      {
        const CmdFuncPorPuntos f2= interpretaFuncPorPuntos(status.GetString());
        f-=f2.f;
        return true;
      }
    else if(cmd == "multiplica") //Multiplica por ésta otra función.
      {
        const CmdFuncPorPuntos f2= interpretaFuncPorPuntos(status.GetString());
        f*=f2.f;
        return true;
      }
    else if(cmd == "divide") //Divide esta por otra función.
      {
        const CmdFuncPorPuntos f2= interpretaFuncPorPuntos(status.GetString());
        f/=f2.f;
        return true;
      }
    else
      return EntWOwner::procesa_comando(status);
  }

CmdFuncPorPuntos CmdFuncPorPuntos::sub(const double &x0,const double &x1) const
  {
    CmdFuncPorPuntos retval(*this);
    retval.f= this->f.sub(x0,x1);
    return retval;
  }

//! @brief Devuelve la función cambiada de signo.
CmdFuncPorPuntos CmdFuncPorPuntos::getNeg(void) const
  {
    CmdFuncPorPuntos retval(*this);
    retval.Neg();
    return retval;
  }

//! @brief Cambia de signo la función.
CmdFuncPorPuntos &CmdFuncPorPuntos::Neg(void)
  {
    f.Neg();
    return *this;
  }

//! @brief Integra la función entre x0 y x1 con paso delta.
CmdFuncPorPuntos CmdFuncPorPuntos::integra(const double &x0,const double &x1,const double &delta) const
  {
    CmdFuncPorPuntos retval(*this);
    retval.f= f.integra(x0,x1,delta);
    return retval;
  }

CmdFuncPorPuntos &CmdFuncPorPuntos::operator+=(const double &c)
  {
    f+=c;
    return *this;
  }
CmdFuncPorPuntos &CmdFuncPorPuntos::operator+=(const CmdFuncPorPuntos &f2)
  {
    f+= f2.f;
    return *this;
  }
CmdFuncPorPuntos &CmdFuncPorPuntos::operator-=(const double &c)
  {
    f-=c;
    return *this;
  }
CmdFuncPorPuntos &CmdFuncPorPuntos::operator-=(const CmdFuncPorPuntos &f2)
  {
    f-= f2.f;
    return *this;
  }
CmdFuncPorPuntos &CmdFuncPorPuntos::operator*=(const double &c)
  {
    f*=c;
    return *this;
  }
CmdFuncPorPuntos &CmdFuncPorPuntos::operator*=(const CmdFuncPorPuntos &f2)
  {
    f*= f2.f;
    return *this;
  }
CmdFuncPorPuntos &CmdFuncPorPuntos::operator/=(const double &c)
  {
    f/=c;
    return *this;
  }
CmdFuncPorPuntos &CmdFuncPorPuntos::operator/=(const CmdFuncPorPuntos &f2)
  {
    f/= f2.f;
    return *this;
  }

void CmdFuncPorPuntos::clear(void)
  { f.clear(); }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro.
any_const_ptr CmdFuncPorPuntos::GetProp(const std::string &cod) const 
  {
    if(cod == "valor")
      {
        const double x= popDouble(cod);
        tmp_gp_dbl= f(x);
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "valores")
      {
	const std::vector<double> x= popVectorDouble(cod);
        tmp_gp_mdbl= convert_to_m_double(f(x));
        return any_const_ptr(tmp_gp_mdbl);
      }
    else if(cod == "max")
      {
        tmp_gp_dbl= f.Max();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "min")
      {
        tmp_gp_dbl= f.Min();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "area")
      {
        tmp_gp_dbl= f.Area();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "firstX")
      {
        tmp_gp_dbl= f.firstX();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "firstY")
      {
        tmp_gp_dbl= f.firstY();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "lastX")
      {
        tmp_gp_dbl= f.lastX();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "lastY")
      {
        tmp_gp_dbl= f.lastY();
        return any_const_ptr(tmp_gp_dbl);
      }
    else if(cod == "dominio")
      {
        const dq_double dom= f.Dominio();
        EntCmd *this_no_const= const_cast<CmdFuncPorPuntos *>(this);
        tmp_gp_lista.set_owner(this_no_const);
        tmp_gp_lista.clearAll();
        for(dq_double::const_iterator i= dom.begin();i!=dom.end();i++)
        tmp_gp_lista.Inserta(*i);
        return any_const_ptr(tmp_gp_lista);
      }
    else if(cod == "abcisas")
      {
        const dq_double abcisas= f.Abcisas();
        EntCmd *this_no_const= const_cast<CmdFuncPorPuntos *>(this);
        tmp_gp_lista.set_owner(this_no_const);
        tmp_gp_lista.clearAll();
        for(dq_double::const_iterator i= abcisas.begin();i!=abcisas.end();i++)
        tmp_gp_lista.Inserta(*i);
        return any_const_ptr(tmp_gp_lista);
      }
    else if(cod == "ordenadas")
      {
        const dq_double ordenadas= f.Ordenadas();
        EntCmd *this_no_const= const_cast<CmdFuncPorPuntos *>(this);
        tmp_gp_lista.set_owner(this_no_const);
        tmp_gp_lista.clearAll();
        for(dq_double::const_iterator i= ordenadas.begin();i!=ordenadas.end();i++)
        tmp_gp_lista.Inserta(*i);
        return any_const_ptr(tmp_gp_lista);
      }
    else if(cod == "ceros")
      {
        const dq_double ceros= f.Ceros();
        EntCmd *this_no_const= const_cast<CmdFuncPorPuntos *>(this);
        tmp_gp_lista.set_owner(this_no_const);
        tmp_gp_lista.clearAll();
        for(dq_double::const_iterator i= ceros.begin();i!=ceros.end();i++)
        tmp_gp_lista.Inserta(*i);
        return any_const_ptr(tmp_gp_lista);
      }
    else if(cod == "sub")
      {
        double x0= 0.0,x1= 0.0;
        if(InterpreteRPN::Pila().size()>1)
          {
            x1= convert_to_double(InterpreteRPN::Pila().Pop());
            x0= convert_to_double(InterpreteRPN::Pila().Pop());
          }
        else
          err_num_argumentos(std::cerr,2,"GetProp",cod);
        tmp_gp_func_pts= sub(x0,x1);
        return any_const_ptr(tmp_gp_func_pts);
      }
    else if(cod == "integra")
      {
        double delta= -1,x0= 0.0,x1= 1.0;
        if(InterpreteRPN::Pila().size()>2)
          {
            delta= convert_to_double(InterpreteRPN::Pila().Pop());
            x1= convert_to_double(InterpreteRPN::Pila().Pop());
            x0= convert_to_double(InterpreteRPN::Pila().Pop());
          }
        else
          err_num_argumentos(std::cerr,3,"GetProp",cod);
        tmp_gp_func_pts= integra(x0,x1,delta);
        return any_const_ptr(tmp_gp_func_pts);
      }
    else
      return EntWOwner::GetProp(cod);
  }

//! @brief Suma a la función una constante.
CmdFuncPorPuntos operator+(const CmdFuncPorPuntos &f,const double &c)
  {
    CmdFuncPorPuntos retval(f);
    retval+= c;
    return retval;
  }
//! @brief Suma dos funciones.
CmdFuncPorPuntos operator+(const CmdFuncPorPuntos &f1,const CmdFuncPorPuntos &f2)
  {
    CmdFuncPorPuntos retval(f1);
    retval+= f2;
    return retval;
  }
//! @brief Resta dos funciones.
CmdFuncPorPuntos operator-(const CmdFuncPorPuntos &f1,const CmdFuncPorPuntos &f2)
  {
    CmdFuncPorPuntos retval(f1);
    retval-= f2;
    return retval;
  }
//! @brief Multiplica dos funciones.
CmdFuncPorPuntos operator*(const CmdFuncPorPuntos &f1,const CmdFuncPorPuntos &f2)
  {
    CmdFuncPorPuntos retval(f1);
    retval*= f2;
    return retval;
  }

//! @brief Divide dos funciones.
CmdFuncPorPuntos operator/(const CmdFuncPorPuntos &f1,const CmdFuncPorPuntos &f2)
  {
    CmdFuncPorPuntos retval(f1);
    retval/= f2;
    return retval;
  }

//! @brief Multiplica la función por una constante.
CmdFuncPorPuntos operator*(const double &c,const CmdFuncPorPuntos &f)
  {
    CmdFuncPorPuntos retval(f);
    retval*= c;
    return retval;
  }
