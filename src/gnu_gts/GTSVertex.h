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
//GTSVertex.h
//C++ wraper para la clase GtsVertex de la biblioteca GTS.

#ifndef GTS_VERTEX_H
#define GTS_VERTEX_H

#include "gts.h"

class GTSSurface;
class Vector3d;
class Pos3d;
class GTSSplit;

class GTSVertex
  {
    GtsVertex *vt;

    bool borrar;

    void crea(const double &x,const double &y,const double &z);
    void borra(void);

  public:

    friend class GTSEdge;
    friend class GTSSplit;

    GTSVertex(const double &x,const double &y,const double &z);
    GTSVertex(GtsVertex *pvt);
    GTSVertex(const GTSVertex &otro);
    GTSVertex &operator=(const GTSVertex &otra);

    Pos3d Posicion(void) const;

    double GaussianCurvature(const GTSSurface &surf) const;
    Vector3d MeanCurvatureNormal(const GTSSurface &surf) const;
    void PrincipalCurvatures(const GTSSurface &surf,double &k1,double &k2) const;
    void PrincipalDirections(const GTSSurface &surf,Vector3d &e1,Vector3d &e2) const;

    GTSSplit GetSplit(const GTSVertex &v1,const GTSVertex &v2);

    ~GTSVertex(void);
  };


#endif
