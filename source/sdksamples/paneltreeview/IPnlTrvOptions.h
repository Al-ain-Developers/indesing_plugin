//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/paneltreeview/IPnlTrvOptions.h $
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

#ifndef __IPnlTrvOptions_H_DEFINED__
#define __IPnlTrvOptions_H_DEFINED__
#include "PnlTrvID.h"


/** From SDK sample; persistent interface added in to the session workspace, holding options
	for this plug-in.

	
	@ingroup paneltreeview
*/

class IPnlTrvOptions : public IPMUnknown
{
public:

	enum { kDefaultIID = IID_IPNLTRVOPTIONS };

	/** Append an option to the persistent list. If the index you specify is outwith the length, then it'll get appended to the list
		@param newVal [IN] new value to add to existing list of options
		@param indexWhere [IN] where you want it in the list of options, zero based
	*/
	virtual void AddOption(
		const WideString& newVal, const int32 indexWhere)=0; 

	/**	Return option at given index in list
		@param index [IN] zero-based index
		@return PMString giving option at specified position
	 */
	virtual WideString GetNthOption(const int32 index) =0; 

	/** Retrieves current list of options as clone
		@param outList OUT contains copy of list of options
	*/
	virtual void GetOptionListCopy(K2Vector<WideString>& outList)=0;
};

#endif // __IPnlTrvOptions_H_DEFINED__


