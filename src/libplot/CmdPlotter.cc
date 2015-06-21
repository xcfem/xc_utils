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
//CmdPlotter

#include "CmdPlotter.h"
#include "xc_utils/src/base/CmdStatus.h"
#include "xc_utils/src/base/any_const_ptr.h"
#include "xc_utils/src/base/utils_any.h"


//! @brief Constructor.
CmdPlotter::CmdPlotter(void)
  :plt(NULL), out(NULL) {}

//! @brief Constructor de copia.
CmdPlotter::CmdPlotter(const CmdPlotter &otro)
  :plt(NULL), out(NULL) 
  {
    std::cerr << "Los objetos CmdPlotter no deben copiarse." << std::endl;
  }

//! @brief Operador asignación.
CmdPlotter &CmdPlotter::operator=(const CmdPlotter &otro)
  {
    std::cerr << "Los objetos CmdPlotter no deben asignarse." << std::endl;
    return *this;
  }

void CmdPlotter::libera(void)
  {
    if(plt)
      {
        if(plt->closepl()<0) // close Plotter
          std::cerr << "No se pudo cerrar el plotter\n";
        delete plt;
        plt= NULL;
      }
    if(out)
      {
        out->close();
        delete out;
        out= NULL;
      }
  }

void CmdPlotter::alloc(const std::string &path)
  {
    libera();
    out= new std::ofstream(path.c_str());
    plt= new PSPlotter(std::cin,*out,std::cerr);
  }

//! @brief Lectura del objeto desde archivo.
bool CmdPlotter::procesa_comando(CmdStatus &status)
  {
    const std::string cmd= deref_cmd(status.Cmd());
    const std::string str_error= "(CmdPlotter) Procesando comando: " + cmd;

    if(verborrea>2)
      std::cerr << str_error << std::endl;

    if(cmd == "pageSize")
      {
        const std::string pgsz= interpretaString(status.GetString());
        char *ptr= const_cast<char *>(pgsz.c_str());
        Plotter::parampl("PAGESIZE",ptr);
        return true;
      }
    else if(cmd == "close")
      {
        status.GetBloque(); //Ignora entrada.
        libera();
        return true;
      }
    else if(cmd == "open")
      {
        const std::string fName= interpretaString(status.GetString());
        alloc(fName);
        assert(plt);
        if(plt->openpl()<0) // open Plotter
          std::cerr << "No se pudo abrir el plotter\n";
        return true;
      }
    if(cmd == "flush")
      {
        status.GetBloque(); //Ignora entrada.
        assert(plt);
        plt->flushpl();
        return true;
      }
    else if(cmd == "erase")
      {
        status.GetBloque(); //Ignora entrada.
        assert(plt);
        plt->erase();
        return true;
      }
    else if(cmd == "fspace")
      {
        std::vector<double> tmp= crea_vector_double(status.GetString());
        const int nc= tmp.size(); //No. de valores leídos.
        assert(plt);
        if(nc<4)
	  std::cerr << str_error
                    << "Se esperaban cuatro valores." << std::endl;
        else
          plt->fspace(tmp[0],tmp[1],tmp[2],tmp[3]);
        return true;
      }
    else if(cmd == "box")
      {
        std::vector<double> tmp= crea_vector_double(status.GetString());
        const int nc= tmp.size(); //No. de valores leídos.
        assert(plt);
        if(nc<4)
	  std::cerr << str_error
                    << "Se esperaban cuatro valores." << std::endl;
        else
          plt->fbox(tmp[0],tmp[1],tmp[2],tmp[3]);
        return true;
      }
    else if(cmd == "line")
      {
        std::vector<double> tmp= crea_vector_double(status.GetString());
        const int nc= tmp.size(); //No. de valores leídos.
        assert(plt);
        if(nc<4)
	  std::cerr << str_error
                    << "Se esperaban coordenadas de los extremos." << std::endl;
        else
          plt->fline(tmp[0],tmp[1],tmp[2],tmp[3]);
        return true;
      }
    else if(cmd == "circle")
      {
        std::vector<double> tmp= crea_vector_double(status.GetString());
        const int nc= tmp.size(); //No. de valores leídos.
        assert(plt);
        if(nc<3)
	  std::cerr << str_error
                    << "Se esperaban coordendadas del centro y radio." << std::endl;
        else
          plt->fcircle(tmp[0],tmp[1],tmp[2]);
        return true;
      }
    else if(cmd == "ellipse")
      {
        std::vector<double> tmp= crea_vector_double(status.GetString());
        const int nc= tmp.size(); //No. de valores leídos.
        assert(plt);
        if(nc<5)
	  std::cerr << str_error
                    << "Se esperaban coordendadas del centro, rx, ry y ángulo." << std::endl;
        else
          plt->fellipse(tmp[0],tmp[1],tmp[2],tmp[3],tmp[4]);
        return true;
      }
    else if(cmd == "lineWidth")
      {
        const double w= interpretaDouble(status.GetBloque());
        assert(plt);
        plt->flinewidth(w);
        return true;
      }
    else if(cmd == "penColorName") //Color de la pluma.
      {
        const std::string clr= interpretaString(status.GetBloque());
        assert(plt);
        plt->pencolorname(clr.c_str());
        return true;
      }
    else if(cmd == "penColor") //Color de la pluma.
      {
        std::vector<double> coo= crea_vector_double(status.GetString());
        const int nc= coo.size(); //No. de valores leídos.
        assert(plt);
        if(nc<3)
	  std::cerr << str_error
                    << "Se esperaban tres valores (R,G,B)." << std::endl;
        else
          plt->pencolor(int(coo[0]),int(coo[1]),int(coo[2]));
        return true;
      }
    else if(cmd == "colorName")
      {
        const std::string clr= interpretaString(status.GetBloque());
        assert(plt);
        plt->colorname(clr.c_str());
        return true;
      }
    else if(cmd == "color")
      {
        std::vector<double> coo= crea_vector_double(status.GetString());
        const int nc= coo.size(); //No. de valores leídos.
        assert(plt);
        if(nc<3)
	  std::cerr << str_error
                    << "Se esperaban tres valores (R,G,B)." << std::endl;
        else
          plt->color(int(coo[0]),int(coo[1]),int(coo[2]));
        return true;
      }
    else if(cmd == "fillColorName") //Color de relleno.
      {
        const std::string clr= interpretaString(status.GetBloque());
        assert(plt);
        plt->fillcolorname(clr.c_str());
        return true;
      }
    else if(cmd == "fillColor")
      {
        std::vector<double> coo= crea_vector_double(status.GetString());
        const int nc= coo.size(); //No. de valores leídos.
        assert(plt);
        if(nc<3)
	  std::cerr << str_error
                    << "Se esperaban tres valores (R,G,B)." << std::endl;
        else
          plt->fillcolor(int(coo[0]),int(coo[1]),int(coo[2]));
        return true;
      }
    else if(cmd == "fillMod") //Modo de relleno.
      {
        const std::string mod= interpretaString(status.GetBloque());
        assert(plt);
        plt->fillmod(mod.c_str());
        return true;
      }
    else if(cmd == "fillType")
      {
        const double level= interpretaDouble(status.GetBloque());
        assert(plt);
        plt->filltype(int(level));
        return true;
      }
    else if(cmd == "moveTo") //Posición de la pluma.
      {

        std::vector<double> coo= crea_vector_double(status.GetString());
        const int nc= coo.size(); //No. de valores leídos.
        assert(plt);
        if(nc<2)
	  std::cerr << str_error
                    << "Se esperaban dos coordenadas." << std::endl;
        else
          plt->fmove(coo[0],coo[1]);
        return true;
      }
    else if(cmd == "moveRel") //Posición de la pluma.
      {

        std::vector<double> coo= crea_vector_double(status.GetString());
        const int nc= coo.size(); //No. de valores leídos.
        assert(plt);
        if(nc<2)
	  std::cerr << str_error
                    << "Se esperaban dos coordenadas." << std::endl;
        else
          plt->fmoverel(coo[0],coo[1]);
        return true;
      }
    else if(cmd == "cont")
      {

        std::vector<double> coo= crea_vector_double(status.GetString());
        const int nc= coo.size(); //No. de valores leídos.
        assert(plt);
        if(nc<2)
	  std::cerr << str_error
                    << "Se esperaban dos coordenadas." << std::endl;
        else
          plt->fcont(coo[0],coo[1]);
        return true;
      }
    else if(cmd == "contRel")
      {

        std::vector<double> coo= crea_vector_double(status.GetString());
        const int nc= coo.size(); //No. de valores leídos.
        assert(plt);
        if(nc<2)
	  std::cerr << str_error
                    << "Se esperaban dos coordenadas." << std::endl;
        else
          plt->fcontrel(coo[0],coo[1]);
        return true;
      }
    else if(cmd == "marker")
      {
        std::vector<double> coo= crea_vector_double(status.GetString());
        const int nc= coo.size(); //No. de valores leídos.
        assert(plt);
        if(nc<4)
	  std::cerr << str_error
                    << "Se esperaban dos coordenadas, el tipo y el tamaño." << std::endl;
        else
          plt->fmarker(coo[0],coo[1],int(coo[2]),coo[3]);
        return true;
      }
    else if(cmd == "alabel") //Etiqueta de texto.
      {
        //El primer argumento es la justificación horizontal
        //el segundo es la justificación vertical y el tercero el texto.
        std::vector<boost::any> param= interpretaVectorAny(status.GetString());
        const int nc= param.size(); //No. de valores leídos.
        assert(plt);
        if(nc<3)
	  std::cerr << str_error
                    << "Se esperaban justificacion horizontal y vertical y el texto." << std::endl;
        else
          plt->alabel(convert_to_int(param[0]),convert_to_int(param[1]),convert_to_string(param[2]).c_str());
        return true;
      }    
    else if(cmd == "label") //Etiqueta de texto.
      {
        //El primer argumento es la justificación horizontal
        //el segundo es la justificación vertical y el tercero el texto.
        std::vector<boost::any> param= interpretaVectorAny(status.GetString());
        const int nc= param.size(); //No. de valores leídos.
        assert(plt);
        if(nc<1)
	  std::cerr << str_error
                    << "Se un argumento (el texto)." << std::endl;
        else
          plt->label(convert_to_string(param[0]).c_str());
        return true;
      }    
    else if(cmd == "fontName") //Nombre de la fuente.
      {
        const std::string clr= interpretaString(status.GetBloque());
        assert(plt);
        plt->fontname(clr.c_str());
        return true;
      }
    else if(cmd == "fontSize")
      {
        const double sz= interpretaDouble(status.GetBloque());
        assert(plt);
        plt->ffontsize(sz);
        return true;
      }
    else if(cmd == "textAngle")
      {
        const double a= interpretaDouble(status.GetBloque());
        assert(plt);
        plt->ftextangle(a);
        return true;
      }
    else
      return EntCmd::procesa_comando(status);
  }

//! @brief Destructor.
CmdPlotter::~CmdPlotter(void)
  { libera(); }

//! Devuelve la propiedad del objeto cuyo código se pasa 
//! como parámetro. 
any_const_ptr CmdPlotter::GetProp(const std::string &cod) const 
  {
    if(verborrea>4)
      std::clog << "CmdPlotter::GetProp (" << nombre_clase() << "::GetProp) Buscando propiedad: " << cod << std::endl;
    return EntCmd::GetProp(cod);
  }
