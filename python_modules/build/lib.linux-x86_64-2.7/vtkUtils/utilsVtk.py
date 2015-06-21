import vtk

flecha= vtk.vtkArrowSource()
flecha.SetTipLength(0.35)
flecha.SetTipRadius(0.1)
flecha.SetTipResolution(10)
flecha.SetShaftRadius(0.03)
flecha.SetShaftResolution(10)

flechaMapper= vtk.vtkPolyDataMapper()
flechaMapper.SetInput(flecha.GetOutput())

print "XXX FALTA DEFINIR LA FLECHA DOBLE"
# flechaDoble= vtk.vtkDblArrowSource()
# flechaDoble.SetTipLength(0.35)
# flechaDoble.SetTipRadius(0.1)
# flechaDoble.SetTipResolution(10)
# flechaDoble.SetShaftRadius(0.03)
# flechaDoble.SetShaftResolution(10)

# flechaDobleMapper= vtk.vtkPolyDataMapper()
# flechaDobleMapper.SetInput(flechaDoble)


def dibujaFlecha(nmbActor,nmbRenderer, color, posicion, direccion, escala):
   nmbActor= vtk.vtkActor()
   nmbActor.SetMapper(flechaMapper)
   nmbActor.paraleloA(direccion[0],direccion[1],direccion[2])
   nmbActor.SetPosition(posicion[0],posicion[1],posicion[2])
   nmbActor.SetScale(escala,escala/2,escala/2)
   nmbActor.GetProperty().SetColor(color[0],color[1],color[2])
   nmbRenderer.AddActor(nmbActor)


def dibujaFlechaDoble(actor,renderer, color, posicion, direccion, escala):
  actor= vtk.vtkActor()
  actor.SetMapper(flechaDobleMapper)
  paraleloA(direccion[0],direccion[1],direccion[2])
  actor.SetPosition(posicion[0],posicion[1],posicion[2])
  actor.SetScale(escala,escala/2,escala/2)
  actor.GetProperty().SetColor(color[0],color[1],color[2])
  renderer.AddActor(actor)

