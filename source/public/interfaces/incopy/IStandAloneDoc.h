//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/incopy/IStandAloneDoc.h $
//  
//  Owner: Kevin Van Wiel
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
#ifndef __IStandAloneDoc__
#define __IStandAloneDoc__

#include "IPMUnknown.h"
#include "InCopyCoreID.h"

/** 
	This interface is used to keep track of the types of InCopy documents. There are two classifications
	Standalone documents and non-standalone (or managed). Standalone documents are created in InCopy by
	selecting new from the file menu in InCopy. These documents have one auto generated story that has
	pages auto generated on an as needed basis (based on how much text is present like autoflow essentially).
	A standalone document also allows the user to edit/add/delete styles and colors. There are various other
	decisions that are made based on whether a document is standalone or not for the InCopy Bridge mostly.
	A managed document (or non-standalone) is a document that is formed by exporting a InCopy stories from
	InDesign. This type document may have multiple stories and frames are not auto created instead the geometry
	is static an the geometry information comes from the associated InDesign document. The user may not
	edit styles or colors in such a document by they may apply them.
*/
class IStandAloneDoc : public IPMUnknown
{
	public:
		//----------------------------------------------------------------------------------------
		//	Enumerations
		//----------------------------------------------------------------------------------------

		enum { kDefaultIID = IID_ISTANDALONEDOC };

		/**
			Allows a document to be marked as standalone. Note the document must meet the criteria above
			(see interface description) to be standalone.
			@param standAlone - kTrue to make the document behave as standalone
			@return none
		**/
		virtual void SetIsStandAloneDoc(bool16 standAlone) = 0;
		
		/**
			Lets the called determine if a document is standalone or managed
			@return kTrue if the document is standalone
		**/
		virtual bool16 IsStandAloneDoc() const = 0;

		/**
			Old way of hiding and showing the info column. Use SetColumnHiddenPrefCmdBoss instead the
			command will handle everthing correctly. This method will go away next release (5.x).
			@param showInfoColumn - show the info column or not
			@return none
		**/
		virtual void SetShowInfoColumn(bool16 showInfoColumn) = 0;
		
		/**
			Info column showing or not.
			@return kTrue showing else kFalse
		**/
		virtual bool16 GetShowInfoColumn() const = 0;

};

#endif	// __IStandAloneDoc__