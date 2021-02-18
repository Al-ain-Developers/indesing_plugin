//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/ChecksumBossHelper.h $
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

#ifndef __ChecksumBossHelper__
#define __ChecksumBossHelper__

#ifdef DEBUG
#include "ChecksumUtils.h"
#include "IClassInfo.h"
#include "K2Vector.h"

class IPMPersist;
class IPMUnknown;

/*
	Helper class for calculating, storing, and comparing checksums for the
	serialized persistent interfaces of a boss. 

	The checksumming code is here to detect cases where an implementation has been changed
	in memory, but was not marked dirty. These bugs can cause pub corruption. The idea
	is that we checksum the implementation by streaming it out and calculating the 
	checksum after it is constructed, and again any time the dirty state is cleared.
	Then we can check the implementation anytime, and if it is not marked dirty, but the
	checksum has changed, we know we have a problem. Here's a list of the events we
	care about:
	- Implementation is constructed (and may have been read in from disk). Calculate
	initial checksum, and store it for future reference.
	- Implementation is marked as not dirty. This happens usually after a SaveDirty call,
	when the implementation has been flushed back to the document. Recalculate the baseline
	checksum, and store it for future reference.
	- Implementation is Release'd, and goes to 0 ref-count. It is now eligible for destruction
	if the memory is needed. This is a good time to check to make sure the dirty state is
	correct, since if it is wrong, and the object is destructed, it will not get written out
	first. Checking every time the ref-count goes to 0 is expensive, but is guaranteed to 
	catch errors that might otherwise appear sporatically.
	- Transaction is closed. This is a good time to check all the referenced implementations
	that are not already marked dirty. The mini-save thread can now fire, and if the objects 
	are dirty but not marked, then they won't get written out as part of the transaction.

	We checksum all persistent bosses, but *not* the non-persistent bosses, since they can't
	be dirtied. Exception is currently made for PMControllingUnknowns; this is because they
	are part of PublicLib and can't call into the object model. We need to fix this.
*/
class PUBLIC_DECL ChecksumBossHelper
{
public:
	ChecksumBossHelper(int32 interfaceCount);
	static void Terminate();

	void Resize(IControllingUnknown *boss, IClassInfo const* clsInfo);

	uint32 GetChecksum(int32 faceIndex) const
	{
		return fChecksumList[faceIndex];
	}
	
	void SetChecksum(int32 faceIndex, uint32 newChecksum)
	{
		fChecksumList[faceIndex] = newChecksum;
	}
		
	/** Calculates and returns the checksum for the specified implementation.
	*/
	uint32 CalcChecksum(IPMUnknown *instance, ImplementationID implID) const;
	
	/** Resets the checksum for the specified interface.
	*/
	void CalcAndStoreChecksum(IPMUnknown *instance, ImplementationID implID, int32 faceIndex)
	{
		SetChecksum(faceIndex, CalcChecksum(instance, implID));
	}
	
	void VerifyAllChecksums(IClassInfo const* clsInfo, const IControllingUnknown *const boss, const IPMPersist *persist) const;
	
private:
	typedef K2Vector<uint32> ChecksumList;
	ChecksumList fChecksumList;
};



#endif // DEBUG


#endif // __ChecksumBossHelper__
