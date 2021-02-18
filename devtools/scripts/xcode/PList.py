#!/usr/bin/python
# PList.py - Dave MacLachlan (dmaclach@adobe.com) 2005/07/26
# Copyright (c) 2005 Adobe Systems Inc. 
# This software is covered by the Adobe Open Source License. Please see the end of
# this file for details.
# Metrowerks and Codewarrior are trademarks of Metrowerks, a Freescale company.
# Based on Property List Compiler by Metrowerks.
# Version 4+
#
# ===============================================================================
# Description
# ===============================================================================
# PList.py is a python script to compile .plc files into Plist files. More information on Plist files can be found here
# http://developer.apple.com/documentation/MacOSX/Conceptual/BPRuntimeConfig/index.html
# It uses a syntax that is extremely similar to the plc compiler that shipped with CodeWarrior albeit with a 
# few minor differences.
# I've included the entire docs below, but for those of you familiar with the plc compiler here are the
# differences from the Plist compiler that shipped with CodeWarrior 9.5
#
# - Does not support #message
# - The __MERGELINKER__, __MWMACHLINKER__, __MWPEFLINKER__, __IDE_TARGET__ defines are never set
# - The __APPLEMACHLINKER__, __MACH__ defines are always set to 1
# - The __PLIST__ define is set to the current version of this script plus 100 (i.e. 101 for version 1)
# - __XCODE__ is defined as 1
# - #pragma plist_version not supported. The plist version is always 1.0. 
# - #pragma output_encoding not supported. The output encoding for *.plist files is always UTF-8 and for *.strings is UTF-16.
# - #pragma mark not supported.
# - #pragma notonce not supported.
# - value for __OUTPUT_CREATOR__ is gotten from the PLC_OUTPUT_CREATOR environment variable or the creator argument
# - value for __OUTPUT_TYPE__ is gotten from the PLC_OUTPUT_TYPE environment variable or the type argument
# - value for __OUTPUT_FILENAME__ is gotten from the PRODUCT_NAME environment variable or the productName argument
# - "data file" syntax not supported
# - environment variable PLC_DEFINES will be added to the defines list
# - environment variable PLC_INCLUDES will be added to the includes path
# - environment variable PLC_PREFIX will be added as a prefix file
# - source file will be taken from environment variable INPUT_FILE_PATH
# - if environment variable PLC_GENERATE_PKGINFO_FILE is defined as YES, it will generate a PkgInfo file with __OUTPUT_TYPE__ & __OUTPUT_CREATOR__
# - the type of package being created is decided by the value ot the PACKAGE_TYPE environment variable. This should be set Xcode. You can also set this
#	using the -t option at the command line. See the description of the #pragma in_package_directory to understand how the package type defines
#	where files are put.
#
# ===============================================================================
# Version 2
# ===============================================================================
# - More errors and warnings due to bad/questionable input
# - Now handles frameworks, bundles, dylibs correctly as to the placement of output
# - Creates the Resources symlink in a framework if required (thanks to ariza)
# - Fixes up bug generating Strings files (thanks to brooks)
# - Fixed up bug with not specifying plistlib.Dict (thanks to bparadie)
# - Fixed up bug with not failing gracefully with errors during preprocessing (thanks to bparadie)
# - Better error reporting when failing in preprocessing (thanks to bparadie)
# - Cleans up tmp files better
#
# ===============================================================================
# Version 3
# ===============================================================================
# - Fixes a bug outputting strings where we didn't add a semicolon (thanks to mengler)
# - Reports its version number correctly when passed the --version
#
# ===============================================================================
# Version 4
# ===============================================================================
# - Now returns an error code appropriately, so failing plc compilation 
#	causes the xcode compile to fail
# - Strips quotes off of include paths properly
# - Gave ability to specify productName, creator and type from cmd line
# - Creates good default values for creator and type based on PACKAGE_TYPE
# - Added checks for productName
# ===============================================================================
# Version 4+
# ===============================================================================
# - This was fixed locally for InDesign.
# - Now handles escaped spaces in include paths properly.
#
# ===============================================================================
# Source Files
# ===============================================================================
# 
# Property list compiler source files are designated with the filename extension
# of ".plc".  The input to the compiler is just regular text, as with most any
# other type of compiler.
# 
# 
# ===============================================================================
# Preprocessor
# ===============================================================================
# 
# The property list compiler is modeled loosely on both the C and Rez languages
# in that it has a preprocessing phase and then a compile phase.  In the
# preprocessing phase, macros may be defined and additional source files may be
# included.  Defined macros are simple text replacements in the main source code.
# 
# Preprocessor definitions all occur on their own line.  The first non-whitespace
# character on the line must be #.  Following the #, there may (or may not) be
# other whitespace characters, followed by the preprocessor directive.
# 
# #include
# --------
# The #include directive tells the property list compiler to find another source
# file and insert it into the compilation stream.  There are two forms of the
# #include directive.  The format is:
# 
# #include "filename"
# or
# #include <filename>
# 
# The first form finds the file from the user access paths, the second form finds
# the file from the system access paths.
# 
# 
# #define
# -------
# The #define directive tells the property list compiler to define a macro.  The
# format is:
# 
# #define macro expansion-text
# 
# The compiler adds the macro, named by "macro" to its macro table.  Whenever the
# text of "macro" appears in the regular source stream, it will be replaced with
# expansion-text.
# 
# 
# #undef
# ------
# The #undef directive tells the property list compiler to forget about a macro
# that has been previously defined.  The format is:
# 
# #undef macro
# 
# 
# #ifdef
# ------
# The #ifdef directive tests for the definition of a compiler macro.  If the
# macro has been previously defined, the property list code immediately following
# the #ifdef directive is processed up until an #else or #endif directive.  If
# the macro has not been defined, the property list code immedately following the
# #ifdef directive is not processed.  If there is an #else directive, instead the
# code following the #else is processed until the #endif directive is found.  The
# #ifdef directive must be matched by an #endif directive.  Some examples are:
# 
# #ifdef macro
#    boolean true
# #endif
# 
# #ifdef macro
#    boolean true
# #else
#    boolean false
# #endif
# 
# 
# #ifndef
# -------
# The #ifndef directive is similar to the #ifdef directive, except that instead
# of testing for the definition of a macro, it tests for the non-definition of
# a macro.  If the macro is not defined, then the code immediately following the
# #ifndef directive is processed.
# 
# 
# #else
# -----
# The #else directive allows for two different cases of conditional compilation
# to be used with a single #ifdef or #ifndef test.
# 
# 
# #endif
# ------
# The #endif directive finalizes the #ifdef or #ifndef immediately preceeding it.
# 
# 
# #if
# ---
# The #if directive tests an expression.  If the expression evaluates to 1, the
# property list code immediately following teh #if directive is processed up until
# an #else, #elif, or #endif directive.  If the expression evaluates to 0, the
# property list code immediately following the #if directive is not processed.
# The #if directive must be matched by an #endif directive.  Some examples are:
# 
# #if 1
#    boolean true
# #endif
# 
# #if defined(abc)
#    boolean true
# #else
#    boolean false
# #endif
# 
# #if __IDE_TARGET__("Debug")
#    #define Debug_Item 1
# #endif
# 
# 
# #elif
# -----
# The #elif directive allows for multiple #if tests during the preprocessing
# stage.  Some examples are:
# 
# #if defined(abc)
#    string "abc is defined"
# #elif defined(def)
#    string "def is defined"
# #endif
# 
# #if defined(abc)
#    string "abc is defined"
# #elif defined(def)
#    string "def is defined"
# #elif defined(ghi)
#    string "ghi is defined"
# #endif
# 
# 
# #error
# ------
# The #error directive triggers a deliberate error condition.  This is most
# useful in combination with #ifdef and #ifndef to test for situations that
# should never occur.  An example is:
# 
# #ifndef __PLIST__
#    #error The property list compiler is not compiling this file!
# #endif
# 
# 
# #warning
# --------
# The #warning directive triggers a deliberate warning condition.  This is most
# useful in combination with #ifdef and #ifndef to test for situations that
# warrant programmer notification but do not stop the compile.  An example is:
# 
# #ifdef ExperimentalVersion
#    #warning Don't forget to fix this for the final version!
# #endif
# 
# #pragma
# -------
# The #pragma directive modifies the internal behavior of the property list
# compiler.  Each pragma is specified by a name and some optional parameters.
# 
# 
# #pragma output_filename
# -----------------------
# The output_filename pragma lets you override the specified output filename
# preference.  The valid option is a string specifying the new filename.  An
# example is:
# 
# #pragma output_filename "Info.plist"
# 
# 
# #pragma in_package_directory
# ----------------------------
# The in_package_directory pragma lets you tell where to place the property list
# file in the final package.  The option is a string which specifies the final
# directory.  The string is relative to the "Base" directory of the package.  Folders are always
# separated by a colon.  
# The Base directory for an application (com.apple.package-type.wrapper.application) or a bundle (com.apple.package-type.wrapper) is "Contents".
# The Base directory for a framework (com.apple.package-type.wrapper.framework)  is the "Resources" folder of the version you are building.
# The Base directory for a static lib (com.apple.package-type.static-library) or a dylib (com.apple.package-type.mach-o-dylib) is wherever the executable is being build.
# Some examples are:
# 
# #pragma in_package_directory "Resources"
# #pragma in_package_directory "Other_Folder:Another_Folder"
# 
# 
# #pragma localize_directory
# --------------------------
# The localize_directory pragma lets you tell where to place the localized string
# files in the final package.  The option is a string which specifies the final
# directory.  The string is relative to the "Base" directory of the package.  Folders are always
# separated by a colon. 
# The Base directory for an application (com.apple.package-type.wrapper.application) or a bundle (com.apple.package-type.wrapper) is "Contents".
# The Base directory for a framework (com.apple.package-type.wrapper.framework)  is the "Resources" folder of the version you are building.
# The Base directory for a static lib (com.apple.package-type.static-library) or a dylib (com.apple.package-type.mach-o-dylib) is wherever the executable is being build.
# In all cases the default for localize_directory is "Resources"
# Some examples are:
# 
# #pragma localize_directory "Other_Folder"
# #pragma localize_directory "Other_Folder:Another_Folder"
# 
# 
# #pragma once
# ------------
# The once pragma lets you control what happens when a file is included.  There
# are three forms of the pragma:
# 
# #pragma once
# #pragma once on
# #pragma once off
# 
# The '#pragma once' form tells the property list compiler to include the file
# currently being preprocessed only one time, even if later in the compile
# process another #include is done which will pull in the same file.
# 
# The '#pragma once on' form tells the property list compiler to include all
# files specified by an #include directive only one time.  (This can be
# overridden on a per-file basis using #pragma notonce.)
# 
# The '#pragma once off' form tells the property list compiler to include files
# multiple times as they appear in #include directives.  This is the default
# setting for the compiler.
# 
# 
# ===============================================================================
# Comments
# ===============================================================================
# 
# The property list compiler uses "//" as a comment to the end of a line, and
# anything within "/*" and "*/" is also considered a comment.  This is the same
# comment mechanism that Rez, C++, and C99 all use.
# 
# 
# ===============================================================================
# Property List Language
# ===============================================================================
# 
# The property list language is fairly simple.  It is simply a list of keywords
# separated by whitespace characters.  Some keywords specify that they are
# containers of other items (e.g. plist, array, dictionary).  Containers require
# beginning and ending symbols to delineate its content.  The plist and
# dictionary containers use { and } as its delineators, and the array container
# uses [ and ].
# 
# plist
# -----
# A property list source file starts off with the "plist" keyword.  Inside the
# plist body come additional keywords to describe the resulting property list.
# The simplest property list file, which specifies a completely empty property
# list, looks like this:
# 
# plist {}
# 
# 
# Inside the plist directive you should place a dictionary.  The property list
# compiler does not enforce this, but all valid property lists are a single
# dictionary.  Thus, the simplest valid property list looks like this:
# 
# plist
# {
# 	dictionary {}
# }
# 
# 
# dictionary
# ----------
# The "dictionary" directive lets you specify key/value pairs.  Each key is a
# string defining the key's name.  Key names must be unique within a single
# dictionary.  Values are any valid property list type (i.e. array, boolean,
# data, date, dictionary, number, or string).  The simplest dictionary is empty
# and looks like this:
# 
# dictionary {}
# 
# A dictionary with key/value pairs is defined by the keyword "key", a string
# specifying the key name, the keyword "value", then another valid property list
# type.  For example, a dictionary containing an empty dictionary specified by
# the key of "Bee sharp" looks like this:
# 
# dictionary
# {
# 	key "Bee sharp" value dictionary {}
# }
# 
# 
# boolean
# -------
# The "boolean" directive lets you specify a true or false value.  The boolean
# directive must be followed by the "true" or "false" keyword.  The only valid
# forms of the boolean directive are:
# 
# boolean true
# boolean false
# 
# 
# number
# ------
# The "number" directive lets you specify an integer or floating point numeric
# value.  The number directive must be followed by a single number.  Some valid
# number examples are:
# 
# number 0
# number 0.0
# number 1
# number -1
# number 1.0
# number -1.0
# number .1
# number -.1
# number 2.0e-4
# 
# 
# string
# ------
# The "string" directive lets you specify a string value.  The string directive
# must be followed by one or more character strings.  Character strings are
# enclosed in either single or double quotes.  If you want to have the quote
# character inside a string, you specify it by a backslash, then a quote.  If
# you want to have a backslash inside a string, you specify it by two
# backslashes.  Unicode values can be embedded in the string by specifying a
# backslash followed by a sequence of U and then four hexadecimal digits
# specifying the unicode value.  Two or more character strings after a string
# directive will be glued together in the final property list as one big string.
# Some valid string examples are:
# 
# string "simple string"
# string 'another simple string'
# string "this has a \" quote character"
# string 'this has a \' single quote character'
# string "this has a \\ backslash character"
# string "this has a unicode copyright character \U00A9 and a bullet \U2022"
# string "two strings"  " made as one"
# 
# 
# date
# ----
# The "date" directive lets you specify a date value.  The date directive must
# be followed by a single character string.  Character strings are enclosed in
# quotes.  All parts of the date value must be present when specifying a date.
# The format for a date is:
# 
# YYYY '-' MM '-' DD 'T' HH ':' MM ':' SS 'Z'
# 
# Some valid date examples are:
# 
# date "2002-12-18T12:00:00Z"
# date __DATE__
# 
# 
# array
# -----
# The "array" directive lets you specify an ordered list of property list types.
# Any valid property list type (i.e. array, boolean, data, date, dictionary,
# number, or string) may appear in an array.  The simplest array is empty and
# looks like this:
# 
# array []
# 
# An array containing a true boolean value and an empty array looks like this:
# 
# array
# [
# 	boolean true
# 	array []
# ]
# 
# 
# data
# ----
# The "data" directive lets you specify raw data values.  There are two forms for
# the data directive.  The first form takes one or more strings of characters and
# interprets them as hexadecimal values.  The second form takes a data file and
# places its contents in the property list.  Some valid data examples are:
# 
# data "00010203"
# data "00 01 02 03"
# data "00 01"  "02 03"
# data file "get_data_from_this_file"
# 
# 
# ===============================================================================
# Localization
# ===============================================================================
# 
# Following the plist {} directive may follow localization directives.  They are
# used to customize the string values present in the main property list
# dictionary.
# 
# localize "English" [ as "InfoPlist.strings" ]
# {
# 	comment "comment string"
# 	key "KEY_NAME" value string "localized string"
# }
# 
# Generally it's helpful to keep localizations separate from the main property
# list compiler source file and have the main localization file #include the
# localizations.  Separate localization files mays be designated with the
# filename extension of ".ploc".
# 
# 
# localize
# --------
# The "localize" directive lets you specify a list of key/value pairs to override
# string values for multiple languages in the main property list dictionary.
# Immediately following the localize directive is a string which represents the
# language for the localization.  Following that may come an optional "as"
# directive which specifies the name of the string file to hold the localied
# information.  If there is no "as" directive, the file will be called
# "InfoPlist.strings".  The simplest localize block is empty and looks like this:
# 
# localize "Region" {}
# 
# A localization block specifiying a different output name looks like this:
# 
# localize "Region" as "Region.strings" {}
# 
# The only items which are valid inside the braces of the localization directive
# are the comment and key/value directives.
# 
# 
# comment
# -------
# The "comment" directive lets you place a comment string to place inside the
# localization strings file.  The comment directive must be followed by one or
# more character strings.  Some valid comment examples are:
# 
# comment "simple comment"
# comment "this has a unicode copyright character \U00A9 and a bullet \U2022"
# comment "two strings"  " made as one"
# 
# key/value
# ---------
# The "key" directive lets you specify a key/value string pair to be placed
# inside the localization strings file.  The value must always be a string.
# Some valid key/value examples are:
# 
# key "CFBundleGetInfoString" value string "Local Get Info"
# key "CFBundleShortVersionString" value string "Local Short Version"
# 
# 
# Some examples of valid localization directives are as follows:
# 
# localize "English"
# {
# 	comment "Localized versions of Info.plist keys"
# 	key "CFBundleName" value string "Calculator"
# }
# 
# localize "French"
# {
# 	comment "Localized versions of Info.plist keys"
# 	key "CFBundleName" value string "Calculette"
# }
# 
# localize "Spanish"
# {
# 	comment "Localized versions of Info.plist keys"
# 	key "CFBundleName" value string "Calculadora"
# }
# 
# localize "German"
# {
# 	comment "Localized versions of Info.plist keys"
# 	key "CFBundleName" value string "Rechner"
# }
# 
# 
# ===============================================================================
# Keywords
# ===============================================================================
# 
# The property list compiler recognizes the following preprocessor directives:
# 
# #define
# #elif
# #else
# #endif
# #error
# #if
# #ifdef
# #ifndef
# #include
# #pragma
# #warning
# 
# 
# The property list compiler recognizes the following keywords:
# 
# as
# array
# boolean
# comment
# data
# date
# dictionary
# false
# file
# key
# localize
# number
# plist
# string
# true
# value
# 
# 
# ===============================================================================
# Predefined Macros
# ===============================================================================
# 
# The property list compiler reserves all macro definitions that begin and end
# with double underscores.  The following macros are predefined:
# 
# __PLIST__
# The __PLIST__ macro is defined to the current version number of the Property
# List Compiler.
# 
# __DATE__
# The __DATE__ macro is defined to be a string containing the date and time when
# the property list source file is compiled.  The format is valid for use with
# the date directive.
# 
# __FILE__
# The __FILE__ macro is defined to be a string containing the filename of the
# property list source file that is being compiled.  It changes whenever there
# is an #include directive to pull in a new file.
# 
# __LINE__
# The __LINE__ macro is defined to be a string containing the current line
# number of the the property list source file that is being compiled.  It
# changes for each line of source code that passes through the compiler.
# 
# __STRING__()
# The __STRING__() macro is a special preprocessing directive.  It converts
# whatever token is inside the parenthesis into a string value.  Some examples
# are:  __STRING__(1.0) generates "1.0", and #define kVersion 1.0 followed by
# a __STRING__(kVersion) would also generate a "1.0".
# 
# __OUTPUT_CREATOR__
# The __OUTPUT_CREATOR__ macro is defined to be a string containing the creator
# type as is set for the current target.  The value for this macro is gotten
# from the PLC_OUTPUT_CREATOR environment variable. It defaults to "__OUTPUT_CREATOR__"
# 
# __OUTPUT_TYPE__
# The __OUTPUT_TYPE__ macro is defined to be a string containing the file type
# as is set for the current target.  The value for this macro is gotten
# from the PLC_OUTPUT_TYPE environment variable. It defaults to "__OUTPUT_TYPE__"
# 
# __OUTPUT_FILENAME__
# The __OUTPUT_FILENAME__ macro is defined to be a string containing the filename
# as is set for the current target.  The value for this macro is gotten
# from the PRODUCT_NAME environment variable. It defaults to "__OUTPUT_FILENAME__"
# 
# __MACH__
# The __MACH__ macro is defined to 1
# 
# __APPLEMACHLINKER__
# The __APPLEMACHLINKER__ macro is defined to 1
#
# __XCODE__
# The __XCODE__ macro is defined to 1



import sys
import re
import plistlib
import codecs
import os
import tempfile
import time

from optparse import OptionParser
from os.path import *

# kPListCompilerVersion is version + 100
kPListCompilerVersion = 105
xcodePath = '/Applications/Xcode.app/Contents/Developer'

(theOutFile, theXcodeselectOutFile) = tempfile.mkstemp();

theXcodeselectCmd = "xcode-select -print-path 1>\"%s\"" % theXcodeselectOutFile
theErr = os.system(theXcodeselectCmd)
if theErr == 0:
	try:
		xcodePath = file(theXcodeselectOutFile).read()
		xcodePath = xcodePath[:-1]
	finally:
		os.unlink(theXcodeselectOutFile);
else:
	raise PreprocessingError("xcode-select error %s" % theXcodeselectOutFile.read())

gccPath = xcodePath + '/usr/bin/gcc'

#sys.stderr.write("%s: %s\n" % ("GCC path", gccPath))

#exceptions
class PListError(Exception): pass

class BadArgsError(PListError):
	def __init__(self,string) : 
		self.string = string

class BadInputFileError(PListError):
	def __init__(self,string) : 
		self.string = string
		
class PreprocessingError(PListError):
	def __init__(self,string) : 
		self.string = string
		
class ParseError(PListError):
	def __init__(self,string, file, line) : 
		self.string = string
		self.file = file
		self.line = line
	pass

#stack utility class
class Stack : 
	def __init__(self) : 
		self.items = [] 

	def push(self, item) : 
		self.items.append(item) 

	def pop(self) : 
		return self.items.pop() 

	def isEmpty(self) : 
		return (self.items == []) 
	
	def top(self) :
		if self.isEmpty():
			return None
		else:
			return self.items[-1]

#PList Generator class
class PlistGenerator:

	def __init__(self):
		self.stack = []
		self.currentKey = None
		self.root = None
		
	def addObject(self, value):
		if self.currentKey is not None:
			self.stack[-1][self.currentKey] = value
			self.currentKey = None
		elif not self.stack:
			# this is the root object
			assert self.root is value
		else:
			self.stack[-1].append(value)

	def getPlist(self):
		return self.root
		
	# element handlers

	def begin_dictionary(self):
		if self.root is None:
			self.root = d = plistlib.Plist()
		else:
			d = plistlib.Dict()
		self.addObject(d)
		self.stack.append(d)
	
	def end_dictionary(self):
		self.stack.pop()

	def add_key(self, inKey):
		self.currentKey = inKey

	def begin_array(self):
		a = []
		self.addObject(a)
		self.stack.append(a)
		
	def end_array(self):
		self.stack.pop()

	def add_true(self):
		self.addObject(True)
	def add_false(self):
		self.addObject(False)
	def add_integer(self, inInt):
		self.addObject(int(inInt))
	def add_real(self, inReal):
		self.addObject(float(inReal))
	def add_string(self, inString):
		self.addObject(unicode(inString,"utf-8"))
	def add_data(self, inData):
		self.addObject(Data.fromBase64(inData))
	def end_date(self, inDate):
		self.addObject(Date(inDate))
		
#Locale Generator class
class LocaleGenerator:

	def __init__(self, inLocale, inFileName="InfoPlist.strings"):
		self.str = unicode("","utf-16")
		self.locale = inLocale
		self.fileName = inFileName
	
	def write(self, inResourcePath):
		thePath = inResourcePath + "/" + self.locale + ".lproj/"
		if not exists(thePath):
			os.mkdir(thePath)	
		thePath += self.fileName
		theFile = codecs.open(thePath, "w", "utf-16")
		theFile.write(self.str)
		
	# element handlers
	
	def add_string(self, inKey, inString):
		theString = "%s = \"%s\";\n" % (inKey, inString)
		theString = unicode(theString,"utf-8")
		self.str += theString
		
	def add_comment(self, inComment):
		theString = "/* %s */\n" % inComment
		theString = unicode(theString,"utf-8")
		self.str += theString
		
# Token matching

def ConvertPLCStringToUTF8(inString):
	# Known potential bug...if string has a \\u in it for some weird reason, we will try and convert it and
	# it could cause issues
	newString = inString.replace("\U","\u")
	newString = unicode(newString, "unicode_escape")
	return newString.encode("utf-8")

def MatchRE(inString, inRE):
	theMatch = inRE.match(inString)
	theAnswer = ""
	theLength = 0
	if theMatch:
		theAnswer = theMatch.group(1)
		theLength = len(theMatch.group(0))
	return theAnswer, theLength

def MatchInclude(inString):
	includeRE = re.compile("\"(.*?)\"[ 0-9]*[ \t]*")
	return MatchRE(inString,includeRE)
	
def MatchLine(inString):
	lineRE = re.compile("[ \t]*(.*)")
	return MatchRE(inString,lineRE)
		
def MatchString(inString):
	stringRE = re.compile("[ \t]*\"(.*?)\"[ \t]*")
	return MatchRE(inString,stringRE)

def MatchNumber(inString):
	numberRE = re.compile("[ \t]*([-+]?(?:[0-9]*\.)?[0-9]+(?:[eE][-+]?[0-9]+)?)[ \t]*")
	return MatchRE(inString, numberRE)
	
def MatchMultiString(inString):
	theAnswer = ""
	theNewLen = 1
	theLength = 0
	theTotalLen = len(inString)
	while theNewLen != 0:
		theRest, theNewLen = MatchString(inString[theLength:theTotalLen])
		theAnswer += theRest
		theLength += theNewLen
	return theAnswer, theLength

def UTF8MatchMultiString(inString):
	a,b = MatchMultiString(inString)
	return ConvertPLCStringToUTF8(a),b

def ErrorString(inString, inFile=None, inLine=None):
	StatusString("Error",inString, inFile, inLine)
	
def WarningString(inString, inFile=None, inLine=None):
	StatusString("Warning",inString, inFile, inLine)
	
def StatusString(inStatus,inString, inFile=None, inLine=None):
	if inFile != None:
		 sys.stderr.write("%s: %s\n\tStatement: %s \n\tFile:%s\n" % (inStatus,inString,inLine,inFile))
	else:
		sys.stderr.write("%s: %s\n" % (inStatus,inString))
	
AS_TOK = 17
ARRAY_TOK = 12
BOOLEAN_TOK = 8
COMMENT_TOK = 16
DATA_TOK = 15
DATE_TOK = 11
DICTIONARY_TOK = 5
FALSE_TOK = 19
FILE_TOK = 18
KEY_TOK = 6
LOCALIZE_TOK = 4
NUMBER_TOK = 9
PLIST_TOK = 1
STRING_TOK = 10
TRUE_TOK = 20
VALUE_TOK = 7

OPENCURLYBRACE_TOK = 2
CLOSECURLYBRACE_TOK = 3
OPENSQUARE_TOK = 13
CLOSESQUARE_TOK = 14

INCLUDE_TOK = 21
PRAGMA_OUTPUT_FILENAME_TOK = 22
PRAGMA_IN_PACKAGE_DIRECTORY_TOK = 23
PRAGMA_LOCALIZE_DIRECTORY_TOK = 24
PRAGMA_TOK = 25
WARNING_TOK = 26
DONE_TOK = 27

class TokenAction : 
	def __init__(self,token,string,action) : 
		self.token = token
		self.string = string
		self.action = action
		
		
TokenActionArray = [ TokenAction(AS_TOK,"as" ,UTF8MatchMultiString),
	TokenAction(AS_TOK, "as", UTF8MatchMultiString),
	TokenAction(ARRAY_TOK, "array", None),
	TokenAction(BOOLEAN_TOK, "boolean", None),
	TokenAction(COMMENT_TOK, "comment", UTF8MatchMultiString),
	TokenAction(DATA_TOK, "data", UTF8MatchMultiString),
	TokenAction(DATE_TOK, "date", None),
	TokenAction(DICTIONARY_TOK, "dictionary", None),
	TokenAction(FALSE_TOK, "false", None),
	TokenAction(FILE_TOK, "file", None),
	TokenAction(KEY_TOK, "key", UTF8MatchMultiString),
	TokenAction(LOCALIZE_TOK, "localize", UTF8MatchMultiString),
	TokenAction(NUMBER_TOK, "number", MatchNumber),
	TokenAction(PLIST_TOK, "plist", None),
	TokenAction(STRING_TOK, "string", UTF8MatchMultiString),
	TokenAction(TRUE_TOK, "true", None),
	TokenAction(VALUE_TOK, "value", None),
	TokenAction(OPENCURLYBRACE_TOK, "\{", None),
	TokenAction(CLOSECURLYBRACE_TOK, "\}", None),
	TokenAction(OPENSQUARE_TOK, "\[", None),
	TokenAction(CLOSESQUARE_TOK, "\]", None),
	TokenAction(PRAGMA_OUTPUT_FILENAME_TOK, "\#[ \t]*pragma[ \t]*output_filename", UTF8MatchMultiString),
	TokenAction(PRAGMA_IN_PACKAGE_DIRECTORY_TOK, "\#[ \t]*pragma[ \t]*in_package_directory", UTF8MatchMultiString),
	TokenAction(PRAGMA_LOCALIZE_DIRECTORY_TOK, "\#[ \t]*pragma[ \t]*localize_directory", UTF8MatchMultiString),
	TokenAction(PRAGMA_TOK, "\#[ \t]*pragma[ \t]*", MatchLine),
	TokenAction(WARNING_TOK, "\#[ \t]*warning[ \t]*", MatchLine),
	TokenAction(INCLUDE_TOK, "\#[ \t]*[0-9]*[ \t]*", MatchInclude),
	TokenAction(DONE_TOK, None, None)
]	

class ParseData : 
	def __init__(self, inFile) : 
		self.plist = None
		self.locales = []
		self.sourceFile = inFile
		self.outputFileName = "Info.plist"
		self.inPackageDirectory = ""
		self.localizeDirectory = "Resources"
		
class TokenValue :
	def __init__(self,token,value, line) : 
		self.token = token
		self.value = value
		self.line = line
		
#state matching
def ArrayArrayOpen(inTokens, inCurrToken, inData):
	inData.plist.begin_array()
	
def ArrayBoolTrue(inTokens, inCurrToken, inData):
	inData.plist.add_true()

def ArrayBoolFalse(inTokens, inCurrToken, inData):
	inData.plist.add_false()

def ArrayData(inTokens, inCurrToken, inData):
	inData.plist.add_data(inTokens[inCurrToken].value)

def ArrayDataFile(inTokens, inCurrToken, inData):
	
	#inData.plist.add_data(inTokens[inCurrToken].value)
	raise ParseError("data file syntax not supported", inData.sourceFile, inTokens[inCurrToken].line)

def ArrayDate(inTokens, inCurrToken, inData):
	inData.plist.add_date(inTokens[inCurrToken].value)

def ArrayDictionaryOpen(inTokens, inCurrToken, inData):
	inData.plist.begin_dictionary()

def ArrayNumber(inTokens, inCurrToken, inData):
	if inTokens[inCurrToken].value.find("e") != -1 or inTokens[inCurrToken].value.find("E") != -1 or inTokens[inCurrToken].value.find(".") != -1:
		inData.plist.add_real(inTokens[inCurrToken].value)
	else:
		inData.plist.add_integer(inTokens[inCurrToken].value)

def ArrayString(inTokens, inCurrToken, inData):
	inData.plist.add_string(inTokens[inCurrToken].value)

def ArrayClose(inTokens, inCurrToken, inData):
	inData.plist.end_array()

def DictionaryArrayOpen(inTokens, inCurrToken, inData):
	inData.plist.add_key(inTokens[inCurrToken].value)
	inData.plist.begin_array()
	
def DictionaryBoolTrue(inTokens, inCurrToken, inData):
	inData.plist.add_key(inTokens[inCurrToken].value)
	inData.plist.add_true()

def DictionaryBoolFalse(inTokens, inCurrToken, inData):
	inData.plist.add_key(inTokens[inCurrToken].value)
	inData.plist.add_false()

def DictionaryData(inTokens, inCurrToken, inData):
	inData.plist.add_key(inTokens[inCurrToken].value)
	inData.plist.add_data(inTokens[inCurrToken + 2].value)

def DictionaryDataFile(inTokens, inCurrToken, inData):
	#inData.plist.add_key(inTokens[inCurrToken].value)
	#inData.plist.add_data(inTokens[inCurrToken + 2].value)
	raise ParseError("data file syntax not supported", inData.sourceFile, inTokens[inCurrToken].line)

def DictionaryDate(inTokens, inCurrToken, inData):
	inData.plist.add_key(inTokens[inCurrToken].value)
	inData.plist.add_date(inTokens[inCurrToken + 2].value)

def DictionaryDictionaryOpen(inTokens, inCurrToken, inData):
	inData.plist.add_key(inTokens[inCurrToken].value)
	inData.plist.begin_dictionary()

def DictionaryNumber(inTokens, inCurrToken, inData):
	inData.plist.add_key(inTokens[inCurrToken].value)
	if inTokens[inCurrToken+2].value.find("e") != -1 or inTokens[inCurrToken+2].value.find("E") != -1 or inTokens[inCurrToken+2].value.find(".") != -1:
		inData.plist.add_real(inTokens[inCurrToken+2].value)
	else:
		inData.plist.add_integer(inTokens[inCurrToken+2].value)


def DictionaryString(inTokens, inCurrToken, inData):
	inData.plist.add_key(inTokens[inCurrToken].value)
	inData.plist.add_string(inTokens[inCurrToken + 2].value)

def DictionaryClose(inTokens, inCurrToken, inData):
	inData.plist.end_dictionary()
	
def PlistDictionaryOpen(inTokens, inCurrToken, inData):
	inData.plist.begin_dictionary()

def BasePlistOpen(inTokens, inCurrToken, inData):
	inData.plist = PlistGenerator()

def BaseLocalizeOpen(inTokens, inCurrToken, inData):
	inData.locales.append(LocaleGenerator(inTokens[inCurrToken].value))
	pass

def BaseLocalizeAsOpen(inTokens, inCurrToken, inData):
	inData.locales.append(LocaleGenerator(inTokens[inCurrToken].value), inTokens[inCurrToken + 1].value)
	pass
	
def AnyPragmaOutputFileName(inTokens, inCurrToken, inData):
	theString = (inTokens[inCurrToken].value).replace(":","/")
	inData.outputFileName = theString
	
	
def AnyPragmaInPackageDirectory(inTokens, inCurrToken, inData):
	theString = (inTokens[inCurrToken].value).replace(":","/")
	inData.inPackageDirectory = theString


def AnyPragmaLocalizeDirectory(inTokens, inCurrToken, inData):
	theString = (inTokens[inCurrToken].value).replace(":","/")
	inData.localizeDirectory = theString
	
def AnyPragma(inTokens, inCurrToken, inData):
	WarningString("Illegal Pragma", inData.sourceFile, inTokens[inCurrToken].line)

def AnyInclude(inTokens, inCurrToken, inData):
	inData.sourceFile = inTokens[inCurrToken].value

def AnyWarning(inTokens, inCurrToken, inData):
	WarningString(inTokens[inCurrToken].value, inData.sourceFile, inTokens[inCurrToken].line)

def LocalizeComment(inTokens, inCurrToken, inData):
	inData.locales[-1].add_comment(inTokens[inCurrToken].value)
	

def LocalizeString(inTokens, inCurrToken, inData):
	inData.locales[-1].add_string(inTokens[inCurrToken].value, inTokens[inCurrToken + 2].value)
	

BASE_STATE = 0
PLIST_STATE = 1
ARRAY_STATE = 2
DICTIONARY_STATE = 3
LOCALIZE_STATE = 4
POP = 5
NOCHANGE = 6

class TokenStateAction :
	def __init__(self,tokens,state,action) : 
		self.tokens = tokens
		self.state = state
		self.action = action
		
ArrayState = [
	 TokenStateAction( [ ARRAY_TOK, OPENSQUARE_TOK ], ARRAY_STATE,  ArrayArrayOpen ),
	 TokenStateAction( [ BOOLEAN_TOK, TRUE_TOK ], NOCHANGE,  ArrayBoolTrue ),
	 TokenStateAction( [ BOOLEAN_TOK, FALSE_TOK ], NOCHANGE,  ArrayBoolFalse ),
	 TokenStateAction( [ DATA_TOK ], NOCHANGE,  ArrayData ),
	 TokenStateAction( [ DATA_TOK, FILE_TOK ], NOCHANGE,  ArrayDataFile ),
	 TokenStateAction( [ DATE_TOK ], NOCHANGE,  ArrayDate ),
	 TokenStateAction( [ DICTIONARY_TOK, OPENCURLYBRACE_TOK ], DICTIONARY_STATE,  ArrayDictionaryOpen ),
	 TokenStateAction( [ NUMBER_TOK ], NOCHANGE,  ArrayNumber ),
	 TokenStateAction( [ STRING_TOK ], NOCHANGE,  ArrayString ),
	 TokenStateAction( [ CLOSESQUARE_TOK ], POP,  ArrayClose )
]

DictionaryState = [
	 TokenStateAction( [ KEY_TOK, VALUE_TOK, ARRAY_TOK, OPENSQUARE_TOK ], ARRAY_STATE,  DictionaryArrayOpen ),
	 TokenStateAction( [ KEY_TOK, VALUE_TOK, BOOLEAN_TOK, TRUE_TOK ], NOCHANGE, DictionaryBoolTrue ),
	 TokenStateAction( [ KEY_TOK, VALUE_TOK, BOOLEAN_TOK, FALSE_TOK ], NOCHANGE, DictionaryBoolFalse ),
	 TokenStateAction( [ KEY_TOK, VALUE_TOK, DATA_TOK ], NOCHANGE,  DictionaryData ),
	 TokenStateAction( [ KEY_TOK, VALUE_TOK, DATE_TOK ], NOCHANGE,  DictionaryDate ),
	 TokenStateAction( [ KEY_TOK, VALUE_TOK, DICTIONARY_TOK, OPENCURLYBRACE_TOK ], DICTIONARY_STATE,  DictionaryDictionaryOpen ),
	 TokenStateAction( [ KEY_TOK, VALUE_TOK, NUMBER_TOK ], NOCHANGE,  DictionaryNumber ),
	 TokenStateAction( [ KEY_TOK, VALUE_TOK, STRING_TOK ], NOCHANGE,  DictionaryString ),
	 TokenStateAction( [ CLOSECURLYBRACE_TOK ], POP,  DictionaryClose  )
]
	
LocalizeState = [
	 TokenStateAction( [ COMMENT_TOK ], NOCHANGE,  LocalizeComment ),
	 TokenStateAction( [ KEY_TOK, VALUE_TOK, STRING_TOK ], NOCHANGE,  LocalizeString ),
	 TokenStateAction( [ CLOSECURLYBRACE_TOK ], POP,  None ),
]

PListState = [
	 TokenStateAction( [ DICTIONARY_TOK, OPENCURLYBRACE_TOK ], DICTIONARY_STATE,  PlistDictionaryOpen ),
	 TokenStateAction( [ CLOSECURLYBRACE_TOK ], POP,  None ),
]

BaseState = [
	 TokenStateAction( [ PLIST_TOK, OPENCURLYBRACE_TOK ],  PLIST_STATE,  BasePlistOpen ),
	 TokenStateAction( [ LOCALIZE_TOK, OPENCURLYBRACE_TOK ], LOCALIZE_STATE,  BaseLocalizeOpen ),
	 TokenStateAction( [ LOCALIZE_TOK, AS_TOK, OPENCURLYBRACE_TOK ], LOCALIZE_STATE,  BaseLocalizeAsOpen )

]

AnyState = [
	TokenStateAction( [ PRAGMA_OUTPUT_FILENAME_TOK ], NOCHANGE,  AnyPragmaOutputFileName ),
	TokenStateAction( [ PRAGMA_IN_PACKAGE_DIRECTORY_TOK ], NOCHANGE,  AnyPragmaInPackageDirectory ),
	TokenStateAction( [ PRAGMA_LOCALIZE_DIRECTORY_TOK ], NOCHANGE,  AnyPragmaLocalizeDirectory ),
	TokenStateAction( [ PRAGMA_TOK ], NOCHANGE,  AnyPragma ),
	TokenStateAction( [ INCLUDE_TOK ], NOCHANGE,  AnyInclude ),
	TokenStateAction( [ WARNING_TOK ], NOCHANGE,  AnyWarning ),
]

States = [ BaseState ,PListState, ArrayState, DictionaryState, LocalizeState ]
		

		
def ParseTokens(inTokens,inFile):
	curState = Stack()
	curState.push(BASE_STATE)
	curToken = 0
	theToken = inTokens[curToken]
	theData = ParseData(inFile)
	
	while theToken.token != DONE_TOK:
		theStates = States[curState.top()] + AnyState
		for state in theStates:
			tempToken = curToken
			for token  in state.tokens:
				if token != inTokens[tempToken].token:
					break
				tempToken += 1
			else:
				# Found our sequence
				# do we need to push a state
				if state.state == NOCHANGE:
					pass
				elif state.state == POP:
					curState.pop();
				else:
					curState.push(state.state)
				#Need to do an action
				if state.action != None:
					state.action(inTokens, curToken, theData)
					
				#need to move forward
				curToken = tempToken
				theToken = inTokens[curToken]
				break
		else:
			raise ParseError("Syntax Error", theData.sourceFile, inTokens[curToken].line)
	if curState.top() != BASE_STATE:
		raise ParseError("Syntax Error", theData.sourceFile, inTokens[curToken].line)
	return theData
		
def Tokenize(inString,inFile):
	outTokens = []
	curChar = 0
	curLine = 0
	curFile = inFile
	length = len(inString)
	theLines =  inString.splitlines()
	while curChar < length:
		curTok = 0
		while TokenActionArray[curTok].token != DONE_TOK:
			theMatch = re.compile(TokenActionArray[curTok].string).match(inString,curChar)
			if theMatch:
				curChar += len(theMatch.group(0))
				if TokenActionArray[curTok].action == None:
					theMatch = TokenActionArray[curTok].string
					theLength = 0
				else:
					theMatch, theLength = TokenActionArray[curTok].action(inString[curChar:length])
				outTokens.append(TokenValue(TokenActionArray[curTok].token, theMatch,theLines[curLine]))
				curChar += theLength
				if TokenActionArray[curTok].token == INCLUDE_TOK:
					if theMatch != "":
						curFile = theMatch
				break
			else:
				curTok += 1
		if TokenActionArray[curTok].token == DONE_TOK:
			if inString[curChar] == "\n":
				curChar = curChar + 1
				curLine = curLine + 1
			elif inString[curChar] == "\t" or inString[curChar] == " ":
				curChar = curChar + 1
			else:
				raise ParseError("Syntax Error", curFile, theLines[curLine])
	outTokens.append(TokenValue(DONE_TOK,"",""))
	return outTokens
	
def ParsePLC(inFile, inIncludePaths, inDefines, inPrefixes, creator, type, productName):
	builtInDefines = [
		"__PLIST__=%d" % kPListCompilerVersion, # Plist version
		"__APPLEMACHLINKER__=1", # We're using the AppleMachLinker
		"__MACH__=1", # We're compiling for MACH
		"__INTERNAL_STRING__\(x\)=#x",
		"__STRING__\(x\)=__INTERNAL_STRING__\(x\)", # This will stringify things for us
		"__OUTPUT_CREATOR__=\"\\\"%s\\\"\"" % creator,
		"__OUTPUT_TYPE__=\"\\\"%s\\\"\"" % type,
		"__OUTPUT_FILENAME__=\"\\\"%s\\\"\"" % productName,
		"__XCODE__=1",
	]
	(theOutFile, thePreProcessOut) = tempfile.mkstemp();
	
	theErrFile = tempfile.NamedTemporaryFile();
	thePreProcess = gccPath + " -E -x c++ -o \"%s\"" % thePreProcessOut
	for b in inIncludePaths:
		thePreProcess = thePreProcess + " -I \"%s\"" % b
	for b in inDefines + builtInDefines:
		thePreProcess = thePreProcess + " -D" + b
	for b in inPrefixes:
		thePreProcess = thePreProcess + " -include \"%s\"" % b
	thePreProcess = thePreProcess + " \"%s\" 2> %s" % (inFile,theErrFile.name)
	theErr = os.system(thePreProcess)
	if theErr == 0:
		try:
			theString = file(thePreProcessOut).read()
			theTokens = Tokenize(theString, inFile)
			theData = ParseTokens(theTokens,inFile)
		finally:
			os.unlink(thePreProcessOut);
	else:
		raise PreprocessingError("Preprocessing Error %s" % theErrFile.read())
		
	return theData
		
def FullPath(inPath):
	outPath = ""
	if inPath != "":
		outPath = expandvars(inPath)
		outPath = expanduser(outPath)
		outPath = abspath(outPath)
	return outPath

def SplitPaths(inString):
	newString = inString.replace("\\ ","~!@DM@!~")
	theRE = re.compile("(?:\".*\")|\S*")
	theFinds = theRE.findall(newString)
	theNewFinds = []
	for b in theFinds:
		if len(b) != 0:
			theNewFinds += [b.replace("~!@DM@!~"," ")]
	return theNewFinds

def DoPackage(inContentsPath, inCreator, inType):
	theFile = file(inContentsPath + "/PkgInfo","w")
	theFile.write(inType+inCreator)
	theFile.close
	
def Main():
	try:
		versionString = "%%prog %.2f Dave MacLachlan(dmaclach@adobe.com)" % (kPListCompilerVersion / 100.0)
		parser = OptionParser(usage="%prog [-I] [-D] [-p] [-P] [-tcom.apple.package-type.*] [-C creator] [-T type] [-o dstBundleDir] [-n productName] [src.plc]", version=versionString)
		parser.add_option("-p", "--prefix", action="append", type="string", dest="prefixes", help="Prefix files", default=[])
		parser.add_option("-I", "--includes", action="append", type="string", dest="includes", help="List of places to include files from", default=["."])
		parser.add_option("-D", "--define", action="append", type="string", dest="defines", help="List of defines", default=[])
		parser.add_option("-o", "--output", type="string", dest="output", help="destination bundle root", default="")
		parser.add_option("-C", "--creator", type="string", dest="creator", help="creator signature", default="")
		parser.add_option("-T", "--type", type="string", dest="type", help="type signature", default="")
		parser.add_option("-n", "--productName", type="string", dest="productName", help="name of the product", default="")
		parser.add_option("-P", "--package", action="store_true", dest="package", help="create pkginfo file", default=False)
		parser.add_option("-t", "--packagetype", type="string", dest="packageType", help="Type of package the plist is being compiled for.\ncom.apple.package-type.wrapper -> bundle\tcom.apple.package-type.wrapper.application -> app\ncom.apple.package-type.wrapper.framework -> framework\ncom.apple.package-type.static-library -> static lib\ncom.apple.package-type.mach-o-dylib -> macho dylib", default="")
		(options,args) = parser.parse_args(sys.argv[1:])
		
		inputFilePath = ""
		if len(args) == 0:
			inputFilePath = FullPath(os.getenv("INPUT_FILE_PATH",""))
		elif len(args) == 1:
			inputFilePath = FullPath(args[0])
				
		if len(inputFilePath) == 0:
			raise BadArgsError("Parameter Error\n\tYou must have a src.plc file, or set the INPUT_FILE_PATH environment variables")
					
		if len(options.output) == 0:
			outputFilePath = os.getenv("TARGET_BUILD_DIR","")
			if len(outputFilePath) > 0:
				newPath = os.getenv("FULL_PRODUCT_NAME","")
				if len(newPath) > 0:
					outputFilePath += "/" + newPath
				else:
					outputFilePath = ""
		else:	
			outputFilePath = FullPath(options.output)
					
		if len(outputFilePath) == 0:
			raise BadArgsError("Parameter Error\n\tYou must have a dstBundleDir, or set the TARGET_BUILD_DIR,FULL_PRODUCT_NAME environment variables")
		
		if not exists(inputFilePath):
			raise BadInputFileError("File Not Found\n\tInput file: %s does not exist.\n" % inputFilePath)
		
		productName = options.productName
		if len(productName) == 0:
			productName = os.getenv("PRODUCT_NAME","")
		
		if len(productName) == 0:
			raise BadArgsError("Parameter Error\n\tYou must have a productName, or set the PRODUCT_NAME environment variable")
			
		for b in options.includes:
			b = FullPath(b)
			if not exists(b):
				WarningString("Path Not Found\n\tInclude path %s does not exist.\n" % b)
		
		otherDefines = os.getenv("PLC_DEFINES","").split()
		otherIncludes = SplitPaths(os.getenv("PLC_INCLUDES",""))
		otherPrefixes = SplitPaths(os.getenv("PLC_PREFIX",""))
		expandedIncludes = []
		for b in otherIncludes:
			b = b.strip("\"\'")
			if b.endswith("**"):
				basepath = b.rstrip("*")
				folders = os.walk(basepath)
				try:
					while 1:
						newFolder = folders.next()
						expandedIncludes += [newFolder[0]]
				except StopIteration:
					pass
			else:
				expandedIncludes += [b]
		
		if options.packageType != "":
			packageType = options.packageType
		else:
			packageType = os.getenv("PACKAGE_TYPE","").strip().lower()
		
		if options.creator != "":
			creator = options.creator
		else:
			creator = os.getenv("PLC_OUTPUT_CREATOR","????")

		if options.type != "":
			type = options.type
		else:
			type = os.getenv("PLC_OUTPUT_TYPE","")
			if type == "":
				if packageType == "com.apple.package-type.wrapper.framework":
					#for a framework we want the default type to be "FMWK"	
					type = "FMWK"
				elif packageType == "com.apple.package-type.wrapper.application":
					type = "APPL"
				elif packageType == "com.apple.package-type.wrapper":
					type = "BNDL"
				else:
					type = "????"
		
		theData = ParsePLC(inputFilePath, options.includes + expandedIncludes, options.defines + otherDefines, options.prefixes + otherPrefixes, creator, type, productName)
		
		if packageType == "com.apple.package-type.wrapper" or packageType == "com.apple.package-type.wrapper.application":
			#bundle or application
			outputFileContentsPath = outputFilePath + "/Contents"
			outputFileResourcesPath = outputFileContentsPath + "/" + theData.localizeDirectory
			outputFileContentsPath += "/" + theData.inPackageDirectory
		elif packageType == "com.apple.package-type.wrapper.framework":
			#framework
			outputFileSymlinkPath = "/Versions/" + os.getenv("FRAMEWORK_VERSION","A") 
			outputFileContentsPath = outputFilePath + outputFileSymlinkPath + "/Resources/" + theData.inPackageDirectory
			outputFileSymlinkPath += "/" + theData.localizeDirectory
			outputFileResourcesPath = outputFilePath + outputFileSymlinkPath
			outputFileSymlinkPath = "." + outputFileSymlinkPath
		elif packageType == "com.apple.package-type.static-library" or packageType == "com.apple.package-type.mach-o-dylib":
			#static lib or machoDylib
			outputFileContentsPath = outputFilePath + "/" + theData.inPackageDirectory
			outputFileResourcesPath = outputFilePath + "/" + theData.localizeDirectory
		else:
			#unknown package type
			#spit out a warning
			if packageType != "":
				WarningString("Unknown package-type: %s." % packageType)
			else:
				WarningString("No package type specified. Please add a -t option to your command")
			
			outputFileContentsPath = outputFilePath + "/" + theData.inPackageDirectory
			outputFileResourcesPath = outputFilePath + "/" + theData.localizeDirectory
			
		
		if not exists(outputFileContentsPath):
			try:
				os.makedirs(outputFileContentsPath)
			except OSError, e:
				time.sleep(10)
				if not exists(outputFileContentsPath):
					ErrorString(e.string)

		outputFile = file(outputFileContentsPath + "/" + theData.outputFileName, "w")
				
		if not exists(outputFileResourcesPath):
			try:
				os.makedirs(outputFileResourcesPath)
			except OSError, e:
				time.sleep(10)
				if not exists(outputFileResourcesPath):
					ErrorString(e.string)
		
		if packageType == "com.apple.package-type.wrapper.framework":
			#if it's a framework we may need to make up the link required to get to resources at the top level
			symlinkLoc = outputFilePath + "/Resources"
			if not exists(symlinkLoc):
				try:
					os.symlink(outputFileSymlinkPath, symlinkLoc)
				except OSError, e:
					time.sleep(10)
					if not exists(symlinkLoc):
						ErrorString(e.string)
						
		if theData.plist != None:

			theData.plist.getPlist().write(outputFile)
			#
			#	The daily build machine is occasionally getting a corrupt binary Info.plist file. Looking at 
			#	this corrupt file in a hex editor shows the first half or so of the file binary, and the remainder ascii text. 
			#	The theory is that plutil is doing its conversion to binary before the file is fully written, then when the 
			#	write finishes from this script, the remaining file is written as text. 
			#	To try to prevent that, we've added a 'flush', 'fsync', and a 'sleep' before letting plutil kick in. 
			#
			#	At the same time, we've re-enabled the error checking from the system(plutil) call. 
			#
			#
			outputFile.flush()
			if hasattr(os, 'fsync'):
				os.fsync(outputFile.fileno())
			outputFile.close()
			#
			# the changes described in the comment above didn't work. 
			# Attempt 2: have plutil output to a different file, and move that file into the output iff the plutil succeeds
			#
			convertPLListToBinary = "plutil -convert binary1 -o \"%s.binary\"  \"%s\" && mv -f \"%s.binary\"  \"%s\"" % (outputFile.name, outputFile.name, outputFile.name, outputFile.name)

			theErr = os.system(convertPLListToBinary)
			if theErr != 0:
				time.sleep(10)
				theErr = os.system(convertPLListToBinary)
				if theErr != 0:
					plistConvErr = "Couldn't convert to binary \"%s\"" % (outputFileContentsPath + theData.outputFileName)
					raise PreprocessingError(plistConvErr)			
		else:
			ErrorString("No plist generated. Did you give an empty file as source?")
			
		for b in theData.locales:
			b.write(outputFileResourcesPath)
		
		if options.package or ( os.getenv("PLC_GENERATE_PKGINFO_FILE","NO").strip().upper() == "YES" ):
			DoPackage(outputFileContentsPath,creator,type)
				

		return 0
		
	except BadArgsError, e:
		ErrorString (e.string)

	except BadInputFileError,e:
		ErrorString(e.string)
		
	except ParseError,e:
		ErrorString(e.string,e.file,e.line)
	
	except PreprocessingError,e:
		ErrorString(e.string)
	
	return 1

sys.exit(Main())

# ADOBE SYSTEMS INCORPORATED
# 
# OPEN SOURCE LICENSE
# 
# NOTICE TO USER:  Adobe Systems Incorporated is providing the Software and 
# Documentation for use under the terms of this Agreement.  Any use, reproduction, 
# modification or distribution of the Software or Documentation, or any 
# derivatives or portions thereof, constitutes your acceptance of this Agreement.
# 
# As used in this Agreement, "Adobe" means Adobe Systems Incorporated.  "Software" 
# means the software code accompanying this Agreement.   "Documentation" means the 
# documents, specifications and all other items accompanying this Agreement other 
# than the Software.   
# 
# 1.  LICENSE GRANT
# Subject to the terms of this Agreement, Adobe hereby grants you 
# a non-exclusive, worldwide, royalty free license to use, reproduce, prepare 
# derivative works from, publicly display, publicly perform, distribute and 
# sublicense the Software for any purpose, provided the copyright notice below 
# appears in a conspicuous location within the source code of the distributed 
# Software and this license is distributed in the supporting documentation of the 
# Software you distribute.
# 
# Copyright 2005 Adobe Systems Incorporated and others.  All rights 
# reserved.  The original version of this source code may be found at 
# http://adobe.com.
# 
# Subject to the terms of this Agreement, Adobe hereby grants you a non-exclusive, 
# worldwide, royalty free license to use, reproduce, publicly display, publicly 
# perform, distribute and sublicense the Documentation  for any purpose.  You may 
# not modify the Documentation.
# 
# No title to the intellectual property in the Software or Documentation is 
# transferred to you under the terms of this Agreement.  You do not acquire any 
# rights to the Software or the Documentation except as expressly set forth in 
# this Agreement.
# 
# If you choose to distribute the Software in a commercial product, you do so with 
# the understanding that you agree to defend, indemnify and hold harmless Adobe 
# against any losses, damages and costs arising from the claims, lawsuits or other 
# legal actions arising out of such distribution.  You may distribute the Software 
# in object code form under your own license, provided that your license 
# agreement:
# 
# (a) 	complies with the terms and conditions of this license agreement; 
# 
# (b) 	effectively disclaims all warranties and conditions, express or implied, 
# on behalf of Adobe;
# 
# (c) 	effectively excludes all liability for damages on behalf of Adobe;
# 
# (d) 	states that any provisions that differ from this Agreement are offered by 
# you alone and not Adobe; and
# 
# (e) 	states that the Software is available from you or Adobe and informs 
# licensees how to obtain it in a reasonable manner on or through a medium 
# customarily used for software exchange.  
# 
# 2.  DISCLAIMER OF WARRANTY
# ADOBE LICENSES THE SOFTWARE AND DOCUMENTATION TO YOU ONLY ON AN "AS IS" BASIS 
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, EITHER EXPRESS OR IMPLIED, 
# INCLUDING WITHOUT LIMITATION ANY WARRANTIES OR CONDITIONS OF TITLE, NON-
# INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  ADOBE MAKES 
# NO WARRANTY THAT THE SOFTWARE OR DOCUMENTATION WILL BE ERROR-FREE.  Each user of 
# the Software or Documentation is solely responsible for determining the 
# appropriateness of using and distributing the Software and Documentation and 
# assumes all risks associated with its exercise of rights under this Agreement, 
# including but not limited to the risks and costs of program errors, compliance 
# with applicable laws, damage to or loss of data, programs, or equipment, and 
# unavailability or interruption of operations.  Use of the Software and 
# Documentation is made with the understanding that Adobe will not provide you 
# with any technical or customer support or maintenance.  Some states or 
# jurisdictions do not allow the exclusion of implied warranties or limitations on 
# how long an implied warranty may last, so the above limitations may not apply to 
# you.  To the extent permissible, any implied warranties are limited to ninety 
# (90) days.
# 
# 
# 3.  LIMITATION OF LIABILITY
# ADOBE AND ITS SUPPLIERS SHALL NOT BE LIABLE FOR LOSS OR DAMAGE ARISING OUT OF 
# THIS AGREEMENT OR FROM THE USE OF THE SOFTWARE OR DOCUMENTATION.  IN NO EVENT 
# WILL ADOBE BE LIABLE TO YOU OR ANY THIRD PARTY FOR ANY DIRECT, INDIRECT, 
# CONSEQUENTIAL, INCIDENTAL, OR SPECIAL DAMAGES INCLUDING LOST PROFITS, LOST 
# SAVINGS, COSTS, FEES, OR EXPENSES OF ANY KIND ARISING OUT OF ANY PROVISION OF 
# THIS AGREEMENT OR THE USE OR THE INABILITY TO USE THE SOFTWARE OR DOCUMENTATION, 
# HOWEVER CAUSED AND UNDER ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
# LIABILITY OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE), EVEN IF ADVISED OF THE 
# POSSIBILITY OF SUCH DAMAGES.  ADOBE'S AGGREGATE LIABILITY AND THAT OF ITS 
# SUPPLIERS UNDER OR IN CONNECTION WITH THIS AGREEMENT SHALL BE LIMITED TO THE 
# AMOUNT PAID BY YOU FOR THE SOFTWARE AND DOCUMENTATION. 
# 
# 4.  TRADEMARK USAGE
# Adobe and XMP are the trademarks or registered trademarks of Adobe Systems 
# Incorporated in the United States and other countries.  Such trademarks may not 
# be used to endorse or promote any product unless expressly permitted under 
# separate agreement with Adobe.  
# 
# 5.  TERM
# Your rights under this Agreement shall terminate if you fail to comply with any 
# of the material terms or conditions of this Agreement and do not cure such 
# failure in a reasonable period of time after becoming aware of such 
# noncompliance.  If all your rights under this Agreement terminate, you agree to 
# cease use and distribution of the Software and Documentation as soon as 
# reasonably practicable. 
# 
# 6. GOVERNING LAW AND JURISDICTION. This Agreement is governed by the statutes 
# and laws of the State of California, without regard to the conflicts of law 
# principles thereof.  If any part of this Agreement is found void and 
# unenforceable, it will not affect the validity of the balance of the Agreement, 
# which shall remain valid and enforceable according to its terms.  Any dispute 
# arising out of or related to this Agreement shall be brought in the courts of 
# Santa Clara County, California, USA. 
# 
# 7.  GENERAL
# You acknowledge that you have read this Agreement, understand it, and that it is 
# the complete and exclusive statement of your agreement with Adobe which 
# supersedes any prior agreement, oral or written, between Adobe and you with 
# respect to the licensing to you of the Software and Documentation. No variation 
# of the terms of this Agreement will be enforceable against Adobe unless Adobe 
# gives its express consent in writing signed by an authorized signatory of Adobe.

