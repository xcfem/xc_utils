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
//Action.hxx

#ifndef ACTION_H
#define ACTION_H

#include <string>
#include <deque>
#include <cmath>
#include "xc_utils/src/base/EntConNmb.h"
#include "ActionRelationships.h"

//! \namespace<cmb_acc>
//! Rutinas para generar combinaciones de acciones.
namespace cmb_acc{

class ActionRValueList;

//! @defgroup CMBACC Rutinas para generar combinaciones de acciones.
//
//! @ingroup CMBACC
//
//! @brief Los objetos de esta clase representan una acción o una combinación de acciones.
class Action: public EntConNmb
  {
    std::string descripcion; //!< Descripcion de la acción p. ej. "Viento derecho".
    ActionRelationships relaciones; //!< Relaciones de una acción con el resto.
    double f_pond; //!< Factor que pondera a la acción.

    void limpia_nombres(void);
    bool incompatible(const Action &f) const;
    void multiplica(const double &d);
    void suma(const Action &f);


  protected:
    virtual bool procesa_comando(CmdStatus &status);

  public:
    static const double zero; //!< Valor por debajo del cual la accion se considera nula.
    Action(const std::string &n="", const std::string &descrip="");

    static Action NULA(void);
    //! @brief Asigna el nombre a la acción.
    inline void SetNombre(const std::string &nmb)
      { EntConNmb::Nombre()= nmb; }
    const std::string GetNombreExpandido(void) const;
    //! @brief Devuelve la descripción de la acción.
    inline const std::string &GetDescripcion(void) const
      { return descripcion; }
    //! @brief Asigna a la acción la descripción que se pasa como parámetro.
    inline void SetDescripcion(const std::string &desc)
      { descripcion= desc; }
    const ActionRelationships &getRelaciones(void) const
      { return relaciones; }
    inline double getWeightingFactor(void) const
      { return f_pond; }
    inline void setWeightingFactor(const double &f)
      { f_pond= f; }
    typedef std::map<std::string,float> map_descomp;
    map_descomp getDescomp(void) const;

    //! @brief Devuelve verdadero si esta acción es incompatible con la que se pasa como parámetro.
    bool Incompatible(const Action &f) const;
    //! @brief Devuelve verdadero si esta acción es compatible con la que se pasa como parámetro.
    inline bool Compatible(const Action &f) const
      { return !Incompatible(f); }

    bool Simple(void) const;
    //! @brief Devuelve verdadero si la acción es nula.
    inline bool Nula(const double &tol= zero) const
      { return (fabs(f_pond)<tol); }
     //! @brief Devuelve la acción multiplicada por un escalar.
    Action GetMult(const double &d) const
      {
        Action retval(*this);
        retval*=(d);
        return retval;
      }
    //! @brief Producto por un escalar.
    inline Action &operator*=(const double &d)
      {
        multiplica(d);
        return *this;
      }
    //! @brief Suma a ésta la acción que se pasa como parámetro.
    inline Action &operator+=(const Action &f)
      {
        suma(f);
        return *this;
      }
    //! @brief Devuelve el producto de la acción por un escalar.
    inline friend Action operator*(const double &d,const Action &f)
      { return f.GetMult(d); }
    //! @brief Devuelve el producto de la acción por un escalar.
    inline friend Action operator*(const Action &f,const double &d)
      { return d*f; }
    //! @brief Suma de acciones.
    inline friend Action operator+(const Action &f1,const Action &f2)
      {
        Action retval(f1);
        retval+=(f2);
        return retval;
      }

    std::string ListaStrIncompatibles(ActionRValueList *af) const;
    std::vector<double> getCoeficientes(const std::vector<std::string> &) const;
    void Print(std::ostream &os) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
  };

std::ostream &operator<<(std::ostream &os,const Action &acc);

bool incompatibles(const Action &acc_i,const Action &acc_j);

//! @brief Devuelve la lista de acciones incompatibles con aquella cuyo nombre se pasa como parámetro.
template <class InputIterator>
std::deque<const Action *> listaIncompatibles(const Action *acc,InputIterator begin,InputIterator end)
  {
    std::deque<const Action *> retval;
    for(InputIterator i=begin;i!=end;i++)
      {
        const Action &data= *i;
        if(acc->Incompatible(data)) retval.push_back(&data);
      }
    return retval;
  }

//! @brief Devuelve la lista de nombre de las acciones.
template <class InputIterator>
std::string nombresAcciones(InputIterator begin,InputIterator end)
  {
    std::string retval;
    InputIterator i=begin;
    retval= (*i).GetNombre(); i++;
    for(;i!=end;i++)
      retval+= "," + (*i).GetNombre();
    return retval;
  }

//! @brief Devuelve la lista de nombre de las acciones.
template <class InputIterator>
std::string nombresPtrAcciones(InputIterator begin,InputIterator end)
  {
    std::string retval;
    InputIterator i=begin;
    retval= (*i)->GetNombre(); i++;
    for(;i!=end;i++)
      retval+= "," + (*i)->GetNombre();
    return retval;
  }
} //fin namespace nmb_acc.

#endif
