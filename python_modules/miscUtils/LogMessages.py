# -*- coding: utf-8 -*-

''' Show error and log messages. '''

__author__= "Luis C. Pérez Tato (LCPT)"
__cppyright__= "Copyright 2016 LCPT"
__license__= "GPL"
__version__= "3.0"
__email__= "l.pereztato@gmail.com"


import logging

logging.addLevelName( logging.INFO, "\033[1;31m%s\033[1;0m" % logging.getLevelName(logging.INFO))
logging.addLevelName( logging.WARNING, "\033[1;31m%s\033[1;0m" % logging.getLevelName(logging.WARNING))
logging.addLevelName( logging.ERROR, "\033[1;41m%s\033[1;0m" % logging.getLevelName(logging.ERROR))

def log(msg):
  logging.info(msg)

def warning(msg):
  logging.warning(msg)

def error(msg):
  logging.error(msg)


