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
//GmGrupo.h

#ifndef GMGRUPO_H
#define GMGRUPO_H

#include "xc_basic/src/stl/pdeque.h"


//! @ingroup GEOM
//
//! @brief Clase base para grupos de entidades geométricas.
template <typename GO>
class GmGrupo : public GO
  {
    static const GO *downcast(const GeomObj *p)
      { return dynamic_cast<const GO *>(p); }
    static GO *downcast(GeomObj *p)
      { return dynamic_cast<GO *>(p); }
  protected:
    typedef pdeque<GO> pdeque_geom_obj;
    pdeque_geom_obj objetos; //Objetos del grupo
    bool igual_dimension(void) const;
    //Return verdadero si todos los objetos son de la misma dimensión.
  private:
    void copia_objetos(const pdeque_geom_obj &objs);
  public:
    typedef typename pdeque_geom_obj::const_iterator const_iterator;
    typedef typename pdeque_geom_obj::iterator iterator;

    inline bool empty(void) const
      { return objetos.empty(); }

    inline const_iterator begin(void) const
      { return objetos.begin(); }
    inline const_iterator end(void) const
      { return objetos.end(); }
    inline bool Vacio(void) const
      { return objetos.empty(); }

    GmGrupo(void) : GO(), objetos() {}
    GmGrupo(const GmGrupo &otro) : GO(otro)
      { copia_objetos(otro.objetos); }
    virtual GEOM_FT GetMax(unsigned short int i) const;
    virtual GEOM_FT GetMin(unsigned short int i) const;
    virtual unsigned short int Dimension(void) const;
    size_t size(void) const
      { return objetos.size(); }
    void push_back(const GO &obj)
      { objetos.push_back(downcast(obj.clon())); }
    virtual GEOM_FT getLength(void) const;
    virtual GEOM_FT Area(void) const;
    virtual GEOM_FT Volumen(void) const;
    void Print(std::ostream &os) const;
  };

template <typename GO>
void GmGrupo<GO>::copia_objetos(const pdeque_geom_obj &objs)
  {
    for(register const_iterator i= objs.begin();i!=objs.end();i++)
      objetos.push_back(downcast((*i)->clon()));
  }

template <typename GO>
bool GmGrupo<GO>::igual_dimension(void) const
//Return verdadero si todos los objetos son de la misma dimensión.
  {
    if(objetos.empty()) return true;
    register const_iterator i(objetos.begin());
    const unsigned short int d((*i)->Dimension());
    i++;
    for(;i!=objetos.end();i++)
      if(d!=(*i)->Dimension()) return false;
    return true;
  }

template <typename GO>
unsigned short int GmGrupo<GO>::Dimension(void) const
//Return the dimension of the object 0, 1, 2 or 3.
  {
    if(objetos.empty()) return 0;
    register const_iterator i(objetos.begin());
    register unsigned short int d((*i)->Dimension());
    i++;
    for(;i!=objetos.end();i++)
      d= std::max(d,(*i)->Dimension());
    return d;
  }

template <typename GO>
GEOM_FT GmGrupo<GO>::GetMax(unsigned short int i) const
  {
    if(objetos.empty()) return 0.0;
    register const_iterator j=objetos.begin();
    register GEOM_FT mx= (*j)->GetMax(i);
    j++;
    for(;j != objetos.end();j++)
      mx= std::max((*j)->GetMax(i),mx);
    return mx;
  }
template <typename GO>
GEOM_FT GmGrupo<GO>::GetMin(unsigned short int i) const
  {
    if(objetos.empty()) return 0.0;
    register const_iterator j=objetos.begin();
    register GEOM_FT mn= (*j)->GetMin(i);
    j++;
    for(;j != objetos.end();j++)
      mn= std::min((*j)->GetMin(i),mn);
    return mn;
  }

//! @brief Return the length of the object.
template <typename GO>
GEOM_FT GmGrupo<GO>::getLength(void) const
  {
    if(objetos.empty()) return 0.0;
	register const_iterator i(objetos.begin());
    register GEOM_FT retval((*i)->getLength());
    i++;
    for(;i!=objetos.end();i++)
      retval+= (*i)->getLength();
    return retval;
  }
template <typename GO>
GEOM_FT GmGrupo<GO>::Area(void) const
  {
    if(objetos.empty()) return 0.0;
	register const_iterator i(objetos.begin());
    register GEOM_FT retval((*i)->Area());
    i++;
    for(;i!=objetos.end();i++)
      retval+= (*i)->Area();
    return retval;
  }
template <typename GO>
GEOM_FT GmGrupo<GO>::Volumen(void) const
  {
    if(objetos.empty()) return 0.0;
	register const_iterator i(objetos.begin());
    register GEOM_FT retval((*i)->Volumen());
    i++;
    for(;i!=objetos.end();i++)
      retval+= (*i)->Volumen();
    return retval;
  }

template <typename GO>
void GmGrupo<GO>::Print(std::ostream &os) const
  {
    if(Vacio()) return;
    register const_iterator i= begin();
    os << **i; i++;
    for(;i!=end();i++)
      os << std::endl << **i;
  }

#endif
