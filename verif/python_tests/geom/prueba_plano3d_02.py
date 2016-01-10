import xc_base
import geom
o=geom.Pos3d(0,0,0)
v=geom.Vector3d(0,0,1)

plano=geom.Plano3d(o,v)
normal=plano.getNormal()
base1=plano.getBase1()
base2=plano.getBase2()
tp=plano.tipo()

if normal.x==0 and normal.y==0 and normal.z==1:
    print "test plano3d 02: ok."
else:
    print "test plano3d 02: ERROR."

