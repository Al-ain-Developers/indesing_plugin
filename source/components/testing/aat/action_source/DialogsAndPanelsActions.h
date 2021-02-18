//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/action_source/DialogsAndPanelsActions.h $
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
#ifndef __DialogsAndPanelsAATActions__
	#define __DialogsAndPanelsAATActions__
	
#include "CAATAction.h"
#include "BaseUIActions.h"
//for AATActionHexID
#include "IAATActionList.h"
#include "AATXMLTagDefs.h"
#include "VirtualDataList.h"

class IWindow;
class IControlView;
class IAATActionUIHandler;
class IListBoxController;
class NodeID;
class IPanelControlData;

// DialogsAndPanels IDs, in hexadecimal - range 00250000-0025FFFF" - OLD_RANGE
// DialogsAndPanels IDs, in hexadecimal - range 00002500-000025FF"
#define kDialogDDListAATActionID 				"00002501"
#define kDialogButtonAATActionID 				"00002502"
#define kDialogRadioButtonAATActionID 	"00002503"
#define kDialogEditBoxAATActionID 			"00002504"
#define kDialogNudgeAATActionID 				"00002505"
#define kDialogCheckBoxAATActionID			"00002506"
#define kDialogListBoxAATActionID				"00002507"
#define kDialogPanelAATActionID					"00002508"
#define kDialogMenuAATActionID					"00002509"
#define kDialogColorDDListAATActionID 	"0000250A"	
#define kDialogStrokeDDListAATActionID 	"0000250B"
#define kDialogComboBoxAATActionID			"0000250C"
#define kDialogTreeViewAATActionID			"0000250D"
#define kDialogSliderAATActionID				"0000250E"
#define kDialogIconAATActionID					"0000250F"
#define kDialogOwnerDDAATActionID				"00002510"
//#define kDialogTextListBoxAATActionID		"00002511"
#define kDialogClickableTextAATActionID	"00002512"
#define kDialogPathStrokeDDAATActionID	"00002513"
//#define kDialogRenderListBoxAATActionID	"00002514"
#define kDialogUIColorDDListAATActionID	"00002515"
#define kDialogPointProxyAATActionID		"00002516"
#define kDialogGlyphGridPanelAATActionID 	"00002517"
#define kDialogSpreadWidgetAATActionID	"00002518"
#define kDialogStrokeFillAATActionID		"00002519"
#define kDialogPluginMgrAATActionID			"0000251A"
//#define kDialogFFTabListBoxAATActionID	"0000251B"
#define kDialogLibraryGridAATActionID		"0000251C"
#define kDialogGradientSliderAATActionID		"0000251D"
#define kDialogQuickApplyAATActionID		"0000251E"
#define kDialogStaticTextHolderAATActionID		"0000251F"
#define kDialogGalleyProgressAATActionID		"00002520"
//#define kDialogSwatchListBoxAATActionID				"00002521"
#define kDialogCornerTypeDDAATActionID			"00002522"


class CommonDDListAATAction : public BaseDialogAATAction
{
	public:
		CommonDDListAATAction(const PMString &str, 
			PMString subject = kNoneTokenValue,
			PMString product = kNoneTokenValue);
		virtual ~CommonDDListAATAction(void) {}
		
		virtual void 	Init(void);
		
		virtual ErrorCode Execute(void);
		
	protected:
		virtual bool16	SetSelection(void);
};

// --------------------- DialogDDListAATAction -------------------------
class DialogDDListAATAction : public CommonDDListAATAction
{
	public:
		DialogDDListAATAction(void);
		virtual ~DialogDDListAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogDDListAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogDDListAATAction; }
		
	protected:
};

// --------------------- DialogOwnerDDAATAction -------------------------
class DialogOwnerDDAATAction : public CommonDDListAATAction
{
	public:
		DialogOwnerDDAATAction(void);
		virtual ~DialogOwnerDDAATAction(void) {}
		
		virtual PMString GetInstanceName(void);

		virtual AATActionHexID GetAATActionID(void) { return kDialogOwnerDDAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogOwnerDDAATAction; }
		
	protected:
};

// --------------------- DialogPathStrokeDDAATAction -------------------------
class DialogPathStrokeDDAATAction : public CommonDDListAATAction
{
	public:
		DialogPathStrokeDDAATAction(void);
		virtual ~DialogPathStrokeDDAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogPathStrokeDDAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogPathStrokeDDAATAction; }
		
	protected:
};


// --------------------- DialogCornerTypeDDAATAction -------------------------
class DialogCornerTypeDDAATAction : public CommonDDListAATAction
{
	public:
		DialogCornerTypeDDAATAction(void);
		virtual ~DialogCornerTypeDDAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogCornerTypeDDAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogCornerTypeDDAATAction; }
		
	protected:
};

// --------------------- DialogColorDDListAATAction -------------------------
class DialogColorDDListAATAction : public CommonDDListAATAction
{
	public:
		DialogColorDDListAATAction(void);
		virtual ~DialogColorDDListAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogColorDDListAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogColorDDListAATAction; }
		
	protected:
		virtual bool16	SetSelection(void);
};

// --------------------- DialogUIColorDDListAATAction -------------------------
class DialogUIColorDDListAATAction : public CommonDDListAATAction
{
	public:
		DialogUIColorDDListAATAction(void);
		virtual ~DialogUIColorDDListAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogUIColorDDListAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogUIColorDDListAATAction; }
		
	protected:
		virtual bool16	SetSelection(void);
};



// --------------------- KeyPressAATAction -------------------------
class DialogStrokeDDListAATAction : public CommonDDListAATAction
{
	public:
		DialogStrokeDDListAATAction(void);
		virtual ~DialogStrokeDDListAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogStrokeDDListAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogStrokeDDListAATAction; }
		
	protected:
		virtual bool16	SetSelection(void);
};


// --------------------- DialogButtonAATAction -------------------------
class DialogButtonAATAction : public BaseDialogAATAction
{
	public:
		DialogButtonAATAction(void);
		virtual ~DialogButtonAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode Execute(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogButtonAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new DialogButtonAATAction; }
		
	protected:
		qaString	fActionType;
};

// --------------------- DialogIconAATAction -------------------------
class DialogIconAATAction : public BaseDialogAATAction
{
	public:
		DialogIconAATAction(void);
		virtual ~DialogIconAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode Execute(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogIconAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogIconAATAction; }
		
		virtual void	GetConvertedTags(K2Vector<PMString> &tags);
		virtual bool16	ConvertParam(VAATData *oldParam, int32 version);
		virtual bool16	ConvertParam(const PMString &readStr, const PMString &tag, int32 version, VAATData **dataHndl);
		
		virtual void 	Init(void);
	protected:
};

// --------------------- DialogPanelAATAction -------------------------
class DialogPanelAATAction : public BaseDialogAATAction
{
	public:
		DialogPanelAATAction(void);
		virtual ~DialogPanelAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode ExecuteFromMainThread(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogPanelAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogPanelAATAction; }
		

	protected:
};

class DialogListBoxAATAction : public BaseDialogAATAction
{
	public:
		DialogListBoxAATAction(void);
		virtual ~DialogListBoxAATAction() {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode 	Execute(void);
		virtual void		Init(void);
		virtual PMString	GetUIString(void);
		virtual void		CollectReadWriteParams(VirtualDataList* fillList);
		
		virtual void		GetConvertedTags(K2Vector<PMString> &tags);
		virtual bool16		ConvertParam(VAATData *oldParam, int32 version);
		virtual bool16		ConvertParam(const PMString &readStr, const PMString &tag, int32 version, VAATData **dataHndl);
	
		virtual AATActionHexID GetAATActionID(void) { return kDialogListBoxAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogListBoxAATAction; }
		
	protected:
		ErrorCode	ClickInList(IControlView *itemList, int32 itemIndex);
		ErrorCode	DragInList(IControlView *itemList, int32 itemIndex, int32 dragToIndex);
		
		qaString 	fTimes;
		qaString	fToItemStr;
		qaInt32		fRowIndex;
		
	private:
		PMString fConvertedActionType;
};


// --------------------- DialogTreeViewAATAction -------------------------
class DialogTreeViewAATAction : public BaseDialogAATAction
{
	public:
		DialogTreeViewAATAction(void);
		virtual ~DialogTreeViewAATAction(void);
		
		virtual bool16	IsContainerAATAction(void) { return kTrue; }
		virtual void	AddContainedItem(ISequenceItem *test, int32 index = -1);
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode ExecuteFromMainThread(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogTreeViewAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogTreeViewAATAction; }
		
		virtual void 	CollectReadWriteParams(VirtualDataList* fillList);
		virtual void	Init(void);
		virtual void	ClearAllValueTrees(void);
		
		virtual VirtualDataList*	AccessValueTree(void) { return &fValueTree; }
		
	protected:
		virtual void			GetActionList(VirtualDataList *srcList, K2Vector<K2Pair<IAATActionList*, NodeID*> > &dstList);
		virtual IAATActionList*	GetAATActionFromTreeEntry(DialogTreeViewAATAction *test, int32 &childIndex);
		virtual void			GetNodeFromEntry(NodeID &finalNode, PMString itemCount);
		virtual PMString		GetSelectedItemString(void);
		
		virtual IControlView*	GetViewFromPanelData(IPanelControlData *pnlData, int32 &col);
		virtual void	AddRows(VAATAction *container, const PMString &baseName);
		virtual void	AddColumn(IAATActionList *testList);
		
		virtual IAATActionList*		MapSelectionToAction(VirtualDataList *srcList, VirtualDataList **dataHndl);
		virtual void				SetDataFromUID(uint32 uid, VirtualDataList *srcData);
		virtual VirtualDataList*	GetDataFromUID(uint32 uid);
		
		
		virtual void			RationalizeValueTreeEntries(VirtualDataList	*subTreeEntries);
		
		VirtualDataList	fValueTree;
		int32 			fAddedEntries;
		int32			fSetUID;
		
	private:
		VirtualDataList	*fXFormSetData;
		
};
// --------------------- DialogComboBoxAATAction -------------------------
class DialogComboBoxAATAction : public BaseDialogAATAction
{
	public:
		DialogComboBoxAATAction(void);
		virtual ~DialogComboBoxAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode Execute(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogComboBoxAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new DialogComboBoxAATAction; }
		
	protected:
		qaBool16	fClear;
		qaBool16	fUseDDEntryOnly;
		qaBool16	fCommitJChars;
};


// --------------------- DialogSliderAATAction -------------------------
class DialogSliderAATAction : public BaseDialogAATAction
{
	public:
		DialogSliderAATAction(void);
		virtual ~DialogSliderAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode ExecuteFromMainThread(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogSliderAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new DialogSliderAATAction; }
		
	protected:
		qaReal		fTolerance;
};
// --------------------- DialogRadioButtonAATAction -------------------------
class DialogRadioButtonAATAction : public BaseDialogAATAction
{
	public:
		DialogRadioButtonAATAction(void);
		virtual ~DialogRadioButtonAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode Execute(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogRadioButtonAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogRadioButtonAATAction; }
		
	protected:
		virtual ErrorCode		PreverifyWidget(IControlView *cntrl, IWindow *dlg);
		//This is required due to Eve conversion and change in hierachy of radio widgets.
		virtual	IControlView * findRadiobuttons(IControlView *cntrlview);
};

// --------------------- KeyPressAATAction -------------------------
class DialogEditBoxAATAction : public BaseDialogAATAction
{
	public:
		DialogEditBoxAATAction(void);
		virtual ~DialogEditBoxAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
			
		virtual AATActionHexID GetAATActionID(void) { return kDialogEditBoxAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new DialogEditBoxAATAction; }
		
        virtual ErrorCode Execute();
    protected:
		qaBool16	fClear;
		qaBool16	fCommitJChars;
};

// --------------------- KeyPressAATAction -------------------------
class DialogNudgeAATAction : public BaseDialogAATAction
{
	public:
		DialogNudgeAATAction(void);
		virtual ~DialogNudgeAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode ExecuteFromMainThread(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogNudgeAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new DialogNudgeAATAction; }
		
	protected:
		qaString	fNudgeDir;
		qaInt32		fTimes;
};

// --------------------- KeyPressAATAction -------------------------
class DialogCheckBoxAATAction : public BaseDialogAATAction
{
	public:
		DialogCheckBoxAATAction(void);
		virtual ~DialogCheckBoxAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		virtual PMString GetUIString(void);
		
		virtual ErrorCode Execute(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogCheckBoxAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogCheckBoxAATAction; }
		
		virtual void	GetConvertedTags(K2Vector<PMString> &tags);
		virtual bool16	ConvertParam(VAATData *oldParam, int32 version);
		virtual bool16	ConvertParam(const PMString &readStr, const PMString &tag, int32 version, VAATData **dataHndl = nil);
		
	protected:
};



// --------------------- DialogIconAATAction -------------------------
class DialogClickableTextAATAction : public BaseDialogAATAction
{
	public:
		DialogClickableTextAATAction(void);
		virtual ~DialogClickableTextAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode ExecuteFromMainThread(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogClickableTextAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogClickableTextAATAction; }
		
		virtual void 	Init(void);
		
};


// --------------------- KeyPressAATAction -------------------------
class DialogQuickApplyAATAction : public BaseDialogAATAction
{
	public:
		DialogQuickApplyAATAction(void);
		virtual ~DialogQuickApplyAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode ExecuteFromMainThread(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogQuickApplyAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new DialogQuickApplyAATAction; }
		virtual int32		GetListLength(IControlView *cntrl);
		
	protected:
		qaString 	fTimes;
};


// --------------------- DialogStaticTextHolderAATAction -------------------------
class DialogStaticTextHolderAATAction : public BaseDialogAATAction
{
	public:
		DialogStaticTextHolderAATAction(void);
		virtual ~DialogStaticTextHolderAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode ExecuteFromMainThread(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogStaticTextHolderAATActionID; }
		
		virtual void	CollectReadWriteParams(VirtualDataList* fillList);
		
		static VAATAction* CreateAATAction(void) { return new DialogStaticTextHolderAATAction; }
		
	protected:
};


// --------------------- DialogGalleyProgressAATAction -------------------------
class DialogGalleyProgressAATAction : public BaseDialogAATAction
{
	public:
		DialogGalleyProgressAATAction(void);
		virtual ~DialogGalleyProgressAATAction(void) {}
		
		virtual PMString GetInstanceName(void);
		
		virtual ErrorCode ExecuteFromMainThread(void);
		
		virtual AATActionHexID GetAATActionID(void) { return kDialogGalleyProgressAATActionID; }
		
		static VAATAction* CreateAATAction(void) { return new DialogGalleyProgressAATAction; }
		
	protected:
};


\

#endif //__DialogsAndPanelsAATActions__





