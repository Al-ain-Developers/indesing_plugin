//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/persistentlist/IPstLstSuite.h $
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

#ifndef _IPstLstSuite_
#define _IPstLstSuite_

//	INCLUDES
#include "IPMUnknown.h"
#include "ShuksanID.h"
#include "PMRect.h"
#include "PstLstID.h"

class UIDList;

/**
	From SDK sample; interface to manipulate the IPstLstData of IPstLstUIDList on the current selection.

	@ingroup persistentlist
	
*/
class IPstLstSuite : public IPMUnknown
{
//	Data Types
public:
	enum { kDefaultIID = IID_IPSTLST_ISUITE };

	/** Stores customized persistent data; the UID as a string and the name. 
	 * 	@ingroup persistentlist
	 */
	struct PstLstDataDescription
	{
		public:
		typedef	object_type	data_type;
		/** UID as a string. */
		PMString	fUIDStr;
		/** Name. */
		PMString	fName;
	};

	/** K2Vector for PstLstDataDescription. 
	 * 	@ingroup persistentlist
	 */
	typedef K2Vector<PstLstDataDescription> PstLstDataVector;

//	Member functions
public:


	/**
		Check the number of a drawable page item selected, a drawable page item will have a IPstLstUIDList interface when the plug-in is loaded.
		So we will check if we can get a valid IPstLstUIDList InterfacePtr thru the selected items as the test to see if it is a
		drawable page item.
	*/
	virtual void	GetNumDrawablePageItemSelected(int32 &num)const =0;

	/**
		Get the nth selected drawable page item with a valid IPstLstUIDList Interface.
	*/
	virtual void	GetNthSelectedDrawablePageItem(int32 nth, UIDRef &item)const = 0;
};

#endif // _IPstLstSuite_
