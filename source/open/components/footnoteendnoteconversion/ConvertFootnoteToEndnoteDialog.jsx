//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/footnoteendnoteconversion/ConvertFootnoteToEndnoteDialog.jsx $
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
//  
//  Purpose: 
//  
//========================================================================================


ConvertFootnoteToEndnoteDialog.prototype.GetDialogString = function() {
var ConvertFootnoteToEndnoteDialogResource = "palette { properties:{maximizeButton:false, minimizeButton:false }\
	alignChildren:'fill', \
	convertfoottoend: Group { orientation:'row', alignChildren:'fill', \
     Panel1: Panel {text:'',orientation:'column', alignChildren:'right', spacing:5,\
        group1: Group {orientation:'row', alignChildren:'fill', spacing:5,\
              group2: Group {orientation:'column', alignChildren:'right', spacing:5,\
				convert: StaticText {text:'" + localize(footnoteToEndnoteStrings.CONVERSION) + "', value:false,alignment:'rigth',justify:'right'} \
                  dummy: StaticText {size:[20,25],text:' ', value:false,alignment:'right',justify:'right'} \
                  scope: StaticText { text:'" + localize(footnoteToEndnoteStrings.SCOPELABEL) + "',orientation:'column:fill',alignment:'right', justify:'right' }, \
			}\
              group3: Group {orientation:'column', alignChildren:'fill', spacing:5,\
				rdef: RadioButton {text:'" + localize(footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE) +"', value:false,justify:'left'} \
                  rdfe: RadioButton {text:'" + localize(footnoteToEndnoteStrings.ENDNOTE_TO_FOOTNOTE) +"', value:false,justify:'left'} \
				dl: DropDownList { alignment:'fill'} \
			}\
		} \
        } \
        Panel2: Panel {text:'',orientation:'column', alignChildren:'fill', spacing:10,\
		convertButGrp: Group { orientation:'column', alignChildren:'fill',spacing:10,\
			convertBtn: Button { text:'" + localize(footnoteToEndnoteStrings.CONVERT_BUTTON_TEXT) + "', properties:{name:'convert'} }, \
			DoneBtn: Button { text:'" + localize(footnoteToEndnoteStrings.DONE_BUTTON_TEXT) + "', properties:{name:'done'}}, \
		} \
        } \
	}\
}";
return ConvertFootnoteToEndnoteDialogResource;
}

function ConvertFootnoteToEndnoteDialog() {
}


ConvertFootnoteToEndnoteDialog.prototype.InitDialog = function() {
	this.win = new Window(this.GetDialogString(),  localize(footnoteToEndnoteStrings.DIALOGHEADER));
     this.win.convertfoottoend.Panel1.group1.group3.rdef.value = true;
	this.win.center();
	this.win.show();
}


ConvertFootnoteToEndnoteDialog.prototype.BindDialogEvents = function(convertEvent, DoneEvent, backP) {

	this.win.convertfoottoend.Panel2.convertButGrp.convertBtn.onClick = function() {
		backP.Convertbtnclickevent();
	}

	this.win.convertfoottoend.Panel2.convertButGrp.DoneBtn.onClick = function() {
		backP.Donebtnclickevent();
	}

	this.win.onClose = function() {
		backP.onCloseEvent();
	}

	this.win.convertfoottoend.Panel1.group1.group3.dl.onChange = function() {
			obj.Selection = app.selection;
	
	}

    
    this.win.convertfoottoend.Panel1.group1.group3.rdfe.onClick = function() {

	}

    this.win.convertfoottoend.Panel1.group1.group3.rdef.onClick = function() {

	}

}

ConvertFootnoteToEndnoteDialog.prototype.InitScopeDL = function(scopes, backP) {
	try 
    {
		this.win.convertfoottoend.Panel1.group1.group3.dl.onChange = null;
		this.win.convertfoottoend.Panel1.group1.group3.dl.removeAll();
		for (var i=0 ; i < scopes.length ; i++) 
        {
			this.win.convertfoottoend.Panel1.group1.group3.dl.add('item', scopes[i]);
		}
		
        this.win.convertfoottoend.Panel1.group1.group3.dl.selection = this.win.convertfoottoend.Panel1.group1.group3.dl.items[0];
	} catch (x) {
		assert(false, x);
	}
}


ConvertFootnoteToEndnoteDialog.prototype.close = function() {
	this.win.close();
}


ConvertFootnoteToEndnoteDialog.prototype.SelectedScope = function() {
	return this.win.convertfoottoend.Panel1.group1.group3.dl.selection.text;
}

ConvertFootnoteToEndnoteDialog.prototype.SelectedConversionType = function() {

    if( (this.win.convertfoottoend.Panel1.group1.group3.rdef.value == true) && (this.win.convertfoottoend.Panel1.group1.group3.rdfe.value == false) )
        return this.win.convertfoottoend.Panel1.group1.group3.rdef.text;
    else if( (this.win.convertfoottoend.Panel1.group1.group3.rdfe.value == true) && (this.win.convertfoottoend.Panel1.group1.group3.rdef.value == false) )
        return this.win.convertfoottoend.Panel1.group1.group3.rdfe.text;
    else if( (this.win.convertfoottoend.Panel1.group1.group3.rdfe.value == false) && (this.win.convertfoottoend.Panel1.group1.group3.rdef.value == false) )
        return null;
        
}

