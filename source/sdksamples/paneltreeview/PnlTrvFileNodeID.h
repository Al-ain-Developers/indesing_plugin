//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/PnlTrvFileNodeID.h $
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

#ifndef __PnlTrvFileNodeID__
#define __PnlTrvFileNodeID__

#include "NodeID.h"
#include "IPMStream.h"
#include "PnlTrvID.h"

/** Represents a node in some notional file system; this could be a platform file
	system, or a file within a repository such as Perforce.
	Overriding this class lets us populate the tree with our own data type that
	represents whatever we want on each node.

	
	@ingroup paneltreeview
*/
class PnlTrvFileNodeID : public NodeIDClass
{
	public:
		enum { kNodeType = kPnlTrvTreeViewWidgetBoss }; 


		/**	Factory method to create 
		new object of this class
			@return   new instance of this class 
		 */
		static	NodeID_rv Create() { return new PnlTrvFileNodeID(); }

		/**	Factory method to create new object of this class
			@param path [IN] specifies initial path
			@return  new instance of this class
		 */
		static	NodeID_rv Create(const PMString& path)  
			{ return new PnlTrvFileNodeID(path); }

		/**	Destructor
		 */
		virtual ~PnlTrvFileNodeID() {}
		
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

		/**	Accessor for the path associated with this node
			@return const PMString& 
		 */
		const PMString& GetPath() const { return fPath; }

		/** This is mostly a debug call so that TreeView asserts have more useful information
		*/
		virtual PMString GetDescription() const { return fPath; }

	private:
		// Note we're keeping the destructor private to force use of the factory methods
		PnlTrvFileNodeID() {}

		PnlTrvFileNodeID(PMString path):fPath(path) {}

		PMString	fPath;
};

#endif // __PnlTrvFileNodeID__


