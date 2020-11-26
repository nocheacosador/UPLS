
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "landinggearinfo_wrapper.h"

// inner classes
#include "landinggearinfo_leg_wrapper.h"

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
Sbk_LandingGearInfo_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::LandingGearInfo >()))
        return -1;

    ::LandingGearInfo *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "LandingGearInfo", 0, 1, &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: LandingGearInfo::LandingGearInfo()
    // 1: LandingGearInfo::LandingGearInfo(LandingGearInfo)
    if (numArgs == 0) {
        overloadId = 0; // LandingGearInfo()
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX]), (pyArgs[0])))) {
        overloadId = 1; // LandingGearInfo(LandingGearInfo)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_LandingGearInfo_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // LandingGearInfo()
        {

            if (!PyErr_Occurred()) {
                // LandingGearInfo()
                cptr = new ::LandingGearInfo();
            }
            break;
        }
        case 1: // LandingGearInfo(const LandingGearInfo & LandingGearInfo)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LandingGearInfo cppArg0_local;
            ::LandingGearInfo *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // LandingGearInfo(LandingGearInfo)
                cptr = new ::LandingGearInfo(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::LandingGearInfo >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_LandingGearInfo_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_LandingGearInfo_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.LandingGearInfo");
        return -1;
}

static PyObject *Sbk_LandingGearInfoFunc_frontInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LandingGearInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // frontInfo()const
            LandingGearInfo::Leg cppResult = const_cast<const ::LandingGearInfo *>(cppSelf)->frontInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LandingGearInfoFunc_rearInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LandingGearInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // rearInfo()const
            LandingGearInfo::Leg cppResult = const_cast<const ::LandingGearInfo *>(cppSelf)->rearInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LandingGearInfo___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::LandingGearInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_LandingGearInfo_methods[] = {
    {"frontInfo", reinterpret_cast<PyCFunction>(Sbk_LandingGearInfoFunc_frontInfo), METH_NOARGS},
    {"rearInfo", reinterpret_cast<PyCFunction>(Sbk_LandingGearInfoFunc_rearInfo), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_LandingGearInfo___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_LandingGearInfo_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_LandingGearInfo_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_LandingGearInfo_Type = nullptr;
static SbkObjectType *Sbk_LandingGearInfo_TypeF(void)
{
    return _Sbk_LandingGearInfo_Type;
}

static PyType_Slot Sbk_LandingGearInfo_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_LandingGearInfo_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_LandingGearInfo_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_LandingGearInfo_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_LandingGearInfo_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_LandingGearInfo_spec = {
    "1:UPLS.LandingGearInfo",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_LandingGearInfo_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void LandingGearInfo_PythonToCpp_LandingGearInfo_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_LandingGearInfo_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_LandingGearInfo_PythonToCpp_LandingGearInfo_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LandingGearInfo_TypeF())))
        return LandingGearInfo_PythonToCpp_LandingGearInfo_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *LandingGearInfo_PTR_CppToPython_LandingGearInfo(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::LandingGearInfo *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_LandingGearInfo_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *LandingGearInfo_COPY_CppToPython_LandingGearInfo(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_LandingGearInfo_TypeF(), new ::LandingGearInfo(*reinterpret_cast<const ::LandingGearInfo *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void LandingGearInfo_PythonToCpp_LandingGearInfo_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LandingGearInfo *>(cppOut) = *reinterpret_cast< ::LandingGearInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_LandingGearInfo_PythonToCpp_LandingGearInfo_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LandingGearInfo_TypeF())))
        return LandingGearInfo_PythonToCpp_LandingGearInfo_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *LandingGearInfo_SignatureStrings[] = {
    "1:UPLS.LandingGearInfo(self)",
    "0:UPLS.LandingGearInfo(self,LandingGearInfo:UPLS.LandingGearInfo)",
    "UPLS.LandingGearInfo.frontInfo(self)->UPLS.LandingGearInfo.Leg",
    "UPLS.LandingGearInfo.rearInfo(self)->UPLS.LandingGearInfo.Leg",
    "UPLS.LandingGearInfo.__copy__()",
    nullptr}; // Sentinel

void init_LandingGearInfo(PyObject *module)
{
    _Sbk_LandingGearInfo_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "LandingGearInfo",
        "LandingGearInfo",
        &Sbk_LandingGearInfo_spec,
        LandingGearInfo_SignatureStrings,
        &Shiboken::callCppDestructor< ::LandingGearInfo >,
        0,
        0,
        0    );
    
    SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_LandingGearInfo_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_LandingGearInfo_TypeF(),
        LandingGearInfo_PythonToCpp_LandingGearInfo_PTR,
        is_LandingGearInfo_PythonToCpp_LandingGearInfo_PTR_Convertible,
        LandingGearInfo_PTR_CppToPython_LandingGearInfo,
        LandingGearInfo_COPY_CppToPython_LandingGearInfo);

    Shiboken::Conversions::registerConverterName(converter, "LandingGearInfo");
    Shiboken::Conversions::registerConverterName(converter, "LandingGearInfo*");
    Shiboken::Conversions::registerConverterName(converter, "LandingGearInfo&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::LandingGearInfo).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        LandingGearInfo_PythonToCpp_LandingGearInfo_COPY,
        is_LandingGearInfo_PythonToCpp_LandingGearInfo_COPY_Convertible);


}
