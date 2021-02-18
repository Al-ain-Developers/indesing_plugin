//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/components/testing/aat/includes/AcquisitionElements.h $
//  
//  Owner: robin briggs
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
//  
//  Interface for storing UIDs.
//  
//========================================================================================

#pragma once
#ifndef __AcquisitionElements__
#define __AcquisitionElements__

#include "IXMLOutStream.h"
#include "AATXMLTagDefs.h"
#include "ProductTypeDefs.h"

class UIGroup;

class  VAcquisitionElement
{
	public:
		virtual ~VAcquisitionElement(void) {}
		
		virtual void		Write(IXMLOutStream *s) = 0;
		virtual void		WriteEntry(IXMLOutStream *stream, const WideString &tag, const WideString &value) = 0;
		
		virtual UIGroup*		GetParentGroup(void)  = 0;
		virtual void	SetParentGroup(UIGroup *parent) = 0;
		
		virtual ProdString 	GetElementToken(void) = 0;
		virtual void		SetElementToken(const ProdString &str) = 0;
		
		virtual	ProdInt32 		GetType(void) = 0;
		
		virtual	void 		SetName(const ProdString &str) = 0;
		virtual	ProdString 	GetName(void) = 0;
		
		virtual	void 		SetBounds(const ProdRect &rect) = 0;
		virtual	ProdRect 		GetBounds(void) = 0;

		virtual void		SetWidgetID(const WidgetID &id) = 0;
		virtual WidgetID	GetWidgetID(void) = 0;
		
		virtual void				SetWidgetType(const ProdString &str) = 0;
		virtual const ProdString & 	GetWidgetType(void) = 0;
		
		virtual void		AddValueEntry(const ProdString &str) = 0;
		virtual ProdInt32		GetNumValues(void) = 0;
		virtual ProdString 	GetNthValue(ProdInt32 index) = 0;
		
		virtual void		SetValue(const ProdString &str) = 0;
		virtual ProdString	GetValue(void) = 0;
		
		virtual void		SetMinValue(const ProdString &min) = 0;
		virtual void		SetMaxValue(const ProdString &max) = 0;
		virtual ProdString	GetMinValue(void) = 0;
		virtual ProdString	GetMaxValue(void) = 0;
		
		virtual void		SetRowIndex(ProdInt32 index) = 0;
		virtual void		GetRowIndex(K2Vector<ProdInt32> &rows) = 0;
		virtual void		SetColumnIndex(ProdInt32 index) = 0;
		virtual ProdInt32		GetColumnIndex(void) = 0;
		
		virtual void		SetEnabled(ProdBool enabled) = 0;
		virtual ProdBool		GetEnabled(void) = 0;
		
		virtual void		AddToolTip(const ProdString& tipText) = 0;
		virtual ProdInt32	GetNumToolTips(void) = 0;
		virtual ProdString 	GetNthToolTip(ProdInt32 index) = 0;
		
		virtual void		SetParentPanelChain(const K2Vector<WidgetID> &id) = 0;
		virtual void		GetParentPanelChain(K2Vector<WidgetID> &id) = 0;
		
		virtual void		SetParentPanel(WidgetID id) = 0;
		virtual WidgetID	GetParentPanel(void) = 0;
	
};

typedef enum {
	kElementType = 1,
	kGroupType = 2
} eElementTypes;

class AATLIB_DECL AcquisitionElement : public VAcquisitionElement
{
	public:
		AcquisitionElement(void) : fColIndex(-1),
			 fParent(nil), fToken(kWidgetEntryToken), fEnabled(kFalse) {}
		
		virtual ~AcquisitionElement(void) {}
		
		virtual void		Write(IXMLOutStream *stream);
		virtual void		WriteEntry(IXMLOutStream *stream, const WideString &tag, const WideString &value);
		
		virtual UIGroup*		GetParentGroup(void) { return fParent; }
		virtual void	SetParentGroup(UIGroup *parent) { fParent = parent; }
		
		virtual ProdString 	GetElementToken(void) { return fToken; }
		virtual void		SetElementToken(const ProdString &str) { fToken = str; }
		
		virtual	ProdInt32 		GetType(void) { return kElementType; }
		
		virtual	void 		SetName(const ProdString &str) { fName = str; }
		virtual	ProdString 	GetName(void) { return fName; }
		
		virtual	void 		SetBounds(const ProdRect &rect) { fBounds = rect; }
		virtual	ProdRect 		GetBounds(void) { return fBounds; }
	
		virtual void		SetWidgetID(const WidgetID &id) { fWidID = id; }
		virtual WidgetID	GetWidgetID(void) { return fWidID; }
		
		virtual void				SetWidgetType(const ProdString &str) { fWidgetTag = str; }
		virtual const ProdString & 	GetWidgetType(void) { return fWidgetTag; }
		
		virtual void		AddValueEntry(const ProdString &str) { fValues.push_back(str); }
		virtual ProdInt32		GetNumValues(void) { return K2length(fValues); }
		virtual ProdString 	GetNthValue(ProdInt32 index);
		
		virtual void		SetValue(const ProdString &str) { fVal = str; }
		virtual ProdString	GetValue(void) { return fVal; }
		
		virtual void		SetMinValue(const ProdString &min) { fMin = min; }
		virtual void		SetMaxValue(const ProdString &max) { fMax = max; }
		virtual ProdString	GetMinValue(void) { return fMin; }
		virtual ProdString	GetMaxValue(void) { return fMax; }
		
		virtual void		SetRowIndex(ProdInt32 index){ fRowIndex.push_back(index); }
		virtual void		GetRowIndex(K2Vector<ProdInt32> &rows) { rows = fRowIndex; }
		virtual void		SetColumnIndex(ProdInt32 index) { fColIndex = index; }
		virtual ProdInt32		GetColumnIndex(void)  { return fColIndex; }
		
		virtual void		SetEnabled(ProdBool enabled) { fEnabled = enabled; }
		virtual ProdBool		GetEnabled(void) { return fEnabled; }
		
		virtual void		AddToolTip(const ProdString& tipText) { fTipText.push_back(tipText); }
		virtual ProdInt32	GetNumToolTips(void) { return K2length(fTipText); }
		virtual ProdString 	GetNthToolTip(ProdInt32 index);
		
		virtual void		SetParentPanelChain(const K2Vector<WidgetID> &id);
		virtual void		GetParentPanelChain(K2Vector<WidgetID> &id);
		
		virtual void		SetParentPanel(WidgetID id);
		virtual WidgetID	GetParentPanel(void) { return fParentIDChain.size() ? fParentIDChain.back() : kInvalidWidgetID; }
		
	protected:
		virtual void		GetTagValues(IXMLOutStream::AttributeList &outList);
		virtual void		WriteValues(IXMLOutStream *s);
		virtual void		WriteParentEntries(IXMLOutStream *stream);

		ProdString 	fVal;
		ProdString	fMin;
		ProdString	fMax;
		ProdString 	fToken;
		
		ProdString 	fName;
		ProdRect				fBounds;
		K2Vector<ProdInt32>		fRowIndex;
		ProdInt32				fColIndex;
		ProdBool				fEnabled;
		
		K2Vector<WidgetID>	fParentIDChain;
		WidgetID	fWidID;
		ProdString	fWidgetTag;
		K2Vector<ProdString> fValues;
		K2Vector<ProdString> fTipText;
		UIGroup		*fParent;
};

class AATLIB_DECL ClickableStringElement : public AcquisitionElement
{
	public:
		ClickableStringElement(void) {}
		
		virtual ~ClickableStringElement(void) {}
		
		virtual void		SetAssocID(WidgetID id) { fAssocID = id; }
		virtual WidgetID	GetAssocID(void) { return fAssocID; }
		
	protected:
		virtual void		GetTagValues(IXMLOutStream::AttributeList &outList);
		
		WidgetID	fAssocID;
};

class AATLIB_DECL UIGroup : public AcquisitionElement
{
	public:
		UIGroup(void) : fSuppressCheck(kFalse), fCanAdd(kTrue) { fToken = kGroupPanelWidgetToken; }
		UIGroup(const ProdString &str) : fSuppressCheck(kFalse), fCanAdd(kTrue) { fToken = str; }
		
		virtual ~UIGroup(void);
		virtual void	Write(IXMLOutStream *s);
		
		virtual	ProdInt32 GetType(void) { return kGroupType; }
		
		virtual void	Clear(bool16 deleteKids = kTrue);
		ProdBool				AddElement(VAcquisitionElement *element);
		ProdInt32				GetNumElements(void);
		VAcquisitionElement*	GetNthElement(ProdInt32 index);
		
		void		AddGroup(UIGroup *group);
		UIGroup*	GetNthGroup(ProdInt32 index);
		ProdInt32 		GetNumGroups(void);
		
		virtual void	SetSuppressBoundsCheck(ProdBool val) { fSuppressCheck = val; }
		virtual ProdBool	GetSuppressBoundsCheck(void) { return fSuppressCheck; }
		
		virtual ProdBool	GetCanAdd(void) { return fCanAdd; }
		virtual void		SetCanAdd(ProdBool addItems) { fCanAdd = addItems; }
		
		virtual void	CleanUp(void);
		
	protected:
		virtual void	WriteChildren(IXMLOutStream *stream);
		
		ProdBool		fSuppressCheck;
		ProdBool		fCanAdd;
		K2Vector<VAcquisitionElement*> fElements;
};


#endif // __AcquisitionUtils__
