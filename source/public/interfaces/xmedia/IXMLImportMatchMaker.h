//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLImportMatchMaker.h $
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
#ifndef __IXMLImportMatchMaker__
#define __IXMLImportMatchMaker__


#include "IDXMLDOMGraph.h"
#include "XMLID.h"
#include "XMLReferenceGraph.h"


class IXMLImportMatchRecorder;

/** class for providing XML import match making service (kXMLImportMatchMakerSignalService) */
class IXMLImportMatchMaker : public IPMUnknown
{
	public:
		enum	{ kDefaultIID = IID_IXMLIMPORTMATCHMAKER };

		/** this method is called by the XMLImporter before the service is used (i.e. before the 
		first of a series of Match() calls). This is where data about the XMLImporter handling 
		the import is passed to the service providers
		@param xmlImporter XMLImporter handling the import. It may contain additional data about 
		the import
		*/
		virtual void Register(IPMUnknown *xmlImporter) = 0;

		/** this is the first match call. It asks the match maker to match the incoming XML's 
		document node to a XMLReference in the existing document. Use the match recorder to 
		indicate whether the match was handled
		@param leftGraph graph of incoming XML
		@param matchRecorder MatchRecorder. If the service decides to make a match, it must make 
		appropriate calls in this functor class. Do not call the match recording method of this 
		data if the service decides to not handle the match. @see XMLImportMatchRecorder
		@return ErrorCode
		*/
		virtual ErrorCode MatchDocument(const IDXMLDOMGraph& leftGraph, IXMLImportMatchRecorder *matchRecorder) = 0;

		/** this is called after MatchDocument(). It is a notification for document element match
		@param leftGraph graph of incoming XML
		@param matchRecorder MatchRecorder. If the service decides to make a match, it must make 
		appropriate calls in this functor class. Do not call the match recording method of this 
		data if the service decides to not handle the match. @see XMLImportMatchRecorder
		@return ErrorCode
		*/
		virtual ErrorCode PostMatchDocument(const IDXMLDOMGraph& leftGraph, IXMLImportMatchRecorder *matchRecorder) = 0;

		/** called for kXMLImportMatchMakerSignalService to perform a match service
		@param leftGraph graph of incoming XML
		@param leftIter left tree iterator
		@param leftIterEnd left tree end iterator
		@param rightGraph graph of existing XML
		@param rightIter right tree iterator
		@param rightIterEnd right tree end iterator
		@param matchRecorder MatchRecorder. If the service decides to make a match, it must make 
		appropriate calls in this functor class. Do not call the match recording method of this 
		data if the service decides to not handle the match. @see XMLImportMatchRecorder
		@return ErrorCode
		*/
		virtual ErrorCode Match(const IDXMLDOMGraph& leftGraph, const IDXMLDOMStructureOnlyIterator& leftIter, const IDXMLDOMStructureOnlyIterator& leftIterEnd, const XMLReferenceGraph& rightGraph, const XMLOutEdgeIterator& rightIter, const XMLOutEdgeIterator& rightIterEnd, IXMLImportMatchRecorder *matchRecorder) = 0;

		/** called as part of kXMLImportMatchMakerSignalService after a match as been performed
		@param leftGraph graph of incoming XML
		@param leftIter left tree iterator
		@param leftIterEnd left tree end iterator
		@param rightGraph graph of existing XML
		@param rightIter right tree iterator
		@param rightIterEnd right tree end iterator
		@return ErrorCode
		*/
		virtual ErrorCode PostMatch(const IDXMLDOMGraph& leftGraph, const IDXMLDOMStructureOnlyIterator& leftIter, const IDXMLDOMStructureOnlyIterator& leftIterEnd, const XMLReferenceGraph& rightGraph, const XMLOutEdgeIterator& rightIter, const XMLOutEdgeIterator& rightIterEnd, IXMLImportMatchRecorder *matchRecorder) = 0;

		/** called by the default match maker. This is called after all match makers have been 
		called, including the default match maker, and none of the services made a match. The 
		default match maker is about to insert a new element and make a match to it. The match 
		maker service being called is allow to make a last attempt at making a match. If still 
		no match is made, then the default match maker will insert a new element
		@param leftGraph graph of incoming XML
		@param leftIter left tree iterator
		@param leftIterEnd left tree end iterator
		@param rightGraph graph of existing XML
		@param rightIter right tree iterator
		@param rightIterEnd right tree end iterator
		@return ErrorCode
		*/
		virtual ErrorCode NoMatchMade(const IDXMLDOMGraph& leftGraph, const IDXMLDOMStructureOnlyIterator& leftIter, const IDXMLDOMStructureOnlyIterator& leftIterEnd, const XMLReferenceGraph& rightGraph, const XMLOutEdgeIterator& rightIter, const XMLOutEdgeIterator& rightIterEnd, IXMLImportMatchRecorder *matchRecorder) = 0;

		/** called at the end of the entire match making phase
		@param leftGraph graph of incoming XML
		@param leftIter left tree iterator
		@param leftIterEnd left tree end iterator
		@param rightGraph graph of existing XML
		@param rightIter right tree iterator
		@param rightIterEnd right tree end iterator
		@return ErrorCode
		*/
		virtual ErrorCode MatchPhaseComplete(const IDXMLDOMGraph& leftGraph, const XMLReferenceGraph& rightGraph, IXMLImportMatchRecorder *matchRecorder) = 0;

		/** called by the default match maker. This is called after all match makers have been 
		called, including the default match maker, and none of the services made a match on the
		incoming root node. The default match maker is about to insert a new element and make a
		match to it. The match maker service being called is allowed to make a last attempt at making
		a match. If still no match is made, then the default match maker will insert a new element
		@param leftGraph graph of incoming XML
		@param leftIter left tree iterator
		@param leftIterEnd left tree end iterator
		@param importIntoXMLRef the element to import into
		@param elementToMatch returns the created element that the incoming root element should match to
		@return ErrorCode
		*/
		virtual ErrorCode NoMatchMadeOnRoot(const IDXMLDOMGraph& leftGraph, const IDXMLDOMStructureOnlyIterator& leftIter, const IDXMLDOMStructureOnlyIterator& leftIterEnd, const XMLReference& importIntoXMLRef, XMLReference& elementToMatch) = 0;
};


#endif	// __IXMLImportMatchMaker__

