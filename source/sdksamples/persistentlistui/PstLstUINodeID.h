//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlistui/PstLstUINodeID.h $
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

#ifndef __PstLstUINodeID__
#define __PstLstUINodeID__

#include "NodeID.h"
#include "IPMStream.h"
#include "PstLstUIID.h"

/** Represents a node in the tree view. It is the list item.
	
	@ingroup wlistboxcomposite
*/
class PstLstUINodeID : public NodeIDClass
{
	public:
		enum { kNodeType = kPstLstUITreeViewWidgetBoss }; 

		enum {
				kInvalidData = -1,
				kPageItemType = 0,
				kPersistentListType = 1,
			};

		/**	Factory method to create new object of this class
			@param path [IN] specifies initial path
			@return  new instance of this class
		 */
		static	NodeID_rv Create(int32 dataType, UID uid, PMString description)  
			{ return new PstLstUINodeID(dataType, uid, description); }

		/**	Destructor
		 */
		virtual ~PstLstUINodeID() {}
		

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
		const int32& GetDataType() const { return fDataType; }
		/**	Accessor for the value associated with this node
			@return const PMString& 
		 */
		const UID& GetUID() const { return fUID; }
		/**	Accessor for the value associated with this node
			@return const PMString& 
		 */
		const PMString& GetDataDescription() const { return fDataDescription; }


	private:
		// Note we're keeping the destructor private to force use of the factory methods
		PstLstUINodeID() {}

		PstLstUINodeID(int32 dataType, UID uid, PMString description):fDataType(dataType),fUID(uid), fDataDescription(description) {}

		int32	fDataType;
		UID	fUID;
		PMString	fDataDescription;
};

#endif // __PstLstUINodeID__


