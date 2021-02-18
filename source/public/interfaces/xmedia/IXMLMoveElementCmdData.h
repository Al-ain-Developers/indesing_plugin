//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/xmedia/IXMLMoveElementCmdData.h $
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
#ifndef __IXMLMoveElementCmdData__
#define __IXMLMoveElementCmdData__

#include "IPMUnknown.h"
#include "XMLID.h"
#include "XMLReference.h"

/** Data interface for moving elements in the logical structure tree;
	use IXMLElementCommands methods to do this rather than processing
	low-level commands from client code.
*/
class IXMLMoveElementCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IXMLMOVEELEMENTCMDDATA };

	/**	Set up the data on this interface.
	Example; suppose that you have the following marked up content:
<pre>
	&lt;A&gt;zzzXzz&lt;B&gt;z&lt;/B&gt;zYz&lt;/A&gt;
</pre>
	to insert at the "X" position, newParentXMLRef = "A"; newIndexInParent = 0; contentOffset = 3
	to insert at the "Y" position, newParentXMLRef = "A"; newIndexInParent = 1; contentOffset = 1

	To get the new XMLReference of the moved element after the command has processed, do:
	<ol>
		<li>Instantiate the new parent element: 
		<pre>
	InterfacePtr&lt;IIDXMLElement&gt; newParentElement(Utils&lt;IXMLUtils&gt;()->Instantiate(newParentXMLRef));
		</pre>
		<li>Ask for the child at newIndexInParent: 
		<pre>
	XMLReference newXMLRef(newParentElement->GetNthChild(newIndexInParent));
		</pre>
	</ol>
		@param moveElementXMLRef XML element to move
		@param newParentXMLRef move the element to a child of this element
		@param newIndexInParent move the element to this child index under the new parent
		@param contentOffset insertion point in the content in front of the specified new index in parent
			use kInvalidTextIndex to specify the end of the content run
	 */
	virtual void Set(const XMLReference& moveElementXMLRef, const XMLReference& newParentXMLRef, int32 newIndexInParent, TextIndex contentOffset) = 0;

	/**	Acccessor for the element to be moved stored on this interface.
		<b>Note</b>: at the end of each of the command's Do/Undo/Redo operations, GetMoveElementXMLRef
		returns the updated XMLReference of the moved element at its current location

		@return XMLReference specifying element to be moved stored on this interface
	 */
	virtual const XMLReference& GetMoveElementXMLRef(void) const = 0;

	/**	Specify element to move
		@param xmlRef specifying element to move
	 */
	virtual void SetMoveElementXMLRef(const XMLReference& xmlRef) = 0;

	/**	Accessor for new parent element stored on this interface
		
		@return XMLReference of new parent stored on this
	 */
	virtual const XMLReference& GetNewParentXMLRef(void) const = 0;

	/**	Accessor for new index in parent stored on this
		
		@return int32 giving index in parent's list of nodes, stored on this interface
	 */
	virtual int32 GetNewIndexInParent(void) const = 0;

	/**	Accessor for content offset stored on this
		
		@return TextIndex stored on this interface
	 */
	virtual TextIndex GetContentOffset(void) const = 0;
};

#endif	// __IXMLMoveElementCmdData__

