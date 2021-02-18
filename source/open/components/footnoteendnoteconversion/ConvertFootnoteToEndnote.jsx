//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/open/components/footnoteendnoteconversion/ConvertFootnoteToEndnote.jsx $
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

#include "includes/FootnoteToEndnoteStrings.jsx"
#include "includes/FootnoteToEndnoteStrings-en_US.jsx"
#include "ConvertFootnoteToEndnoteDialog.jsx"

function ConvertFootnoteToEndnote() {
}


/***************************************************************************************************************
This is used for searching footnote/endnote , depending upon conversion scope selected by user.

***************************************************************************************************************/

ConvertFootnoteToEndnote.prototype.searchData = function() {
	try {
		this.myFoundItems;
		this.currentFoundItem;
        this.convert_to_footnote_count ;
        this.convert_to_endnote_count ;
        this.failed_conversion_count ;
         
        var findWhat = ''; 
         
        //Set Conversion type
        this.conversionType = this.dialog.SelectedConversionType();
        if(this.conversionType != null)
        {
            if( this.conversionType == localize(footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE) )
            {
                //for footnote
                findWhat = findWhat.concat("~F");
            }
            else if( this.conversionType == localize(footnoteToEndnoteStrings.ENDNOTE_TO_FOOTNOTE) )
            {
                //for Endnote
                findWhat = findWhat.concat("~U");
            }

            //based on conversion type we need to set findWhat variable
            app.findGrepPreferences = NothingEnum.nothing;
            app.findChangeGrepOptions.includeFootnotes = true;
            app.findChangeGrepOptions.includeHiddenLayers = true;
            app.findChangeGrepOptions.includeLockedLayersForFind = false;
            app.findChangeGrepOptions.includeLockedStoriesForFind = false;
         
            //Excluding master pages since endnotes are not allowed on master pages.
            app.findChangeGrepOptions.includeMasterPages = false;
            app.findGrepPreferences.findWhat = findWhat;
        
            //Set Conversion Scope
            this.currentFoundItem = null;
		
            switch (this.dialog.SelectedScope())
            {
                case localize(footnoteToEndnoteStrings.SEARCH_DOCUMENT_ITEM):
                    //Find  footnote/endnote
                    this.doc = this.activeApp.activeDocument;
                    this.myFoundItems = this.doc.findGrep().reverse();
                    this.myFoundItems = this.create_conversionlist_endnote_footnote();
                    break;
                case localize(footnoteToEndnoteStrings.SEARCH_STORY_ITEM):
            
                    //Based on selection either multiple objects, group , text , or anything else create endnote or footnote conversion list.
                    this.Selection = app.selection;
                    this.myFoundItems = this.search_for_storytype_item(this.Selection);
    
                    this.myFoundItems = this.create_conversionlist_endnote_footnote();
                    break;
            }
        }
	} 
    catch (x) {
		assert(false, 'Caught in searchData : ' + x);
	}
}

ConvertFootnoteToEndnote.prototype.checkparentstory = function ( obj1 )
{
    var flag = false;
    switch (obj1.constructor.name)
    {
		case 'Character':
		case 'Word':
		case 'TextStyleRange':
		case 'Line':
		case 'Paragraph':
		case 'TextColumn':
		case 'Text':
		//case 'InsertionPoint':
		case 'Story':
		case 'TextFrame':
                    if(obj1.contents =="") 
                    {flag = false; break;}
        case 'EndnoteTextFrame':
        case 'TextPath':
        case 'Cell':
        case 'Table':
        case 'Column':
        case 'Row':
            flag = true;
			break;
		default :
			flag = false;
			break;
    }
 
    return flag;
}



/**************************************************************************************************************************************************
This is used for searching footnote/endnote , based on user selection . Since,user can select multiple pageItems  for conversion.

**************************************************************************************************************************************************/

ConvertFootnoteToEndnote.prototype.search_for_storytype_item = function ( obj2 )
{
    var datatype=[];
    var i=0;  
    var sel_len = obj2.length;


    for(;i<sel_len;i++)
    {
        if( this.checkparentstory(obj2[i]) )
        {
            datatype = datatype.concat(obj2[i].findGrep().reverse());
        }
        
        if( obj2[i].constructor.name == 'Group')
        {
            var arr = obj2[i].pageItems;
            var grp_len =  arr.length;
            var j=0;
            for(;j<grp_len;j++)
            {

                if( this.checkparentstory(arr[j].getElements()[0]) )
                {
                    datatype = datatype.concat(arr[j].getElements()[0].findGrep().reverse());
                }
            
                if( arr[j].getElements()[0].constructor.name == 'Group')
                {
                    datatype =  datatype.concat(this.search_for_storytype_item(arr[j].getElements()));
                }
            } //End of for  loop
        }
    }//End of for loop

    return datatype;
}

/**************************************************************************************************************************************************
This is used final conversion of  footnote to endnote 

**************************************************************************************************************************************************/


ConvertFootnoteToEndnote.prototype.footnote_to_endnote = function (fnote){
    try 
    {
        var enote;
        if(fnote!=null)
        {
            //Create a new endnote at same location of footnote
            enote = fnote.storyOffset.createEndnote();
                            
            //Clean all the content of endnote
            //enote.texts[0].remove();
            fnote.characters[0].contents = '';
                            
            //move data from footnote to endnote
            fnote.texts[0].move (LocationOptions.AFTER, enote.insertionPoints[-1]);
            
            enote.insertionPoints[0].applyParagraphStyle(app.activeDocument.endnoteOptions.endnoteTextStyle);
    
            //remove footnote.
            fnote.remove();
            return true;
        }
        else
        {
            return false;
        }
    }
    catch(x)
    {
		assert(false, 'Caught in footnote_to_endnote : ' + x);
        return false;
	}
}


/**************************************************************************************************************************************************
This is used final conversion of  endnote  to footnote.

**************************************************************************************************************************************************/

ConvertFootnoteToEndnote.prototype.endnote_to_footnote = function (enote){
    
    try 
    {    
        var fnote;
        if( enote !=null )
        {
            //Create a new footnote at same location of endnote
            fnote = enote.storyOffset.footnotes.add();
                        
            //Clean all the content of footnote
            enote.characters[0].contents = '';
            //fnote.texts[0].remove();
                       
            //move data from endnote to footnote
            enote.texts[0].move(LocationOptions.AFTER, fnote.insertionPoints[-1]);

            fnote.insertionPoints[0].applyParagraphStyle(app.activeDocument.footnoteOptions.footnoteTextStyle);
            
            //remove endnote.
            enote.deleteEndnote();
            
            return true;
        }
        else
        {
            return false;
        }
    }
    catch(x)
    {
		assert(false, 'Caught in endnote_to_footnote : ' + x);
        return false;
	}
}


/***************************************************************************************************************
This is used for creating list of footnote/endnote , when conversion scope is for complete document.

***************************************************************************************************************/

ConvertFootnoteToEndnote.prototype.create_conversionlist_endnote_footnote  = function() {

    var temp_arr = [];
    var temp_data;
    var isendnotestoryflag;
    
    var len = this.myFoundItems.length;
    
    if(this.conversionType != null)
    {
        if( this.conversionType == localize(footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE) )
        {
            //for footnote
            while (len > 0) 
            {
                try {
                temp_data = this.myFoundItems.shift();
                if(temp_data.parent.constructor.name == 'Footnote' )
                {
                    temp_arr.push(temp_data);
                }
                len--;
                }
                catch(x){
                    len--;
                }
            } //End of while loop
    
        }
        else if( this.conversionType == localize(footnoteToEndnoteStrings.ENDNOTE_TO_FOOTNOTE) )
        {
            //for Endnote
            isendnotestoryflag = this.checkisendnotestory(this.myFoundItems);            
            
            while (len > 0) 
            {
                try {
                
                temp_data = this.myFoundItems.shift();
                if(this.dialog.SelectedScope() == localize(footnoteToEndnoteStrings.SEARCH_DOCUMENT_ITEM) )
                {
                    if((temp_data.parent.constructor.name == 'Story') && (temp_data.parent.isEndnoteStory== true) )
                    {
                        temp_arr.push(temp_data);
                    }
                    len--;
                }

                else //Scope is selection
                {
                    if( isendnotestoryflag == true)
                    {
                        if((temp_data.parent.constructor.name == 'Story') && (temp_data.parent.isEndnoteStory== true) )
                        {
                            temp_arr.push(temp_data);
                        }
                        len--;
                    }    
                    else
                    {
                        if( (temp_data.parent.constructor.name == 'Story') || (temp_data.parent.constructor.name == 'Cell') )
                        {
                            temp_arr.push(temp_data);
                        }
                        len--;
                    
                    }
                    
                }
                }//end of try
                    catch(x){
                    len--;
                }
            } //End of while loop
    
        }
    

        return temp_arr;
    }

}


ConvertFootnoteToEndnote.prototype.Donebtnclickevent  = function() {
		this.dialog.close();
        this.dialogOpen = false;
}

ConvertFootnoteToEndnote.prototype.onCloseEvent = function() {
    this.dialogOpen = false;
}


/***********************************************************************************
This is for finding correct index endnote based on selection. 

***********************************************************************************/
ConvertFootnoteToEndnote.prototype.searchendnoteindex = function( echar) 
{
    
    var estory = echar.parent;
     
    var findWhat = ''; 
    findWhat = findWhat.concat("~U");
    app.findGrepPreferences = NothingEnum.nothing;
            app.findChangeGrepOptions.includeFootnotes = true;
            app.findChangeGrepOptions.includeHiddenLayers = true;
            app.findChangeGrepOptions.includeLockedLayersForFind = false;
            app.findChangeGrepOptions.includeLockedStoriesForFind = false;
         
            //Excluding master pages since endnotes are not allowed on master pages.
            app.findChangeGrepOptions.includeMasterPages = false;
            app.findGrepPreferences.findWhat = findWhat;
            
            story_endnotes = estory.findGrep();
            
            for(var i =0 ; i<story_endnotes.length;i++)
            {
                if(echar.index == story_endnotes[i].index)
                {
                    eindex = i;
                    break;
                }
             }
         
         
         if(echar.parent.constructor.name == 'Story')  
        {
            for(var j=0;j<estory.endnotes.length;j++)
            {
                
                if(estory.endnotes[j].index == eindex)
                { eindex = j; break;}
            }
        }
         
         return eindex;
}



/***********************************************************************************
This is for finding isendnotestory is true for list of endnote based on selection. 

***********************************************************************************/
ConvertFootnoteToEndnote.prototype.checkisendnotestory = function( itemList) 
{
        var flag = false;
        var len = itemList.length;
        for (i=0;i<len;i++)
        {
            var temp = itemList[i];
            if( (temp.parent.constructor.name == 'Story') && (temp.parent.isEndnoteStory== true) )
            {
                flag = true;
                break;
            }
        }    
          
         if(flag==true)
            return true;
         else
            return false;
}



/***********************************************************************************
This is for converting endnote to footnote when conversion dialog is used. 

***********************************************************************************/

ConvertFootnoteToEndnote.prototype.convert_endnote_to_footnote = function() 
{
    var enote;
    var fnote;
    

    try 
    {
        if( this.dialog.SelectedScope() == localize(footnoteToEndnoteStrings.SEARCH_DOCUMENT_ITEM) )
        {
            enote = this.currentFoundItem.parent.endnoteRanges[0].sourceEndnote;
        }
        else //when scope is selection.
        {
            var eindex = this.searchendnoteindex(this.currentFoundItem);
            if( (this.currentFoundItem.parent.constructor.name == 'Story') && (this.currentFoundItem.parent.isEndnoteStory== true) )
                enote = this.currentFoundItem.parent.endnoteRanges[eindex].sourceEndnote;        
            else
                enote = this.currentFoundItem.parent.endnotes[eindex];
         }

         var e_sep = app.activeDocument.endnoteOptions.endnoteSeparatorText ;
         app.activeDocument.endnoteOptions.endnoteSeparatorText = '';


            if(this.endnote_to_footnote(enote) == true)
            {
                this.convert_to_footnote_count++;
            }
            else
            {
                this.failed_conversion_count++;
            }
            
            app.activeDocument.endnoteOptions.endnoteSeparatorText = e_sep;
            
	}//end of try
     catch(x)
     {
         this.failed_conversion_count++;
    }

}


/***********************************************************************************
This is for converting footnote to endnote when conversion dialog is used. 

***********************************************************************************/

ConvertFootnoteToEndnote.prototype.convert_footnote_to_endnote = function() 
{
    var enote;
    var fnote;
     
     if(this.currentFoundItem.parent.constructor.name == 'Footnote' )
     {
            fnote = this.currentFoundItem.parent;
            
             var f_sep = app.activeDocument.footnoteOptions.separatorText ;
             app.activeDocument.footnoteOptions.separatorText = '';

            if(this.footnote_to_endnote(fnote) == true)
            {
                this.convert_to_endnote_count++;
            }
            else
            {
                //This might fail because endenote is not allowed on mater pages.
                this.failed_conversion_count++;
            }
            
            app.activeDocument.footnoteOptions.separatorText  = f_sep;
      }

}


/***********************************************************************************
This is for conversion operation when convert button is clicked.

***********************************************************************************/

ConvertFootnoteToEndnote.prototype.Convertbtnclickevent = function() {
	try
	{
        //check atleast one conversion type is selected.
        this.conversionType = this.dialog.SelectedConversionType();
        if(this.conversionType == null)
        {
            alert(localize(footnoteToEndnoteStrings.CONVERSION_TYPE_NOT_SELECTED_ERROR), localize(footnoteToEndnoteStrings.INDESIGN));
        }
        else
        {
            //reseting all the counters
            this.convert_to_footnote_count  = 0;
            this.convert_to_endnote_count = 0;
            this.failed_conversion_count = 0;
            this.searchData(); 

            if( this.myFoundItems.length == 0)
            {
                   if(this.conversionType != null)
                  {
                        if( this.conversionType == localize(footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE) )
                        {
                            alert(localize(footnoteToEndnoteStrings.NO_FOOTNOTE_FOUND), localize(footnoteToEndnoteStrings.INDESIGN));
                         }
                        else if( this.conversionType == localize(footnoteToEndnoteStrings.ENDNOTE_TO_FOOTNOTE) )
                        {
                            alert(localize(footnoteToEndnoteStrings.NO_ENDNOTE_FOUND), localize(footnoteToEndnoteStrings.INDESIGN));
                        }
                  }
            }
            else
            {
                if( this.conversionType == localize(footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE) )
                {
                   
                    while (this.myFoundItems.length > 0) 
                    {
                        this.currentFoundItem = this.myFoundItems.pop();
                        app.doScript('this.convert_footnote_to_endnote()', undefined, undefined, UndoModes.entireScript);
                    }
                    
                 }
                 else if( this.conversionType == localize(footnoteToEndnoteStrings.ENDNOTE_TO_FOOTNOTE) )
                 {
                     while (this.myFoundItems.length > 0) 
                     {
                        this.currentFoundItem = this.myFoundItems.pop();
                        app.doScript('this.convert_endnote_to_footnote()', undefined, undefined, UndoModes.entireScript);
                     }

                  } 
                
                this.currentFoundItem = null;
           
                if( this.conversionType == localize(footnoteToEndnoteStrings.FOOTNOTE_TO_ENDNOTE) )
                {
					//check for failures
                    if(this.failed_conversion_count > 0)
                    {
						if(this.convert_to_endnote_count<=1 && this.failed_conversion_count<=1)
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE_WITH_ERROR,this.convert_to_endnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
						else if(this.convert_to_endnote_count<=1 && this.failed_conversion_count>1)
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE_WITH_ERRORS,this.convert_to_endnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
						else if(this.convert_to_endnote_count>1 && this.failed_conversion_count<=1)
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTES_TO_ENDNOTES_FINISHED_MESSAGE_WITH_ERROR,this.convert_to_endnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
						else 
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTES_TO_ENDNOTES_FINISHED_MESSAGE_WITH_ERRORS,this.convert_to_endnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
                    }
                    else
                    {
						if(this.convert_to_endnote_count==1)
                        {
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE, this.convert_to_endnote_count), localize(footnoteToEndnoteStrings.INDESIGN));
						}
						else
						{
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTES_TO_ENDNOTES_FINISHED_MESSAGE, this.convert_to_endnote_count), localize(footnoteToEndnoteStrings.INDESIGN));
						}
                    }
                }
                else if( this.conversionType == localize(footnoteToEndnoteStrings.ENDNOTE_TO_FOOTNOTE) )
                {
					//check for failures
                    if(this.failed_conversion_count > 0)
                    {
						if(this.convert_to_footnote_count<=1 && this.failed_conversion_count<=1)
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE_WITH_ERROR,this.convert_to_footnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
						else if(this.convert_to_footnote_count<=1 && this.failed_conversion_count>1)
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE_WITH_ERRORS,this.convert_to_footnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
						else if(this.convert_to_footnote_count>1 && this.failed_conversion_count<=1)
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTES_TO_FOOTNOTES_FINISHED_MESSAGE_WITH_ERROR,this.convert_to_footnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
						else
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTES_TO_FOOTNOTES_FINISHED_MESSAGE_WITH_ERRORS,this.convert_to_footnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
                    }
                    else
                    {
                        if(this.convert_to_footnote_count==1)
						{
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE, this.convert_to_footnote_count), localize(footnoteToEndnoteStrings.INDESIGN));
						}
						else
						{
							alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTES_TO_FOOTNOTES_FINISHED_MESSAGE, this.convert_to_footnote_count), localize(footnoteToEndnoteStrings.INDESIGN));
						}
                    }
                }
            }  
        }
    }// end of try
    catch(x) {
		this.currentFoundItem = null;
		assert(false, 'Caught in Convertallbtnclickevent : ' + x);
	}
}



/***********************************************************************************
This is for setting up various conversion scopes like document and story.

***********************************************************************************/

ConvertFootnoteToEndnote.prototype.SetCurrentScopes  = function(){

    var possibleScopes = [localize(footnoteToEndnoteStrings.SEARCH_DOCUMENT_ITEM),localize(footnoteToEndnoteStrings.SEARCH_STORY_ITEM)];
	try 
    {
			/*possibleScopes[0] = localize(footnoteToEndnoteStrings.SEARCH_DOCUMENT_ITEM);
            possibleScopes[1] = localize(footnoteToEndnoteStrings.SEARCH_STORY_ITEM);*/
			obj.dialog.InitScopeDL(possibleScopes, obj);
	} catch(x) 
    {
		assert(false, 'Caught in SetCurrentScopes : ' + x);
	}
}


/***********************************************************************************
This is for converting endnote to footnote using mouse right click 

***********************************************************************************/

ConvertFootnoteToEndnote.prototype.do_context_endnote_to_footnote = function(){
    
        this.convert_to_footnote_count = 0;
        this.failed_conversion_count = 0;
        var i = 0;
        var enote_list = [];
        
        //create list of endnote based on selection    
        for(;i<app.selection[0].endnoteRanges.length;i++)
        {
            enote_list.push(app.selection[0].endnoteRanges[i].sourceEndnote);
        }
    
        var e_sep = app.activeDocument.endnoteOptions.endnoteSeparatorText ;
        app.activeDocument.endnoteOptions.endnoteSeparatorText = '';
        
        for(i=0;i<enote_list.length;i++)
        {
            if( this.endnote_to_footnote(enote_list[i]) == true )
            {
                this.convert_to_footnote_count++;
            }
            else
            {
                this.failed_conversion_count++;
            }
        }
    
        app.activeDocument.endnoteOptions.endnoteSeparatorText = e_sep;
        
        if(this.failed_conversion_count > 0)
        {
            alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE_WITH_ERROR,this.convert_to_footnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
        }
        else
        {
            alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_ENDNOTE_TO_FOOTNOTE_FINISHED_MESSAGE, this.convert_to_footnote_count), localize(footnoteToEndnoteStrings.INDESIGN));
       }
  
}


/***********************************************************************************
This is for converting footnote to endnote using mouse right click 

***********************************************************************************/
ConvertFootnoteToEndnote.prototype.do_context_footnote_to_endnote = function(){

    try
    {
        this.convert_to_endnote_count = 0;
        this.failed_conversion_count = 0;
        
        var fnote = app.selection[0].parent;

        var f_sep = app.activeDocument.footnoteOptions.separatorText ;
        app.activeDocument.footnoteOptions.separatorText = '';
        
        if(this.footnote_to_endnote(fnote) == true)
        {
            this.convert_to_endnote_count++;
        }
        else
        {
            this.failed_conversion_count++;
        }
    
        app.activeDocument.footnoteOptions.separatorText = f_sep;
    
        if(this.failed_conversion_count > 0)
        {
            alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE_WITH_ERROR,this.convert_to_endnote_count,this.failed_conversion_count), localize(footnoteToEndnoteStrings.INDESIGN));
        }
        else
        {
            alert(localize(footnoteToEndnoteStrings.CONVERT_ALL_FOOTNOTE_TO_ENDNOTE_FINISHED_MESSAGE, this.convert_to_endnote_count), localize(footnoteToEndnoteStrings.INDESIGN));
        }
    }
    catch(x) 
    {
		assert(false, 'Caught in do_context_footnote_to_endnote : ' + x);
    }
   
}


/********************************************************
This is for initailizing the conversion dialog.

********************************************************/
ConvertFootnoteToEndnote.prototype.RunDialog  = function()
{
	try 
    {
		this.activeApp = app;
		this.doc = this.activeApp.activeDocument;
		this.Selection = app.selection;
		
		//load localized strings 
        ConvertFootnoteToEndnoteMenuItem.localizeStrings();
		
		this.dialog = new ConvertFootnoteToEndnoteDialog();
        this.dialog.InitDialog();
		this.dialogOpen = true;

		this.SetCurrentScopes();
		
		this.dialog.BindDialogEvents(this.Convertbtnclickevent, this.Donebtnclickevent, obj);
	} 
    catch(x) 
    {
		assert(false, 'Caught in RunDialog : ' + x);
	}
}

