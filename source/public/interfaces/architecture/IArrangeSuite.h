//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IArrangeSuite.h $
//  
//  Owner: Ryan Gano
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
//  Note:
//  
//========================================================================================

#pragma once
	#ifndef _IArrangeSuite_
	#define _IArrangeSuite_
//________________________________________________________________________________________________
//	INCLUDES
//________________________________________________________________________________________________

//================================================================================================
//________________________________________________________________________________________________
//	CLASS DECLARATION
//________________________________________________________________________________________________
class IArrangeSuite : public IPMUnknown
	{
	//____________________________________________________________________________________________
	//	Data Types
	//____________________________________________________________________________________________
	public:
		enum { kDefaultIID = IID_IARRANGESUITE };

	//____________________________________________________________________________________________
	//	Member functions
	//____________________________________________________________________________________________
	public:
		/**	Can any of the CSBs bring to front?
			@param none
			@return bool16 - kTrue == Yes, kFalse == No
		 */
		virtual bool16 CanBringToFront		(void) const = 0;	

		/**	Can any of the CSBs bring forward?
			@param none
			@return bool16 - kTrue == Yes, kFalse == No
		 */
		virtual bool16 CanBringForward		(void) const = 0;	

		/**	Can any of the CSBs send backward?
			@param none
			@return bool16 - kTrue == Yes, kFalse == No
		 */
		virtual bool16 CanSendBackward		(void) const = 0;	

		/**	Can any of the CSBs send to back?
			@param none
			@return bool16 - kTrue == Yes, kFalse == No
		 */
		virtual bool16 CanSendToBack		(void) const = 0;	

		/**	Bring the current selection to the front of the selection order
			@param none
			@return ErrorCode - Success/Failure
		 */
		virtual ErrorCode ProcessBringToFront () = 0;

		/**	Bring the current selection forward in the selection order
			@param none
			@return ErrorCode - Success/Failure
		 */
		virtual ErrorCode ProcessBringForward () = 0;

		/**	Send the current selection backward in the selection order
			@param none
			@return ErrorCode - Success/Failure
		 */
		virtual ErrorCode ProcessSendBackward () = 0;

		/**	Send the current selection to the back of the selection order
			@param none
			@return ErrorCode - Success/Failure
		 */
		virtual ErrorCode ProcessSendToBack () = 0;
			
	};

#endif // _IArrangeSuite_