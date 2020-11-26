
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "ledinfo_led_fadeinfadeout_wrapper.h"

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
Sbk_LedInfo_Led_FadeInFadeOut_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::LedInfo::Led::FadeInFadeOut >()))
        return -1;

    ::LedInfo::Led::FadeInFadeOut *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0, 0, 0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 3) {
        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.FadeInFadeOut(): too many arguments");
        return -1;
    }

    if (!PyArg_ParseTuple(args, "|OOO:FadeInFadeOut", &(pyArgs[0]), &(pyArgs[1]), &(pyArgs[2])))
        return -1;


    // Overloaded function decisor
    // 0: FadeInFadeOut::FadeInFadeOut(LedInfo::Led::FadeInFadeOut)
    // 1: FadeInFadeOut::FadeInFadeOut(uint8_t,uint16_t,uint16_t)
    if (numArgs == 0) {
        overloadId = 1; // FadeInFadeOut(uint8_t,uint16_t,uint16_t)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 1; // FadeInFadeOut(uint8_t,uint16_t,uint16_t)
        } else if ((pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[1])))) {
            if (numArgs == 2) {
                overloadId = 1; // FadeInFadeOut(uint8_t,uint16_t,uint16_t)
            } else if ((pythonToCpp[2] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[2])))) {
                overloadId = 1; // FadeInFadeOut(uint8_t,uint16_t,uint16_t)
            }
        }
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX]), (pyArgs[0])))) {
        overloadId = 0; // FadeInFadeOut(LedInfo::Led::FadeInFadeOut)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_LedInfo_Led_FadeInFadeOut_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // FadeInFadeOut(const LedInfo::Led::FadeInFadeOut & FadeInFadeOut)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led::FadeInFadeOut cppArg0_local;
            ::LedInfo::Led::FadeInFadeOut *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // FadeInFadeOut(LedInfo::Led::FadeInFadeOut)
                cptr = new ::LedInfo::Led::FadeInFadeOut(*cppArg0);
            }
            break;
        }
        case 1: // FadeInFadeOut(uint8_t _brightness, uint16_t _fadeInDuration, uint16_t _fadeOutDuration)
        {
            if (kwds) {
                PyObject *keyName = nullptr;
                PyObject *value = nullptr;
                keyName = Py_BuildValue("s","_brightness");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[0]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.FadeInFadeOut(): got multiple values for keyword argument '_brightness'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[0] = value;
                        if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), (pyArgs[0]))))
                            goto Sbk_LedInfo_Led_FadeInFadeOut_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_fadeInDuration");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[1]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.FadeInFadeOut(): got multiple values for keyword argument '_fadeInDuration'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[1] = value;
                        if (!(pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[1]))))
                            goto Sbk_LedInfo_Led_FadeInFadeOut_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_fadeOutDuration");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[2]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.LedInfo.Led.FadeInFadeOut(): got multiple values for keyword argument '_fadeOutDuration'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[2] = value;
                        if (!(pythonToCpp[2] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[2]))))
                            goto Sbk_LedInfo_Led_FadeInFadeOut_Init_TypeError;
                    }
                }
            }
            ::uint8_t cppArg0 = 255;
            if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);
            ::uint16_t cppArg1 = 1000;
            if (pythonToCpp[1]) pythonToCpp[1](pyArgs[1], &cppArg1);
            ::uint16_t cppArg2 = 1000;
            if (pythonToCpp[2]) pythonToCpp[2](pyArgs[2], &cppArg2);

            if (!PyErr_Occurred()) {
                // FadeInFadeOut(uint8_t,uint16_t,uint16_t)
                cptr = new ::LedInfo::Led::FadeInFadeOut(cppArg0, cppArg1, cppArg2);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::LedInfo::Led::FadeInFadeOut >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_LedInfo_Led_FadeInFadeOut_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_LedInfo_Led_FadeInFadeOut_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.LedInfo.Led.FadeInFadeOut");
        return -1;
}

static PyObject *Sbk_LedInfo_Led_FadeInFadeOutFunc_getBrightness(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::FadeInFadeOut *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getBrightness()const
            uint8_t cppResult = const_cast<const ::LedInfo::Led::FadeInFadeOut *>(cppSelf)->getBrightness();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_FadeInFadeOutFunc_getFadeInDuration(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::FadeInFadeOut *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getFadeInDuration()const
            uint16_t cppResult = const_cast<const ::LedInfo::Led::FadeInFadeOut *>(cppSelf)->getFadeInDuration();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_FadeInFadeOutFunc_getFadeOutDuration(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led::FadeInFadeOut *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getFadeOutDuration()const
            uint16_t cppResult = const_cast<const ::LedInfo::Led::FadeInFadeOut *>(cppSelf)->getFadeOutDuration();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led_FadeInFadeOut___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::LedInfo::Led::FadeInFadeOut *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_LedInfo_Led_FadeInFadeOut_methods[] = {
    {"getBrightness", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_FadeInFadeOutFunc_getBrightness), METH_NOARGS},
    {"getFadeInDuration", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_FadeInFadeOutFunc_getFadeInDuration), METH_NOARGS},
    {"getFadeOutDuration", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_FadeInFadeOutFunc_getFadeOutDuration), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led_FadeInFadeOut___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_LedInfo_Led_FadeInFadeOut_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_LedInfo_Led_FadeInFadeOut_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_LedInfo_Led_FadeInFadeOut_Type = nullptr;
static SbkObjectType *Sbk_LedInfo_Led_FadeInFadeOut_TypeF(void)
{
    return _Sbk_LedInfo_Led_FadeInFadeOut_Type;
}

static PyType_Slot Sbk_LedInfo_Led_FadeInFadeOut_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_LedInfo_Led_FadeInFadeOut_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_LedInfo_Led_FadeInFadeOut_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_LedInfo_Led_FadeInFadeOut_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_LedInfo_Led_FadeInFadeOut_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_LedInfo_Led_FadeInFadeOut_spec = {
    "1:UPLS.LedInfo.Led.FadeInFadeOut",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_LedInfo_Led_FadeInFadeOut_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void FadeInFadeOut_PythonToCpp_FadeInFadeOut_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_LedInfo_Led_FadeInFadeOut_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_FadeInFadeOut_PythonToCpp_FadeInFadeOut_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_FadeInFadeOut_TypeF())))
        return FadeInFadeOut_PythonToCpp_FadeInFadeOut_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *FadeInFadeOut_PTR_CppToPython_FadeInFadeOut(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::LedInfo::Led::FadeInFadeOut *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_LedInfo_Led_FadeInFadeOut_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *FadeInFadeOut_COPY_CppToPython_FadeInFadeOut(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_LedInfo_Led_FadeInFadeOut_TypeF(), new ::LedInfo::Led::FadeInFadeOut(*reinterpret_cast<const ::LedInfo::Led::FadeInFadeOut *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void FadeInFadeOut_PythonToCpp_FadeInFadeOut_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led::FadeInFadeOut *>(cppOut) = *reinterpret_cast< ::LedInfo::Led::FadeInFadeOut *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_FadeInFadeOut_PythonToCpp_FadeInFadeOut_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_FadeInFadeOut_TypeF())))
        return FadeInFadeOut_PythonToCpp_FadeInFadeOut_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *LedInfo_Led_FadeInFadeOut_SignatureStrings[] = {
    "1:UPLS.LedInfo.Led.FadeInFadeOut(self,FadeInFadeOut:UPLS.LedInfo.Led.FadeInFadeOut)",
    "0:UPLS.LedInfo.Led.FadeInFadeOut(self,_brightness:uint8_t=255,_fadeInDuration:uint16_t=1000,_fadeOutDuration:uint16_t=1000)",
    "UPLS.LedInfo.Led.FadeInFadeOut.getBrightness(self)->uint8_t",
    "UPLS.LedInfo.Led.FadeInFadeOut.getFadeInDuration(self)->uint16_t",
    "UPLS.LedInfo.Led.FadeInFadeOut.getFadeOutDuration(self)->uint16_t",
    "UPLS.LedInfo.Led.FadeInFadeOut.__copy__()",
    nullptr}; // Sentinel

void init_LedInfo_Led_FadeInFadeOut(PyObject *enclosingClass)
{
    _Sbk_LedInfo_Led_FadeInFadeOut_Type = Shiboken::ObjectType::introduceWrapperType(
        enclosingClass,
        "FadeInFadeOut",
        "LedInfo::Led::FadeInFadeOut",
        &Sbk_LedInfo_Led_FadeInFadeOut_spec,
        LedInfo_Led_FadeInFadeOut_SignatureStrings,
        &Shiboken::callCppDestructor< ::LedInfo::Led::FadeInFadeOut >,
        0,
        0,
        Shiboken::ObjectType::WrapperFlags::InnerClass    );
    
    SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_FadeInFadeOut_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_LedInfo_Led_FadeInFadeOut_TypeF(),
        FadeInFadeOut_PythonToCpp_FadeInFadeOut_PTR,
        is_FadeInFadeOut_PythonToCpp_FadeInFadeOut_PTR_Convertible,
        FadeInFadeOut_PTR_CppToPython_FadeInFadeOut,
        FadeInFadeOut_COPY_CppToPython_FadeInFadeOut);

    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::FadeInFadeOut");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::FadeInFadeOut*");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::FadeInFadeOut&");
    Shiboken::Conversions::registerConverterName(converter, "Led::FadeInFadeOut");
    Shiboken::Conversions::registerConverterName(converter, "Led::FadeInFadeOut*");
    Shiboken::Conversions::registerConverterName(converter, "Led::FadeInFadeOut&");
    Shiboken::Conversions::registerConverterName(converter, "FadeInFadeOut");
    Shiboken::Conversions::registerConverterName(converter, "FadeInFadeOut*");
    Shiboken::Conversions::registerConverterName(converter, "FadeInFadeOut&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::LedInfo::Led::FadeInFadeOut).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        FadeInFadeOut_PythonToCpp_FadeInFadeOut_COPY,
        is_FadeInFadeOut_PythonToCpp_FadeInFadeOut_COPY_Convertible);


}
