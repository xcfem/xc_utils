#!/bin/sh
mkdir -p ./extensions
ln_geom=./extensions/geom.so
if [ ! -h $ln_geom ]; then
  echo "Making $ln_geom symlink."
  ln -si ../lib/libgeom.so $ln_geom
fi
ln_loadComb=./extensions/loadCombinations.so
if [ ! -h $ln_loadComb ]; then
  echo "Making $ln_loadComb symlink."
  ln -si ../lib/libloadCombinations.so $ln_loadComb
fi
ln_xcBase=./extensions/xc_base.so
if [ ! -h $ln_xcBase ]; then
  echo "Making $ln_xcBase symlink."
  ln -si ../lib/libxc_base.so $ln_xcBase
fi
sudo python setup.py install --prefix=/usr/local
