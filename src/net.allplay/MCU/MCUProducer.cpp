//-----------------------------------------------------------------------------
// <auto-generated> 
//   This code was generated by a tool. 
// 
//   Changes to this file may cause incorrect behavior and will be lost if  
//   the code is regenerated.
//
//   Tool: AllJoynCodeGenerator.exe
//
//   This tool is located in the Windows 10 SDK and the Windows 10 AllJoyn 
//   Visual Studio Extension in the Visual Studio Gallery.  
//
//   The generated code should be packaged in a Windows 10 C++/CX Runtime  
//   Component which can be consumed in any UWP-supported language using 
//   APIs that are available in Windows.Devices.AllJoyn.
//
//   Using AllJoynCodeGenerator - Invoke the following command with a valid 
//   Introspection XML file and a writable output directory:
//     AllJoynCodeGenerator -i <INPUT XML FILE> -o <OUTPUT DIRECTORY>
// </auto-generated>
//-----------------------------------------------------------------------------
#include "pch.h"

using namespace concurrency;
using namespace Microsoft::WRL;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Devices::AllJoyn;
using namespace net::allplay::MCU;

std::map<alljoyn_busobject, WeakReference*> MCUProducer::SourceObjects;
std::map<alljoyn_interfacedescription, WeakReference*> MCUProducer::SourceInterfaces;

MCUProducer::MCUProducer(AllJoynBusAttachment^ busAttachment)
    : m_busAttachment(busAttachment),
    m_sessionListener(nullptr),
    m_busObject(nullptr),
    m_sessionPort(0),
    m_sessionId(0)
{
    m_weak = new WeakReference(this);
    ServiceObjectPath = ref new String(L"/net/allplay/mediaplayer");
    m_signals = ref new MCUSignals();
    m_busAttachmentStateChangedToken.Value = 0;
}

MCUProducer::~MCUProducer()
{
    UnregisterFromBus();
    delete m_weak;
}

void MCUProducer::UnregisterFromBus()
{
    if ((nullptr != m_busAttachment) && (0 != m_busAttachmentStateChangedToken.Value))
    {
        m_busAttachment->StateChanged -= m_busAttachmentStateChangedToken;
        m_busAttachmentStateChangedToken.Value = 0;
    }
    if ((nullptr != m_busAttachment) && (nullptr != SessionPortListener))
    {
        alljoyn_busattachment_unbindsessionport(AllJoynHelpers::GetInternalBusAttachment(m_busAttachment), m_sessionPort);
        alljoyn_sessionportlistener_destroy(SessionPortListener);
        SessionPortListener = nullptr;
    }
    if ((nullptr != m_busAttachment) && (nullptr != BusObject))
    {
        alljoyn_busattachment_unregisterbusobject(AllJoynHelpers::GetInternalBusAttachment(m_busAttachment), BusObject);
        alljoyn_busobject_destroy(BusObject);
        BusObject = nullptr;
    }
    if (nullptr != SessionListener)
    {
        alljoyn_sessionlistener_destroy(SessionListener);
        SessionListener = nullptr;
    }
}

bool MCUProducer::OnAcceptSessionJoiner(_In_ alljoyn_sessionport sessionPort, _In_ PCSTR joiner, _In_ const alljoyn_sessionopts opts)
{
    UNREFERENCED_PARAMETER(sessionPort); UNREFERENCED_PARAMETER(joiner); UNREFERENCED_PARAMETER(opts);
    
    return true;
}

void MCUProducer::InitializeSignals(_In_ alljoyn_sessionid id)
{
	m_signals->Initialize(BusObject, id);
	m_sessionId = id;
}

void MCUProducer::OnSessionJoined(_In_ alljoyn_sessionport sessionPort, _In_ alljoyn_sessionid id, _In_ PCSTR joiner)
{
    UNREFERENCED_PARAMETER(joiner);

    // We initialize the Signals object after the session has been joined, because it needs
    // the session id.
    m_signals->Initialize(BusObject, id);
    m_sessionPort = sessionPort;
    m_sessionId = id;

    alljoyn_sessionlistener_callbacks callbacks =
    {
        AllJoynHelpers::SessionLostHandler<MCUProducer>,
        AllJoynHelpers::SessionMemberAddedHandler<MCUProducer>,
        AllJoynHelpers::SessionMemberRemovedHandler<MCUProducer>
    };

    SessionListener = alljoyn_sessionlistener_create(&callbacks, m_weak);
    alljoyn_busattachment_setsessionlistener(AllJoynHelpers::GetInternalBusAttachment(m_busAttachment), id, SessionListener);
}

void MCUProducer::OnSessionLost(_In_ alljoyn_sessionid sessionId, _In_ alljoyn_sessionlostreason reason)
{
    if (sessionId == m_sessionId)
    {
        AllJoynSessionLostEventArgs^ args = ref new AllJoynSessionLostEventArgs(static_cast<AllJoynSessionLostReason>(reason));
        SessionLost(this, args);
    }
}

void MCUProducer::OnSessionMemberAdded(_In_ alljoyn_sessionid sessionId, _In_ PCSTR uniqueName)
{
    if (sessionId == m_sessionId)
    {
        auto args = ref new AllJoynSessionMemberAddedEventArgs(AllJoynHelpers::MultibyteToPlatformString(uniqueName));
        SessionMemberAdded(this, args);
    }
}

void MCUProducer::OnSessionMemberRemoved(_In_ alljoyn_sessionid sessionId, _In_ PCSTR uniqueName)
{
    if (sessionId == m_sessionId)
    {
        auto args = ref new AllJoynSessionMemberRemovedEventArgs(AllJoynHelpers::MultibyteToPlatformString(uniqueName));
        SessionMemberRemoved(this, args);
    }
}

void MCUProducer::BusAttachmentStateChanged(_In_ AllJoynBusAttachment^ sender, _In_ AllJoynBusAttachmentStateChangedEventArgs^ args)
{
    if (args->State == AllJoynBusAttachmentState::Connected)
    {   
        QStatus result = AllJoynHelpers::CreateProducerSession<MCUProducer>(m_busAttachment, m_weak);
        if (ER_OK != result)
        {
            StopInternal(result);
            return;
        }
    }
    else if (args->State == AllJoynBusAttachmentState::Disconnected)
    {
        StopInternal(ER_BUS_STOPPING);
    }
}

void MCUProducer::CallAdvanceLoopModeHandler(_Inout_ alljoyn_busobject busObject, _In_ alljoyn_message message)
{
    auto source = SourceObjects.find(busObject);
    if (source == SourceObjects.end())
    {
        return;
    }

    MCUProducer^ producer = source->second->Resolve<MCUProducer>();
    if (producer->Service != nullptr)
    {
        AllJoynMessageInfo^ callInfo = ref new AllJoynMessageInfo(AllJoynHelpers::MultibyteToPlatformString(alljoyn_message_getsender(message)));


        MCUAdvanceLoopModeResult^ result = create_task(producer->Service->AdvanceLoopModeAsync(callInfo)).get();
        create_task([](){}).then([=]
        {
            int32 status;

            if (nullptr == result)
            {
                alljoyn_busobject_methodreply_status(busObject, message, ER_BUS_NO_LISTENER);
                return;
            }

            status = result->Status;
            if (AllJoynStatus::Ok != status)
            {
                alljoyn_busobject_methodreply_status(busObject, message, static_cast<QStatus>(status));
                return;
            }

            size_t argCount = 0;
            alljoyn_msgarg outputs = alljoyn_msgarg_array_create(argCount);

            alljoyn_busobject_methodreply_args(busObject, message, outputs, argCount);
            alljoyn_msgarg_destroy(outputs);
        }, result->m_creationContext).wait();
    }
}

void MCUProducer::CallGetCurrentItemUrlHandler(_Inout_ alljoyn_busobject busObject, _In_ alljoyn_message message)
{
    auto source = SourceObjects.find(busObject);
    if (source == SourceObjects.end())
    {
        return;
    }

    MCUProducer^ producer = source->second->Resolve<MCUProducer>();
    if (producer->Service != nullptr)
    {
        AllJoynMessageInfo^ callInfo = ref new AllJoynMessageInfo(AllJoynHelpers::MultibyteToPlatformString(alljoyn_message_getsender(message)));


        MCUGetCurrentItemUrlResult^ result = create_task(producer->Service->GetCurrentItemUrlAsync(callInfo)).get();
        create_task([](){}).then([=]
        {
            int32 status;

            if (nullptr == result)
            {
                alljoyn_busobject_methodreply_status(busObject, message, ER_BUS_NO_LISTENER);
                return;
            }

            status = result->Status;
            if (AllJoynStatus::Ok != status)
            {
                alljoyn_busobject_methodreply_status(busObject, message, static_cast<QStatus>(status));
                return;
            }

            size_t argCount = 1;
            alljoyn_msgarg outputs = alljoyn_msgarg_array_create(argCount);

            status = TypeConversionHelpers::SetAllJoynMessageArg(alljoyn_msgarg_array_element(outputs, 0), "s", result->Url);
            if (AllJoynStatus::Ok != status)
            {
                alljoyn_busobject_methodreply_status(busObject, message, static_cast<QStatus>(status));
                alljoyn_msgarg_destroy(outputs);
                return;
            }

            alljoyn_busobject_methodreply_args(busObject, message, outputs, argCount);
            alljoyn_msgarg_destroy(outputs);
        }, result->m_creationContext).wait();
    }
}

void MCUProducer::CallPlayItemHandler(_Inout_ alljoyn_busobject busObject, _In_ alljoyn_message message)
{
    auto source = SourceObjects.find(busObject);
    if (source == SourceObjects.end())
    {
        return;
    }

    MCUProducer^ producer = source->second->Resolve<MCUProducer>();
    if (producer->Service != nullptr)
    {
        AllJoynMessageInfo^ callInfo = ref new AllJoynMessageInfo(AllJoynHelpers::MultibyteToPlatformString(alljoyn_message_getsender(message)));

        Platform::String^ inputArg0;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 0), "s", &inputArg0);
        Platform::String^ inputArg1;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 1), "s", &inputArg1);
        Platform::String^ inputArg2;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 2), "s", &inputArg2);
        Platform::String^ inputArg3;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 3), "s", &inputArg3);
        int64 inputArg4;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 4), "x", &inputArg4);
        Platform::String^ inputArg5;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 5), "s", &inputArg5);
        Platform::String^ inputArg6;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 6), "s", &inputArg6);

        MCUPlayItemResult^ result = create_task(producer->Service->PlayItemAsync(callInfo, inputArg0, inputArg1, inputArg2, inputArg3, inputArg4, inputArg5, inputArg6)).get();
        create_task([](){}).then([=]
        {
            int32 status;

            if (nullptr == result)
            {
                alljoyn_busobject_methodreply_status(busObject, message, ER_BUS_NO_LISTENER);
                return;
            }

            status = result->Status;
            if (AllJoynStatus::Ok != status)
            {
                alljoyn_busobject_methodreply_status(busObject, message, static_cast<QStatus>(status));
                return;
            }

            size_t argCount = 0;
            alljoyn_msgarg outputs = alljoyn_msgarg_array_create(argCount);

            alljoyn_busobject_methodreply_args(busObject, message, outputs, argCount);
            alljoyn_msgarg_destroy(outputs);
        }, result->m_creationContext).wait();
    }
}

void MCUProducer::CallSetExternalSourceHandler(_Inout_ alljoyn_busobject busObject, _In_ alljoyn_message message)
{
    auto source = SourceObjects.find(busObject);
    if (source == SourceObjects.end())
    {
        return;
    }

    MCUProducer^ producer = source->second->Resolve<MCUProducer>();
    if (producer->Service != nullptr)
    {
        AllJoynMessageInfo^ callInfo = ref new AllJoynMessageInfo(AllJoynHelpers::MultibyteToPlatformString(alljoyn_message_getsender(message)));

        Platform::String^ inputArg0;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 0), "s", &inputArg0);
        bool inputArg1;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 1), "b", &inputArg1);
        bool inputArg2;
        (void)TypeConversionHelpers::GetAllJoynMessageArg(alljoyn_message_getarg(message, 2), "b", &inputArg2);

        MCUSetExternalSourceResult^ result = create_task(producer->Service->SetExternalSourceAsync(callInfo, inputArg0, inputArg1, inputArg2)).get();
        create_task([](){}).then([=]
        {
            int32 status;

            if (nullptr == result)
            {
                alljoyn_busobject_methodreply_status(busObject, message, ER_BUS_NO_LISTENER);
                return;
            }

            status = result->Status;
            if (AllJoynStatus::Ok != status)
            {
                alljoyn_busobject_methodreply_status(busObject, message, static_cast<QStatus>(status));
                return;
            }

            size_t argCount = 0;
            alljoyn_msgarg outputs = alljoyn_msgarg_array_create(argCount);

            alljoyn_busobject_methodreply_args(busObject, message, outputs, argCount);
            alljoyn_msgarg_destroy(outputs);
        }, result->m_creationContext).wait();
    }
}

void MCUProducer::CallToggleShuffleModeHandler(_Inout_ alljoyn_busobject busObject, _In_ alljoyn_message message)
{
    auto source = SourceObjects.find(busObject);
    if (source == SourceObjects.end())
    {
        return;
    }

    MCUProducer^ producer = source->second->Resolve<MCUProducer>();
    if (producer->Service != nullptr)
    {
        AllJoynMessageInfo^ callInfo = ref new AllJoynMessageInfo(AllJoynHelpers::MultibyteToPlatformString(alljoyn_message_getsender(message)));


        MCUToggleShuffleModeResult^ result = create_task(producer->Service->ToggleShuffleModeAsync(callInfo)).get();
        create_task([](){}).then([=]
        {
            int32 status;

            if (nullptr == result)
            {
                alljoyn_busobject_methodreply_status(busObject, message, ER_BUS_NO_LISTENER);
                return;
            }

            status = result->Status;
            if (AllJoynStatus::Ok != status)
            {
                alljoyn_busobject_methodreply_status(busObject, message, static_cast<QStatus>(status));
                return;
            }

            size_t argCount = 0;
            alljoyn_msgarg outputs = alljoyn_msgarg_array_create(argCount);

            alljoyn_busobject_methodreply_args(busObject, message, outputs, argCount);
            alljoyn_msgarg_destroy(outputs);
        }, result->m_creationContext).wait();
    }
}

QStatus MCUProducer::AddMethodHandler(_In_ alljoyn_interfacedescription interfaceDescription, _In_ PCSTR methodName, _In_ alljoyn_messagereceiver_methodhandler_ptr handler)
{
    alljoyn_interfacedescription_member member;
    if (!alljoyn_interfacedescription_getmember(interfaceDescription, methodName, &member))
    {
        return ER_BUS_INTERFACE_NO_SUCH_MEMBER;
    }

    return alljoyn_busobject_addmethodhandler(
        m_busObject,
        member,
        handler,
        m_weak);
}

QStatus MCUProducer::AddSignalHandler(_In_ alljoyn_busattachment busAttachment, _In_ alljoyn_interfacedescription interfaceDescription, _In_ PCSTR methodName, _In_ alljoyn_messagereceiver_signalhandler_ptr handler)
{
    alljoyn_interfacedescription_member member;
    if (!alljoyn_interfacedescription_getmember(interfaceDescription, methodName, &member))
    {
        return ER_BUS_INTERFACE_NO_SUCH_MEMBER;
    }

    return alljoyn_busattachment_registersignalhandler(busAttachment, handler, member, NULL);
}

QStatus MCUProducer::OnPropertyGet(_In_ PCSTR interfaceName, _In_ PCSTR propertyName, _Inout_ alljoyn_msgarg value)
{
    UNREFERENCED_PARAMETER(interfaceName);

    if (0 == strcmp(propertyName, "Version"))
    {
        auto task = create_task(Service->GetVersionAsync(nullptr));
        auto result = task.get();

        return create_task([](){}).then([=]() -> QStatus
        {
            if (AllJoynStatus::Ok != result->Status)
            {
                return static_cast<QStatus>(result->Status);
            }
            return static_cast<QStatus>(TypeConversionHelpers::SetAllJoynMessageArg(value, "q", result->Version));
        }, result->m_creationContext).get();
    }

    return ER_BUS_NO_SUCH_PROPERTY;
}

QStatus MCUProducer::OnPropertySet(_In_ PCSTR interfaceName, _In_ PCSTR propertyName, _In_ alljoyn_msgarg value)
{
    UNREFERENCED_PARAMETER(interfaceName);

    return ER_BUS_NO_SUCH_PROPERTY;
}

void MCUProducer::Start(alljoyn_busobject bus)
{
	m_busObject = bus;

    if (nullptr == m_busAttachment)
    {
        StopInternal(ER_FAIL);
        return;
    }

    QStatus result = AllJoynHelpers::CreateInterfaces(m_busAttachment, c_MCUIntrospectionXml);
    if (result != ER_OK)
    {
        StopInternal(result);
        return;
    }

    alljoyn_interfacedescription interfaceDescription = alljoyn_busattachment_getinterface(AllJoynHelpers::GetInternalBusAttachment(m_busAttachment), "net.allplay.MCU");
    if (interfaceDescription == nullptr)
    {
        StopInternal(ER_FAIL);
        return;
    }
    alljoyn_busobject_addinterface_announced(BusObject, interfaceDescription);

    result = AddMethodHandler(
        interfaceDescription, 
        "AdvanceLoopMode", 
        [](alljoyn_busobject busObject, const alljoyn_interfacedescription_member* member, alljoyn_message message) { UNREFERENCED_PARAMETER(member); CallAdvanceLoopModeHandler(busObject, message); });
    if (result != ER_OK)
    {
        StopInternal(result);
        return;
    }

    result = AddMethodHandler(
        interfaceDescription, 
        "GetCurrentItemUrl", 
        [](alljoyn_busobject busObject, const alljoyn_interfacedescription_member* member, alljoyn_message message) { UNREFERENCED_PARAMETER(member); CallGetCurrentItemUrlHandler(busObject, message); });
    if (result != ER_OK)
    {
        StopInternal(result);
        return;
    }

    result = AddMethodHandler(
        interfaceDescription, 
        "PlayItem", 
        [](alljoyn_busobject busObject, const alljoyn_interfacedescription_member* member, alljoyn_message message) { UNREFERENCED_PARAMETER(member); CallPlayItemHandler(busObject, message); });
    if (result != ER_OK)
    {
        StopInternal(result);
        return;
    }

    result = AddMethodHandler(
        interfaceDescription, 
        "SetExternalSource", 
        [](alljoyn_busobject busObject, const alljoyn_interfacedescription_member* member, alljoyn_message message) { UNREFERENCED_PARAMETER(member); CallSetExternalSourceHandler(busObject, message); });
    if (result != ER_OK)
    {
        StopInternal(result);
        return;
    }

    result = AddMethodHandler(
        interfaceDescription, 
        "ToggleShuffleMode", 
        [](alljoyn_busobject busObject, const alljoyn_interfacedescription_member* member, alljoyn_message message) { UNREFERENCED_PARAMETER(member); CallToggleShuffleModeHandler(busObject, message); });
    if (result != ER_OK)
    {
        StopInternal(result);
        return;
    }

    
    SourceObjects[m_busObject] = m_weak;
    SourceInterfaces[interfaceDescription] = m_weak;
    }

void MCUProducer::Stop()
{
    StopInternal(AllJoynStatus::Ok);
}

void MCUProducer::StopInternal(int32 status)
{
    UnregisterFromBus();
    Stopped(this, ref new AllJoynProducerStoppedEventArgs(status));
}

int32 MCUProducer::RemoveMemberFromSession(_In_ String^ uniqueName)
{
    return alljoyn_busattachment_removesessionmember(
        AllJoynHelpers::GetInternalBusAttachment(m_busAttachment),
        m_sessionId,
        AllJoynHelpers::PlatformToMultibyteString(uniqueName).data());
}

PCSTR net::allplay::MCU::c_MCUIntrospectionXml = "<interface name=\"net.allplay.MCU\">"
"  <method name=\"AdvanceLoopMode\"></method>"
"  <method name=\"GetCurrentItemUrl\">"
"    <arg name=\"url\" type=\"s\" direction=\"out\" />"
"  </method>"
"  <method name=\"PlayItem\">"
"    <arg name=\"url\" type=\"s\" direction=\"in\" />"
"    <arg name=\"title\" type=\"s\" direction=\"in\" />"
"    <arg name=\"artist\" type=\"s\" direction=\"in\" />"
"    <arg name=\"thumbnailUrl\" type=\"s\" direction=\"in\" />"
"    <arg name=\"duration\" type=\"x\" direction=\"in\" />"
"    <arg name=\"album\" type=\"s\" direction=\"in\" />"
"    <arg name=\"genre\" type=\"s\" direction=\"in\" />"
"  </method>"
"  <method name=\"SetExternalSource\">"
"    <arg name=\"name\" type=\"s\" direction=\"in\" />"
"    <arg name=\"interruptible\" type=\"b\" direction=\"in\" />"
"    <arg name=\"volumeCtrlEnabled\" type=\"b\" direction=\"in\" />"
"  </method>"
"  <method name=\"ToggleShuffleMode\"></method>"
"  <property name=\"Version\" type=\"q\" access=\"read\" />"
"</interface>"
;
