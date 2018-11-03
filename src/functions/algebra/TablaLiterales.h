//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
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
//TablaLiterales.h

#ifndef TABLALITERALES_H
#define TABLALITERALES_H

#include "Operando.h"
#include <map>

class TablaLiterales
  {
  private:
    class Literal : public Operando
      {
        //static TablaLiterales *ptr_tabla;
        //Literal &operator=(const Literal &otro);
      public:
	explicit Literal(const double &d= 0.0);
        inline virtual bool Evaluable(void) const
          { return true; }
        inline virtual bool IgualA(const double &d) const
          { return (valor == d); }
        virtual Rama Diferencia(const Variable &,const Rama &) const;
        virtual int GetPrioridad(void) const
          { return 8; }
        std::ostream &Imprime(std::ostream &os) const;

        friend int operator <(const Literal &c1,const Literal &c2)
          { return (c1.valor < c2.valor); }
        friend int operator ==(const Literal &c1,const Literal &c2)
          { return (c1.valor == c2.valor); }
        friend int operator !=(const Literal &c1,const Literal &c2)
          { return (c1.valor != c2.valor); }
        friend int operator >(const Literal &c1,const Literal &c2)
          { return (c1.valor > c2.valor); }

      };
    typedef std::map<Literal,size_t> tabla_literales;
    typedef tabla_literales::iterator iterator;
    typedef tabla_literales::const_iterator const_iterator;
    typedef tabla_literales::value_type value_type;
    tabla_literales literales;

    const Literal *Nuevo(const Literal &l);
    void NuevaRef(const Literal &l);
    void Borra(const Literal &l);
  public:
    TablaLiterales(void);
    inline const Operando *NuevoDbl(const double &d)
      { return Nuevo(Literal(d)); }
    void NuevaRef(const double &);
    void NuevaRef(const Segnal *);
    void Borra(const double &d);
    void BorraSiLiteral(const Segnal *s);
    inline size_t size(void) const
      { return literales.size(); }
 };

#endif
