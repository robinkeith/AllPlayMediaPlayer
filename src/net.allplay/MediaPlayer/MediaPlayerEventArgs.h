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

namespace net { namespace allplay { namespace MediaPlayer {

// Signals
public ref class MediaPlayerEnabledControlsChangedReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }

    property Windows::Foundation::Collections::IMap<Platform::String^,bool>^ EnabledControls
    {
        Windows::Foundation::Collections::IMap<Platform::String^,bool>^ get() { return m_interfaceMemberEnabledControls; }
    internal:
        void set(_In_ Windows::Foundation::Collections::IMap<Platform::String^,bool>^ value) { m_interfaceMemberEnabledControls = value; }
    }

private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

    Windows::Foundation::Collections::IMap<Platform::String^,bool>^ m_interfaceMemberEnabledControls;
};

public ref class MediaPlayerEndOfPlaybackReceivedEventArgs sealed
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

public ref class MediaPlayerInterruptibleChangedReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }

    property bool Interruptible
    {
        bool get() { return m_interfaceMemberInterruptible; }
    internal:
        void set(_In_ bool value) { m_interfaceMemberInterruptible = value; }
    }

private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

    bool m_interfaceMemberInterruptible;
};

public ref class MediaPlayerLoopModeChangedReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }

    property Platform::String^ LoopMode
    {
        Platform::String^ get() { return m_interfaceMemberLoopMode; }
    internal:
        void set(_In_ Platform::String^ value) { m_interfaceMemberLoopMode = value; }
    }

private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

    Platform::String^ m_interfaceMemberLoopMode;
};

public ref class MediaPlayerOnPlaybackErrorReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }

    property int32 Index
    {
        int32 get() { return m_interfaceMemberIndex; }
    internal:
        void set(_In_ int32 value) { m_interfaceMemberIndex = value; }
    }
    property Platform::String^ Error
    {
        Platform::String^ get() { return m_interfaceMemberError; }
    internal:
        void set(_In_ Platform::String^ value) { m_interfaceMemberError = value; }
    }
    property Platform::String^ Description
    {
        Platform::String^ get() { return m_interfaceMemberDescription; }
    internal:
        void set(_In_ Platform::String^ value) { m_interfaceMemberDescription = value; }
    }

private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

    int32 m_interfaceMemberIndex;
    Platform::String^ m_interfaceMemberError;
    Platform::String^ m_interfaceMemberDescription;
};

public ref class MediaPlayerPlaylistChangedReceivedEventArgs sealed
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

public ref class MediaPlayerShuffleModeChangedReceivedEventArgs sealed
{
public:
    property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
    {
        Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
        void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
    }

    property Platform::String^ ShuffleMode
    {
        Platform::String^ get() { return m_interfaceMemberShuffleMode; }
    internal:
        void set(_In_ Platform::String^ value) { m_interfaceMemberShuffleMode = value; }
    }

private:
    Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

    Platform::String^ m_interfaceMemberShuffleMode;
};


public ref class MediaPlayerPlayStateChangedReceivedEventArgs sealed
{
public:
	property Windows::Devices::AllJoyn::AllJoynMessageInfo^ MessageInfo
	{
		Windows::Devices::AllJoyn::AllJoynMessageInfo^ get() { return m_messageInfo; }
		void set(_In_ Windows::Devices::AllJoyn::AllJoynMessageInfo^ value) { m_messageInfo = value; }
	}

	property net::allplay::MediaPlayer::MediaPlayerPlayState^ PlayState
	{
		net::allplay::MediaPlayer::MediaPlayerPlayState^ get() { return m_interfaceMemberPlayState; }
	internal:
		void set(_In_ net::allplay::MediaPlayer::MediaPlayerPlayState^ value) { m_interfaceMemberPlayState = value; }
	}

private:
	Windows::Devices::AllJoyn::AllJoynMessageInfo^ m_messageInfo;

	net::allplay::MediaPlayer::MediaPlayerPlayState^ m_interfaceMemberPlayState;
};



} } } 
