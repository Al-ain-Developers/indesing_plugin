//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/IPnlTrvChangeOptionsCmdData.h $
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
//========================================================================================

#ifndef __IPnlTrvCHANGEOPTIONSCMDDATA__
#define __IPnlTrvCHANGEOPTIONSCMDDATA__

#include "PnlTrvID.h"


/** From SDK sample; data interface for PnlTrvChangeOptionsCmd, responsible 
for changing options for this plug-in.

	
	@ingroup paneltreeview
*/

class IPnlTrvChangeOptionsCmdData : public IPMUnknown
{
public:
	enum { kDefaultIID = IID_IPNLTRVCHANGEOPTIONSCMDDATA };

	/** Method to append option to list of options
		@param newVal [IN] new  value to append to option-list
	*/
	virtual void AddOption(const PMString& newVal)=0; 

	/** Accessor for stored option by index
		@param index [IN] specifies position of interest (zero-based)
		@return the option at this position
	*/
	virtual PMString GetNthOption(const int32 index)=0; 


	/**	Return count of options on this data interface
		@return int32 returned giving the number of options currently cached
	 */
	virtual int32 GetOptionCount()=0;

};


#endif // __IPnlTrvCHANGEOPTIONSCMDDATA__
