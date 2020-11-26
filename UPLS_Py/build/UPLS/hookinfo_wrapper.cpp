
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "hookinfo_wrapper.h"

// inner classes
#include "hookinfo_latch_wrapper.h"
#include "hookinfo_battery_wrapper.h"

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
Sbk_HookInfo_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::HookInfo >()))
        return -1;

    ::HookInfo *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "HookInfo", 0, 1, &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: HookInfo::HookInfo()
    // 1: HookInfo::HookInfo(HookInfo)
    if (numArgs == 0) {
        overloadId = 0; // HookInfo()
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_IDX]), (pyArgs[0])))) {
        overloadId = 1; // HookInfo(HookInfo)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_HookInfo_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // HookInfo()
        {

            if (!PyErr_Occurred()) {
                // HookInfo()
                cptr = new ::HookInfo();
            }
            break;
        }
        case 1: // HookInfo(const HookInfo & HookInfo)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::HookInfo cppArg0_local;
            ::HookInfo *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // HookInfo(HookInfo)
                cptr = new ::HookInfo(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::HookInfo >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_HookInfo_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_HookInfo_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.HookInfo");
        return -1;
}

static PyObject *Sbk_HookInfoFunc_getAverageRetrie(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getAverageRetrie()const
            float cppResult = const_cast<const ::HookInfo *>(cppSelf)->getAverageRetrie();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<float>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfoFunc_getBatteryInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getBatteryInfo()const
            HookInfo::Battery cppResult = const_cast<const ::HookInfo *>(cppSelf)->getBatteryInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfoFunc_getLatchInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getLatchInfo()const
            HookInfo::Latch cppResult = const_cast<const ::HookInfo *>(cppSelf)->getLatchInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfoFunc_getMCURuntime(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getMCURuntime()const
            float cppResult = const_cast<const ::HookInfo *>(cppSelf)->getMCURuntime();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<float>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfoFunc_getTemperature(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getTemperature()const
            int16_t cppResult = const_cast<const ::HookInfo *>(cppSelf)->getTemperature();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<int16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfoFunc_getlostMessages(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getlostMessages()const
            uint16_t cppResult = const_cast<const ::HookInfo *>(cppSelf)->getlostMessages();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfo___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::HookInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_HookInfo_methods[] = {
    {"getAverageRetrie", reinterpret_cast<PyCFunction>(Sbk_HookInfoFunc_getAverageRetrie), METH_NOARGS},
    {"getBatteryInfo", reinterpret_cast<PyCFunction>(Sbk_HookInfoFunc_getBatteryInfo), METH_NOARGS},
    {"getLatchInfo", reinterpret_cast<PyCFunction>(Sbk_HookInfoFunc_getLatchInfo), METH_NOARGS},
    {"getMCURuntime", reinterpret_cast<PyCFunction>(Sbk_HookInfoFunc_getMCURuntime), METH_NOARGS},
    {"getTemperature", reinterpret_cast<PyCFunction>(Sbk_HookInfoFunc_getTemperature), METH_NOARGS},
    {"getlostMessages", reinterpret_cast<PyCFunction>(Sbk_HookInfoFunc_getlostMessages), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_HookInfo___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_HookInfo_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_HookInfo_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_HookInfo_Type = nullptr;
static SbkObjectType *Sbk_HookInfo_TypeF(void)
{
    return _Sbk_HookInfo_Type;
}

static PyType_Slot Sbk_HookInfo_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_HookInfo_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_HookInfo_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_HookInfo_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_HookInfo_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_HookInfo_spec = {
    "1:UPLS.HookInfo",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_HookInfo_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void HookInfo_PythonToCpp_HookInfo_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_HookInfo_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_HookInfo_PythonToCpp_HookInfo_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_HookInfo_TypeF())))
        return HookInfo_PythonToCpp_HookInfo_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *HookInfo_PTR_CppToPython_HookInfo(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::HookInfo *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_HookInfo_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *HookInfo_COPY_CppToPython_HookInfo(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_HookInfo_TypeF(), new ::HookInfo(*reinterpret_cast<const ::HookInfo *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void HookInfo_PythonToCpp_HookInfo_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::HookInfo *>(cppOut) = *reinterpret_cast< ::HookInfo *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_HookInfo_PythonToCpp_HookInfo_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_HookInfo_TypeF())))
        return HookInfo_PythonToCpp_HookInfo_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *HookInfo_SignatureStrings[] = {
    "1:UPLS.HookInfo(self)",
    "0:UPLS.HookInfo(self,HookInfo:UPLS.HookInfo)",
    "UPLS.HookInfo.getAverageRetrie(self)->float",
    "UPLS.HookInfo.getBatteryInfo(self)->UPLS.HookInfo.Battery",
    "UPLS.HookInfo.getLatchInfo(self)->UPLS.HookInfo.Latch",
    "UPLS.HookInfo.getMCURuntime(self)->float",
    "UPLS.HookInfo.getTemperature(self)->int16_t",
    "UPLS.HookInfo.getlostMessages(self)->uint16_t",
    "UPLS.HookInfo.__copy__()",
    nullptr}; // Sentinel

void init_HookInfo(PyObject *module)
{
    _Sbk_HookInfo_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "HookInfo",
        "HookInfo",
        &Sbk_HookInfo_spec,
        HookInfo_SignatureStrings,
        &Shiboken::callCppDestructor< ::HookInfo >,
        0,
        0,
        0    );
    
    SbkUPLSTypes[SBK_HOOKINFO_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_HookInfo_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_HookInfo_TypeF(),
        HookInfo_PythonToCpp_HookInfo_PTR,
        is_HookInfo_PythonToCpp_HookInfo_PTR_Convertible,
        HookInfo_PTR_CppToPython_HookInfo,
        HookInfo_COPY_CppToPython_HookInfo);

    Shiboken::Conversions::registerConverterName(converter, "HookInfo");
    Shiboken::Conversions::registerConverterName(converter, "HookInfo*");
    Shiboken::Conversions::registerConverterName(converter, "HookInfo&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::HookInfo).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        HookInfo_PythonToCpp_HookInfo_COPY,
        is_HookInfo_PythonToCpp_HookInfo_COPY_Convertible);


}
