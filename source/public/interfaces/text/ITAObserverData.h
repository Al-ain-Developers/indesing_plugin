//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/ITAObserverData.h $
//  
//  Owner: Bernd Paradies
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
#ifndef __ITAObserverData__
#define __ITAObserverData__

#include "IPMUnknown.h"
#include "ShuksanID.h"		// for IUNKNOWN
#include "TextPanelID.h"

//----------------------------------------------------------------------------------------
// Class ITAObserverData
//----------------------------------------------------------------------------------------

/** 
	@ingroup text_targserv
*/
struct TAObserverDataStruct
{
		PMIID				fControlID;
		ClassID				fAttrClass;
		PMIID				fAttrID;
		ClassID				fStrandID;
		PMReal				fMin;
		PMReal				fMax;
		PMReal				fToUIFactor;
		bool16				fReset;
		ClassID				fRadioClass;
		bool16				fUseMeasurement;
		bool16				fReadOnly;
		bool16				fSupportUnknownValues;
		
		inline	TAObserverDataStruct() :
					fControlID( IID_IUNKNOWN ),
					fAttrClass( kInvalidClass ),
					fAttrID( IID_IUNKNOWN ),
					fStrandID( kInvalidClass ),
					fMin(0.0), fMax(0.0), fToUIFactor(1.0),
					fReset( kTrue ),
					fRadioClass( kInvalidClass ),
					fUseMeasurement( kFalse ),
					fReadOnly( kFalse ),
					fSupportUnknownValues( kFalse )
				{ }
};


/** 
	@ingroup text_targserv
*/
class ITAObserverData : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_ITEXTATTROBSERVERDATA };

		/**	
			Sets control ID for observer data.

			@param nID		Control ID to set to.
		 */
		virtual	void	SetControlID( const PMIID& nID ) = 0;
		/**	
			Gets control ID in observer data.

			@return PMIID	Control ID in observer data.
		 */
		virtual	PMIID 	GetControlID() const = 0;

		/**	
			Sets attribute class ID for observer data.

			@param nClass		Attribute class ID to set to.
		 */
		virtual	void	SetAttrClass( const ClassID &nClass ) = 0;
		/**	
			Gets attribute class ID in observer data.

			@return ClassID	Attribute class ID in observer data.
		 */
		virtual	ClassID	GetAttrClass() const = 0;

		/**	
			Sets attribute ID for observer data.

			@param nID		Attribute ID to set to.
		 */
		virtual	void	SetAttrID( const PMIID& nID ) = 0;
		/**	
			Gets attribute ID in observer data.

			@return PMIID	Attribute ID in observer data.
		 */
		virtual	PMIID	GetAttrID() const = 0;

		/**	
			Sets strand class ID for observer data.

			@param nID		Strand class ID to set to.
		 */
		virtual	void	SetStrandID( const ClassID &nID ) = 0;
		/**	
			Gets strand class ID in observer data.

			@return ClassID	Strand class ID in observer data.
		 */
		virtual	ClassID	GetStrandID() const = 0;

		/**	
			Sets minimum value for observer data.

			@param nMin		minimum value to set to.
		 */
		virtual	void	SetMinValue( PMReal nMin ) = 0;
		/**	
			Gets minimum value in observer data.

			@return PMReal	Minimum value in observer data.
		 */
		virtual	PMReal	GetMinValue() const = 0;

		/**	
			Sets maximum value for observer data.

			@param nMax		Maximum value to set to.
		 */
		virtual	void	SetMaxValue( PMReal nMax ) = 0;
		/**	
			Gets maximum value in observer data.

			@return PMReal	Maximum value in observer data.
		 */
		virtual	PMReal	GetMaxValue() const = 0;

		/**	
			Sets "To UI Factor" for observer data.

			@param nMax		"To UI Factor" to set to.
		 */
		virtual	void	SetToUIFactor( PMReal nMax ) = 0;
		/**	
			Gets "To UI Factor" in observer data.

			@return PMReal	"To UI Factor" in observer data.
		 */
		virtual	PMReal	GetToUIFactor() const = 0;

		/**	
			Sets observer data.

			@param rData		Observer data to set to.
		 */
		virtual	void	SetData( const TAObserverDataStruct &rData ) = 0;
		
		/**	
			Sets reset flag in observer data.

			@param bOn		kTrue to turn on rest in observer data.
		 */
		virtual void	SetReset( bool16 bOn ) = 0;
		/**	
			Returns reset flag in observer data.

			@return bool16	kTrue if reset is turned on, kFalse otherwise.
		 */
		virtual bool16	IsReset() const = 0;

		/**	
			Sets use measurement flga in observer data.

			@param bUseMeasurement		kTrue to turn on use measurement in observer data.
		 */
		virtual	void	SetUseMeasurement( bool16 bUseMeasurement ) = 0;
		/**	
			Returns use measurement flag in observer data.

			@return bool16	kTrue if use measurement is turned on, kFalse otherwise.
		 */
		virtual	bool16	UseMeasurement() const = 0;

		/**	
			Sets read only flag in observer data.

			@param bReadOnly		kTrue to turn on read only flag in observer data.
		 */
		virtual void	SetReadOnly( bool16 bReadOnly ) = 0;
		/**	
			Returns read only flag in observer data.

			@return bool16	kTrue if read only flag is  on, kFalse otherwise.
		 */
		virtual bool16	IsReadOnly() const = 0;

		/**	
			Sets support unknown values flag in observer data.

			@param bSupportsUnknownValues		kTrue to turn on support unknown values flag in observer data.
		 */
		virtual void	SetSupportUnknownValues( bool16 bSupportsUnknownValues ) = 0;
		/**	
			Returns support unknown values flag in observer data.

			@return bool16	kTrue if support unknown values flag is  on, kFalse otherwise.
		 */
		virtual bool16	DoesSupportUnknownValues() const = 0;
};

#endif
