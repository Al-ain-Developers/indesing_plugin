//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IDialogUtils.h $
//  
//  Owner: rkamicar
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

#pragma once
#ifndef __IDialogUtils__
#define __IDialogUtils__

//#include "IPMUnknown.h"
#include "OMTypes.h"
#include "BaseType.h"
#include "ICompositionStyle.h"
#include "StringUtils.h"

class ModelRange;
class IPanelControlData;
class IStringListControlData;
class IStyleGroupListControlData;
class IDialogController;
class IDialogUtils;
class IDFile;


// UIDFillerFunc's
/** a pointer to a method that fills the control with the data from the given UID @see IDialogUtils::InitDropDownFromUID */
typedef int32 (*UIDFillerFunc)(IActiveContext* dlgContext, IPanelControlData*, IStringListControlData*, UID);
/** a pointer to a method that fills the style group drop down control with the data from the given UID @see IDialogUtils::InitStyleGroupDropDownFromUID */
typedef int32 (*UIDFillerStyleGroupFunc)(IActiveContext* dlgContext, IPanelControlData*, IStyleGroupListControlData*, UID);
/** a pointer to a method that returns the UID selected in the control @see IDialogUtils::UIDFromDropDown */
typedef UID (*UIDExtractorFunc)(IWorkspace*, const IStringListControlData*, int32);

/** same as UIDFillerFunc, except this is a pointer to a member of the utils interface */
typedef int32 (IDialogUtils:: *UIDFillerFunc2)(IActiveContext* dlgContext, IPanelControlData*, IStringListControlData*, UID);
/** same as UIDExtractorFunc, except this is a pointer to a member of the utils interface */
typedef UID (IDialogUtils:: *UIDExtractorFunc2)(IWorkspace*, const IStringListControlData*, int32);
/** same as UIDFillerStyleGroupFunc, except this is a pointer to a member of the utils interface */
typedef int32 (IDialogUtils:: *UIDFillerStyleGroupFunc2 )(IActiveContext* dlgContext, IPanelControlData*, IStyleGroupListControlData*, UID);

// CLSFillerFunc's
/** a pointer to a method that fills the control with the data from the given ClassID @see IDialogUtils::InitDropDownFromService */
typedef int32 (*CLSFillerFunc)(IPanelControlData*, IStringListControlData*, ServiceID, ClassID);
/** a pointer to a method that returns the ClassID selected in the control @see IDialogUtils::ServiceFromDropDown */
typedef ClassID (*CLSExtractorFunc)(const IStringListControlData*, int32, ServiceID);
/** same as CLSFillerFunc, except this is a pointer to a member of the utils interface */
typedef int32 (IDialogUtils:: *CLSFillerFunc2)(IPanelControlData*, IStringListControlData*, ServiceID, ClassID);
/** same as CLSExtractorFunc, except this is a pointer to a member of the utils interface */
typedef ClassID (IDialogUtils:: *CLSExtractorFunc2)(const IStringListControlData*, int32, ServiceID);

/** Utility methods for dailog-related functions.
	<pre>Utils&lt;IDialogUtils&gt;()->QueryCalculatedText( ... ) ;</pre>
	@ingroup text_util
*/
class IDialogUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IDIALOGUTILS };

	static const bool16 kDontInvalidate = kFalse;
	static const bool16 kDontNotify = kFalse;
	static const bool16 kDoInvalidate = kTrue;
	static const bool16 kDoNotify = kTrue;
	static const bool16 kShow = kTrue;
	static const bool16 kHide = kFalse;
	static const bool16 kEnable = kTrue;
	static const bool16 kDisable = kFalse;

// =====================================================================================================================
	// helpers for IK2ServiceProvider's

	template <class I>
	int32 ServiceDropDownFiller(IPanelControlData*, IStringListControlData* offsetData, ServiceID sid, ClassID cid);

	template<class I>
	ClassID Index2ServiceStyle(const IStringListControlData* offsetData, int32 which, ServiceID sid);

	/**
		@note there are two methods of this name - one that allows a pointer to any function and another for pointers to this interface's methods.
	*/
	virtual void InitDropDownFromUID(IDialogController* controller, IActiveContext* dlgContext, IPanelControlData* panelData, WidgetID wid, UID uid, UIDFillerFunc dropDownFiller) = 0;
	virtual void InitDropDownFromUID(IDialogController* controller, IActiveContext* dlgContext, IPanelControlData* panelData, WidgetID wid, UID uid, UIDFillerFunc2 dropDownFiller) = 0;

	/**
		@note there are two methods of this name - one that allows a pointer to any function and another for pointers to this interface's methods.
	*/
	virtual void InitStyleGroupDropDownFromUID(IDialogController* controller, IActiveContext* dlgContext, IPanelControlData* panelData, WidgetID wid, UID uid, UIDFillerStyleGroupFunc dropDownFiller) = 0;
	virtual void InitStyleGroupDropDownFromUID(IDialogController* controller, IActiveContext* dlgContext, IPanelControlData* panelData, WidgetID wid, UID uid, UIDFillerStyleGroupFunc2 dropDownFiller) = 0;

	/**
		@note there are two methods of this name - one that allows a pointer to any function and another for pointers to this interface's methods.
	*/
	virtual UID UIDFromDropDown(IWorkspace* ws, const IDialogController* controller, WidgetID wid, UIDExtractorFunc dropDownExtractor) = 0;
	virtual UID UIDFromDropDown(IWorkspace* ws, const IDialogController* controller, WidgetID wid, UIDExtractorFunc2 dropDownExtractor) = 0;

	virtual int32 CharStyleDropDownFiller(IActiveContext* dlgContext, IPanelControlData* panelData, IStyleGroupListControlData* offsetData, UID uid) = 0;
	virtual int32 ParaStyleDropDownFiller(IActiveContext* dlgContext, IPanelControlData* panelData, IStyleGroupListControlData* offsetData, UID uid) = 0;
	virtual int32 TextStyleDropDownFiller(IActiveContext* dlgContext, IPanelControlData*, IStyleGroupListControlData* offsetData, UID uid, PMIID styleType) = 0;

	//virtual UID Index2ParaStyle(IWorkspace* ws, IStringListControlData* offsetData, int32 which) = 0;
	//virtual UID Index2CharStyle(IWorkspace* ws, IStringListControlData* offsetData, int32 which) = 0;

	/**
		@note there are two methods of this name - one that allows a pointer to any function and another for pointers to this interface's methods.
	*/
	virtual void InitDropDownFromService(IDialogController* controller, WidgetID wid, ServiceID sid, ClassID cid, CLSFillerFunc dropDownFiller, bool16 enable = kTrue, bool16 hide = kFalse) = 0;
	virtual void InitDropDownFromService(IDialogController* controller, WidgetID wid, ServiceID sid, ClassID cid, CLSFillerFunc2 dropDownFiller, bool16 enable = kTrue, bool16 hide = kFalse) = 0;

	virtual ClassID ServiceFromDropDown(IWorkspace* ws, const IDialogController* controller, WidgetID wid, ServiceID sid, CLSExtractorFunc dropDownExtractor) = 0;
	virtual ClassID ServiceFromDropDown(IWorkspace* ws, const IDialogController* controller, WidgetID wid, ServiceID sid, CLSExtractorFunc2 dropDownExtractor) = 0;

	virtual int32 DateServiceDropDownFiller(IPanelControlData*, IStringListControlData* offsetData, ServiceID sid, ClassID cid) = 0;
	virtual int32 NumberingServiceDropDownFiller(IPanelControlData*, IStringListControlData* offsetData, ServiceID sid, ClassID cid) = 0;
	virtual int32 StringServiceDropDownFiller(IPanelControlData*, IStringListControlData* offsetData, ServiceID sid, ClassID cid) = 0;

	virtual ClassID Index2DateStyle(const IStringListControlData* offsetData, int32 which, ServiceID sid) = 0;
	virtual ClassID Index2NumberingStyle(const IStringListControlData* offsetData, int32 which, ServiceID sid) = 0;
	virtual ClassID Index2StringStyle(const IStringListControlData* offsetData, int32 which, ServiceID sid) = 0;

	virtual Text::FirstLineOffsetMetric Index2FLO(const IStringListControlData* offsetData, int32 index) = 0;
	virtual bool16 FLO2Index(IStringListControlData* offsetData, Text::FirstLineOffsetMetric flo, bool16 JFeatureSet, int32 *index) = 0;

	virtual void InitColorDropDown(const IActiveContext* dlgContext, IPanelControlData* panelData, WidgetID wid, UID uid) = 0;
	virtual UID GetColorUID(IPanelControlData* panelData, WidgetID& widgetID) = 0;
	virtual UID GetColorUID(IControlView *view) = 0;
	virtual void SetColorUID(IPanelControlData* panelData, WidgetID& widgetID, UID& newUID) = 0;
	virtual void SetColorUID(IControlView *view, UID& newUID) = 0;

	virtual void InitStrokeStyleDropDown(const IActiveContext* dlgContext, IPanelControlData* panelData, WidgetID wid, ICompositionStyle::StrokeType strokeType) = 0;
	virtual void GetStrokeType(IPanelControlData* panelData, WidgetID& widgetID, ICompositionStyle::StrokeType& newStroke) = 0;
	virtual void GetStrokeType(IControlView *view, ICompositionStyle::StrokeType& newStroke) = 0;
	virtual void SetStrokeType(IPanelControlData* panelData, WidgetID& widgetID, ICompositionStyle::StrokeType& newStroke) = 0;
	virtual void SetStrokeType(IControlView *view, ICompositionStyle::StrokeType& newStroke) = 0;
	virtual void StrokeTypeControlHack(IPanelControlData* panelData, WidgetID wid) = 0;

	virtual bool16 EnableOverprint(const IDialogController* fController, int32 colorWID, UIDRef colorUIDRef, PMReal tint) = 0;
	virtual bool16 EnableGap(ICompositionStyle::StrokeType strokeType) = 0;

	virtual void EnableControl(IDialogController* controller, WidgetID nWidgetID, bool16 bEnable) = 0;
	virtual void EnableShowControl(IDialogController* controller, WidgetID nWidgetID, bool16 bEnableShow) = 0;

	virtual bool16 GetSourceFileViaDialog(IDFile& sourceFile) = 0;
	virtual IDocument* OpenFile(IDFile systemFile,bool32& docWasAlreadyOpen) = 0;
	virtual void CloseFile(IDocument *openedDoc, bool32 docWasAlreadyOpen) = 0;
};
#endif	// __IDialogUtils__

