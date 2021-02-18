//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightObjectModelUtils.h $
//  
//  Owner: Matt Phillips
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

#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "PreflightObjectID.h"
#include "Utils.h"
#include "TableTypes.h"

class IDocument;
class ISpread;
class IShape;

/**	Preflight object model utilities. These utilities initialize and return PreflightObjectIDs 
	corresponding to well-known entities in the InDesign object model.

	This interface lives on the global utilities boss. Use it via

		Utils<IPreflightObjectModelUtils>()->XX();

		or 

		Utils<IPreflightObjectModelUtils> iUtils;
		iUtils->XX();
*/
class IPreflightObjectModelUtils : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTOBJECTMODELUTILS };

public:

	/** Obtain a preflight ObjectID for a document.

		@param iDoc IN The document you want an object ID for.
		@return The object ID corresponding to the document. Note that this is NOT a UID; this ID
				makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetDocumentObject(const IDocument* iDoc) const = 0;

	/** Obtain a preflight ObjectID for a spread. 

		@param iDoc IN The spread you want an object ID for.
		@return The object ID corresponding to the spread. Note that this is NOT a UID; this ID
				makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetSpreadObject(const ISpread* iSpread) const = 0;

	/** Obtain a preflight ObjectID for a page item (IShape based). The result will will be 
		a kPreflightOM_PageItem class preflight object; no attempt is made to specialize further.

		@param iDoc IN The page item you want an object ID for.
		@return The object ID corresponding to the spread. Note that this is NOT a UID; this ID
				makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetShapeObject(const IShape* iShape) const = 0;

	/** Obtain a preflight ObjectID for a text range. The class ID is kPreflightOM_TextRange.

		@param textModelRef IN The UIDRef of the text model.
		@param start IN The starting index in model.
		@param span IN The number of characters in the range (starting at 'start')
		@return The object ID corresponding to the text range. Note that this is NOT a UID; this ID
				makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetTextRangeObject
		(
			const UIDRef& textModelRef,
			TextIndex start,
			int32 span
		) const = 0;

	/** Obtain a preflight ObjectID for a text wax run. The class ID is kPreflightOM_WaxRun.

		@param textModelRef IN The UIDRef of the text model.
		@param start IN The starting index in model of the wax run.
		@return The object ID corresponding to the text range. Note that this is NOT a UID; this ID
				makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetTextWaxRunObject
		(
			const UIDRef& textModelRef,
			TextIndex start
		) const = 0;

	/** Obtain a preflight ObjectID for a text wax run adornment. The class ID is kPreflightOM_WaxRunAdornment.

		@param textModelRef IN The UIDRef of the text model.
		@param start IN The starting index in model of the wax run.
		@param adornmentID IN The class ID of the adornment on the run. If kInvalidClass, this is
				the same as calling GetTextWaxRunObject.
		@return The object ID corresponding to the text run. Note that this is NOT a UID; this ID
				makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetTextWaxRunAdornmentObject
		(
			const UIDRef& textModelRef,
			TextIndex start,
			ClassID adornmentID
		) const = 0;

	/** Obtain a preflight ObjectID for a single character. The class ID is kPreflightOM_TextCharacter
		and is reported differently from a single-character text range, ie its glyph data is shown.

		@param textModelRef IN The UIDRef of the text model.
		@param index IN The index of the character in the model.
		@return The object ID corresponding to the character. Note that this is NOT a UID; this ID
				makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetTextCharacterObject
		(
			const UIDRef& textModelRef,
			TextIndex index
		) const = 0;

	/** Obtain a preflight ObjectID for a table area or table frame area.

		@param tableModelRef IN The UIDRef of the table model.
		@param tableFrameRef IN The UIDRef of the table frame model, or UIDRef() if this 
			is table area and not a frame area.
		@param area IN The grid area for the cell range. Empty area = whole table.
		@return The object ID corresponding to the table or frame area. Note that this is NOT 
			a UID; this ID makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetTableAreaObject
		(
			const UIDRef& tableModelRef,
			const UIDRef& tableFrameRef,
			const GridArea& area
		) const = 0;

	/** Obtain a preflight ObjectID for the document spell check state. This is a virtual object which
		is invalidated when the application-level spell check state changes or dynamic spelling indicates
		that the document has moved from a no-error to error state or vice-versa.

		@return The object ID corresponding to the spell check state. Note that this is NOT 
			a UID; this ID makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetSpellCheckStateObject(const IDocument* iDoc) const = 0;

	/** Obtain a preflight ObjectID for the tracked change state. This is a virtual object which
		is invalidated when the the document has moved from a no-error to error state or vice-versa.

		@return The object ID corresponding to the spell check state. Note that this is NOT 
			a UID; this ID makes sense only within the preflight model.
	*/
	virtual PreflightObjectID GetTrackedChangeStateObject(const IDocument* iDoc) const = 0;
};



