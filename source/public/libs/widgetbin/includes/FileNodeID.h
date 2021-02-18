//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/libs/widgetbin/includes/FileNodeID.h $
//  
//  Owner: Peter Boctor
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

#ifndef __FILENODEID__
#define __FILENODEID__

#include "NodeID.h"
#include "IPMStream.h"
#include "widgetid.h"

class WIDGET_DECL FileNodeID : public NodeIDClass
{
	public:
		enum { kNodeType = kFileNodeID }; 

		static	NodeID_rv		Create() { return new FileNodeID(); }
		static	NodeID_rv		Create(const PMString& pathListString) { return new FileNodeID(pathListString); }

		virtual ~FileNodeID() {}
		
		virtual	NodeType		GetNodeType() const { return kNodeType; } 
		virtual int32			Compare(const NodeIDClass* NodeID) const;
		virtual NodeIDClass*	Clone() const;
		virtual void			Read(IPMStream*	stream);
		virtual void			Write(IPMStream* stream) const;
		
		const PMString& GetPathItemsString() const { return fPathListString;}

		// This is mostly a debug call so that TreeView asserts have more context information
		virtual PMString		GetDescription() const { return fPathListString; };

private:
		FileNodeID() {}
		FileNodeID( const PMString& pathListString ) : fPathListString( pathListString ) {}

		PMString	fPathListString;
};

#endif
