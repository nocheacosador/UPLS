
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "hookinfo_latch_wrapper.h"

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
Sbk_HookInfo_Latch_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::HookInfo::Latch >()))
        return -1;

    ::HookInfo::Latch *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0, 0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 2) {
        PyErr_SetString(PyExc_TypeError, "UPLS.HookInfo.Latch(): too many arguments");
        return -1;
    }

    if (!PyArg_ParseTuple(args, "|OO:Latch", &(pyArgs[0]), &(pyArgs[1])))
        return -1;


    // Overloaded function decisor
    // 0: Latch::Latch(HookInfo::Latch::State,uint16_t)
    // 1: Latch::Latch(HookInfo::Latch)
    if (numArgs == 0) {
        overloadId = 0; // Latch(HookInfo::Latch::State,uint16_t)
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX]), (pyArgs[0])))) {
        overloadId = 1; // Latch(HookInfo::Latch)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX])->converter, (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 0; // Latch(HookInfo::Latch::State,uint16_t)
        } else if ((pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[1])))) {
            overloadId = 0; // Latch(HookInfo::Latch::State,uint16_t)
        }
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_HookInfo_Latch_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Latch(HookInfo::Latch::State _state, uint16_t _current)
        {
            if (kwds) {
                PyObject *keyName = nullptr;
                PyObject *value = nullptr;
                keyName = Py_BuildValue("s","_state");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[0]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.HookInfo.Latch(): got multiple values for keyword argument '_state'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[0] = value;
                        if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX])->converter, (pyArgs[0]))))
                            goto Sbk_HookInfo_Latch_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_current");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[1]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.HookInfo.Latch(): got multiple values for keyword argument '_current'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[1] = value;
                        if (!(pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[1]))))
                            goto Sbk_HookInfo_Latch_Init_TypeError;
                    }
                }
            }
            ::HookInfo::Latch::State cppArg0 = HookInfo::Latch::State::Unknown;
            if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);
            ::uint16_t cppArg1 = 0;
            if (pythonToCpp[1]) pythonToCpp[1](pyArgs[1], &cppArg1);

            if (!PyErr_Occurred()) {
                // Latch(HookInfo::Latch::State,uint16_t)
                cptr = new ::HookInfo::Latch(cppArg0, cppArg1);
            }
            break;
        }
        case 1: // Latch(const HookInfo::Latch & Latch)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::HookInfo::Latch cppArg0_local;
            ::HookInfo::Latch *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Latch(HookInfo::Latch)
                cptr = new ::HookInfo::Latch(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::HookInfo::Latch >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_HookInfo_Latch_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_HookInfo_Latch_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.HookInfo.Latch");
        return -1;
}

static PyObject *Sbk_HookInfo_LatchFunc_getCurrent(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo::Latch *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getCurrent()const
            float cppResult = const_cast<const ::HookInfo::Latch *>(cppSelf)->getCurrent();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<float>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfo_LatchFunc_getState(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo::Latch *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getState()const
            HookInfo::Latch::State cppResult = HookInfo::Latch::State(const_cast<const ::HookInfo::Latch *>(cppSelf)->getState());
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfo_LatchFunc_setCurrent(PyObject *self, PyObject *pyArg)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo::Latch *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: Latch::setCurrent(uint16_t)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArg)))) {
        overloadId = 0; // setCurrent(uint16_t)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_HookInfo_LatchFunc_setCurrent_TypeError;

    // Call function/method
    {
        ::uint16_t cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setCurrent(uint16_t)
            cppSelf->setCurrent(cppArg0);
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_HookInfo_LatchFunc_setCurrent_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "UPLS.HookInfo.Latch.setCurrent");
        return {};
}

static PyObject *Sbk_HookInfo_LatchFunc_setState(PyObject *self, PyObject *pyArg)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo::Latch *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: Latch::setState(HookInfo::Latch::State)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX])->converter, (pyArg)))) {
        overloadId = 0; // setState(HookInfo::Latch::State)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_HookInfo_LatchFunc_setState_TypeError;

    // Call function/method
    {
        ::HookInfo::Latch::State cppArg0{HookInfo::Latch::State::Unknown};
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setState(HookInfo::Latch::State)
            cppSelf->setState(cppArg0);
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_HookInfo_LatchFunc_setState_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "UPLS.HookInfo.Latch.setState");
        return {};
}

static PyObject *Sbk_HookInfo_Latch___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::HookInfo::Latch *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_HookInfo_Latch_methods[] = {
    {"getCurrent", reinterpret_cast<PyCFunction>(Sbk_HookInfo_LatchFunc_getCurrent), METH_NOARGS},
    {"getState", reinterpret_cast<PyCFunction>(Sbk_HookInfo_LatchFunc_getState), METH_NOARGS},
    {"setCurrent", reinterpret_cast<PyCFunction>(Sbk_HookInfo_LatchFunc_setCurrent), METH_O},
    {"setState", reinterpret_cast<PyCFunction>(Sbk_HookInfo_LatchFunc_setState), METH_O},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_HookInfo_Latch___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_HookInfo_Latch_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_HookInfo_Latch_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_HookInfo_Latch_Type = nullptr;
static SbkObjectType *Sbk_HookInfo_Latch_TypeF(void)
{
    return _Sbk_HookInfo_Latch_Type;
}

static PyType_Slot Sbk_HookInfo_Latch_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_HookInfo_Latch_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_HookInfo_Latch_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_HookInfo_Latch_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_HookInfo_Latch_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_HookInfo_Latch_spec = {
    "1:UPLS.HookInfo.Latch",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_HookInfo_Latch_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ enum conversion.
static void HookInfo_Latch_State_PythonToCpp_HookInfo_Latch_State(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::HookInfo::Latch::State *>(cppOut) =
        static_cast<::HookInfo::Latch::State>(Shiboken::Enum::getValue(pyIn));

}
static PythonToCppFunc is_HookInfo_Latch_State_PythonToCpp_HookInfo_Latch_State_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX]))
        return HookInfo_Latch_State_PythonToCpp_HookInfo_Latch_State;
    return {};
}
static PyObject *HookInfo_Latch_State_CppToPython_HookInfo_Latch_State(const void *cppIn) {
    const int castCppIn = int(*reinterpret_cast<const ::HookInfo::Latch::State *>(cppIn));
    return Shiboken::Enum::newItem(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX], castCppIn);

}

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Latch_PythonToCpp_Latch_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_HookInfo_Latch_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Latch_PythonToCpp_Latch_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_HookInfo_Latch_TypeF())))
        return Latch_PythonToCpp_Latch_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Latch_PTR_CppToPython_Latch(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::HookInfo::Latch *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_HookInfo_Latch_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Latch_COPY_CppToPython_Latch(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_HookInfo_Latch_TypeF(), new ::HookInfo::Latch(*reinterpret_cast<const ::HookInfo::Latch *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Latch_PythonToCpp_Latch_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::HookInfo::Latch *>(cppOut) = *reinterpret_cast< ::HookInfo::Latch *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Latch_PythonToCpp_Latch_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_HookInfo_Latch_TypeF())))
        return Latch_PythonToCpp_Latch_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *HookInfo_Latch_SignatureStrings[] = {
    "1:UPLS.HookInfo.Latch(self,_state:UPLS.HookInfo.Latch.State=State.Unknown,_current:uint16_t=0)",
    "0:UPLS.HookInfo.Latch(self,Latch:UPLS.HookInfo.Latch)",
    "UPLS.HookInfo.Latch.getCurrent(self)->float",
    "UPLS.HookInfo.Latch.getState(self)->UPLS.HookInfo.Latch.State",
    "UPLS.HookInfo.Latch.setCurrent(self,_current:uint16_t)",
    "UPLS.HookInfo.Latch.setState(self,_state:UPLS.HookInfo.Latch.State)",
    "UPLS.HookInfo.Latch.__copy__()",
    nullptr}; // Sentinel

void init_HookInfo_Latch(PyObject *enclosingClass)
{
    _Sbk_HookInfo_Latch_Type = Shiboken::ObjectType::introduceWrapperType(
        enclosingClass,
        "Latch",
        "HookInfo::Latch",
        &Sbk_HookInfo_Latch_spec,
        HookInfo_Latch_SignatureStrings,
        &Shiboken::callCppDestructor< ::HookInfo::Latch >,
        0,
        0,
        Shiboken::ObjectType::WrapperFlags::InnerClass    );
    
    SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_HookInfo_Latch_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_HookInfo_Latch_TypeF(),
        Latch_PythonToCpp_Latch_PTR,
        is_Latch_PythonToCpp_Latch_PTR_Convertible,
        Latch_PTR_CppToPython_Latch,
        Latch_COPY_CppToPython_Latch);

    Shiboken::Conversions::registerConverterName(converter, "HookInfo::Latch");
    Shiboken::Conversions::registerConverterName(converter, "HookInfo::Latch*");
    Shiboken::Conversions::registerConverterName(converter, "HookInfo::Latch&");
    Shiboken::Conversions::registerConverterName(converter, "Latch");
    Shiboken::Conversions::registerConverterName(converter, "Latch*");
    Shiboken::Conversions::registerConverterName(converter, "Latch&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::HookInfo::Latch).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Latch_PythonToCpp_Latch_COPY,
        is_Latch_PythonToCpp_Latch_COPY_Convertible);

    // Initialization of enums.

    // Initialization of enum 'State'.
    SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX] = Shiboken::Enum::createScopedEnum(Sbk_HookInfo_Latch_TypeF(),
        "State",
        "1:UPLS.HookInfo.Latch.State",
        "HookInfo::Latch::State");
    if (!SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX])
        return;

    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX],
        SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX], "Unknown", (long) HookInfo::Latch::State::Unknown))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX],
        SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX], "Open", (long) HookInfo::Latch::State::Open))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX],
        SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX], "Closed", (long) HookInfo::Latch::State::Closed))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX],
        SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX], "Opening", (long) HookInfo::Latch::State::Opening))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX],
        SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX], "Closing", (long) HookInfo::Latch::State::Closing))
        return;
    // Register converter for enum 'HookInfo::Latch::State'.
    {
        SbkConverter *converter = Shiboken::Conversions::createConverter(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX],
            HookInfo_Latch_State_CppToPython_HookInfo_Latch_State);
        Shiboken::Conversions::addPythonToCppValueConversion(converter,
            HookInfo_Latch_State_PythonToCpp_HookInfo_Latch_State,
            is_HookInfo_Latch_State_PythonToCpp_HookInfo_Latch_State_Convertible);
        Shiboken::Enum::setTypeConverter(SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX], converter);
        Shiboken::Conversions::registerConverterName(converter, "HookInfo::Latch::State");
        Shiboken::Conversions::registerConverterName(converter, "Latch::State");
        Shiboken::Conversions::registerConverterName(converter, "State");
    }
    // End of 'State' enum.


}
