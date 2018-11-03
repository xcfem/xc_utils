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
//#include <unistd.h>
#include <streambuf>
#include <iostream>

class proto_istreambuf: public std::streambuf
  {
  protected:                                              // 1
    char    d_buffer[1];
    virtual int lee(void) { return 0; }

  public:
    proto_istreambuf()
      {
        setg(d_buffer, d_buffer + 1, d_buffer + 1);     // 2
      }
    int underflow() 
      {
        if(gptr() < egptr())                           // 3
          return *gptr();                             // 4
   
        if (lee() <= 0)               // 5
          return EOF;
    
        setg(d_buffer, d_buffer, d_buffer + 1);         // 6
        return *gptr();
      }
  };

class ifdstreambuf: public proto_istreambuf
  {
  protected:                                              // 1
    int d_fd; //Descriptor de fichero.
    virtual int lee(void)
      { return read(d_fd, d_buffer, 1); }

  public:
    ifdstreambuf(int fd)
      : proto_istreambuf(), d_fd(fd){}
  };

//  Please note the following:

//     * At 1 two data members are defined: they were defined as protected data members so that derived classes (e.g., see section 19.1.2.3) can access them.
//     * At 2 the buffer is set up. In the private section a small array of one character is defined, and setg() will set gptr() equal to egptr(). Since this implies that the buffer is empty, underflow() will be called to refill the buffer.
//     * At 3 and 4 underflow() will first see whether the buffer is really empty. If not, then the character to be retrieved next is returned.
//     * At line 5 the buffer is refilled. If this fails (for whatever reason), EOF is returned. More sophisticated implementations could react more intelligently here, of course.
// * At line 6 the buffer has been refilled, so setg() is called once again to set up streambuf's buffer pointers correctly. 


