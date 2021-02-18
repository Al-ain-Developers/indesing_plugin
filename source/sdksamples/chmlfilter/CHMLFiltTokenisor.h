//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/chmlfilter/CHMLFiltTokenisor.h $
//  
//  Owner: Adobe Developer Technologies
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

#ifndef _CHMLFiltTokenisor_H_
#define _CHMLFiltTokenisor_H_


/** Typedef of TokenValue.  We only deal in simple uchar arrays in this sample. 
*/
typedef PMString TokenValue;


/** The list of token types supported by this sample.
	@ingroup chmlfilter

*/
enum Token_t
{
	/** Invalid token. For the internal use of the tokeniser. */
	kTokenInvalid,		
	/** End of file token. For the internal use of the tokeniser. */
	kTokenEOF,
	
	/** CHML header token. <BR>Followed by: No value - might put revision number in here.  <BR>Syntax: <B>&lt;CHML&gt;</B>*/
	kTokenHead,			
	/** Text token. For the internal use of the tokeniser. */
	kTokenText,			
	/** Size.  <BR>Followed by: size.  <BR>Syntax: <B>&lt;s size&gt;</B> */
	kTokenSize,			
	/** Bold.  <BR>Followed by: No value.  <BR>Syntax: <B>&lt;b&gt;</B> */
	kTokenBold,			
	/** No bold.  <BR>Followed by: No value. <BR>Syntax: <B>&lt;/b&gt;</B> */
	kTokenNoBold,		
	/** Underline.  <BR>Followed by: No value. <BR>Syntax: <B>&lt;u&gt;</B>  */
	kTokenUnderline,	
	/** No underline.  <BR>Followed by: No value. <BR>Syntax: <B>&lt;/u&gt;</B> */
	kTokenNoUnderline,	
	/** Font.  <BR>Followed by: font name.  <BR>Syntax: <B>&lt;f fontname&gt;</B> */
	kTokenFont,			
	/** Paragraph.  <BR>Followed by: No value. <BR>Syntax: <B>&lt;p&gt;</B>  */
	kTokenPara,			
	/** Image file.  <BR>Followed by: x,y = top left coords of image.  <BR>Syntax: <B>&lt;i filename x y&gt;</B> */
	kTokenIFile,		
	/** Textbox. <BR>Followed by: bbox coordinates. <BR>Syntax: <B>&lt;t tlx tly brx bry&gt;</B> */
	kTokenTbox,			
	/** Alignment.  <BR>Followed by: one of left, right centre or justify. <BR>Syntax: <B>&lt;a l/r/c/j&gt;</B>  */
	kTokenAlign,		
	/** Comment start.  <BR>Followed by: No value.  <BR>Syntax: <B>&lt;c&gt;</B> */
	kTokenCommentStart, 
	/** Comment end.  <BR>Followed by: No value.  <BR>Syntax: <B>&lt;/c&gt;</B> */
	kTokenCommentEnd,	
    // additional tokens for CJK features (not recognised in main import provider, Apr 2003: IRP)
	/** Kenten (Japanese).  <BR>Followed by: No value. <BR>Syntax: <B>&lt;k&gt;</B>*/
    kTokenKenten,		
    /** No kenten (Japanese).  <BR>Followed by: No value. <BR>Syntax: <B>&lt;/k&gt;</B>*/
    kTokenNoKenten,
    /** Syatai (Japanese).  <BR>Followed by: No value. <BR>Syntax: <B>&lt;q&gt;</B>*/
    kTokenSyatai,		
    /** No syatai (Japanese).  <BR>Followed by: No value. <BR>Syntax: <B>&lt;/q&gt;</B>*/
    kTokenNoSyatai,
	/** Ruby (Japanese).  Ruby is a hiragana-reading aid that describes how to read the adorned Kanji glyphs. <BR>Followed by: m = mono ruby, or g = group ruby. <BR>Syntax: <B>&lt;r Ruby m/g NumOfParent&gt;</B>*/
	kTokenRuby
};

// string equivalents of the token typess of (see enum Token_t above)
#define TOKENHEAD PMString("<CHML>")
#define TOKENSIZE PMString("<s ")
#define TOKENSTARTBOLD PMString("<b>")
#define TOKENENDBOLD PMString("</b>")
#define TOKENSTARTUNDERLINE PMString("<u>")
#define TOKENENDUNDERLINE PMString("</u>")
#define TOKENFONT PMString("<f ")
#define TOKENPARA PMString("<p>")
#define TOKENIFILE PMString ("<i ")
#define TOKENTBOX PMString("<t ")
#define TOKENALIGN PMString("<a ")
#define TOKENSTARTCOMMENT PMString("<c>")
#define TOKENENDCOMMENT PMString("</c>")
// Additional Japanese specific tokens
#define TOKENKENTEN PMString("<k>")
#define TOKENENDKENTEN PMString("</k>")
#define TOKENSYATAI PMString("<q>")
#define TOKENENDSYATAI PMString("</q>")
#define TOKENRUBY PMString("<r ")


/**
	Builds a basic abstraction onto the PMStream; redefines the stream in terms of our markup tokens.

	There is no control placed on the stream, we might not be the
	only users of it. No definition of ownership...
	This is a very simple abstraction, as very little error handling is being done.
	
	@ingroup chmlfilter

 */
class CHMLFiltTokenisor 
{
public:
	/** Constructor. Initialize the stream and instance variables.
		
		@param s The stream from which to read tokens.
	*/
	CHMLFiltTokenisor(IPMStream* s);
	
	/** Destructor. 
	*/
	~CHMLFiltTokenisor(void);
	
	/** Get the next token and its value (if it has one) from the stream
        
		@param theToken The next token value in the stream.
		@return Token_t contains the type of token returned by reference (theToken).
	*/
    Token_t GetNextToken(TokenValue& theToken);

	/**	Returns the current token we are dealing with.
	
		@param theToken The current token value.
		@return Token_t contains the type of token returned by reference (theToken).
	*/
	Token_t GetCurrentToken(TokenValue& theToken);

	/** Rewinds the stream back to the beginning.
	*/
	void ResetStream(void);

	/**	Pushes the token back.
		We need some mechanism to allow users of this module to disregard a token
		we push the token back onto the stream (only works once), 
		the next time GetNextToken() is called, the token already read is returned.
		NOTE: This can only ever push one token back.
	*/
	void PushTokenBack(void); 

private:
	// we maintain the current token, this is what we pass back to the caller
 	// of GetNextToken. Ownership remains with this class. 
	// We also maintain the current token type. This is in line with
	// the idea of a "global" current token used within compiler technologies.
	TokenValue 	fCurrentToken; 
	Token_t 	fCurrentTokenType;

	// we need to be able to push a token back onto the stream
	bool 		token_spare; 
	
	// the stream we are acting on
	IPMStream*	theStream;
};

#endif //_CHMLFiltTokenisor_H_


// End, CHMLFiltTokenisor.h.


