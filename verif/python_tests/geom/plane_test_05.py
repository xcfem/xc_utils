import xc_base
import geom
p0=geom.Pos3d(0.000331586,0,0)
# p1=geom.Pos3d(0.000331586,100,0)
# p2=geom.Pos3d(-0.301719,0,100)
p1=geom.Pos3d(0.000331586,1,0)
p2=geom.Pos3d(-0.00268892,0,1)

plane=geom.Plane3d(p0,p1,p2)
normal=plane.getNormal()
YZplane= geom.Plane3d(geom.Pos3d(0,0,0),geom.Pos3d(0,100,0),geom.Pos3d(0,0,100))
angle= plane.getAnguloPlano3d(YZplane)
yzTrace= plane.getYZTrace()

print 'normal: ', normal*(1.0/1e4)
print 'angle= ', angle
print 'trace= ', yzTrace
