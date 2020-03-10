# -*- coding: utf-8 -*-
#!/usr/bin/env python

# Copyright (C) 2009-2012  Luis C. Pérez Tato
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
#
# See https://github.com/lcpt/xc_utils or email : l.pereztato@gmail.com
#
from __future__ import print_function
from distutils.core import setup, sys
from distutils.sysconfig import get_python_lib

myPrefix = sys.prefix
if len (sys.argv) > 2:
    i = 0
    for o in sys.argv:
        if o.startswith ("--prefix"):
            if o == "--prefix":
                if len (sys.argv) >= i:
                    myPrefix = sys.argv[i + 1]
                sys.argv.remove (prefix)
            elif o.startswith ("--prefix=") and len (o[9:]):
                myPrefix = o[9:]
            sys.argv.remove (o)
        i += 1
if not myPrefix and "PREFIX" in os.environ:
    myPrefix = os.environ["PREFIX"]
if not myPrefix or not len (myPrefix):
    myPrefix = "/usr/local"

pth_to_libs= get_python_lib(1,0,myPrefix)
print(pth_to_libs)

setup(name='LcmdModules',
      version='0.12.0',
      author='Luis C. Pérez Tato',
      packages=['load_combination_utils','geom_utils','geotechnics','geotechnics.foundations','geotechnics.tuneles','misc_utils','sqliteUtils','latex','vtkUtils'],
      data_files=[(pth_to_libs, ['extensions/xc_base.so','extensions/loadCombinations.so','extensions/geom.so','extensions/xcGnuGts.so'])]
     )
