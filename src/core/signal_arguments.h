#ifndef SIGNAL_ARGUMENTS_H
#define SIGNAL_ARGUMENTS_H

#include <Python.h>

struct SignalArguments {
    PyObject *pyArgs = nullptr;
};

#endif //SIGNAL_ARGUMENTS_H
