
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "ledinfo_led_wrapper.h"

// inner classes
#include "ledinfo_led_fadeinfadeout_wrapper.h"
#include "ledinfo_led_normal_wrapper.h"
#include "ledinfo_led_blinking_wrapper.h"
#include "ledinfo_led_pulsing_wrapper.h"

// Extra includes
#include <packet/packet.h>


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
Sbk_LedInfo_Led_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::LedInfo::Led >()))
        return -1;

    ::LedInfo::Led *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "Led", 0, 1, &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: Led::Led()
    // 1: Led::Led(LedInfo::Led::Blinking)
    // 2: Led::Led(LedInfo::Led::FadeInFadeOut)
    // 3: Led::Led(LedInfo::Led::Normal)
    // 4: Led::Led(LedInfo::Led::Pulsing)
    // 5: Led::Led(LedInfo::Led)
    if (numArgs == 0) {
        overloadId = 0; // Led()
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppValueConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX]), (pyArgs[0])))) {
        overloadId = 4; // Led(LedInfo::Led::Pulsing)
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppValueConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX]), (pyArgs[0])))) {
        overloadId = 3; // Led(LedInfo::Led::Normal)
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppValueConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX]), (pyArgs[0])))) {
        overloadId = 2; // Led(LedInfo::Led::FadeInFadeOut)
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppValueConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX]), (pyArgs[0])))) {
        overloadId = 1; // Led(LedInfo::Led::Blinking)
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX]), (pyArgs[0])))) {
        overloadId = 5; // Led(LedInfo::Led)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_LedInfo_Led_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Led()
        {

            if (!PyErr_Occurred()) {
                // Led()
                cptr = new ::LedInfo::Led();
            }
            break;
        }
        case 1: // Led(LedInfo::Led::Blinking _blinking)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led::Blinking cppArg0 = ::LedInfo::Led::Blinking(::uint16_t(), ::uint16_t());
            pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // Led(LedInfo::Led::Blinking)
                cptr = new ::LedInfo::Led(cppArg0);
            }
            break;
        }
        case 2: // Led(LedInfo::Led::FadeInFadeOut _fadeInOut)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led::FadeInFadeOut cppArg0;
            pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // Led(LedInfo::Led::FadeInFadeOut)
                cptr = new ::LedInfo::Led(cppArg0);
            }
            break;
        }
        case 3: // Led(LedInfo::Led::Normal _normal)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led::Normal cppArg0 = ::LedInfo::Led::Normal(::uint8_t());
            pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // Led(LedInfo::Led::Normal)
                cptr = new ::LedInfo::Led(cppArg0);
            }
            break;
        }
        case 4: // Led(LedInfo::Led::Pulsing _pulsing)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led::Pulsing cppArg0;
            pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // Led(LedInfo::Led::Pulsing)
                cptr = new ::LedInfo::Led(cppArg0);
            }
            break;
        }
        case 5: // Led(const LedInfo::Led & Led)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led cppArg0_local;
            ::LedInfo::Led *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Led(LedInfo::Led)
                cptr = new ::LedInfo::Led(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::LedInfo::Led >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_LedInfo_Led_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_LedInfo_Led_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.LedInfo.Led");
        return -1;
}

static PyObject *Sbk_LedInfo_LedFunc_getBlinking(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getBlinking()const
            LedInfo::Led::Blinking cppResult = const_cast<const ::LedInfo::Led *>(cppSelf)->getBlinking();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_LedFunc_getCurrent_value(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getCurrent_value()const
            uint8_t cppResult = const_cast<const ::LedInfo::Led *>(cppSelf)->getCurrent_value();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_LedFunc_getEnabled(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getEnabled()const
            bool cppResult = const_cast<const ::LedInfo::Led *>(cppSelf)->getEnabled();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_LedFunc_getFadeInFadeOutSettings(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getFadeInFadeOutSettings()const
            LedInfo::Led::FadeInFadeOut cppResult = const_cast<const ::LedInfo::Led *>(cppSelf)->getFadeInFadeOutSettings();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_LedFunc_getMode(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getMode()const
            LedInfo::Led::Mode cppResult = LedInfo::Led::Mode(const_cast<const ::LedInfo::Led *>(cppSelf)->getMode());
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_LedFunc_getNormalSettings(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getNormalSettings()const
            LedInfo::Led::Normal cppResult = const_cast<const ::LedInfo::Led *>(cppSelf)->getNormalSettings();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_LedFunc_getPulsingSettings(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getPulsingSettings()const
            LedInfo::Led::Pulsing cppResult = const_cast<const ::LedInfo::Led *>(cppSelf)->getPulsingSettings();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo_Led___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_LedInfo_Led_methods[] = {
    {"getBlinking", reinterpret_cast<PyCFunction>(Sbk_LedInfo_LedFunc_getBlinking), METH_NOARGS},
    {"getCurrent_value", reinterpret_cast<PyCFunction>(Sbk_LedInfo_LedFunc_getCurrent_value), METH_NOARGS},
    {"getEnabled", reinterpret_cast<PyCFunction>(Sbk_LedInfo_LedFunc_getEnabled), METH_NOARGS},
    {"getFadeInFadeOutSettings", reinterpret_cast<PyCFunction>(Sbk_LedInfo_LedFunc_getFadeInFadeOutSettings), METH_NOARGS},
    {"getMode", reinterpret_cast<PyCFunction>(Sbk_LedInfo_LedFunc_getMode), METH_NOARGS},
    {"getNormalSettings", reinterpret_cast<PyCFunction>(Sbk_LedInfo_LedFunc_getNormalSettings), METH_NOARGS},
    {"getPulsingSettings", reinterpret_cast<PyCFunction>(Sbk_LedInfo_LedFunc_getPulsingSettings), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_LedInfo_Led___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_LedInfo_Led_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_LedInfo_Led_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_LedInfo_Led_Type = nullptr;
static SbkObjectType *Sbk_LedInfo_Led_TypeF(void)
{
    return _Sbk_LedInfo_Led_Type;
}

static PyType_Slot Sbk_LedInfo_Led_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_LedInfo_Led_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_LedInfo_Led_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_LedInfo_Led_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_LedInfo_Led_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_LedInfo_Led_spec = {
    "1:UPLS.LedInfo.Led",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_LedInfo_Led_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ enum conversion.
static void LedInfo_Led_Mode_PythonToCpp_LedInfo_Led_Mode(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led::Mode *>(cppOut) =
        static_cast<::LedInfo::Led::Mode>(Shiboken::Enum::getValue(pyIn));

}
static PythonToCppFunc is_LedInfo_Led_Mode_PythonToCpp_LedInfo_Led_Mode_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX]))
        return LedInfo_Led_Mode_PythonToCpp_LedInfo_Led_Mode;
    return {};
}
static PyObject *LedInfo_Led_Mode_CppToPython_LedInfo_Led_Mode(const void *cppIn) {
    const int castCppIn = int(*reinterpret_cast<const ::LedInfo::Led::Mode *>(cppIn));
    return Shiboken::Enum::newItem(SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX], castCppIn);

}

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Led_PythonToCpp_Led_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_LedInfo_Led_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Led_PythonToCpp_Led_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_TypeF())))
        return Led_PythonToCpp_Led_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Led_PTR_CppToPython_Led(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::LedInfo::Led *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_LedInfo_Led_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Led_COPY_CppToPython_Led(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_LedInfo_Led_TypeF(), new ::LedInfo::Led(*reinterpret_cast<const ::LedInfo::Led *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Led_PythonToCpp_Led_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led *>(cppOut) = *reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Led_PythonToCpp_Led_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_TypeF())))
        return Led_PythonToCpp_Led_COPY;
    return {};
}

// Implicit conversions.
static void LedInfo_Led_Blinking_PythonToCpp_LedInfo_Led(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led *>(cppOut) = ::LedInfo::Led( *reinterpret_cast< ::LedInfo::Led::Blinking *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX], reinterpret_cast<SbkObject *>(pyIn))));
}
static PythonToCppFunc is_LedInfo_Led_Blinking_PythonToCpp_LedInfo_Led_Convertible(PyObject *pyIn) {
    if (SbkObject_TypeCheck(SbkUPLSTypes[SBK_LEDINFO_LED_BLINKING_IDX], pyIn))
        return LedInfo_Led_Blinking_PythonToCpp_LedInfo_Led;
    return {};
}

static void LedInfo_Led_FadeInFadeOut_PythonToCpp_LedInfo_Led(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led *>(cppOut) = ::LedInfo::Led( *reinterpret_cast< ::LedInfo::Led::FadeInFadeOut *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX], reinterpret_cast<SbkObject *>(pyIn))));
}
static PythonToCppFunc is_LedInfo_Led_FadeInFadeOut_PythonToCpp_LedInfo_Led_Convertible(PyObject *pyIn) {
    if (SbkObject_TypeCheck(SbkUPLSTypes[SBK_LEDINFO_LED_FADEINFADEOUT_IDX], pyIn))
        return LedInfo_Led_FadeInFadeOut_PythonToCpp_LedInfo_Led;
    return {};
}

static void LedInfo_Led_Normal_PythonToCpp_LedInfo_Led(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led *>(cppOut) = ::LedInfo::Led( *reinterpret_cast< ::LedInfo::Led::Normal *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX], reinterpret_cast<SbkObject *>(pyIn))));
}
static PythonToCppFunc is_LedInfo_Led_Normal_PythonToCpp_LedInfo_Led_Convertible(PyObject *pyIn) {
    if (SbkObject_TypeCheck(SbkUPLSTypes[SBK_LEDINFO_LED_NORMAL_IDX], pyIn))
        return LedInfo_Led_Normal_PythonToCpp_LedInfo_Led;
    return {};
}

static void LedInfo_Led_Pulsing_PythonToCpp_LedInfo_Led(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo::Led *>(cppOut) = ::LedInfo::Led( *reinterpret_cast< ::LedInfo::Led::Pulsing *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], reinterpret_cast<SbkObject *>(pyIn))));
}
static PythonToCppFunc is_LedInfo_Led_Pulsing_PythonToCpp_LedInfo_Led_Convertible(PyObject *pyIn) {
    if (SbkObject_TypeCheck(SbkUPLSTypes[SBK_LEDINFO_LED_PULSING_IDX], pyIn))
        return LedInfo_Led_Pulsing_PythonToCpp_LedInfo_Led;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *LedInfo_Led_SignatureStrings[] = {
    "5:UPLS.LedInfo.Led(self)",
    "4:UPLS.LedInfo.Led(self,_blinking:UPLS.LedInfo.Led.Blinking)",
    "3:UPLS.LedInfo.Led(self,_fadeInOut:UPLS.LedInfo.Led.FadeInFadeOut)",
    "2:UPLS.LedInfo.Led(self,_normal:UPLS.LedInfo.Led.Normal)",
    "1:UPLS.LedInfo.Led(self,_pulsing:UPLS.LedInfo.Led.Pulsing)",
    "0:UPLS.LedInfo.Led(self,Led:UPLS.LedInfo.Led)",
    "UPLS.LedInfo.Led.getBlinking(self)->UPLS.LedInfo.Led.Blinking",
    "UPLS.LedInfo.Led.getCurrent_value(self)->uint8_t",
    "UPLS.LedInfo.Led.getEnabled(self)->bool",
    "UPLS.LedInfo.Led.getFadeInFadeOutSettings(self)->UPLS.LedInfo.Led.FadeInFadeOut",
    "UPLS.LedInfo.Led.getMode(self)->UPLS.LedInfo.Led.Mode",
    "UPLS.LedInfo.Led.getNormalSettings(self)->UPLS.LedInfo.Led.Normal",
    "UPLS.LedInfo.Led.getPulsingSettings(self)->UPLS.LedInfo.Led.Pulsing",
    "UPLS.LedInfo.Led.__copy__()",
    nullptr}; // Sentinel

void init_LedInfo_Led(PyObject *enclosingClass)
{
    _Sbk_LedInfo_Led_Type = Shiboken::ObjectType::introduceWrapperType(
        enclosingClass,
        "Led",
        "LedInfo::Led",
        &Sbk_LedInfo_Led_spec,
        LedInfo_Led_SignatureStrings,
        &Shiboken::callCppDestructor< ::LedInfo::Led >,
        0,
        0,
        Shiboken::ObjectType::WrapperFlags::InnerClass    );
    
    SbkUPLSTypes[SBK_LEDINFO_LED_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_Led_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_LedInfo_Led_TypeF(),
        Led_PythonToCpp_Led_PTR,
        is_Led_PythonToCpp_Led_PTR_Convertible,
        Led_PTR_CppToPython_Led,
        Led_COPY_CppToPython_Led);

    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led*");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led&");
    Shiboken::Conversions::registerConverterName(converter, "Led");
    Shiboken::Conversions::registerConverterName(converter, "Led*");
    Shiboken::Conversions::registerConverterName(converter, "Led&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::LedInfo::Led).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Led_PythonToCpp_Led_COPY,
        is_Led_PythonToCpp_Led_COPY_Convertible);
    // Add implicit conversions to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        LedInfo_Led_Blinking_PythonToCpp_LedInfo_Led,
        is_LedInfo_Led_Blinking_PythonToCpp_LedInfo_Led_Convertible);
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        LedInfo_Led_FadeInFadeOut_PythonToCpp_LedInfo_Led,
        is_LedInfo_Led_FadeInFadeOut_PythonToCpp_LedInfo_Led_Convertible);
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        LedInfo_Led_Normal_PythonToCpp_LedInfo_Led,
        is_LedInfo_Led_Normal_PythonToCpp_LedInfo_Led_Convertible);
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        LedInfo_Led_Pulsing_PythonToCpp_LedInfo_Led,
        is_LedInfo_Led_Pulsing_PythonToCpp_LedInfo_Led_Convertible);

    // Initialization of enums.

    // Initialization of enum 'Mode'.
    SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX] = Shiboken::Enum::createScopedEnum(Sbk_LedInfo_Led_TypeF(),
        "Mode",
        "1:UPLS.LedInfo.Led.Mode",
        "LedInfo::Led::Mode");
    if (!SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX])
        return;

    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX],
        SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX], "Normal", (long) LedInfo::Led::Mode::Normal))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX],
        SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX], "Pulsing", (long) LedInfo::Led::Mode::Pulsing))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX],
        SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX], "FadeInOut", (long) LedInfo::Led::Mode::FadeInOut))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX],
        SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX], "Blinking", (long) LedInfo::Led::Mode::Blinking))
        return;
    // Register converter for enum 'LedInfo::Led::Mode'.
    {
        SbkConverter *converter = Shiboken::Conversions::createConverter(SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX],
            LedInfo_Led_Mode_CppToPython_LedInfo_Led_Mode);
        Shiboken::Conversions::addPythonToCppValueConversion(converter,
            LedInfo_Led_Mode_PythonToCpp_LedInfo_Led_Mode,
            is_LedInfo_Led_Mode_PythonToCpp_LedInfo_Led_Mode_Convertible);
        Shiboken::Enum::setTypeConverter(SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX], converter);
        Shiboken::Conversions::registerConverterName(converter, "LedInfo::Led::Mode");
        Shiboken::Conversions::registerConverterName(converter, "Led::Mode");
        Shiboken::Conversions::registerConverterName(converter, "Mode");
    }
    // End of 'Mode' enum.


}
