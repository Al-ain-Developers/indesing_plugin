//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/interfaces/graphics/IExportStyleCmdData.h $
//  
//  Owner: Ed Bomke
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
#ifndef __IExportStyleCmdData__
#define __IExportStyleCmdData__

#include "IPMUnknown.h"
#include "PMString.h"

/** General command data interface for different style commands, such as
	set style name, add style, edit style and delete style. Used for 
	Document styles, PDF styles, Printer styles and Flattener styles.
*/
class IExportStyleCmdData : public IPMUnknown
{
	public:
		/**	Set the style index to operate on.
			@param index IN the style index
		 */
		virtual void SetStyleIndex(int32 index) = 0;
		/** Get the style index.
		*/
		virtual int32 GetStyleIndex() const = 0;
		
		/**	Holds string that can be used for setting a new style name.
			@param newName IN the name to store
		 */
		virtual void SetNewName(const PMString &newName) = 0;
		/** Get the string to use for a new style name.
		*/
		virtual PMString GetNewName() const = 0;
		
		/** Set the source list to use.
			@param srcListRef IN a UIDRef that is used to instaniate the style list manager
		*/
		virtual void SetSrcList(UIDRef srcListRef) = 0;
		/** Get the UIDRef for the source list to use.
			@return UIDRef to use to instaniate the style list manager
		*/
		virtual UIDRef GetSrcList() const = 0;

		/** Set the destination list to use.
			@param dstListRef IN a UIDRef that is used to instaniate the style list manager
		*/
		virtual void SetDstList(UIDRef dstListRef) = 0;
		/** Get the UIDRef for the destination list to use.
			@return UIDRef to use to instaniate the style list manager
		*/
		virtual UIDRef GetDstList() const = 0;
		
		/** Get whether this is an import of styles or not.
			@return bool16 kTrue if importing, kFalse otherwise
		*/
		virtual bool16 IsImport() const = 0;
		/** Set whether this is an import of styles.
			@param f IN kTrue if import of styles, kFalse otherwise
		*/
		virtual void SetIsImport( bool16 f ) = 0;
	
		/** Set whether operation was successful or not.
			@param successful IN kTrue if operation was successful, kFalse otherwise
		*/
   		virtual void SetSuccess(bool32 successful) = 0;
		/** Get whether operation was successful.
			@return bool32 kTrue if operation was successful, kFalse otherwise
		*/
   		virtual bool32 GetSuccess() = 0;

		/** Set the list manager interface IID
		@param interfaceid IN  interface id of the list manager to use
		*/
		virtual void SetListMgrIID(PMIID interfaceid) = 0;

		/** Get the list manager interface IID
		@return interfaceid  interface id of the list manager to use
		*/
		virtual PMIID GetListMgrIID() const = 0;
};

#endif
