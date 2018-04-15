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
//VertexMap.cc

#include "VertexMap.h"
#include "xc_utils/src/geom/pos_vec/Vector3d.h"
#include "xc_utils/src/geom/pos_vec/ListaPos3d.h"
#include <stack>

VerticesArista::VerticesArista(const size_t &i,const size_t &j)
  : v0(i), v1(j) { assert(i!=j); }

void VerticesArista::Swap(void)
  { std::swap(v0,v1); }

bool VerticesArista::comparteVertices(const VerticesArista &otra) const
  {
    bool retval= false;
    if((*this)==otra)
      retval= false;
    else if((v0== otra.v1) && (v1== otra.v0))
      retval= true;
    return retval;
  }

bool operator==(const VerticesArista &a,const VerticesArista &b)
  { return ((a.v0==b.v0) && (a.v1==b.v1)); }

VerticesCara::VerticesCara(void)
  : visitada(false) {}

void VerticesCara::setVisitada(const bool &b)
  { visitada= b; }

const bool &VerticesCara::yaVisitada(void) const
  { return visitada; }

void VerticesCara::Swap(void)
  { reverse(); }



//! @brief Return las posiciones de los vertices de la cara.
ListaPos3d VerticesCara::getPosVertices(const std::vector<Pos3d> &vertices) const
  {
    ListaPos3d retval;
    for(const_iterator i=begin();i!=end();i++)
      retval.appendPoint(vertices[*i]);
    return retval;
  }

//! @brief Return el centroide de la cara.
Pos3d VerticesCara::getCentroide(const std::vector<Pos3d> &vertices) const
  { return getPosVertices(vertices).Cdg();  }

//! @brief Return las aristas de la cara.
std::list<VerticesArista> VerticesCara::getAristas(void) const
  {
    std::list<VerticesArista> retval;
    const_iterator i= begin();
    const_iterator j= i; j++;
    for(;j!=end();j++)
      {
        retval.push_back(VerticesArista(*i,*j));
        i=j;
      }
    retval.push_back(VerticesArista(*i,*begin()));
    return retval;
  }

//! @brief Return true if la cara contiene la arista
//! que se pasa como parámetro.
bool VerticesCara::tieneArista(const VerticesArista &arista) const
  {
    bool retval= false;
    const_iterator i= std::find(begin(),end(),arista.getVI());
    if(i!=end())
      {
        const_iterator j= std::find(begin(),end(),arista.getVJ());
        if(j!=end())
          {
            const_iterator k= i;k++;
            if(k==j)
              retval= true;
            else
              {
                k= i; k--;
                if(k==j)
                  retval= true;
              }
          }
      }
    return retval;
  }

//! @brief Return true if la cara contiene la arista
//! que se pasa como parámetro y está orientada igual.
bool VerticesCara::tieneAristaOrientada(const VerticesArista &arista) const
  {
    bool retval= false;
    const_iterator i= std::find(begin(),end(),arista.getVI());
    if(i!=end())
      {
        const_iterator j= std::find(begin(),end(),arista.getVJ());
        if(j!=end())
          {
            const_iterator k= i;k++;
            if(k==j)
              retval= true;
          }
      }
    return retval;
  }

//! @brief Return las caras que comparten una arista con ésta.
std::deque<VerticesCara> VerticesCara::compartenArista(const std::deque<VerticesCara> &caras) const
  {
    std::deque<VerticesCara> retval;
    std::list<VerticesArista> aristas= getAristas();
    for(std::list<VerticesArista>::const_iterator i= aristas.begin();i!=aristas.end();i++)
      {
        const VerticesArista &arista= *i;
        for(std::deque<VerticesCara>::const_iterator j= caras.begin();j!=caras.end();j++)
          if(*j!=*this)
            if(j->tieneArista(arista))
              retval.push_back(*j);
      }
    return retval;
  }

//! @brief Imprime los índices de los vértices.
void VerticesCara::Print(std::ostream &os) const
  {
    for(const_iterator j=begin();j!=end();j++)
      os << " " << *j;
  }

std::ostream &operator<<(std::ostream &os,const VerticesCara &vc)
  {
    vc.Print(os);
    return os;
  }

//! @brief Constructor.
VertexMap::VertexMap(const TripletMap<Pos3d> &vertexMap)
  : vertices(vertexMap.size()) 
  {
    //Colocamos los vértices.
    TripletMap<size_t> indices;
    size_t conta= 0;
    for(TripletMap<Pos3d>::const_iterator i=vertexMap.begin();i!=vertexMap.end();i++,conta++)
      {
        Triplete t= (*i).first;
        indices[t]= conta;
        vertices[conta]= (*i).second;
      }

    std::set<size_t> planos;
    //Obtenemos los planos que contienen las caras.
    for(TripletMap<Pos3d>::const_iterator i=vertexMap.begin();i!=vertexMap.end();i++)
      {
        Triplete t= (*i).first;
        planos.insert(t.get<0>());
        planos.insert(t.get<1>());
        planos.insert(t.get<2>());
      }

    //Obtenemos las caras contenidas en cada plano.
    for(std::set<size_t>::const_iterator i=planos.begin();i!=planos.end();i++)
      {
        const size_t indice= *i;
        VerticesCara indicesCara;
        for(TripletMap<Pos3d>::const_iterator j=vertexMap.begin();j!=vertexMap.end();j++)
          {
            Triplete t= (*j).first;
            const size_t indiceVertice= indices[t];
            if(t.get<0>()==indice) indicesCara.push_back(indiceVertice);
            if(t.get<1>()==indice) indicesCara.push_back(indiceVertice);
            if(t.get<2>()==indice) indicesCara.push_back(indiceVertice);
          }
        assert(indicesCara.size()>=3);
        caras.push_back(indicesCara);
        indicesCara.clear();
      }
    //Hacemos consistente la ordenación de vértices en las caras.
    makeConsistent();
  }

//! @brief Return los vértices.
const std::vector<Pos3d> &VertexMap::getVertices(void) const
  { return vertices; }

//! @brief Return el número de vertices.
size_t VertexMap::getNumVertices(void) const
  { return vertices.size(); }

//! @brief Return el número de caras.
size_t VertexMap::getNumCaras(void) const
  { return caras.size(); }

//! @brief Return the cara cuyo índice se pasa como parámetro.
const VerticesCara &VertexMap::getCara(const size_t &i) const
  { return caras[i]; }

//! @brief Return las caras.
const std::deque<VerticesCara > &VertexMap::getCaras(void) const
  { return caras; }

//! @brief Return el centroide.
Pos3d VertexMap::getCentroide(void) const
  {
    const GEOM_FT sz= getNumVertices();
    Vector3d tmp;
    for(std::vector<Pos3d>::const_iterator i=vertices.begin();i!=vertices.end();i++)
      tmp= tmp + (*i).VectorPos();
    return Pos3d(tmp.x()/sz,tmp.y()/sz,tmp.z()/sz);
  }

std::deque<VerticesCara *> VertexMap::tienenArista(const VerticesArista &arista)
  {
    std::deque<VerticesCara *> retval;
    for(std::deque<VerticesCara>::iterator i= caras.begin();i!=caras.end();i++)
      if(i->tieneArista(arista))
        retval.push_back(&(*i));
    return retval;
  }

void VertexMap::makeConsistent(void)
  {
    for(std::deque<VerticesCara >::iterator i=caras.begin();i!=caras.end();i++)
      (*i).setVisitada(false);
    
    std::stack<VerticesCara> pilaCaras;
    std::deque<VerticesCara >::iterator i= caras.begin();
    pilaCaras.push(*i);
    i->setVisitada(true);

    while(!pilaCaras.empty())
      {
        VerticesCara f= pilaCaras.top();
        pilaCaras.pop();
        const std::list<VerticesArista> aristas= f.getAristas();
        for(std::list<VerticesArista>::const_iterator i= aristas.begin();i!=aristas.end();i++)
          {
            std::deque<VerticesCara *> adyacentes= tienenArista(*i);
            for(std::deque<VerticesCara *>::iterator j= adyacentes.begin();j!=adyacentes.end();j++)
              if(!((*j)->yaVisitada()))
                {
                  if((*j)->tieneAristaOrientada(*i))
                    (*j)->Swap();
                  (*j)->setVisitada(true);
                  pilaCaras.push(*(*j));
                }
          }
      }
  }

void VertexMap::Print(std::ostream &os) const
  {
    os << "vertices:" << std::endl;
    for(std::vector<Pos3d>::const_iterator i=vertices.begin();i!=vertices.end();i++)
      os << *i << std::endl;
    os << "caras:" << std::endl;
    for(std::deque<VerticesCara >::const_iterator i=caras.begin();i!=caras.end();i++)
      { os << *i << std::endl; }
  }

std::ostream &operator<<(std::ostream &os,const VertexMap &vm)
  {
    vm.Print(os);
    return os;
  }

//! @brief Constructor.
BuildFromVertexMap::BuildFromVertexMap(const TripletMap<Pos3d> &v)
      :vertex_map(v) {}

//! @brief Operador ().
void BuildFromVertexMap::operator()(Poliedro3d::HalfedgeDS &hds)
  {
    // Postcondition: `hds' is a valid polyhedral surface.
    CGAL::Polyhedron_incremental_builder_3<Poliedro3d::HalfedgeDS> B( hds, true);
    const std::vector<Pos3d> &vertices= vertex_map.getVertices();
    const size_t numVertices= vertices.size();
    const size_t numCaras= vertex_map.getNumCaras();
     
    B.begin_surface(numVertices,numCaras);
    //Agregamos vértices.
    typedef Poliedro3d::HalfedgeDS::Vertex Vertex;
    typedef Vertex::Point Point;
    for(std::vector<Pos3d>::const_iterator i=vertices.begin();i!=vertices.end();i++)
      B.add_vertex(Point((*i).ToCGAL()));

    const std::deque<VerticesCara> &caras= vertex_map.getCaras();
    for(std::deque<VerticesCara>::const_iterator i=caras.begin();i!=caras.end();i++)
      {
        B.begin_facet();
        const VerticesCara &cara= *i;
        for(VerticesCara::const_iterator j=cara.begin();j!=cara.end();j++)
          B.add_vertex_to_facet(*j);
        B.end_facet();
      }
    B.end_surface();
  }
