//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPMInkBossData.h $
//  
//  Owner: SusanCL
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
#ifndef __IPMInkBossData__
#define __IPMInkBossData__

#include "ColorSystemID.h"
#include "IColorData.h"
#include "IPMUnknown.h"
#include "PMString.h"

class PMReal;
class IPMStream;

/**	A data interface for InDesign's ink objects. InDesign inks are kPMInkDataBoss objects.
	@see also IInkList.h.
*/
class IPMInkBossData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPMINKBOSSDATA };

		/** AGM trapping ink types
		*/
		enum {
			/** kAGMPrintTrapInkNormal indicates traditional process inks and most spot inks.
			*/
			kAGMPrintTrapInkNormal = 0,
			/** kAGMPrintTrapInkTransp indicates trapping for varnishes and die line inks
			*/
			kAGMPrintTrapInkTransp,
			/** kAGMPrintTrapInkOpaque indicates trapping for heavy, non-transparent inks, e.g., metallic inks.
			*/
			kAGMPrintTrapInkOpaque,
			/* kAGMPrintTrapInkOpaqueIgnore indicates trapping for inks that have undesirable interactions with other inks, usually heavy non-transp inks.
			*/
			kAGMPrintTrapInkOpaqueIgnore
		};
		
		/**	Returns the ink name.
		*/
		virtual const PMString& GetInkName() const = 0;
		/**	Returns true if ink is a process ink.
		*/
		virtual bool16 GetInkIsProcess() const = 0;
		/**	Returns true if ink is set to print.
		*/
		virtual bool16 GetInkPrintInk() const = 0;
		/**	Returns true if ink is set to overprint.
		*/
		virtual bool16 GetInkOverprintInk() const = 0;
		/**	Returns ink's overprint threshhold.
		*/
		virtual PMReal GetInkOverprintThold() const = 0;
		/**	Returns ink's neutral density.
		*/
		virtual PMReal GetInkNeutralDensity() const = 0;
		/**	Returns ink's trapping type.
		*/
		virtual uint32 GetInkAGMPrintInkTrapType() const = 0;
		/**	Returns ink's trapping order.
		*/
		virtual int32 GetInkTrapOrder() const = 0;
		/**	Returns true if overrideing PPD.
		*/
		virtual bool16 GetInkOverridePPD() const = 0;
		/**	Returns ink's frequency setting.
		*/
		virtual PMReal GetInkFrequency() const = 0;
		/**	Returns ink's angle setting.
		*/
		virtual PMReal GetInkAngle() const = 0;
		/**	Returns ink's RGB value representation.
		*/
		virtual const ColorArray& GetRGBValue() const = 0;
		/**	Returns ink's solidity setting.
		*/
		virtual PMReal GetInkSolidity() const = 0;
		/**	Returns true if spot ink is treated as process ink.
		*/
		virtual bool16 GetInkAsProcess() const = 0;
		/**	Returns the ink's ink alias UID.
		*/
		virtual UID GetInkAliasUID() const = 0;

		/**	Set the ink name.
			@param inkName specifies the ink name to set.
		*/
		virtual void SetInkName( const PMString& inkName ) = 0;
		/**	Set whether or not ink is a process ink.
			@param isProcess is true if ink is a process ink.
		*/
		virtual void SetInkIsProcess( bool16 isProcess ) = 0;
		/**	Set whether or not this ink should be printed.
			@param printInk is true if ink should be printed.
		*/
		virtual void SetInkPrintInk( bool16 printInk ) = 0;
		/**	Set whether or not should overprint ink.
			@param overprintInk is true if ink should be overprinted.
		*/
		virtual void SetInkOverprintInk( bool16 overprintInk ) = 0;
		/**	Set the ink's overprint threshhold.
			@param overprintThold is the overprint threshhold to set.
		*/
		virtual void SetInkOverprintThold( PMReal overprintThold ) = 0;
		/**	Set ink's neutral density.
			@param neutralDensity specifies the neutral density.
		*/
		virtual void SetInkNeutralDensity( PMReal neutralDensity ) = 0;
		/**	Set ink's trapping type.
			@param trapType specifies the trapping type.
		*/
		virtual void SetInkAGMPrintInkTrapType( uint32 trapType ) = 0;
		/**	Set ink's trapping order.
			@param trapOrder specifies the trapping order.
		*/
		virtual void SetInkTrapOrder( int32 trapOrder ) = 0;
		/**	Set whether or not ink should override PPD.
			@param overridePPD is true if to override PPD.
		*/
		virtual void SetInkOverridePPD( bool16 overridePPD ) = 0;
		/**	Set ink's frequency.
			@param frequency specifies the ink frequency.
		*/
		virtual void SetInkFrequency( PMReal frequency ) = 0;
		/**	Set ink's angle.
			@param angle specifies the angle.
		*/
		virtual void SetInkAngle( PMReal angle ) = 0;
		/**	Set the ink's RGB color representation.
			@param rgbValue specifies the RGB color values.
		*/
		virtual void SetRGBValue( const ColorArray& rgbValue ) = 0;
		/**	Set ink's solidity.
			@param solidity specifies the solidity.
		*/
		virtual void SetInkSolidity(PMReal solidity) = 0;
		/**	Set whether or not spot ink should be treated as process ink.
			@param asProcess is true if spot ink is treated as process ink.
		*/
		virtual void SetInkAsProcess(bool16 asProcess) = 0;
		/**	Set the ink's ink alias UID.
			@param inkAliasUID specifies the ink alias UID.
		*/
		virtual void SetInkAliasUID(UID inkAliasUID) = 0;

		/**	Copy the ink data.
			@param iSourceData specifies the source ink data to copy data from. 
		*/
		virtual void CopyInkData ( IPMInkBossData* iSourceData ) = 0;

};
#endif
