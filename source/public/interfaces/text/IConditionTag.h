//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IConditionTag.h $
//  
//  Owner: Michele Stutzman
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
#ifndef __ICONDITIONTAG__
#define __ICONDITIONTAG__

#include "IPMUnknown.h"
#include "ConditionalTextID.h"

class PMString;

/** Interface to get and set data associated with condition tags. These
	are known as "conditions" in the conditional text UI. High-level 
	operations are provided by the conditional text facade.
	
	@see kConditionTagBoss
	@see IConditionalTextFacade
*/
class IConditionTag : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_ICONDITIONTAG };

	typedef enum {
		kUnderline = 0,
		kHighlight = 1,
	} IndicatorMethod;

	typedef enum {
		kSingleWavy = 0,
		kSolid = 1,
		kDashed = 2,
	} UnderlineIndicatorAppearance;


	/**	Get the name of the condition tag.
		@return WideString The name of the condition tag
	 */
	virtual WideString GetName() const = 0;

	/**	Set the name of the condition tag.
		@param name IN The new name for the condition tag
	 */
	virtual void SetName(const WideString& name) = 0;

	/**	Get the visibility for text with this condition tag applied.
		@param none
		@return bool16 
	 */
	virtual bool16 IsVisible() const = 0;
	
	/**	Set the visiblity for text with this condition tag applied.
		@param visible The kTrue if the text with this condition tag applied should who or kFalse if it should hide
	 */
	virtual void SetVisible(bool16 visible) = 0;

	/**	Get the display color for text with this condition tag applied.
		@return UID The UID of the color
	 */
	virtual UID GetColor() const = 0;

	/** Set the display color for the text with this condition tag applied.
		@param colorUID The UID of the color 
	 */
	virtual void SetColor(UID colorUID) = 0;

	/**	Get the method of indicator for text with this condition tag applied.
		@return IndicatorMethod The method for the indicator
	 */
	virtual IndicatorMethod GetMethod() const = 0;

	/** Set the method of indicator for the text with this condition tag applied.
		@param method The method for the indicator
	 */
	virtual void SetMethod(IndicatorMethod method) = 0;

	/**	Get the appearance of the underline indicator for text with this condition tag applied.
		@return UnderlineIndicatorAppearance The appearance for the underline indicator
	 */
	virtual UnderlineIndicatorAppearance GetAppearance() const = 0;

	/** Set the appearance of the underline indicator for the text with this condition tag applied.
		@param appearance The appearance setting for the underline indicator
	 */
	virtual void SetAppearance(UnderlineIndicatorAppearance appearance) = 0;
};

#endif // __ICONDITIONTAG__
