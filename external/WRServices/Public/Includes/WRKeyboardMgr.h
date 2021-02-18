//========================================================================================
//
//	File:	WRKeyboardMgr.h
//
//	Author: prubini
//
//	Date:	6/8/01
//
//  Copyright 1988 - 2005 WinSoft SA. All rights reserved.
//  Usage rights licenced to Adobe Inc. 1993 - 2005.
//
//========================================================================================

#ifndef __WRKeyboardMgr__
#define __WRKeyboardMgr__

#include "WRConfig.h"
#include "WRDefines.h"
#include "IWRFontContext.h"
#include "WRClass.h"
#include "WRVector.h"
#include "WRLanguageID.h"
#ifdef WR_WIN_ENV
#pragma warning (disable:4251)
#endif

class WRMutex;
class IWRMultiProcessing;

#ifdef WR_MAC_ENV
#pragma options align=power
#endif

typedef void* KBID;
#define UNKNOWN_KBID  0

class KeyboardData : public WRClass
{
public:
	KeyboardData(KBID idf,short script);
	
	KBID		fIdf; // kchrid on mac, hkl on win
	WRScriptID	fScript;
#ifdef WR_MAC_ENV
	WRScriptID	fBaseScript;
#endif
	WRCodePage	fCodepage;
	WRUInt32 fStamp;
	WRFontDict*	fPrefFace;
	WRLanguageID fPrefLang;
	bool		fSupported;
};

class WRSERVICES_DECL WRKeyboardMgr : public WRClass
{
private:
	WRKeyboardMgr( );
	virtual ~WRKeyboardMgr( );
public:
	static WRKeyboardMgr*	GetWRKeyboardMgr();
	static void				ReleaseWRKeyboardMgr();
	void	Init(IWRMultiProcessing* fMulti);
	void	Term();

//	static bool				gMouseTracking;

	virtual KBID		GetCurrentKeyboard();
	virtual void		SetCurrentKeyboard(KBID idf);
	virtual WRScriptID	GetCurrentKeyboardScript();
	virtual WRCodePage	GetCurrentKeyboardCodepage();
	virtual KBID		GetPrefKeyboardForScript(WRScriptID script);
	virtual void		SetCurrentKeyboardScript(WRScriptID script);
	virtual bool		IsCurrentKeyboardRTL();
	virtual	void		FaceUsed(WRFontDict *face, WRLanguageID languageID);
	virtual void		ResetPrefFaces();
	virtual WRFontDict*	GetCurrentKeyboardPrefFace();
	virtual WRLanguageID	GetCurrentKeyboardPrefLanguage();
//	virtual WRFontDict*	GetCurrentKeyboardDefaultFace(WRFontDict* face);
	virtual WRFontDict*	GetCurrentKeyboardCompatibleFaceByEnum();
	virtual void		SetScriptCompatibleKeyboard(WRFontDict* face = NULL);
	virtual WRUnichar32	TranslateKBInputToUnicode(char c, WRFontDict* font, bool& handled);
	virtual WRLanguageID	CheckLanguage(WRLanguageID languageID,bool recordIt);
	//dm
	virtual	WRFontDict*		CheckFont(WRFontDict* font,bool recordIt);

	virtual bool		IsMonoscriptFont(WRFontDict* face);
	virtual KBID		GetLastKeyboardForFace(WRFontDict* face);
	virtual KBID		GetLastKeyboardForLang(WRLanguageID languageID);
	virtual WRFontDict* GetDefaultPrefsForFace(WRScriptID script);
	
#ifdef WR_WIN_ENV
	virtual WRHKL			GetAndLoadKeyboardLayoutForShortcut();
#endif

	typedef enum	{	kUnknownChange,
						kLanguageChange,
						kFaceChange,
						kKeyStroke,
						kSelChange,
						kKeyboardChange } WRKBDChangeType;

	virtual void		FaceChanged();
	virtual void		LangChanged();
	virtual void		KeyboardChanged();
	virtual void		SelectionChanged();
	virtual void		Synchronized();
	virtual int		GetLastChangeType(); // what was the last action

	virtual KBID	GetLastKeyboardForDir(bool rtl)
	{
		return GetPrefKeyboardForScript(rtl ? fLastRTL : fLastLTR );
	}

private:
	WRMutex*	fLock;
	IWRMultiProcessing* fMulti;
	WRBool		fIsInitialized;
	WRBool		fIsInitializing;	// Recursivity control boolean
	void		Initialize();

	KeyboardData* 	SearchKeyboardData(KBID id);
	KeyboardData*	GetKeyboardData(KBID id);

	WRUInt32 fLastStamp;
	WRScriptID fLastRTL;
	WRScriptID fLastLTR;
	//dm
	WRUInt32 fLastLangChangeDate;
	WRUInt32 fLastFaceChangeDate;
	WRUInt32 fLastKeyStrokeDate;
	WRUInt32 fLastSelChangeDate;
	WRUInt32 fLastKeybChangeDate;
	
	WRVector<KeyboardData> fKeyboards;
} ;


#ifdef WR_MAC_ENV
#pragma options align=reset
#endif

#endif //__WRKeyboard__

