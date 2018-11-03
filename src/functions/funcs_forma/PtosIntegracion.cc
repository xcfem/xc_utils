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
// Copyright (c) 1999, A.H. van den Boogaard

#include "PtosIntegracion.h"
#include <sstream>

//! Abcisa y peso de un punto de Gauss.
//!
//! Dado un punto de integración definido por su índice ip
//! y por el número total de puntos de integración a emplear
//! nip, devuelve su abcisa xi y su peso weight.
//! @param ip: Índice del punto de integración.
//! @param nip: Número de puntos de integración.
//! @param xi: Abcisa del punto de integración.
//! @param weight: Peso del punto de integración.
void Gauss( int ip, int nip, double& xi, double& weight )
  {
    if ( ip<1 || ip>nip )
     {
       std::cerr << "wrong integration point number:" << ip <<
                  " of " << nip << " available";
     }

   switch(nip)
     {
     case  1:
       xi = 0.0;
       weight = 2.0;
       break;
     case  2:
       switch ( ip )
         {
         case 1:
           xi = -0.577350269189626;
           break;
         case 2:
           xi =  0.577350269189626;
           break;
         }
       weight = 1.0;
       break;
     case  3:
       switch ( ip )
         {
         case 1:
           xi     = -0.774596669241483;
           weight =  0.555556;
           break;
         case 2:
           xi     =  0.0;
           weight =  0.888888888888889;
           break;
         case 3:
           xi     =  0.774596669241483;
           weight =  0.555555555555556;
           break;
         }
       break;
     case  4:
       switch ( ip )
         {
         case 1:
           xi     = -0.861136311594053;
           weight =  0.347854845137454;
           break;
         case 2:
           xi     = -0.339981043584856;
           weight =  0.652145154862546;
           break;
         case 3:
           xi     =  0.339981043584856;
           weight =  0.652145154862546;
           break;
         case 4:
           xi     =  0.861136311594053;
           weight =  0.347854845137454;
           break;
         }
       break;
     case  5:
       switch ( ip )
         {
         case 1:
           xi     = -0.906179845938664;
           weight =  0.236926885056189;
           break;
         case 2:
           xi     = -0.538469310105683;
           weight =  0.478628670499366;
           break;
         case 3:
           xi     =  0.0;
           weight =  0.568888888888889;
           break;
         case 4:
           xi     =  0.906179845938664;
           weight =  0.236926885056189;
           break;
         case 5:
           xi     =  0.538469310105683;
           weight =  0.478628670499366;
           break;
         }
       break;
     case  6:
       switch ( ip )
         {
         case 1:
           xi     = -0.932469514203152;
           weight =  0.171324492379170;
           break;
         case 2:
           xi     = -0.661209386466265;
           weight =  0.360761573048139;
           break;
         case 3:
           xi     = -0.238619186083197;
           weight =  0.467913934572691;
           break;
         case 4:
           xi     =  0.932469514203152;
           weight =  0.171324492379170;
           break;
         case 5:
           xi     =  0.661209386466265;
           weight =  0.360761573048139;
           break;
         case 6:
           xi     =  0.238619186083197;
           weight =  0.467913934572691;
           break;
         }
       break;
     default:
       { 
         std::cerr << "wrong nr of integration points: " << nip;
       }
     }
  }

//! Abcisa y peso de un punto de integración en un dominio triangular.
//!
//! Dado un punto de integración definido por su índice ip
//! y por el número total de puntos de integración a emplear
//! nip, devuelve su abcisa xi y su peso weight.
//! @param ip: Índice del punto de integración.
//! @param nip: Número de puntos de integración.
//! @param L1: Primera coordenada natural del punto de integración.
//! @param L2: Segunda coordenada natural del punto de integración.
//! @param L3: Tercera coordenada natural del punto de integración.
//! @param weight: Peso del punto de integración.
void Hammer( int ip, int nip, double& L1, double& L2, double& L3,
             double& weight )
  {
    if ( ip<1 || ip>nip )
      {
	std::cerr << "wrong integration point number:" << ip <<
                     " of " << nip << " available";
      }

   switch ( nip )
     {
       case  1:
         L1 = L2 = L3 = 0.333333333333333;
         weight = 0.5;
         break;
    /*  case  3: switch ( ip )   // alternative scheme degree of precision = 2
                                 // unsuitable for axisymmetric, division by r=0
               {
               case 1: L1 = 0.5; L2 = 0.5; L3 = 0.0;
                       break;
               case 2: L1 = 0.5; L2 = 0.0; L3 = 0.5;
                       break;
               case 3: L1 = 0.0; L2 = 0.5; L3 = 0.5;
                       break;
               }
               weight = 0.166666666666667;   // 1.0/6.0;
               break; */
       case  3:
         switch ( ip )    // alternative scheme  degree of precision = 2
           {
           case 1: 
             L1 = 0.166666666666667; L2 = 0.166666666666667; L3 = 0.666666666666667;
             break;
           case 2:
             L1 = 0.666666666666667; L2 = 0.166666666666667; L3 = 0.166666666666667;
             break;
           case 3:
             L1 = 0.166666666666667; L2 = 0.666666666666667; L3 = 0.166666666666667;
             break;
           }
           weight = 0.166666666666667;   // 1.0/6.0;
           break;
       case  4:
         switch ( ip )
           {
           case 1:
             L1 = L2 = L3 = 0.333333333333333;  // 1.0/3.0;
             weight =  -0.28125;   // -9.0/32.0;
             break;
           case 2:
             L1 = 0.6; L2 = L3 = 0.2;
             weight =  0.260416666666667;   // 25.0/96.0;
             break;
           case 3:
             L2 = 0.6; L1 = L3 = 0.2;
             weight =  0.260416666666667;   // 25.0/96.0;
             break;
           case 4:
             L1 = L2 = 0.2; L3 = 0.6;
             weight =  0.260416666666667;   //25.0/96.0;
             break;
           }
               break;
       case  7:
         switch ( ip )   // degree of precision = 5
           {
           case 1:
             L1 = L2 = 0.1012865073235; L3 = 0.7974269853531;
             weight = 0.0629695902724;
             break;
           case 2:
             L1 = 0.7974269853531; L2 = L3 = 0.1012865073235;
             weight = 0.0629695902724;
             break;
           case 3: L1 = L3 = 0.1012865073235; L2 = 0.7974269853531;
             weight = 0.0629695902724;
             break;
           case 4: L1 = L3 = 0.4701420641051; L2 = 0.0597158717898;
             weight =  0.0661970763943;
             break;
           case 5:
             L1 = L2 = 0.4701420641051; L3 = 0.0597158717898;
             weight =  0.0661970763943;
             break;
           case 6:
             L2 = L3 = 0.4701420641051; L1 = 0.0597158717898;
             weight =  0.0661970763943;
             break;
           case 7:
             L1 = L2 = L3 = 0.3333333333333;
             weight = 0.1125;
             break;
           }
         break;
       default:
         {
	   std::cerr << "wrong nr of integration points: " << nip;
         }
     }
  }
//! @brief Constructor por defecto.
PtosIntegracion::PtosIntegracion()
  {
    nr_of_intpt = 0;
    intpts = NULL;
  }

//! @brief Constructor.
//!
//! @param nr: Número de puntos de integración.
PtosIntegracion::PtosIntegracion( int nr )
  {
    nr_of_intpt = nr;
    intpts = new pto_int[nr];
  }

//! @brief Constructor de copia.
PtosIntegracion::PtosIntegracion( const PtosIntegracion& intlocs )
  {
    nr_of_intpt = intlocs.nr_of_intpt;
    if( nr_of_intpt == 0 )
      {
        intpts = NULL;
        return;
      }
    intpts = new pto_int[nr_of_intpt];
    for ( int ip=0; ip<nr_of_intpt; ip++ )
      {
        intpts[ip] = intlocs.intpts[ip];
      }
  }

//! @brief Destructor.
PtosIntegracion::~PtosIntegracion()
  { if ( intpts != NULL ) delete [] intpts; }

//! @brief Establece el número de puntos de integración.
void PtosIntegracion::set_nr_intpt( int nr )
  {
    if ( intpts != NULL ) delete [] intpts;
    nr_of_intpt = nr;
    intpts = new pto_int[nr];
  }

//! @brief Devuelve el número de puntos de integración.
int PtosIntegracion::get_nr_intpt() const
  { return nr_of_intpt; }
//! @brief Asigna las coordenadas naturales coor y el peso wght al punto
//! de integración cuyo índice se pasa como parámetro.
void PtosIntegracion::set_values( int ip,const m_double &coor,const double &wght)
  {
    if( ip < 1 || ip > nr_of_intpt )
      {
        std::cerr << "wrong integration point number: " << ip << std::endl;
        std::cerr << "should be between 1 and " << nr_of_intpt;
      }
    intpts[ip-1].nat_coord = coor;
    intpts[ip-1].weight = wght;
  }
//! @brief Devuelve las coordenadas naturales del punto de integración cuyo índice se pasa como parámetro.
m_double PtosIntegracion::get_coor(int ip) const
  { return ( intpts[ip-1].nat_coord ); }

//! @brief Devuelve el peso del punto de integración cuyo índice se pasa como parámetro.
double PtosIntegracion::get_weight(int ip) const
  { return ( intpts[ip-1].weight ); }
