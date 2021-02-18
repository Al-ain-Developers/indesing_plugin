//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/converturltohyperlink/ConvertURLToHyperlinkDialog.jsx $
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
//  
//  Purpose: 
//  
//========================================================================================


ConvertURLToHyperlinkDialog.prototype.GetDialogString = function() {
var convertURLToHyperlinkDialogResource = "palette { properties:{maximizeButton:false, minimizeButton:false }\
	alignChildren:'fill', \
	converttohyperlinks: Group { orientation:'column', alignChildren:'fill', \
		scopePanel: Panel {text:'" + localize(urlToHyperlinkStrings.SCOPELABEL) + "',orientation:'column', alignChildren:'right', spacing:3,\
			scopeGroup: Group { orientation:'row', alignChildren:'right', spacing:3,  \
				st: StaticText { text:'" + localize(urlToHyperlinkStrings.SEARCHLABEL) + "', justify:'right' }, \
				dl: DropDownList { size:[150, 20], alignment:'left'} \
			}\
		} \
		hyperlinkAppearence: Panel {text:'" + localize(urlToHyperlinkStrings.APPLYTOHYPERLINKLABEL) + "',orientation:'column', alignChildren:'right', spacing:3,\
			characterStyleProperty: Group { orientation:'row', alignChildren:'right', spacing:3,  \
				ck: Checkbox{ size:[25, 15], justify:'right'},\
				st: StaticText { text:'" + localize(urlToHyperlinkStrings.CHARACTERSTYLELABEL) + "', justify:'right' }, \
				dl: DropDownList { size:[150, 20], alignment:'right'} \
			} \
		}\
		convertButGrp: Group { orientation:'row', \
			findBtn: Button { text:'" + localize(urlToHyperlinkStrings.FINDBUTTONTEXT) + "', properties:{name:'find'}, alignment:'right' }, \
			convertBtn: Button { text:'" + localize(urlToHyperlinkStrings.CONVERTBUTTONTEXT) + "', properties:{name:'convert'}, alignment:'right' }, \
			convertallBtn: Button { text:'" + localize(urlToHyperlinkStrings.CONVERTALLBUTTONTEXT) + "', properties:{name:'convertall'}, alignment:'right' } \
			DoneBtn: Button { text:'" + localize(urlToHyperlinkStrings.DONEBUTTONTEXT) + "', properties:{name:'done'}, alignment:'right' }, \
		} \
	}\
}";
return convertURLToHyperlinkDialogResource;
}

function ConvertURLToHyperlinkDialog() {
}

ConvertURLToHyperlinkDialog.prototype.InitDialog = function(styles) {
	this.win = new Window(this.GetDialogString(),  localize(urlToHyperlinkStrings.DIALOGHEADER));
	this.InitCharacterStyleDL(styles);
	this.win.center();
	this.win.show();
}


ConvertURLToHyperlinkDialog.prototype.BindDialogEvents = function(findEvent, convertEvent, convertallEvent, DoneEvent, backP) {
	this.win.converttohyperlinks.convertButGrp.findBtn.onClick = function() {
		backP.Findbtnclickevent();
	}

	this.win.converttohyperlinks.convertButGrp.convertBtn.onClick = function() {
		backP.Convertbtnclickevent();
	}

	this.win.converttohyperlinks.convertButGrp.convertallBtn.onClick = function() {
		backP.Convertallbtnclickevent();
	}

	this.win.converttohyperlinks.convertButGrp.DoneBtn.onClick = function() {
		backP.Donebtnclickevent();
	}

	this.win.onClose = function() {
		backP.onCloseEvent();
	}

	this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.dl.onChange = function() {
		backP.dialog.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.ck.value = true;
	}

	this.win.converttohyperlinks.scopePanel.scopeGroup.dl.onChange = function() {
			obj.Selection = app.selection;
			backP.InitData();
	}
}

ConvertURLToHyperlinkDialog.prototype.InitScopeDL = function(scopes, backP) {
	try {
		this.win.converttohyperlinks.scopePanel.scopeGroup.dl.onChange = null;
		this.win.converttohyperlinks.scopePanel.scopeGroup.dl.removeAll();
		for (var i=0 ; i < scopes.length ; i++) {
			this.win.converttohyperlinks.scopePanel.scopeGroup.dl.add('item', scopes[i]);
		}
		this.win.converttohyperlinks.scopePanel.scopeGroup.dl.selection = this.win.converttohyperlinks.scopePanel.scopeGroup.dl.items[0];
		this.win.converttohyperlinks.scopePanel.scopeGroup.dl.onChange = function() {
				backP.Selection = app.selection;
				backP.InitData();
		}
	} catch (x) {
		assert(false, x);
	}
}

ConvertURLToHyperlinkDialog.prototype.SetFindNextButtonText = function() {
	this.win.converttohyperlinks.convertButGrp.findBtn.text = localize(urlToHyperlinkStrings.FINDNEXTBUTTONTEXT);
}

ConvertURLToHyperlinkDialog.prototype.SetFindButtonText = function() {
	this.win.converttohyperlinks.convertButGrp.findBtn.text = localize(urlToHyperlinkStrings.FINDBUTTONTEXT);
}

ConvertURLToHyperlinkDialog.prototype.close = function() {
	this.win.close();
}

ConvertURLToHyperlinkDialog.prototype.characterStyleToSet = function() {
	return (this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.ck.value == true);
}

ConvertURLToHyperlinkDialog.prototype.CharStyleCount = function() {
	return this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.dl.items.length;
}

ConvertURLToHyperlinkDialog.prototype.SelectedStyle = function() {
	return this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.dl.selection.text;
}

ConvertURLToHyperlinkDialog.prototype.SelectedScope = function() {
	return this.win.converttohyperlinks.scopePanel.scopeGroup.dl.selection.text;
}

ConvertURLToHyperlinkDialog.prototype.InitCharacterStyleDL = function(styles) {
	this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.dl.removeAll();
	for (var i=0 ; i < styles.length ; i++)
	{
		this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.dl.add('item', styles[i].name);
	}
//	this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.dl.add('separator', 'separator');
//	this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.dl.add('item', localize(urlToHyperlinkStrings.NEWCHARACTERSTYLEITEM));

	this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.dl.selection = this.win.converttohyperlinks.hyperlinkAppearence.characterStyleProperty.dl.items[0];
}