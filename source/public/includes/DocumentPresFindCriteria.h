//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/DocumentPresFindCriteria.h $
//  
//  Owner: Dave Burnard
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
#ifndef _DocumentPresFindCriteria_
#define _DocumentPresFindCriteria_

#include "IDocumentPresentation.h"
#include "IDocumentUIUtils.h"

/**
	This file contains declarations of simple selector and comparison functions designed to be used with two methods
	from IDocumentUIUtils. 
	
		FindPresentationsForDocument: used to find and optionally order a subset of the presentations on a document (or on all documents)
		
		FindRelatedPresentations: used to find and optionally order a subset of the presentations on a document (or on all documents) that are related to
			a particular presentation (most commonly are the presentations of the same type) 
	
	The implementations of these functions are found in the WidgetBin shared library, so you cannot use them from a
		model only plugin. Should the need arise you can create local implementations, such as:

		static bool private_is_active(IDocumentPresentation* p)
		{
			return p->IsActive();
		}
*/


/**
	FindPresCriteria: are unary predicates (one parameter boolean functions) used to
		select and order the set of document presentations returned from IDocumentUIUtils::FindPresentationsForDocument.
		
	Examples:
		Find all minimized presentations, ordered so that the layout presentations come before any story editors.
				whichDocument: NIL
				acceptCriteria: is_minimized
				preferCriteria: is_layout
			
		Find all presentations, and order them loosely by activation (active one first followed by
			the frontmost ones in any tab groups, followed by the obscured ones in tab groups.
				whichDocument: NIL
				acceptCriteria: accept_all
				preferCriteria: is_active + is_frontmost_in_tabgroup
			
		Find all floating presentations, and order them loosely by activation
				whichDocument: NIL
				acceptCriteria: is_floating
				preferCriteria: is_active + is_frontmost_in_tabgroup
				
			Code snippet:
				PresentationSequence plist;
				FindPresentation_Criteria require = FindPresCriteria::is_floating; // only the floating ones
				FindPresentation_PreferCriteria prefer;
					prefer.push_back(FindPresCriteria::is_active);
					prefer.push_back(FindPresCriteria::is_frontmost_in_tabgroup);
				int32 count = Utils<IDocumentUIUtils>()->FindPresentationsForDocument(nil, plist, require, prefer);
*/

struct WIDGET_DECL FindPresCriteria
{
	static unary_presentation_predicate accept_all;

	static unary_presentation_predicate is_active;
	static unary_presentation_predicate is_frontmost_in_tabgroup;
	static unary_presentation_predicate is_layout;
	static unary_presentation_predicate is_floating;
	static unary_presentation_predicate is_minimized;
	static unary_presentation_predicate is_autonomous;
	static unary_presentation_predicate is_visible;
	static unary_presentation_predicate is_not_minimized;
	
	static unary_presentation_predicate IC_in_layoutmode;
	static unary_presentation_predicate IC_in_galleymode;
	static unary_presentation_predicate IC_in_storymode;
	static unary_presentation_predicate IC_in_galleyorstory;

	static FindPresentation_PreferCriteria empty;
};

/**
	FindRelatedPresCriteria: are binary predicates (two parameter boolean functions) used to
		select and order the set of document presentations relative to a particular one returned from IDocumentUIUtils::FindRelatedPresentations.
		
	Examples:
		Find all other presentations of the same kind on the same document as a particlar presentation, ordered loosely by activation. 
				whichDocument: document
				acceptCriteria: is_samekind
				preferCriteria: is_active + is_frontmost_in_tabgroup
				includeMe: kFalse
				
			Code snippet:
				PresentationSequence relatedPresentations;
				FindRelatedPresentation_Criteria require = FindRelatedPresCriteria::is_samekind;
				FindRelatedPresentation_PreferCriteria prefer;
					prefer.push_back(FindRelatedPresCriteria::is_active);
					prefer.push_back(FindRelatedPresCriteria::is_frontmost_in_tabgroup);
	
				int32 count = Utils<IDocumentUIUtils>()->FindRelatedPresentations(document, active, relatedPresentations, require, prefer);

			
*/
struct WIDGET_DECL FindRelatedPresCriteria
{
	//functors that test some quality of a potential relative
	static binary_presentation_predicate accept_all;
	
	static binary_presentation_predicate is_active;
	static binary_presentation_predicate is_frontmost_in_tabgroup;
	static binary_presentation_predicate is_layout;
	static binary_presentation_predicate is_floating;
	static binary_presentation_predicate is_minimized;
	static binary_presentation_predicate is_autonomous;
	static binary_presentation_predicate is_visible;
	
	static binary_presentation_predicate IC_in_layoutmode;
	static binary_presentation_predicate IC_in_galleymode;
	static binary_presentation_predicate IC_in_storymode;
	static binary_presentation_predicate IC_in_galleyorstory;

	//functors that do some sort of comparison between two potential relatives
	static binary_presentation_predicate is_samekind;
	static binary_presentation_predicate isnot_samekind;
	static binary_presentation_predicate is_samedocument;
	static binary_presentation_predicate isnot_samedocument;

	static FindRelatedPresentation_PreferCriteria empty;
};

#endif	/* DocumentPresFindCriteria */
