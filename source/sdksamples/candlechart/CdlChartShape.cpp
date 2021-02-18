//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/sdksamples/candlechart/CdlChartShape.cpp $
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
#include "ICdlChartData.h"
#include "IFontMgr.h"
#include "IGeometry.h"
#include "IGraphicsPort.h"
#include "IPMFont.h"
#include "IPMUnknown.h"
#include "ISession.h"

// General includes:
#include "CGraphicFrameShape.h"
#include "GraphicsData.h"

// Project includes:
#include "CdlChartID.h"

/** Responsible for drawing candle stock chart page item.
	
	@ingroup candlechart
	@auther Kaz Yoshikawa
*/
class CdlChartShape : public CGraphicFrameShape
{
public:

	/**	Constructor.
		@param boss IN interface ptr from boss object on which this interface is aggregated.
	*/
	CdlChartShape(IPMUnknown* boss);

	/** Destructor
	 */
	virtual ~CdlChartShape();

protected:

	/**	Called by the parent class Draw() method.  Responsible for drawing everything
		in the bounds of this object.
		@param	gd IN The current drawing context.
		@param	flags IN The IShape drawing flags for the current drawing context.
	*/
	virtual void DrawShape(GraphicsData* gd, int32 flags);
};

/* CREATE_PMINTERFACE
 Binds the C++ implementation class onto its
 ImplementationID making the C++ code callable by the
 application.
*/
CREATE_PMINTERFACE(CdlChartShape, kCdlChartShapeImpl)

/* Constructor
*/
CdlChartShape::CdlChartShape(IPMUnknown* boss)
	: CGraphicFrameShape(boss)
{
}

/* Destructor
*/
CdlChartShape::~CdlChartShape()	
{
}

/* Max
*/
template <class T>
inline T Max(T& a, T& b)
{
	return(a < b) ? b : a;
}

/* Min
*/
template <class T>
inline T Min(T& a, T& b)
{
	return(a < b) ? a : b;
}

/* DrawShape
*/
void CdlChartShape::DrawShape(GraphicsData* gd, int32 flags)
{
	do
	{
		int32       i;

		// graphic data
		if (gd == nil)
		{
			ASSERT_FAIL("Nil GraphicsData*");
			break;
		}

		// graphics port
		IGraphicsPort* gPort = gd->GetGraphicsPort();
		if (gPort == nil)
		{
			ASSERT_FAIL("Nil IGraphicsPort*");
			break;
		}

		// obtain bounding box of the item
		const PMRect r = fGeometry->GetStrokeBoundingBox(); 

		// find lowest and highest prise in the table
		InterfacePtr<ICdlChartData> CdlChartData(this, UseDefaultIID());
		CdlStockChartData graphData = CdlChartData->Get();

		// cannot show if no stock data.
		if (graphData.size() == 0)
		{
			return;
		}

		double      lowest = graphData[0].low;
		double      highest = graphData[0].high;
		for (i=0 ; i< graphData.size(); i++)
		{
			lowest = Min(lowest, graphData[i].low);
			highest = Max(highest, graphData[i].high);
		}

		double      highLow = highest - lowest;

		// to make the chart look not too tight
		double      hight5Percent = (highLow / 100) * 5;
		lowest -= hight5Percent;
		highest += hight5Percent;

		// check candle
		PMReal  rightMargin = 25.0;
		PMReal  barWidth = (r.Width() - rightMargin) / graphData.size();
		PMReal  factor = r.Height() / (highest - lowest);

		// setup default font for drawing stock prise
		PMString    fontName;
		InterfacePtr<IFontMgr> fontMgr (GetExecutionContextSession(), UseDefaultIID());
		if (fontMgr == nil)
		{
			ASSERT_FAIL("Nil IFontMgr*");
			break;
		}
		fontName = fontMgr->GetDefaultFontName();
		InterfacePtr<IPMFont> iFont (fontMgr->QueryFont(fontName));
		if (iFont == nil)
		{
			ASSERT_FAIL("Nil IPMFont*");
			break;
		}

		// detamines horizontal line step
		double      stopStep;
		if (highLow > 50.0)			stopStep = highLow /5.0;
		else if (highLow > 25.0)	stopStep = 5.0;
		else if (highLow > 10.0)	stopStep = 2.5;
		else if (highLow > 5.0)		stopStep = 1.0;
		else if (highLow > 2.5)		stopStep = 0.5;
		else						stopStep = 0.25;

		// horizontal lines
		gPort->gsave();
		gPort->selectfont(iFont, 6.0);
		for (double y = 0 ; y < highest ; y += stopStep)
		{
			if (y > lowest)
			{

				// horizontal lines
				PMReal  yy = r.Top() + (highest - y) * factor;
				gPort->setgray(0.4);
				gPort->moveto(r.Left(), yy);
				gPort->lineto(r.Right() - rightMargin, yy);
				gPort->stroke();

				// stock prise
				PMString    priceStr;
				priceStr.AppendNumber(y, 2);
				gPort->setgray(0);
				gPort->show(r.Right() - rightMargin + 4, yy, priceStr.WCharLength(), priceStr.GrabUTF16Buffer(nil));
			}
		}
		gPort->grestore();

		// drawing whole candles
		PMReal  barTop, barBot, barLeft, barRight, barCenter, barHigh, barLow, barFill;
		CdlStockData* dataPtr;
		for (i=0 ; i< graphData.size() ; i++)
		{

			// calculate candle position
			dataPtr = &graphData[graphData.size() - i - 1];

			barLeft = r.Left() + (barWidth * i) + 1.0;
			barRight = barLeft + barWidth - 1.0;
			barCenter = (barLeft + barRight) / 2;
			barHigh = r.Top() + (highest - dataPtr->high) * factor;
			barLow = r.Top() + (highest - dataPtr->low) * factor;

			// YOH sen & IN sen
			if (dataPtr->open < dataPtr->close)
			{
				barTop = r.Top() + (highest - dataPtr->close) * factor;
				barBot = r.Top() + (highest - dataPtr->open) * factor;
				barFill = 0.9;
			}
			else
			{
				barTop = r.Top() + (highest - dataPtr->open) * factor;
				barBot = r.Top() + (highest - dataPtr->close) * factor;
				barFill = 0;
			}

			// wiskers
			gPort->moveto(barCenter, barHigh);
			gPort->lineto(barCenter, barLow);
			gPort->stroke();

			// candle fill
			gPort->gsave();
			PMRect barRect(barLeft, barTop, barRight, barBot);
			gPort->rectpath(barRect);
			gPort->setgray(barFill);
			gPort->fill();
			gPort->grestore();

			// candle frame
			gPort->moveto(barRect.Left(), barRect.Top());
			gPort->lineto(barRect.Right(), barRect.Top());
			gPort->lineto(barRect.Right(), barRect.Bottom());
			gPort->lineto(barRect.Left(), barRect.Bottom());
			gPort->lineto(barRect.Left(), barRect.Top());
			gPort->stroke();
		}

		// drawing frame
		gPort->moveto(r.Left(), r.Top());
		gPort->lineto(r.Right() - rightMargin, r.Top());
		gPort->lineto(r.Right() - rightMargin, r.Bottom());
		gPort->lineto(r.Left(), r.Bottom());
		gPort->lineto(r.Left(), r.Top());
		gPort->stroke();

	} while (false);    
}

// End, CdlChartShape.cpp.
