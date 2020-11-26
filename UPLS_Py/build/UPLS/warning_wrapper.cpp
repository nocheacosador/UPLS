
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "warning_wrapper.h"

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
Sbk_Warning_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::Warning >()))
        return -1;

    ::Warning *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "Warning", 0, 2, &(pyArgs[0]), &(pyArgs[1])))
        return -1;


    // Overloaded function decisor
    // 0: Warning::Warning()
    // 1: Warning::Warning(Warning::Code)
    // 2: Warning::Warning(Warning::Code,const char*)
    // 3: Warning::Warning(Warning)
    if (numArgs == 0) {
        overloadId = 0; // Warning()
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkUPLSTypes[SBK_WARNING_CODE_IDX])->converter, (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 1; // Warning(Warning::Code)
        } else if (numArgs == 2
            && Shiboken::String::check(pyArgs[1]) && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<const char *>(), (pyArgs[1])))) {
            overloadId = 2; // Warning(Warning::Code,const char*)
        }
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_WARNING_IDX]), (pyArgs[0])))) {
        overloadId = 3; // Warning(Warning)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_Warning_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Warning()
        {

            if (!PyErr_Occurred()) {
                // Warning()
                cptr = new ::Warning();
            }
            break;
        }
        case 1: // Warning(Warning::Code _code)
        {
            ::Warning::Code cppArg0{Warning::Code::Other};
            pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // Warning(Warning::Code)
                cptr = new ::Warning(cppArg0);
            }
            break;
        }
        case 2: // Warning(Warning::Code _code, const char * msg)
        {
            ::Warning::Code cppArg0{Warning::Code::Other};
            pythonToCpp[0](pyArgs[0], &cppArg0);
            const char* cppArg1;
            pythonToCpp[1](pyArgs[1], &cppArg1);

            if (!PyErr_Occurred()) {
                // Warning(Warning::Code,const char*)
                cptr = new ::Warning(cppArg0, cppArg1);
            }
            break;
        }
        case 3: // Warning(const Warning & Warning)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::Warning cppArg0_local;
            ::Warning *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_WARNING_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Warning(Warning)
                cptr = new ::Warning(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::Warning >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_Warning_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_Warning_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.Warning");
        return -1;
}

static PyObject *Sbk_WarningFunc_getCode(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::Warning *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_WARNING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getCode()const
            Warning::Code cppResult = Warning::Code(const_cast<const ::Warning *>(cppSelf)->getCode());
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkUPLSTypes[SBK_WARNING_CODE_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_WarningFunc_getMessage(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::Warning *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_WARNING_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getMessage()const
            const char * cppResult = const_cast<const ::Warning *>(cppSelf)->getMessage();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<const char *>(), cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_Warning___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::Warning *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_WARNING_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_WARNING_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_Warning_methods[] = {
    {"getCode", reinterpret_cast<PyCFunction>(Sbk_WarningFunc_getCode), METH_NOARGS},
    {"getMessage", reinterpret_cast<PyCFunction>(Sbk_WarningFunc_getMessage), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_Warning___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_Warning_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_Warning_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_Warning_Type = nullptr;
static SbkObjectType *Sbk_Warning_TypeF(void)
{
    return _Sbk_Warning_Type;
}

static PyType_Slot Sbk_Warning_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_Warning_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_Warning_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_Warning_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_Warning_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_Warning_spec = {
    "1:UPLS.Warning",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_Warning_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ enum conversion.
static void Warning_Code_PythonToCpp_Warning_Code(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::Warning::Code *>(cppOut) =
        static_cast<::Warning::Code>(Shiboken::Enum::getValue(pyIn));

}
static PythonToCppFunc is_Warning_Code_PythonToCpp_Warning_Code_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, SbkUPLSTypes[SBK_WARNING_CODE_IDX]))
        return Warning_Code_PythonToCpp_Warning_Code;
    return {};
}
static PyObject *Warning_Code_CppToPython_Warning_Code(const void *cppIn) {
    const int castCppIn = int(*reinterpret_cast<const ::Warning::Code *>(cppIn));
    return Shiboken::Enum::newItem(SbkUPLSTypes[SBK_WARNING_CODE_IDX], castCppIn);

}

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Warning_PythonToCpp_Warning_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_Warning_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Warning_PythonToCpp_Warning_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_Warning_TypeF())))
        return Warning_PythonToCpp_Warning_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Warning_PTR_CppToPython_Warning(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::Warning *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_Warning_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Warning_COPY_CppToPython_Warning(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_Warning_TypeF(), new ::Warning(*reinterpret_cast<const ::Warning *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Warning_PythonToCpp_Warning_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::Warning *>(cppOut) = *reinterpret_cast< ::Warning *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_WARNING_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Warning_PythonToCpp_Warning_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_Warning_TypeF())))
        return Warning_PythonToCpp_Warning_COPY;
    return {};
}

// Implicit conversions.
static void Warning_Code_PythonToCpp_Warning(PyObject *pyIn, void *cppOut) {
    ::Warning::Code cppIn{Warning::Code::Other};
    Shiboken::Conversions::pythonToCppCopy(*PepType_SGTP(SbkUPLSTypes[SBK_WARNING_CODE_IDX])->converter, pyIn, &cppIn);
    *reinterpret_cast<::Warning *>(cppOut) = ::Warning(cppIn);
}
static PythonToCppFunc is_Warning_Code_PythonToCpp_Warning_Convertible(PyObject *pyIn) {
    if (SbkObject_TypeCheck(SbkUPLSTypes[SBK_WARNING_CODE_IDX], pyIn))
        return Warning_Code_PythonToCpp_Warning;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *Warning_SignatureStrings[] = {
    "3:UPLS.Warning(self)",
    "2:UPLS.Warning(self,_code:UPLS.Warning.Code)",
    "1:UPLS.Warning(self,_code:UPLS.Warning.Code,msg:char*)",
    "0:UPLS.Warning(self,Warning:UPLS.Warning)",
    "UPLS.Warning.getCode(self)->UPLS.Warning.Code",
    "UPLS.Warning.getMessage(self)->char*",
    "UPLS.Warning.__copy__()",
    nullptr}; // Sentinel

void init_Warning(PyObject *module)
{
    _Sbk_Warning_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "Warning",
        "Warning",
        &Sbk_Warning_spec,
        Warning_SignatureStrings,
        &Shiboken::callCppDestructor< ::Warning >,
        0,
        0,
        0    );
    
    SbkUPLSTypes[SBK_WARNING_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_Warning_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_Warning_TypeF(),
        Warning_PythonToCpp_Warning_PTR,
        is_Warning_PythonToCpp_Warning_PTR_Convertible,
        Warning_PTR_CppToPython_Warning,
        Warning_COPY_CppToPython_Warning);

    Shiboken::Conversions::registerConverterName(converter, "Warning");
    Shiboken::Conversions::registerConverterName(converter, "Warning*");
    Shiboken::Conversions::registerConverterName(converter, "Warning&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::Warning).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Warning_PythonToCpp_Warning_COPY,
        is_Warning_PythonToCpp_Warning_COPY_Convertible);
    // Add implicit conversions to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Warning_Code_PythonToCpp_Warning,
        is_Warning_Code_PythonToCpp_Warning_Convertible);

    // Initialization of enums.

    // Initialization of enum 'Code'.
    SbkUPLSTypes[SBK_WARNING_CODE_IDX] = Shiboken::Enum::createScopedEnum(Sbk_Warning_TypeF(),
        "Code",
        "1:UPLS.Warning.Code",
        "Warning::Code");
    if (!SbkUPLSTypes[SBK_WARNING_CODE_IDX])
        return;

    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_WARNING_CODE_IDX],
        SbkUPLSTypes[SBK_WARNING_CODE_IDX], "Other", (long) Warning::Code::Other))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_WARNING_CODE_IDX],
        SbkUPLSTypes[SBK_WARNING_CODE_IDX], "LatchBatteryLow", (long) Warning::Code::LatchBatteryLow))
        return;
    // Register converter for enum 'Warning::Code'.
    {
        SbkConverter *converter = Shiboken::Conversions::createConverter(SbkUPLSTypes[SBK_WARNING_CODE_IDX],
            Warning_Code_CppToPython_Warning_Code);
        Shiboken::Conversions::addPythonToCppValueConversion(converter,
            Warning_Code_PythonToCpp_Warning_Code,
            is_Warning_Code_PythonToCpp_Warning_Code_Convertible);
        Shiboken::Enum::setTypeConverter(SbkUPLSTypes[SBK_WARNING_CODE_IDX], converter);
        Shiboken::Conversions::registerConverterName(converter, "Warning::Code");
        Shiboken::Conversions::registerConverterName(converter, "Code");
    }
    // End of 'Code' enum.


}
