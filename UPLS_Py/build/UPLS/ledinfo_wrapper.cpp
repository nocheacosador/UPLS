
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "ledinfo_wrapper.h"

// inner classes
#include "ledinfo_led_wrapper.h"

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
Sbk_LedInfo_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::LedInfo >()))
        return -1;

    ::LedInfo *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "LedInfo", 0, 2, &(pyArgs[0]), &(pyArgs[1])))
        return -1;


    // Overloaded function decisor
    // 0: LedInfo::LedInfo()
    // 1: LedInfo::LedInfo(LedInfo::Led,LedInfo::Led)
    // 2: LedInfo::LedInfo(LedInfo::Led)
    // 3: LedInfo::LedInfo(LedInfo)
    if (numArgs == 0) {
        overloadId = 0; // LedInfo()
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppValueConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX]), (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 2; // LedInfo(LedInfo::Led)
        } else if (numArgs == 2
            && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppValueConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX]), (pyArgs[1])))) {
            overloadId = 1; // LedInfo(LedInfo::Led,LedInfo::Led)
        }
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_IDX]), (pyArgs[0])))) {
        overloadId = 3; // LedInfo(LedInfo)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_LedInfo_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // LedInfo()
        {

            if (!PyErr_Occurred()) {
                // LedInfo()
                cptr = new ::LedInfo();
            }
            break;
        }
        case 1: // LedInfo(LedInfo::Led _front, LedInfo::Led _rear)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led cppArg0;
            pythonToCpp[0](pyArgs[0], &cppArg0);
            if (!Shiboken::Object::isValid(pyArgs[1]))
                return -1;
            ::LedInfo::Led cppArg1;
            pythonToCpp[1](pyArgs[1], &cppArg1);

            if (!PyErr_Occurred()) {
                // LedInfo(LedInfo::Led,LedInfo::Led)
                cptr = new ::LedInfo(cppArg0, cppArg1);
            }
            break;
        }
        case 2: // LedInfo(LedInfo::Led both)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo::Led cppArg0;
            pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // LedInfo(LedInfo::Led)
                cptr = new ::LedInfo(cppArg0);
            }
            break;
        }
        case 3: // LedInfo(const LedInfo & LedInfo)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LedInfo cppArg0_local;
            ::LedInfo *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // LedInfo(LedInfo)
                cptr = new ::LedInfo(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::LedInfo >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_LedInfo_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_LedInfo_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.LedInfo");
        return -1;
}

static PyObject *Sbk_LedInfoFunc_frontInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // frontInfo()const
            LedInfo::Led cppResult = const_cast<const ::LedInfo *>(cppSelf)->frontInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfoFunc_rearInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LedInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // rearInfo()const
            LedInfo::Led cppResult = const_cast<const ::LedInfo *>(cppSelf)->rearInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LedInfo___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::LedInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_LedInfo_methods[] = {
    {"frontInfo", reinterpret_cast<PyCFunction>(Sbk_LedInfoFunc_frontInfo), METH_NOARGS},
    {"rearInfo", reinterpret_cast<PyCFunction>(Sbk_LedInfoFunc_rearInfo), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_LedInfo___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_LedInfo_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_LedInfo_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_LedInfo_Type = nullptr;
static SbkObjectType *Sbk_LedInfo_TypeF(void)
{
    return _Sbk_LedInfo_Type;
}

static PyType_Slot Sbk_LedInfo_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_LedInfo_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_LedInfo_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_LedInfo_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_LedInfo_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_LedInfo_spec = {
    "1:UPLS.LedInfo",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_LedInfo_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void LedInfo_PythonToCpp_LedInfo_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_LedInfo_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_LedInfo_PythonToCpp_LedInfo_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_TypeF())))
        return LedInfo_PythonToCpp_LedInfo_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *LedInfo_PTR_CppToPython_LedInfo(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::LedInfo *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_LedInfo_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *LedInfo_COPY_CppToPython_LedInfo(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_LedInfo_TypeF(), new ::LedInfo(*reinterpret_cast<const ::LedInfo *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void LedInfo_PythonToCpp_LedInfo_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo *>(cppOut) = *reinterpret_cast< ::LedInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_LedInfo_PythonToCpp_LedInfo_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_TypeF())))
        return LedInfo_PythonToCpp_LedInfo_COPY;
    return {};
}

// Implicit conversions.
static void LedInfo_Led_PythonToCpp_LedInfo(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LedInfo *>(cppOut) = ::LedInfo( *reinterpret_cast< ::LedInfo::Led *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], reinterpret_cast<SbkObject *>(pyIn))));
}
static PythonToCppFunc is_LedInfo_Led_PythonToCpp_LedInfo_Convertible(PyObject *pyIn) {
    if (SbkObject_TypeCheck(SbkUPLSTypes[SBK_LEDINFO_LED_IDX], pyIn))
        return LedInfo_Led_PythonToCpp_LedInfo;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *LedInfo_SignatureStrings[] = {
    "3:UPLS.LedInfo(self)",
    "2:UPLS.LedInfo(self,_front:UPLS.LedInfo.Led,_rear:UPLS.LedInfo.Led)",
    "1:UPLS.LedInfo(self,both:UPLS.LedInfo.Led)",
    "0:UPLS.LedInfo(self,LedInfo:UPLS.LedInfo)",
    "UPLS.LedInfo.frontInfo(self)->UPLS.LedInfo.Led",
    "UPLS.LedInfo.rearInfo(self)->UPLS.LedInfo.Led",
    "UPLS.LedInfo.__copy__()",
    nullptr}; // Sentinel

void init_LedInfo(PyObject *module)
{
    _Sbk_LedInfo_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "LedInfo",
        "LedInfo",
        &Sbk_LedInfo_spec,
        LedInfo_SignatureStrings,
        &Shiboken::callCppDestructor< ::LedInfo >,
        0,
        0,
        0    );
    
    SbkUPLSTypes[SBK_LEDINFO_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_LedInfo_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_LedInfo_TypeF(),
        LedInfo_PythonToCpp_LedInfo_PTR,
        is_LedInfo_PythonToCpp_LedInfo_PTR_Convertible,
        LedInfo_PTR_CppToPython_LedInfo,
        LedInfo_COPY_CppToPython_LedInfo);

    Shiboken::Conversions::registerConverterName(converter, "LedInfo");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo*");
    Shiboken::Conversions::registerConverterName(converter, "LedInfo&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::LedInfo).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        LedInfo_PythonToCpp_LedInfo_COPY,
        is_LedInfo_PythonToCpp_LedInfo_COPY_Convertible);
    // Add implicit conversions to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        LedInfo_Led_PythonToCpp_LedInfo,
        is_LedInfo_Led_PythonToCpp_LedInfo_Convertible);


}
