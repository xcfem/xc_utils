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
//EntProp.h

#ifndef ENTPROP_H
#define ENTPROP_H

#include "EntBase.h"
#include <map>
#include <set>
#include <deque>
#include "MapPropVar.h"
#include "EntPropSorter.h"

//! @ingroup NUCLEO
//
//! @brief Objeto capaz de devolver propiedades.
class EntProp: public EntBase
  {
  private:
    EntProp *owner; //! Objeto propietario de ESTE.
  public:
    static bool existe_archivo(const std::string &FileName);
    static bool es_directorio(const std::string &FileName);
  protected:
    MapPropVar params;//!< Contenedor de propiedades y variables.
    friend class BloqueSub;
    mutable const BloqueSub *sub; //!< Objeto que pide a éste la ejecución de un bloque de código.
    void set_sub(const BloqueSub *sub) const; //!< Asigna el puntero a la subrutina.

    friend class PilaLlamadas;
    static std::set<const EntProp *> visitados; //!< Objetos a los que ya se ha solicitado la propiedad.
    static inline bool visitado(const EntProp *tmp)
      { return (visitados.find(tmp) != visitados.end()); }
    static inline void visita(const EntProp *tmp)
      { visitados.insert(tmp); }
    static inline void clear_visitados(void)
      { visitados.clear(); }

    any_const_ptr set_temp_var(const boost::any &, const std::string &) const;

    static int verborrea; //!< Nivel de verborrea.

    static EntPropSorter ent_prop_sorter;

    static std::string nombre_variable(const std::string &str);
    static std::string nombre_propiedad(const std::string &str);

    void err_num_argumentos(std::ostream &os,const size_t &,const std::string &,const std::string &) const;
    void err_tipo_argumento(std::ostream &os,const size_t &,const std::string &,const std::string &,const std::string &,const std::string &) const;
    void err_tipo_devuelto(std::ostream &os,const std::string &,const std::string &,const std::string &,const std::string &) const;

    std::string deref_cmd(const std::string &) const;
    static void nueva_expr(const std::string &nmb,const ExprAlgebra &expr);
    void nueva_expr(const std::string &nmb,const std::string &e);
    static void nueva_var(const std::string &nmb,const double &d);
    static bool eval(const std::string &nmb_var);

    virtual bool interpreta(const std::string &,const int &numValEsperados= -1) const;
    bool interpretaUno(const std::string &) const;

    void print(std::ostream *out_file,const std::string &) const;
   public:
    EntProp(EntProp *owr= NULL);
    EntProp(const EntProp &otro);
    EntProp &operator=(const EntProp &otro);
    static const int &GetNivelVerborrea(void);
    virtual std::string nombre_clase(void) const;
    bool verdadero(const std::string &cond) const;
    inline bool falso(const std::string &cond) const
      { return !verdadero(cond); }
    void clearProps(void);
    any_const_ptr BasicMathFunc(const std::string &cod) const;
    any_const_ptr BasicStrFunc(const std::string &cod) const;
    any_const_ptr BasicBoolFunc(const std::string &cod) const;
    any_const_ptr BasicImageFunc(const std::string &cod) const;
    any_const_ptr BasicGeomFunc(const std::string &cod) const;
    any_const_ptr GetPropLocal(const std::string &cod) const;
    virtual any_const_ptr GetPropPilaLlamadas(const std::string &cod) const= 0;
    any_const_ptr Recall(const std::string &cod) const;
    virtual any_const_ptr GetProp(const std::string &cod) const;
    void set_owner(EntProp *owr);
    EntProp *Owner(void)
      { return owner; }
    const EntProp *Owner(void) const
      { return owner; }

    std::string getPass(const std::string &) const;

    std::deque<boost::any> crea_deque_boost_any(const std::string &str) const;
    std::vector<std::string> crea_vector_string(const std::string &str) const;
    std::vector<char> crea_vector_char(const std::string &str) const;
    std::vector<double> crea_vector_double(const std::string &) const;
    std::vector<int> crea_vector_int(const std::string &) const;
    std::vector<size_t> crea_vector_size_t(const std::string &) const;
    std::vector<ExprAlgebra> crea_vector_expr(const std::string &str) const;

    static inline void set_sorter_cod(const std::string &c)
      { ent_prop_sorter.set_cod(c); }
    static inline bool menor_ent_prop(const EntProp *a,const EntProp *b)
      { return ent_prop_sorter.menor(a,b); }
    static inline bool mayor_ent_prop(const EntProp *a,const EntProp *b)
      { return ent_prop_sorter.mayor(a,b); }

    std::string popString(const std::string &) const;
    double popDouble(const std::string &) const;
    int popInt(const std::string &) const;
    bool popBool(const std::string &) const;
    size_t popSize_t(const std::string &) const;
    std::vector<double> popVectorDouble(const std::string &) const;
    std::vector<int> popVectorInt(const std::string &) const;
    std::vector<std::string> popVectorString(const std::string &) const;
    m_double popMDouble(const std::string &) const;
    m_int popMInt(const std::string &) const;
    m_string popMString(const std::string &) const;
    Pos2d popPos2d(const std::string &) const;
    Vector2d popVector2d(const std::string &) const;
    Segmento2d popSegmento2d(const std::string &) const;
    Circulo2d popCirculo2d(const std::string &) const;
    Poligono2d popPoligono2d(const std::string &) const;
    PoligonoConAgujeros2d popPoligonoConAgujeros2d(const std::string &) const;
    ListaPos2d popListaPos2d(const std::string &) const;
    Polilinea2d popPolilinea2d(const std::string &) const;
    ListaPos3d popListaPos3d(const std::string &) const;
    Pos3d popPos3d(const std::string &) const;
    Vector3d popVector3d(const std::string &) const;
    Segmento3d popSegmento3d(const std::string &) const;
    VDesliz2d popVDesliz2d(const std::string &) const;
    VDesliz3d popVDesliz3d(const std::string &) const;
    VFijo2d popVFijo2d(const std::string &) const;
    VFijo3d popVFijo3d(const std::string &) const;
    SVD3d popSVD3d(const std::string &) const;
    Recta2d popRecta2d(const std::string &) const;
    Recta3d popRecta3d(const std::string &) const;
    Plano3d popPlano3d(const std::string &) const;
    SemiEspacio3d popSemiEspacio3d(const std::string &) const;
    Ref2d3d popRef2d3d(const std::string &) const;

  };

#endif
