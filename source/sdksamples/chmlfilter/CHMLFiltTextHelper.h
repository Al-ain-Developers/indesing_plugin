//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chmlfilter/CHMLFiltTextHelper.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef __CHMLFiltTextHelper_H_DEFINED__
#define __CHMLFiltTextHelper_H_DEFINED__

#include "K2SmartPtr.h"
#include "RangeData.h"
#include "AttributeBossList.h"
#include "ICompositionStyle.h"

/** Helper methods to ease text manipulations; these can be used to add overrides to both character and paragraph
	attributes to a specified text model and range (RangeData). Note that the overrides will not be applied until
	the Apply method is called on the instance. This enables several different overrides to be stored up and then applied
	by processing a single command rather than lots of individual commands for each override.
	@ingroup chmlfilter
*/
class CHMLFiltTextHelper {

public:

	/**Constructor taking a text model and a range.
		@param textModelUIDRef IN text model to encapsulate
		@param targetRangeData IN range over which this will operate
	*/
	CHMLFiltTextHelper(const UIDRef& textModelUIDRef, const RangeData& targetRangeData);	

	/** Constructor taking just a text model but no range.
		@param textModelUIDRef IN text model to encapsulate
	*/
	CHMLFiltTextHelper(const UIDRef& textModelUIDRef);

	/** Destructor */
	virtual ~CHMLFiltTextHelper();
	
	/**  Method to insert a WideString into the text model at the current insertion position (start of encapsulated range
		or the insertion position stored in this).

		@param wstr IN text to insert
		@precondition wstr should not be an empty string
		@return kSuccess on a successful insertion, kFailure otherwise
		@postcondition on success the text model will now contain the contents of wstr at insertion position or start of range stored in this
	*/
	ErrorCode InsertText(const WideString& wstr);


	/**  Applies the overrides stored in this object to appropriate targets 
		 such as the strand for paragraph attributes 
		 (kParaAttrStrandBoss) or character attributes (kCharAttrStrandBoss).

		@precondition some overrides ought to have been added
		@return kSuccess if overrides could be applied, kFailure otherwise
		@postcondition text in range specified by encapsulated RangeData and text model would have overrides indicated,
		override lists flushed for next Apply
	*/
	ErrorCode Apply();


	/**  Add an underline override.
		@precondition there should be a range set
		
		@postcondition an underline override attribute is stored in this ready to be applied on the range
	*/
	void AddUnderline();


	/**  Add an override to remove underlining
		@precondition there should be a range set
		
		@postcondition the underline override will be turned off on the range stored in this when the Apply method is called
	*/
	void AddNonUnderline();


	/**  Add an alignment override (paragraph level attribute)
		@param alignment IN specifies the type of alignment to set
		@precondition there should be a range set
		
		@postcondition alignment override is stored ready to be applied when Apply called
	*/
	void AddAlignment(ICompositionStyle::TextAlignment alignment);


	/**  Add a override to add a bold style
		@precondition there should be a range set
		
		@postcondition bold override  stored ready to be applied when Apply called
	*/
	void AddBold();


	/**  Add override to restore the default font (e.g. to remove bold)
		@precondition there should be a range set
		
		@postcondition  default font attribute ready to be applied when Apply called
	*/
	void AddDefaultFont();


	/**  Add a point size override
		@param pointSize IN point size of override.
		@precondition pointSize should be > 0 and a range set
	
		@postcondition point size is stored ready to be applied
	*/
	void AddPointSize(const PMReal& pointSize);


	/**  Add a font override
		@param fontName IN name of font to apply
		@precondition there should be a range set and the font should ideally exist in the document
		
		@postcondition a font override is stored ready for an Apply
	*/
	void AddFont(const PMString& fontName);


	/**  Change the encapsulated text range (stored in a RangeData)
		@param targetRangeData IN new range 
		@postcondition the encapsulated range has changed
	*/
	void Reset(const RangeData& targetRangeData);


	/**  Change from a range to an insertion position
		@param position IN insertion position in text model.
		@precondition position should lie in the span of the text model
		
		@postcondition we now encapsulate an insertion position
	*/
	void Reset(const TextIndex& position);


	
	
protected:
	void checkInvariant();
	ErrorCode doApplyAttributes(boost::shared_ptr<AttributeBossList>& attrList, const ClassID& which);

private:

	UIDRef fTextModelUIDRef;
	RangeData fRangeData;
	boost::shared_ptr<AttributeBossList> fCharAttributeBossList;
	boost::shared_ptr<AttributeBossList> fParaAttributeBossList;

};



#endif // __CHMLFiltTextHelper_H_DEFINED__


//  Code generated by DollyXS code generator
