//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/preflight/IPreflightResultNodeInfo.h $
//  
//  Owner: Matt Phillips
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
#include "IPMUnknown.h"
#include "PackageAndPreflightID.h"
#include "IPreflightResultNodeInfo.h"

/** Encapsulates information about a node in the aggregated results tree. This tree is 
	built dynamically from the preflight process database via a combination of the engine 
	and the intelligence in each rule.

	@see IPreflightAggregatedResults which manages the tree as a whole, including hierarchy.

	The node info, as you can see, is read-only. That's because it represents ONLY the 
	information that is required by the UI and reporting mechanisms; there's no provision
	for the user setting any of this stuff. If you're only looking to consume this data
	then the method comments below should give you what you need to know.

	If you're implementing a rule then you'll need to be able to generate one of these.
	There are two ways to do this. 
	
	In the vast majority of cases you'll use IPreflightAggregatedResultsUtils :: 
	CreateResultNodeInfo() or one of the other utility methods that do some additional 
	configuration (eg CreateGenericNode()). These methods create a kPreflightResultNodeBoss 
	which has on it the IPreflightResultNodeData interface. That contains all the setters.
	Its IPreflightResultNodeInfo implementation defers to the data interface for everything,
	and for go-to support it uses the object model (relying on the object ID in the data
	interface).

	@see IPreflightResultNodeData which is typically used as the backing store for the Info.

	If, however, your node needs specific behaviors, such as special go-to support that is
	not properly handled by the object model, you can create your own IPreflightResultNodeInfo.
	There is no requirement that the IPreflightResultNodeData be on the same boss (but you
	might still want to use it for the functions it already provides).
*/

class IPreflightResultNodeInfo : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPREFLIGHTRESULTNODEINFO };

	typedef enum 
	{
		/** General invalid/none state. */
		kInvalid,

		/** Used for non-functional nodes. Root and generic headings are this sort. */
		kGeneric,

		/** Used for a criteria or rule node, ie something that groups together violations. */
		kCriteria,

		/** This is used for special purposes and actually will probably go away.. */
		kStatus,

		/** A rule result (violation). These can be single or aggregated violations.
			What's critical is that there are actions associated with these nodes -- selection,
			fixup, descriptions, information, and so on. */
		kViolation

	} NodeType;

public:

	/** Get the node type.
		@return The type of this node.
	*/
	virtual NodeType GetType() const = 0;

	/** Get the short name, ie the name that would appear in a tree view widget row.
		@return The name.
	*/
	virtual PMString GetName() const = 0;

	/** Get the information string, ie the long-form string that would appear in a larger static
		box such as the information pane in the tree view widget. This is usually just a concatenated
		form of the description pairs.

		@see GetDescriptionPairs

		@return The description, or an empty string if there is none.
	*/
	virtual PMString GetDescription() const = 0;

	/** Helper class used by GetDescriptionPairs.
	*/
	class DescriptionPair
	{
	public:
		DescriptionPair(const PMString& sLabel, const PMString& sValue) : fLabel(sLabel), fValue(sValue) {}
		typedef object_type data_type;
		PMString fLabel;
		PMString fValue;
	};

	/** Convenience declaration.
	*/
	typedef K2Vector<DescriptionPair> DescriptionPairVector;

	/** Deeper dive into descriptions. Sometimes a giant string isn't so useful and requires
		(error-prone) parsing in order to format nicely in a report or UI. This method provides
		the individual strings that make up the larger description string.

		@param pairs OUT Receives a vector of description pairs
	*/
	virtual void GetDescriptionPairs(DescriptionPairVector& pairs) const = 0;

	/** Get the sorting string. This determines the sort order compared to others at the same
		hierarchy level.

		@return A string that is used for sorting purposes.
	*/
	virtual PMString GetSortValue() const = 0;

	/** Get a unique string -- a hash, basically -- which uniquely identifies the node apart from
		all others in a given results set. Typically this is built using the rule ID, object ID hash,
		etc. This is used to support mapping of results between invalidations in the UI since the
		IPreflightResultNode::NodeID can vary.

		@return A unique identifier string.
	*/
	virtual WideString GetUniqueString() const = 0;

	typedef enum
	{
		/** No go-to support. Nothing showable or selectable. Eg document transparency blend space. */
		kSupportsNothing,

		/** Can show something to you but you can't select it. Eg a master page item on a document page. */
		kSupportsShow,

		/** Can select something but can't scroll to it. Fairly unusual, but for example might be a
			swatch in the swatch palette; or a setting in a palette somewhere.
		*/
		kSupportsSelect,
		
		/** Can show it and select it. This is the most common. Example is a page item. */
		kSupportsShowAndSelect,

		/** Normally could show it to you, but the item for some reason can't be shown or selected.
			For example, the object is on a hidden layer.
		*/
		kCantShowRightNow

	} GoToSupport;

	/** Return the type of go-to support the node offers.
		@param OUT If not nil, receives a (optional) string indicating why it can't be selected.
			This string can be used in, say, a tool tip, or alert.
		@return The type of go-to support the node offers.
	*/
	virtual GoToSupport GetGoToSupport(PMString* pFailStr = nil) const = 0;

	/** Go to the node. You can assume that the document is opened and the frontmost window
		is the window in which any scrolling should occur.
	*/
	virtual bool DoGoTo() const = 0;

	/** Get the page number string on which the item occurs. (This method may be modified somewhat.)
		Empty string indicates there is no corresponding page number (eg a swatch).
	*/
	virtual PMString GetPageNumber() const = 0;
};

