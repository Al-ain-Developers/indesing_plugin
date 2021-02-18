//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/xdocbookworkflow/XDocBkScriptingDefs.h $
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

#ifndef __XDocBkScriptingDefs_h__
#define __XDocBkScriptingDefs_h__

// Object ScriptIDs
#define c_XDocBkPref 'cxdb'

// Property IDs
enum BscMEScriptProperties
{
	p_XDocPref = 'pxdp',
	p_XDocSetOption = 'pstp',
	p_XDocUseImportIt = 'piit',
	p_XDocUseXMLTsf = 'psxt',
	p_XDocUseCALSContentHndl = 'ptsh',
	p_XDocSuppliedXSLOverridingPI = 'pspi'
};

// {1AE3D6FA-8CBE-4ae9-9796-2489CE77A427}
#define kXDocBkPref_CLSID {0x1ae3d6fa, 0x8cbe, 0x4ae9, {0x97, 0x96, 0x24, 0x89, 0xce, 0x77, 0xa4, 0x27} }

#endif //__XDocBkScriptingDefs_h__