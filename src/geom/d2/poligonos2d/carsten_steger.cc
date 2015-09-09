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
//Carsten_Steger.cc

#include "carsten_steger.h"
#include "xc_basic/src/funciones/estadisticas/combinatoria.h"
#include "xc_utils/src/geom/d2/poligonos2d/SupPoligonal2d.h"

inline long long c_p_q_k_l(const int &p,
                                    const int &q,
                                    const int &k,
                                    const int &l)
  { return coeficiente_binomial(k+l,l)*coeficiente_binomial(p+q-k-l,q-l); }

inline double potencias(const double &xi,const double &xi_1, const double &yi,const double &yi_1,
                        const int &p, const int &q,
                        const int &k, const int &l)
  { return pow(xi,k)*pow(xi_1,p-k)*pow(yi,l)*pow(yi_1,q-l); }

inline double sumando_p_q_k_l(const double &xi,const double &xi_1, 
                              const double &yi,const double &yi_1,
                              const int &p, const int &q,
                              const int &k, const int &l)
  { return c_p_q_k_l(p,q,k,l)*potencias(xi,xi_1,yi,yi_1,p,q,k,l); }

double sumatorio_k_l(const double &xi,const double &xi_1, 
                     const double &yi,const double &yi_1,
                     const int &p, const int &q)
  {
    double retval= 0.0;
    for(register int k=0;k<=p;k++)
      for(register int l=0;l<=q;l++)
        retval+=sumando_p_q_k_l(xi,xi_1,yi,yi_1,p,q,k,l);
    return retval;
  }
double sumatorio_i_p_q(const SupPoligonal2d &sp,const int &p, const int &q)
  {
    double retval= 0;
    const size_t num_vertices= sp.GetNumVertices();
    for(register size_t i=1;i<=num_vertices;i++)
      {
        
        const size_t imas1= i%num_vertices+1;

        const Pos2d vi= sp.Vertice(imas1);
        const Pos2d vi_1= sp.Vertice(i);

        const double xi= vi.x();
        const double xi_1= vi_1.x();
        const double yi= vi.y();
        const double yi_1= vi_1.y();
        retval+=(xi_1*yi-xi*yi_1)*sumatorio_k_l(xi,xi_1,yi,yi_1,p,q);
      }
    return retval;
  }
inline long long divisor(const int &p, const int &q)
  { return (p+q+2)*(p+q+1)*coeficiente_binomial(p+q,q); }
GEOM_FT momento_p_q(const SupPoligonal2d &sp,const int &p, const int &q)
  { return double_to_FT(sumatorio_i_p_q(sp,p,q)/divisor(p,q)); }
