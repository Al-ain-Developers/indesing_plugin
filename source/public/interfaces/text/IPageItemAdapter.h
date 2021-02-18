//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IPageItemAdapter.h $
//  
//  Owner: shagupta
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
//  Copyright 2013 Adobe Systems Incorporated
//  All Rights Reserved.
//  
//  NOTICE:  All information contained herein is, and remains
//  the property of Adobe Systems Incorporated and its suppliers,
//  if any.  The intellectual and technical concepts contained
//  herein are proprietary to Adobe Systems Incorporated and its
//  suppliers and are protected by all applicable intellectual property
//  laws, including trade secret and copyright laws.
//  Dissemination of this information or reproduction of this material
//  is strictly forbidden unless prior written permission is obtained
//  from Adobe Systems Incorporated.
//  
//========================================================================================


#pragma once
#ifndef __IPageItemAdapter__
#define __IPageItemAdapter__

#include "IPMUnknown.h"
#include "TextID.h"

class ITextFrameColumn;
class PMRect;
class IParcel;
class ParcelKey;
class ITextModel;
class IItemContext;

/**
	The page items can be placed inside text as inlines or placed inside graphic cells of tables.
	This is a common wrapper of such objects, for interaction of text with objects and vice-versa.
	This interface is always available on such objects.

*/
class IPageItemAdapter : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPAGEITEMADAPTER };

	/**
	@return UIDRef for the TextFrameColumn that the Parcel containing the
	PageItem is part of.
	*/
	virtual UIDRef			GetTextFrameRef() const = 0;

	/**
	@return The TextFrameColumn that the Parcel containing the PageItem is
	part of.
	*/
	virtual ITextFrameColumn*	QueryTextFrame() const = 0;

	/**
	@return the root UID of the TextFrame associated with the Parcel.
	*/
	virtual UID				GetSpreadUID() const = 0;

	/**
	Equivalent to GetStrokeBoundingBox() on the child PageItem.
	*/
	virtual PMRect			GetGlyphBoundingBox() const = 0;

	/**
	Equivalent to GetPaintedBBox() on the child PageItem.
	*/
	virtual PMRect			GetPaintedBoundingBox() const = 0;

	/**
	Equivalent to GetPrintedBBox() on the child PageItem.
	@param includeAdornments [IN] Whether or not printing adornments are included in the resulting bounding box
	*/
	virtual PMRect			GetPrintedBoundingBox(bool32 includeAdornments = kTrue) const = 0;

	/**
	@return The pasteboard rectangle that the PageItem is constrained to.
	*/
	virtual PMRect			GetConstrainedTo() const = 0;

	/**
	Returns kTrue if any descendent of the has a page item hyperlink.
	*/
	virtual bool16			GetHasPageItemHyperlink() const = 0;

	/**
	@return the registered ParcelKey of the Page Item.
	*/
	virtual ParcelKey		GetParcelKey() const = 0;

	/**
	@return the Parcel of the Page Item.
	*/
	virtual const IParcel*	QueryParcel() const = 0;

	/**
	@return the text story containing the page item
	*/
	virtual ITextModel*		QueryTextModel() const = 0;

	/** Returns the item context on the text frame containing the object,
	 or the one on the last text frame, if the frame is overset.
	*/
	virtual IItemContext*	QueryItemContext() const = 0;

	/**
	Adobe internal use only
	Called after the parcel containing this object is invalidated
    */ 
	virtual void NotifyCacheInval(bool16 isRebuilding) const = 0;

	/** 
	Adobe internal use only 
	Called after the damage is clear, appropriate action to the changes should be taken
    */ 
    virtual void NotifyChangeDamage() const = 0; 

    /**
     Adobe internal use only
     Called after the damage is clear, appropriate action to the changes should be taken
     */
    virtual void NotifyContentDamage() const = 0; 
	/** 
	Adobe internal use only 
	Called if the descendants of the object has been changed, and appropriate action needs to be taken
    */
	virtual void NotifyDescendentChanged() const = 0;

	/** Adobe internal use only 
	*/
	virtual bool16	GetRegistering() const = 0;
};

#endif

