#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "Python.h"
#include "numpy/arrayobject.h"
#include <cmath>
//#include <iostream>

// Compute the p-norm of a NumPy array
static PyObject *
norm( PyObject *self, PyObject *args ) {

  PyObject *arg1;
  PyArrayObject *arr;
  double p;           // exponent
  double result = 0;
  import_array();
  
  if( !PyArg_ParseTuple(args,"O!d", &PyArray_Type, &arg1, &p) ) return NULL;

  // import_array();
  arr = (PyArrayObject*)PyArray_FROM_OTF(arg1,NPY_DOUBLE,NPY_ARRAY_C_CONTIGUOUS);

  if( arr == NULL ) return NULL;

  // get number of dimensions
//  int ndim = PyArray_NDIM(arr);

  npy_intp size = PyArray_SIZE(arr);
  NpyIter *in_iter = NpyIter_New(arr,NPY_ITER_READONLY,NPY_KEEPORDER,NPY_NO_CASTING,NULL);

  double **data_ptr = (double **)NpyIter_GetDataPtrArray( in_iter );
  NpyIter_Deallocate(in_iter);

//  std::cout << "Number of dimensions = " << ndim << std::endl;
//  std::cout << "Number of elements = " << size << std::endl;
 
  for( npy_intp i=0; i<size; ++i ) { 
//    std::cout << data_ptr[0][i] << std::endl;
    result += std::pow(data_ptr[0][i],p);
  }

  return PyFloat_FromDouble(std::pow(result,1.0/p));

}

static char norm_doc[] = 
  "norm(x,p) : Compute the p-norm of x\n";

static PyMethodDef numerics_methods[] = {
  {"norm",(PyCFunction)norm,METH_VARARGS,norm_doc},
  {NULL,NULL}
};

static struct PyModuleDef numerics_module = {
  PyModuleDef_HEAD_INIT,
  "norm",
  norm_doc,
  -1,
  numerics_methods
};

PyMODINIT_FUNC
PyInit_numerics(void) {
  return PyModule_Create(&numerics_module);
}

   



