
#include <sbkpython.h>
#include <shiboken.h>
#include <algorithm>
#include <signature.h>
#include "upls_python.h"



// Extra includes

// Current module's type array.
PyTypeObject **SbkUPLSTypes = nullptr;
// Current module's PyObject pointer.
PyObject *SbkUPLSModuleObject = nullptr;
// Current module's converter array.
SbkConverter **SbkUPLSTypeConverters = nullptr;
// Global functions ------------------------------------------------------------

static PyMethodDef UPLS_methods[] = {
    {0} // Sentinel
};

// Classes initialization functions ------------------------------------------------------------
void init_WinchInfo(PyObject *module);
void init_Warning(PyObject *module);
void init_UPLS_Controller(PyObject *module);
void init_LedInfo(PyObject *module);
void init_LedInfo_Led(PyObject *enclosingClass);
void init_LedInfo_Led_Pulsing(PyObject *enclosingClass);
void init_LedInfo_Led_Normal(PyObject *enclosingClass);
void init_LandingGearInfo(PyObject *module);
void init_LandingGearInfo_Leg(PyObject *enclosingClass);
void init_HookInfo(PyObject *module);
void init_HookInfo_Latch(PyObject *enclosingClass);
void init_LedInfo_Led_FadeInFadeOut(PyObject *enclosingClass);
void init_Error(PyObject *module);
void init_Command(PyObject *module);
void init_LedInfo_Led_Blinking(PyObject *enclosingClass);
void init_HookInfo_Battery(PyObject *enclosingClass);

// Enum definitions ------------------------------------------------------------
static void Device_PythonToCpp_Device(PyObject *pyIn, void *cppOut) {
    *reinterpret_cast<::Device *>(cppOut) =
        static_cast<::Device>(Shiboken::Enum::getValue(pyIn));

}
static PythonToCppFunc is_Device_PythonToCpp_Device_Convertible(PyObject *pyIn) {
    if (PyObject_TypeCheck(pyIn, SbkUPLSTypes[SBK_DEVICE_IDX]))
        return Device_PythonToCpp_Device;
    return {};
}
static PyObject *Device_CppToPython_Device(const void *cppIn) {
    const int castCppIn = int(*reinterpret_cast<const ::Device *>(cppIn));
    return Shiboken::Enum::newItem(SbkUPLSTypes[SBK_DEVICE_IDX], castCppIn);

}



// Module initialization ------------------------------------------------------------
// Container Type converters.

// C++ to Python conversion for type 'std::list<std::string >'.
static PyObject *std_list_std_string__CppToPython_std_list_std_string_(const void *cppIn) {
    auto &cppInRef = *reinterpret_cast<::std::list<std::string > *>(const_cast<void *>(cppIn));
    PyObject* pyOut = PyList_New((int) cppInRef.size());
    ::std::list<std::string >::const_iterator it = cppInRef.begin();
    for (int idx = 0; it != cppInRef.end(); ++it, ++idx) {
        ::std::string cppItem(*it);
        PyList_SET_ITEM(pyOut, idx, Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<std::string>(), &cppItem));
    }
    return pyOut;

}
static void std_list_std_string__PythonToCpp_std_list_std_string_(PyObject *pyIn, void *cppOut) {
    auto &cppOutRef = *reinterpret_cast<::std::list<std::string > *>(cppOut);
    Shiboken::AutoDecRef seq(PySequence_Fast(pyIn, 0));
    for (int i = 0; i < PySequence_Fast_GET_SIZE(seq.object()); i++) {
        PyObject* pyItem = PySequence_Fast_GET_ITEM(seq.object(), i);
        ::std::string cppItem;
        Shiboken::Conversions::pythonToCppCopy(Shiboken::Conversions::PrimitiveTypeConverter<std::string>(), pyItem, &(cppItem));
        cppOutRef.push_back(cppItem);
    }

}
static PythonToCppFunc is_std_list_std_string__PythonToCpp_std_list_std_string__Convertible(PyObject *pyIn) {
    if (Shiboken::Conversions::convertibleSequenceTypes(Shiboken::Conversions::PrimitiveTypeConverter<std::string>(), pyIn))
        return std_list_std_string__PythonToCpp_std_list_std_string_;
    return {};
}


#if defined _WIN32 || defined __CYGWIN__
    #define SBK_EXPORT_MODULE __declspec(dllexport)
#elif __GNUC__ >= 4
    #define SBK_EXPORT_MODULE __attribute__ ((visibility("default")))
#else
    #define SBK_EXPORT_MODULE
#endif

#ifdef IS_PY3K
static struct PyModuleDef moduledef = {
    /* m_base     */ PyModuleDef_HEAD_INIT,
    /* m_name     */ "UPLS",
    /* m_doc      */ nullptr,
    /* m_size     */ -1,
    /* m_methods  */ UPLS_methods,
    /* m_reload   */ nullptr,
    /* m_traverse */ nullptr,
    /* m_clear    */ nullptr,
    /* m_free     */ nullptr
};

#endif

// The signatures string for the global functions.
// Multiple signatures have their index "n:" in front.
static const char *UPLS_SignatureStrings[] = {
    nullptr}; // Sentinel

SBK_MODULE_INIT_FUNCTION_BEGIN(UPLS)
    // Create an array of wrapper types for the current module.
    static PyTypeObject *cppApi[SBK_UPLS_IDX_COUNT];
    SbkUPLSTypes = cppApi;

    // Create an array of primitive type converters for the current module.
    static SbkConverter *sbkConverters[SBK_UPLS_CONVERTERS_IDX_COUNT];
    SbkUPLSTypeConverters = sbkConverters;

#ifdef IS_PY3K
    PyObject *module = Shiboken::Module::create("UPLS", &moduledef);
#else
    PyObject *module = Shiboken::Module::create("UPLS", UPLS_methods);
#endif

    // Make module available from global scope
    SbkUPLSModuleObject = module;

    // Initialize classes in the type system
    init_WinchInfo(module);
    init_Warning(module);
    init_UPLS_Controller(module);
    init_LedInfo(module);
    init_LedInfo_Led(reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LEDINFO_IDX])->tp_dict);
    init_LedInfo_Led_Pulsing(reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX])->tp_dict);
    init_LedInfo_Led_Normal(reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX])->tp_dict);
    init_LandingGearInfo(module);
    init_LandingGearInfo_Leg(reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX])->tp_dict);
    init_HookInfo(module);
    init_HookInfo_Latch(reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_HOOKINFO_IDX])->tp_dict);
    init_LedInfo_Led_FadeInFadeOut(reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX])->tp_dict);
    init_Error(module);
    init_Command(module);
    init_LedInfo_Led_Blinking(reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX])->tp_dict);
    init_HookInfo_Battery(reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_HOOKINFO_IDX])->tp_dict);

    // Register converter for type 'std::list<std::string>'.
    SbkUPLSTypeConverters[SBK_UPLS_STD_LIST_STD_STRING_IDX] = Shiboken::Conversions::createConverter(&PyList_Type, std_list_std_string__CppToPython_std_list_std_string_);
    Shiboken::Conversions::registerConverterName(SbkUPLSTypeConverters[SBK_UPLS_STD_LIST_STD_STRING_IDX], "std::list<std::string>");
    Shiboken::Conversions::addPythonToCppValueConversion(SbkUPLSTypeConverters[SBK_UPLS_STD_LIST_STD_STRING_IDX],
        std_list_std_string__PythonToCpp_std_list_std_string_,
        is_std_list_std_string__PythonToCpp_std_list_std_string__Convertible);

    // Initialization of enums.

    // Initialization of enum 'Device'.
    SbkUPLSTypes[SBK_DEVICE_IDX] = Shiboken::Enum::createGlobalEnum(module,
        "Device",
        "1:UPLS.Device",
        "Device");
    if (!SbkUPLSTypes[SBK_DEVICE_IDX])
        return SBK_MODULE_INIT_ERROR;

    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_DEVICE_IDX],
        SbkUPLSTypes[SBK_DEVICE_IDX], "Unknown", (long) Device::Unknown))
        return SBK_MODULE_INIT_ERROR;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_DEVICE_IDX],
        SbkUPLSTypes[SBK_DEVICE_IDX], "Xavier", (long) Device::Xavier))
        return SBK_MODULE_INIT_ERROR;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_DEVICE_IDX],
        SbkUPLSTypes[SBK_DEVICE_IDX], "Hook", (long) Device::Hook))
        return SBK_MODULE_INIT_ERROR;
    if (!Shiboken::Enum::createScopedEnumItem(SbkUPLSTypes[SBK_DEVICE_IDX],
        SbkUPLSTypes[SBK_DEVICE_IDX], "MainController", (long) Device::MainController))
        return SBK_MODULE_INIT_ERROR;
    // Register converter for enum 'Device'.
    {
        SbkConverter *converter = Shiboken::Conversions::createConverter(SbkUPLSTypes[SBK_DEVICE_IDX],
            Device_CppToPython_Device);
        Shiboken::Conversions::addPythonToCppValueConversion(converter,
            Device_PythonToCpp_Device,
            is_Device_PythonToCpp_Device_Convertible);
        Shiboken::Enum::setTypeConverter(SbkUPLSTypes[SBK_DEVICE_IDX], converter);
        Shiboken::Conversions::registerConverterName(converter, "Device");
    }
    // End of 'Device' enum.

    // Register primitive types converters.

    Shiboken::Module::registerTypes(module, SbkUPLSTypes);
    Shiboken::Module::registerTypeConverters(module, SbkUPLSTypeConverters);

    if (PyErr_Occurred()) {
        PyErr_Print();
        Py_FatalError("can't initialize module UPLS");
    }
    FinishSignatureInitialization(module, UPLS_SignatureStrings);

SBK_MODULE_INIT_FUNCTION_END
