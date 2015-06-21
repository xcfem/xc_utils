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
//any_const_ptr.h

#ifndef ANY_CONST_PTR_H
#define ANY_CONST_PTR_H

#include <cstdlib>
#include <cassert>
#include <typeinfo>
#include <boost/any.hpp>

class EntCmd;

//! @ingroup BASE
//
//! @brief this class can point to any copy-constructible value_type.
class any_const_ptr
  {
  public:
    struct table;
  private:
    const void *m_a;
    table *m_t;
    const EntCmd *ptr_ent_cmd;
  public:
    // forward declarations
    template <class T>
    struct functions;

    //! @brief Constructor para puntero a size_t.
    explicit any_const_ptr(size_t *x)
      : m_a(&x), m_t(&functions<size_t>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para string.
    explicit any_const_ptr(std::string *x)
      : m_a(&x), m_t(&functions<std::string>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para puntero a int.
    explicit any_const_ptr(int *x)
      : m_a(x), m_t(&functions<int>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para puntero a long int.
    explicit any_const_ptr(long int *x)
      : m_a(x), m_t(&functions<long int>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para puntero a float.
    explicit any_const_ptr(float *x)
      : m_a(x), m_t(&functions<float>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para puntero a double.
    explicit any_const_ptr(double *x)
      : m_a(x), m_t(&functions<double>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para puntero a long double.
    explicit any_const_ptr(long double *x)
      : m_a(x), m_t(&functions<long double>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para puntero a bool.
    explicit any_const_ptr(bool *x)
      : m_a(x), m_t(&functions<bool>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para puntero a boost::any.
    explicit any_const_ptr(boost::any *x)
      : m_a(x), m_t(&functions<boost::any>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para puntero a vector<boost::any>.
    explicit any_const_ptr(std::vector<boost::any> *x)
      : m_a(x), m_t(&functions<std::vector<boost::any> >::table), ptr_ent_cmd(NULL)
      {}

    //! @brief Constructor.
    template <class T>
    explicit any_const_ptr(T *x)
      : m_a(x), m_t(&functions<T>::table), ptr_ent_cmd(NULL)
      {
        ptr_ent_cmd= dynamic_cast<const EntCmd *>(x);
      }

    //! @brief Constructor para size_t.
    explicit any_const_ptr(size_t &x)
      : m_a(&x), m_t(&functions<size_t>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para string.
    explicit any_const_ptr(std::string &x)
      : m_a(&x), m_t(&functions<std::string>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para int.
    explicit any_const_ptr(int &x)
      : m_a(&x), m_t(&functions<int>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para long int.
    explicit any_const_ptr(long int &x)
      : m_a(&x), m_t(&functions<long int>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para float.
    explicit any_const_ptr(float &x)
      : m_a(&x), m_t(&functions<float>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para double.
    explicit any_const_ptr(double &x)
      : m_a(&x), m_t(&functions<double>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para long double.
    explicit any_const_ptr(long double &x)
      : m_a(&x), m_t(&functions<long double>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para bool.
    explicit any_const_ptr(bool &x)
      : m_a(&x), m_t(&functions<bool>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para boost::any.
    explicit any_const_ptr(boost::any &x)
      : m_a(&x), m_t(&functions<boost::any>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para std::vector<boost::any>.
    explicit any_const_ptr(std::vector<boost::any> &x)
      : m_a(&x), m_t(&functions<std::vector<boost::any> >::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para char.
    explicit any_const_ptr(char &x)
      : m_a(&x), m_t(&functions<char>::table), ptr_ent_cmd(NULL)
      {}

    //! @brief Constructor.
    template <class T>
    explicit any_const_ptr(T &x)
      : m_a(&x), m_t(&functions<T>::table), ptr_ent_cmd(NULL)
      {
        ptr_ent_cmd= dynamic_cast<EntCmd *>(&x);
      }


    //! @brief Constructor de copia.
    any_const_ptr(any_const_ptr &otro)
      : m_a(otro.m_a), m_t(otro.m_t), ptr_ent_cmd(otro.ptr_ent_cmd)
      {}

    //! @brief Constructor para const size_t.
    explicit any_const_ptr(const size_t &x)
      : m_a(&x), m_t(&functions<const size_t>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para const string.
    explicit any_const_ptr(const std::string &x)
      : m_a(&x), m_t(&functions<const std::string>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para const int.
    explicit any_const_ptr(const int &x)
      : m_a(&x), m_t(&functions<const int>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para const long int.
    explicit any_const_ptr(const long int &x)
      : m_a(&x), m_t(&functions<const long int>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para const float.
    explicit any_const_ptr(const float &x)
      : m_a(&x), m_t(&functions<const float>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para const double.
    explicit any_const_ptr(const double &x)
      : m_a(&x), m_t(&functions<const double>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para const long double.
    explicit any_const_ptr(const long double &x)
      : m_a(&x), m_t(&functions<const long double>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para const bool.
    explicit any_const_ptr(const bool &x)
      : m_a(&x), m_t(&functions<const bool>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para const boost::any.
    explicit any_const_ptr(const boost::any &x)
      : m_a(&x), m_t(&functions<const boost::any>::table), ptr_ent_cmd(NULL)
      {}
    //! @brief Constructor para const vector<boost::any>.
    explicit any_const_ptr(const std::vector<boost::any> &x)
      : m_a(&x), m_t(&functions<const std::vector<boost::any> >::table), ptr_ent_cmd(NULL)
      {}

    //! @brief Constructor.
    template <class T>
    explicit any_const_ptr(const T &x)
      : m_a(&x), m_t(&functions<T>::table)
      {
        ptr_ent_cmd= dynamic_cast<const EntCmd *>(&x);
      }

    //! @brief Constructor de copia.
    any_const_ptr(const any_const_ptr &otro)
      : m_a(otro.m_a), m_t(otro.m_t), ptr_ent_cmd(otro.ptr_ent_cmd)
      {}

    //! @brief Constructor.
    any_const_ptr(void)
      : m_a(NULL), m_t(NULL), ptr_ent_cmd(NULL)
      {}

    //! @brief Operador de asignación.
    any_const_ptr &operator=(const any_const_ptr &otro)
      {
        m_a= otro.m_a;
        m_t= otro.m_t;
        ptr_ent_cmd= otro.ptr_ent_cmd;
        return *this;
      }
    bool isEntCmd(void) const
      { return (ptr_ent_cmd!=NULL); }
    const EntCmd *getEntCmdPtr(void) const
      { return ptr_ent_cmd; }
    //!@brief Devuelve la información de tipo.
    const std::type_info &GetType(void) const
      { return m_t->GetType(m_a); }
    //!@brief Devuelve la información de tipo (compatibilidad boost::any).
    inline const std::type_info &type(void) const
      { return GetType(); }

    template<typename ValueType>
    bool is_type(void) const
      { return (typeid(ValueType) == GetType()); }

    //! @brief Devuelve un puntero a la referencia almacenada.
    template<typename ValueType>
    const ValueType* PtrCast(void) const
      {
        const ValueType *retval= NULL;
/*         if(!(typeid(ValueType) == GetType())) */
/*           std::cerr << "any_ptr::PtrCast; tipos incompatibles." << std::endl; */
/*         else */
        if(typeid(ValueType) == GetType())
          retval= static_cast<const ValueType*>(m_a);
        return retval;
      }

    template<typename ValueType>
    static const ValueType* cast(const any_const_ptr &ptr)
      { return ptr.PtrCast<ValueType>(); }

    bool empty(void) const
      { return (m_a == NULL); }

    // Function table type
    // order is important, must match all other lists of functions
    struct table
      {
        const std::type_info &(*GetType)(const void *);
      };

    // For a given referenced type T, generates functions for the
    // function table and a static instance of the table.
    template<class T>
    struct functions
      {
        static typename any_const_ptr::table table;
        static const std::type_info& GetType(const void *p)
          { return typeid(T); }
      };
  };

template<class T>
typename any_const_ptr::table any_const_ptr::functions<T>::table=
  {
    &any_const_ptr::template functions<T>::GetType
  };

template<typename ValueType>
bool is_type(const any_const_ptr &ptr)
  { return ptr.is_type<ValueType>(); }


//! @brief Devuelve verdadero si los objetos son del mismo tipo.
inline bool same_type(const any_const_ptr &a,const any_const_ptr &b)
  { return (a.type() == b.type()); }

template<class ValueType>
const ValueType *any_const_ptr_cast(const any_const_ptr &ptr)
  { return any_const_ptr::cast<ValueType>(ptr); }

#endif
