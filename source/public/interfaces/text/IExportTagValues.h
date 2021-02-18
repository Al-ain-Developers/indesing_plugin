//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/text/IExportTagValues.h $
//  
//  Owner: Margie Vogel
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
#ifndef __IExportTagValues__
#define __IExportTagValues__

#include "IPMUnknown.h"
#include "TextID.h"


/**
	ExportTagData. Used in IExportTagValues.
	
	@see GetTagData
	@see SetTagData
*/
class ExportTagData
{
public:
	bool operator==(const ExportTagData& other) const { 
	   return (tagName == other.tagName	&& className == other.className && attributes == other.attributes); 
	}

	/** Tag name. i.e. "H1" */
	WideString tagName;
	/** Class name. For epub this is usually the paragraph style name. */
	WideString className;
	/** Attributes. For epub this can be style overrides or attributes that indesign doesn't have. */
	WideString attributes;
	 
};


/**
	The IExportTagValues interface stores a persistent, list of tags and values. It is used to store the tags
	to use for exporting EPUB and PDF
 	@ingroup text_style
*/
class IExportTagValues : public IPMUnknown
{
public:
		enum { kDefaultIID = IID_IEXPORTTAGVALUES };

		/**	Get the tag data for export type.
			@param exportType		type of export to get tag data for. i.e. L"PDF", L"EPUB"
			@return ExportTagData	tag data
		 */
		virtual ExportTagData GetTagData(const WideString& exportType) const = 0;

		/**	Set the tag data for export type. Setting to ExportTagData() will remove the entry.
			@param exportType		type of export to get tag data for. i.e. L"PDF", L"EPUB"
			@param tagData			tag data
		 */
		virtual void SetTagData(const WideString& exportType, const ExportTagData &tagData) = 0;

		/**	Get the number of export types.
			@return size_t		number of export types
		 */
		virtual size_t GetNumberOfExportTypes() const = 0;

		/**	Get the nth export type.
			@param nthType			index to type of export
			@return WideString		export type. i.e. L"PDF", L"EPUB"
		 */
		virtual WideString GetNthExportType(size_t nthType) const = 0;

		/**	Get break html file in EPUB at style. Only meaningful for paragraph style.
			@return bool16 kTrue if break HTML file at style. Value defaults to kFalse.
		 */
		virtual bool16 GetBreakHTMLFileInEPUB() const = 0;

		/**	Set break html file in EPUB at style.
			@param breakFile		kTrue to break HTML file at style.
		 */
		virtual void SetBreakHTMLFileInEPUB(bool16 breakFile) = 0;

		/**	Get the status of 'emit CSS for this style'.
			@return kTrue if CSS should be emitted for this style, kFalse otherwise. Default is kTrue.
		 */
		virtual bool16 GetEmitCSSForStyle() const = 0;

		/**	Set 'emit CSS' for this style.
			@param emitCSS		kTrue to emit CSS for this style, kFalse otherwise.
		 */
		virtual void SetEmitCSSForStyle(bool16 emitCSS) = 0;

		/**	Get the status of 'include class' for this style.
		@return kTrue if class should be included for this style, kFalse otherwise. Default is kTrue.
		*/
		virtual bool16 GetIncludeClassInHTML() const = 0;

		/**	Set 'include class' for this style.
		@param includeClass		kTrue to include class for this style, kFalse otherwise.
		*/
		virtual void SetIncludeClassInHTML(bool16 includeClass) = 0;


};

#endif
