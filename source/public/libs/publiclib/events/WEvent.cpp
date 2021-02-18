//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/publiclib/events/WEvent.cpp $
//  
//  Owner: Robin_Briggs
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
//========================================================================================

#include "VCPublicHeaders.h"

#include "WEvent.h"
#include "IApplication.h"
#include "IWindowList.h"

WEvent :: WEvent() :
	fTheWindow(NULL),
	fTarget(nil),
	fReturnValue(0),
	fSystemHandledState(kShouldCall),
	fType(kInvalid),
	fPartCode(0)
{
	//ASSERT_FAIL("WEvent is obsolete, use DVEvent instead."); Used by IDServer startup...
	fEvent.time = ::GetTickCount();
}


WEvent::WEvent(WinProcParam * param)
{
#if ID_DROVER_ENABLE
	ASSERT_FAIL("WEvent is obsolete, use DVEvent instead.");
#else
	fEvent.hwnd = param->hwnd;
	fEvent.message = param->msg;
	fEvent.wParam = param->wParam;
	fEvent.lParam = param->lParam;
	fEvent.time = ::GetTickCount();
	fType = kPlatformEvent;
	fTheWindow = NULL;
	fTarget = nil;
	fReturnValue = 0;
	fSystemHandledState = kShouldCall;
	fPartCode = 0;
#endif
}


WEvent::WEvent( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#if ID_DROVER_ENABLE
	ASSERT_FAIL("WEvent is obsolete, use DVEvent instead.");
#else
	fEvent.hwnd = hwnd;
	fEvent.message = msg;
	fEvent.wParam = wParam;
	fEvent.lParam = lParam;
	fType = kPlatformEvent;
	fEvent.time = ::GetTickCount();

	fTheWindow = NULL;
	fTarget = nil;
	fReturnValue = 0;
	fSystemHandledState = kShouldCall;
	fPartCode = 0;
#endif
}


bool16  WEvent :: LButtonDn() const
{
	return (fEvent.message == WM_LBUTTONDOWN); //needs work
}


bool16  WEvent :: OptionAltKeyDown() const
{
	// On Windows Eurpean keyboard support the AltGr key which
	// is usually the right Alt key. When this is down Windows makes it
	// seem like both Atl and Ctrl are down. Avoid reporting in that case.
	if(!this->IsAltGrChar() && ::GetKeyState( VK_MENU ) & 0x8000)
		return kTrue;
	else
		return kFalse;
}



bool16  WEvent :: CmdKeyDown() const
{
	// On Windows Eurpean keyboards support the AltGr key which
	// is usually the right Alt key. When this is down Windows makes it
	// seem like both Atl and Ctrl are down. Avoid reporting in that case.
	if(!this->IsAltGrChar() && ::GetKeyState( VK_CONTROL ) & 0x8000)
		return kTrue;
	else
		return kFalse;
}



bool16  WEvent :: ShiftKeyDown() const
{
	if(::GetKeyState( VK_SHIFT ) & 0x8000)
		return kTrue;
	else
		return kFalse;
}



bool16  WEvent :: ShiftLockKeyDown() const
{
	return kFalse; //needs work
}

bool16  WEvent :: LeftAltDown() const
{
	if(::GetKeyState( VK_LMENU ) & 0x8000)
		return kTrue;
	else
		return kFalse;
}

bool16  WEvent :: RightAltDown() const
{
	if(::GetKeyState( VK_RMENU ) & 0x8000)
		return kTrue;
	else
		return kFalse;
}

bool16  WEvent :: LeftControlDown() const
{
	if(::GetKeyState( VK_LCONTROL ) & 0x8000)
		return kTrue;
	else
		return kFalse;
}

bool16  WEvent :: RightControlDown() const
{
	if(::GetKeyState( VK_RCONTROL ) & 0x8000)
		return kTrue;
	else
		return kFalse;
}


bool16  WEvent :: MacCtrlDown() const
{
	return kFalse; //always
}



SysChar  WEvent :: GetChar() const
{
	return fEvent.wParam;
}

VirtualKey  WEvent :: GetVirtualKey() const
{
	SysChar theChar = GetChar();

	// See if the user pressed Enter key or Enter key on num pad.
	if (theChar == VK_RETURN)
	{
		if ((fEvent.lParam & 0x01000000) != 0)
		{
			theChar = 0x0a;//kEnterKey
		}
	}

	return VirtualKey(theChar);
}

/*
SysKeyCode  WEvent :: GetKeyCode() const
{
	return (unsigned short)fEvent.lParam;
}*/

SysEvent  WEvent :: GetSysEvent()
{
	return &fEvent;
}


void  WEvent :: SetSysEvent(SysEvent theEvent)
{
	fEvent = *theEvent;
}


GSysPoint  WEvent :: GlobalWhere() const
{
	GSysPoint where;
	short x = LOWORD(fEvent.lParam);
	short y = HIWORD(fEvent.lParam);

	where.x = x;
	where.y = y;

	if (fEvent.message != WM_MOUSEWHEEL) // point already in screen cords.
	{
		where.x = 0;
		where.y = 0;

		::ClientToScreen( fEvent.hwnd , &where );

		where.x += x;
		where.y += y;
	}
	return where;
}

PMPoint WEvent::GetMouseScrollDelta(ScrollUnits units) const
{
	PMPoint delta(0,0);

	if (units == kLines)
	{
		delta.Y() = GET_WHEEL_DELTA_WPARAM(fEvent.wParam)/ WHEEL_DELTA;

		UINT	ucNumLines;
			SystemParametersInfo(SPI_GETWHEELSCROLLLINES,  0, &ucNumLines, 0);
			if(ucNumLines > 10)
				ucNumLines = 10;
			if(ucNumLines > 0)
			delta.Y() *= ucNumLines;
	}
	// else (units == kPixels), unsupported on Windows, always return 0, 0

	return delta;
}

PMReal	WEvent :: GetTime() const
{
	// fEvent.time is in milliseconds since startup.  We return seconds, so we must convert it
	PMReal time(fEvent.time);
	return time/1000;
}


SysWindow  WEvent :: GetSysWindow() const
{
	return fTheWindow;
}




void  WEvent :: SetSysWindow(const SysWindow targetWindow)
{
	fTheWindow = targetWindow;
}



IEventHandler *WEvent :: GetTarget() const
{
	return fTarget;
}


void WEvent :: SetTarget(const IEventHandler *target)
{
	fTarget = (IEventHandler*) target;
}


void WEvent :: SetReturnValue(uintptr_t value)
{
	fReturnValue = value;
}


uintptr_t WEvent :: GetReturnValue() const
{
	return fReturnValue;
}


void WEvent :: SetSystemHandledState(SystemHandledState state)
{
	fSystemHandledState = state;
}


IEvent::SystemHandledState WEvent :: GetSystemHandledState() const
{
	return fSystemHandledState;
}



IEvent::EventType WEvent :: GetType() const
{
	return fType;
}



void WEvent :: SetType(const EventType theType)
{
	fType = theType;
}


IPMUnknown* WEvent :: QueryTargetWindowInterface(const PMIID& id) const
{
	SysWindow macWindow = GetSysWindow();
	if (macWindow)
	{
		InterfacePtr<IApplication> theApp(GetExecutionContextSession()->QueryApplication());
		InterfacePtr<IWindowList> appWindows(theApp, IID_IWINDOWLIST);
		IPMUnknown* target = appWindows->GetPMUnknown(macWindow);
		if (target)
			return target->QueryInterface(id);
	}

	return nil;
}

void WEvent::SetChar( SysChar theChar )
{
	fEvent.wParam = theChar;
}


static bool16 IsEuropeanKeyboard()
{
	ASSERT(IDThreading::IsMainThreadDomain());
	static bool16 ts_IsEuropeanKeyboard = kFalse;
	static HKL ts_previousKeyboardLayout = 0;

	HKL currentKeyboardLayout = ::GetKeyboardLayout(0);
	if (currentKeyboardLayout != ts_previousKeyboardLayout)
	{
		/*<MSDN>
		For keyboard layouts that use the right-hand ALT key as a shift key
		(for example, the French keyboard layout), the shift state is
		represented by the value 6, because the right-hand ALT key is
		converted internally into CTRL+ALT.
		</MSDN>
		*/
		ts_IsEuropeanKeyboard = kFalse;
		for(TCHAR ch=0x20; ch<=0xff && ch!=0x00; ++ch)
		{
			if(HIBYTE(::VkKeyScanEx(ch,currentKeyboardLayout))==6)
			{
				ts_IsEuropeanKeyboard = kTrue;
				break;
			}
		}

		//fix hebrew keyboard
		if(!ts_IsEuropeanKeyboard && HIBYTE(::VkKeyScanEx(0x05F1,currentKeyboardLayout))==6)
			ts_IsEuropeanKeyboard = kTrue;
		ts_previousKeyboardLayout = currentKeyboardLayout;
	}

	return ts_IsEuropeanKeyboard;
}

bool16 WEvent::IsAltGrChar() const
{
	// ---- The logic for this code comes from Illustrator 8.0
	//		Original Illustrator filename	 : /App/WinEdge/WinWndProcs.cpp
	//		Original Illustrator function name: IsEuropeanKeyEvent
	//		Observations.
	//		A window procedure recieves key scan code and some other info in its lParam
	//		double word parameter.  Right Alt key and Right Ctrl key down event causes
	//		different lParam value comaring Left Alt and Left Ctrl key.
	//
	//		WM_SYSKEYDOWN
	//		L-Alt           0x20380001
	//		R-Alt           0x21380001
	//      Alt-Gr          0x20000001
	//
	//		WM_KEYDOWN
	//		L-Ctrl          0x001d0001
	//		R-Ctrl          0x011d0001
	//		L-Alt + L-Ctrl  0x201d0001
	//		R-Alt + R-Ctrl  0x211d0001
	//		L-Alt + R-Ctrl  0x211d0001
	//		R-Alt + L-Ctrl  0x201d0001
	//
	// It implies:
	//
	// detecting R-Ctrl key event is possible.
	// detecting R-Alt key event is possible, unless Ctrl key is not pressed.

	// This static gets set/reset during keydown/keyup.
	// This method gets called from the IEventConverter implementation on Windows
	// during IEvent::kKeyDown and IEvent::kKeyUp conversion.
	ASSERT(IDThreading::IsMainThreadDomain());
	static bool16 ts_AltGrKeyDown = kFalse;

	// find out if we're using an English or some other keyboard
	if (IsEuropeanKeyboard() == kFalse)
	{
		ts_AltGrKeyDown = kFalse;
		return kFalse;
	}

	LPARAM lParam = fEvent.lParam;
	uint16 scanCode = (lParam >> 16 ) & 0xff;

	if (scanCode >= 0x45 && scanCode <= 0x53)
		return kFalse;

	if (ts_AltGrKeyDown)
	{
		if (!(GetAsyncKeyState(VK_MENU) & 0x8000) || !(GetAsyncKeyState(VK_CONTROL) & 0x8000))
		{
			ts_AltGrKeyDown  = kFalse;
			TRACEFLOW_OBSOLETE("Old:Public", "---->ts_AltGrKeyDown = %d\n", (int32)(ts_AltGrKeyDown != 0));
		}
	}
	else if ((lParam & 0x21000000) == 0x21000000 || (lParam & 0x01ff0000) == 0x011d0000)  // this appears to handle US style keyboards using the ctrl/alt combo to simulate alt-gr
	{
		if ((GetAsyncKeyState(VK_MENU) & 0x8000) && (GetAsyncKeyState(VK_CONTROL) & 0x8000))
		{
			ts_AltGrKeyDown = kTrue;
			TRACEFLOW_OBSOLETE("Old:Public", "---->ts_AltGrKeyDown = %d\n", (int32)(ts_AltGrKeyDown != 0));
		}
	}
	
	// handle for the actual european keyboard alt-gr key (this can be added via the lang opts in the control panel and brought up with
	// the ease access center to use the onscreen keyboard if you dont have a real german/european keyboard available) 
	else if (IsEuropeanKeyboard() && (lParam  == 0x20000001))
	{
		ts_AltGrKeyDown = kTrue;
		TRACEFLOW_OBSOLETE("Old:Public", "---->ts_AltGrKeyDown = %d\n", (int32)(ts_AltGrKeyDown != 0));
	}

	return ts_AltGrKeyDown;
}
bool16 WEvent::IsRepeatKey() const
{
	ASSERT_FAIL("WEvent::IsRepeatKey: WEvent is obsolete.");
	return kFalse;
}

