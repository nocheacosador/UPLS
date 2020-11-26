
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "error_wrapper.h"

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
Sbk_Error_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::Error >()))
        return -1;

    ::Error *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0, 0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "Error", 0, 2, &(pyArgs[0]), &(pyArgs[1])))
        return -1;


    // Overloaded function decisor
    // 0: Error::Error()
    // 1: Error::Error(Error::Code)
    // 2: Error::Error(Error::Code,const char*)
    // 3: Error::Error(Error)
    if (numArgs == 0) {
        overloadId = 0; // Error()
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkUPLSTypes[SBK_ERROR_CODE_IDX])->converter, (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 1; // Error(Error::Code)
        } else if (numArgs == 2
            && Shiboken::String::check(pyArgs[1]) && (pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<const char *>(), (pyArgs[1])))) {
            overloadId = 2; // Error(Error::Code,const char*)
        }
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_ERROR_IDX]), (pyArgs[0])))) {
        overloadId = 3; // Error(Error)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_Error_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Error()
        {

            if (!PyErr_Occurred()) {
                // Error()
                cptr = new ::Error();
            }
            break;
        }
        case 1: // Error(Error::Code _code)
        {
            ::Error::Code cppArg0{Error::Code::Other};
            pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // Error(Error::Code)
                cptr = new ::Error(cppArg0);
            }
            break;
        }
        case 2: // Error(Error::Code _code, const char * msg)
        {
            ::Error::Code cppArg0{Error::Code::Other};
            pythonToCpp[0](pyArgs[0], &cppArg0);
            const char* cppArg1;
            pythonToCpp[1](pyArgs[1], &cppArg1);

            if (!PyErr_Occurred()) {
                // Error(Error::Code,const char*)
                cptr = new ::Error(cppArg0, cppArg1);
            }
            break;
        }
        case 3: // Error(const Error & Error)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::Error cppArg0_local;
            ::Error *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_ERROR_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Error(Error)
                cptr = new ::Error(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::Error >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_Error_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_Error_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.Error");
        return -1;
}

static PyObject *Sbk_ErrorFunc_getCode(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::Error *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_ERROR_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getCode()const
            Error::Code cppResult = Error::Code(const_cast<const ::Error *>(cppSelf)->getCode());
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkUPLSTypes[SBK_ERROR_CODE_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_ErrorFunc_getMessage(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::Error *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_ERROR_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getMessage()const
            const char * cppResult = const_cast<const ::Error *>(cppSelf)->getMessage();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<const char *>(), cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_Error___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::Error *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_ERROR_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_ERROR_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_Error_methods[] = {
    {"getCode", reinterpret_cast<PyCFunction>(Sbk_ErrorFunc_getCode), METH_NOARGS},
    {"getMessage", reinterpret_cast<PyCFunction>(Sbk_ErrorFunc_getMessage), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_Error___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_Error_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_Error_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_Error_Type = nullptr;
static SbkObjectType *Sbk_Error_TypeF(void)
{
    return _Sbk_Error_Type;
}

static PyType_Slot Sbk_Error_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_Error_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_Error_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_Error_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_Error_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_Error_spec = {
    "1:UPLS.Error",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_Error_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ enum conversion.
static void Error_Code_PythonToCpp_Error_Code(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::Error::Code *>(cppOut) =
        static_cast<::Error::Code>(Shiboken::Enum::getValue(pyIn));

}
static PythonToCppFunc is_Error_Code_PythonToCpp_Error_Code_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, SbkUPLSTypes[SBK_ERROR_CODE_IDX]))
        return Error_Code_PythonToCpp_Error_Code;
    return {};
}
static PyObject *Error_Code_CppToPython_Error_Code(const void *cppIn) {
    const int castCppIn = int(*reinterpret_cast<const ::Error::Code *>(cppIn));
    return Shiboken::Enum::newItem(SbkUPLSTypes[SBK_ERROR_CODE_IDX], castCppIn);

}

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Error_PythonToCpp_Error_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_Error_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Error_PythonToCpp_Error_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_Error_TypeF())))
        return Error_PythonToCpp_Error_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Error_PTR_CppToPython_Error(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::Error *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_Error_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Error_COPY_CppToPython_Error(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_Error_TypeF(), new ::Error(*reinterpret_cast<const ::Error *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Error_PythonToCpp_Error_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::Error *>(cppOut) = *reinterpret_cast< ::Error *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_ERROR_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Error_PythonToCpp_Error_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_Error_TypeF())))
        return Error_PythonToCpp_Error_COPY;
    return {};
}

// Implicit conversions.
static void Error_Code_PythonToCpp_Error(PyObject *pyIn, void *cppOut) {
    ::Error::Code cppIn{Error::Code::Other};
    Shiboken::Conversions::pythonToCppCopy(*PepType_SGTP(SbkUPLSTypes[SBK_ERROR_CODE_IDX])->converter, pyIn, &cppIn);
    *reinterpret_cast<::Error *>(cppOut) = ::Error(cppIn);
}
static PythonToCppFunc is_Error_Code_PythonToCpp_Error_Convertible(PyObject *pyIn) {
    if (SbkObject_TypeCheck(SbkUPLSTypes[SBK_ERROR_CODE_IDX], pyIn))
        return Error_Code_PythonToCpp_Error;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *Error_SignatureStrings[] = {
    "3:UPLS.Error(self)",
    "2:UPLS.Error(self,_code:UPLS.Error.Code)",
    "1:UPLS.Error(self,_code:UPLS.Error.Code,msg:char*)",
    "0:UPLS.Error(self,Error:UPLS.Error)",
    "UPLS.Error.getCode(self)->UPLS.Error.Code",
    "UPLS.Error.getMessage(self)->char*",
    "UPLS.Error.__copy__()",
    nullptr}; // Sentinel

void init_Error(PyObject *module)
{
    _Sbk_Error_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "Error",
        "Error",
        &Sbk_Error_spec,
        Error_SignatureStrings,
        &Shiboken::callCppDestructor< ::Error >,
        0,
        0,
        0    );
    
    SbkUPLSTypes[SBK_ERROR_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_Error_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_Error_TypeF(),
        Error_PythonToCpp_Error_PTR,
        is_Error_PythonToCpp_Error_PTR_Convertible,
        Error_PTR_CppToPython_Error,
        Error_COPY_CppToPython_Error);

    Shiboken::Conversions::registerConverterName(converter, "Error");
    Shiboken::Conversions::registerConverterName(converter, "Error*");
    Shiboken::Conversions::registerConverterName(converter, "Error&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::Error).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Error_PythonToCpp_Error_COPY,
        is_Error_PythonToCpp_Error_COPY_Convertible);
    // Add implicit conversions to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Error_Code_PythonToCpp_Error,
        is_Error_Code_PythonToCpp_Error_Convertible);

    // Initialization of enums.

    // Initialization of enum 'Code'.
    SbkUPLSTypes[SBK_ERROR_CODE_IDX] = Shiboken::Enum::createScopedEnum(Sbk_Error_TypeF(),
        "Code",
        "1:UPLS.Error.Code",
        "Error::Code");
    if (!SbkUPLSTypes[SBK_ERROR_CODE_IDX])
        return;

    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_ERROR_CODE_IDX],
        SbkUPLSTypes[SBK_ERROR_CODE_IDX], "Other", (long) Error::Code::Other))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_ERROR_CODE_IDX],
        SbkUPLSTypes[SBK_ERROR_CODE_IDX], "LatchFailedToClose", (long) Error::Code::LatchFailedToClose))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_ERROR_CODE_IDX],
        SbkUPLSTypes[SBK_ERROR_CODE_IDX], "LatchFailedToOpen", (long) Error::Code::LatchFailedToOpen))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_ERROR_CODE_IDX],
        SbkUPLSTypes[SBK_ERROR_CODE_IDX], "LatchBatteryEmpty", (long) Error::Code::LatchBatteryEmpty))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_ERROR_CODE_IDX],
        SbkUPLSTypes[SBK_ERROR_CODE_IDX], "UnknownPacket", (long) Error::Code::UnknownPacket))
        return;
    // Register converter for enum 'Error::Code'.
    {
        SbkConverter *converter = Shiboken::Conversions::createConverter(SbkUPLSTypes[SBK_ERROR_CODE_IDX],
            Error_Code_CppToPython_Error_Code);
        Shiboken::Conversions::addPythonToCppValueConversion(converter,
            Error_Code_PythonToCpp_Error_Code,
            is_Error_Code_PythonToCpp_Error_Code_Convertible);
        Shiboken::Enum::setTypeConverter(SbkUPLSTypes[SBK_ERROR_CODE_IDX], converter);
        Shiboken::Conversions::registerConverterName(converter, "Error::Code");
        Shiboken::Conversions::registerConverterName(converter, "Code");
    }
    // End of 'Code' enum.


}
