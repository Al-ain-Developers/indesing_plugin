//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/architecture/IPathOperationSuite.h $
//  
//  Owner: Shengliu Dai
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
#ifndef _IPathOperationSuite_
#define _IPathOperationSuite_

/** IPathOperationSuite interface

	Provide a suite for operations on paths of selected objects
  */

class IPathOperationSuite : public IPMUnknown
	{
	public:
		enum { kDefaultIID = IID_IPATHOPERATIONSUITE };

	public:

		/**	Can MakeCompoundPath?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanMakeCompoundPath (void) const = 0;	

		/**	Can IntersectPath?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanIntersectPath (void) const = 0;	

		/**	Can UnionPath?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanUnionPath (void) const = 0;	

		/**	Can DifferencePath?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanDifferencePath (void) const = 0;	

		/**	Can ReverseDiffPath?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanReverseDiffPath (void) const = 0;	

		/**	Can XorPath?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanXorPath (void) const = 0;	

		/**	Can ReleaseCompoundPath?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanReleaseCompoundPath (void) const = 0;
		
		/**	Can ReversePath?
			@param none
			@return bool16 
		 */
		virtual bool16 	CanReversePath (void) const = 0;
		
		/**	Can End Path Drawing? (get out of spline creation state)
			@param none
			@return bool16 
		 */
		virtual bool16 	CanEndPathDrawing (void) const = 0;	

		/**	MakeCompoundPath
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	MakeCompoundPath (void) = 0;

		/**	IntersectPath
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	IntersectPath (void) = 0;

		/**	UnionPath
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	UnionPath (void) = 0;


		/**	DifferencePath
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	DifferencePath (void) = 0;

		/**	ReverseDiffPath
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	ReverseDiffPath (void) = 0;

		/**	XorPath
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	XorPath (void) = 0;


		/**	ReleaseCompoundPath
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	ReleaseCompoundPath (void) = 0;

		/**	ReversePath
			@param void 
			@return Success or Failure 
		 */
		virtual ErrorCode	ReversePath (void) = 0;

		/** End Path Drawing (get out of spline creation state)
			@param none
			@return bool16 
		 */
		virtual ErrorCode 	EndPathDrawing (void) = 0;	
	};

#endif // _IPathOperationSuite_