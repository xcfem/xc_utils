//----------------------------------------------------------------------------
//  xc_utils library; general purpose classes and functions.
//
//  Copyright (C)  Luis Claudio Pérez Tato
//
//  XC utils is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or 
//  (at your option) any later version.
//
//  This software is distributed in the hope that it will be useful, but 
//  WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.  
//
// You should have received a copy of the GNU General Public License 
// along with this program.
// If not, see <http://www.gnu.org/licenses/>.
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
        m_double nat_coord;//!< Natural coordinates of the integration point.
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
