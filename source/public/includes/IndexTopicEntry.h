//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/IndexTopicEntry.h $
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
//  comments: Data class to store one Index Topic entry (up to 4 Topic entry nodes).
//  
//========================================================================================

#pragma once
#ifndef __INDEXTOPICENTRY__
#define __INDEXTOPICENTRY__

#include "IndexingID.h"				// Needed for kIDXMaxTopicLevel
#include "IndexTopicEntryNode.h"

class UIDRef;

/** Models a topic entry which can have up to kIDXMaxTopicLevel topic nodes.
	@see IndexTopicEntryNode
*/
class IndexTopicEntry
{
	public:
		typedef object_type data_type;

		/** Constructs an empty topic entry.
		*/
		IndexTopicEntry():
			fNumNodes(0)
		{}

		/** Copy constructor.
			Copies the content of the specified topic entry.
			@param other [IN] - topic entry to be copied.
		*/
		IndexTopicEntry(const IndexTopicEntry& other)
		{
			fNumNodes = other.fNumNodes;
			for (int32 i = 0; i < kIDXMaxTopicLevel; i++)
				fNodes[i] = other.fNodes[i];
		};

		/** Equality test operator.
		*/
		bool16 operator==(const IndexTopicEntry& other) const
		{
			if (fNumNodes != other.fNumNodes)
				return kFalse;

			for (int32 i = 0; i < fNumNodes; i++)
				if (!(fNodes[i] == other.fNodes[i]))
					return kFalse;
			
			return kTrue;
		}

		/** Assignment operator.
		*/
		IndexTopicEntry& operator=(const IndexTopicEntry& other)
		{
			if (this != &other)
			{
				fNumNodes = other.fNumNodes;
				for (int32 i = 0; i < fNumNodes; i++)
					fNodes[i] = other.fNodes[i];
			}
			return *this;
		}
		
		/** Accessor for the number of topic nodes.
			@return the number of topics contained in this topic entry.
		*/
		const int16&		GetNumNodes() const { return fNumNodes;} ;

		/** Accessor for the number of topic nodes.
			@return a modifiable reference to the number of topics property.
		*/
		int16&				GetNumNodes() { return fNumNodes;} ;
		
		/** Accessor for a topic node.
			@param number [IN] - the index (level) of the topic node within this entry.
			@return a modifiable reference to the topic node at the specified index.
		*/
		IndexTopicEntryNode&		GetTopicEntryNode(int16 number) {return fNodes[number];};

		/** Accessor for a topic node.
			@param number [IN] - the index (level) of the topic node within this entry.
			@return the topic node at the specified index.
		*/
		const IndexTopicEntryNode&	GetTopicEntryNode(int16 number) const {return fNodes[number];}

protected:
		int16				fNumNodes;
		IndexTopicEntryNode	fNodes[kIDXMaxTopicLevel];	// the IndexTopicEntryNodes
};

#endif // __INDEXTOPICENTRY__