
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "ledinfo_led_pulsing_wrapper.h"

// inner classes

// Extra includes


#include <cctype>
#include <cstring>



template <class T>
static const char *typeNameOf(const T &t)
{
    const char *typeName =  typeid(t).name();
    auto size = std::strlen(typeName);
#if defined(Q_CC_MSVC) // MSVC: "class QPaintDevice * __ptr64"
    if (auto lastStar = strchr(typeName, '*')) {
        // MSVC: "class QPaintDevice * __ptr64"
        while (*--lastStar == ' ') {
        }
        size = lastStar - typeName + 1;
    }
#else // g++, Clang: "QPaintDevice *" -> "P12QPaintDevice"
    if (size > 2 && typeName[0] == 'P' && std::isdigit(typeName[1])) {
        ++typeName;
        --size;
    }
#endif
    char *result = new char[size + 1];
    result[size] = '\0';
    memcpy(result, typeName, size);
    return result;
}


// Target ---------------------------------------------------------

extern "C" {
static int
Sbk_LedInfo_Led_Pulsing_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::LedInfo::Led::Pulsing >()))
        return -1;

    ::LedInfo::Led::Pulsing *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0, 0, 0, 0, 0, 0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 6) {
        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Pulsing(): too many arguments");
        return -1;
    }

    if (!PyArg_ParseTuple(args, "|OOOOOO:Pulsing", &(pyArgs[0]), &(pyArgs[1]), &(pyArgs[2]), &(pyArgs[3]), &(pyArgs[4]), &(pyArgs[5])))
        return -1;


    // Overloaded function decisor
    // 0: Pulsing::Pulsing(LedInfo::Led::Pulsing)
    // 1: Pulsing::Pulsing(uint16_t,uint16_t,uint16_t,uint16_t,uint8_t,uint8_t)
    if (numArgs == 0) {
        overloadId = 1; // Pulsing(uint16_t,uint16_t,uint16_t,uint16_t,uint8_t,uint8_t)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 1; // Pulsing(uint16_t,uint16_t,uint16_t,uint16_t,uint8_t,uint8_t)
        } else if ((pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[1])))) {
            if (numArgs == 2) {
                overloadId = 1; // Pulsing(uint16_t,uint16_t,uint16_t,uint16_t,uint8_t,uint8_t)
            } else if ((pythonToCpp[2] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[2])))) {
                if (numArgs == 3) {
                    overloadId = 1; // Pulsing(uint16_t,uint16_t,uint16_t,uint16_t,uint8_t,uint8_t)
                } else if ((pythonToCpp[3] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[3])))) {
                    if (numArgs == 4) {
                        overloadId = 1; // Pulsing(uint16_t,uint16_t,uint16_t,uint16_t,uint8_t,uint8_t)
                    } else if ((pythonToCpp[4] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), (pyArgs[4])))) {
                        if (numArgs == 5) {
                            overloadId = 1; // Pulsing(uint16_t,uint16_t,uint16_t,uint16_t,uint8_t,uint8_t)
                        } else if ((pythonToCpp[5] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), (pyArgs[5])))) {
                            overloadId = 1; // Pulsing(uint16_t,uint16_t,uint16_t,uint16_t,uint8_t,uint8_t)
                        }
                    }
                }
            }
        }
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX]), (pyArgs[0])))) {
        overloadId = 0; // Pulsing(LedInfo::Led::Pulsing)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_LedInfo_Led_Pulsing_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Pulsing(const LedInfo::Led::Pulsing & Pulsing)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led::Pulsing cppArg0_local;
            ::LedInfo::Led::Pulsing *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Pulsing(LedInfo::Led::Pulsing)
                cptr = new ::LedInfo::Led::Pulsing(*cppArg0);
            }
            break;
        }
        case 1: // Pulsing(uint16_t _fadeInDuration, uint16_t _fadeOutDuration, uint16_t _maxValueDuration, uint16_t _minValueDuration, uint8_t _maxValue, uint8_t _minValue)
        {
            if (kwds) {
                PyObject *keyName = nullptr;
                PyObject *value = nullptr;
                keyName = Py_BuildValue("s","_fadeInDuration");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[0]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Pulsing(): got multiple values for keyword argument '_fadeInDuration'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[0] = value;
                        if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[0]))))
                            goto Sbk_LedInfo_Led_Pulsing_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_fadeOutDuration");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[1]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Pulsing(): got multiple values for keyword argument '_fadeOutDuration'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[1] = value;
                        if (!(pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[1]))))
                            goto Sbk_LedInfo_Led_Pulsing_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_maxValueDuration");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[2]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Pulsing(): got multiple values for keyword argument '_maxValueDuration'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[2] = value;
                        if (!(pythonToCpp[2] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[2]))))
                            goto Sbk_LedInfo_Led_Pulsing_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_minValueDuration");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[3]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Pulsing(): got multiple values for keyword argument '_minValueDuration'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[3] = value;
                        if (!(pythonToCpp[3] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[3]))))
                            goto Sbk_LedInfo_Led_Pulsing_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_maxValue");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[4]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Pulsing(): got multiple values for keyword argument '_maxValue'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[4] = value;
                        if (!(pythonToCpp[4] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), (pyArgs[4]))))
                            goto Sbk_LedInfo_Led_Pulsing_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_minValue");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[5]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Pulsing(): got multiple values for keyword argument '_minValue'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[5] = value;
                        if (!(pythonToCpp[5] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), (pyArgs[5]))))
                            goto Sbk_LedInfo_Led_Pulsing_Init_TypeError;
                    }
                }
            }
            ::uint16_t cppArg0 = 900;
            if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);
            ::uint16_t cppArg1 = 900;
            if (pythonToCpp[1]) pythonToCpp[1](pyArgs[1], &cppArg1);
            ::uint16_t cppArg2 = 100;
            if (pythonToCpp[2]) pythonToCpp[2](pyArgs[2], &cppArg2);
            ::uint16_t cppArg3 = 100;
            if (pythonToCpp[3]) pythonToCpp[3](pyArgs[3], &cppArg3);
            ::uint8_t cppArg4 = 255;
            if (pythonToCpp[4]) pythonToCpp[4](pyArgs[4], &cppArg4);
            ::uint8_t cppArg5 = 0;
            if (pythonToCpp[5]) pythonToCpp[5](pyArgs[5], &cppArg5);

            if (!PyErr_Occurred()) {
                // Pulsing(uint16_t,uint16_t,uint16_t,uint16_t,uint8_t,uint8_t)
                cptr = new ::LedInfo::Led::Pulsing(cppArg0, cppArg1, cppArg2, cppArg3, cppArg4, cppArg5);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::LedInfo::Led::Pulsing >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_LedInfo_Led_Pulsing_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_LedInfo_Led_Pulsing_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.LedInfo.Led.Pulsing");
        return -1;
}

static PyObject *Sbk_LedInfo_Led_PulsingFunc_getFadeInDuration(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::Pulsing *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getFadeInDuration()const
            uint16_t cppResult = const_cast<const ::LedInfo::Led::Pulsing *>(cppSelf)->getFadeInDuration();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_PulsingFunc_getFadeOutDuration(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::Pulsing *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getFadeOutDuration()const
            uint16_t cppResult = const_cast<const ::LedInfo::Led::Pulsing *>(cppSelf)->getFadeOutDuration();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_PulsingFunc_getMaxValue(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::Pulsing *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getMaxValue()const
            uint8_t cppResult = const_cast<const ::LedInfo::Led::Pulsing *>(cppSelf)->getMaxValue();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_PulsingFunc_getMaxValueDuration(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::Pulsing *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getMaxValueDuration()const
            uint16_t cppResult = const_cast<const ::LedInfo::Led::Pulsing *>(cppSelf)->getMaxValueDuration();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_PulsingFunc_getMinValue(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::Pulsing *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getMinValue()const
            uint8_t cppResult = const_cast<const ::LedInfo::Led::Pulsing *>(cppSelf)->getMinValue();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_PulsingFunc_getMinValueDuration(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::Pulsing *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getMinValueDuration()const
            uint16_t cppResult = const_cast<const ::LedInfo::Led::Pulsing *>(cppSelf)->getMinValueDuration();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_Pulsing___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::LedInfo::Led::Pulsing *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_LedInfo_Led_Pulsing_methods[] = {
    {"getFadeInDuration", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_PulsingFunc_getFadeInDuration), METH_NOARGS},
    {"getFadeOutDuration", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_PulsingFunc_getFadeOutDuration), METH_NOARGS},
    {"getMaxValue", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_PulsingFunc_getMaxValue), METH_NOARGS},
    {"getMaxValueDuration", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_PulsingFunc_getMaxValueDuration), METH_NOARGS},
    {"getMinValue", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_PulsingFunc_getMinValue), METH_NOARGS},
    {"getMinValueDuration", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_PulsingFunc_getMinValueDuration), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_Pulsing___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_LedInfo_Led_Pulsing_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_LedInfo_Led_Pulsing_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_LedInfo_Led_Pulsing_Type = nullptr;
static SbkObjectType *Sbk_LedInfo_Led_Pulsing_TypeF(void)
{
    return _Sbk_LedInfo_Led_Pulsing_Type;
}

static PyType_Slot Sbk_LedInfo_Led_Pulsing_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_LedInfo_Led_Pulsing_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_LedInfo_Led_Pulsing_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_LedInfo_Led_Pulsing_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_LedInfo_Led_Pulsing_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_LedInfo_Led_Pulsing_spec = {
    "1:UPLS.LedInfo.Led.Pulsing",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_LedInfo_Led_Pulsing_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Pulsing_PythonToCpp_Pulsing_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_LedInfo_Led_Pulsing_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Pulsing_PythonToCpp_Pulsing_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_Pulsing_TypeF())))
        return Pulsing_PythonToCpp_Pulsing_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Pulsing_PTR_CppToPython_Pulsing(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::LedInfo::Led::Pulsing *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_LedInfo_Led_Pulsing_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Pulsing_COPY_CppToPython_Pulsing(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_LedInfo_Led_Pulsing_TypeF(), new ::LedInfo::Led::Pulsing(*reinterpret_cast<const ::LedInfo::Led::Pulsing *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Pulsing_PythonToCpp_Pulsing_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led::Pulsing *>(cppOut) = *reinterpret_cast< ::LedInfo::Led::Pulsing *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Pulsing_PythonToCpp_Pulsing_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_Pulsing_TypeF())))
        return Pulsing_PythonToCpp_Pulsing_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *LedInfo_Led_Pulsing_SignatureStrings[] = {
    "1:UPLS.LedInfo.Led.Pulsing(self,Pulsing:UPLS.LedInfo.Led.Pulsing)",
    "0:UPLS.LedInfo.Led.Pulsing(self,_fadeInDuration:uint16_t=900,_fadeOutDuration:uint16_t=900,_maxValueDuration:uint16_t=100,_minValueDuration:uint16_t=100,_maxValue:uint8_t=255,_minValue:uint8_t=0)",
    "UPLS.LedInfo.Led.Pulsing.getFadeInDuration(self)->uint16_t",
    "UPLS.LedInfo.Led.Pulsing.getFadeOutDuration(self)->uint16_t",
    "UPLS.LedInfo.Led.Pulsing.getMaxValue(self)->uint8_t",
    "UPLS.LedInfo.Led.Pulsing.getMaxValueDuration(self)->uint16_t",
    "UPLS.LedInfo.Led.Pulsing.getMinValue(self)->uint8_t",
    "UPLS.LedInfo.Led.Pulsing.getMinValueDuration(self)->uint16_t",
    "UPLS.LedInfo.Led.Pulsing.__copy__()",
    nullptr}; // Sentinel

void init_LedInfo_Led_Pulsing(PyObject *enclosingClass)
{
    _Sbk_LedInfo_Led_Pulsing_Type = Shiboken::ObjectType::introduceWrapperType(
        enclosingClass,
        "Pulsing",
        "LedInfo::Led::Pulsing",
        &Sbk_LedInfo_Led_Pulsing_spec,
        LedInfo_Led_Pulsing_SignatureStrings,
        &Shiboken::callCppDestructor< ::LedInfo::Led::Pulsing >,
        0,
        0,
        Shiboken::ObjectType::WrapperFlags::InnerClass    );
    
    SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_Pulsing_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_LedInfo_Led_Pulsing_TypeF(),
        Pulsing_PythonToCpp_Pulsing_PTR,
        is_Pulsing_PythonToCpp_Pulsing_PTR_Convertible,
        Pulsing_PTR_CppToPython_Pulsing,
        Pulsing_COPY_CppToPython_Pulsing);

    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Pulsing");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Pulsing*");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Pulsing&");
    Shiboken::Conversions::registerConverterName(converter, "Led::Pulsing");
    Shiboken::Conversions::registerConverterName(converter, "Led::Pulsing*");
    Shiboken::Conversions::registerConverterName(converter, "Led::Pulsing&");
    Shiboken::Conversions::registerConverterName(converter, "Pulsing");
    Shiboken::Conversions::registerConverterName(converter, "Pulsing*");
    Shiboken::Conversions::registerConverterName(converter, "Pulsing&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::LedInfo::Led::Pulsing).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Pulsing_PythonToCpp_Pulsing_COPY,
        is_Pulsing_PythonToCpp_Pulsing_COPY_Convertible);


}
