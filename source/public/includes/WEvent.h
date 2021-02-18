//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/WEvent.h $
//  
//  Owner: ?
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  Adobe permits you to use, modify, and distribute this file in accordance 
//  with the terms of the Adobe license agreement accompanying it.  If you have received
//  this file from a source other than Adobe, then your use, modification, or 
//  distribution of it requires the prior written permission of Adobe.
//  
//  
//  Windows-specific implementation of IEvents
//  
//  This is the Windows edge implementation of the core IEvents interface.
//  
//========================================================================================

#pragma once
#ifndef __WEvent__
#define __WEvent__

#ifndef __IEVENT__
#include "IEvent.h"
#endif

#include "K2Assert.h"

#if(WINVER < 0x0601)
/** Windows gesture support has been included in the VS2008 7.0 SDK (for Windows 7).
    The following declarations allow the ID Windows gesture support code to compile
	with 6.0 SDK, and run on Windows 7.
*/
#define WM_GESTURE                      0x0119
#define WM_GESTURENOTIFY                0x011A

/*
 * Gesture defines and functions
 */

/*
 * Gesture information handle
 */
DECLARE_HANDLE(HGESTUREINFO);


/*
 * Gesture flags - GESTUREINFO.dwFlags
 */
#define GF_BEGIN                        0x00000001
#define GF_INERTIA                      0x00000002
#define GF_END                          0x00000004

/*
 * Gesture IDs
 */
#define GID_BEGIN                       1
#define GID_END                         2
#define GID_ZOOM                        3
#define GID_PAN                         4
#define GID_ROTATE                      5
#define GID_TWOFINGERTAP                6
#define GID_PRESSANDTAP                 7
#define GID_ROLLOVER                    GID_PRESSANDTAP

/*
 * Gesture information structure
 *   - Pass the HGESTUREINFO received in the WM_GESTURE message lParam into the
 *     GetGestureInfo function to retrieve this information.
 *   - If cbExtraArgs is non-zero, pass the HGESTUREINFO received in the WM_GESTURE
 *     message lParam into the GetGestureExtraArgs function to retrieve extended
 *     argument information.
 */
typedef struct tagGESTUREINFO {
    UINT cbSize;                    // size, in bytes, of this structure (including variable length Args field)
    DWORD dwFlags;                  // see GF_* flags
    DWORD dwID;                     // gesture ID, see GID_* defines
    HWND hwndTarget;                // handle to window targeted by this gesture
    POINTS ptsLocation;             // current location of this gesture
    DWORD dwInstanceID;             // internally used
    DWORD dwSequenceID;             // internally used
    ULONGLONG ullArguments;         // arguments for gestures whose arguments fit in 8 BYTES
    UINT cbExtraArgs;               // size, in bytes, of extra arguments, if any, that accompany this gesture
} GESTUREINFO, *PGESTUREINFO;
typedef GESTUREINFO const * PCGESTUREINFO;


/*
 * Gesture notification structure
 *   - The WM_GESTURENOTIFY message lParam contains a pointer to this structure.
 *   - The WM_GESTURENOTIFY message notifies a window that gesture recognition is
 *     in progress and a gesture will be generated if one is recognized under the
 *     current gesture settings.
 */
typedef struct tagGESTURENOTIFYSTRUCT {
    UINT cbSize;                    // size, in bytes, of this structure
    DWORD dwFlags;                  // unused
    HWND hwndTarget;                // handle to window targeted by the gesture
    POINTS ptsLocation;             // starting location
    DWORD dwInstanceID;             // internally used
} GESTURENOTIFYSTRUCT, *PGESTURENOTIFYSTRUCT;

/*
 * Gesture argument helpers
 *   - Angle should be a double in the range of -2pi to +2pi
 *   - Argument should be an unsigned 16-bit value
 */
#define GID_ROTATE_ANGLE_TO_ARGUMENT(_arg_)     ((USHORT)((((_arg_) + 2.0 * 3.14159265) / (4.0 * 3.14159265)) * 65535.0))
#define GID_ROTATE_ANGLE_FROM_ARGUMENT(_arg_)   ((((double)(_arg_) / 65535.0) * 4.0 * 3.14159265) - 2.0 * 3.14159265)

/*
 * Gesture information retrieval
 *   - HGESTUREINFO is received by a window in the lParam of a WM_GESTURE message.
 */
WINUSERAPI
BOOL
WINAPI
GetGestureInfo(
    __in HGESTUREINFO hGestureInfo,
    __out PGESTUREINFO pGestureInfo);

/*
 * Gesture extra arguments retrieval
 *   - HGESTUREINFO is received by a window in the lParam of a WM_GESTURE message.
 *   - Size, in bytes, of the extra argument data is available in the cbExtraArgs
 *     field of the GESTUREINFO structure retrieved using the GetGestureInfo function.
 */
WINUSERAPI
BOOL
WINAPI
GetGestureExtraArgs(
    __in HGESTUREINFO hGestureInfo,
    __in UINT cbExtraArgs,
    __out_bcount(cbExtraArgs) PBYTE pExtraArgs);

/*
 * Gesture information handle management
 *   - If an application processes the WM_GESTURE message, then once it is done
 *     with the associated HGESTUREINFO, the application is responsible for
 *     closing the handle using this function. Failure to do so may result in
 *     process memory leaks.
 *   - If the message is instead passed to DefWindowProc, or is forwarded using
 *     one of the PostMessage or SendMessage class of API functions, the handle
 *     is transfered with the message and need not be closed by the application.
 */
WINUSERAPI
BOOL
WINAPI
CloseGestureInfoHandle(
    __in HGESTUREINFO hGestureInfo);


/*
 * Gesture configuration structure
 *   - Used in SetGestureConfig and GetGestureConfig
 *   - Note that any setting not included in either GESTURECONFIG.dwWant or
 *     GESTURECONFIG.dwBlock will use the parent window's preferences or
 *     system defaults.
 */
typedef struct tagGESTURECONFIG {
    DWORD dwID;                     // gesture ID
    DWORD dwWant;                   // settings related to gesture ID that are to be turned on
    DWORD dwBlock;                  // settings related to gesture ID that are to be turned off
} GESTURECONFIG, *PGESTURECONFIG;

/*
 * Gesture configuration flags - GESTURECONFIG.dwWant or GESTURECONFIG.dwBlock
 */

/*
 * Common gesture configuration flags - set GESTURECONFIG.dwID to zero
 */
#define GC_ALLGESTURES                              0x00000001

/*
 * Zoom gesture configuration flags - set GESTURECONFIG.dwID to GID_ZOOM
 */
#define GC_ZOOM                                     0x00000001

/*
 * Pan gesture configuration flags - set GESTURECONFIG.dwID to GID_PAN
 */
#define GC_PAN                                      0x00000001
#define GC_PAN_WITH_SINGLE_FINGER_VERTICALLY        0x00000002
#define GC_PAN_WITH_SINGLE_FINGER_HORIZONTALLY      0x00000004
#define GC_PAN_WITH_GUTTER                          0x00000008
#define GC_PAN_WITH_INERTIA                         0x00000010

/*
 * Rotate gesture configuration flags - set GESTURECONFIG.dwID to GID_ROTATE
 */
#define GC_ROTATE                                   0x00000001

/*
 * Two finger tap gesture configuration flags - set GESTURECONFIG.dwID to GID_TWOFINGERTAP
 */
#define GC_TWOFINGERTAP                             0x00000001

/*
 * PressAndTap gesture configuration flags - set GESTURECONFIG.dwID to GID_PRESSANDTAP
 */
#define GC_PRESSANDTAP                              0x00000001
#define GC_ROLLOVER                                 GC_PRESSANDTAP

#define GESTURECONFIGMAXCOUNT           256             // Maximum number of gestures that can be included
                                                        // in a single call to SetGestureConfig / GetGestureConfig

WINUSERAPI
BOOL
WINAPI
SetGestureConfig(
    __in HWND hwnd,                                     // window for which configuration is specified
    __in DWORD dwReserved,                              // reserved, must be 0
    __in UINT cIDs,                                     // count of GESTURECONFIG structures
    __in_ecount(cIDs) PGESTURECONFIG pGestureConfig,    // array of GESTURECONFIG structures, dwIDs will be processed in the
                                                        // order specified and repeated occurances will overwrite previous ones
    __in UINT cbSize);                                  // sizeof(GESTURECONFIG)


#define GCF_INCLUDE_ANCESTORS           0x00000001      // If specified, GetGestureConfig returns consolidated configuration
                                                        // for the specified window and it's parent window chain

WINUSERAPI
BOOL
WINAPI
GetGestureConfig(
    __in HWND hwnd,                                     // window for which configuration is required
    __in DWORD dwReserved,                              // reserved, must be 0
    __in DWORD dwFlags,                                 // see GCF_* flags
    __in PUINT pcIDs,                                   // *pcIDs contains the size, in number of GESTURECONFIG structures,
                                                        // of the buffer pointed to by pGestureConfig
    __inout_ecount(*pcIDs) PGESTURECONFIG pGestureConfig,
                                                        // pointer to buffer to receive the returned array of GESTURECONFIG structures
    __in UINT cbSize);                                  // sizeof(GESTURECONFIG)

#endif /* WINVER < 0x0601 */


struct WinProcParam{
	HWND hwnd;
	UINT msg;
	WPARAM wParam;
	LPARAM lParam;
};

/**	This is the Windows implementation of an Event. The only clients who need to use this class are those who need to create an event to pass around. This is fairly rare.
	Usually you can declare a PlatformEvent on the stack, set the sys event into it, run it through the event converter, and then pass it to the event dispatcher.
	<pre>
		InterfacePtr<const IApplication> app( GetExecutionContextSession()->QueryApplication() );
		InterfacePtr<IEventDispatcher> dispatcher(app, IID_IEVENTDISPATCHER);

		PlatformEvent myEvent;
		myEvent.SetSysEvent(osLevelEvent);

		GetExecutionContextSession()->GetEventConverter()->ConvertIEvent(myEvent);

		dispatcher->DispatchEvent(&myEvent);
	</pre>

	@see PlatformEvent.h
	@see IEvent
	@see IEventConverter
	@see IEventDispatcher
*/
class PUBLIC_DECL WEvent : public IEvent
{
	public:
		WEvent();

		WEvent(WinProcParam *);

		WEvent( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		virtual bool16		LButtonDn() const;

		virtual bool16		OptionAltKeyDown() const;

		virtual bool16		CmdKeyDown() const;

		virtual bool16		ShiftKeyDown() const;

		virtual bool16		ShiftLockKeyDown() const;

		virtual bool16 		MacCtrlDown() const;

		virtual bool16	LeftAltDown() const;

		virtual bool16	RightAltDown() const;

		virtual bool16	LeftControlDown() const;

		virtual bool16	RightControlDown() const;

		virtual SysChar 	GetChar() const;

		virtual void  SetChar( SysChar theChar );


		virtual VirtualKey GetVirtualKey() const;

		virtual	SysEvent  		GetSysEvent();

		virtual void SetSysEvent(SysEvent theEvent);

		virtual bool16		IsRepeatKey() const;

		virtual bool16		IsAltGrChar() const;

		virtual GSysPoint 	GlobalWhere() const;

		virtual PMPoint GetMouseScrollDelta(ScrollUnits units = kLines) const;

		virtual PMReal	GetTime() const;

		virtual SysWindow 			GetSysWindow() const;

		virtual void 		SetSysWindow(const SysWindow targetWindow);


		virtual IEventHandler *GetTarget() const;
		virtual void 		SetTarget(const IEventHandler *target);

		virtual void SetReturnValue(uintptr_t value);
		virtual uintptr_t GetReturnValue() const;

		virtual void SetSystemHandledState(SystemHandledState state);
		virtual SystemHandledState GetSystemHandledState() const;

		virtual EventType GetType() const;
		virtual void SetType(const EventType theType);

		virtual IPMUnknown* QueryTargetWindowInterface(const PMIID&) const;

		virtual int16 GetPartCode() const{ return fPartCode; }
		virtual void SetPartCode(const int16 pCode) {  fPartCode = pCode; }


		const WEvent& 		operator=(const WEvent& e)
							{
								fEvent = *((WEvent&)e).GetSysEvent();
								fTheWindow = e.GetSysWindow();
								fType = e.GetType();
								return *this;
							}


	private:
		MSG					fEvent;
		SysWindow			fTheWindow;
		IEventHandler*		fTarget;
		uintptr_t			fReturnValue;
		SystemHandledState	fSystemHandledState;
		IEvent::EventType	fType;
		int16 				fPartCode;
};

// private message used in handling app resume
#define kDelayResumeEvent (WM_USER+321)

// Private app message to handle main thread tasks
#define kMainThreadTaskQueuedEvent (WM_APP + 1)

#endif // __WEvent__
