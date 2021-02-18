//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/XMLDTDValidateSuggest.h $
//  
//  Owner: Will Lin
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
//  Adobe Patent of Adobe Patent Pending Invention Included Within this File
//  
//========================================================================================

#pragma once
#ifndef __XMLDTDValidateSuggest__
#define __XMLDTDValidateSuggest__


//
// Adobe patent application tracking P563, entitled XML DTD Validation With 
// Suggestion For Fixing Validation Errors, inventors: Lin
//
/**	Base class for a suggestion in a XML DTD validation error. All XML DTD validation error 
	suggestion implementations must be based on this class. Suggestions may be added to a
	DTD validation error, presented to the user, and processed

	@see XMLDTDValidationError
*/
class PUBLIC_DECL XMLDTDValidateSuggest
{
	public:
		virtual ~XMLDTDValidateSuggest();

		/** make a copy of this
			@return XMLDTDValidateSuggest* a copy of this
		*/
		virtual XMLDTDValidateSuggest* Clone(void) const = 0;

		/** query the display string for this suggestion
			@return PMString display string for this. Caller owns the string
		*/
		virtual PMString *QueryDisplayString(void) const = 0;

		/** process command(s) that corresponds to this suggestion
			@return ErrorCode command error code from processing command(s)
		*/
		virtual ErrorCode Process(void) const = 0;
};


#endif // __XMLDTDValidateSuggest__

