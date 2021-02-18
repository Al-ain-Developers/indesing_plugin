//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/PMControllingUnknown.h $
//  
//  Owner: Robin_Briggs
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
#ifndef __PMControllingUnknown__
#define __PMControllingUnknown__


#include "MultiControllingUnknown.h"
#ifdef DEBUG
#include "ChecksumBossHelper.h"
#endif

/**	PMControllingUnknown is for bosses which may or may not be persistent.
	It is table-driven; it keeps the multiple interfaces of the boss in a table.
*/
class PUBLIC_DECL PMControllingUnknown : public MultiControllingUnknown
{
public:
	PMControllingUnknown(const ClassID theClass);
	PMControllingUnknown(IClassInfo const *theClass);

	virtual IPMUnknown *QueryInterface(PMIID interfaceID) const;
	virtual void LastRelease() const;
			
	const IPMPersist *GetPersist() const;
	// for pmpersist, DebugControllingUnknown

#ifdef DEBUG
	virtual void SetChecksum(IPMUnknown *face, uint32 newChecksum);
	virtual void SetChecksum(int32 faceIndex, uint32 newChecksum);
	virtual uint32 GetChecksum(int32 faceIndex)const;
protected:
	ChecksumBossHelper fChecksumHelper;
#endif
};

#endif // __PMControllingUnknown__
