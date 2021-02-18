//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/footnoteendnoteconversion/resources/FootnoteToEndnoteStrings-ja_JP.jsx $
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

var footnoteToEndnotelocale = 'ja_JP';		

//------------------------------------------------------------------------------
// General strings
//------------------------------------------------------------------------------
footnoteToEndnoteStrings.DIALOGHEADER[footnoteToEndnotelocale] = "脚注と後注を変換";
footnoteToEndnoteStrings.SCOPELABEL[footnoteToEndnotelocale] = "スコープ(&S) : ";
footnoteToEndnoteStrings.SEARCH_DOCUMENT_ITEM[footnoteToEndnotelocale] = "ドキュメント";
footnoteToEndnoteStrings.SEARCH_STORY_ITEM[footnoteToEndnotelocale] = "選択範囲";
footnoteToEndnoteStrings.CONVERT_BUTTON_TEXT[footnoteToEndnotelocale] = "変換(&O)";
footnoteToEndnoteStrings.DONE_BUTTON_TEXT[footnoteToEndnotelocale] = "完了(&D)";
footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE_ACTION_NAME[footnoteToEndnotelocale] = "脚注と後注を変換する...";
footnoteToEndnoteStrings.INDESIGN[footnoteToEndnotelocale] = "Adobe InDesign";
footnoteToEndnoteStrings.CONVERSION[footnoteToEndnotelocale] = "変換(&N)：";
footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE[footnoteToEndnotelocale] = "脚注を後注へ";
footnoteToEndnoteStrings.ENDNOTE_TO_FOOTNOTE[footnoteToEndnotelocale] = "後注を脚注へ";
footnoteToEndnoteStrings.CONVERT_TO_FOOTNOTE[footnoteToEndnotelocale] = "脚注に変換";
footnoteToEndnoteStrings.CONVERT_TO_ENDNOTE[footnoteToEndnotelocale] = "後注に変換";
footnoteToEndnoteStrings.MAIN_MENU_LOCATION[footnoteToEndnotelocale] = "後注オプション...";
footnoteToEndnoteStrings.CONTEXT_MENU_LOCATION[footnoteToEndnotelocale] = "変数を挿入";
footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTE[footnoteToEndnotelocale] = "選択した後注を脚注に変換する";
footnoteToEndnoteStrings.CONTEXT_MENU_TO_FOOTNOTES[footnoteToEndnotelocale] = "選択した後注を脚注に変換する";
footnoteToEndnoteStrings.CONTEXT_MENU_TO_ENDNOTE[footnoteToEndnotelocale] = "選択した脚注を後注に変換して";



//------------------------------------------------------------------------------
// Message strings
//------------------------------------------------------------------------------
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE[footnoteToEndnotelocale] = "%1 脚注を後注に変換しました。";
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTES_TO_ENDNOTES_FINISHED_MESSAGE[footnoteToEndnotelocale] = "%1 個の脚注を後注に変換しました。";

footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE_WITH_ERROR[footnoteToEndnotelocale] = "%1 脚注を後注に変換しました。\n%2 脚注を変換できません。";
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE_WITH_ERRORS[footnoteToEndnotelocale] = "%1 個の脚注を後注に変換しました。\n%2 個の脚注を変換できません。";
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTES_TO_ENDNOTES_FINISHED_MESSAGE_WITH_ERROR[footnoteToEndnotelocale] = "%1 個の脚注を後注に変換しました。\n%2 個の脚注を変換できません。";
footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTES_TO_ENDNOTES_FINISHED_MESSAGE_WITH_ERRORS[footnoteToEndnotelocale] = "%1 個の脚注を後注に変換しました。\n%2 個の脚注を変換できません。";

footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE[footnoteToEndnotelocale] = "%1 後注を脚注に変換しました。";
footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTES_TO_FOOTNOTES_FINISHED_MESSAGE[footnoteToEndnotelocale] = "%1 個の後注を脚注に変換しました。";

footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE_WITH_ERROR[footnoteToEndnotelocale] = "%1 後注を脚注に変換しました。\n%2 後注を変換できません。";
footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE_WITH_ERRORS[footnoteToEndnotelocale] = "%1 個の後注を脚注に変換しました。\n%2 個の後注を変換できません。";
footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTES_TO_FOOTNOTES_FINISHED_MESSAGE_WITH_ERROR[footnoteToEndnotelocale] = "%1 個の後注を脚注に変換しました。\n%2 個の後注を変換できません。";
footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTES_TO_FOOTNOTES_FINISHED_MESSAGE_WITH_ERRORS[footnoteToEndnotelocale] = "%1 個の後注を脚注に変換しました。\n%2 個の後注を変換できません。";

footnoteToEndnoteStrings.NO_FOOTNOTE_FOUND[footnoteToEndnotelocale] = "変換する脚注はありません。 選択範囲を確認してから、もう一度試してください。";
footnoteToEndnoteStrings.NO_ENDNOTE_FOUND[footnoteToEndnotelocale] = "変換する後注はありません。 選択範囲を確認してから、もう一度試してください。";



//------------------------------------------------------------------------------
// Error strings
//------------------------------------------------------------------------------


footnoteToEndnoteStrings.MISSING_SCRIPT_FILE_ERROR[footnoteToEndnotelocale] = "エラー：ConvertFootnoteToEndnote.jsx が見つからないため読み込めません。";
footnoteToEndnoteStrings.CONVERSION_TYPE_NOT_SELECTED_ERROR[footnoteToEndnotelocale] = "エラー：変換オプションを選択してください。";