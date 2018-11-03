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
//PtosIntegracion.h
// ORIGINAL: Copyright (c) 1999, A.H. van den Boogaard
//FeaTure is put on the internet as free software. I would very 
//much like to hear your feedback and if possible improvements. See 
//also the 'Future plans' part in the manual.
//Modificado por LCPT para integrarlo en Swing.

#ifndef PTOSINTEGRACION_H
#define PTOSINTEGRACION_H

#include "xc_utils/src/matrices/m_double.h"


void Gauss( int ip, int nip, double &xi, double &weight);

void Hammer( int ip, int nip, double& L1, double& L2, double& L3,
             double& weight );

//! @ingroup ShapeFunctionsGroup
//!
//! @brief Contenedor de puntos de integración.
class PtosIntegracion
  {
    //! @brief Definición del un punto de integración.
    class pto_int
      { 
      public:
        pto_int(){};
        ~pto_int(){};
        m_double nat_coord;//!< Coordenadas naturales del punto de integración.
        double weight; //!< Peso del punto de integración.
      };

    private:
      int nr_of_intpt; //!< Número de puntos de integración.
      pto_int *intpts; //!< Puntos de integración.

    public:
      PtosIntegracion();
      PtosIntegracion(const PtosIntegracion &);
      PtosIntegracion(int nr);
      ~PtosIntegracion();

      void set_nr_intpt(int nr);
      int  get_nr_intpt() const;
      void set_values(int ip,const m_double &coor,const double &weight);
      m_double get_coor(int ip) const;
      double get_weight(int ip) const;
};

#endif /* PTOSINTEGRACION_H */
