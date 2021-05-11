#ifndef SIGNAL_ARGUMENTS_H
#define SIGNAL_ARGUMENTS_H

#include <Python.h>

struct SignalArguments {
    PyObject *pyArgs = nullptr;
};

class PythonSignalArguments {
  public:
    static SignalArguments GetStringSignalArgument(const std::string text) {
        PyObject *pListObject = PyList_New(0);
        if (PyList_Append(pListObject, Py_BuildValue("s", text.c_str())) == -1) {
            PyErr_Print();
        }
        return SignalArguments{.pyArgs = pListObject};
    }
};

#endif //SIGNAL_ARGUMENTS_H
