//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLImportMatchRecorder.h $
//  
//  Owner: Will Lin
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
#ifndef __IXMLImportMatchRecorder__
#define __IXMLImportMatchRecorder__


#include "KeyValuePair.h"
#include "XMLID.h"
#include "XMLReference.h"


class IIDXMLDOMNode;

/** interface to perform XML import match notification and record keeping */
class IXMLImportMatchRecorder : public IPMUnknown {
	public:
		enum { kDefaultIID = IID_IXMLIMPORTMATCHRECORDER };

		/** a match record denoting how an incoming XML node is matched to the existing node
		@param key left tree (incoming XML) node
		@param value right tree (existing/importing into) node
		*/
		typedef KeyValuePair<IIDXMLDOMNode*, XMLReference> MatchRecord;

		/** call this method to record a match
		@param leftNode incoming node
		@param rightNode left node is matched to this node in the right/existing tree. If 
		kInvalidXMLReference is used, it means a match was made, and leftNode was matched to 
		nothing. This is different than no match made (in which case this function should not 
		be called at all)
		@param rightNodeIsNew indicates whether the right node is a new element in the document.
		If the element is an existing element or one that was cloned/duplicated from an existing 
		element, then the element/node is not new. If the element was created by, for example, 
		a XMLCreateElementCmd, or it was cloned/duplicated from a new element, then the element 
		is new
		@param recordAsLastMatch if kTrue (default), the given match will be recorded as the
		last match made. Until another RecordMatch is called on this level, all subsequent 
		calls to GetLastMatch() will return this match. If kFalse, the given match will not 
		be recorded as last match. The previous last match record will remain
		*/
		virtual void RecordMatch(IIDXMLDOMNode *leftNode, const XMLReference& rightNode, bool16 rightNodeIsNew, bool16 recordAsLastMatch = kTrue) = 0;

		/** returns whether a match has been made during this round
		@return bool16 whether a match has been made during this round
		*/
		virtual bool16 MatchMade(void) const = 0;

		/** if MatchMade() is kTrue, return the match that was made for this round
		@return std::pair<XMLReference, XMLReference> the made made during this round
		*/
		virtual MatchRecord GetLastMatch(void) const = 0;

		/** for use by ContentHandlers. Use this method to find the corresponding element in the 
		document for the incoming elements
		@param leftNode incoming XML node
		@param rightNode [OUT] optionally receives the element in the document leftNode is 
		matched to
		@param rightNodeIsNew [OUT] optionally receives whether the right element is a new element
		@returns bool16 whether a match was found
		*/
		virtual bool16 FindMatch(IIDXMLDOMNode *leftNode, XMLReference *rightNode = nil, bool16 *rightNodeIsNew = nil) const = 0;

		/* the following are for internal use only */

		/** internal use only
		temporary method to lookup whether a right node has a match applied to it already. Later 
		when we have a way to determine this from the right tree iterator, this method should be 
		removed
		@param rightNode right tree node to lookup
		@param leftNode [OUT] optionally returns the element in the document that rightNode is 
		matched to
		note that it could be nil
		@param rightNodeIsNew [OUT] optionally receives whether the right element is a new element
		@return bool16 whether rightNode has a match applied alreaedy
		*/
		virtual bool16 FindMatchRight(const XMLReference& rightNode, IIDXMLDOMNode **leftNode = nil, bool16 *rightNodeIsNew = nil) const = 0;

		/** internal use only
		 replaces the a right tree node in the match recorder with a new one
		@param oldRightNode right tree node to be replaced
		@param newRightNode the new right tree node
		@param rightNodeIsNew indicates whether the right node is a new element in the document.
		If the element is an existing element or one that was cloned/duplicated from an existing 
		element, then the element/node is not new. If the element was created by, for example, 
		a XMLCreateElementCmd, or it was cloned/duplicated from a new element, then the element 
		is new
		NOTE: Passing kInvalidXMLReference for oldRightNode is not recommended because it could result in the wrong DOMNode getting replaced.
		Similarly, Passing kInvalidXMLReference for newRightNode is not recommended because it can result in incorect searches by FindMatchRight()
		*/
		virtual void ReplaceRightNode(const XMLReference& oldRightNode, const XMLReference& newRightNode, bool16 rightNodeIsNew) = 0;

		/** internal use only
		 call this method at the beginning of each round of match making process. A round is 
		defined as a single match
		@param matchMade initial value of match made for the new round
		*/
		virtual void PushMatchMade(bool16 matchMade = kFalse) = 0;

		/** internal use only
		 call this method at the end of each round of match making process */
		virtual bool16 PopMatchMade(void) = 0;

		/** internal use only
		 call this method at the beginning of each level of match making process. A level is 
		defined as a parent/child level
		*/
		virtual void PushLevel(void) = 0;

		/** internal use only
		 call this method at the end of each level of match making process. A level is 
		defined as a parent/child level
		*/
		virtual void PopLevel(void) = 0;
};

const IXMLImportMatchRecorder::MatchRecord kInvalidMatchRecord;


#endif //__IXMLImportMatchRecorder__

