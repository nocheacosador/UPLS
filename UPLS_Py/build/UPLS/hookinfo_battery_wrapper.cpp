
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "hookinfo_battery_wrapper.h"

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
Sbk_HookInfo_Battery_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::HookInfo::Battery >()))
        return -1;

    ::HookInfo::Battery *cptr{};
    int overloadId = -1;
    PythonToCppFunc pythonToCpp[] = { nullptr, nullptr };
    SBK_UNUSED(pythonToCpp)
    const Py_ssize_t numNamedArgs = (kwds ? PyDict_Size(kwds) : 0);
    const Py_ssize_t numArgs = PyTuple_GET_SIZE(args);
    SBK_UNUSED(numArgs)
    PyObject *pyArgs[] = {0, 0};

    // invalid argument lengths
    if (numArgs + numNamedArgs > 2) {
        PyErr_SetString(PyExc_TypeError, "UPLS.HookInfo.Battery(): too many arguments");
        return -1;
    }

    if (!PyArg_ParseTuple(args, "|OO:Battery", &(pyArgs[0]), &(pyArgs[1])))
        return -1;


    // Overloaded function decisor
    // 0: Battery::Battery(HookInfo::Battery)
    // 1: Battery::Battery(uint16_t,HookInfo::Battery::State)
    if (numArgs == 0) {
        overloadId = 1; // Battery(uint16_t,HookInfo::Battery::State)
    } else if ((pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[0])))) {
        if (numArgs == 1) {
            overloadId = 1; // Battery(uint16_t,HookInfo::Battery::State)
        } else if ((pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX])->converter, (pyArgs[1])))) {
            overloadId = 1; // Battery(uint16_t,HookInfo::Battery::State)
        }
    } else if (numArgs == 1
        && (pythonToCpp[0] = Shiboken::Conversions::isPythonToCppReferenceConvertible(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX]), (pyArgs[0])))) {
        overloadId = 0; // Battery(HookInfo::Battery)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_HookInfo_Battery_Init_TypeError;

    // Call function/method
    switch (overloadId) {
        case 0: // Battery(const HookInfo::Battery & Battery)
        {
            if (!Shiboken::Object::isValid(pyArgs[0]))
                return -1;
            ::HookInfo::Battery cppArg0_local;
            ::HookInfo::Battery *cppArg0 = &cppArg0_local;
            if (Shiboken::Conversions::isImplicitConversion(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX]), pythonToCpp[0]))
                pythonToCpp[0](pyArgs[0], &cppArg0_local);
            else
                pythonToCpp[0](pyArgs[0], &cppArg0);


            if (!PyErr_Occurred()) {
                // Battery(HookInfo::Battery)
                cptr = new ::HookInfo::Battery(*cppArg0);
            }
            break;
        }
        case 1: // Battery(uint16_t _voltage, HookInfo::Battery::State _state)
        {
            if (kwds) {
                PyObject *keyName = nullptr;
                PyObject *value = nullptr;
                keyName = Py_BuildValue("s","_voltage");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[0]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.HookInfo.Battery(): got multiple values for keyword argument '_voltage'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[0] = value;
                        if (!(pythonToCpp[0] = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<uint16_t>(), (pyArgs[0]))))
                            goto Sbk_HookInfo_Battery_Init_TypeError;
                    }
                }
                keyName = Py_BuildValue("s","_state");
                if (PyDict_Contains(kwds, keyName)) {
                    value = PyDict_GetItem(kwds, keyName);
                    if (value && pyArgs[1]) {
                        PyErr_SetString(PyExc_TypeError, "UPLS.HookInfo.Battery(): got multiple values for keyword argument '_state'.");
                        return -1;
                    }
                    if (value) {
                        pyArgs[1] = value;
                        if (!(pythonToCpp[1] = Shiboken::Conversions::isPythonToCppConvertible(*PepType_SGTP(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX])->converter, (pyArgs[1]))))
                            goto Sbk_HookInfo_Battery_Init_TypeError;
                    }
                }
            }
            ::uint16_t cppArg0 = 0;
            if (pythonToCpp[0]) pythonToCpp[0](pyArgs[0], &cppArg0);
            ::HookInfo::Battery::State cppArg1 = HookInfo::Battery::State::Unknown;
            if (pythonToCpp[1]) pythonToCpp[1](pyArgs[1], &cppArg1);

            if (!PyErr_Occurred()) {
                // Battery(uint16_t,HookInfo::Battery::State)
                cptr = new ::HookInfo::Battery(cppArg0, cppArg1);
            }
            break;
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::HookInfo::Battery >(), cptr)) {
        delete cptr;
        return -1;
    }
    if (!cptr) goto Sbk_HookInfo_Battery_Init_TypeError;

    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;

    Sbk_HookInfo_Battery_Init_TypeError:
        Shiboken::setErrorAboutWrongArguments(args, "UPLS.HookInfo.Battery");
        return -1;
}

static PyObject *Sbk_HookInfo_BatteryFunc_getState(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo::Battery *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getState()const
            HookInfo::Battery::State cppResult = HookInfo::Battery::State(const_cast<const ::HookInfo::Battery *>(cppSelf)->getState());
            pyResult = Shiboken::Conversions::copyToPython(*PepType_SGTP(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX])->converter, &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfo_BatteryFunc_getVoltage(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::HookInfo::Battery *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // getVoltage()const
            float cppResult = const_cast<const ::HookInfo::Battery *>(cppSelf)->getVoltage();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<float>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_HookInfo_Battery___copy__(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto &cppSelf = *reinterpret_cast< ::HookInfo::Battery *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX], reinterpret_cast<SbkObject *>(self)));
    PyObject *pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX]), &cppSelf);
    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_HookInfo_Battery_methods[] = {
    {"getState", reinterpret_cast<PyCFunction>(Sbk_HookInfo_BatteryFunc_getState), METH_NOARGS},
    {"getVoltage", reinterpret_cast<PyCFunction>(Sbk_HookInfo_BatteryFunc_getVoltage), METH_NOARGS},

    {"__copy__", reinterpret_cast<PyCFunction>(Sbk_HookInfo_Battery___copy__), METH_NOARGS},
    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_HookInfo_Battery_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_HookInfo_Battery_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_HookInfo_Battery_Type = nullptr;
static SbkObjectType *Sbk_HookInfo_Battery_TypeF(void)
{
    return _Sbk_HookInfo_Battery_Type;
}

static PyType_Slot Sbk_HookInfo_Battery_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_HookInfo_Battery_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_HookInfo_Battery_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_HookInfo_Battery_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_HookInfo_Battery_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_HookInfo_Battery_spec = {
    "1:UPLS.HookInfo.Battery",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_HookInfo_Battery_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ enum conversion.
static void HookInfo_Battery_State_PythonToCpp_HookInfo_Battery_State(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::HookInfo::Battery::State *>(cppOut) =
        static_cast<::HookInfo::Battery::State>(Shiboken::Enum::getValue(pyIn));

}
static PythonToCppFunc is_HookInfo_Battery_State_PythonToCpp_HookInfo_Battery_State_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX]))
        return HookInfo_Battery_State_PythonToCpp_HookInfo_Battery_State;
    return {};
}
static PyObject *HookInfo_Battery_State_CppToPython_HookInfo_Battery_State(const void *cppIn) {
    const int castCppIn = int(*reinterpret_cast<const ::HookInfo::Battery::State *>(cppIn));
    return Shiboken::Enum::newItem(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX], castCppIn);

}

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void Battery_PythonToCpp_Battery_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_HookInfo_Battery_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_Battery_PythonToCpp_Battery_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_HookInfo_Battery_TypeF())))
        return Battery_PythonToCpp_Battery_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *Battery_PTR_CppToPython_Battery(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::HookInfo::Battery *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_HookInfo_Battery_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// C++ to Python copy conversion.
static PyObject *Battery_COPY_CppToPython_Battery(const void *cppIn) {
    return Shiboken::Object::newObject(Sbk_HookInfo_Battery_TypeF(), new ::HookInfo::Battery(*reinterpret_cast<const ::HookInfo::Battery *>(cppIn)), true, true);
}

// Python to C++ copy conversion.
static void Battery_PythonToCpp_Battery_COPY(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::HookInfo::Battery *>(cppOut) = *reinterpret_cast< ::HookInfo::Battery *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX], reinterpret_cast<SbkObject *>(pyIn)));
}
static PythonToCppFunc is_Battery_PythonToCpp_Battery_COPY_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_HookInfo_Battery_TypeF())))
        return Battery_PythonToCpp_Battery_COPY;
    return {};
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *HookInfo_Battery_SignatureStrings[] = {
    "1:UPLS.HookInfo.Battery(self,Battery:UPLS.HookInfo.Battery)",
    "0:UPLS.HookInfo.Battery(self,_voltage:uint16_t=0,_state:UPLS.HookInfo.Battery.State=State.Unknown)",
    "UPLS.HookInfo.Battery.getState(self)->UPLS.HookInfo.Battery.State",
    "UPLS.HookInfo.Battery.getVoltage(self)->float",
    "UPLS.HookInfo.Battery.__copy__()",
    nullptr}; // Sentinel

void init_HookInfo_Battery(PyObject *enclosingClass)
{
    _Sbk_HookInfo_Battery_Type = Shiboken::ObjectType::introduceWrapperType(
        enclosingClass,
        "Battery",
        "HookInfo::Battery",
        &Sbk_HookInfo_Battery_spec,
        HookInfo_Battery_SignatureStrings,
        &Shiboken::callCppDestructor< ::HookInfo::Battery >,
        0,
        0,
        Shiboken::ObjectType::WrapperFlags::InnerClass    );
    
    SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_HookInfo_Battery_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_HookInfo_Battery_TypeF(),
        Battery_PythonToCpp_Battery_PTR,
        is_Battery_PythonToCpp_Battery_PTR_Convertible,
        Battery_PTR_CppToPython_Battery,
        Battery_COPY_CppToPython_Battery);

    Shiboken::Conversions::registerConverterName(converter, "HookInfo::Battery");
    Shiboken::Conversions::registerConverterName(converter, "HookInfo::Battery*");
    Shiboken::Conversions::registerConverterName(converter, "HookInfo::Battery&");
    Shiboken::Conversions::registerConverterName(converter, "Battery");
    Shiboken::Conversions::registerConverterName(converter, "Battery*");
    Shiboken::Conversions::registerConverterName(converter, "Battery&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::HookInfo::Battery).name());

    // Add Python to C++ copy (value, not pointer neither reference) conversion to type converter.
    Shiboken::Conversions::addPythonToCppValueConversion(converter,
        Battery_PythonToCpp_Battery_COPY,
        is_Battery_PythonToCpp_Battery_COPY_Convertible);

    // Initialization of enums.

    // Initialization of enum 'State'.
    SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX] = Shiboken::Enum::createScopedEnum(Sbk_HookInfo_Battery_TypeF(),
        "State",
        "1:UPLS.HookInfo.Battery.State",
        "HookInfo::Battery::State");
    if (!SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX])
        return;

    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX],
        SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX], "Unknown", (long) HookInfo::Battery::State::Unknown))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX],
        SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX], "Charging", (long) HookInfo::Battery::State::Charging))
        return;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX],
        SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX], "Discharging", (long) HookInfo::Battery::State::Discharging))
        return;
    // Register converter for enum 'HookInfo::Battery::State'.
    {
        SbkConverter *converter = Shiboken::Conversions::createConverter(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX],
            HookInfo_Battery_State_CppToPython_HookInfo_Battery_State);
        Shiboken::Conversions::addPythonToCppValueConversion(converter,
            HookInfo_Battery_State_PythonToCpp_HookInfo_Battery_State,
            is_HookInfo_Battery_State_PythonToCpp_HookInfo_Battery_State_Convertible);
        Shiboken::Enum::setTypeConverter(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX], converter);
        Shiboken::Conversions::registerConverterName(converter, "HookInfo::Battery::State");
        Shiboken::Conversions::registerConverterName(converter, "Battery::State");
        Shiboken::Conversions::registerConverterName(converter, "State");
    }
    // End of 'State' enum.


}
