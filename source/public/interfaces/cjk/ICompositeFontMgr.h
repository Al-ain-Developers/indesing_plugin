//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/cjk/ICompositeFontMgr.h $
//  
//  Owner: Kuniko Nagayama
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
#ifndef __ICompositeFontMgr__
#define __ICompositeFontMgr__

#include "IPMUnknown.h"
#include "IPMFont.h"
#include "IWorkspace.h"
#include "ICompositeFont.h"
#include "IDocFontMgr.h"

class PMString;

/** Manager for compsite fonts
*/
class ICompositeFontMgr	:	public IPMUnknown
{
	public:

		virtual void UpdateFonts(int32 oldSeed) = 0;

		virtual void GetCompositeFontFolder(IDFile* fileSpec) = 0;

		virtual PMString GetCompositeFontPath(IPMFont* font) = 0;

		// import composite fonts with kLoadCompFontCmdBoss
		/**
			Add to import list. Please use the one below with psname or documents cannot
			be recomposed correctly.
			@param	fontName - native family name of composite font that was imported
		*/
		virtual void AddImportList(const PMString& fontName) = 0;

		/**
			Add to import list.
			@param	fontName - native family name of composite font that was imported
			@param	psFontName - postscript name of composite font that was imported
		*/
		virtual void AddImportList(const PMString& fontName, PMString psFontName) = 0;
		virtual int32 GetImportListLength() const = 0;
		virtual PMString GetImportList(const int32 index) const = 0;
		virtual bool16 GetImportList(const PMString& fontName) const = 0;
		virtual void RemoveImportList(const PMString& fontName) = 0;
		virtual void ClearImportList() = 0;
		virtual const K2Vector<PMString>& GetImportPSNameList() const = 0;

		// data for a dialog in listing duplicate fonts
		/**
			AddCompFontOrgName
		
			@param	fontUID
			@param	fontName
		*/
		virtual void AddCompFontOrgName(UID fontUID, PMString& fontName) = 0;
		virtual void AddCompFontNewName(UID fontUID, PMString& fontName) = 0;

		virtual UID GetCompFontOrgName(int32 index, PMString& fontName) = 0;
		virtual UID GetCompFontNewName(int32 index, PMString& fontName) = 0;

		virtual int32 GetCompFontOrgNameLength() = 0;
		virtual int32 GetCompFontNewNameLength() = 0;

		virtual void ClearCompFontOrgNewName() = 0;

		/**
			Gets a default Roman name from installed fonts
		
			@return	PMString	postscript name of default Roman font
		*/
		virtual PMString GetDefaultRomanFontInstalled() = 0;

		/**
			Gets a default Japanese name from installed fonts
		
			@return	PMString	postscript name of default Japanese font
		*/
		virtual PMString GetDefaultJFontInstalled() = 0;

		virtual void SetDefaultCompositeFontInstalled (IDocFontMgr* docFontMgr, ICompositeFont* defaultData) = 0;

};

#endif

//__ICompositeFontMgr__
