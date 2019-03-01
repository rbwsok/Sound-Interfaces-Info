#include <windows.h>
#include <commctrl.h>
#include <objbase.h>
#include <cguid.h>
#include <initguid.h>
#include <stdio.h>

#include <ddraw.h>
#include <dinput.h>
#include <dmusici.h>
#include <mmsystem.h>

#include "addinc/ia3dapi.h"
#include "addinc/dxver.h"
//#include "addinc/eax.h"
#include "addinc/altypes.h"
#include "addinc/alctypes.h"
#include "addinc/xram.h"
#include "addinc/zoomfx.h"
#include "addinc/3DL2.h"
#include "addinc/id.h"
#include "addinc/asio/asiosys.h"
#include "addinc/asio/asio.h"
#include "addinc/asio/asiodrivers.h"
#include "addinc/asio/asiolist.h"
#include "fileversion.h"

#include "resource.h"

////////////////////////////////////////////////////////////////////
// EAX Unified
DEFINE_GUID(CLSID_EAXDirectSound, 
    0x4ff53b81, 
    0x1ce0, 
    0x11d3,
    0xaa, 0xb8, 0x0, 0xa0, 0xc9, 0x59, 0x49, 0xd5);

////////////////////////////////////////////////////////////////////
// EAX 1.0
DEFINE_GUID(DSPROPSETID_EAX_ReverbProperties, 
    0x4a4e6fc1,
    0xc341,
    0x11d1,
    0xb7, 0x3a, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

typedef enum 
{
    DSPROPERTY_EAX_ALL,                // all reverb properties
    DSPROPERTY_EAX_ENVIRONMENT,        // standard environment no.
    DSPROPERTY_EAX_VOLUME,             // loudness of the reverb
    DSPROPERTY_EAX_DECAYTIME,          // how long the reverb lasts
    DSPROPERTY_EAX_DAMPING             // the high frequencies decay faster
} DSPROPERTY_EAX_REVERBPROPERTY;


DEFINE_GUID(DSPROPSETID_EAXBUFFER_ReverbProperties, 
    0x4a4e6fc0,
    0xc341,
    0x11d1,
    0xb7, 0x3a, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00);

typedef enum 
{
    DSPROPERTY_EAXBUFFER_ALL,           // all reverb buffer properties
    DSPROPERTY_EAXBUFFER_REVERBMIX      // the wet source amount
} DSPROPERTY_EAXBUFFER_REVERBPROPERTY;


////////////////////////////////////////////////////////////////////
// EAX 2.0
DEFINE_GUID(DSPROPSETID_EAX20_ListenerProperties, 
    0x306a6a8, 
    0xb224, 
    0x11d2, 
    0x99, 0xe5, 0x0, 0x0, 0xe8, 0xd8, 0xc7, 0x22);

typedef enum
{
    DSPROPERTY_EAX2LISTENER_NONE,
    DSPROPERTY_EAX2LISTENER_ALLPARAMETERS,
    DSPROPERTY_EAX2LISTENER_ROOM,
    DSPROPERTY_EAX2LISTENER_ROOMHF,
    DSPROPERTY_EAX2LISTENER_ROOMROLLOFFFACTOR,
    DSPROPERTY_EAX2LISTENER_DECAYTIME,
    DSPROPERTY_EAX2LISTENER_DECAYHFRATIO,
    DSPROPERTY_EAX2LISTENER_REFLECTIONS,
    DSPROPERTY_EAX2LISTENER_REFLECTIONSDELAY,
    DSPROPERTY_EAX2LISTENER_REVERB,
    DSPROPERTY_EAX2LISTENER_REVERBDELAY,
    DSPROPERTY_EAX2LISTENER_ENVIRONMENT,
    DSPROPERTY_EAX2LISTENER_ENVIRONMENTSIZE,
    DSPROPERTY_EAX2LISTENER_ENVIRONMENTDIFFUSION,
    DSPROPERTY_EAX2LISTENER_AIRABSORPTIONHF,
    DSPROPERTY_EAX2LISTENER_FLAGS
} DSPROPERTY_EAX2_LISTENERPROPERTY;

DEFINE_GUID(DSPROPSETID_EAX20_BufferProperties, 
    0x306a6a7, 
    0xb224, 
    0x11d2, 
    0x99, 0xe5, 0x0, 0x0, 0xe8, 0xd8, 0xc7, 0x22);

typedef enum
{
    DSPROPERTY_EAX2BUFFER_NONE,
    DSPROPERTY_EAX2BUFFER_ALLPARAMETERS,
    DSPROPERTY_EAX2BUFFER_DIRECT,
    DSPROPERTY_EAX2BUFFER_DIRECTHF,
    DSPROPERTY_EAX2BUFFER_ROOM,
    DSPROPERTY_EAX2BUFFER_ROOMHF, 
    DSPROPERTY_EAX2BUFFER_ROOMROLLOFFFACTOR,
    DSPROPERTY_EAX2BUFFER_OBSTRUCTION,
    DSPROPERTY_EAX2BUFFER_OBSTRUCTIONLFRATIO,
    DSPROPERTY_EAX2BUFFER_OCCLUSION, 
    DSPROPERTY_EAX2BUFFER_OCCLUSIONLFRATIO,
    DSPROPERTY_EAX2BUFFER_OCCLUSIONROOMRATIO,
    DSPROPERTY_EAX2BUFFER_OUTSIDEVOLUMEHF,
    DSPROPERTY_EAX2BUFFER_AIRABSORPTIONFACTOR,
    DSPROPERTY_EAX2BUFFER_FLAGS
} DSPROPERTY_EAX2_BUFFERPROPERTY;    

////////////////////////////////////////////////////////////////////
// EAX 3.0
DEFINE_GUID(DSPROPSETID_EAX30_ListenerProperties, 
	0xa8fa6882, 
	0xb476, 
	0x11d3, 
	0xbd, 0xb9, 0x00, 0xc0, 0xf0, 0x2d, 0xdf, 0x87);

typedef enum
{
    DSPROPERTY_EAX3LISTENER_NONE,
    DSPROPERTY_EAX3LISTENER_ALLPARAMETERS,
    DSPROPERTY_EAX3LISTENER_ENVIRONMENT,
    DSPROPERTY_EAX3LISTENER_ENVIRONMENTSIZE,
    DSPROPERTY_EAX3LISTENER_ENVIRONMENTDIFFUSION,
    DSPROPERTY_EAX3LISTENER_ROOM,
    DSPROPERTY_EAX3LISTENER_ROOMHF,
    DSPROPERTY_EAX3LISTENER_ROOMLF,
    DSPROPERTY_EAX3LISTENER_DECAYTIME,
    DSPROPERTY_EAX3LISTENER_DECAYHFRATIO,
    DSPROPERTY_EAX3LISTENER_DECAYLFRATIO,
    DSPROPERTY_EAX3LISTENER_REFLECTIONS,
    DSPROPERTY_EAX3LISTENER_REFLECTIONSDELAY,
    DSPROPERTY_EAX3LISTENER_REFLECTIONSPAN,
    DSPROPERTY_EAX3LISTENER_REVERB,
    DSPROPERTY_EAX3LISTENER_REVERBDELAY,
    DSPROPERTY_EAX3LISTENER_REVERBPAN,
    DSPROPERTY_EAX3LISTENER_ECHOTIME,
    DSPROPERTY_EAX3LISTENER_ECHODEPTH,
    DSPROPERTY_EAX3LISTENER_MODULATIONTIME,
    DSPROPERTY_EAX3LISTENER_MODULATIONDEPTH,
    DSPROPERTY_EAX3LISTENER_AIRABSORPTIONHF,
    DSPROPERTY_EAX3LISTENER_HFREFERENCE,
    DSPROPERTY_EAX3LISTENER_LFREFERENCE,
    DSPROPERTY_EAX3LISTENER_ROOMROLLOFFFACTOR,
    DSPROPERTY_EAX3LISTENER_FLAGS
} DSPROPERTY_EAX3_LISTENERPROPERTY;

DEFINE_GUID(DSPROPSETID_EAX30_BufferProperties, 
	0xa8fa6881, 
	0xb476, 
	0x11d3, 
	0xbd, 0xb9, 0x0, 0xc0, 0xf0, 0x2d, 0xdf, 0x87);

typedef enum
{
    DSPROPERTY_EAX3BUFFER_NONE,
    DSPROPERTY_EAX3BUFFER_ALLPARAMETERS,
    DSPROPERTY_EAX3BUFFER_OBSTRUCTIONPARAMETERS,
    DSPROPERTY_EAX3BUFFER_OCCLUSIONPARAMETERS,
    DSPROPERTY_EAX3BUFFER_EXCLUSIONPARAMETERS,
    DSPROPERTY_EAX3BUFFER_DIRECT,
    DSPROPERTY_EAX3BUFFER_DIRECTHF,
    DSPROPERTY_EAX3BUFFER_ROOM,
    DSPROPERTY_EAX3BUFFER_ROOMHF,
    DSPROPERTY_EAX3BUFFER_OBSTRUCTION,
    DSPROPERTY_EAX3BUFFER_OBSTRUCTIONLFRATIO,
    DSPROPERTY_EAX3BUFFER_OCCLUSION, 
    DSPROPERTY_EAX3BUFFER_OCCLUSIONLFRATIO,
    DSPROPERTY_EAX3BUFFER_OCCLUSIONROOMRATIO,
    DSPROPERTY_EAX3BUFFER_OCCLUSIONDIRECTRATIO,
    DSPROPERTY_EAX3BUFFER_EXCLUSION, 
    DSPROPERTY_EAX3BUFFER_EXCLUSIONLFRATIO,
    DSPROPERTY_EAX3BUFFER_OUTSIDEVOLUMEHF, 
    DSPROPERTY_EAX3BUFFER_DOPPLERFACTOR, 
    DSPROPERTY_EAX3BUFFER_ROLLOFFFACTOR, 
    DSPROPERTY_EAX3BUFFER_ROOMROLLOFFFACTOR,
    DSPROPERTY_EAX3BUFFER_AIRABSORPTIONFACTOR,
    DSPROPERTY_EAX3BUFFER_FLAGS
} DSPROPERTY_EAX3_BUFFERPROPERTY;    

////////////////////////////////////////////////////////////////////
// EAX 4.0

DEFINE_GUID(EAXPROPERTYID_EAX40_Context, 
    0x1d4870ad, 
    0xdef, 
    0x43c0, 
    0xa4, 0xc, 0x52, 0x36, 0x32, 0x29, 0x63, 0x42);

typedef enum
{
    EAX4CONTEXT_NONE = 0,
    EAX4CONTEXT_ALLPARAMETERS,
    EAX4CONTEXT_PRIMARYFXSLOTID,
    EAX4CONTEXT_DISTANCEFACTOR,
    EAX4CONTEXT_AIRABSORPTIONHF,
    EAX4CONTEXT_HFREFERENCE,
    EAX4CONTEXT_LASTERROR
} EAX4CONTEXT_PROPERTY;

DEFINE_GUID(EAXPROPERTYID_EAX40_FXSlot0, 
    0xc4d79f1e, 
    0xf1ac, 
    0x436b, 
    0xa8, 0x1d, 0xa7, 0x38, 0xe7, 0x4, 0x54, 0x69);

DEFINE_GUID(EAXPROPERTYID_EAX40_FXSlot1, 
    0x8c00e96, 
    0x74be, 
    0x4491, 
    0x93, 0xaa, 0xe8, 0xad, 0x35, 0xa4, 0x91, 0x17);

DEFINE_GUID(EAXPROPERTYID_EAX40_FXSlot2, 
    0x1d433b88, 
    0xf0f6, 
    0x4637, 
    0x91, 0x9f, 0x60, 0xe7, 0xe0, 0x6b, 0x5e, 0xdd);

DEFINE_GUID(EAXPROPERTYID_EAX40_FXSlot3, 
    0xefff08ea, 
    0xc7d8, 
    0x44ab, 
    0x93, 0xad, 0x6d, 0xbd, 0x5f, 0x91, 0x0, 0x64);

typedef enum
{
    EAX4FXSLOT_PARAMETER = 0,
    EAX4FXSLOT_NONE = 0x10000,
	EAX4FXSLOT_ALLPARAMETERS,
    EAX4FXSLOT_LOADEFFECT,
    EAX4FXSLOT_VOLUME,
	EAX4FXSLOT_LOCK,
	EAX4FXSLOT_FLAGS
} EAX4FXSLOT_PROPERTY;

DEFINE_GUID(EAXPROPERTYID_EAX40_Source, 
    0x1b86b823, 
    0x22df, 
    0x4eae, 
    0x8b, 0x3c, 0x12, 0x78, 0xce, 0x54, 0x42, 0x27);

typedef enum
{
    EAX4SOURCE_NONE,
    EAX4SOURCE_ALLPARAMETERS,
    EAX4SOURCE_OBSTRUCTIONPARAMETERS,
    EAX4SOURCE_OCCLUSIONPARAMETERS,
    EAX4SOURCE_EXCLUSIONPARAMETERS,
    EAX4SOURCE_DIRECT,
    EAX4SOURCE_DIRECTHF,
    EAX4SOURCE_ROOM,
    EAX4SOURCE_ROOMHF,
    EAX4SOURCE_OBSTRUCTION,
    EAX4SOURCE_OBSTRUCTIONLFRATIO,
    EAX4SOURCE_OCCLUSION,
    EAX4SOURCE_OCCLUSIONLFRATIO, 
    EAX4SOURCE_OCCLUSIONROOMRATIO,
    EAX4SOURCE_OCCLUSIONDIRECTRATIO,
    EAX4SOURCE_EXCLUSION, 
    EAX4SOURCE_EXCLUSIONLFRATIO,
    EAX4SOURCE_OUTSIDEVOLUMEHF, 
    EAX4SOURCE_DOPPLERFACTOR, 
    EAX4SOURCE_ROLLOFFFACTOR, 
    EAX4SOURCE_ROOMROLLOFFFACTOR,
    EAX4SOURCE_AIRABSORPTIONFACTOR,
    EAX4SOURCE_FLAGS,
    EAX4SOURCE_SENDPARAMETERS,
    EAX4SOURCE_ALLSENDPARAMETERS,
    EAX4SOURCE_OCCLUSIONSENDPARAMETERS,
    EAX4SOURCE_EXCLUSIONSENDPARAMETERS,
    EAX4SOURCE_ACTIVEFXSLOTID,
} EAX4SOURCE_PROPERTY;

////////////////////////////////////////////////////////////////////
// EAX 5.0

typedef struct _EAX50SESSIONPROPERTIES
{
    unsigned long     ulEAXVersion;
    unsigned long     ulMaxActiveSends;
} EAX50SESSIONPROPERTIES, *LPEAX50SESSIONPROPERTIES;

enum {
	EAX_40 = 5,       // EAX 4.0 
	EAX_50 = 6,       // EAX 5.0 
};

DEFINE_GUID(EAXPROPERTYID_EAX50_Context, 
    0x57e13437, 
	0xb932, 
	0x4ab2, 
	0xb8, 0xbd, 0x52, 0x66, 0xc1, 0xa8, 0x87, 0xee);

typedef enum
{
    EAX5CONTEXT_NONE = 0,
    EAX5CONTEXT_ALLPARAMETERS,
    EAX5CONTEXT_PRIMARYFXSLOTID,
    EAX5CONTEXT_DISTANCEFACTOR,
    EAX5CONTEXT_AIRABSORPTIONHF,
    EAX5CONTEXT_HFREFERENCE,
    EAX5CONTEXT_LASTERROR,
	 EAX5CONTEXT_SPEAKERCONFIG,
	 EAX5CONTEXT_EAXSESSION,
	 EAX5CONTEXT_MACROFXFACTOR
} EAX5CONTEXT_PROPERTY;

DEFINE_GUID(EAXPROPERTYID_EAX50_FXSlot0, 
    0x91f9590f, 
	0xc388, 
	0x407a, 
	0x84, 0xb0, 0x1b, 0xae, 0xe, 0xf7, 0x1a, 0xbc);

DEFINE_GUID(EAXPROPERTYID_EAX50_FXSlot1, 
    0x8f5f7aca, 
	0x9608, 
	0x4965, 
	0x81, 0x37, 0x82, 0x13, 0xc7, 0xb9, 0xd9, 0xde);

DEFINE_GUID(EAXPROPERTYID_EAX50_FXSlot2, 
    0x3c0f5252, 
	0x9834, 
	0x46f0, 
	0xa1, 0xd8, 0x5b, 0x95, 0xc4, 0xa0, 0xa, 0x30);

DEFINE_GUID(EAXPROPERTYID_EAX50_FXSlot3, 
    0xe2eb0eaa, 
	0xe806, 
	0x45e7, 
	0x9f, 0x86, 0x6, 0xc1, 0x57, 0x1a, 0x6f, 0xa3);

typedef enum
{
    EAX5FXSLOT_PARAMETER = 0,
    EAX5FXSLOT_NONE = 0x10000,
	 EAX5FXSLOT_ALLPARAMETERS,
    EAX5FXSLOT_LOADEFFECT,
    EAX5FXSLOT_VOLUME,
	 EAX5FXSLOT_LOCK,
	 EAX5FXSLOT_FLAGS,
	 EAX5FXSLOT_OCCLUSION,
	 EAX5FXSLOT_OCCLUSIONLFRATIO
} EAX5FXSLOT_PROPERTY;

DEFINE_GUID(EAXPROPERTYID_EAX50_Source, 
    0x5edf82f0, 
	0x24a7, 
	0x4f38, 
	0x8e, 0x64, 0x2f, 0x9, 0xca, 0x5, 0xde, 0xe1);

typedef enum
{
    EAX5SOURCE_NONE,
    EAX5SOURCE_ALLPARAMETERS,
    EAX5SOURCE_OBSTRUCTIONPARAMETERS,
    EAX5SOURCE_OCCLUSIONPARAMETERS,
    EAX5SOURCE_EXCLUSIONPARAMETERS,
    EAX5SOURCE_DIRECT,
    EAX5SOURCE_DIRECTHF,
    EAX5SOURCE_ROOM,
    EAX5SOURCE_ROOMHF,
    EAX5SOURCE_OBSTRUCTION,
    EAX5SOURCE_OBSTRUCTIONLFRATIO,
    EAX5SOURCE_OCCLUSION,
    EAX5SOURCE_OCCLUSIONLFRATIO, 
    EAX5SOURCE_OCCLUSIONROOMRATIO,
    EAX5SOURCE_OCCLUSIONDIRECTRATIO,
    EAX5SOURCE_EXCLUSION, 
    EAX5SOURCE_EXCLUSIONLFRATIO,
    EAX5SOURCE_OUTSIDEVOLUMEHF, 
    EAX5SOURCE_DOPPLERFACTOR, 
    EAX5SOURCE_ROLLOFFFACTOR, 
    EAX5SOURCE_ROOMROLLOFFFACTOR,
    EAX5SOURCE_AIRABSORPTIONFACTOR,
    EAX5SOURCE_FLAGS,
    EAX5SOURCE_SENDPARAMETERS,
    EAX5SOURCE_ALLSENDPARAMETERS,
    EAX5SOURCE_OCCLUSIONSENDPARAMETERS,
    EAX5SOURCE_EXCLUSIONSENDPARAMETERS,
    EAX5SOURCE_ACTIVEFXSLOTID,
	 EAX5SOURCE_MACROFXFACTOR,
	 EAX5SOURCE_SPEAKERLEVELS,
	 EAX5SOURCE_ALL2DPARAMETERS,
} EAX5SOURCE_PROPERTY;