#pragma once
#ifndef __DVPanelViewCustomColor__
#define __DVPanelViewCustomColor__

#include "DVPanelView.h"
#include "DVUtilities.h"

#ifdef DV_WIDGET_BUILD
#pragma export on
#endif

/**	Drover-based widget equivalent for PanelView - the base container widget. This version does not
* setup an AGM Graphics chain and should be used for PanelViews that dont need custom AGM drawing.
*/

class DV_WIDGET_DECL DVPanelViewCustomColor : public DVPanelView
{
	typedef DVPanelView inherited;
public:
	DVPanelViewCustomColor(IPMUnknown *boss);
	virtual	~DVPanelViewCustomColor();

	virtual void DV_Draw(dvaui::drawbot::Drawbot* drawbotP) const;
};

DVPanelViewCustomColor::DVPanelViewCustomColor(IPMUnknown *boss): inherited(boss)
{
	
}

DVPanelViewCustomColor::~DVPanelViewCustomColor()
{

}

#endif