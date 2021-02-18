//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IInkResourceData.h $
//  
//  Owner: jargast
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
//  Page items that have drawing resources should include this interface
//  
//========================================================================================

#pragma once
#ifndef __IInkResourceData__
#define __IInkResourceData__

#include "IPMUnknown.h"

class IInkList;
class IPrintData;

/**	Records the ink usage for different types of page items. This is the data interface
	that is passed through the GetUsedInks() method of IInkResources, to store off ink
	usage results.
	@see IInkResources
*/
class IInkResourceData : public IPMUnknown
{
public:
	/**	The creating code needs to call Setup with the current IInkList. If printing, pass
		the IPrintData for the second parameter, or nil otherwise.
		@param iInkList IN current IInkList being used
		@param iPrintData IN current IPrintData being used, or nil
	 */
	virtual void Setup (IInkList* iInkList, IPrintData* iPrintData) = 0;
	
	/**	Copy an existing ink resource data list into this list.
		@param srcData IN source ink resource data
	 */
	virtual void CopyInkResouceData (IInkResourceData* srcData) = 0;
	
	/**	Add a used ink.  The implementation of this interface guarantees that only
		one instance of an ink is stored. Implementations of this interface and
		users of this interface assume that the ink UID exists in the ink
		list that was passed into Setup.
		@param inkUIDRef IN the ink being used by the page item
	 */
	virtual void AddInk (UIDRef inkUIDRef) = 0;
					
	/**	Shortcut method for adding process Cyan.
	 */
	virtual void AddProcessCyan() = 0;
	/**	Shortcut method for adding process Magenta.
	 */
	virtual void AddProcessMagenta() = 0;
	/**	Shortcut method for adding process Yellow.
	 */
	virtual void AddProcessYellow() = 0;
	/**	Shortcut method for adding process Black.
	 */
	virtual void AddProcessBlack() = 0;
					
	/**	Performance improving method that tells clients if all process inks are already
		used.  If true, the client can skip adding it's resources as it already knows.
		they all exist.
		@return bool8 - kTrue if all process inks already registered as being used, kFalse otherwise
	 */
	virtual bool8 AllProcessInksUsed() const = 0;
	
	/**	Returns the ink list that the resource data is using.
		@return IInkList* - pointer to the IInkList being used
	 */
	virtual IInkList* QueryInkList() const = 0;
	
	/**	Returns the print data that the resource data is using.
		@return IPrintData* - pointer to the IPrintData being used - maybe nil
	 */
	virtual IPrintData* QueryPrintData() const = 0;
	
	/**	Retrieve the number of inks being used.
		@return int32 - the number of inks being used
	 */
	virtual int32 GetNumInks() const = 0;
	
	/**	Retrieve the UID of the Nth ink being used.
		@param n IN which ink to retrieve
		@return UID the UID of the Nth ink
	 */
	virtual UID GetNthInk (int32 n) const = 0;
	
	/**	Remove all entries from the list and remove the reference to the doc ink list.
	 */
	virtual void Clear() = 0;

	/**	Tells whether a gradient paint server is used in the pub - print code
		will not download the gradient paint server procset if this is false.
		@return bool8 kTrue if gradient used, kFalse otherwise
	 */
	virtual bool8 GetGradientUsed() const = 0;

	/**	Set whether a gradient paint server is used in the pub.
		@param bGradientUsed IN kTrue if gradient used, kFalse otherwise
	 */
	virtual void SetGradientUsed(const bool8 bGradientUsed) = 0;

	/**	Tells whether a gradient mesh paint server is used in the pub - print code
		will not download the gradient mesh paint server procset if this is false
		@return bool8 - kTrue if gradient mesh used, kFalse otherwise
	 */
	virtual bool8 GetGradientMeshUsed() const = 0;

	/**	Set whether a gradient mesh paint server is used in the pub
		@param bGradientUsed IN kTrue if gradient mesh used, kFalse otherwise
	 */
	virtual void SetGradientMeshUsed(const bool8 bGradientMeshUsed) = 0;

};

#endif
