//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/converturltohyperlink/resources/URLToHyperlinkStrings-ru_RU.jsx $
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

var urlToHyperlinklocale = 'ru_RU';		// this is also the fallback for all English locales

//------------------------------------------------------------------------------
// General strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.DIALOGHEADER[urlToHyperlinklocale] = 'Преобразовать адреса URL в гиперссылки';
urlToHyperlinkStrings.SCOPELABEL[urlToHyperlinklocale] = 'Диапазон';
urlToHyperlinkStrings.SEARCHLABEL[urlToHyperlinklocale] = '&Зона поиска:';
urlToHyperlinkStrings.SEARCHDOCUMENTITEM[urlToHyperlinklocale] = 'Документ';
urlToHyperlinkStrings.SEARCHSTORYITEM[urlToHyperlinklocale] = 'Материал';
urlToHyperlinkStrings.SEARCHSELECTIONITEM[urlToHyperlinklocale] = 'Выделенный фрагмент';
urlToHyperlinkStrings.APPLYTOHYPERLINKLABEL[urlToHyperlinklocale] = 'Применить к гиперссылке';
urlToHyperlinkStrings.CHARACTERSTYLELABEL[urlToHyperlinklocale] = '&Стиль символа:';
urlToHyperlinkStrings.NEWCHARACTERSTYLEITEM[urlToHyperlinklocale] = 'Новый стиль символов...';
urlToHyperlinkStrings.FINDBUTTONTEXT[urlToHyperlinklocale] = '&Найти';
urlToHyperlinkStrings.FINDNEXTBUTTONTEXT[urlToHyperlinklocale] = 'Найти &далее';
urlToHyperlinkStrings.CONVERTBUTTONTEXT[urlToHyperlinklocale] = 'Пр&еобразовать';
urlToHyperlinkStrings.CONVERTALLBUTTONTEXT[urlToHyperlinklocale] = 'Преобразовать &все';
urlToHyperlinkStrings.DONEBUTTONTEXT[urlToHyperlinklocale] = '&Готово';

urlToHyperlinkStrings.URLTOHYPERLINLKACTIONNAME[urlToHyperlinklocale] = 'Преобразовать адреса URL в &гиперссылки...';
urlToHyperlinkStrings.INDESIGN[urlToHyperlinklocale] = 'Adobe InDesign';

//------------------------------------------------------------------------------
// Message strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.FINISHEDFINDINGMESSAGE[urlToHyperlinklocale] = 'Поиск адресов URL завершен';
urlToHyperlinkStrings.CONVERTALLFINISHEDMESSAGE[urlToHyperlinklocale] = 'Поиск завершен. Произведено замен: %1.';


//------------------------------------------------------------------------------
// Error strings
//------------------------------------------------------------------------------

urlToHyperlinkStrings.NOACTIVEDOCERROR[urlToHyperlinklocale] = 'Ошибка: Нет открытых документов';
urlToHyperlinkStrings.UNEXPECTEDSCOPEERROR[urlToHyperlinklocale] = 'Ошибка: Выбрана зона поиска “%1”... Найдено: “%2”';
urlToHyperlinkStrings.MISSINGSCRIPTFILEERROR[urlToHyperlinklocale] = 'Ошибка: Файл ConvertURLToHyperlink.jsx* отсутствует; загрузка прервана';
