# -*- coding: utf-8 -*-
# Macros útiles para teoría de bloques (ver Goodman & Shi, Block theory and its application to rock engineering 1985)

'''Devuelve el plano de buzamiento definido por:
   alpha: Ángulo de buzamiento.
   beta: Dirección del buzamiento.
   p: Punto por el que pasa el plano.'''
def calcPlanoBuzamiento(alpha,beta,pos3d p):
  A= math.sin(alpha)*sin(beta)
  B= math.sin(alpha)*cos(beta)
  C= math.cos(alpha)
  D= -(A*p.x+B*p.y+C*p.z)

  retval= ecuacion_general([A,B,C,D])
  return retval

def procesaAnguloPoliedrico(nmbAng,nmbTunel):
  {
    print "\n\\subsection{Ángulo poliédrico: ",nmbAng,"}\n"
    print "\n\\begin{alltt}\n"
    if(not(JPvacio))
        \then
          {
            if(contieneEjeTunel)
                \then
                  {
                    print "  Contiene al eje del túnel= Si.\n"
                    print "\\end{alltt}\n"
                  }
                else:
                  {
                    print "  Contiene al eje del túnel= No.\n"
                    print "  Vectores externos:\n"
                    print "    I1= ",I1," I2= ",I2,"\n"
                    print "    angI1= ",rad2deg(angI1),"\n"
                    print "    angI2= ",rad2deg(angI2),"\n"
                    print "    angI1I2= ",rad2deg(angI1I2),"\n"
                    if(angI1I2>=PI)
                        \then
                          {
                            print "  La cuña abarca toda la sección (bloque inamovible).\n"
                            print "\\end{alltt}\n"
                          }
                        else:
                          {
                            print "  Pirámide:\n"
                            print "    puntos de tangencia= ",ptsTang,"\n"
                            print "    cúspide= ",p3,"\n"
                            \psplot
                              {
                                \pageSize{"letter"}
                                \open{nmbTunel+nmbAng+".ps"}
                                \fspace{0.0, 0.0, 30.0, 30.0} # specify user coor system
                                \lineWidth{0.1} # line thickness in user coordinates
                                \penColorName{"blue"}  # path will be drawn in red
                                \erase{} # erase Plotter's graphics display
                                \seccionTunel
                                  {
                                    nv= getNumVertices
                                    ptPlot= at(1)
                                    \moveTo{ptPlot.x,ptPlot.y}
                                    i= 0
                                    \for
                                      {
                                        \inicio{i=2}} \continua{i<=nv} \incremento{\set{i=i+1}
                                        \bucle
                                           {
                                             ptPlot= at(i)
                                             \cont{ptPlot.x,ptPlot.y}
                                           }
                                      }
                                    ptPlot= at(1)
                                    \cont{ptPlot.x,ptPlot.y}
                                  }
                                \penColorName{"red"}  # path will be drawn in red
                                \moveTo{p1.x,p1.y}
                                \cont{p3.x,p3.y}
                                \cont{p2.x,p2.y}
                                \flush{}
                                \close{}
                                print "\\end{alltt}\n"
                                print "\\begin{figure}\n"
                                print "  \\centering\n"
                                print "  \\includegraphics[width=40mm]{",nmbTunel+nmbAng+".ps","}\n"
                                print "  \\caption{",caption+" Pirámide "+ nmbAng,"}\n"
                                print "\\end{figure}\n"
                              }
                          }
                      }
                  }
              }
          }
        else:
          {
            print "  El bloque generado es inamovible.\n"
            print "\\end{alltt}\n"
          }
      }
  }

'''Calcula los puntos de tangencia de los vectores
   externos con la sección.'''
def calcPuntosTangencia(nmbSeccion,vector2d vt1,vector2d vt2):
  {
    retval= 
    \nmbSeccion{retval= getPosTangAprox(vt1)}
    pt0= 
    pt0= retval.at(1)
    \retval{\clear{}}
    \nmbSeccion{retval= getPosTangAprox(vt2)}
    pt1= 
    pt1= retval.at(1)
    \retval{\clear{}}
    \retval{\inserta{pt0} \inserta{pt1}}
    return retval
  }
