# Microsoft Developer Studio Project File - Name="sndinfo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=sndinfo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sndinfo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sndinfo.mak" CFG="sndinfo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sndinfo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "sndinfo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sndinfo - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /G6 /W3 /GX /Od /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 winmm.lib version.lib dsound.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "sndinfo - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x419 /d "_DEBUG"
# ADD RSC /l 0x419 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib version.lib dsound.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "sndinfo - Win32 Release"
# Name "sndinfo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "asio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ADDINC\asio\asio.cpp
# End Source File
# Begin Source File

SOURCE=.\ADDINC\asio\asio.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\asio\asiodrivers.cpp
# End Source File
# Begin Source File

SOURCE=.\ADDINC\asio\asiodrivers.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\asio\asiolist.cpp
# End Source File
# Begin Source File

SOURCE=.\ADDINC\asio\asiolist.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\asio\asiosys.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\asio\ginclude.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\asio\iasiodrv.h
# End Source File
# End Group
# Begin Group "File Version"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\fileversion.cpp
# End Source File
# Begin Source File

SOURCE=.\fileversion.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Getdxver.cpp
# End Source File
# Begin Source File

SOURCE=.\Addinc\id.cpp
# End Source File
# Begin Source File

SOURCE=.\sndinfo.cpp
# End Source File
# Begin Source File

SOURCE=.\sndinfo.rc
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ADDINC\3dl2.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\al.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\alc.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\alctypes.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\altypes.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\Dxver.h
# End Source File
# Begin Source File

SOURCE=.\hpci.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\ia3dapi.h
# End Source File
# Begin Source File

SOURCE=.\Addinc\id.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\mmreg.h
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\xram.h
# End Source File
# Begin Source File

SOURCE=.\ADDINC\ZoomFx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\WIEW1.BMP
# End Source File
# End Group
# Begin Source File

SOURCE=.\rdrv.sys
# End Source File
# End Target
# End Project
