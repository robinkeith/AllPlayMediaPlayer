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
#pragma once

namespace net { namespace allplay { namespace ZoneManager {

// Signals
public ref class ZoneManagerEnabledChangedReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }

    property bool Enabled
    {
        bool get() { return m_interfaceMemberEnabled; }
    internal:
        void set(_In_ bool value) { m_interfaceMemberEnabled = value; }
    }

private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

    bool m_interfaceMemberEnabled;
};

public ref class ZoneManagerOnZoneChangedReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }

    property Platform::String^ ZoneId
    {
        Platform::String^ get() { return m_interfaceMemberZoneId; }
    internal:
        void set(_In_ Platform::String^ value) { m_interfaceMemberZoneId = value; }
    }
    property int32 Timestamp
    {
        int32 get() { return m_interfaceMemberTimestamp; }
    internal:
        void set(_In_ int32 value) { m_interfaceMemberTimestamp = value; }
    }
    property Windows::Foundation::Collections::IMap<Platform::String^,int32>^ Slaves
    {
        Windows::Foundation::Collections::IMap<Platform::String^,int32>^ get() { return m_interfaceMemberSlaves; }
    internal:
        void set(_In_ Windows::Foundation::Collections::IMap<Platform::String^,int32>^ value) { m_interfaceMemberSlaves = value; }
    }

private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

    Platform::String^ m_interfaceMemberZoneId;
    int32 m_interfaceMemberTimestamp;
    Windows::Foundation::Collections::IMap<Platform::String^,int32>^ m_interfaceMemberSlaves;
};

public ref class ZoneManagerPlayerReadyReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }

    property uint64 ResumeLatency
    {
        uint64 get() { return m_interfaceMemberResumeLatency; }
    internal:
        void set(_In_ uint64 value) { m_interfaceMemberResumeLatency = value; }
    }

private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

    uint64 m_interfaceMemberResumeLatency;
};

public ref class ZoneManagerSlaveOutOfDataReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }


private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

};

public ref class ZoneManagerSlaveStateReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }

    property int32 Timestamp
    {
        int32 get() { return m_interfaceMemberTimestamp; }
    internal:
        void set(_In_ int32 value) { m_interfaceMemberTimestamp = value; }
    }
    property Platform::String^ State
    {
        Platform::String^ get() { return m_interfaceMemberState; }
    internal:
        void set(_In_ Platform::String^ value) { m_interfaceMemberState = value; }
    }
    property Platform::String^ Url
    {
        Platform::String^ get() { return m_interfaceMemberUrl; }
    internal:
        void set(_In_ Platform::String^ value) { m_interfaceMemberUrl = value; }
    }
    property uint64 StartTime
    {
        uint64 get() { return m_interfaceMemberStartTime; }
    internal:
        void set(_In_ uint64 value) { m_interfaceMemberStartTime = value; }
    }
    property uint64 CurrentPosition
    {
        uint64 get() { return m_interfaceMemberCurrentPosition; }
    internal:
        void set(_In_ uint64 value) { m_interfaceMemberCurrentPosition = value; }
    }
    property Platform::String^ NextStream
    {
        Platform::String^ get() { return m_interfaceMemberNextStream; }
    internal:
        void set(_In_ Platform::String^ value) { m_interfaceMemberNextStream = value; }
    }

private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

    int32 m_interfaceMemberTimestamp;
    Platform::String^ m_interfaceMemberState;
    Platform::String^ m_interfaceMemberUrl;
    uint64 m_interfaceMemberStartTime;
    uint64 m_interfaceMemberCurrentPosition;
    Platform::String^ m_interfaceMemberNextStream;
};


} } } 
