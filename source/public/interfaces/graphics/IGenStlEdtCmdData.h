//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IGenStlEdtCmdData.h $
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
#ifndef __IGenStlEdtCmdData__
#define __IGenStlEdtCmdData__

#include "IPMUnknown.h"
#include "K2Vector.h"
#include "GenericSettingsID.h"

class IDFile;

class IGenStlEdtCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IGENSTLEDTCMDDATA };

		// Sets/gets the IID of the list mgr to use.
		virtual PMIID	GetListMgrIID() const = 0;
		virtual void	SetListMgrIID(PMIID iid) = 0;
	
		// Sets/gets the list of indices to which the command applies.
		// NOTE: If the list is empty, the command applies to ALL styles.
		// Currently this is only used on Export.
		virtual void	GetStyleIndexList(K2Vector<int32>& list) const = 0;
		virtual void	SetStyleIndexList(const K2Vector<int32>& list) = 0;
		
		// Specifies the import or export file.  If theFile is an empty string,
		//  the command will prompt the user for the file.
		virtual const IDFile* GetTargetFile() const = 0;
		virtual void	SetTargetFile(const IDFile* theFile) = 0;
};

#endif
