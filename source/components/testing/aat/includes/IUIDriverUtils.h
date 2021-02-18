//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/IUIDriverUtils.h $
//  
//  Owner: Kristina Roberts
//  
//  $Author: pmbuilder $
//  
//  $DateTime: 2020/11/06 13:08:29 $
//  
//  $Revision: #2 $
//  
//  $Change: 1088580 $
//  
//  ADOBE CONFIDENTIAL
//  
//  Copyright 1997-2010 Adobe Systems Incorporated. All rights reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and may be covered by U.S. and Foreign Patents,
//  patents in process, and are protected by trade secret or copyright law.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================

#pragma once
#ifndef __IUIDriverUtils__
#define __IUIDriverUtils__
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________

#include "AATArchUIID.h"
#include "IPMUnknown.h"

#include "AATXMLTagDefs.h"
#include "keyboarddefs.h"
#include "ProductTypeDefs.h"

class IWindow;

//Modifier Defs
typedef enum {
	kNoKey = 0x00,
	kCmdControlKey = 0x01, 
	kShiftKey = 0x02, 
	kOptionAltKey = 0x04, 
	kMacCtrlKey = 0x08} KeyboardModifiers;
	
//NOTE:  0xFF == -1, which is No Key
#define kAATNoKey	0xFF

typedef enum {
	kAATDeleteKeyDef			= 0xFE,
	kAATTabKeyDef				= 0xFD,			
	kAATReturnKeyDef			= 0xFC, //Macintosh "return" or Windows "Enter" (on main keyboard)
	kAATEnterKeyDef			= 0xFB, //Macintosh "enter" or Windows "Enter" (on numeric keypad)
	kAATEscapeKeyDef			= 0xFA,			
	kAATHelpKeyDef				= 0xF9,			 

	// Page Keys
	kAATPageUpKeyDef			= 0xF8,
	kAATPageDownKeyDef			= 0xF7,
	kAATHomeKeyDef				= 0xF6,
	kAATEndKeyDef				= 0xF5,

	// Arrow Keys
	kAATUpArrowKeyDef			= 0xF4,
	kAATDownArrowKeyDef		= 0xF3,
	kAATRightArrowKeyDef		= 0xF2,
	kAATLeftArrowKeyDef		= 0xF1,
	kAATBackspaceKeyDef		= 0xF0
} NoPrintKeyDefs;

#define kcHome			0x73
#define kcEnter			0x4C
#define kcEnd			0x77
#define kcHelp			0x72
#define kcDelete		0x33
#define kcPageUp		0x74
#define kcPageDown		0x79
#define kcReturn		0x24
#define kcEsc			0x35
#define kcClear			0x47
#define kcLeftArrow		0x7B
#define kcRightArrow	0x7C
#define kcUpArrow		0x7E
#define kcDownArrow		0x7D
#define kcFwdDelete		0x75
#define kcHyphen		0x1b
#define kcTab			0x30


#ifdef WINDOWS
typedef struct
{
	ProdInt16	loword;
	ProdInt16	hiword;
} WinMsg;

typedef union 
{
	int32	lParam;
	WinMsg	brokenOutlParam;
} WinMsgUnion;
#endif

typedef enum
{
	kUp		= 0x01,
	kDown	= 0x02,
	kUpDown	= kUp | kDown
}eUpDown;

#ifdef MACINTOSH
class MUIDriverUtils;
#define PlatformDriverUtils MUIDriverUtils
#else
class WUIDriverUtils;
#define PlatformDriverUtils WUIDriverUtils
#endif

class IWindow;
class AATScrollEventObserver;

class MouseEventInfo
{
	public:
		MouseEventInfo(void) :
			fDriver(nil),
			fObserver(nil),
			time(.01),
			steps(10),
			numClicks(1),
			upDown(kUpDown),
			startPt(-1,-1),
			endPt(-1,-1),
			fWinFrame(-1,-1,-1,-1),
			mods(kNoKey),
			done(kFalse),
			err(kSuccess) {}
	
		PlatformDriverUtils	*fDriver;
		AATScrollEventObserver *fObserver;
		PMRect		fWinFrame;
		double	time;
		int32	steps;
		int32	numClicks;
		eUpDown	upDown;
		ProdPoint	startPt; //In global coors
		ProdPoint	endPt; //In page/win coors - in case it needs to be converted
		ProdUInt32	mods;
		ProdBool	done;
		ErrorCode	err;
};

class KeyEventInfo
{
	public:
		KeyEventInfo(void) :
			fDriver(nil),
			time(.01),
			virtKey(-1),
			theChar('\0'),
			mods(kNoKey),
			upDown(kUpDown),
			done(kFalse),
			err(kSuccess) {}
	
		PlatformDriverUtils	*fDriver;
		double		time;
		int32	virtKey;
		ProdUInt32	mods;
		char		theChar;
		eUpDown		upDown;
		ProdBool	done;
		ErrorCode	err;
};
class IControlView;
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class IUIDriverUtils : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IUIDRIVERUTILS };
		
		virtual void	SetEventWatching(ProdBool watch) = 0;
		
		virtual ProdBool SelectDropDownListItem(int32 index, IControlView *cntrl, IWindow *win, ProdInt16 keyMods = 0) = 0;
		
		virtual ProdBool MouseButton(ProdPoint localPoint,  
					UIDRef winRef, 
					PMReal	time,
					const PMString &modStr = PMString(""), 
					const PMString &times = PMString(kSingleStr), 
					const PMString &upDownStr = PMString(kUpDownStr),
					UIDRef pageRef = kInvalidUIDRef, 
					IControlView *cntrl = nil) = 0;
					
		virtual ProdBool MouseMove(ProdPoint startPt, 
					ProdPoint endPt, 
					UIDRef winRef, 
					PMReal time = .01, 
					int32 steps = 10, 
					const PMString &modStr = PMString(""), 
					const PMString &upDownStr = PMString(kUpDownStr),
					UIDRef pageRef = kInvalidUIDRef,
					const PMString &times = PMString(kSingleStr)) = 0;
		
		//if "suppressYield" is kTrue the call to Yield will not fire, but the thread pressing the key will still 
		//sleep.
		virtual ProdBool	PressKey(char theChar, PMString modString, PMReal yield = .01, eUpDown upDown = kUpDown, bool16 suppressYield = kFalse) = 0;
		virtual ProdBool	PressKey(int32 virtualKey, PMString modString, PMReal yield = .01, eUpDown upDown = kUpDown, bool16 suppressYield = kFalse) = 0;
		virtual void	SetModKeys(uint32 mods, ProdBool down) = 0;
	
		//Map modifier keys to modifier value
		virtual ProdUInt16		MapStringToModifiers(const PMString &str) = 0;
		virtual ProdInt16		MapCharToVirtualKey(char theChar, PMString &modifiers) = 0;
		//virtual void			MapVirtualKey(ProdInt16 virtKey, char &theChar, const PMString &modifiers) = 0;
		
	protected:
};

class CUIDriverUtils : public CPMUnknown<IUIDriverUtils>
{
	public:

		CUIDriverUtils(IPMUnknown * iBoss);
		virtual ~CUIDriverUtils(void) {}
		
		virtual void	SetEventWatching(ProdBool watch);
		
		virtual ProdBool SelectDropDownListItem(int32 index, IControlView *cntrl, IWindow *win, ProdInt16 keyMods = 0);
		
		virtual ProdBool 	MouseButton(ProdPoint localPoint,  
					UIDRef winRef, 
					PMReal	time,
					const PMString &modStr = PMString(""), 
					const PMString &times = PMString(kSingleStr), 
					const PMString &upDownStr = PMString(kUpDownStr),
					UIDRef pageRef = kInvalidUIDRef, 
					IControlView *cntrl = nil);

		virtual ProdBool 	MouseMove(ProdPoint startPt, 
					ProdPoint endPt, 
					UIDRef winRef, 
					PMReal time = .01, 
					int32 steps = 10, 
					const PMString &modStr = PMString(""), 
					const PMString &upDownStr = PMString(kUpDownStr),
					UIDRef pageRef = kInvalidUIDRef,
					const PMString &times = PMString(kSingleStr));
		
		//Map modifier keys to modifier value
		virtual ProdUInt16		MapStringToModifiers(const PMString &str);
		
	protected:
		virtual ProdBool		MouseButton(MouseEventInfo *info) = 0;
		virtual ProdBool		MouseMove(MouseEventInfo *info) = 0;

		virtual int32		MapStringToTimes(const PMString &times);
};
	#ifdef MACINTOSH
	//________________________________________________________________________________________
	//	CLASS DECLARATION
	//________________________________________________________________________________________
	class MUIDriverUtils : public CUIDriverUtils
	{	
		public:
			enum { kDefaultIID = IID_IUIDRIVERUTILS };
			
			MUIDriverUtils(IPMUnknown * iBoss);
			virtual	~MUIDriverUtils(void);
			
			virtual void		SetModKeys(uint32 mods, ProdBool down);
			
			virtual ProdBool	PressKey(char theChar, PMString modString, PMReal yield = .01, eUpDown upDown = kUpDown, bool16 suppressYield = kFalse);
			virtual ProdBool	PressKey(int32 virtualKey, PMString modString, PMReal yield = .01, eUpDown upDown = kUpDown, bool16 suppressYield = kFalse);
			
		//	virtual void			MapVirtualKey(ProdInt16 virtKey, char &theChar, const PMString &modifiers);
			virtual ProdInt16		MapCharToVirtualKey(char theChar, PMString &modifiers);

            virtual ProdBool SelectDropDownListItem(int32 index, IControlView *cntrl, IWindow *win, ProdInt16 keyMods = 0);

		protected:
			virtual ProdBool		MouseButton(MouseEventInfo *info);
			virtual ProdBool		MouseMove(MouseEventInfo *info);
			
			using CUIDriverUtils::MouseButton; // needed to defeat C++ name lookup rules, so that we can find the other function with the same name in the base class.
			using CUIDriverUtils::MouseMove; // needed to defeat C++ name lookup rules, so that we can find the other function with the same name in the base class.

		private:
			static void ClickTask(void *param, OSStatus* result);
			static void ClickDragTask(void *param, OSStatus* result);
			static void KeyPressTask(void *param, OSStatus* result);
            static void SelectDropDownListFromMainThread(int32 index, IControlView *cntrl, IWindow *win, ProdInt16 keyMods, bool16* outError);
	};
#else
	class WUIDriverUtils : public CUIDriverUtils
	{	
		public:
			enum { kDefaultIID = IID_IUIDRIVERUTILS };
			
			WUIDriverUtils(IPMUnknown * iBoss);
			virtual	~WUIDriverUtils(void);

			virtual ProdBool		PressKey(char theChar, PMString modString, PMReal yield = .01, eUpDown upDown = kUpDown, bool16 suppressYield = kFalse);
			virtual ProdBool		PressKey(int32 virtualKey, PMString modString, PMReal yield = .01, eUpDown upDown = kUpDown, bool16 suppressYield = kFalse);
			virtual void			SetModKeys(uint32 mods, ProdBool down);
			
			virtual ProdInt16		MapCharToVirtualKey(char theChar, PMString &modifiers);
			//virtual void			MapVirtualKey(ProdInt16 virtKey, char &theChar, PMString &modifiers);

		protected:
			virtual ProdBool		MouseButton(MouseEventInfo *info);
			virtual ProdBool		MouseMove(MouseEventInfo *info);

			//Returns the number of inputs created
			virtual int32		CreateOSMouseEvent(INPUT *inputs, ProdUInt32 eventKind, ProdPoint where);
			
			virtual INPUT 			MakeKeyEvent(short keyCode, int32 eventType);
			
			virtual ProdBool 		IsExtendedKey(uchar virtualKey);

		private:
			static unsigned __stdcall 	ClickTask(void *param);
			static unsigned __stdcall 	ClickDragTask(void *param);
			static unsigned __stdcall 	KeyPressTask(void *param);
	};
	#endif

#endif // __IUIDriverUtils__
