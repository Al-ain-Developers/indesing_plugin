//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/includes/architecture/UIDListUtils.h $
//  
//  Owner: Jeff Stone
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
	#ifndef _UIDLISTUTILS_
	#define _UIDLISTUTILS_
//================================================================================================
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________
	//.......Interface headers....................................................................
	#include "ICommand.h"

	//.......Other headers........................................................................
	#include "UIDList.h"
//________________________________________________________________________________________________
//	PREPROCESSOR DIRECTIVES
//________________________________________________________________________________________________
	#ifdef PUBLIC_BUILD
		#pragma export on
	#endif //PUBLIC_BUILD
//================================================================================================
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class PUBLIC_DECL UIDListUtils
	{
	public:
		//________________________________________________________________________________________
		//	DESCR:		**Deprecated** This was used to mimick the old behaviour of commands which
		//				consumed UIDList objects (i.e. the command became responsible for deleting
		//				the UIDList). Some code that was more difficult to update to the new 
		//				reference counted, letter/envelope pattern of UIDLists
		//________________________________________________________________________________________
		static void SetItemList_Deprecated (ICommand *iCommand, UIDList *uidList)
			{
			UIDList list (*uidList);
			delete uidList;
			iCommand->SetItemList (list);
			}
		
		//________________________________________________________________________________________
		//	DESCR:		Find the intersection of two UIDLists.
		//				if bool16 is kTrue, then check for invalid UIDs.
		//________________________________________________________________________________________
		static UIDList IntersectUIDLists (const UIDList& listOne, const UIDList& listTwo, bool16 = kTrue);

		//________________________________________________________________________________________
		//	DESCR:		Append the second list to the first one.
		//________________________________________________________________________________________
		static void AppendUIDLists (UIDList& listOne, const UIDList& listTwo);


		//________________________________________________________________________________________
		//	DESCR:		Remove any deleted items from the list.
		//________________________________________________________________________________________
		static void RemoveDeletedItems(UIDList& items);
	};


#ifdef PUBLIC_BUILD
	#pragma export off
#endif //PUBLIC_BUILD
 
#endif // _UIDLISTUTILS_