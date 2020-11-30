
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "ledinfo_led_normal_wrapper.h"

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
Sbk_LedInfo_Led_Normal_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::LedInfo::Led::Normal >()))
        return -1;

    ::LedInfo::Led::Normal *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 1) {
        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Normal(): too many arguments");
        return -1;
    }

    if (!PyArg_ParseTuple(args, "|O:Normal", &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: Normal::Normal(LedInfo::Led::Normal)
    // 1: Normal::Normal(uint8_t)
    if (numArgs == 0) {
        overloadId = 1; // Normal(uint8_t)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), (pyArgs[0])))) {
        overloadId = 1; // Normal(uint8_t)
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX]), (pyArgs[0])))) {
        overloadId = 0; // Normal(LedInfo::Led::Normal)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_LedInfo_Led_Normal_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Normal(const LedInfo::Led::Normal & Normal)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led::Normal cppArg0_local;
            ::LedInfo::Led::Normal *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Normal(LedInfo::Led::Normal)
                cptr = new ::LedInfo::Led::Normal(*cppArg0);
            }
            break;
        }
        case 1: // Normal(uint8_t _brightness)
        {
            if (kwds) {
                PyObject *keyName = nullptr;
                PyObject *value = nullptr;
                keyName = Py_BuildValue("s","_brightness");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[0]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.Normal(): got multiple values for keyword argument '_brightness'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[0] = value;
                        if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), (pyArgs[0]))))
                            goto Sbk_LedInfo_Led_Normal_Init_TypeError;
                    }
                }
            }
            ::uint8_t cppArg0 = 255;
            if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // Normal(uint8_t)
                cptr = new ::LedInfo::Led::Normal(cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::LedInfo::Led::Normal >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_LedInfo_Led_Normal_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_LedInfo_Led_Normal_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.LedInfo.Led.Normal");
        return -1;
}

static PyObject *Sbk_LedInfo_Led_NormalFunc_getBrightness(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::Normal *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getBrightness()const
            uint8_t cppResult = const_cast<const ::LedInfo::Led::Normal *>(cppSelf)->getBrightness();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_Normal___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::LedInfo::Led::Normal *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_LedInfo_Led_Normal_methods[] = {
    {"getBrightness", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_NormalFunc_getBrightness), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_Normal___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_LedInfo_Led_Normal_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_LedInfo_Led_Normal_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_LedInfo_Led_Normal_Type = nullptr;
static SbkObjectType *Sbk_LedInfo_Led_Normal_TypeF(void)
{
    return _Sbk_LedInfo_Led_Normal_Type;
}

static PyType_Slot Sbk_LedInfo_Led_Normal_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_LedInfo_Led_Normal_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_LedInfo_Led_Normal_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_LedInfo_Led_Normal_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_LedInfo_Led_Normal_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_LedInfo_Led_Normal_spec = {
    "1:UPLS.LedInfo.Led.Normal",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_LedInfo_Led_Normal_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Normal_PythonToCpp_Normal_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_LedInfo_Led_Normal_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Normal_PythonToCpp_Normal_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_Normal_TypeF())))
        return Normal_PythonToCpp_Normal_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Normal_PTR_CppToPython_Normal(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::LedInfo::Led::Normal *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_LedInfo_Led_Normal_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Normal_COPY_CppToPython_Normal(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_LedInfo_Led_Normal_TypeF(), new ::LedInfo::Led::Normal(*reinterpret_cast<const ::LedInfo::Led::Normal *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Normal_PythonToCpp_Normal_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led::Normal *>(cppOut) = *reinterpret_cast< ::LedInfo::Led::Normal *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Normal_PythonToCpp_Normal_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_Normal_TypeF())))
        return Normal_PythonToCpp_Normal_COPY;
    return {};
}

// Implicit conversions.
static void uint8_t_PythonToCpp_LedInfo_Led_Normal(PyObject *pyIn, void *cppOut) {
    ::uint8_t cppIn;
    Shiboken::Conversions::pythonToCppCopy(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), pyIn, &cppIn);
    *reinterpret_cast<::LedInfo::Led::Normal *>(cppOut) = ::LedInfo::Led::Normal(cppIn);
}
static PythonToCppFunc is_uint8_t_PythonToCpp_LedInfo_Led_Normal_Convertible(PyObject *pyIn) {
    if (Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), pyIn))
        return uint8_t_PythonToCpp_LedInfo_Led_Normal;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *LedInfo_Led_Normal_SignatureStrings[] = {
    "1:UPLS.LedInfo.Led.Normal(self,Normal:UPLS.LedInfo.Led.Normal)",
    "0:UPLS.LedInfo.Led.Normal(self,_brightness:uint8_t=255)",
    "UPLS.LedInfo.Led.Normal.getBrightness(self)->uint8_t",
    "UPLS.LedInfo.Led.Normal.__copy__()",
    nullptr}; // Sentinel

void init_LedInfo_Led_Normal(PyObject *enclosingClass)
{
    _Sbk_LedInfo_Led_Normal_Type = Shiboken::ObjectType::introduceWrapperType(
        enclosingClass,
        "Normal",
        "LedInfo::Led::Normal",
        &Sbk_LedInfo_Led_Normal_spec,
        LedInfo_Led_Normal_SignatureStrings,
        &Shiboken::callCppDestructor< ::LedInfo::Led::Normal >,
        0,
        0,
        Shiboken::ObjectType::WrapperFlags::InnerClass    );
    
    SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_Normal_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_LedInfo_Led_Normal_TypeF(),
        Normal_PythonToCpp_Normal_PTR,
        is_Normal_PythonToCpp_Normal_PTR_Convertible,
        Normal_PTR_CppToPython_Normal,
        Normal_COPY_CppToPython_Normal);

    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Normal");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Normal*");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Normal&");
    Shiboken::Conversions::registerConverterName(converter, "Led::Normal");
    Shiboken::Conversions::registerConverterName(converter, "Led::Normal*");
    Shiboken::Conversions::registerConverterName(converter, "Led::Normal&");
    Shiboken::Conversions::registerConverterName(converter, "Normal");
    Shiboken::Conversions::registerConverterName(converter, "Normal*");
    Shiboken::Conversions::registerConverterName(converter, "Normal&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::LedInfo::Led::Normal).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Normal_PythonToCpp_Normal_COPY,
        is_Normal_PythonToCpp_Normal_COPY_Convertible);
    // Add implicit conversions to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        uint8_t_PythonToCpp_LedInfo_Led_Normal,
        is_uint8_t_PythonToCpp_LedInfo_Led_Normal_Convertible);


}
