/* Secret Labs' Regular Expression Engine
 *
 * regular expression matching engine
 *
 * partial history:
 * 1999-10-24 fl   created (based on existing template matcher code)
 * 2000-03-06 fl   first alpha, sort of
 * 2000-08-01 fl   fixes for 1.6b1
 * 2000-08-07 fl   use PyOS_CheckStack() if available
 * 2000-09-20 fl   added expand method
 * 2001-03-20 fl   lots of fixes for 2.1b2
 * 2001-04-15 fl   export copyright as Python attribute, not global
 * 2001-04-28 fl   added __copy__ methods (work in progress)
 * 2001-05-14 fl   fixes for 1.5.2 compatibility
 * 2001-07-01 fl   added BIGCHARSET support (from Martin von Loewis)
 * 2001-10-18 fl   fixed group reset issue (from Matthew Mueller)
 * 2001-10-20 fl   added split primitive; reenable unicode for 1.6/2.0/2.1
 * 2001-10-21 fl   added sub/subn primitive
 * 2001-10-24 fl   added finditer primitive (for 2.2 only)
 * 2001-12-07 fl   fixed memory leak in sub/subn (Guido van Rossum)
 * 2002-11-09 fl   fixed empty sub/subn return type
 * 2003-04-18 mvl  fully support 4-byte codes
 * 2003-10-17 gn   implemented non recursive scheme
 * 2009-07-26 mrab completely re-designed matcher code
 * 2011-11-18 mrab added support for PEP 393 strings
 *
 * Copyright (c) 1997-2001 by Secret Labs AB.  All rights reserved.
 *
 * This version of the SRE library can be redistributed under CNRI's
 * Python 1.6 license.  For any other use, please contact Secret Labs
 * AB (info@pythonware.com).
 *
 * Portions of this engine have been developed in cooperation with
 * CNRI.  Hewlett-Packard provided funding for 1.6 integration and
 * other compatibility work.
 */

/* #define VERBOSE */

#define RE_MEMORY_LIMIT 0x40000000

#if defined(VERBOSE)
#define TRACE(X) printf X;
#else
#define TRACE(X)
#endif

#define PY_SSIZE_T_CLEAN

#include "Python.h"
#include "structmember.h" /* offsetof */
#include <ctype.h>
#include "pyport.h"
#include "pythread.h"

#if PY_VERSION_HEX < 0x03070000
/* Issue 29943: PySlice_GetIndicesEx change broke ABI in 3.5 and 3.6 branches
 */
#if defined(PySlice_GetIndicesEx) && !defined(PYPY_VERSION)
#undef PySlice_GetIndicesEx
#endif
#endif


PyObject *test(PyObject *self, PyObject *args) {
    return PyLong_FromLong(42);
}

/* The table of the module's functions. */
static PyMethodDef _functions[] = {
   {"test", (PyCFunction)test, METH_NOARGS},
    {NULL, NULL}
};

/* The module definition. */
static struct PyModuleDef regex_module = {
    PyModuleDef_HEAD_INIT,
    "_regex",
    NULL,
    -1,
    _functions,
    NULL,
    NULL,
    NULL,
    NULL
};

/* Initialises the module. */
PyMODINIT_FUNC PyInit__regex(void) {
    return PyModule_Create(&regex_module);
}
