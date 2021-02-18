//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/footnoteendnoteconversion/includes/FootnoteToEndnoteStrings-en_US.jsx $
//  
//  Owner: 
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

var footnoteToEndnotelocale = 'en';		// this is also the fallback for all English locales

//------------------------------------------------------------------------------
// General strings
//------------------------------------------------------------------------------
footnoteToEndnoteStrings.DIALOGHEADER[footnoteToEndnotelocale] = "Convert Footnotes and Endnotes";
footnoteToEndnoteStrings.SCOPELABEL[footnoteToEndnotelocale] = "&Scope: ";
footnoteToEndnoteStrings.SEARCH_DOCUMENT_ITEM[footnoteToEndnotelocale] = "Document";
footnoteToEndnoteStrings.SEARCH_STORY_ITEM[footnoteToEndnotelocale] = "Selection";
footnoteToEndnoteStrings.CONVERT_BUTTON_TEXT[footnoteToEndnotelocale] = "C&onvert";
footnoteToEndnoteStrings.DONE_BUTTON_TEXT[footnoteToEndnotelocale] = "&Done";

footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE_ACTION_NAME[footnoteToEndnotelocale] = "Convert Footnotes and Endnotes...";
footnoteToEndnoteStrings.INDESIGN[footnoteToEndnotelocale] = "Adobe InDesign";

footnoteToEndnoteStrings.CONVERSION[footnoteToEndnotelocale] = "Co&nvert: ";
footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE[footnoteToEndnotelocale] = "Footnotes to Endnotes";
footnoteToEndnoteStrings.ENDNOTE_TO_FOOTNOTE[footnoteToEndnotelocale] = "Endnotes to Footnotes";
footnoteToEndnoteStrings.CONVERT_TO_FOOTNOTE[footnoteToEndnotelocale] = "Convert to Footnote";
footnoteToEndnoteStrings.CONVERT_TO_ENDNOTE[footnoteToEndnotelocale] = "Convert to Endnote";



footnoteToEndnoteStrings.MAIN_MENU_LOCATION[footnoteToEndnotelocale] = "Document Endnote Options...";
footnoteToEndnoteStrings.CONTEXT_MENU_LOCATION[footnoteToEndnotelocale] = "Insert Variable";
footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTE[footnoteToEndnotelocale] = "Convert Selected Endnote to Footnote";
footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTES[footnoteToEndnotelocale] = "Convert Selected Endnotes to Footnotes";
footnoteToEndnoteStrings.CONTEXT_MENU_TO_ENDNOTE[footnoteToEndnotelocale] = "Convert Selected Footnote to Endnote";


//------------------------------------------------------------------------------
// Message strings
//------------------------------------------------------------------------------
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE[footnoteToEndnotelocale] = "Successfully converted %1 Footnote to Endnote.";
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTES_TO_ENDNOTES_FINISHED_MESSAGE[footnoteToEndnotelocale] = "Successfully converted %1 Footnotes to Endnotes.";

footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE_WITH_ERROR[footnoteToEndnotelocale] = "Successfully converted %1 Footnote to Endnote.\nUnable to convert %2 footnote.";
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE_WITH_ERRORS[footnoteToEndnotelocale] = "Successfully converted %1 Footnote to Endnote.\nUnable to convert %2 footnotes.";
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTES_TO_ENDNOTES_FINISHED_MESSAGE_WITH_ERROR[footnoteToEndnotelocale] = "Successfully converted %1 Footnotes to Endnotes.\nUnable to convert %2 footnote.";
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTES_TO_ENDNOTES_FINISHED_MESSAGE_WITH_ERRORS[footnoteToEndnotelocale] = "Successfully converted %1 Footnotes to Endnotes.\nUnable to convert %2 footnotes.";

footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE[footnoteToEndnotelocale] = "Successfully converted %1 Endnote to Footnote.";
footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTES_TO_FOOTNOTES_FINISHED_MESSAGE[footnoteToEndnotelocale] = "Successfully converted %1 Endnotes to Footnotes.";

footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE_WITH_ERROR[footnoteToEndnotelocale] = "Successfully converted %1 Endnote to Footnote.\nUnable to convert %2 Endnote.";
footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE_WITH_ERRORS[footnoteToEndnotelocale] = "Successfully converted %1 Endnote to Footnote.\nUnable to convert %2 Endnotes.";
footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTES_TO_FOOTNOTES_FINISHED_MESSAGE_WITH_ERROR[footnoteToEndnotelocale] = "Successfully converted %1 Endnotes to Footnotes.\nUnable to convert %2 Endnote.";
footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTES_TO_FOOTNOTES_FINISHED_MESSAGE_WITH_ERRORS[footnoteToEndnotelocale] = "Successfully converted %1 Endnotes to Footnotes.\nUnable to convert %2 Endnotes.";

footnoteToEndnoteStrings.NO_FOOTNOTE_FOUND[footnoteToEndnotelocale] = "There are no footnotes to convert. Verify the selection and try again.";
footnoteToEndnoteStrings.NO_ENDNOTE_FOUND[footnoteToEndnotelocale] = "There are no endnotes to convert. Verify the selection and try again.";

//------------------------------------------------------------------------------
// Error strings
//------------------------------------------------------------------------------
footnoteToEndnoteStrings.MISSING_SCRIPT_FILE_ERROR[footnoteToEndnotelocale] = "Error: ConvertFootnoteToEndnote.jsx is missing and cannot be loaded.";
footnoteToEndnoteStrings.CONVERSION_TYPE_NOT_SELECTED_ERROR[footnoteToEndnotelocale] = "Error: Select a conversion option.";