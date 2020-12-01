

#ifndef SBK_UPLS_PYTHON_H
#define SBK_UPLS_PYTHON_H

#include <sbkpython.h>
#include <sbkconverter.h>
// Bound library includes
#include <upls_controller.h>
#include <packet/packet.h>
// Conversion Includes - Primitive Types

// Conversion Includes - Container Types
#include <list>

// Type indices
enum : int {
    SBK_COMMAND_IDX                                          = 0,
    SBK_COMMAND_CODE_IDX                                     = 1,
    SBK_ERROR_IDX                                            = 3,
    SBK_ERROR_CODE_IDX                                       = 4,
    SBK_HOOKINFO_IDX                                         = 5,
    SBK_HOOKINFO_BATTERY_IDX                                 = 6,
    SBK_HOOKINFO_BATTERY_STATE_IDX                           = 7,
    SBK_HOOKINFO_LATCH_IDX                                   = 8,
    SBK_HOOKINFO_LATCH_STATE_IDX                             = 9,
    SBK_LANDINGGEARINFO_IDX                                  = 10,
    SBK_LANDINGGEARINFO_LEG_IDX                              = 11,
    SBK_LANDINGGEARINFO_LEG_STATUS_IDX                       = 12,
    SBK_LEDINFO_IDX                                          = 13,
    SBK_LEDINFO_LED_IDX                                      = 14,
    SBK_LEDINFO_LED_MODE_IDX                                 = 15,
    SBK_LEDINFO_LED_SETTINGS_IDX                             = 16,
    SBK_UPLS_CONTROLLER_IDX                                  = 17,
    SBK_WARNING_IDX                                          = 18,
    SBK_WARNING_CODE_IDX                                     = 19,
    SBK_WINCHINFO_IDX                                        = 20,
    SBK_WINCHINFO_STATUS_IDX                                 = 21,
    SBK_DEVICE_IDX                                           = 2,
    SBK_UPLS_IDX_COUNT                                       = 22
};
// This variable stores all Python types exported by this module.
extern PyTypeObject **SbkUPLSTypes;

// This variable stores the Python module object exported by this module.
extern PyObject *SbkUPLSModuleObject;

// This variable stores all type converters exported by this module.
extern SbkConverter **SbkUPLSTypeConverters;

// Converter indices
enum : int {
    SBK_UPLS_STD_LIST_STD_STRING_IDX                         = 0, // std::list<std::string >
    SBK_UPLS_CONVERTERS_IDX_COUNT                            = 1
};
// Macros for type check

namespace Shiboken
{

// PyType functions, to get the PyObjectType for a type T
template<> inline PyTypeObject *SbkType< ::Device >() { return SbkUPLSTypes[SBK_DEVICE_IDX]; }
template<> inline PyTypeObject *SbkType< ::Command::Code >() { return SbkUPLSTypes[SBK_COMMAND_CODE_IDX]; }
template<> inline PyTypeObject *SbkType< ::Command >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_COMMAND_IDX]); }
template<> inline PyTypeObject *SbkType< ::Error::Code >() { return SbkUPLSTypes[SBK_ERROR_CODE_IDX]; }
template<> inline PyTypeObject *SbkType< ::Error >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_ERROR_IDX]); }
template<> inline PyTypeObject *SbkType< ::HookInfo >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_HOOKINFO_IDX]); }
template<> inline PyTypeObject *SbkType< ::HookInfo::Battery::State >() { return SbkUPLSTypes[SBK_HOOKINFO_BATTERY_STATE_IDX]; }
template<> inline PyTypeObject *SbkType< ::HookInfo::Battery >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_HOOKINFO_BATTERY_IDX]); }
template<> inline PyTypeObject *SbkType< ::HookInfo::Latch::State >() { return SbkUPLSTypes[SBK_HOOKINFO_LATCH_STATE_IDX]; }
template<> inline PyTypeObject *SbkType< ::HookInfo::Latch >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_HOOKINFO_LATCH_IDX]); }
template<> inline PyTypeObject *SbkType< ::LandingGearInfo >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX]); }
template<> inline PyTypeObject *SbkType< ::LandingGearInfo::Leg::Status >() { return SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_STATUS_IDX]; }
template<> inline PyTypeObject *SbkType< ::LandingGearInfo::Leg >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_LEG_IDX]); }
template<> inline PyTypeObject *SbkType< ::LedInfo >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LEDINFO_IDX]); }
template<> inline PyTypeObject *SbkType< ::LedInfo::Led::Mode >() { return SbkUPLSTypes[SBK_LEDINFO_LED_MODE_IDX]; }
template<> inline PyTypeObject *SbkType< ::LedInfo::Led >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LEDINFO_LED_IDX]); }
template<> inline PyTypeObject *SbkType< ::LedInfo::Led::Settings >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_LEDINFO_LED_SETTINGS_IDX]); }
template<> inline PyTypeObject *SbkType< ::UPLS_Controller >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX]); }
template<> inline PyTypeObject *SbkType< ::Warning::Code >() { return SbkUPLSTypes[SBK_WARNING_CODE_IDX]; }
template<> inline PyTypeObject *SbkType< ::Warning >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_WARNING_IDX]); }
template<> inline PyTypeObject *SbkType< ::WinchInfo::Status >() { return SbkUPLSTypes[SBK_WINCHINFO_STATUS_IDX]; }
template<> inline PyTypeObject *SbkType< ::WinchInfo >() { return reinterpret_cast<PyTypeObject *>(SbkUPLSTypes[SBK_WINCHINFO_IDX]); }

} // namespace Shiboken

#endif // SBK_UPLS_PYTHON_H

