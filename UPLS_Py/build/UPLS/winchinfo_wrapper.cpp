
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "winchinfo_wrapper.h"

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
Sbk_WinchInfo_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::WinchInfo >()))
        return -1;

    ::WinchInfo *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "WinchInfo", 0, 1, &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: WinchInfo::WinchInfo()
    // 1: WinchInfo::WinchInfo(WinchInfo)
    if (numArgs == 0) {
        overloadId = 0; // WinchInfo()
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_WINCHINFO_IDX]), (pyArgs[0])))) {
        overloadId = 1; // WinchInfo(WinchInfo)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_WinchInfo_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // WinchInfo()
        {

            if (!PyErr_Occurred()) {
                // WinchInfo()
                cptr = new ::WinchInfo();
            }
            break;
        }
        case 1: // WinchInfo(const WinchInfo & WinchInfo)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::WinchInfo cppArg0_local;
            ::WinchInfo *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_WINCHINFO_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // WinchInfo(WinchInfo)
                cptr = new ::WinchInfo(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::WinchInfo >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_WinchInfo_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_WinchInfo_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.WinchInfo");
        return -1;
}

static PyObject *Sbk_WinchInfoFunc_getCurrent(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::WinchInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_WINCHINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getCurrent()const
            uint16_t cppResult = const_cast<const ::WinchInfo *>(cppSelf)->getCurrent();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_WinchInfoFunc_getPosition(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::WinchInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_WINCHINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getPosition()const
            float cppResult = const_cast<const ::WinchInfo *>(cppSelf)->getPosition();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<float>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_WinchInfoFunc_getStatus(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::WinchInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_WINCHINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getStatus()const
            WinchInfo::Status cppResult = WinchInfo::Status(const_cast<const ::WinchInfo *>(cppSelf)->getStatus());
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_WinchInfo___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::WinchInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_WINCHINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_WINCHINFO_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_WinchInfo_methods[] = {
    {"getCurrent", reinterpret_cast<PyCFunction>(Sbk_WinchInfoFunc_getCurrent), METH_NOARGS},
    {"getPosition", reinterpret_cast<PyCFunction>(Sbk_WinchInfoFunc_getPosition), METH_NOARGS},
    {"getStatus", reinterpret_cast<PyCFunction>(Sbk_WinchInfoFunc_getStatus), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_WinchInfo___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_WinchInfo_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_WinchInfo_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_WinchInfo_Type = nullptr;
static SbkObjectType *Sbk_WinchInfo_TypeF(void)
{
    return _Sbk_WinchInfo_Type;
}

static PyType_Slot Sbk_WinchInfo_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_WinchInfo_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_WinchInfo_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_WinchInfo_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_WinchInfo_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_WinchInfo_spec = {
    "1:UPLS.WinchInfo",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_WinchInfo_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ enum conversion.
static void WinchInfo_Status_PythonToCpp_WinchInfo_Status(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::WinchInfo::Status *>(cppOut) =
        static_cast<::WinchInfo::Status>(Shiboken::Enum::getValue(pyIn));

}
static PythonToCppFunc is_WinchInfo_Status_PythonToCpp_WinchInfo_Status_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX]))
        return WinchInfo_Status_PythonToCpp_WinchInfo_Status;
    return {};
}
static PyObject *WinchInfo_Status_CppToPython_WinchInfo_Status(const void *cppIn) {
    const int castCppIn = int(*reinterpret_cast<const ::WinchInfo::Status *>(cppIn));
    return Shiboken::Enum::newItem(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX], castCppIn);

}

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void WinchInfo_PythonToCpp_WinchInfo_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_WinchInfo_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_WinchInfo_PythonToCpp_WinchInfo_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_WinchInfo_TypeF())))
        return WinchInfo_PythonToCpp_WinchInfo_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *WinchInfo_PTR_CppToPython_WinchInfo(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::WinchInfo *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_WinchInfo_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *WinchInfo_COPY_CppToPython_WinchInfo(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_WinchInfo_TypeF(), new ::WinchInfo(*reinterpret_cast<const ::WinchInfo *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void WinchInfo_PythonToCpp_WinchInfo_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::WinchInfo *>(cppOut) = *reinterpret_cast< ::WinchInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_WINCHINFO_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_WinchInfo_PythonToCpp_WinchInfo_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_WinchInfo_TypeF())))
        return WinchInfo_PythonToCpp_WinchInfo_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *WinchInfo_SignatureStrings[] = {
    "1:UPLS.WinchInfo(self)",
    "0:UPLS.WinchInfo(self,WinchInfo:UPLS.WinchInfo)",
    "UPLS.WinchInfo.getCurrent(self)->uint16_t",
    "UPLS.WinchInfo.getPosition(self)->float",
    "UPLS.WinchInfo.getStatus(self)->UPLS.WinchInfo.Status",
    "UPLS.WinchInfo.__copy__()",
    nullptr}; // Sentinel

void init_WinchInfo(PyObject *module)
{
    _Sbk_WinchInfo_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "WinchInfo",
        "WinchInfo",
        &Sbk_WinchInfo_spec,
        WinchInfo_SignatureStrings,
        &Shiboken::callCppDestructor< ::WinchInfo >,
        0,
        0,
        0    );
    
    SbkUPLSTypes[SBK_WINCHINFO_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_WinchInfo_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_WinchInfo_TypeF(),
        WinchInfo_PythonToCpp_WinchInfo_PTR,
        is_WinchInfo_PythonToCpp_WinchInfo_PTR_Convertible,
        WinchInfo_PTR_CppToPython_WinchInfo,
        WinchInfo_COPY_CppToPython_WinchInfo);

    Shiboken::Conversions::registerConverterName(converter, "WinchInfo");
    Shiboken::Conversions::registerConverterName(converter, "WinchInfo*");
    Shiboken::Conversions::registerConverterName(converter, "WinchInfo&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::WinchInfo).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        WinchInfo_PythonToCpp_WinchInfo_COPY,
        is_WinchInfo_PythonToCpp_WinchInfo_COPY_Convertible);

    // Initialization of enums.

    // Initialization of enum 'Status'.
    SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX] = Shiboken::Enum::createScopedEnum(Sbk_WinchInfo_TypeF(),
        "Status",
        "1:UPLS.WinchInfo.Status",
        "WinchInfo::Status");
    if (!SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX])
        return;

    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX],
        SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX], "Unknown", (long) WinchInfo::Status::Unknown))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX],
        SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX], "Lowering", (long) WinchInfo::Status::Lowering))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX],
        SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX], "Lifting", (long) WinchInfo::Status::Lifting))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX],
        SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX], "Halted", (long) WinchInfo::Status::Halted))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX],
        SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX], "Lowered", (long) WinchInfo::Status::Lowered))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX],
        SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX], "Home", (long) WinchInfo::Status::Home))
        return;
    // Register converter for enum 'WinchInfo::Status'.
    {
        SbkConverter *converter = Shiboken::Conversions::createConverter(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX],
            WinchInfo_Status_CppToPython_WinchInfo_Status);
        Shiboken::Conversions::addPythonToCppValueConversion(converter,
            WinchInfo_Status_PythonToCpp_WinchInfo_Status,
            is_WinchInfo_Status_PythonToCpp_WinchInfo_Status_Convertible);
        Shiboken::Enum::setTypeConverter(SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX], converter);
        Shiboken::Conversions::registerConverterName(converter, "WinchInfo::Status");
        Shiboken::Conversions::registerConverterName(converter, "Status");
    }
    // End of 'Status' enum.


}
