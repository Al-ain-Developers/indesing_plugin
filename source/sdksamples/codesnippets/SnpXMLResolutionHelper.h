//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/codesnippets/SnpXMLResolutionHelper.h $
//  
//  Owner:	Ian Paterson
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

#ifndef __SnpXMLResolutionHelper_H_DEFINED__
#define __SnpXMLResolutionHelper_H_DEFINED__
#include <map>


/** Supports resolution of identifiers to symbolic form in
	both debug and release build.

	The list of symbols is compiled into the code here for use in release build,
	created by Perl script run over the SDK.

	
	@ingroup sdk_snippet

*/
class SnpXMLResolutionHelper
{

public:

	/**	Constructor.
	 */
	SnpXMLResolutionHelper();

	/**	Destructor. 
	 */
	virtual ~SnpXMLResolutionHelper();


	/**	Acquire a symbolic name from an ActionID
		@param id from ActionID.Get()
		@return PMString containing symbolic name of action
	 */
	PMString ResolveAction(ActionID id);

	/**	Acquire symbolic name from ClassID
		@param id  from ClassID.Get()
		@return PMString containing symbolic name of boss class
	 */
	PMString ResolveClass(ClassID id);

	/**	Acquire symbolic name from ImplementationID
		@param id from ImplementationID.Get()
		@return PMString containing symbolic name of the implementation 
	 */
	PMString ResolveImplementation(PMIID id);
};

#endif // __SnpXMLResolutionHelper_H_DEFINED__
