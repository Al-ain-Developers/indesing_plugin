//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/snippetrunner/SnipRunNoStrip.cpp $
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

#include "VCPlugInHeaders.h"

#include "InterfaceFactory.h"
#include "SnpReferenceMacros.h"

extern bool16 gFalse;


/** DontDeadStrip
	references all implementations to stop the compiler dead stripping them from the executable image.
	
*/
void DontDeadStrip();

void DontDeadStrip()
{
	if (gFalse)
	{
#include "SnipRunFactoryList.h"	

	//+REFERENCE_SNIPPET() avoid Mac debug build stripping out snippets
	REFERENCE_SNIPPET(_SnpRunnerAddMediaFile);
	REFERENCE_SNIPPET(_SnpRunnerAccessTableContent);
	REFERENCE_SNIPPET(_SnpRunnerApplyTextStyleAttributes); 
	REFERENCE_SNIPPET(_SnpRunnerChooseFile); 
	REFERENCE_SNIPPET(_SnpRunnerCopyPasteTable);
	REFERENCE_SNIPPET(_SnpRunnerCreateCustomAnimation);
	REFERENCE_SNIPPET(_SnpRunnerCreateDocument); 
	REFERENCE_SNIPPET(_SnpRunnerCreateFrame); 
	REFERENCE_SNIPPET(_SnpRunnerCreateFrameGrid); 
	REFERENCE_SNIPPET(_SnpRunnerCreateInddPreview); 
	REFERENCE_SNIPPET(_SnpRunnerCreateTable); 	
	REFERENCE_SNIPPET(_SnpRunnerEstimateTextDepth); 
	REFERENCE_SNIPPET(_SnpRunnerExportBookAsPDF);
	REFERENCE_SNIPPET(_SnpRunnerFindAndReplace); 
	REFERENCE_SNIPPET(_SnpRunnerGetTableParcel); 
	REFERENCE_SNIPPET(_SnpRunnerHitTestFrame); 
	REFERENCE_SNIPPET(_SnpRunnerImportExportSnippet);	
	REFERENCE_SNIPPET(_SnpRunnerImportExportXML); 	
	REFERENCE_SNIPPET(_SnpRunnerInsertGlyph); 		
	REFERENCE_SNIPPET(_SnpRunnerInspectFontMgr); 
	REFERENCE_SNIPPET(_SnpRunnerInspectLayoutGrid); 
	REFERENCE_SNIPPET(_SnpRunnerInspectLayoutModel); 	
	REFERENCE_SNIPPET(_SnpRunnerInspectSelectionXMLProperties); 	
	REFERENCE_SNIPPET(_SnpRunnerInspectTableModel); 
	REFERENCE_SNIPPET(_SnpRunnerInspectTextModel); 	
	REFERENCE_SNIPPET(_SnpRunnerInspectTextStyles); 	
	REFERENCE_SNIPPET(_SnpRunnerInspectXMPMetaData);
	REFERENCE_SNIPPET(_SnpRunnerIterTableStories); 
	REFERENCE_SNIPPET(_SnpRunnerIterTableUseDictHier); 
	REFERENCE_SNIPPET(_SnpRunnerManipulateSwatch); 	
	REFERENCE_SNIPPET(_SnpRunnerManipulateAssignment); 
	REFERENCE_SNIPPET(_SnpRunnerManipulateConditionalText); 
	REFERENCE_SNIPPET(_SnpRunnerManipulateGraphicAttributes); 	
	REFERENCE_SNIPPET(_SnpRunnerManipulateInCopyCJKGridAttributes);
	REFERENCE_SNIPPET(_SnpRunnerManipulateInline); 
	REFERENCE_SNIPPET(_SnpRunnerManipulatePrintStyles);
	REFERENCE_SNIPPET(_SnpRunnerManipulateTrapStyles);
	REFERENCE_SNIPPET(_SnpRunnerManipulateStructureView); 	
	REFERENCE_SNIPPET(_SnpRunnerManipulateTextFrame); 	
	REFERENCE_SNIPPET(_SnpRunnerManipulateTextModel); 	
	REFERENCE_SNIPPET(_SnpRunnerManipulateTextOnPath); 
	REFERENCE_SNIPPET(_SnpRunnerManipulateTextStyle); 
	REFERENCE_SNIPPET(_SnpRunnerManipulateXMLElements); 	
	REFERENCE_SNIPPET(_SnpRunnerManipulateXMLSelection); 
	REFERENCE_SNIPPET(_SnpRunnerManipulateXMLTags);  
	REFERENCE_SNIPPET(_SnpRunnerModifyLayoutGrid); 	 
	REFERENCE_SNIPPET(_SnpRunnerModifyTable); 	
	REFERENCE_SNIPPET(_SnpRunnerPerformCompFont); 	
	REFERENCE_SNIPPET(_SnpRunnerPerformFontGroupIterator); 	
	REFERENCE_SNIPPET(_SnpRunnerPerformKinsokuTable); 	
	REFERENCE_SNIPPET(_SnpRunnerPerformNamedGrid); 
	REFERENCE_SNIPPET(_SnpRunnerPerformNoteFunction); 
	REFERENCE_SNIPPET(_SnpRunnerPerformTextAttrKenten); 
	REFERENCE_SNIPPET(_SnpRunnerPerformTextAttrLanguage); 
	REFERENCE_SNIPPET(_SnpRunnerPerformTextAttrRuby); 	
	REFERENCE_SNIPPET(_SnpRunnerPerformTextAttrTateChuYoko); 
	REFERENCE_SNIPPET(_SnpRunnerPerformTextAttrWarichu); 
	REFERENCE_SNIPPET(_SnpRunnerPerformXMPCommands); 
	REFERENCE_SNIPPET(_SnpRunnerPlaceFile); 	
	REFERENCE_SNIPPET(_SnpRunnerPrintDocument); 	
	REFERENCE_SNIPPET(_SnpRunnerProcessDocumentLayerCmds); 	
	REFERENCE_SNIPPET(_SnpRunnerSelectShape); 	
	REFERENCE_SNIPPET(_SnpRunnerSetTableFill); 	
	REFERENCE_SNIPPET(_SnpRunnerShowPalette); 	
	REFERENCE_SNIPPET(_SnpRunnerSortTable); 	
	REFERENCE_SNIPPET(_SnpRunnerTemplate); 
	REFERENCE_SNIPPET(_SnpRunnerXMLSampleHelper); 	
	REFERENCE_SNIPPET(_SnpRunnerManipulateTextFootnotes); 	
	REFERENCE_SNIPPET(_SnpRunnerShareAppResources);
	REFERENCE_SNIPPET(_SnpRunnerManipulateSpreadsAndPages);
	REFERENCE_SNIPPET(_SnpRunnerInspectPathInfo);
	REFERENCE_SNIPPET(_SnpRunnerManipulateDisplayPerformance);
	REFERENCE_SNIPPET(_SnpRunnerManipulatePathandGraphics);
	REFERENCE_SNIPPET(_SnpRunnerHyphenation);
	REFERENCE_SNIPPET(_SnpRunnerExportEPub);
	REFERENCE_SNIPPET(_SnpRunnerManipulateArticles);
    REFERENCE_SNIPPET(_SnpHelloCSXS);
    REFERENCE_SNIPPET(_SnpHelloBridgeTalk);
    REFERENCE_SNIPPET(_SnpCreateQRCode);
	//-REFERENCE_SNIPPET()
	}
}

//  Generated by Dolly build 17: template "IfPanelMenu".
// End, SnipRunNoStrip.cpp.




