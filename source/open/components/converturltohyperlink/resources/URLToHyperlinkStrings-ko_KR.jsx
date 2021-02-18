//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/converturltohyperlink/resources/URLToHyperlinkStrings-ko_KR.jsx $
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

var urlToHyperlinklocale = 'ko_KR';		// this is also the fallback for all English locales

//------------------------------------------------------------------------------
// General strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.DIALOGHEADER[urlToHyperlinklocale] = 'URL을 하이퍼링크로 변환';
urlToHyperlinkStrings.SCOPELABEL[urlToHyperlinklocale] = '범위';
urlToHyperlinkStrings.SEARCHLABEL[urlToHyperlinklocale] = '검색(&S):';
urlToHyperlinkStrings.SEARCHDOCUMENTITEM[urlToHyperlinklocale] = '문서';
urlToHyperlinkStrings.SEARCHSTORYITEM[urlToHyperlinklocale] = '스토리';
urlToHyperlinkStrings.SEARCHSELECTIONITEM[urlToHyperlinklocale] = '선택 항목';
urlToHyperlinkStrings.APPLYTOHYPERLINKLABEL[urlToHyperlinklocale] = '하이퍼링크에 적용';
urlToHyperlinkStrings.CHARACTERSTYLELABEL[urlToHyperlinklocale] = '문자 스타일(&C):';
urlToHyperlinkStrings.NEWCHARACTERSTYLEITEM[urlToHyperlinklocale] = '새 문자 스타일...';
urlToHyperlinkStrings.FINDBUTTONTEXT[urlToHyperlinklocale] = '찾기(&F)';
urlToHyperlinkStrings.FINDNEXTBUTTONTEXT[urlToHyperlinklocale] = '다음 찾기(&N)';
urlToHyperlinkStrings.CONVERTBUTTONTEXT[urlToHyperlinklocale] = '변환(&O)';
urlToHyperlinkStrings.CONVERTALLBUTTONTEXT[urlToHyperlinklocale] = '모두 변환(&A)';
urlToHyperlinkStrings.DONEBUTTONTEXT[urlToHyperlinklocale] = '완료(&D)';

urlToHyperlinkStrings.URLTOHYPERLINLKACTIONNAME[urlToHyperlinklocale] = 'URL을 하이퍼링크로 변환(&T)...';
urlToHyperlinkStrings.INDESIGN[urlToHyperlinklocale] = 'Adobe InDesign';

//------------------------------------------------------------------------------
// Message strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.FINISHEDFINDINGMESSAGE[urlToHyperlinklocale] = 'URL 찾기 완료';
urlToHyperlinkStrings.CONVERTALLFINISHEDMESSAGE[urlToHyperlinklocale] = '검색이 완료되었습니다. %1개의 항목을 바꿨습니다.';


//------------------------------------------------------------------------------
// Error strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.NOACTIVEDOCERROR[urlToHyperlinklocale] = '오류 : 열린 문서 없음';
urlToHyperlinkStrings.UNEXPECTEDSCOPEERROR[urlToHyperlinklocale] = '오류 : 예상 범위는 “%1”인데... 찾은 범위: “%2”';
urlToHyperlinkStrings.MISSINGSCRIPTFILEERROR[urlToHyperlinklocale] = '오류 : ConvertURLToHyperlink.jsx*가 없음. 불러오기 실패';
