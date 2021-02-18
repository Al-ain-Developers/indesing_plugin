//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/converturltohyperlink/resources/URLToHyperlinkStrings-zh_TW.jsx $
//  
//  Owner: Saurabh Deshpande
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

var urlToHyperlinklocale = 'zh_TW';		// this is also the fallback for all English locales

//------------------------------------------------------------------------------
// General strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.DIALOGHEADER[urlToHyperlinklocale] = '將 URL 轉換為超連結';
urlToHyperlinkStrings.SCOPELABEL[urlToHyperlinklocale] = '範圍';
urlToHyperlinkStrings.SEARCHLABEL[urlToHyperlinklocale] = '搜尋(&S):';
urlToHyperlinkStrings.SEARCHDOCUMENTITEM[urlToHyperlinklocale] = '文件';
urlToHyperlinkStrings.SEARCHSTORYITEM[urlToHyperlinklocale] = '內文';
urlToHyperlinkStrings.SEARCHSELECTIONITEM[urlToHyperlinklocale] = '選取範圍';
urlToHyperlinkStrings.APPLYTOHYPERLINKLABEL[urlToHyperlinklocale] = '套用至超連結';
urlToHyperlinkStrings.CHARACTERSTYLELABEL[urlToHyperlinklocale] = '字元樣式(&C):';
urlToHyperlinkStrings.NEWCHARACTERSTYLEITEM[urlToHyperlinklocale] = '新增字元樣式...';
urlToHyperlinkStrings.FINDBUTTONTEXT[urlToHyperlinklocale] = '尋找(&F)';
urlToHyperlinkStrings.FINDNEXTBUTTONTEXT[urlToHyperlinklocale] = '尋找下一個(&N)';
urlToHyperlinkStrings.CONVERTBUTTONTEXT[urlToHyperlinklocale] = '轉換(&O)';
urlToHyperlinkStrings.CONVERTALLBUTTONTEXT[urlToHyperlinklocale] = '全部轉換(&A)';
urlToHyperlinkStrings.DONEBUTTONTEXT[urlToHyperlinklocale] = '完成(&D)';

urlToHyperlinkStrings.URLTOHYPERLINLKACTIONNAME[urlToHyperlinklocale] = '將 URL 轉換為超連結(&T)...';
urlToHyperlinkStrings.INDESIGN[urlToHyperlinklocale] = 'Adobe InDesign';

//------------------------------------------------------------------------------
// Message strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.FINISHEDFINDINGMESSAGE[urlToHyperlinklocale] = '已完成尋找 URL';
urlToHyperlinkStrings.CONVERTALLFINISHEDMESSAGE[urlToHyperlinklocale] = '已完成搜尋。%1 處取代已完成。';


//------------------------------------------------------------------------------
// Error strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.NOACTIVEDOCERROR[urlToHyperlinklocale] = '錯誤:尚未開啟任何文件';
urlToHyperlinkStrings.UNEXPECTEDSCOPEERROR[urlToHyperlinklocale] = '錯誤: 範圍應該是「%1」...找到的範圍是:「%2」';
urlToHyperlinkStrings.MISSINGSCRIPTFILEERROR[urlToHyperlinklocale] = '錯誤: ConvertURLToHyperlink.jsx* 遺失；載入失敗';
