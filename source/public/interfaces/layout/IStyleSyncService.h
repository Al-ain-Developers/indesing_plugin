//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/layout/IStyleSyncService.h $
//  
//  Owner: Yeming Liu
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
#ifndef __ISTYLESYNCSERVICE__
#define __ISTYLESYNCSERVICE__

#include "StyleClashResolutionTypes.h"

class IDocument;

/**
   This interface is used to provide information of styles that are registered as 
   synchronizable and do the actual synchronization(adding/modifying styles) by 
   comparing the source/target documents.
 */

class IStyleSyncService : public IPMUnknown
{
	public:

		/**
			Get the interface ID of style.
			
			@return PMIID interface ID of style.
		*/

		virtual PMIID GetStyleInterfaceID() = 0;

		/**
			Get the group name that the style belongs to. For Roman version, there is only one group("All Styles");
			for J version, we have two groups("All Styles" and "CJK Styles").
			
			@return PMString the group name.
		*/

		virtual PMString GetGroupName() = 0;

		/**
			Get the registered synchronizable style name.
			
			@return PMString the style name(e.g., TOC Style, Paragraph Style, Character Style etc.)
		*/

		virtual PMString GetStyleName() = 0;

		/**
			Check if this is a CJK style or not.
			
			@return bool16 kTrue is CJK style, kFalse is NOT CJK style.
		*/

		virtual bool16 IsCJKStyle() = 0;

		/**
			Do the actual synchronization, e.g., copy/modify the styles from source document to target document.
			@param sourceFile refers to the master document(also called style source) of the book.
			@param target refers to the document whose styles may be modified or new styles may be added into.
			@return void.
		*/

		virtual void DoSynchronization(IDFile sourceFile, IDocument* target) = 0;

		/**
			Check if this option is turned on or off by default.
			
			@return bool16 kTrue if it is turned on, otherwise return kFalse.
		*/

		virtual bool16 IsOptionOnByDefault() = 0;

		/**	Sets the Style matching Strategy, This choice is not on per style type basis. If set then this will
		be used for all the style types for that load style command. 
			@note This value will be only used if the global clash resolution strategy is 
				StyleClashResolutionTypes::kLoadAllWithOverwrite or Individual styles resolve strategy is 
				StyleClashResolutionStrategy::kUseIncomingStyleDefinition. In all other cases style's full path 
				will be used for matching the styles in target.
		@param styleMatchingStrategy [IN] To find the clashing style in target, Uses full path of style if kMatchStyleFullPath is passed
			if kMatchStyleName is passed then matches style with the same name at any location if the style
			is unique in target. if same name style exist in more then one location then falls back to matching
			styles path.
		*/
		virtual void	SetStyleMatchingStrategy(StyleClashResolutionTypes::StyleMatchingStrategyEnum styleMatchingStrategy) = 0;

		/** Return the style matching method. 
		@return the style matching method set via SetStyleMatchingMethod.
		*/
		virtual StyleClashResolutionTypes::StyleMatchingStrategyEnum		GetStyleMatchingStrategy () const = 0;
};

#endif //__ISTYLESYNCSERVICE__