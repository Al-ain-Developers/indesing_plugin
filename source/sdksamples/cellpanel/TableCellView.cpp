//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/cellpanel/TableCellView.cpp $
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

#include "VCPlugInHeaders.h"

// Interface includes:
#include "IGraphicsPort.h"			/* <IGraphicsPort>     */
#include "IRasterPort.h"			/* <IRasterPort>       */
#include "IWidgetParent.h"			/* <IWidgetParent>     */
#include "IPanelControlData.h"		/* <IPanelControlData> */
#include "IPMFont.h"				/* <IPMFont>	           */
#include "ICounterControlData.h"
#include "ISubject.h"
#include "ITableCellData.h"
#include "IInterfaceColors.h"

// General includes:
#include "AGMGraphicsContext.h"		/* AGMGraphicsContext  */
#include "AutoGSave.h"
#include "WorkspaceID.h"
#include "DVControlView.h"
#include "CellTable.h"

// Project includes:
#include "CelPnlID.h"

/** 
	This implementation draws the table and the cell contents.
	TableCellView implements IControlView based on the partial implementation DVControlView.

	@ingroup cellpanel
	
*/
class TableCellView : public DVControlView
{
	typedef DVControlView inherited;
	
	public:
		/**
			Constructor.
			@param boss interface ptr from boss object on which this interface is aggregated.
		*/
		TableCellView(IPMUnknown *boss);
		/**
			Destructor.
		*/
		~TableCellView();

		/**
			Render the contents of the view.
			@param vp ViewPort interface pointer.
			@param updateRgn Updating region of ViewPort.
		*/
		virtual void	Draw(IViewPort* vp, SysRgn updateRgn);

	protected:
		/**
			Draws the lines around cells for the TableCellView widget.
			@param gPort The graphic port to draw. 
			@param updateRgn The update region for drawing.
			@param colors The interface to get a color for UI 
			@param frame The size of the rectangle of the widget.
		*/
		void DrawCell(IGraphicsPort*		gPort,
						SysRgn				updateRgn,
					    IInterfaceColors*	colors,
					    const PMRect& 		frame);
		/**
			Draws contents of cell for the TableCellView widget.
			@param gPort The graphic port to draw. 
			@param updateRgn The update region for drawing.
			@param colors The interface to get a color for UI 
			@param frame The size of the rectangle of the widget.
		*/
		void DrawContents(IGraphicsPort*		gPort,
							SysRgn				updateRgn,
						    IInterfaceColors*	colors,
						    const PMRect& 		frame);
		/**
			Renews the scroll bar positions based on the current state of the TableCellView widget.
		*/
		void	UpdateScrollBar(void);
		/**
			The value of the vertical scroll bar new case is calculated. 
			@param newMax New upper bound on counter range of scrool bar.
			@param newValue New counter state.
			@param newIncrementMultiple New increment multiple.
		*/
		void	ComputeVerticalScrollBarNewValues(int32& newMax,
													int32& newValue,
													int32& newIncrementMultiple);
		/**
			The value of the horizontal scroll bar new case is calculated.
			@param newMax New upper bound on counter range of scrool bar.
			@param newValue New counter state.
			@param newIncrementMultiple New increment multiple.
		*/
		void	ComputeHorizontalScrollBarNewValues(int32& newMax,
													int32& newValue,
													int32& newIncrementMultiple);
						    
	private:
		WidgetID		fWidgetId;
		
		PMReal			fCellWidth, fCellHeight;
		
		int32			fColumnCount, fRowCount;
		
		int32			fStartColumn;
		int32			fStartRow;
		
		ICounterControlData	*fVScrollBar;
		ICounterControlData	*fHScrollBar;
		

};

CREATE_PERSIST_PMINTERFACE(TableCellView, kTableCellViewImpl)

/* Constructor
*/
TableCellView::TableCellView(IPMUnknown *boss) : inherited(boss),
	fStartColumn(0),
	fStartRow(0),
	fColumnCount(0),
	fRowCount(0),
	fVScrollBar(nil),
	fHScrollBar(nil)
{

}

/* ~TableCellView
*/
TableCellView::~TableCellView()
{
	if(fVScrollBar){
		fVScrollBar->Release();
	}
	if(fHScrollBar){
		fHScrollBar->Release();
	}
}

/* Draw
*/
void TableCellView::Draw(IViewPort* vp, SysRgn updateRgn)
{
	do{
		AGMGraphicsContext				gc(vp, this, updateRgn);
		InterfacePtr<IGraphicsPort> 	grPort(gc.GetViewPort(), UseDefaultIID());
		if(grPort == nil) break;
		
		InterfacePtr<IInterfaceColors>	colors(GetExecutionContextSession(), IID_IINTERFACECOLORS);
		if(colors ==nil) break;
		
		InterfacePtr<IWidgetParent>		parent(this, UseDefaultIID());
		if(parent == nil) break;
		
		InterfacePtr<ITableCellData>	pTableCellData((ITableCellData*)parent->QueryParentFor(IID_ITABLECELLDATA));
		// Assert message
		ASSERT_MSG(pTableCellData != nil, "TableCellView::Draw - We need a ITableCellData");
		if(pTableCellData == nil) break;

		// Get scroll bar control interface.
		if(!fVScrollBar || !fHScrollBar){
			InterfacePtr<IPanelControlData>	panelData((IPanelControlData*)parent->QueryParentFor(IID_IPANELCONTROLDATA));
			
			if(!fVScrollBar){
				InterfacePtr<IControlView> vScrollBar(panelData->FindWidget(kTableCellScrollWidgetID), UseDefaultIID());
				// Assert message
				ASSERT_MSG(vScrollBar != nil, "TableCellView::Draw - We need a vScroll bar");
				if(vScrollBar)
					 fVScrollBar = (ICounterControlData*)vScrollBar->QueryInterface(IID_ICOUNTERCONTROLDATA);
			}
			if(!fHScrollBar){
				InterfacePtr<IControlView> hScrollBar(panelData->FindWidget(kTableCellHScrollWidgetID), UseDefaultIID());
				// Assert message
				ASSERT_MSG(hScrollBar != nil, "TableCellView::Draw - We need a hScroll bar");
				if(hScrollBar)
					fHScrollBar = (ICounterControlData*)hScrollBar->QueryInterface(IID_ICOUNTERCONTROLDATA);
			}
		}
		
		// Ger cel width and height from TableCellData.
		if(pTableCellData){
			fCellWidth = pTableCellData->GetCellWidth();
			fCellHeight = pTableCellData->GetCellHeight();
			
			fColumnCount = pTableCellData->GetCellNumberOfColumns();
			fRowCount = pTableCellData->GetCellNumberOfRows();
		}
		
		PMRect frame = GetFrame();
			
		frame.MoveTo(0, 0);

		fWidgetId = this->GetWidgetID();

		AutoGSave autoGSave(grPort);
		
		UpdateScrollBar();
		
		DrawCell(grPort, updateRgn, colors, frame);
		
		DrawContents(grPort, updateRgn, colors, frame);
		
	}while(false);
}

/* DrawCell
*/
void TableCellView::DrawCell(IGraphicsPort*		grPort,
								 SysRgn				updateRgn,
							     IInterfaceColors*	colors,
							     const PMRect& 		frame	)
{
	if(grPort == nil) return;

	PMRect border(frame);
	
	//border.Inset(1.0, 1.0);
		
	AutoGSave autoGSave(grPort);

	RealAGMColor whiteColor;
	colors->GetRealAGMColor(kInterfaceWhite, whiteColor);
	grPort->setrgbcolor(whiteColor.red, whiteColor.green, whiteColor.blue);

	grPort->moveto(border.Left(), 		border.Bottom());
	grPort->lineto(border.Left(),		border.Top());
	grPort->lineto(border.Right(),		border.Top());
	grPort->lineto(border.Right(),		border.Bottom());
	grPort->fill();

	RealAGMColor  shadowColor, blackColor; 
	colors->GetRealAGMColor(kInterfaceBevelShadow,    shadowColor);
	colors->GetRealAGMColor(kInterfaceBlack, blackColor);	

	PMReal	ix, iy , a;
	int32	i;
	
	grPort->setrgbcolor(shadowColor.red, shadowColor.green, shadowColor.blue);
		
	for(i = 0, ix = fCellWidth; i < fColumnCount - 1; i++, ix += fCellWidth)
		{
		grPort->moveto(border.Left() + ix, border.Top()   );
		grPort->lineto(border.Left() + ix, border.Bottom());
		}
	
	for(i = 0, iy = fCellHeight; i < fRowCount - 1; i++, iy += fCellHeight)
		{
		grPort->moveto(border.Left(),  border.Top() + iy);
		grPort->lineto(border.Right(), border.Top() + iy);
		}
		
	grPort->stroke();

	// draw frame 
	grPort->setrgbcolor(blackColor.red, blackColor.green, blackColor.blue);
	grPort->moveto(border.Left(), 		border.Bottom());
	grPort->lineto(border.Left(),		border.Top());
	grPort->lineto(border.Right(),		border.Top());
	grPort->lineto(border.Right(),		border.Bottom());
	grPort->lineto(border.Left(),		border.Bottom());
	grPort->stroke();
}

/* DrawContents
*/
void TableCellView::DrawContents(	IGraphicsPort*		grPort,
									SysRgn				updateRgn,
								    IInterfaceColors*	colors,
								    const PMRect& 		frame)
{
	if(grPort == nil) return;

	do{
		PMReal		pointSize = 10;

		InterfacePtr<IFontMgr>		fontMgr(GetExecutionContextSession(), UseDefaultIID());
		if(fontMgr == nil) break;

		const PMString fontName = fontMgr->GetDefaultFontName();

		InterfacePtr<IPMFont>			font(fontMgr->QueryFont(fontName));
		if(font == nil) break;
		
		grPort->translate(frame.Left(), frame.Top());

		int32 antialias = 1; // None = 0, Enable text antialiasing: 1, Enable antialiasing of all graphic paths including clips and images: 2 
		
		InterfacePtr<IRasterPort> rport(grPort, UseDefaultIID());
		if(rport == nil) break;

		rport->setantialiaspolicy(&antialias); // Change 6/4/2001. rport->setantialiaspolicy(&antialias, nil);

		RealAGMColor  blackColor, highLightColor,highLightText;

		colors->GetRealAGMColor(kInterfaceHighLightText, highLightText);
		colors->GetRealAGMColor(kInterfaceBlack, blackColor);	
		colors->GetRealAGMColor(kInterfaceHighLight, highLightColor);

	#ifdef MACINTOSH
		RealAGMColor	whiteColor;

		colors->GetRealAGMColor(kInterfaceWhite, whiteColor);
		bool16 lightHilite = kFalse;

		if((highLightColor.red + highLightColor.green + highLightColor.blue) > 2.5)
			lightHilite = kTrue;
	#endif
		
		// Draw cell
		grPort->selectfont(font, pointSize);
		
		PMRect border(frame);
		
		InterfacePtr<IWidgetParent>		parent(this, UseDefaultIID());
		if(parent == nil) break;
		
		InterfacePtr<ITableCellData>	pTableCellData((ITableCellData*)parent->QueryParentFor(IID_ITABLECELLDATA));
		// Assert message
		ASSERT_MSG(pTableCellData != nil, "TableCellView::ConstrainDimensions - We need a ITableCellData");
		if(pTableCellData == nil) break;
			
		PMReal	ix, iy;
		int32	column, row;
		WideString	s;
		
		if(fVScrollBar){
			fStartRow	= fVScrollBar->GetValue();
			pTableCellData->SetViewTopRow(fStartRow);
		}
			
		if(fHScrollBar){
			fStartColumn = fHScrollBar->GetValue();
			pTableCellData->SetViewLeftColumn(fStartColumn);
		}
		
		int32 	endRow		= fStartRow + fRowCount;
		int32	endColumn	= fStartColumn + fColumnCount;
		int32	selCol, selRow;
		
		selCol = pTableCellData->GetSelectColumn();
		selRow = pTableCellData->GetSelectRow();
			
		for(row = fStartRow, iy = border.Left(); row < endRow; row++, iy += fCellHeight){
			for(column = fStartColumn, ix = border.Top(); column < endColumn; column++, ix += fCellWidth){

				AutoGSave autoGSave(grPort);
				grPort->rectclip(ix + 1 , iy + 1 , fCellWidth - 1, fCellHeight - 1);
				
				if((column == selCol) && (row == selRow)){
					grPort->setrgbcolor(highLightColor.red, highLightColor.green, highLightColor.blue);
					grPort->rectfill(ix + 1 , iy + 1 , fCellWidth - 1, fCellHeight - 1);
	#ifdef MACINTOSH
					if(!lightHilite)
						grPort->setrgbcolor(whiteColor.red, whiteColor.green, whiteColor.blue);
					else
	#endif
						grPort->setrgbcolor(highLightText.red, highLightText.green, highLightText.blue);
				}else{
					grPort->setrgbcolor(blackColor.red, blackColor.green, blackColor.blue);
				}

				s = pTableCellData->GetCellString(column, row);
				
				if(!s.empty())
					grPort->show(ix + 2, iy + fCellHeight - 2, s.NumUTF16TextChars(), s.GrabUTF16Buffer(nil));

			}
		}

		   if (rport)
					rport->setantialiaspolicy(&antialias); // Change 6/4/2001 rport->setantialiaspolicy(&antialias, nil);
	}while(false);
}

/* UpdateScrollBar
*/
void TableCellView::UpdateScrollBar(void)
{
	if (!fVScrollBar || !fHScrollBar)
		return;
		
	int32 newMax, newValue, newIncrementMultiple;
	
	// Update vertical scroll bar value.
	
	ComputeVerticalScrollBarNewValues(newMax, newValue, newIncrementMultiple);

	int32 oldMax				= fVScrollBar->GetMaximum();
	int32 oldValue				= fVScrollBar->GetValue();
	int32 oldIncrementMultiple	= fVScrollBar->GetIncrementMultiple();
	
	if (newMax != oldMax)
	{
		InterfacePtr<IControlView> scrollBarView(fVScrollBar, UseDefaultIID());		
		fVScrollBar->SetMaximum(newMax);
		if (newMax)
		{
			scrollBarView->Enable();
#ifdef MACINTOSH
			// On Mac, we need to force invalidation
			scrollBarView->Invalidate();
#endif
		}
		else
			scrollBarView->Disable();
	}

	if ((newValue != oldValue) || (newIncrementMultiple != oldIncrementMultiple))
	{
		InterfacePtr<ISubject> scrollSubject(fVScrollBar, UseDefaultIID());
		if (scrollSubject)
		{
			bool16	saveMute = scrollSubject->IsMuted();

			scrollSubject->Mute(kTrue);

			if (newValue != oldValue)
				fVScrollBar->SetValue(newValue);
			
			if (newIncrementMultiple != oldIncrementMultiple)
				fVScrollBar->SetIncrementMultiple(newIncrementMultiple);

			scrollSubject->Mute(saveMute);
		}
	}
	
	// Update vertical scroll bar value.
	
	ComputeHorizontalScrollBarNewValues(newMax, newValue, newIncrementMultiple);

	oldMax					= fHScrollBar->GetMaximum();
	oldValue				= fHScrollBar->GetValue();
	oldIncrementMultiple	= fHScrollBar->GetIncrementMultiple();
	
	if (newMax != oldMax)
	{
		InterfacePtr<IControlView> scrollBarView(fHScrollBar, UseDefaultIID());		
		fHScrollBar->SetMaximum(newMax);
		if (newMax)
		{
			scrollBarView->Enable();
#ifdef MACINTOSH
			// On Mac, we need to force invalidation
			scrollBarView->Invalidate();
#endif
		}
		else
			scrollBarView->Disable();
	}

	if ((newValue != oldValue) || (newIncrementMultiple != oldIncrementMultiple))
	{
		InterfacePtr<ISubject> scrollSubject(fHScrollBar, UseDefaultIID()); 
		if (scrollSubject)
		{
			bool16	saveMute = scrollSubject->IsMuted();

			scrollSubject->Mute(kTrue);

			if (newValue != oldValue)
				fHScrollBar->SetValue(newValue);
			
			if (newIncrementMultiple != oldIncrementMultiple)
				fHScrollBar->SetIncrementMultiple(newIncrementMultiple);

			scrollSubject->Mute(saveMute);
		}
	}
	

}

/* ComputeVerticalScrollBarNewValues
*/
void TableCellView::ComputeVerticalScrollBarNewValues(int32& newMax, int32& newValue, int32& newIncrementMultiple)
{
	do{
		InterfacePtr<IWidgetParent>		parent(this, UseDefaultIID());
		if(parent == nil) break;
		InterfacePtr<ITableCellData>	pTableCellData((ITableCellData*)parent->QueryParentFor(IID_ITABLECELLDATA));
		// Assert message
		ASSERT_MSG(pTableCellData != nil, "TableCellView::ConstrainDimensions - We need a ITableCellData");
		if(pTableCellData == nil) break;

		int32 numRows = pTableCellData->GetMaxRow();
		int32 rowCount = pTableCellData->GetCellNumberOfRows();
		
		newMax = numRows - rowCount; // First cell is 0.
		if(newMax < 0) newMax = 0;
			
		newIncrementMultiple = rowCount - 1;
		
		if(fVScrollBar){
			newValue	= fVScrollBar->GetValue();
			if(newValue > newMax)	newValue = newMax;
		}else
			newValue = 0;
	}while(false);
}
	
/* ComputeHorizontalScrollBarNewValues
*/
void TableCellView::ComputeHorizontalScrollBarNewValues(int32& newMax, int32& newValue, int32& newIncrementMultiple)
{
	do{
		InterfacePtr<IWidgetParent>		parent(this, UseDefaultIID());
		if(parent == nil) break;
		
		InterfacePtr<ITableCellData>	pTableCellData((ITableCellData*)parent->QueryParentFor(IID_ITABLECELLDATA));
		// Assert message
		ASSERT_MSG(pTableCellData != nil, "TableCellView::ConstrainDimensions - We need a ITableCellData");
		if(pTableCellData == nil) break;
		
		int32 numColumn(0);
		int32 colmunCount(0);
		
		if(pTableCellData){
			numColumn = pTableCellData->GetMaxColumn(); 
			colmunCount = pTableCellData->GetCellNumberOfColumns();
		}
		
		newMax = numColumn - colmunCount; // First cell is 0.
		if(newMax < 0) newMax = 0;
		
		newIncrementMultiple  = colmunCount - 1;
			
		if(fHScrollBar){
			newValue	= fHScrollBar->GetValue();
			if(newValue > newMax)	newValue = newMax;
		}else
			newValue = 0;
	}while(false);
}

// End, TableCellView.cpp.

