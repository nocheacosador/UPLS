
// default includes
#include <shiboken.h>
#include <typeinfo>
#include <iterator>

// module include
#include "upls_python.h"

// main header
#include "upls_controller_wrapper.h"

// inner classes

// Extra includes
#include <list>
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
Sbk_UPLS_Controller_Init(PyObject *self, PyObject *args, PyObject *kwds)
{
    SbkObject *sbkSelf = reinterpret_cast<SbkObject *>(self);
    if (Shiboken::Object::isUserType(self) && !Shiboken::ObjectType::canCallConstructor(self->ob_type, Shiboken::SbkType< ::UPLS_Controller >()))
        return -1;

    ::UPLS_Controller *cptr{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // UPLS_Controller()
            cptr = new ::UPLS_Controller();
        }
    }

    if (PyErr_Occurred() || !Shiboken::Object::setCppPointer(sbkSelf, Shiboken::SbkType< ::UPLS_Controller >(), cptr)) {
        delete cptr;
        return -1;
    }
    Shiboken::Object::setValidCpp(sbkSelf, true);
    if (Shiboken::BindingManager::instance().hasWrapper(cptr)) {
        Shiboken::BindingManager::instance().releaseWrapper(Shiboken::BindingManager::instance().retrieveWrapper(cptr));
    }
    Shiboken::BindingManager::instance().registerWrapper(sbkSelf, cptr);


    return 1;
}

static PyObject *Sbk_UPLS_ControllerFunc_clearAllErrors(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // clearAllErrors()
            cppSelf->clearAllErrors();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_clearAllWarnings(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // clearAllWarnings()
            cppSelf->clearAllWarnings();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_error(PyObject *self, PyObject *pyArg)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: UPLS_Controller::error(const char*)
    if (Shiboken::String::check(pyArg) && (pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<const char *>(), (pyArg)))) {
        overloadId = 0; // error(const char*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_UPLS_ControllerFunc_error_TypeError;

    // Call function/method
    {
        const char* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // error(const char*)
            cppSelf->error(cppArg0);
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_UPLS_ControllerFunc_error_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "UPLS.UPLS_Controller.error");
        return {};
}

static PyObject *Sbk_UPLS_ControllerFunc_errorsOccured(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // errorsOccured()
            bool cppResult = cppSelf->errorsOccured();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_hookInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // hookInfo()
            HookInfo cppResult = cppSelf->hookInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_HOOKINFO_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_hookInfoUpdateFrequency(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // hookInfoUpdateFrequency()
            float cppResult = cppSelf->hookInfoUpdateFrequency();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<float>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_landingGearInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // landingGearInfo()
            LandingGearInfo cppResult = cppSelf->landingGearInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LANDINGGEARINFO_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_landingGearInfoUpdateFrequency(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // landingGearInfoUpdateFrequency()
            float cppResult = cppSelf->landingGearInfoUpdateFrequency();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<float>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_ledInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // ledInfo()
            LedInfo cppResult = cppSelf->ledInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_LEDINFO_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_ledInfoUpdateFrequency(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // ledInfoUpdateFrequency()
            float cppResult = cppSelf->ledInfoUpdateFrequency();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<float>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_ledOff(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // ledOff()
            cppSelf->ledOff();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_ledOn(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // ledOn()
            cppSelf->ledOn();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_listAvailablePorts(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // listAvailablePorts()
            std::list<std::string > cppResult = cppSelf->listAvailablePorts();
            pyResult = Shiboken::Conversions::copyToPython(SbkUPLSTypeConverters[SBK_UPLS_STD_LIST_STD_STRING_IDX], &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_message(PyObject *self, PyObject *pyArg)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: UPLS_Controller::message(const char*)
    if (Shiboken::String::check(pyArg) && (pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<const char *>(), (pyArg)))) {
        overloadId = 0; // message(const char*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_UPLS_ControllerFunc_message_TypeError;

    // Call function/method
    {
        const char* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // message(const char*)
            cppSelf->message(cppArg0);
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_UPLS_ControllerFunc_message_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "UPLS.UPLS_Controller.message");
        return {};
}

static PyObject *Sbk_UPLS_ControllerFunc_messagesReceived(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // messagesReceived()
            bool cppResult = cppSelf->messagesReceived();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_printAllErrors(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // printAllErrors()
            cppSelf->printAllErrors();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_printAllMessages(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // printAllMessages()
            cppSelf->printAllMessages();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_printAllWarnings(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // printAllWarnings()
            cppSelf->printAllWarnings();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_printAvailablePorts(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // printAvailablePorts()
            cppSelf->printAvailablePorts();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_printError(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // printError()
            cppSelf->printError();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_printWarning(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // printWarning()
            cppSelf->printWarning();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_setSerialPort(PyObject *self, PyObject *pyArg)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: UPLS_Controller::setSerialPort(const char*)
    if (Shiboken::String::check(pyArg) && (pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<const char *>(), (pyArg)))) {
        overloadId = 0; // setSerialPort(const char*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_UPLS_ControllerFunc_setSerialPort_TypeError;

    // Call function/method
    {
        const char* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // setSerialPort(const char*)
            cppSelf->setSerialPort(cppArg0);
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_UPLS_ControllerFunc_setSerialPort_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "UPLS.UPLS_Controller.setSerialPort");
        return {};
}

static PyObject *Sbk_UPLS_ControllerFunc_start(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // start()
            bool cppResult = cppSelf->start();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_stop(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // stop()
            cppSelf->stop();
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;
}

static PyObject *Sbk_UPLS_ControllerFunc_warning(PyObject *self, PyObject *pyArg)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    int overloadId = -1;
    PythonToCppFunc pythonToCpp{};
    SBK_UNUSED(pythonToCpp)

    // Overloaded function decisor
    // 0: UPLS_Controller::warning(const char*)
    if (Shiboken::String::check(pyArg) && (pythonToCpp = Shiboken::Conversions::isPythonToCppConvertible(Shiboken::Conversions::PrimitiveTypeConverter<const char *>(), (pyArg)))) {
        overloadId = 0; // warning(const char*)
    }

    // Function signature not found.
    if (overloadId == -1) goto Sbk_UPLS_ControllerFunc_warning_TypeError;

    // Call function/method
    {
        const char* cppArg0;
        pythonToCpp(pyArg, &cppArg0);

        if (!PyErr_Occurred()) {
            // warning(const char*)
            cppSelf->warning(cppArg0);
        }
    }

    if (PyErr_Occurred()) {
        return {};
    }
    Py_RETURN_NONE;

    Sbk_UPLS_ControllerFunc_warning_TypeError:
        Shiboken::setErrorAboutWrongArguments(pyArg, "UPLS.UPLS_Controller.warning");
        return {};
}

static PyObject *Sbk_UPLS_ControllerFunc_warningsReceived(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // warningsReceived()
            bool cppResult = cppSelf->warningsReceived();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<bool>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_winchInfo(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // winchInfo()
            WinchInfo cppResult = cppSelf->winchInfo();
            pyResult = Shiboken::Conversions::copyToPython(reinterpret_cast<SbkObjectType *>(SbkUPLSTypes[SBK_WINCHINFO_IDX]), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyObject *Sbk_UPLS_ControllerFunc_winchInfoUpdateFrequency(PyObject *self)
{
    if (!Shiboken::Object::isValid(self))
        return {};
    auto cppSelf = reinterpret_cast< ::UPLS_Controller *>(Shiboken::Conversions::cppPointer(SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX], reinterpret_cast<SbkObject *>(self)));
    SBK_UNUSED(cppSelf)
    PyObject *pyResult{};

    // Call function/method
    {

        if (!PyErr_Occurred()) {
            // winchInfoUpdateFrequency()
            float cppResult = cppSelf->winchInfoUpdateFrequency();
            pyResult = Shiboken::Conversions::copyToPython(Shiboken::Conversions::PrimitiveTypeConverter<float>(), &cppResult);
        }
    }

    if (PyErr_Occurred() || !pyResult) {
        Py_XDECREF(pyResult);
        return {};
    }
    return pyResult;
}

static PyMethodDef Sbk_UPLS_Controller_methods[] = {
    {"clearAllErrors", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_clearAllErrors), METH_NOARGS},
    {"clearAllWarnings", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_clearAllWarnings), METH_NOARGS},
    {"error", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_error), METH_O},
    {"errorsOccured", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_errorsOccured), METH_NOARGS},
    {"hookInfo", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_hookInfo), METH_NOARGS},
    {"hookInfoUpdateFrequency", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_hookInfoUpdateFrequency), METH_NOARGS},
    {"landingGearInfo", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_landingGearInfo), METH_NOARGS},
    {"landingGearInfoUpdateFrequency", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_landingGearInfoUpdateFrequency), METH_NOARGS},
    {"ledInfo", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_ledInfo), METH_NOARGS},
    {"ledInfoUpdateFrequency", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_ledInfoUpdateFrequency), METH_NOARGS},
    {"ledOff", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_ledOff), METH_NOARGS},
    {"ledOn", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_ledOn), METH_NOARGS},
    {"listAvailablePorts", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_listAvailablePorts), METH_NOARGS},
    {"message", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_message), METH_O},
    {"messagesReceived", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_messagesReceived), METH_NOARGS},
    {"printAllErrors", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_printAllErrors), METH_NOARGS},
    {"printAllMessages", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_printAllMessages), METH_NOARGS},
    {"printAllWarnings", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_printAllWarnings), METH_NOARGS},
    {"printAvailablePorts", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_printAvailablePorts), METH_NOARGS},
    {"printError", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_printError), METH_NOARGS},
    {"printWarning", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_printWarning), METH_NOARGS},
    {"setSerialPort", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_setSerialPort), METH_O},
    {"start", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_start), METH_NOARGS},
    {"stop", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_stop), METH_NOARGS},
    {"warning", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_warning), METH_O},
    {"warningsReceived", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_warningsReceived), METH_NOARGS},
    {"winchInfo", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_winchInfo), METH_NOARGS},
    {"winchInfoUpdateFrequency", reinterpret_cast<PyCFunction>(Sbk_UPLS_ControllerFunc_winchInfoUpdateFrequency), METH_NOARGS},

    {nullptr, nullptr} // Sentinel
};

} // extern "C"

static int Sbk_UPLS_Controller_traverse(PyObject *self, visitproc visit, void *arg)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_traverse(self, visit, arg);
}
static int Sbk_UPLS_Controller_clear(PyObject *self)
{
    return reinterpret_cast<PyTypeObject *>(SbkObject_TypeF())->tp_clear(self);
}
// Class Definition -----------------------------------------------
extern "C" {
static SbkObjectType *_Sbk_UPLS_Controller_Type = nullptr;
static SbkObjectType *Sbk_UPLS_Controller_TypeF(void)
{
    return _Sbk_UPLS_Controller_Type;
}

static PyType_Slot Sbk_UPLS_Controller_slots[] = {
    {Py_tp_base,        nullptr}, // inserted by introduceWrapperType
    {Py_tp_dealloc,     reinterpret_cast<void *>(&SbkDeallocWrapper)},
    {Py_tp_repr,        nullptr},
    {Py_tp_hash,        nullptr},
    {Py_tp_call,        nullptr},
    {Py_tp_str,         nullptr},
    {Py_tp_getattro,    nullptr},
    {Py_tp_setattro,    nullptr},
    {Py_tp_traverse,    reinterpret_cast<void *>(Sbk_UPLS_Controller_traverse)},
    {Py_tp_clear,       reinterpret_cast<void *>(Sbk_UPLS_Controller_clear)},
    {Py_tp_richcompare, nullptr},
    {Py_tp_iter,        nullptr},
    {Py_tp_iternext,    nullptr},
    {Py_tp_methods,     reinterpret_cast<void *>(Sbk_UPLS_Controller_methods)},
    {Py_tp_getset,      nullptr},
    {Py_tp_init,        reinterpret_cast<void *>(Sbk_UPLS_Controller_Init)},
    {Py_tp_new,         reinterpret_cast<void *>(SbkObjectTpNew)},
    {0, nullptr}
};
static PyType_Spec Sbk_UPLS_Controller_spec = {
    "1:UPLS.UPLS_Controller",
    sizeof(SbkObject),
    0,
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES|Py_TPFLAGS_HAVE_GC,
    Sbk_UPLS_Controller_slots
};

} //extern "C"


// Type conversion functions.

// Python to C++ pointer conversion - returns the C++ object of the Python wrapper (keeps object identity).
static void UPLS_Controller_PythonToCpp_UPLS_Controller_PTR(PyObject *pyIn, void *cppOut) {
    Shiboken::Conversions::pythonToCppPointer(Sbk_UPLS_Controller_TypeF(), pyIn, cppOut);
}
static PythonToCppFunc is_UPLS_Controller_PythonToCpp_UPLS_Controller_PTR_Convertible(PyObject *pyIn) {
    if (pyIn == Py_None)
        return Shiboken::Conversions::nonePythonToCppNullPtr;
    if (PyObject_TypeCheck(pyIn, reinterpret_cast<PyTypeObject *>(Sbk_UPLS_Controller_TypeF())))
        return UPLS_Controller_PythonToCpp_UPLS_Controller_PTR;
    return {};
}

// C++ to Python pointer conversion - tries to find the Python wrapper for the C++ object (keeps object identity).
static PyObject *UPLS_Controller_PTR_CppToPython_UPLS_Controller(const void *cppIn) {
    auto pyOut = reinterpret_cast<PyObject *>(Shiboken::BindingManager::instance().retrieveWrapper(cppIn));
    if (pyOut) {
        Py_INCREF(pyOut);
        return pyOut;
    }
    bool changedTypeName = false;
    auto tCppIn = reinterpret_cast<const ::UPLS_Controller *>(cppIn);
    const char *typeName = typeid(*tCppIn).name();
    auto sbkType = Shiboken::ObjectType::typeForTypeName(typeName);
    if (sbkType && Shiboken::ObjectType::hasSpecialCastFunction(sbkType)) {
        typeName = typeNameOf(tCppIn);
        changedTypeName = true;
    }
    PyObject *result = Shiboken::Object::newObject(Sbk_UPLS_Controller_TypeF(), const_cast<void *>(cppIn), false, /* exactType */ changedTypeName, typeName);
    if (changedTypeName)
        delete [] typeName;
    return result;
}

// The signatures string for the functions.
// Multiple signatures have their index "n:" in front.
static const char *UPLS_Controller_SignatureStrings[] = {
    "UPLS.UPLS_Controller(self)",
    "UPLS.UPLS_Controller.clearAllErrors(self)",
    "UPLS.UPLS_Controller.clearAllWarnings(self)",
    "UPLS.UPLS_Controller.error(self,error_msg:char*)",
    "UPLS.UPLS_Controller.errorsOccured(self)->bool",
    "UPLS.UPLS_Controller.hookInfo(self)->UPLS.HookInfo",
    "UPLS.UPLS_Controller.hookInfoUpdateFrequency(self)->float",
    "UPLS.UPLS_Controller.landingGearInfo(self)->UPLS.LandingGearInfo",
    "UPLS.UPLS_Controller.landingGearInfoUpdateFrequency(self)->float",
    "UPLS.UPLS_Controller.ledInfo(self)->UPLS.LedInfo",
    "UPLS.UPLS_Controller.ledInfoUpdateFrequency(self)->float",
    "UPLS.UPLS_Controller.ledOff(self)",
    "UPLS.UPLS_Controller.ledOn(self)",
    "UPLS.UPLS_Controller.listAvailablePorts(self)->std.list[std.string]",
    "UPLS.UPLS_Controller.message(self,message:char*)",
    "UPLS.UPLS_Controller.messagesReceived(self)->bool",
    "UPLS.UPLS_Controller.printAllErrors(self)",
    "UPLS.UPLS_Controller.printAllMessages(self)",
    "UPLS.UPLS_Controller.printAllWarnings(self)",
    "UPLS.UPLS_Controller.printAvailablePorts(self)",
    "UPLS.UPLS_Controller.printError(self)",
    "UPLS.UPLS_Controller.printWarning(self)",
    "UPLS.UPLS_Controller.setSerialPort(self,portName:char*)",
    "UPLS.UPLS_Controller.start(self)->bool",
    "UPLS.UPLS_Controller.stop(self)",
    "UPLS.UPLS_Controller.warning(self,warning_msg:char*)",
    "UPLS.UPLS_Controller.warningsReceived(self)->bool",
    "UPLS.UPLS_Controller.winchInfo(self)->UPLS.WinchInfo",
    "UPLS.UPLS_Controller.winchInfoUpdateFrequency(self)->float",
    nullptr}; // Sentinel

void init_UPLS_Controller(PyObject *module)
{
    _Sbk_UPLS_Controller_Type = Shiboken::ObjectType::introduceWrapperType(
        module,
        "UPLS_Controller",
        "UPLS_Controller*",
        &Sbk_UPLS_Controller_spec,
        UPLS_Controller_SignatureStrings,
        &Shiboken::callCppDestructor< ::UPLS_Controller >,
        0,
        0,
        0    );
    
    SbkUPLSTypes[SBK_UPLS_CONTROLLER_IDX]
        = reinterpret_cast<PyTypeObject *>(Sbk_UPLS_Controller_TypeF());

    // Register Converter
    SbkConverter *converter = Shiboken::Conversions::createConverter(Sbk_UPLS_Controller_TypeF(),
        UPLS_Controller_PythonToCpp_UPLS_Controller_PTR,
        is_UPLS_Controller_PythonToCpp_UPLS_Controller_PTR_Convertible,
        UPLS_Controller_PTR_CppToPython_UPLS_Controller);

    Shiboken::Conversions::registerConverterName(converter, "UPLS_Controller");
    Shiboken::Conversions::registerConverterName(converter, "UPLS_Controller*");
    Shiboken::Conversions::registerConverterName(converter, "UPLS_Controller&");
    Shiboken::Conversions::registerConverterName(converter, typeid(::UPLS_Controller).name());



}
