#!/usr/bin/env python
 
from distutils.core import setup
from distutils.extension import Extension
 
setup(name="PackageName",
    ext_modules=[
        Extension("lmathcpp", ["lmathmodule.cpp"],
        libraries = ["boost_python", "gmp", "mpfr",]
        )
    ])
