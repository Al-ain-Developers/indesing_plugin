//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/ui/includes/BaseUIActions.h $
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
#ifndef __BaseUIAATActions__
	#define __BaseUIAATActions__
	
#include "CAATAction.h"
#include "AATXMLTagDefs.h"
#include "UnkeyedDataList.h"

class IWindow;
class IControlView;
class IPanelControlData;
class IAATUIHandler;

class AATLIB_DECL BaseUIAction : public CAATAction
{
	public:
		BaseUIAction(const PMString &str, 
			PMString subject = kNoneTokenValue,
			PMString product = kNoneTokenValue);
		virtual ~BaseUIAction(void) {}
		
		virtual void CollectReadWriteParams(VirtualDataList* fillList);
		
	protected:
		
		qaString 	fModList;
    public:
        virtual ErrorCode Execute(void);
        void MainThreadExecuteCaller(ErrorCode* err);
        
};

class AATLIB_DECL BaseDialogAATAction : public BaseUIAction
{
	public:
		BaseDialogAATAction(const PMString &str, 
			PMString subject = kNoneTokenValue,
			PMString product = kNoneTokenValue);
		virtual ~BaseDialogAATAction(void);
		
		virtual void 	Init(void);
		
		virtual PMString 	GetInstanceName(void) = 0;
		virtual bool16		IsSupportedToken(const PMString &token);
		virtual void		GetSupportedTokens(K2Vector<PMString> &tokens);
		
		virtual void 		CollectReadWriteParams(VirtualDataList* fillList);
		
		virtual PMString		GetUIString(void);
		virtual PMString		GetTypeName(void) { return GetInstanceName(); }
		
		virtual	void					SetHandler(IAATUIHandler *handler);
		virtual	IAATUIHandler*	GetHandler(void) { return fHandler; }
		
		virtual void	GetConvertedTags(K2Vector<PMString> &tags);
		virtual bool16	ConvertParam(VAATData *oldParam, int32 version);
		virtual bool16	ConvertParam(const PMString &readStr, const PMString &tag, int32 version, VAATData **dataHndl);
		
		virtual void			SetView(IControlView *view);
        
        virtual ErrorCode       Execute();
	
	protected:
		virtual IControlView*	LocateWidget(void);
		virtual IPanelControlData*		LocateParent(qaInt32 **parID);
		virtual bool16			LocateWindow(IWindow **winHndl);
		virtual ErrorCode		PreverifyWidget(IControlView *cntrl, IWindow *dlg);
		
		qaInt32		fPanelActionID;
		qaString	fPanelCommand;
		UnkeyedDataList		fParentWidgets;
		qaBool16	fIsDialog;
		qaBool16	fCommit;
		qaInt32		fWidgetID;
		qaString	fWidgetType;
		qaString	fWidgetValue;
		qaString	fWidgetMin;
		qaString	fWidgetMax;
		qaQARect	fWidgetBounds;
		qaBool16	fPreClick;
		qaString	fSetGet;
		qaInt32		fTreeColumn;
		qaString	fTreeRow;
		qaString	fExpected;
		qaString	fCheckEnabled;
		qaString	fCheckVisibility;
		qaReal		fYieldTime;
		qaString	fGetProduct;
		
		qaString	fSrcPlatform;
		qaString	fSrcFeatureSet;
		qaString	fSrcProduct;
		qaString	fSrcWidgetWindowTitle;
		qaString	fSrcDebugRelease;
		
		K2Vector<PMString>	fSupportedTokens;
		
		IAATUIHandler *fHandler;
		IControlView		*fMyView;
		IWindow 			*fDlg;
		VAATAction			*fParentContainer;

    private:
        void MainThreadExecuteCaller(ErrorCode* err);
};





#endif //__BaseUIAction__





