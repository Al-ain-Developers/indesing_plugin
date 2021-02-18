/**************************************************************************
 *                                                                        *
 *  Copyright 2014 Adobe Systems Incorporated                             *
 *  All Rights Reserved.                                                  *
 *                                                                        *
 * NOTICE:  All information contained herein is, and remains the property *
 * of Adobe Systems Incorporated and its suppliers, if any.               *
 * The intellectual and technical concepts contained herein are           *
 * proprietary to Adobe Systems Incorporated and its suppliers and may be *
 * covered by U.S. and Foreign Patents, patents in process, and are       *
 * protected by trade secret or copyright law.                            *
 * Dissemination of this information or reproduction of this material     *
 * strictly forbidden unless prior written permission is obtained from    *
 * Adobe Systems Incorporated.                                            *
 *                                                                        *
 **************************************************************************/

if(typeof($)=='undefined')
	$={};

$._ext = {
    //Evaluate a file and catch the exception.
    evalFile : function(path) {
        try {
            $.evalFile(path);
        } catch (e) {alert("Exception:" + e);}
    },
    // Evaluate all the files in the given folder 
    evalFiles: function(jsxFolderPath) {
        var folder = new Folder(jsxFolderPath);
        if (folder.exists) {
            var jsxFiles = folder.getFiles("*.jsx");
            for (var i = 0; i < jsxFiles.length; i++) {
                var jsxFile = jsxFiles[i];
                $._ext.evalFile(jsxFile);
            }
        }
    }
};
