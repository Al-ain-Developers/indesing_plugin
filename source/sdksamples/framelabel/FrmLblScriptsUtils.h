//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/framelabel/FrmLblScriptsUtils.h $
//  
//  Owner: Adobe Developer Technologies
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
#ifndef __FrmLblParameterUtils__
#define __FrmLblParameterUtils__

#include "FrmLblType.h"

class IDocument;

/** FrmLblScriptsUtils is a class of static functions that manipulate common script operation.
    It is provided for convenience and ease of use.

*/

class FrmLblScriptsUtils 
{
	public:

		 /** Put Script FrameLabel info.
            @param frmLblInfo the FrameLabel properties. 
            @param propID identifies the ID of the property to handle.
			@param data identifies an interface pointer used to extract data.
			@param script identifies an interface pointer on the script object representing the parent of the application object.           
        */
		static ErrorCode PutScriptFrmLblInfo(FrmLblInfo& frmLblInfo, const ScriptID& propID, IScriptRequestData* data, IScript* script) ;

		 /** Get Script FrameLabel info.
            @param doc the current opened document or application default document. 
            @param frmLblInfo the FrameLabel properties. 
            @param propID identifies the ID of the property to handle.
			@param data identifies an interface pointer used to extract data.
			@param script identifies an interface pointer on the script object representing the parent of the application object. 
		*/
		static void GetScriptFrmLblInfo(IDocument* doc, FrmLblInfo& frmLblInfo, const ScriptID& propID, IScriptRequestData* data, IScript* script) ;

	private:
		
		 /** Get FrameLabel Position.
            @param frmLblInfo the FrameLabel properties. 
            @param propID identifies the ID of the property to handle.
			@param data identifies an interface pointer used to extract data.
		*/
		static ErrorCode GetPosition(FrmLblPosition& position, const ScriptID& scriptID, IScriptRequestData* data) ;	

		/** Private Constructor.
		*/
		FrmLblScriptsUtils(){};
	
};

#endif	// __FrmLblScriptsUtils__
