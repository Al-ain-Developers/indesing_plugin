//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IAttrReport.h $
//  
//  Owner: EricK
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
#ifndef __IAttrReport__
#define __IAttrReport__

#include "IPMUnknown.h"
#include "TextID.h"

class ICompositionStyle;
class IDrawingStyle;
class PMString;
class IDataBase;
class AttributeBossList;

/**  This interface is the "designator" interface for every text attribute.
	Each attribute implements the following methods:
	IsParagraphAttribute() -- obvious.
	TellComposition() -- each attribute tells the composition style boss
	what the attribute "means". Both &lt;style&gt; and &lt;draw&gt; are on the same
	boss. They are both passed in because half the attributes would need
	need to query for the other if they weren't both available.
	AppendAttributeName() -- add a descriptive name to the end of the passed in string
	AppendAttributeValue() -- add a descriptive value. These 2 are most likely going
	to change.
	 
	@ingroup text_attr
*/
class IAttrReport : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IATTRREPORT };

			/** See IAttrReport::RequiresRecomposition() for an explanation of the
				use of these enum values.
			 */
		enum RecompositionLevel {kInvalOnly, kInkBoundsChange, kRequiresRecomposition};
		
			/** See IAttrReport::AutomaticContinuation() for an explanation of the
				use of these enum values.
			 */
		enum ContinuationType {kNeverContinue, kAlwaysContinue, kContinueFromLeftOnly};

			/** Self explanatory.
			 */
		virtual bool16 IsParagraphAttribute() const = 0;
		
			/** The vast majority of attributes return kFalse.  However, if an attribute
				should not be altered when a style is applied, this method should return
				kTrue.  Examples of attributes that return kTrue include: the page number
				attribute that is applied to a page number character to indicate whether
				the number should be for this page, or the continued on/from page; the
				attribute used to indicate a carriage return is actually a column break,
				page break, etc. character; and a handful of other attributes.
			 */
		virtual bool16 LastsThroughStyleChange() const = 0;
		
			/** Most text attributes return kAlwaysContinue.  That is they should be
				extended to text that is added immediately to the right of a run of text
				that has this attribute applied.  (If you type directly following blue
				text the newly inserted text is also blue.)  However, some special case
				attributes only apply to a single character and should never be
				"propagated" to newly entered text.  Examples include: pair kerning;
				the attribute to identify a special glyph when no unique Unicode value
				exists; and the page number attribute that is applied to a page number
				character to indicate whether the number should be for this page, or
				the continued on/from page; among others.  kContinueFromLeftOnly is
				currently unused and should be considered deprecated.
			 */
		virtual IAttrReport::ContinuationType AutomaticContinuation() const = 0;
		
			/** Indicates whether this attribute should be part of style definitions.
				If a text attribute has no end user UI in the Style Options dialog, it
				should probably return kFalse (since if it were allowed into styles it
				would be difficult for the end user to edit or remove the attribute from
				the style).
			 */
		virtual bool16 CanBeInStyle() const = 0;

			/**	The values of the returned enum are used to decide what level of response is required
				when an attribute is applied into the model.  Most text attributes effect composition
				(glyph positions, font, point size, etc.).  Therefore most attributes return
				kRequiresRecomposition.  However, some attributes only require the screen to be
				inval'ed and redraw (i.e. color), thus kInvalOnly.  And still others don't affect
				composition, but may change the area the text marks (i.e. paragraph rule weight, offset)
				and thus kInkBoundsChange.  If your attribute adds a text adornment, kInkBoundsChange
				is the right choice.  (Returning anything other than kRequiresRecomposition is purely
				an optimization.  kRequiresRecomposition will always work, but is much slower.)
			 */
		virtual IAttrReport::RecompositionLevel RequiresRecomposition() const = 0;

			/** This is where a text attribute gets a chance to alter composition and/or what
				is attached to the text for drawing purposes (text adornments).  The ICompositionStyle
				and IDrawingStyle that are passed in are on the same boss.  (They're both passed since
				a large number of attributes would have to query for the other interface if only one
				was passed in.)  The IxxxStyle interfaces are the "setter" interfaces for the "knobs"
				that control text composition.
			 */
		virtual void TellComposition(ICompositionStyle *style, IDrawingStyle *draw) const = 0;

			/** AppendDescription is used to generate the style descriptions that are displayed in the
				"Settings" display of the "General" panel of the "Style Options" dialog as well as by
				the style overrides tooltip (that displays when the user lingers over the "+" override
				symbol next to a style name in the Styles Palettes.
				@param into is the string to append the description to.
				@param theDB the database (document) the attribute is in.  (This may be needed to lookup
				a human readable name associated with a UID referenced by an attribute, such as a Swatch name.)
				@param attrBossList the other attributes that are applied to the same text run or text style
				as this attribute.  In some cases it is difficult to create a nicely formatted string without
				knowing the value of other closely related attributes.
			 */
		virtual void AppendDescription(PMString *into, IDataBase *theDB, const AttributeBossList *attrBossList) const = 0;
};


#endif		// __IAttrReport__