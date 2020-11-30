
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "ledinfo_led_blinking_wrapper.h"

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
Sbk_LedInfo_Led_Blinking_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::LedInfo::Led::Blinking >()))
        return -1;

    ::LedInfo::Led::Blinking *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0, 0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 2) {
        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Blinking(): too many arguments");
        return -1;
    }

    if (!PyArg_ParseTuple(args, "|OO:Blinking", &(pyArgs[0]), &(pyArgs[1])))
        return -1;


    // Overloaded function decisor
    // 0: Blinking::Blinking(LedInfo::Led::Blinking)
    // 1: Blinking::Blinking(uint16_t,uint16_t)
    if (numArgs == 0) {
        overloadId = 1; // Blinking(uint16_t,uint16_t)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 1; // Blinking(uint16_t,uint16_t)
        } else if ((pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[1])))) {
            overloadId = 1; // Blinking(uint16_t,uint16_t)
        }
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX]), (pyArgs[0])))) {
        overloadId = 0; // Blinking(LedInfo::Led::Blinking)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_LedInfo_Led_Blinking_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Blinking(const LedInfo::Led::Blinking & Blinking)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led::Blinking cppArg0_local;
            ::LedInfo::Led::Blinking *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Blinking(LedInfo::Led::Blinking)
                cptr = new ::LedInfo::Led::Blinking(*cppArg0);
            }
            break;
        }
        case 1: // Blinking(uint16_t _onDuration, uint16_t _offDuration)
        {
            if (kwds) {
                PyObject *keyName = nullptr;
                PyObject *value = nullptr;
                keyName = Py_BuildValue("s","_onDuration");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[0]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Blinking(): got multiple values for keyword argument '_onDuration'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[0] = value;
                        if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[0]))))
                            goto Sbk_LedInfo_Led_Blinking_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_offDuration");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[1]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Blinking(): got multiple values for keyword argument '_offDuration'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[1] = value;
                        if (!(pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[1]))))
                            goto Sbk_LedInfo_Led_Blinking_Init_TypeError;
                    }
                }
            }
            ::uint16_t cppArg0 = 1000;
            if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);
            ::uint16_t cppArg1 = 1000;
            if (pythonToCpp[1]) pythonToCpp[1](pyArgs[1], &cppArg1);

            if (!PyErr_Occurred()) {
                // Blinking(uint16_t,uint16_t)
                cptr = new ::LedInfo::Led::Blinking(cppArg0, cppArg1);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::LedInfo::Led::Blinking >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_LedInfo_Led_Blinking_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_LedInfo_Led_Blinking_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.LedInfo.Led.Blinking");
        return -1;
}

static PyObject *Sbk_LedInfo_Led_BlinkingFunc_getOffDuration(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::Blinking *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getOffDuration()const
            uint16_t cppResult = const_cast<const ::LedInfo::Led::Blinking *>(cppSelf)->getOffDuration();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_BlinkingFunc_getOnDuration(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::Blinking *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getOnDuration()const
            uint16_t cppResult = const_cast<const ::LedInfo::Led::Blinking *>(cppSelf)->getOnDuration();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_Blinking___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::LedInfo::Led::Blinking *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_LedInfo_Led_Blinking_methods[] = {
    {"getOffDuration", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_BlinkingFunc_getOffDuration), METH_NOARGS},
    {"getOnDuration", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_BlinkingFunc_getOnDuration), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_Blinking___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_LedInfo_Led_Blinking_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_LedInfo_Led_Blinking_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_LedInfo_Led_Blinking_Type = nullptr;
static SbkObjectType *Sbk_LedInfo_Led_Blinking_TypeF(void)
{
    return _Sbk_LedInfo_Led_Blinking_Type;
}

static PyType_Slot Sbk_LedInfo_Led_Blinking_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_LedInfo_Led_Blinking_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_LedInfo_Led_Blinking_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_LedInfo_Led_Blinking_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_LedInfo_Led_Blinking_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_LedInfo_Led_Blinking_spec = {
    "1:UPLS.LedInfo.Led.Blinking",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_LedInfo_Led_Blinking_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Blinking_PythonToCpp_Blinking_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_LedInfo_Led_Blinking_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Blinking_PythonToCpp_Blinking_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_Blinking_TypeF())))
        return Blinking_PythonToCpp_Blinking_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Blinking_PTR_CppToPython_Blinking(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::LedInfo::Led::Blinking *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_LedInfo_Led_Blinking_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Blinking_COPY_CppToPython_Blinking(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_LedInfo_Led_Blinking_TypeF(), new ::LedInfo::Led::Blinking(*reinterpret_cast<const ::LedInfo::Led::Blinking *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Blinking_PythonToCpp_Blinking_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led::Blinking *>(cppOut) = *reinterpret_cast< ::LedInfo::Led::Blinking *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Blinking_PythonToCpp_Blinking_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_Blinking_TypeF())))
        return Blinking_PythonToCpp_Blinking_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *LedInfo_Led_Blinking_SignatureStrings[] = {
    "1:UPLS.LedInfo.Led.Blinking(self,Blinking:UPLS.LedInfo.Led.Blinking)",
    "0:UPLS.LedInfo.Led.Blinking(self,_onDuration:uint16_t=1000,_offDuration:uint16_t=1000)",
    "UPLS.LedInfo.Led.Blinking.getOffDuration(self)->uint16_t",
    "UPLS.LedInfo.Led.Blinking.getOnDuration(self)->uint16_t",
    "UPLS.LedInfo.Led.Blinking.__copy__()",
    nullptr}; // Sentinel

void init_LedInfo_Led_Blinking(PyObject *enclosingClass)
{
    _Sbk_LedInfo_Led_Blinking_Type = Shiboken::ObjectType::introduceWrapperType(
        enclosingClass,
        "Blinking",
        "LedInfo::Led::Blinking",
        &Sbk_LedInfo_Led_Blinking_spec,
        LedInfo_Led_Blinking_SignatureStrings,
        &Shiboken::callCppDestructor< ::LedInfo::Led::Blinking >,
        0,
        0,
        Shiboken::ObjectType::WrapperFlags::InnerClass    );
    
    SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_Blinking_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_LedInfo_Led_Blinking_TypeF(),
        Blinking_PythonToCpp_Blinking_PTR,
        is_Blinking_PythonToCpp_Blinking_PTR_Convertible,
        Blinking_PTR_CppToPython_Blinking,
        Blinking_COPY_CppToPython_Blinking);

    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Blinking");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Blinking*");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Blinking&");
    Shiboken::Conversions::registerConverterName(converter, "Led::Blinking");
    Shiboken::Conversions::registerConverterName(converter, "Led::Blinking*");
    Shiboken::Conversions::registerConverterName(converter, "Led::Blinking&");
    Shiboken::Conversions::registerConverterName(converter, "Blinking");
    Shiboken::Conversions::registerConverterName(converter, "Blinking*");
    Shiboken::Conversions::registerConverterName(converter, "Blinking&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::LedInfo::Led::Blinking).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Blinking_PythonToCpp_Blinking_COPY,
        is_Blinking_PythonToCpp_Blinking_COPY_Convertible);


}
