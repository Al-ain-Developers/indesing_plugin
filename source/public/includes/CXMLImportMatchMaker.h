//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/CXMLImportMatchMaker.h $
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
//  
//  A default implementation of ISAXContentHandler.  This provides an empty implementation
//  of each method so that clients can only override those that they really care about.
//  
//========================================================================================

#pragma once
#ifndef __CXMLImportMatchMaker_h__
#define __CXMLImportMatchMaker_h__


#include "CPMUnknown.h"
#include "IXMLImportMatchMaker.h"
#include "IXMLImportMatchRecorder.h"


/**
An empty base class implementation of IXMLImportMatchMaker. Clients who wish 
to add a XML import match maker serevice provider should implement new classes 
derived from this class.

@see IXMLImportMatchMaker
*/
class PUBLIC_DECL CXMLImportMatchMaker : public CPMUnknown<IXMLImportMatchMaker>
{
public:
	CXMLImportMatchMaker(IPMUnknown *boss);
	virtual ~CXMLImportMatchMaker();
	
	/** Initializes some preferences. 
		Clients that implement this fuction should call the implementation in the base class. */
	virtual void Register(IPMUnknown *xmlImporter);
	virtual ErrorCode MatchDocument(const IDXMLDOMGraph& leftGraph, IXMLImportMatchRecorder *matchRecorder);
	virtual ErrorCode PostMatchDocument(const IDXMLDOMGraph& leftGraph, IXMLImportMatchRecorder *matchRecorder);
	virtual ErrorCode Match(const IDXMLDOMGraph& leftGraph, const IDXMLDOMStructureOnlyIterator& leftIter, const IDXMLDOMStructureOnlyIterator& leftIterEnd, const XMLReferenceGraph& rightGraph, const XMLOutEdgeIterator& rightIter, const XMLOutEdgeIterator& rightIterEnd, IXMLImportMatchRecorder *matchRecorder);
	virtual ErrorCode PostMatch(const IDXMLDOMGraph& leftGraph, const IDXMLDOMStructureOnlyIterator& leftIter, const IDXMLDOMStructureOnlyIterator& leftIterEnd, const XMLReferenceGraph& rightGraph, const XMLOutEdgeIterator& rightIter, const XMLOutEdgeIterator& rightIterEnd, IXMLImportMatchRecorder *matchRecorder);
	virtual ErrorCode NoMatchMade(const IDXMLDOMGraph& leftGraph, const IDXMLDOMStructureOnlyIterator& leftIter, const IDXMLDOMStructureOnlyIterator& leftIterEnd, const XMLReferenceGraph& rightGraph, const XMLOutEdgeIterator& rightIter, const XMLOutEdgeIterator& rightIterEnd, IXMLImportMatchRecorder *matchRecorder);
	virtual ErrorCode MatchPhaseComplete(const IDXMLDOMGraph& leftGraph, const XMLReferenceGraph& rightGraph, IXMLImportMatchRecorder *matchRecorder);
	virtual ErrorCode NoMatchMadeOnRoot(const IDXMLDOMGraph& leftGraph, const IDXMLDOMStructureOnlyIterator& leftIter, const IDXMLDOMStructureOnlyIterator& leftIterEnd, const XMLReference& importIntoXMLRef, XMLReference& elementToMatch);

protected:
    /** the type of the element */
    enum ElementType {
        kElementType_Normal = 0,        /** generic element */
        kElementType_Table,            /** table element */
        kElementType_TableGrid,        /** table row element -- for future expansion */
        kElementType_TableCell        /** table cell element */
    };

	enum CellType {		/** the order here is the same as they appear in a table */
		kUnknown = 0,
		kHeader,		/** a cell in a header row */
		kBody,			/** a cell in a body row */
		kFooter			/** a cell in a footer row */
	};

	/**	Get the UID of the node's tag. */
	ErrorCode GetTagUID(const IIDXMLDOMNode *leftNode, const UIDRef& tagList, UID& tagUID) const;

	/** Given an IIDXMLDOMNode, return its element type by by checking its attributes */
	ElementType GetElementType(const IIDXMLDOMNode *leftNode) const;

	/** Given an element, return its type */
	ElementType GetElementType(const IIDXMLElement *rightElement) const;

	/** Check if the left node's type matches rightElement. */
	bool16 MatchType(IIDXMLDOMNode *leftNode, IIDXMLElement* rightElement, IXMLImportMatchRecorder *matchRecorder) const;

	/** Given an element, return whether it is a new element created during this import session */
	bool16 IsElementNew(const IIDXMLElement *element, const IXMLImportMatchRecorder *matchRecorder) const;

	/* Check if the left node's children can be matched to a grid (when bCheckGrid is kTrue) or a cell (when bCheckGrid is kFalse). */
	bool16 CheckTableNode(IIDXMLDOMNode *node, bool16 bCheckGrid) const;

	/** Given an IIDXMLDOMNode, return its cell type by by checking its attributes 
	    The IIDXMLDOMNode must have ElementType kElementType_TableCell. */
	CellType GetCellType(const IIDXMLDOMNode *leftNode) const;

	/** Given a table cell element, get its type. */
	CellType GetCellType(const IIDXMLElement *rightElement) const;

	/** Import option "Import text elements into tables if tags match". Default is kTrue. 
		Initialized in Register(). */
	bool16 fMatchTextToTable;

	// Static member used to avoid initializing a WideString all over
	WideString fURI;
};

#endif	// __CXMLImportMatchMaker_h__


