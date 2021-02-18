//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/action_source/UIActionsActions.h $
//  
//  Owner: Gregor Kaplan
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
#ifndef __UIActionsAATActions__
	#define __UIActionsAATActions__
	
#include "CAATAction.h"
//for AATActionHexID
#include "BaseUIActions.h"
#include "IAATActionList.h"
#include "AATXMLTagDefs.h"

class IWindow;
class IControlView;

// AppAATActions IDs, in hexadecimal - range 000A0000-000AFFFF" - OLD_RANGE
// AppAATActions IDs, in hexadecimal - range 00000A00-00000AFF"
#define kKeyPressAATActionID 					"00000A00"
/*
			DEAD IDs

#define kDialogDDListAATActionID 			"000A0001"
#define kDialogButtonAATActionID 			"000A0002"
#define kDialogRadioButtonAATActionID 	"000A0003"
#define kDialogEditBoxAATActionID 		"000A0004"
#define kDialogNudgeAATActionID 			"000A0005"
#define kDialogCheckBoxAATActionID		"000A0006"
#define kDialogListBoxAATActionID			"000A0007"
#define kDialogPanelAATActionID			"000A0008"
#define kDialogMenuAATActionID			"000A0009"
#define kDialogColorDDListAATActionID 	"000A000A"
#define kDialogStrokeDDListAATActionID 	"000A000B"*/

#define kMenuAATActionID 					"00000A0C"
#define kClickAATActionID					"00000A0D"
#define kClickAndDragAATActionID			"00000A0E"
/*
			DEAD IDs
			
#define kDialogComboBoxAATActionID		"000A000F"
#define kDialogTreeViewAATActionID		"000A0010"
#define kDialogSliderAATActionID			"000A0011"
#define kDialogIconAATActionID			"000A0012"*/
#define kFunctionKeyPressAATActionID 			"00000A13"
#define kNumPadKeyPressAATActionID				"00000A14"
#define kTypeTextAATActionID					"00000A15"
#define kLoadDefaultWorkspaceAATActionID		"00000AF0"
#define kSelectFileAATActionID					"00000AF1"
#define kScarfActionAATActionID					"00000AF2"
#define kScarfScriptAATActionID					"00000AF3"
#define kGetKBSCAATActionID						"00000AF4"




// --------------------- KeyPressAATAction -------------------------
class KeyPressAATAction : public BaseUIAction
{
	public:
		KeyPressAATAction(void);
		virtual ~KeyPressAATAction(void) {}
		
		
		virtual AATActionHexID GetAATActionID(void) { return kKeyPressAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new KeyPressAATAction; }
		
		virtual PMString	GetUIString(void);
		
        virtual ErrorCode ExecuteFromMainThread();
	protected:
		qaChar		fPressChar;
};

// --------------------- FunctionKeyPressAATAction -------------------------
class FunctionKeyPressAATAction : public BaseUIAction
{
	public:
		FunctionKeyPressAATAction(void);
		virtual ~FunctionKeyPressAATAction(void) {}
		
		

		
		virtual AATActionHexID GetAATActionID(void) { return kFunctionKeyPressAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new FunctionKeyPressAATAction; }
		
		virtual PMString	GetUIString(void);
		
		virtual int32 		MapFunctionKey(const PMString &str);

        virtual ErrorCode ExecuteFromMainThread();

	protected:
		qaString		fPressChar;
};

// --------------------- NumPadKeyPressAATAction -------------------------
class NumPadKeyPressAATAction : public BaseUIAction
{
	public:
		NumPadKeyPressAATAction(void);
		virtual ~NumPadKeyPressAATAction(void) {}
		
		

		
		virtual AATActionHexID GetAATActionID(void) { return kNumPadKeyPressAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new NumPadKeyPressAATAction; }
		
		virtual PMString	GetUIString(void);
		
		virtual int32 		MapNumPadKey(const PMString &str);
		
        virtual ErrorCode ExecuteFromMainThread();

	protected:
		qaString		fPressChar;
};
class MenuAATAction : public BaseUIAction
{
	public:
		MenuAATAction(void);
		virtual ~MenuAATAction(void) {}
		
        virtual ErrorCode Execute();
		
		virtual AATActionHexID GetAATActionID(void) { return kMenuAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new MenuAATAction; }
		
		virtual PMString	GetUIString(void);
		
		virtual void	InitForEdit(void);
		
	protected:
		qaString	fCommand;
		qaReal		fYieldTime;
};

class LoadDefaultWorkspaceAATAction : public BaseUIAction
{
	public:
		LoadDefaultWorkspaceAATAction(void);
		virtual ~LoadDefaultWorkspaceAATAction(void) {}
		

		
		virtual AATActionHexID GetAATActionID(void) { return kLoadDefaultWorkspaceAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new LoadDefaultWorkspaceAATAction; }
		
		virtual PMString	GetUIString(void);

        virtual ErrorCode ExecuteFromMainThread();

	protected:
		virtual void	ForceWorkspaceUpdate(void);
		
		qaString	fCommand;
		qaReal		fYieldTime;
		qaBool16	fSuppress;
};
class ClickAATAction : public BaseUIAction
{
	public:
		ClickAATAction(void);
		virtual ~ClickAATAction(void) {}
		
		virtual PMString GetUIString(void);
		

		
		virtual AATActionHexID GetAATActionID(void) { return kClickAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new ClickAATAction; }
		
        virtual ErrorCode Execute();
	protected:
		qaString	fClickCount;
		qaPoint 	fLocation;
		qaUIDRef	fPage;
		qaReal		fYieldTime;
		qaString	fUpDown;
};

class ClickAndDragAATAction : public BaseUIAction
{
	public:
		ClickAndDragAATAction(void);
		virtual ~ClickAndDragAATAction(void) {}
		
		virtual PMString GetUIString(void);
		

		
		virtual AATActionHexID GetAATActionID(void) { return kClickAndDragAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new ClickAndDragAATAction; }
		
		virtual void	GetConvertedTags(K2Vector<PMString> &tags);
		virtual bool16	ConvertParam(VAATData *oldParam, int32 version);
		virtual bool16	ConvertParam(const PMString &readStr, const PMString &tag, int32 version, VAATData **dataHndl);
		
        virtual ErrorCode Execute();
	protected:
		qaPoint 	fStart;
		qaPoint 	fEnd;
		qaUIDRef	fPage;
		qaInt32		fSteps;
		qaReal		fYieldTime;
		qaString	fClickCount;
};





// --------------------- TypeTextAATAction -------------------------
class TypeTextAATAction : public CAATAction
{
	public:
		TypeTextAATAction(void);
		virtual ~TypeTextAATAction(void) {}
		
		
		virtual ErrorCode Execute(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kTypeTextAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new TypeTextAATAction; }
		
	protected:
		qaQAFile	fFile;
		qaString	fTextToType;
};


// --------------------- SelectFileAATAction -------------------------
class SelectFileAATAction : public CAATAction
{
	public:
		SelectFileAATAction(void);
		virtual ~SelectFileAATAction(void) {}
		
		
		virtual ErrorCode Execute(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kSelectFileAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new SelectFileAATAction; }
		
		virtual void	InitForEdit(void);
		
	protected:
		qaQAFile	fFile;
		qaString	fCommand;
		qaReal	fYieldTime;
		qaChar	fPressChar;
};

// --------------------- ScarfActionAATAction -------------------------
class ScarfActionAATAction : public CAATAction
{
	public:
		ScarfActionAATAction(void);
		virtual ~ScarfActionAATAction(void) {}
		
		
		virtual ErrorCode Execute(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kScarfActionAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new ScarfActionAATAction; }
		
	protected:
		qaString	fActionName;
		qaString	fType;
		qaString	fPlatform;
		qaString	fOS;
		qaString	fAppearance;
		qaString	fFocused;
		qaString	fDescription;
		qaString	fApplication;
		qaString	fLocale;
		qaString	fDate;
		qaString	fTester;
		qaInt32		fID;
		qaPoint	fOutPoint;
};

// --------------------- ScarfScriptAATAction -------------------------
class ScarfScriptAATAction : public CAATAction
{
	public:
		ScarfScriptAATAction(void);
		virtual ~ScarfScriptAATAction(void) {}
		
		
		virtual ErrorCode Execute(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kScarfScriptAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new ScarfScriptAATAction; }
		
	protected:
		qaScarfData	fScarfScript;
		qaReal		fYieldTime;
		
};


// --------------------- GetKBSCAATAction -------------------------
class GetKBSCAATAction : public CAATAction
{
	public:
		GetKBSCAATAction(void);
		virtual ~GetKBSCAATAction(void) {}

		virtual ErrorCode Execute(void);

		virtual AATActionHexID GetAATActionID(void) { return kGetKBSCAATActionID; }

		static VAATAction* CreateAATAction(void) { return new GetKBSCAATAction; }

		virtual void CollectReadWriteParams(VirtualDataList* fillList);

	protected:
		qaString		fExpected;
		qaString		fPostingVal;
		qaString		fCommand;
		qaString		fModifiers;
		qaString		fKeyVal;

};


#endif //__UIActionsAATActions__





