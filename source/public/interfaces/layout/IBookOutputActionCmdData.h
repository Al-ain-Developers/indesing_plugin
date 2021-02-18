//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IBookOutputActionCmdData.h $
//  
//  Owner: DBerggren
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
#ifndef __IBookOutputActionCmdData__
#define __IBookOutputActionCmdData__

#include "BookID.h"
class UIDList;

/** Command data interface relating to commands to output books (kBookBoss).
	@ingroup layout_book
	@see kBookExportActionCmdBoss 
	@see kBookPrintActionCmdBoss 
*/
class IBookOutputActionCmdData : public IPMUnknown
{
	public:
		enum { kDefaultIID = IID_IBOOKOUTPUTACTIONCMDDATA };

		/**	All inclusive set method to initialize data members.
			@param sysFile IN the book file
			@param itemList IN UIDs of the pubs being output
			@param outputAll IN if kTrue, all pubs are output, itemList is ignored
		 */
		virtual void Set(IDFile& sysFile, UIDList* itemList, bool16 outputAll = kTrue) = 0;

		/** Return the book file.
		*/
		virtual IDFile GetBookFile() = 0;

		/**	Set the book file.
			@param BookFile IN the book file being output
		 */
		virtual void SetBookFile(const IDFile& BookFile) = 0;

		/** Return the UID list containing the pubs being output.
		*/
		virtual UIDList* GetUIDList() = 0;

		/**	Set the pub list of the pubs being output.
			@param uidList IN a list of pub UIDs to output
		 */
		virtual void SetUIDList(UIDList* uidList) = 0;
		
		/** Determine whether all pubs being output.
			@return bool16 kTrue if all pubs being output, kFalse otherwise
		*/
		virtual bool16 IsOutputAll() = 0;

		/** Output UI options. Options may be ORed together.
		*/
		typedef enum 
		{
			/** Don't suppress any UI.
			*/
			kSuppressNothing		= 0x0,
			/** Suppress progress bar.
			*/
			kSuppressOutputProgress	= 0x1,
			/** Suppress output warnings.
			*/
			kSuppressOutputWarnings	= 0x2,
			/** Suppress output dialog.
			*/
			kSuppressOutputDialog	= 0x4,
			/** Suppress all UI.
			*/
			kSuppressEverything		= 0xFF
		} OutputUIOptions;

		/**	Set method for the output UI options.
			@param uiOptions IN the desired UI options
		 */
		virtual void SetOutputUIOptions(const OutputUIOptions uiOptions) = 0;

		/** Get method for the output UI options.
			@return OutputUIOption enum value for current output UI option
		*/
		virtual OutputUIOptions GetOutputUIOptions() const = 0;
		
		/**	Set export destination file.
			@param sysFile IN the export destination file
			@param validFile IN kTrue if the file is valid, kFalse otherwise
		 */
		virtual void SetOutputFile(IDFile& sysFile, bool16 validFile = kFalse) = 0;

		/** Get the export destination file.
			@param isValidOutputFile OUT kTrue if the output file is valid, kFalse otherwise
			@return IDFile of the output file
		*/
		virtual IDFile GetOutputFile(bool16& isValidOutputFile) = 0;
		
		/**	Set the book export provider class ID. 
			Set to kInvalidClass to use the default book export provider.
			@param classID IN the export book provider classID
		 */
		virtual void SetExportProviderClassID(const ClassID& classID) = 0;

		/** Get the export provider class ID.
			@return ClassID of the output export provider, may be kInvalidClass if not set
		*/
		virtual ClassID GetExportProviderClassID() const = 0;

		/**	Set the preset for PDF export. 
			Set to kInvalidUIDRef to use the default PDF preset.
			@param styleRef IN the preset for PDF Export
		 */
		virtual void SetPDFStyleRef(const UIDRef& styleRef) = 0;
		
		/** Get the preset for PDF export.
			@return preset for PDF export, may be kInvalidUIDRef if not set
		*/
		virtual UIDRef GetPDFStyleRef() const = 0;

};

#endif //__IBookOutputActionCmdData__