
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "command_wrapper.h"

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
Sbk_Command_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::Command >()))
        return -1;

    ::Command *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0};

    // invalid argument lengths


    if (!PyArg_UnpackTuple(args, "Command", 0, 1, &(pyArgs[0])))
        return -1;


    // Overloaded function decisor
    // 0: Command::Command()
    // 1: Command::Command(Command::Code)
    // 2: Command::Command(Command)
    if (numArgs == 0) {
        overloadId = 0; // Command()
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkUPLSTypes[SBK_COMMAND_CODE_IDX])->converter, (pyArgs[0])))) {
        overloadId = 1; // Command(Command::Code)
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_COMMAND_IDX]), (pyArgs[0])))) {
        overloadId = 2; // Command(Command)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_Command_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Command()
        {

            if (!PyErr_Occurred()) {
                // Command()
                cptr = new ::Command();
            }
            break;
        }
        case 1: // Command(Command::Code code)
        {
            ::Command::Code cppArg0{Command::Code::Unknown};
            pythonToCpp[0](pyArgs[0], &cppArg0);

            if (!PyErr_Occurred()) {
                // Command(Command::Code)
                cptr = new ::Command(cppArg0);
            }
            break;
        }
        case 2: // Command(const Command & Command)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::Command cppArg0_local;
            ::Command *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_COMMAND_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Command(Command)
                cptr = new ::Command(*cppArg0);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::Command >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_Command_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_Command_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.Command");
        return -1;
}

static PyObject *Sbk_CommandFunc_getCode(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::Command *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_COMMAND_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getCode()
            Command::Code cppResult = Command::Code(cppSelf->getCode());
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkUPLSTypes[SBK_COMMAND_CODE_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_CommandFunc_setPulseLength(PyObject *self, PyObject *pyArg)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::Command *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_COMMAND_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: Command::setPulseLength(uint16_t)
    if ((pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArg)))) {
        overloadId = 0; // setPulseLength(uint16_t)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_CommandFunc_setPulseLength_TypeError;

    // Call function/method
    {
        ::uint16_t cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setPulseLength(uint16_t)
            cppSelf->setPulseLength(cppArg0);
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_CommandFunc_setPulseLength_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "UPLS.Command.setPulseLength");
        return {};
}

static PyObject *Sbk_Command___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::Command *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_COMMAND_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_COMMAND_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_Command_methods[] = {
    {"getCode", reinterpret_cast<PyCFunction>(Sbk_CommandFunc_getCode), METH_NOARGS},
    {"setPulseLength", reinterpret_cast<PyCFunction>(Sbk_CommandFunc_setPulseLength), METH_O},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_Command___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_Command_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_Command_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_Command_Type = nullptr;
static SbkObjectType *Sbk_Command_TypeF(void)
{
    return _Sbk_Command_Type;
}

static PyType_Slot Sbk_Command_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_Command_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_Command_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_Command_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_Command_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_Command_spec = {
    "1:UPLS.Command",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_Command_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ enum conversion.
static void Command_Code_PythonToCpp_Command_Code(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::Command::Code *>(cppOut) =
        static_cast<::Command::Code>(Shiboken::Enum::getValue(pyIn));

}
static PythonToCppFunc is_Command_Code_PythonToCpp_Command_Code_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, SbkUPLSTypes[SBK_COMMAND_CODE_IDX]))
        return Command_Code_PythonToCpp_Command_Code;
    return {};
}
static PyObject *Command_Code_CppToPython_Command_Code(const void *cppIn) {
    const int castCppIn = int(*reinterpret_cast<const ::Command::Code *>(cppIn));
    return Shiboken::Enum::newItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX], castCppIn);

}

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Command_PythonToCpp_Command_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_Command_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Command_PythonToCpp_Command_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_Command_TypeF())))
        return Command_PythonToCpp_Command_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Command_PTR_CppToPython_Command(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::Command *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_Command_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Command_COPY_CppToPython_Command(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_Command_TypeF(), new ::Command(*reinterpret_cast<const ::Command *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Command_PythonToCpp_Command_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::Command *>(cppOut) = *reinterpret_cast< ::Command *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_COMMAND_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Command_PythonToCpp_Command_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_Command_TypeF())))
        return Command_PythonToCpp_Command_COPY;
    return {};
}

// Implicit conversions.
static void Command_Code_PythonToCpp_Command(PyObject *pyIn, void *cppOut) {
    ::Command::Code cppIn{Command::Code::Unknown};
    Shiboken::Conversions::pythonToCppCopy(*PepType_SGTP(SbkUPLSTypes[SBK_COMMAND_CODE_IDX])->converter, pyIn, &cppIn);
    *reinterpret_cast<::Command *>(cppOut) = ::Command(cppIn);
}
static PythonToCppFunc is_Command_Code_PythonToCpp_Command_Convertible(PyObject *pyIn) {
    if (SbkObject_TypeCheck(SbkUPLSTypes[SBK_COMMAND_CODE_IDX], pyIn))
        return Command_Code_PythonToCpp_Command;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *Command_SignatureStrings[] = {
    "2:UPLS.Command(self)",
    "1:UPLS.Command(self,code:UPLS.Command.Code)",
    "0:UPLS.Command(self,Command:UPLS.Command)",
    "UPLS.Command.getCode(self)->UPLS.Command.Code",
    "UPLS.Command.setPulseLength(self,value:uint16_t)",
    "UPLS.Command.__copy__()",
    nullptr}; // Sentinel

void init_Command(PyObject *module)
{
    _Sbk_Command_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "Command",
        "Command",
        &Sbk_Command_spec,
        Command_SignatureStrings,
        &Shiboken::callCppDestructor< ::Command >,
        0,
        0,
        0    );
    
    SbkUPLSTypes[SBK_COMMAND_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_Command_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_Command_TypeF(),
        Command_PythonToCpp_Command_PTR,
        is_Command_PythonToCpp_Command_PTR_Convertible,
        Command_PTR_CppToPython_Command,
        Command_COPY_CppToPython_Command);

    Shiboken::Conversions::registerConverterName(converter, "Command");
    Shiboken::Conversions::registerConverterName(converter, "Command*");
    Shiboken::Conversions::registerConverterName(converter, "Command&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::Command).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Command_PythonToCpp_Command_COPY,
        is_Command_PythonToCpp_Command_COPY_Convertible);
    // Add implicit conversions to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Command_Code_PythonToCpp_Command,
        is_Command_Code_PythonToCpp_Command_Convertible);

    // Initialization of enums.

    // Initialization of enum 'Code'.
    SbkUPLSTypes[SBK_COMMAND_CODE_IDX] = Shiboken::Enum::createScopedEnum(Sbk_Command_TypeF(),
        "Code",
        "1:UPLS.Command.Code",
        "Command::Code");
    if (!SbkUPLSTypes[SBK_COMMAND_CODE_IDX])
        return;

    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
        SbkUPLSTypes[SBK_COMMAND_CODE_IDX], "Unknown", (long) Command::Code::Unknown))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
        SbkUPLSTypes[SBK_COMMAND_CODE_IDX], "OpenLatch", (long) Command::Code::OpenLatch))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
        SbkUPLSTypes[SBK_COMMAND_CODE_IDX], "CloseLatch", (long) Command::Code::CloseLatch))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
        SbkUPLSTypes[SBK_COMMAND_CODE_IDX], "SetLatchClosePulseDuration", (long) Command::Code::SetLatchClosePulseDuration))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
        SbkUPLSTypes[SBK_COMMAND_CODE_IDX], "SetLatchOpenPulseDuration", (long) Command::Code::SetLatchOpenPulseDuration))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
        SbkUPLSTypes[SBK_COMMAND_CODE_IDX], "StatusRequest", (long) Command::Code::StatusRequest))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
        SbkUPLSTypes[SBK_COMMAND_CODE_IDX], "LedsOn", (long) Command::Code::LedsOn))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
        SbkUPLSTypes[SBK_COMMAND_CODE_IDX], "LedsOff", (long) Command::Code::LedsOff))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
        SbkUPLSTypes[SBK_COMMAND_CODE_IDX], "LatchShutdown", (long) Command::Code::LatchShutdown))
        return;
    // Register converter for enum 'Command::Code'.
    {
        SbkConverter *converter = Shiboken::Conversions::createConverter(SbkUPLSTypes[SBK_COMMAND_CODE_IDX],
            Command_Code_CppToPython_Command_Code);
        Shiboken::Conversions::addPythonToCppValueConversion(converter,
            Command_Code_PythonToCpp_Command_Code,
            is_Command_Code_PythonToCpp_Command_Code_Convertible);
        Shiboken::Enum::setTypeConverter(SbkUPLSTypes[SBK_COMMAND_CODE_IDX], converter);
        Shiboken::Conversions::registerConverterName(converter, "Command::Code");
        Shiboken::Conversions::registerConverterName(converter, "Code");
    }
    // End of 'Code' enum.


}
