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
//Metodo2Func.h

#ifndef METODO2FUNC_H
#define METODO2FUNC_H


template<class T,class metodo>
class Metodo2Func
//Este objeto vale para "convertir" un método
//de un objeto en una función de manera
//que se pueda llamar con ella a las templates
//de calculo de raíces.
  {
  protected:
    T *t_;
    metodo f_;
  public:
    Metodo2Func(void)
      : t_(NULL), f_(NULL) {}
    Metodo2Func(T &t,metodo f)
      : t_(&t), f_(f) {}
    Metodo2Func(const Metodo2Func<T,metodo> &otro)
      {
        t_= otro.t_;
        f_= otro.f_;
      }
    Metodo2Func &operator=(const Metodo2Func<T,metodo> &otro)
      {
        t_= otro.t_;
        f_= otro.f_;
        return *this;
      }
  };

template<class T,class metodo>
class Metodo2FuncDDP: public Metodo2Func<T,metodo>
  {
    typedef Metodo2Func<T,metodo> metodo_2_func_t_metodo;

    inline double eval(const double &d,const double *p) const
      { return (this->t_ && this->f_) ? (this->t_->*this->f_)(d,p) : 0.0; }
  public:
    Metodo2FuncDDP(T &t,metodo f)
      : metodo_2_func_t_metodo(t,f) {}
    inline double operator()(const double &d,const double *p) const
      { return eval(d,p); }
  };

#endif
