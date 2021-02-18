//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/converturltohyperlink/resources/URLToHyperlinkStrings-ja_JP.jsx $
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

var urlToHyperlinklocale = 'ja_JP';		// this is also the fallback for all English locales

//------------------------------------------------------------------------------
// General strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.DIALOGHEADER[urlToHyperlinklocale] = 'URL をハイパーリンクに変換';
urlToHyperlinkStrings.SCOPELABEL[urlToHyperlinklocale] = 'スコープ';
urlToHyperlinkStrings.SEARCHLABEL[urlToHyperlinklocale] = '検索(&S) :';
urlToHyperlinkStrings.SEARCHDOCUMENTITEM[urlToHyperlinklocale] = 'ドキュメント';
urlToHyperlinkStrings.SEARCHSTORYITEM[urlToHyperlinklocale] = 'ストーリー';
urlToHyperlinkStrings.SEARCHSELECTIONITEM[urlToHyperlinklocale] = '選択範囲';
urlToHyperlinkStrings.APPLYTOHYPERLINKLABEL[urlToHyperlinklocale] = 'ハイパーリンクに適用';
urlToHyperlinkStrings.CHARACTERSTYLELABEL[urlToHyperlinklocale] = '文字スタイル(&C) :';
urlToHyperlinkStrings.NEWCHARACTERSTYLEITEM[urlToHyperlinklocale] = '新規文字スタイル...';
urlToHyperlinkStrings.FINDBUTTONTEXT[urlToHyperlinklocale] = '検索(&F)';
urlToHyperlinkStrings.FINDNEXTBUTTONTEXT[urlToHyperlinklocale] = '次を検索(&N)';
urlToHyperlinkStrings.CONVERTBUTTONTEXT[urlToHyperlinklocale] = '変換(&O)';
urlToHyperlinkStrings.CONVERTALLBUTTONTEXT[urlToHyperlinklocale] = 'すべて変換(&A)';
urlToHyperlinkStrings.DONEBUTTONTEXT[urlToHyperlinklocale] = '完了(&D)';

urlToHyperlinkStrings.URLTOHYPERLINLKACTIONNAME[urlToHyperlinklocale] = 'URL をハイパーリンクに変換(&T)...';
urlToHyperlinkStrings.INDESIGN[urlToHyperlinklocale] = 'Adobe InDesign';

//------------------------------------------------------------------------------
// Message strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.FINISHEDFINDINGMESSAGE[urlToHyperlinklocale] = 'URL 検索が終了しました。';
urlToHyperlinkStrings.CONVERTALLFINISHEDMESSAGE[urlToHyperlinklocale] = ' %1 項目の変換が終了しました。';


//------------------------------------------------------------------------------
// Error strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.NOACTIVEDOCERROR[urlToHyperlinklocale] = 'エラー : ドキュメントが開いていません';
urlToHyperlinkStrings.UNEXPECTEDSCOPEERROR[urlToHyperlinklocale] = 'エラー : 予想されるスコープは「%1」です... 検索結果 :「%2」';
urlToHyperlinkStrings.MISSINGSCRIPTFILEERROR[urlToHyperlinklocale] = 'エラー : ConvertURLToHyperlink.jsx* が見つかりません。読み込みに失敗しました';
