//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IIndexXRefEntryData.h $
//  
//  Owner: Michel Hutinel
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
//  
//  Comments: This interface saves the informations about an XRef Page Entry.
//  
//========================================================================================

#pragma once
#ifndef __IINDEXXREFENTRYDATA__
#define __IINDEXXREFENTRYDATA__

#include "IPMUnknown.h"
#include "IndexingID.h"

class WideString;
class IndexTopicEntry;

/** Data interface that aggregates information about a cross-reference entry.
	@ingroup layout_index
*/
class IIndexXRefEntryData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IINDEXXREFENTRYDATA };
		
		/** Type of cross-reference */
		enum XRefType {	kSeeOrAlso = 0,				// also used in Japanese for "See [also], See also"
						kSee = 1,
						kSeeAlso = 2,				// also used in Japanese for "Arrow"
						kSeeHerein = 3,				// also used in Japanese for "See herein, See also herein"
						kSeeAlsoHerein = 4,			// also used in Japanese for "Pointed hand"
						kCustom = 5,				// customString must be != NULL and not empty
						// MH 07/31/01: 2 new XRefType values added to match with last version (6) of "InDesign Indexing Interface (Japanese)"
						// kCustom is left and is identified to kCustomBefore: use now kCustomBefore 
						// There is really only one value added: kCustomAfter
						// kCustomBefore: the custom string is display (preview or generated index) before the referenced topic
						// kCustomAfter: the custom string is display (preview or generated index) after the referenced topic
						// Ther file format is not changed
						kCustomBefore = 5,			// customString must be != NULL and not empty
						kCustomAfter = 6};			// customString must be != NULL and not empty

		/**	Retrieves the type of the cross-reference.
			@param customString [OUT] - optional, will contain the value of the custom string on return.
			@return the type of the cross-reference.
		 */
		virtual IIndexXRefEntryData::XRefType	GetXRefType(WideString* customString = NULL) const = 0;		

		/**	Sets the type of the cross-reference.
			@param xRefType [IN] - the type of the cross-reference.
			@param customString [IN] - if the type is custom,
			this parameter specifies the value of the custom string.
		 */
		virtual void		SetXRefType(const IIndexXRefEntryData::XRefType xRefType, const WideString* customString = NULL) = 0;

		/**	Retrieves the UID of the kIndexXRefLinkBoss associated with this cross-reference.
			@return UID of kIndexXRefLinkBoss.
		 */
		virtual UID			GetXRefLinkUID() const = 0;

		/**	Sets the UID of the kIndexXRefLinkBoss associated with this cross-reference.
			@param xRefLinkUID [IN] - UID of kIndexXRefLinkBoss.
		 */
		virtual void		SetXRefLinkUID(const UID xRefLinkUID) = 0;

		/**	Retrieves the topic entry that this cross-reference refers to.
			@param topicEntry [OUT] - the topic entry refered by this cross-reference.
			@param sectionUID [OUT] - the UID of the topic section.
			@param nodeId [OUT] - the topic node id within the section.
		 */
		virtual void		GetRefedTopicEntry(IndexTopicEntry& topicEntry, UID *sectionUID = nil, int32 *nodeId = nil) const = 0;

};

#endif // __IINDEXXREFENTRYDATA__