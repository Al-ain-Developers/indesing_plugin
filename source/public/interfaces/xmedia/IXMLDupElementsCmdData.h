//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLDupElementsCmdData.h $
//  
//  Owner: Daniel Guenther
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
#ifndef __IXMLDupElementsCmdData__
#define __IXMLDupElementsCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
class XMLReference;

/**  Data interface used by command for duplicating XML elements.
	If the target range is set up, it will be used to determine where the elements
	are to be duplicated to, else they will be duplicated in place.
	Descendants of the nodes being duplicated will be added in to the processing; it
	is the sub-tree descending from a given node that is duplicated, for each node.
*/
class IXMLDupElementsCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IXMLDUPELEMENTSCMDDATA };

		/**	SetSource() must be called at least once, and can be called as many times as needed to set 
			up source XML nodes to duplicate.
			@param sourceXMLRef specifies element to add to list of nodes to duplicate
		 */
		virtual void SetSource(const XMLReference& sourceXMLRef) = 0;

		/**	Specify a destination node in the structure tree to be parent to newly created duplicate items.
			The behaviour of the command  if no destination is specified
			is to duplicate each item added in SetSource() with a destination equal to the end of that source, as
			a sibling element.
			@param destXMLRef new parent for duplicated nodes
			@param destIndex specify an index in the list of children, or e.g. IIDXMLElement::kEndIndex to add as last child
		 */
		virtual void SetDestination(const XMLReference& destXMLRef, int32 destIndex) = 0;		

		/**	Accessor for destination node that is to be new parent for duplicated nodes
			@return XMLReference for destination node stored on this interface
		 */
		virtual const XMLReference& GetDestinationXMLRef(void) const = 0;

		/**	Accessor for entries in the list of source nodes to be duplicated stored on this interface, by index in the list
			@param index zero-based index, specifying position of interest for a source node, 0 < index < SourceSize()
			@return XMLReference for source node at specified index in list of nodes to be duplicated
		 */
		virtual const XMLReference& GetSourceXMLRef(int32 index) const = 0;

		/**	Accessor for the position in the list of children of the destination node where the duplicated nodes are heading, stored on this interface
			@return int32 index in parent of duplicated node(s) 
		 */
		virtual int32 GetDestinationIndex() = 0;

		/**	Accessor for the number of nodes in the source list, i.e. indicates how many times SetSource was called with
			distinct XMLReference's on this.
			
			@return int32 giving number of nodes in source list
		 */
		virtual int32 SourceSize() = 0;

		/**	Specify the list of duplicated elements.  Used by the command when duplication is complete to post the results.
			
			@param duplicatedElements the list of newly duplicated elements
		 */
		virtual void 							SetCreatedElements(const K2Vector<XMLReference>& duplicatedElements) = 0;
		
		/**	Accessor for newly duplicated elements.
			
			@return a list of duplicated elements
		 */
		virtual const K2Vector<XMLReference>&	GetCreatedElements() = 0;		
};


#endif  // __IXMLDupElementsCmdData__