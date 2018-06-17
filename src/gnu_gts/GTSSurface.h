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
//GTSSuface.h
//C++ wrapper para la clase GtsSurface de la biblioteca GTS.

#ifndef GTS_SURFACE_H
#define GTS_SURFACE_H

#include "gts.h"

class GTSVertex;
class GTSFace;
class GTSSurfaceTraverse;
class GTSBBoxTree;
class GTSGraph;
class GTSSplit;
class Vector3d;
class TriangleMap;

class GTSSurface
  {
    GtsSurface *s;

    bool borrar;

    void crea(void);
    void borra(void);

  protected:
    GtsSurface const *get_const_ptr(void) const
      { return s; }
    GtsSurface *get_ptr(void)
      { return s; }
    GTSSurface(GtsSurface *ptr);
  public:
    friend class GTSVertex;
    friend class GTSSurfaceTraverse;
    friend class GTSSurfaceIntersection;
    friend class GTSGraph;

    GTSSurface(void);
    GTSSurface(const GTSSurface &otra);
    GTSSurface &operator=(const GTSSurface &otra);

    int Read(GtsFile *fp);
    void Write(FILE *fp);
    void WriteOogl(FILE *fp);

    void PrintStats(FILE* fp) const;
    bool IsClosed(void) const;
    bool IsOpen(void) const;
    bool IsOrientable(void) const;
    GTSSurface selfIntersecting(void) const;
    bool Vacia(void) const;
    bool CheckSelfIntersection(bool verbose) const;

    void appendFace(GTSFace &f);
    void removeFace(GTSFace &f);
    void Merge(const GTSSurface &otra);

    guint GetNumVertices(void) const;
    guint GetNumAristas(void) const;
    guint GetNumCaras(void) const;
    GTSSurfaceTraverse Begin(void) const;
    GTSGraph Graph(void) const;
    void ForEachVertex(GtsFunc func,gpointer data) const;
    void ForEachEdge(GtsFunc func,gpointer data) const;
    void ForEachFace(GtsFunc func,gpointer data) const;

    GNode *BBoxTree(void) const;

    double GaussianCurvature(const GTSVertex &v) const;
    Vector3d MeanCurvatureNormal(const GTSVertex &v) const;
    void PrincipalCurvatures(const GTSVertex &v,double &k1,double &k2) const;
    void PrincipalDirections(const GTSVertex &v,Vector3d &e1,Vector3d &e2) const;

    double Volume(void) const
      { return gts_surface_volume(s); }
    //! @brief Return the sum of the areas (with sign) of the faces.
    double getArea(void) const
      { return gts_surface_area(s); }

    TriangleMap GetTriangleMap(void) const;

    ~GTSSurface(void);
  };


GTSSurface Union(const GTSSurface &a,const GTSSurface &b,bool check_self_intersection=false,bool verbose=false);
GTSSurface intersection(const GTSSurface &a,const GTSSurface &b,bool check_self_intersection=false,bool verbose=false);
GTSSurface Diferencia(const GTSSurface &a,const GTSSurface &b,bool check_self_intersection=false,bool verbose=false);


#endif
