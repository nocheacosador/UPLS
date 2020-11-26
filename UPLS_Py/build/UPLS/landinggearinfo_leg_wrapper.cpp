
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "landinggearinfo_leg_wrapper.h"

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
Sbk_LandingGearInfo_Leg_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::LandingGearInfo::Leg >()))
        return -1;

    ::LandingGearInfo::Leg *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "Leg", 0, 1, &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: Leg::Leg()
    // 1: Leg::Leg(LandingGearInfo::Leg)
    if (numArgs == 0) {
        overloadId = 0; // Leg()
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX]), (pyArgs[0])))) {
        overloadId = 1; // Leg(LandingGearInfo::Leg)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_LandingGearInfo_Leg_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Leg()
        {

            if (!PyErr_Occurred()) {
                // Leg()
                cptr = new ::LandingGearInfo::Leg();
            }
            break;
        }
        case 1: // Leg(const LandingGearInfo::Leg & Leg)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::LandingGearInfo::Leg cppArg0_local;
            ::LandingGearInfo::Leg *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Leg(LandingGearInfo::Leg)
                cptr = new ::LandingGearInfo::Leg(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::LandingGearInfo::Leg >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_LandingGearInfo_Leg_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_LandingGearInfo_Leg_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.LandingGearInfo.Leg");
        return -1;
}

static PyObject *Sbk_LandingGearInfo_LegFunc_getCurrent(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LandingGearInfo::Leg *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getCurrent()const
            uint16_t cppResult = const_cast<const ::LandingGearInfo::Leg *>(cppSelf)->getCurrent();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LandingGearInfo_LegFunc_getStatus(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LandingGearInfo::Leg *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getStatus()const
            LandingGearInfo::Leg::Status cppResult = LandingGearInfo::Leg::Status(const_cast<const ::LandingGearInfo::Leg *>(cppSelf)->getStatus());
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LandingGearInfo_LegFunc_getValue(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::LandingGearInfo::Leg *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getValue()const
            uint8_t cppResult = const_cast<const ::LandingGearInfo::Leg *>(cppSelf)->getValue();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint8_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_LandingGearInfo_Leg___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::LandingGearInfo::Leg *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_LandingGearInfo_Leg_methods[] = {
    {"getCurrent", reinterpret_cast<PyCFunction>(Sbk_LandingGearInfo_LegFunc_getCurrent), METH_NOARGS},
    {"getStatus", reinterpret_cast<PyCFunction>(Sbk_LandingGearInfo_LegFunc_getStatus), METH_NOARGS},
    {"getValue", reinterpret_cast<PyCFunction>(Sbk_LandingGearInfo_LegFunc_getValue), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_LandingGearInfo_Leg___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_LandingGearInfo_Leg_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_LandingGearInfo_Leg_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_LandingGearInfo_Leg_Type = nullptr;
static SbkObjectType *Sbk_LandingGearInfo_Leg_TypeF(void)
{
    return _Sbk_LandingGearInfo_Leg_Type;
}

static PyType_Slot Sbk_LandingGearInfo_Leg_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_LandingGearInfo_Leg_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_LandingGearInfo_Leg_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_LandingGearInfo_Leg_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_LandingGearInfo_Leg_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_LandingGearInfo_Leg_spec = {
    "1:UPLS.LandingGearInfo.Leg",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_LandingGearInfo_Leg_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ enum conversion.
static void LandingGearInfo_Leg_Status_PythonToCpp_LandingGearInfo_Leg_Status(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LandingGearInfo::Leg::Status *>(cppOut) =
        static_cast<::LandingGearInfo::Leg::Status>(Shiboken::Enum::getValue(pyIn));

}
static PythonToCppFunc is_LandingGearInfo_Leg_Status_PythonToCpp_LandingGearInfo_Leg_Status_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX]))
        return LandingGearInfo_Leg_Status_PythonToCpp_LandingGearInfo_Leg_Status;
    return {};
}
static PyObject *LandingGearInfo_Leg_Status_CppToPython_LandingGearInfo_Leg_Status(const void *cppIn) {
    const int castCppIn = int(*reinterpret_cast<const ::LandingGearInfo::Leg::Status *>(cppIn));
    return Shiboken::Enum::newItem(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX], castCppIn);

}

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Leg_PythonToCpp_Leg_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_LandingGearInfo_Leg_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Leg_PythonToCpp_Leg_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LandingGearInfo_Leg_TypeF())))
        return Leg_PythonToCpp_Leg_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Leg_PTR_CppToPython_Leg(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::LandingGearInfo::Leg *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_LandingGearInfo_Leg_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Leg_COPY_CppToPython_Leg(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_LandingGearInfo_Leg_TypeF(), new ::LandingGearInfo::Leg(*reinterpret_cast<const ::LandingGearInfo::Leg *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Leg_PythonToCpp_Leg_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::LandingGearInfo::Leg *>(cppOut) = *reinterpret_cast< ::LandingGearInfo::Leg *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Leg_PythonToCpp_Leg_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_LandingGearInfo_Leg_TypeF())))
        return Leg_PythonToCpp_Leg_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *LandingGearInfo_Leg_SignatureStrings[] = {
    "1:UPLS.LandingGearInfo.Leg(self)",
    "0:UPLS.LandingGearInfo.Leg(self,Leg:UPLS.LandingGearInfo.Leg)",
    "UPLS.LandingGearInfo.Leg.getCurrent(self)->uint16_t",
    "UPLS.LandingGearInfo.Leg.getStatus(self)->UPLS.LandingGearInfo.Leg.Status",
    "UPLS.LandingGearInfo.Leg.getValue(self)->uint8_t",
    "UPLS.LandingGearInfo.Leg.__copy__()",
    nullptr}; // Sentinel

void init_LandingGearInfo_Leg(PyObject *enclosingClass)
{
    _Sbk_LandingGearInfo_Leg_Type = Shiboken::ObjectType::introduceWrapperType(
        enclosingClass,
        "Leg",
        "LandingGearInfo::Leg",
        &Sbk_LandingGearInfo_Leg_spec,
        LandingGearInfo_Leg_SignatureStrings,
        &Shiboken::callCppDestructor< ::LandingGearInfo::Leg >,
        0,
        0,
        Shiboken::ObjectType::WrapperFlags::InnerClass    );
    
    SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_LandingGearInfo_Leg_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_LandingGearInfo_Leg_TypeF(),
        Leg_PythonToCpp_Leg_PTR,
        is_Leg_PythonToCpp_Leg_PTR_Convertible,
        Leg_PTR_CppToPython_Leg,
        Leg_COPY_CppToPython_Leg);

    Shiboken::Conversions::registerConverterName(converter, "LandingGearInfo::Leg");
    Shiboken::Conversions::registerConverterName(converter, "LandingGearInfo::Leg*");
    Shiboken::Conversions::registerConverterName(converter, "LandingGearInfo::Leg&");
    Shiboken::Conversions::registerConverterName(converter, "Leg");
    Shiboken::Conversions::registerConverterName(converter, "Leg*");
    Shiboken::Conversions::registerConverterName(converter, "Leg&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::LandingGearInfo::Leg).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Leg_PythonToCpp_Leg_COPY,
        is_Leg_PythonToCpp_Leg_COPY_Convertible);

    // Initialization of enums.

    // Initialization of enum 'Status'.
    SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX] = Shiboken::Enum::createScopedEnum(Sbk_LandingGearInfo_Leg_TypeF(),
        "Status",
        "1:UPLS.LandingGearInfo.Leg.Status",
        "LandingGearInfo::Leg::Status");
    if (!SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX])
        return;

    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX],
        SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX], "Unknown", (long) LandingGearInfo::Leg::Status::Unknown))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX],
        SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX], "Opened", (long) LandingGearInfo::Leg::Status::Opened))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX],
        SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX], "Closed", (long) LandingGearInfo::Leg::Status::Closed))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX],
        SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX], "Closing", (long) LandingGearInfo::Leg::Status::Closing))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX],
        SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX], "Opening", (long) LandingGearInfo::Leg::Status::Opening))
        return;
    // Register converter for enum 'LandingGearInfo::Leg::Status'.
    {
        SbkConverter *converter = Shiboken::Conversions::createConverter(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX],
            LandingGearInfo_Leg_Status_CppToPython_LandingGearInfo_Leg_Status);
        Shiboken::Conversions::addPythonToCppValueConversion(converter,
            LandingGearInfo_Leg_Status_PythonToCpp_LandingGearInfo_Leg_Status,
            is_LandingGearInfo_Leg_Status_PythonToCpp_LandingGearInfo_Leg_Status_Convertible);
        Shiboken::Enum::setTypeConverter(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX], converter);
        Shiboken::Conversions::registerConverterName(converter, "LandingGearInfo::Leg::Status");
        Shiboken::Conversions::registerConverterName(converter, "Leg::Status");
        Shiboken::Conversions::registerConverterName(converter, "Status");
    }
    // End of 'Status' enum.


}
