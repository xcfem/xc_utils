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
//LabelContainer.h

#ifndef LABELCONTAINER_H
#define LABELCONTAINER_H

#include <string>
#include <set>
#include "bimap.h"
#include <iostream>


class DiccionarioEtiquetas
  {
    friend class LabelContainer;
  private:
    typedef bidirectional_map<int,std::string>::type bm_type;
    bm_type bm;

    int get_indice_etiqueta(const std::string &e) const;
    const std::string &get_etiqueta_indice(const int &i) const;
    int insert(const std::string &e);
  public:
    size_t getNumEtiquetas(void) const;

    const std::string &operator()(const int &) const;
    int operator()(const std::string &) const;
  
    void Print(std::ostream &os) const;
  };

std::ostream &operator<<(std::ostream &os,const DiccionarioEtiquetas &lc);

//! @brief Contenedor de etiquetas para objetos.
class LabelContainer
  {
    static DiccionarioEtiquetas dic;
    std::set<int> etiquetas;
    bool hasEtiqueta(const int &i) const;

  public:
    LabelContainer(void);
    LabelContainer &operator+=(const LabelContainer &);
    LabelContainer &operator-=(const LabelContainer &);
    LabelContainer &operator*=(const LabelContainer &);

    void extend(const LabelContainer &);

    const std::set<int> &getIdsEtiquetas(void) const;

    static const DiccionarioEtiquetas &getDiccionario(void);
    size_t getNumEtiquetas(void) const;
    int addEtiqueta(const std::string &e);
    int removeEtiqueta(const std::string &e);
    bool hasEtiqueta(const std::string &e) const;
    void clear(void);

    void Print(std::ostream &os) const;
    friend LabelContainer operator+(const LabelContainer &,const LabelContainer &);
    friend LabelContainer operator-(const LabelContainer &,const LabelContainer &);
    friend LabelContainer operator*(const LabelContainer &,const LabelContainer &);

  };

std::ostream &operator<<(std::ostream &os,const LabelContainer &lc);
LabelContainer operator+(const LabelContainer &,const LabelContainer &);
LabelContainer operator-(const LabelContainer &,const LabelContainer &);
LabelContainer operator*(const LabelContainer &,const LabelContainer &);

#endif
