//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/SBOSRefInstantiate.h $
//  
//  Owner: Jianlan Song
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

/**  This class is used by SBOSReference to instantiate a small boss object.
	SBOSRefInstantiate should not be instantiated.
	@See SBOSReference
*/

class PUBLIC_DECL SBOSRefInstantiate 
{
	public:
		/**	Given the base UIDRef and subItem of a SBOSReference,
			instantiate an SBOS element from the database.

			@param baseUIDRef - Base UIDRef of the SBOSReference.
			@param subItem - sub item of the SBOSReference.
			@return reference - Incremented interface ptr referenced.
		 */
		static IPMUnknown* Instantiate(UIDRef baseUIDRef, SBOSID subItem, PMIID iid);	

	private:
		/** We only declare the contructor as we don't want to instantiate the object.
		*/
		SBOSRefInstantiate();
};

