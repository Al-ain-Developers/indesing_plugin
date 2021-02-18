//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IIDXMLDOMNList.h $
//  
//  Owner: Lonnie Millett
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

#ifndef __IIDXMLDOMNList_h__
#define __IIDXMLDOMNList_h__

class ISAXServices;
class IIDXMLDOMNode;

// Forward declare this in the proper namespace
namespace BIB_NAMESPACE {
	class CAXENListDOM;
}

/**
The IIDXMLDOMNList (DOM NodeList) object provides the
abstraction of an ordered collection of nodes.

The items in the node list are accessible via an
index, starting from 0.

Node lists are "live", in that any changes to the document
tree are immediately reflected in any IIDXMLDOMNLists that may
have been created for that tree.

<b>WARNING:</b>
Because node lists are "live",
the following is a very common error that should be avoided:
<pre>
// Move children from this node to another
IIDXMLDOMNList *nl = parent.getChildNodes();
unsigned int length = nl.getLength();
IIDXMLDOMNList *kid;
for (unsigned int i = 0; i < length; ++i) {
    kid = nl.item(i);
	if (kid)
		parent->RemoveChild(kid); //This changes length of nl!
}
</pre>
The index 'i' will exceed the modified length of the list,
which will result in 'kid' being invalid.</p>

<b>Invalid Parameters</b>

Unless otherwise indicated, it is an error to use an invalid
container (IsValid() == false), or a NULL pointer, as a
parameter to any function. In some instances, the requirement
that a specific parameter must be valid is repeated in the
commentary for the specific function. The lack of any
indication in the commentary for the specific function should
still be taken to mean that an invalid container or NULL
pointer will result in an error.
*/
class IIDXMLDOMNList
{
public:

	IIDXMLDOMNList(const BIB_NAMESPACE::CAXENListDOM& /*nodeListDOM*/) {}
	virtual ~IIDXMLDOMNList() {}

    /**
    Get number of nodes in list

    The range of valid child node indices is 0 to length-1
    inclusive.

    @return                     Number of nodes
    */
	virtual int32 Length() const = 0;

    /**
    Get a node by index

    If 'which' is greater than or equal to the number of nodes in
    the list, returns nil.

    @param which                Index into the list, starting
                                with 0.

    @return                     Returns the specified node. If node
								cannot be found because 'which' < 0
								or >= Length nil will be returned.
    */
	virtual IIDXMLDOMNode *GetNthNode(int32 which) = 0;
};

#endif