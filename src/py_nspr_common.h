/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is a Python binding for Network Security Services (NSS).
 *
 * The Initial Developer of the Original Code is Red Hat, Inc.
 *   (Author: John Dennis <jdennis@redhat.com>) 
 * 
 * Portions created by the Initial Developer are Copyright (C) 2008,2009
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above.  If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

//#define DEBUG

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#if PY_VERSION_HEX < 0x02050000 && !defined(PY_SSIZE_T_MIN)
typedef int Py_ssize_t;
#define PY_SSIZE_T_MAX INT_MAX
#define PY_SSIZE_T_MIN INT_MIN
#endif

#define AddIntConstant(c) if (PyModule_AddIntConstant(m, #c, c) < 0) return;

#ifdef DEBUG

#define TraceMessage(_msg)                      \
{                                               \
    printf("%s\n", _msg);                       \
}

#define TraceMethodEnter(_name, _obj)                           \
{                                                               \
    PyObject *repr = NULL;                                      \
    char *repr_str = NULL;                                      \
                                                                \
    if (_obj) {                                                 \
        repr = _obj->ob_type->tp_repr((PyObject *)_obj);        \
        repr_str = PyString_AsString(repr);                     \
    }                                                           \
    printf("%s: %s\n", _name, repr_str);                        \
    Py_XDECREF(repr);                                           \
}

#define TraceMethodLeave(_name, _obj)                           \
{                                                               \
    PyObject *repr = NULL;                                      \
    char *repr_str = NULL;                                      \
                                                                \
    if (_obj) {                                                 \
        repr = _obj->ob_type->tp_repr((PyObject *)_obj);        \
        repr_str = PyString_AsString(repr);                     \
    }                                                           \
    printf("%s: %s\n", _name, repr_str);                        \
    Py_XDECREF(repr);                                           \
}

#define TraceObjNewEnter(_name, _tp)            \
{                                               \
    PyTypeObject *tp = _tp;                     \
    if (tp != NULL)                             \
        printf("%s %s\n", _name, tp->tp_name);  \
    else                                        \
        printf("%s\n", _name);                  \
}


#define TraceObjNewLeave(_name, _obj)                                   \
{                                                                       \
    PyObject *repr = NULL;                                              \
                                                                        \
    if ((repr = _obj->ob_type->tp_repr((PyObject *)_obj))) {            \
        printf("%s: returns %s\n", _name, PyString_AsString(repr));     \
        Py_DECREF(repr);                                                \
    }                                                                   \
}

#else
#define TraceMessage(_msg)
#define TraceMethodEnter(_name, _obj)
#define TraceMethodLeave(_name, _obj)
#define TraceObjNewEnter(_name, _tp)
#define TraceObjNewLeave(_name, _obj)
#endif