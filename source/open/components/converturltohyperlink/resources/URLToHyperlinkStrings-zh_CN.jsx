//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/converturltohyperlink/resources/URLToHyperlinkStrings-zh_CN.jsx $
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

var urlToHyperlinklocale = 'zh_CN';		// this is also the fallback for all English locales

//------------------------------------------------------------------------------
// General strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.DIALOGHEADER[urlToHyperlinklocale] = '将 URL 转换为超链接';
urlToHyperlinkStrings.SCOPELABEL[urlToHyperlinklocale] = '范围';
urlToHyperlinkStrings.SEARCHLABEL[urlToHyperlinklocale] = '搜索(&S):';
urlToHyperlinkStrings.SEARCHDOCUMENTITEM[urlToHyperlinklocale] = '文档';
urlToHyperlinkStrings.SEARCHSTORYITEM[urlToHyperlinklocale] = '文章';
urlToHyperlinkStrings.SEARCHSELECTIONITEM[urlToHyperlinklocale] = '选区';
urlToHyperlinkStrings.APPLYTOHYPERLINKLABEL[urlToHyperlinklocale] = '应用于超链接';
urlToHyperlinkStrings.CHARACTERSTYLELABEL[urlToHyperlinklocale] = '字符样式(&C):';
urlToHyperlinkStrings.NEWCHARACTERSTYLEITEM[urlToHyperlinklocale] = '新建字符样式...';
urlToHyperlinkStrings.FINDBUTTONTEXT[urlToHyperlinklocale] = '查找(&F)';
urlToHyperlinkStrings.FINDNEXTBUTTONTEXT[urlToHyperlinklocale] = '查找下一个(&N)';
urlToHyperlinkStrings.CONVERTBUTTONTEXT[urlToHyperlinklocale] = '转换(&O)';
urlToHyperlinkStrings.CONVERTALLBUTTONTEXT[urlToHyperlinklocale] = '全部转换(&A)';
urlToHyperlinkStrings.DONEBUTTONTEXT[urlToHyperlinklocale] = '完成(&D)';

urlToHyperlinkStrings.URLTOHYPERLINLKACTIONNAME[urlToHyperlinklocale] = '将 URL 转换为超链接(&T)...';
urlToHyperlinkStrings.INDESIGN[urlToHyperlinklocale] = 'Adobe InDesign';

//------------------------------------------------------------------------------
// Message strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.FINISHEDFINDINGMESSAGE[urlToHyperlinklocale] = '结束 URL 的查找';
urlToHyperlinkStrings.CONVERTALLFINISHEDMESSAGE[urlToHyperlinklocale] = '已完成搜索。共执行了 %1 次替换。';


//------------------------------------------------------------------------------
// Error strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.NOACTIVEDOCERROR[urlToHyperlinklocale] = '错误: 文档未打开';
urlToHyperlinkStrings.UNEXPECTEDSCOPEERROR[urlToHyperlinklocale] = '错误: 期望的范围是“%1”...找到的范围是:“%2”';
urlToHyperlinkStrings.MISSINGSCRIPTFILEERROR[urlToHyperlinklocale] = '错误: 缺少 ConvertURLToHyperlink.jsx*；载入失败';
