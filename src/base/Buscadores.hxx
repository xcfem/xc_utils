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
//Buscadores.hxx


//XXX Esta clase deberá desaparecer (sustituyéndola por
// un puntero al contenedor en el que se quiere buscar
// como hacen en OpenSees).
#ifndef BUSCADORES_HXX
#define BUSCADORES_HXX

#include <map>
#include <string>

class BuscadorPtros
  {
  public:
    virtual void const *Busca(const std::string &clave) const= 0;
    virtual void *Busca(const std::string &clave)= 0;
    virtual ~BuscadorPtros(void) {}
  };

typedef BuscadorPtros* PtrBuscador;

class Buscadores: public std::map<std::string,PtrBuscador>
  {
    PtrBuscador nulo;
  public:
    Buscadores(void);
    PtrBuscador &operator[](const std::string &str);
    const PtrBuscador &operator[](const std::string &str) const;
    void Print(std::ostream &os) const;
  };

#endif
