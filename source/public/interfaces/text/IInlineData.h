//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IInlineData.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __IInlineData__
#define __IInlineData__

#include "IPMUnknown.h"
#include "TextID.h"
#include "ParcelKey.h"

class IHierarchy;
class IItemContext;
class IParcel;
class ITextFrameColumn;
class ITextModel;
class ITextParcelList;
class ITextStoryThread;
class IWaxLine;
class IWaxStrand;
class PMMatrix;
class PMPoint;
class PMRect;

/**
	The ILG is considered position dependent content for the Parcel and
	as such must be notified whenever it moves relative to the Pasteboard.

	@ingroup text_owned
*/
class IInlineData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IINLINEDATA };

	/**
	@return the UID of the text story containing the ILG
	*/
	virtual UID				GetTextModelUID() const = 0;

	/**
	@return the text story containing the ILG
	*/
	virtual ITextModel*		QueryTextModel() const = 0;

	/**
	@return the WaxStrand of the text story containing the ILG
	*/
	virtual IWaxStrand*		QueryWaxStrand() const = 0;

	/**
	@return the TextStoryThread containing the ILG
	*/
	virtual const ITextStoryThread*	QueryStoryThread() const = 0;

	/**
	@return the TextParcelList of the text story thread containing the ILG
	*/
	virtual const ITextParcelList*	QueryTextParcelList() const = 0;

	/**
	@return the registered ParcelKey of the ILG. This value is set when the ILG is Applied() and cleared when it is Unregister()ed. Thus registered Inlines return a valid ParcelKey and unregistered ones do not.
	*/
	virtual ParcelKey		GetParcelKey() const = 0;

	/**
	@return the Parcel of the ILG. This value is set when the ILG is Applied() and cleared when it is Unregister()ed.
	*/
	virtual const IParcel *	QueryParcel() const = 0;

	/**
	Relative to the Wax, or content coordinate space, the Inline is translated
	by the waxToILGMatrix provided at Register().
	@return PMMatrix to translate from Wax to Inline position
	*/
	virtual PMMatrix		GetWaxToILGMatrix() const = 0;

	/**
	@return the TextIndex of the ILG in the strands
	*/
	virtual TextIndex		GetILGIndex() const = 0;

	/**
	@return UIDRef for the TextFrameColumn that the Parcel containing the
	Inline is part of.
	*/
	virtual UIDRef			GetTextFrameRef() const = 0;

	/**
	@return The TextFrameColumn that the Parcel containing the Inline is
	part of.
	*/
	virtual ITextFrameColumn*	QueryTextFrame() const = 0;

	/**
	@return the root UID of the TextFrame associated with the Parcel.
	*/
	virtual UID				GetSpreadUID() const = 0;

	/**
	Sets (when created) the type of object, the key used by the item strand
	@param objectType ClassID
	*/
	virtual void			SetObjectDesignation(ClassID objectType) = 0;

	/**
	@return	The key used by the item strand
	*/
	virtual ClassID			GetObjectDesignation() const = 0;

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
	@return The pasteboard rectangle that the Inline is constrained to.
	*/
	virtual PMRect			GetConstrainedTo() const = 0;

	/**
	The containing story thread, and any threads that it is anchored in, are
	forced to be composed. Note that this may or may not result in the Inline
	being registered - the inline or a containing anchor thread may still be
	in overset.
	*/
	virtual void			RecomposeThru() const = 0;

	/**
	*/
	virtual void			InlineChangeDamage() const = 0;
    
    /**
     */
    virtual void            InlineContentDamage() const = 0;

	// Returns the item context on the text frame containing the Inline,
	// or the one on the last text frame, if the frame is overset.
	virtual IItemContext*	QueryItemContext() const = 0;

	/**
	Unregister the Inline. May be safely called even if the Inline is already
	unregistered.
	*/
	virtual void			UnRegister() = 0;

	/**
	Returns kTrue if any descendent of the Inline has a page item hyperlink.
	*/
	virtual bool16			GetHasPageItemHyperlink() const = 0;

	/// Adobe internal use only
	virtual void			ConvertPhase2(ITextModel* textModel, TextIndex at,
											int32 privatePhase2Code) = 0;

	/// Adobe internal use only.
	virtual bool16			Register(const IWaxLine* waxLine,
									const IParcel* pParcel,
									const PMMatrix& waxToILGMatrix) = 0;

	/// Adobe internal use only.
	virtual bool16			Rebuilt(const PMMatrix& waxToILGMatrix, bool16* damagedBack = nil) = 0;

	/// Adobe internal use only
	virtual bool16			GetRegistering() const = 0;

};

#endif

