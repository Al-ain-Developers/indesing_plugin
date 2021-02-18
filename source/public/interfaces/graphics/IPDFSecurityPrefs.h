//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IPDFSecurityPrefs.h $
//  
//  Owner: Tommy Donovan
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
#ifndef __IPDFSECURITYPREFS__
#define __IPDFSECURITYPREFS__

#include "PDFID.h"
//
//  Forward declarations
//
class PMString;

/**
	Class IPDFSecurityPrefs

	Defines an interface for storing Acrobat security settings information.  This is modelled
	after the internal PDF representation of this information rather than its manifestation in 
	the UI.
*/
class IPDFSecurityPrefs : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IPDFSECURITYPREFS };
		
		virtual void CopyPrefs(IPDFSecurityPrefs const* prefsToCopy) = 0;

		virtual void SetUseSecurity(const bool16 useSecurity) = 0;
		virtual bool16 GetUseSecurity() const = 0;

		virtual bool16 HasSecuritySettings() const = 0;
		
		virtual void SetKeyLength(const int32 len) = 0;
		virtual int32 GetKeyLength() const = 0;
				
		/**
			Passwords
		*/
		virtual void SetUseMasterPassword(const bool16 useSecurity) = 0;
		virtual bool16 GetUseMasterPassword() const = 0;

		virtual void SetUseUserPassword(const bool16 useSecurity) = 0;
		virtual bool16 GetUseUserPassword() const = 0;

		virtual void SetOpenDocPassword(const PMString& openDocPass) = 0;
		virtual PMString GetOpenDocPassword() const = 0;

		virtual void SetChangeSettingsPassword(const PMString& changeSettingsPass) = 0;
		virtual PMString GetChangeSettingsPassword() const = 0;
		
		virtual bool16 GetConfirmMasterPassword() const = 0;
		virtual void SetConfirmMasterPassword( bool16 b ) = 0;

		virtual bool16 GetConfirmUserPassword() const = 0;
		virtual void SetConfirmUserPassword( bool16 b ) = 0;

		/**
			User access permissions from Table 3.15 of PDF 1.4 Reference Manual
		*/
		/**
			Bit 3
		*/
		virtual void SetDisallowPrinting(const bool16 disallowPrinting) = 0;
		virtual bool16 GetDisallowPrinting() const = 0;

		/**
			Bit 4
		*/
		virtual void SetDisallowChanging(const bool16 disallowChanging) = 0;
		virtual bool16 GetDisallowChanging() const = 0;

		/**
			Bit 5
		*/
		virtual void SetDisallowCopying(const bool16 disallowCopying) = 0;
		virtual bool16 GetDisallowCopying() const = 0;

		/**
			Bit 6
		*/
		virtual void SetDisallowChangingNotes(const bool16 disallowChangingNotes) = 0;
		virtual bool16 GetDisallowChangingNotes() const = 0;

		/**
			Bit 9
		*/
		virtual void SetDisallowFormFillIn(const bool16 disallowFormFillIn) = 0;
		virtual bool16 GetDisallowFormFillIn() const = 0;
		
		/**
			Bit 10
		*/
		virtual void SetDisallowExtractionForAccessibility(const bool16 disallowAccessibility) = 0;
		virtual bool16 GetDisallowExtractionForAccessibility() const = 0;
		
		/**
			Bit 11
		*/
		virtual void SetDisallowDocumentAssembly(const bool16 disallowAssembly) = 0;
		virtual bool16 GetDisallowDocumentAssembly() const = 0;
		
		/**
			Bit 12
		*/
		virtual void SetDisallowPrintHiRes(const bool16 disallowPrintHiRes) = 0;
		virtual bool16 GetDisallowPrintHiRes() const = 0;
		
		/**
			Bit 13
		*/
		virtual void SetDisallowPlaintextMetadata(const bool16 disallowPlaintextMetadata) = 0;
		virtual bool16 GetDisallowPlaintextMetadata() const = 0;

		/** Method to stream in/out the preferences. 
		@param iPMStream is the stream to read/write. 
		@param prop is the implementation ID. 
		*/ 
		virtual void ReadWrite (IPMStream* iPMStream, ImplementationID prop) = 0;
};

#endif // __IPDFSECURITYPREFS__
