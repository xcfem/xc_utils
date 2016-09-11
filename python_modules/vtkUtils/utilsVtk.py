# -*- coding: utf-8 -*-
import vtk
import math

flecha= vtk.vtkArrowSource()
flecha.SetTipLength(0.35)
flecha.SetTipRadius(0.1)
flecha.SetTipResolution(10)
flecha.SetShaftRadius(0.03)
flecha.SetShaftResolution(10)

flechaMapper= vtk.vtkPolyDataMapper()
flechaMapper.SetInput(flecha.GetOutput())

#print "XXX FALTA DEFINIR LA FLECHA DOBLE"
# flechaDoble= vtk.vtkDblArrowSource()
# flechaDoble.SetTipLength(0.35)
# flechaDoble.SetTipRadius(0.1)
# flechaDoble.SetTipResolution(10)
# flechaDoble.SetShaftRadius(0.03)
# flechaDoble.SetShaftResolution(10)

# flechaDobleMapper= vtk.vtkPolyDataMapper()
# flechaDobleMapper.SetInput(flechaDoble)

def parallelTo(actor,vDir):
  nc= len(vDir)
  if(nc!=3):
    print "parallelTo: ", vDir, " wrong dimension (must be 3)."
  else:
    v= [vDir[0],vDir[1],vDir[2]]
    thetaZ= math.degrees(math.atan2(v[1],v[0]));
    actor.RotateZ(thetaZ);
    thetaY= -math.degrees(math.atan2(v[2],math.sqrt((v[0]*v[0])+(v[1]*v[1]))));
    actor.RotateY(thetaY);

def dibujaFlecha(renderer, color, posicion, direccion, escala):
  arrowSource = vtk.vtkArrowSource()
  #arrowSource.SetShaftRadius(0.01)
  #arrowSource.SetTipLength(.9)
  actor= vtk.vtkActor()
  parallelTo(actor,direccion)
  actor.SetPosition(posicion[0],posicion[1],posicion[2])
  actor.SetScale(escala,escala/2,escala/2)
  actor.GetProperty().SetColor(color[0],color[1],color[2])

  mapper = vtk.vtkPolyDataMapper()
  mapper.SetInputConnection(arrowSource.GetOutputPort())
  actor.SetMapper(mapper)
  renderer.AddActor(actor)


def dibujaFlechaDoble(renderer, color, posicion, direccion, escala):
  actor= vtk.vtkActor()
  actor.SetMapper(flechaDobleMapper)
  paraleloA(direccion[0],direccion[1],direccion[2])
  actor.SetPosition(posicion[0],posicion[1],posicion[2])
  actor.SetScale(escala,escala/2,escala/2)
  actor.GetProperty().SetColor(color[0],color[1],color[2])
  renderer.AddActor(actor)

