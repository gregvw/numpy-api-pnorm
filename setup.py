import sys
import numpy
from numpy.distutils.core import setup, Extension

if sys.version_info[0] == 3:

  module = Extension('numerics', 
                     sources = ['numerics.cpp'],
                     include_dirs = [numpy.get_include()] )

  setup(name = 'numerics',
        version = '1.0',
        ext_modules=[module])

else: 
    print("This example requires building with Python 3")
