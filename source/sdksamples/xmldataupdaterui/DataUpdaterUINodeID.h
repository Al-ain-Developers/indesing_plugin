//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xmldataupdaterui/DataUpdaterUINodeID.h $
//  
//  Owner: Adobe Developer Technologies
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
//  Each C++ implementation class in the plug-in and its corresponding ImplementationID
//  should be registered in this file.
//  
//========================================================================================

#ifndef __DataUpdaterUINodeID__
#define __DataUpdaterUINodeID__

#include "NodeID.h"
#include "IPMStream.h"
#include "DataUpdaterUIID.h"

/** Represents a node in the tree view. This could be a record name,
    field name or value of a field.
	
	@ingroup xmldataupdaterui
*/
class DataUpdaterUINodeID : public NodeIDClass
{
	public:
		enum { kNodeType = kDataUpdaterUITreeViewWidgetBoss }; 


		/**	Factory method to create 
		new object of this class
			@return   new instance of this class 
		 */
		static	NodeID_rv Create() { return new DataUpdaterUINodeID(); }

		/**	Factory method to create new object of this class
			@param path [IN] specifies initial path
			@return  new instance of this class
		 */
		static	NodeID_rv Create(PMString type, int32 index, PMString value)  
			{ return new DataUpdaterUINodeID(type, index, value); }

		/**	Destructor
		 */
		virtual ~DataUpdaterUINodeID() {}
		

		/**	@return type of this node
		 */
		virtual	NodeType GetNodeType() const { return kNodeType; } 

		/**	Comparator function
			@param NodeID [IN] specifies the node that we should compare against
			@return  Comparison results
		 */
		virtual int32 Compare(const NodeIDClass* NodeID) const;

		/**	Create a copy of this
			@return  
		 */
		virtual NodeIDClass* Clone() const;

		/**	Read this from the given stream
			@param stream [IN] specified stream
			@return  
		 */
		virtual void Read(IPMStream* stream);

		/**	Write this to the given stream
			@param [OUT] stream 
			@return  
		 */
		virtual void Write(IPMStream* stream) const;

		/**	Accessor for the value associated with this node
			@return const PMString& 
		 */
		const PMString& GetValue() const { return fValue; }

		/**	Accessor for the type associated with this node
			@return const PMString& 
		 */
		const PMString& GetType() const { return fType; }

		/**	Accessor for the with this node
			@return const PMString& 
		 */
		const int32 GetIndex() const { return fIndex; }

	private:
		// Note we're keeping the destructor private to force use of the factory methods
		DataUpdaterUINodeID(): fIndex(0) {}

		DataUpdaterUINodeID(PMString type, int32 index,  PMString value):fType(type),fIndex(index), fValue(value) {}

		PMString	fType;
		int32		fIndex;
		PMString	fValue;
};

#endif // __DataUpdaterUINodeID__


