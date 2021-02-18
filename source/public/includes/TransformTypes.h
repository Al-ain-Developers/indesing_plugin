//========================================================================================
//  
//  $File: //depot/devtech/16.0.x/plugin/source/public/includes/TransformTypes.h $
//  
//  Owner: psorrick
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

#pragma once

#ifndef __TransformTypes__
#define __TransformTypes__

class GeometryFacade;
class TransformFacade;



/* This file implements type-safe enums and value objects used throughout the
transform and geometry API stacks.  In particular:

	        Type                                   Legal values
    Geometry::BoundsKind
                                           Geometry::OuterStrokeBounds()
                                           Geometry::PathBounds()
                                           Geometry::PreferredBoundsKind()

    Geometry::ResizeValue
                                           Geometry::MultiplyBy( Geometry::KeepCurrentValue(), y_factor)
                                           Geometry::MultiplyBy( x_factor, Geometry::KeepCurrentValue())
                                           Geometry::MultiplyBy( Geometry::KeepCurrentProportions(), y_factor)
                                           Geometry::MultiplyBy( x_factor, Geometry::KeepCurrentProportions())
                                           Geometry::MultiplyBy( x_factor, y_factor)

                                           Geometry::MakeTallAspectRatio()
                                           Geometry::MakeWideAspectRatio()
                                           Geometry::InvertAspectRatio()
                                           Geometry::ReshapeArea( width_to_height_ratio)
                                           Geometry::ReshapeArea( x_portion, y_portion)
                                           Geometry::ReshapeBorder( width_to_height_ratio)
                                           Geometry::ReshapeBorder( x_portion, y_portion)

									//the following optionally take a coordinateSpace parameter
                                           Geometry::AddTo( Geometry::KeepCurrentValue(), y_delta)
                                           Geometry::AddTo( x_delta, Geometry::KeepCurrentValue())
                                           Geometry::AddTo( Geometry::KeepCurrentProportions(), y_delta)
                                           Geometry::AddTo( x_delta, Geometry::KeepCurrentProportions())
                                           Geometry::AddTo( x_delta, y_delta)

                                           Geometry::ResizeTo( Geometry::KeepCurrentValue(), y_value)
                                           Geometry::ResizeTo( x_value, Geometry::KeepCurrentValue())
                                           Geometry::ResizeTo( Geometry::KeepCurrentProportions(), y_value)
                                           Geometry::ResizeTo( x_value, Geometry::KeepCurrentProportions())
                                           Geometry::ResizeTo( x_value, y_value)

    Transform::CoordinateSpace
                                           Transform::PasteboardCoordinates()
                                           Transform::SpreadCoordinates()
                                           Transform::ParentCoordinates()
                                           Transform::InnerCoordinates()

    Transform::TransformOrigin
                                           Transform::PasteboardLocation( x, y)
                                           Transform::PasteboardLocation( PMPoint(x, y))
                                           Transform::SpreadLocation( x, y)
                                           Transform::SpreadLocation( PMPoint(x, y))
                                           Transform::ParentLocation( x, y)
                                           Transform::ParentLocation( PMPoint(x, y))
                                           Transform::InnerLocation( x, y)
                                           Transform::InnerLocation( PMPoint(x, y))
                                           Transform::TransformLocation( x, y)
                                           Transform::TransformLocation( PMPoint(x, y))
                                           Transform::CurrentOrigin()

                                           Transform::RulerLocation( PMPoint(x, y), rulerNumber)
                                           Transform::RulerLocation( PMPoint(x, y), Transform::LeftTopLocation()) //or similar
										   
                                           Transform::BoundsLocation( boundsKind, x, y)
                                           Transform::BoundsLocation( boundsKind, PMPoint(x, y))
                                           Transform::BoundsLocation( coordinateSpace, boundsKind, x, y)
                                           Transform::BoundsLocation( coordinateSpace, boundsKind, PMPoint(x, y))
									//the following optionally take a boundsKind parameter with OuterStrokeBounds() as the default
                                           Transform::LeftTopLocation()
                                           Transform::LeftMiddleLocation()
                                           Transform::LeftBottomLocation()
                                           Transform::RightTopLocation()
                                           Transform::RightMiddleLocation()
                                           Transform::RightBottomLocation()
                                           Transform::MiddleTopLocation()
                                           Transform::MiddleBottomLocation()
                                           Transform::CenterLocation()

    Transform::TransformValue
                                           Transform::ScaleBy( xscale, yscale)
                                           Transform::ScaleTo( xscale, yscale)
                                           Transform::SkewBy( degrees)
                                           Transform::SkewTo( degrees)
                                           Transform::SkewBySlope( slope)
                                           Transform::SkewToSlope( slope)
                                           Transform::RotateBy( degrees)
                                           Transform::RotateTo( degrees)
                                           Transform::RotateBy( cosine, sine)
                                           Transform::RotateTo( cosine, sine)
                                           Transform::TranslateBy( deltaX, deltaY)
                                           Transform::TranslateTo( x, y)
                                           Transform::TransformBy( matrix)
                                           Transform::TransformTo( matrix, matrixContent)

    Transform::Target
                                           Transform::OriginalItems()
                                           Transform::DuplicateItems()
										   Transform::SpreadItems()



Further, the following constants are defined for use in the ITransformSuite and ITransformFacade interfaces:
	Transform::kScaleXValue, Transform::kScaleYValue, Transform::kSkewValue, Transform::kRotationValue, Transform::kTranslationXValue, Transform::kTranslationYValue


Other constructs in this file should be considered implementation details for
the types and values listed above.
*/


namespace Transform
{
	/* The structs below implement type-safe enums.  (For example, even using
	 * casts, you can't assign a variable of type Transform::View to an int or
	 * vice-versa.  Nor can you assign an object of type Transform::View to
	 * a Transform::Action.) The transform APIs use the types to help prevent 
	 * "silly" bugs that are hard to detect.  See the remarks on the inlines
	 * below for sample usage.
	 */

	typedef uint32 value_type;
	template< typename, value_type v> struct Int2Type { enum { value = v};};

	struct CoordinateSpace
	{
		typedef Int2Type< CoordinateSpace, 0> Pasteboard;
		typedef Int2Type< CoordinateSpace, 1> Parent;
		typedef Int2Type< CoordinateSpace, 2> Inner;
		typedef Int2Type< CoordinateSpace, 3> Spread;
		typedef Int2Type< CoordinateSpace, 4> Page;


		/*--------trickery below--------*/
		template<value_type v> CoordinateSpace( const Int2Type<CoordinateSpace, v>&, const PMMatrix& m)
			: base_space(v),final_space(m)  { }
		friend bool operator==( const CoordinateSpace& lhs, const CoordinateSpace& rhs) { return lhs.base_space == rhs.base_space; } //search for CoordinateCompare and Coordinate_Compare_OK
		friend bool operator!=( const CoordinateSpace& lhs, const CoordinateSpace& rhs) { return lhs.base_space != rhs.base_space; }
		private: value_type base_space;
		public:  PMMatrix final_space;
	};
	inline CoordinateSpace PasteboardCoordinates( const PMMatrix& m = PMMatrix())
		{ return CoordinateSpace( CoordinateSpace::Pasteboard(), m);}
	inline CoordinateSpace SpreadCoordinates( const PMMatrix& m = PMMatrix())
		{ return CoordinateSpace( CoordinateSpace::Spread(), m);}
	inline CoordinateSpace ParentCoordinates( const PMMatrix& m = PMMatrix())
		{ return CoordinateSpace( CoordinateSpace::Parent(), m);}
	inline CoordinateSpace InnerCoordinates( const PMMatrix& m = PMMatrix())
		{ return CoordinateSpace( CoordinateSpace::Inner(), m);}
	inline CoordinateSpace PageCoordinates( const PMMatrix& m = PMMatrix())
		{ return CoordinateSpace( CoordinateSpace::Page(), m);}
}



namespace Geometry
{
	typedef uint32 value_type;
	template< typename, value_type v> struct Int2Type { enum { value = v};};

	struct ResizeMethod
	{
		typedef Int2Type< ResizeMethod, 0> Equal;
		typedef Int2Type< ResizeMethod, 1> Add;
		typedef Int2Type< ResizeMethod, 2> Multiply;
		typedef Int2Type< ResizeMethod, 3> ConstantArea;
		typedef Int2Type< ResizeMethod, 4> ConstantPerimeter;


		/*--------trickery below--------*/
		template<value_type v> ResizeMethod( const Int2Type<ResizeMethod, v>& ) : resize_method(v) { }
		friend bool operator==( const ResizeMethod& lhs, const ResizeMethod& rhs) { return lhs.resize_method == rhs.resize_method; }
		friend bool operator!=( const ResizeMethod& lhs, const ResizeMethod& rhs) { return lhs.resize_method != rhs.resize_method; }
		private: value_type resize_method;
	};

	inline ResizeMethod ResizeEqual() { return ResizeMethod::Equal();}
	inline ResizeMethod ResizeAdd() { return ResizeMethod::Add();}
	inline ResizeMethod ResizeMultiply() { return ResizeMethod::Multiply();}
	inline ResizeMethod AspectRatioArea() { return ResizeMethod::ConstantArea();}
	inline ResizeMethod AspectRatioBorder() { return ResizeMethod::ConstantPerimeter();}




	struct BoundsKind
	{
		typedef Int2Type< BoundsKind, 0> OuterStroke;
		typedef Int2Type< BoundsKind, 1> Path;
		typedef Int2Type< BoundsKind, 2> Preferred;
		//not yet   typedef Int2Type< BoundsKind, 0> InnerStroke;


		/*--------trickery below--------*/
		template<value_type v> BoundsKind( const Int2Type<BoundsKind, v>& ) : bounds_kind(v) { }
		friend bool operator==( const BoundsKind& lhs, const BoundsKind& rhs) { return lhs.bounds_kind == rhs.bounds_kind; } //BoundsKindCompare
		friend bool operator!=( const BoundsKind& lhs, const BoundsKind& rhs) { return lhs.bounds_kind != rhs.bounds_kind; }
		private: value_type bounds_kind;
	};

	inline BoundsKind OuterStrokeBounds() { return BoundsKind::OuterStroke();}
	inline BoundsKind PathBounds() { return BoundsKind::Path();}
	//not yet   inline BoundsKind InnerStrokeBounds() { return BoundsKind::InnerStroke();}

	PUBLIC_DECL BoundsKind ResolvePreferredBounds( BoundsKind kind);
#if 0
	inline BoundsKind PreferredBoundsKind(){ return ResolvePreferredBounds( BoundsKind::Preferred());} //check the pref right now!
#else
	inline BoundsKind PreferredBoundsKind() { return BoundsKind::Preferred();} //be lazy--wait until the bounds kind is needed before checking the pref
#endif





	struct ResizeConstraint
	{
		typedef Int2Type< ResizeConstraint, 0> IgnoreProportions;
		typedef Int2Type< ResizeConstraint, 1> KeepProportions;
		typedef Int2Type< ResizeConstraint, 2> TallProportions;
		typedef Int2Type< ResizeConstraint, 3> WideProportions;
		typedef Int2Type< ResizeConstraint, 4> InverseProportions;


		/*--------trickery below--------*/
		template<value_type v> ResizeConstraint( const Int2Type<ResizeConstraint, v>& ) : resize_constraint(v) { }
		friend bool operator==( const ResizeConstraint& lhs, const ResizeConstraint& rhs) { return lhs.resize_constraint == rhs.resize_constraint; }
		friend bool operator!=( const ResizeConstraint& lhs, const ResizeConstraint& rhs) { return lhs.resize_constraint != rhs.resize_constraint; }
		private: value_type resize_constraint;
	};

	inline ResizeConstraint IgnoreCurrentProportions() { return ResizeConstraint::IgnoreProportions();} //Dismiss, Release ...?
	inline ResizeConstraint KeepCurrentProportions() { return ResizeConstraint::KeepProportions();} //Retain, Preserve ...?
	inline ResizeConstraint KeepCurrentValue() { return ResizeConstraint::IgnoreProportions();}
	inline ResizeConstraint MakeTallAspect() { return ResizeConstraint::TallProportions();}
	inline ResizeConstraint MakeWideAspect() { return ResizeConstraint::WideProportions();}
	inline ResizeConstraint InvertAspect() { return ResizeConstraint::InverseProportions();}

	enum ValueSource { kValueProvided, kValueCalculated};
	class ResizeValue
	{
		ResizeValue();
	public:
		Transform::CoordinateSpace provided_coordinates;
		ResizeMethod method;
		ResizeConstraint constraint;
		ValueSource x_source;
		ValueSource y_source;
		ValueSource coordinates_source;
		PMReal provided_x;
		PMReal provided_y;

		ResizeValue( ResizeMethod method_, ResizeConstraint constraint_,
			ValueSource x_source_, PMReal provided_x_,
			ValueSource y_source_, PMReal provided_y_,
			ValueSource coordinates_source_, const Transform::CoordinateSpace& provided_coordinates_
		) : method(method_), constraint(constraint_),
		    x_source(x_source_), provided_x(provided_x_),
		    y_source(y_source_), provided_y(provided_y_),
			coordinates_source(coordinates_source_), provided_coordinates(provided_coordinates_)
		{}
	};


	inline ResizeValue AddTo( ResizeConstraint constrainX, PMReal y_delta)
	{
		return ResizeValue( ResizeAdd(), constrainX, kValueCalculated, 0, kValueProvided, y_delta, kValueCalculated, Transform::InnerCoordinates());
	}

	inline ResizeValue AddTo( ResizeConstraint constrainX, PMReal y_delta, const Transform::CoordinateSpace& coordinateSpace)
	{
		return ResizeValue( ResizeAdd(), constrainX, kValueCalculated, 0, kValueProvided, y_delta, kValueProvided, coordinateSpace);
	}


	inline ResizeValue AddTo( PMReal x_delta, ResizeConstraint constrainY)
	{
		return ResizeValue( ResizeAdd(), constrainY, kValueProvided, x_delta, kValueCalculated, 0, kValueCalculated, Transform::InnerCoordinates());
	}
	
	inline ResizeValue AddTo( PMReal x_delta, ResizeConstraint constrainY, const Transform::CoordinateSpace& coordinateSpace)
	{
		return ResizeValue( ResizeAdd(), constrainY, kValueProvided, x_delta, kValueCalculated, 0, kValueProvided, coordinateSpace);
	}


	inline ResizeValue AddTo( PMReal x_delta, PMReal y_delta)
	{
		return ResizeValue( ResizeAdd(), IgnoreCurrentProportions(), kValueProvided, x_delta, kValueProvided, y_delta, kValueCalculated, Transform::InnerCoordinates());
	}
	
	inline ResizeValue AddTo( PMReal x_delta, PMReal y_delta, const Transform::CoordinateSpace& coordinateSpace)
	{
		return ResizeValue( ResizeAdd(), IgnoreCurrentProportions(), kValueProvided, x_delta, kValueProvided, y_delta, kValueProvided, coordinateSpace);
	}


	inline ResizeValue MultiplyBy( ResizeConstraint constrainX, PMReal y_factor)
	{
		return ResizeValue( ResizeMultiply(), constrainX, kValueCalculated, y_factor, kValueProvided, y_factor, kValueCalculated, Transform::InnerCoordinates()); //question do we pass proportional down or calc proportion here?
	}

	inline ResizeValue MultiplyBy( PMReal x_factor, ResizeConstraint constrainY)
	{
		return ResizeValue( ResizeMultiply(), constrainY, kValueProvided, x_factor, kValueCalculated, x_factor, kValueCalculated, Transform::InnerCoordinates()); //see note above
	}
	
	inline ResizeValue MultiplyBy( PMReal x_factor, PMReal y_factor)
	{
		return ResizeValue( ResizeMultiply(), IgnoreCurrentProportions(), kValueProvided, x_factor, kValueProvided, y_factor, kValueCalculated, Transform::InnerCoordinates());
	}


	inline ResizeValue ResizeTo( ResizeConstraint constrainX, PMReal y_value)
	{
		return ResizeValue( ResizeEqual(), constrainX, kValueCalculated, 0, kValueProvided, y_value, kValueCalculated, Transform::InnerCoordinates());
	}

	inline ResizeValue ResizeTo( ResizeConstraint constrainX, PMReal y_value, const Transform::CoordinateSpace& coordinateSpace)
	{
		return ResizeValue( ResizeEqual(), constrainX, kValueCalculated, 0, kValueProvided, y_value, kValueProvided, coordinateSpace);
	}


	inline ResizeValue ResizeTo( PMReal x_value, ResizeConstraint constrainY)
	{
		return ResizeValue( ResizeEqual(), constrainY, kValueProvided, x_value, kValueCalculated, 0, kValueCalculated, Transform::InnerCoordinates());
	}
	
	inline ResizeValue ResizeTo( PMReal x_value, ResizeConstraint constrainY, const Transform::CoordinateSpace& coordinateSpace)
	{
		return ResizeValue( ResizeEqual(), constrainY, kValueProvided, x_value, kValueCalculated, 0, kValueProvided, coordinateSpace);
	}


	inline ResizeValue ResizeTo( PMReal x_value, PMReal y_value)
	{
		return ResizeValue( ResizeEqual(), IgnoreCurrentProportions(), kValueProvided, x_value, kValueProvided, y_value, kValueCalculated, Transform::InnerCoordinates());
	}

	inline ResizeValue ResizeTo( PMReal x_value, PMReal y_value, const Transform::CoordinateSpace& coordinateSpace)
	{
		return ResizeValue( ResizeEqual(), IgnoreCurrentProportions(), kValueProvided, x_value, kValueProvided, y_value, kValueProvided, coordinateSpace);
	}




	inline ResizeValue ReshapeArea( ResizeConstraint orientation)
	{
		return ResizeValue( AspectRatioArea(), orientation, kValueCalculated, 0, kValueCalculated, 0, kValueCalculated, Transform::InnerCoordinates());
	}

	inline ResizeValue ReshapeArea( PMReal width_to_height_ratio)
	{
		return ResizeValue( AspectRatioArea(), IgnoreCurrentProportions(), kValueProvided, width_to_height_ratio, kValueProvided, 1, kValueCalculated, Transform::InnerCoordinates());
	}
	
	inline ResizeValue ReshapeArea( PMReal x_portion, PMReal y_portion)
	{
		return ResizeValue( AspectRatioArea(), IgnoreCurrentProportions(), kValueProvided, x_portion, kValueProvided, y_portion, kValueCalculated, Transform::InnerCoordinates());
	}


	inline ResizeValue ReshapeBorder( ResizeConstraint orientation)
	{
		return ResizeValue( AspectRatioBorder(), orientation, kValueCalculated, 0, kValueCalculated, 0, kValueCalculated, Transform::InnerCoordinates());
	}

	inline ResizeValue ReshapeBorder( PMReal width_to_height_ratio)
	{
		return ResizeValue( AspectRatioBorder(), IgnoreCurrentProportions(), kValueProvided, width_to_height_ratio, kValueProvided, 1, kValueCalculated, Transform::InnerCoordinates());
	}
	
	inline ResizeValue ReshapeBorder( PMReal x_portion, PMReal y_portion)
	{
		return ResizeValue( AspectRatioBorder(), IgnoreCurrentProportions(), kValueProvided, x_portion, kValueProvided, y_portion, kValueCalculated, Transform::InnerCoordinates());
	}

	inline ResizeValue MakeTallAspectRatio()
	{
		return ReshapeArea( Geometry::MakeTallAspect()); //ReshapeBorder would have the same effect
	}

	inline ResizeValue MakeWideAspectRatio()
	{
		return ReshapeArea( Geometry::MakeWideAspect()); //ReshapeBorder would have the same effect
	}

	inline ResizeValue InvertAspectRatio()
	{
		return ReshapeArea( Geometry::InvertAspect()); //ReshapeBorder would have the same effect
	}


} //namespace Geometry



namespace Transform
{

	struct Target
	{
		typedef Int2Type< Target, 0> OriginalItems;
		typedef Int2Type< Target, 1> DuplicateItems;
		typedef Int2Type< Target, 2> SpreadItems;

		/*--------trickery below--------*/
		template<value_type v> Target( const Int2Type<Target, v>& ) : transform_target(v) { }
		friend bool operator==( const Target& lhs, const Target& rhs) { return lhs.transform_target == rhs.transform_target; }
		friend bool operator!=( const Target& lhs, const Target& rhs) { return lhs.transform_target != rhs.transform_target; }
		private: value_type transform_target;
	};

	struct Action
	{
		typedef Int2Type< Action, 0> TransformBy;
		typedef Int2Type< Action, 1> TransformTo;
		typedef Int2Type< Action, 0> ScaleBy;
		typedef Int2Type< Action, 1> ScaleTo;
		typedef Int2Type< Action, 0> SkewBy;
		typedef Int2Type< Action, 1> SkewTo;
		typedef Int2Type< Action, 0> RotateBy;
		typedef Int2Type< Action, 1> RotateTo;
		typedef Int2Type< Action, 0> TranslateBy;
		typedef Int2Type< Action, 1> TranslateTo;

		/*--------trickery below--------*/
		template<value_type v> Action( const Int2Type< Action, v>& ) : transform_action(v) { }
		friend bool operator==( const Action& lhs, const Action& rhs) { return lhs.transform_action == rhs.transform_action; }
		friend bool operator!=( const Action& lhs, const Action& rhs) { return lhs.transform_action != rhs.transform_action; }
		private: value_type transform_action;
	};


	/* Note these inlines below serve two purposes.
	 * First they are more convenient to use.
	 *    use:           ScaleSelection(.... Transform::ScaleBy().....)
	 *    instead of:    ScaleSelection(.... Transform::Action::ScaleBy().....)
	 *
	 * Second they work with the ?: tertiary operator.
	 *    works:          absolute ? Transform::ScaleTo() : Transform::ScaleBy()
	 *    doesn't work:   absolute ? Transform::Action::ScaleTo() : Transform::Action::ScaleBy()
	 */

	inline Target OriginalItems() { return Target::OriginalItems();}
	inline Target DuplicateItems() { return Target::DuplicateItems();}
	inline Target SpreadItems() { return Target::SpreadItems();}

	inline Action ScaleBy() { return Action::ScaleBy();}
	inline Action ScaleTo() { return Action::ScaleTo();}
	inline Action SkewBy() { return Action::SkewBy();}
	inline Action SkewTo() { return Action::SkewTo();}
	inline Action RotateBy() { return Action::RotateBy();}
	inline Action RotateTo() { return Action::RotateTo();}
	inline Action TranslateBy() { return Action::TranslateBy();}
	inline Action TranslateTo() { return Action::TranslateTo();}
	inline Action TransformBy() { return Action::TransformBy();}
	inline Action TransformTo() { return Action::TransformTo();}


	struct LocationSpace
	{
		typedef Int2Type< LocationSpace, 0> TransformSpace;
		typedef Int2Type< LocationSpace, 1> RulerSpace;
		typedef Int2Type< LocationSpace, 2> BoundsSpace;


		/*--------trickery below--------*/
		template<value_type v> LocationSpace( const Int2Type<LocationSpace, v>& ) : location_space(v) { }
		friend bool operator==( const LocationSpace& lhs, const LocationSpace& rhs)
			{ return lhs.location_space == rhs.location_space;}
		friend bool operator!=( const LocationSpace& lhs, const LocationSpace& rhs) { return lhs.location_space != rhs.location_space; }
		private: value_type location_space;
	};


	class TransformOrigin
	{
		TransformOrigin();
	public:
		CoordinateSpace coordinateSpace;
		LocationSpace locationSpace;
		Geometry::BoundsKind boundsKind;
		PMPoint originLocation, pageLocator;
		//in TransformSpace case, a non-zero altValue means ignore coordinateSpace member and use coordinates specified in param list
		//in RulerSpace case, (altValue/2) non-zero means use the (altValue/2)th rulers on the spread, otherwise use BoundsSpace(), coordinateSpace, boundsKind, pageLocator to figure which spread rulers to use
		//in BoundsSpace case, a non-zero altValue means use inner coordinates for a single item and pasteboard coordinates for multiple items, otherwise use bounding box aligned with the specified coordinate system
		uint32 altValue, pageAltValue;

		TransformOrigin( const CoordinateSpace& coordinates, const PMPoint& location)
		  : locationSpace( LocationSpace::TransformSpace()),
		    originLocation(location),
		altValue(0), //use CoordinateSpace provided in this constructor
			coordinateSpace( coordinates),
			//ignored members...
			boundsKind(Geometry::PathBounds()),     //always ignored for TransformSpace
			pageLocator( PMPoint(0,0)),             //always ignored for TransformSpace
			pageAltValue(0)                         //always ignored when not RulerSpace
		{}

		TransformOrigin( const PMPoint& location) //MPSIssue kill this constructor and make callers use Transform::PasteboardLocation( PBPMPoint p)
		  : locationSpace( LocationSpace::TransformSpace()),
		    originLocation(location),
		altValue(0), //use CoordinateSpace provided in this constructor
			coordinateSpace( PasteboardCoordinates()),
			//ignored members...
			boundsKind(Geometry::PathBounds()),     //always ignored for TransformSpace
			pageLocator( PMPoint(0,0)),             //always ignored for TransformSpace
			pageAltValue(0)                         //always ignored when not RulerSpace
		{}
		
		TransformOrigin( const PMPoint& location, char* )
		  : locationSpace( LocationSpace::TransformSpace()),
		    originLocation(location),
		altValue(1), //use the same CoordinateSpace already provided elsewhere in the parameter list of the client function
			//ignored members...
			coordinateSpace( InnerCoordinates()),   //ignored when altValue is non-zero
			boundsKind(Geometry::PathBounds()),     //always ignored for TransformSpace
			pageLocator( PMPoint(0,0)),             //always ignored for TransformSpace
			pageAltValue(0)                         //always ignored when not RulerSpace
		{}


		TransformOrigin( const CoordinateSpace& coordinates, Geometry::BoundsKind bounds, const PMPoint& location)
		  : locationSpace( LocationSpace::BoundsSpace()),
			boundsKind( bounds),
		    originLocation( location),
		  altValue(0), //use coordinate space provided no matter how many items are being transformed
			coordinateSpace( coordinates),
			//ignored members...
			pageLocator( PMPoint(0,0)),             //always ignored for BoundsSpace
			pageAltValue(0)                         //always ignored when not RulerSpace
		{}
		
		TransformOrigin( Geometry::BoundsKind bounds, const PMPoint& location)
		  : locationSpace( LocationSpace::BoundsSpace()),
			boundsKind( bounds),
		    originLocation( location),
		  altValue(1), //use inner coordinates for a single item and pasteboard coordinates for multiple items
			coordinateSpace( PasteboardCoordinates()),   //when altValue is non-zero, use PasteboardCoordinates() for multiple items case
			//ignored members...
			pageLocator( PMPoint(0,0)),             //always ignored for BoundsSpace
			pageAltValue(0)                         //always ignored when not RulerSpace
		{}


		TransformOrigin( const PMPoint& location, uint32 spreadRuler, bool16 useRulerUnits = false)
		  : locationSpace( LocationSpace::RulerSpace()),
		    originLocation( location),
		  altValue( (2*spreadRuler) + (useRulerUnits ? 1 : 0)), // 0 means originLocation is in points, 1 means use current ruler units for the page
			//ignored members...
			coordinateSpace( InnerCoordinates()),   //ignored when altValue is non-zero
			boundsKind( Geometry::PathBounds()),    //ignored when altValue is non-zero
			pageLocator( PMPoint(0,0)),             //ignored when altValue is non-zero
			pageAltValue(0)                         //ignored when altValue is non-zero
		{
			ASSERT( spreadRuler != 0);
		}

		TransformOrigin( const PMPoint& location, const TransformOrigin& pageFinder, bool16 useRulerUnits = false)
		  : locationSpace( LocationSpace::RulerSpace()),
		    originLocation( location),
		  altValue( useRulerUnits ? 1 : 0), // 0 means originLocation is in points, 1 means use current ruler units for the page
			coordinateSpace( pageFinder.coordinateSpace),
			boundsKind( pageFinder.boundsKind),
			pageLocator( pageFinder.originLocation),
			pageAltValue( pageFinder.altValue)
			//no ignored members
		{
			ASSERT( pageFinder.locationSpace == LocationSpace::BoundsSpace());
		}


//		friend bool operator==( const TransformOrigin& lhs, const TransformOrigin& rhs) //XFIssue stronger test than necessary //CoordinateCompare
//			{ return lhs.locationSpace == rhs.locationSpace
//				&& lhs.coordinateSpace == rhs.coordinateSpace
//				&& lhs.boundsKind == rhs.boundsKind
//				&& lhs.originLocation == rhs.originLocation
//				&& lhs.pageLocator == rhs.pageLocator
//				&& lhs.altValue == rhs.altValue
//				&& lhs.pageAltValue == rhs.pageAltValue;
//			}
//		friend bool operator!=( const TransformOrigin& lhs, const TransformOrigin& rhs) { return !(lhs == rhs); }
	};

	inline TransformOrigin PasteboardLocation( PMPoint l)
	{
		return TransformOrigin( PasteboardCoordinates(), l);
	}
	inline TransformOrigin PasteboardLocation( PMReal x, PMReal y)
	{
		return PasteboardLocation( PMPoint(x,y));
	}
	inline TransformOrigin SpreadLocation( PMPoint l)
	{
		return TransformOrigin( SpreadCoordinates(), l);
	}
	inline TransformOrigin SpreadLocation( PMReal x, PMReal y)
	{
		return SpreadLocation( PMPoint(x,y));
	}
	inline TransformOrigin ParentLocation( PMPoint l)
	{
		return TransformOrigin( ParentCoordinates(), l);
	}
	inline TransformOrigin ParentLocation( PMReal x, PMReal y)
	{
		return ParentLocation( PMPoint(x,y));
	}
	inline TransformOrigin InnerLocation( PMPoint l)
	{
		return TransformOrigin( InnerCoordinates(), l);
	}
	inline TransformOrigin InnerLocation( PMReal x, PMReal y)
	{
		return InnerLocation( PMPoint(x,y));
	}
	inline TransformOrigin TransformLocation( PMPoint l)
	{
		return TransformOrigin( l, (char*)0/*dummy*/);
	}
	inline TransformOrigin TransformLocation( PMReal x, PMReal y)
	{
		return TransformLocation( PMPoint(x,y));
	}
	inline TransformOrigin CurrentOrigin()
	{
		return TransformLocation( 0,0);
	}


	inline TransformOrigin RulerLocation( PMPoint l, uint32 spreadRuler, bool16 useRulerUnits = false)
	{
		return TransformOrigin( l, spreadRuler, useRulerUnits);
	}
	inline TransformOrigin RulerLocation( PMPoint l, const TransformOrigin& boundsLocation, bool16 useRulerUnits = false)
	{
		return TransformOrigin( l, boundsLocation, useRulerUnits);
	}


	inline TransformOrigin BoundsLocation( const CoordinateSpace& coordinates, Geometry::BoundsKind boundsKind, PMPoint l)
	{
		return TransformOrigin( coordinates, boundsKind, l);
	}
	inline TransformOrigin BoundsLocation( const CoordinateSpace& coordinates, Geometry::BoundsKind boundsKind, PMReal x, PMReal y)
	{
		return BoundsLocation( coordinates, boundsKind, PMPoint(x,y));
	}
	inline TransformOrigin BoundsLocation( Geometry::BoundsKind boundsKind, PMPoint l)
	{
		return TransformOrigin( boundsKind, l);
	}
	inline TransformOrigin BoundsLocation( Geometry::BoundsKind boundsKind, PMReal x, PMReal y)
	{
		return BoundsLocation( boundsKind, PMPoint(x,y));
	}


	inline TransformOrigin LeftTopLocation( Geometry::BoundsKind boundsKind)
	{
		return BoundsLocation( boundsKind, 0.0, 0.0);
	}
	inline TransformOrigin MiddleTopLocation( Geometry::BoundsKind boundsKind)
	{
		return BoundsLocation( boundsKind, 0.5, 0.0);
	}
	inline TransformOrigin RightTopLocation( Geometry::BoundsKind boundsKind)
	{
		return BoundsLocation( boundsKind, 1.0, 0.0);
	}
	inline TransformOrigin LeftMiddleLocation( Geometry::BoundsKind boundsKind)
	{
		return BoundsLocation( boundsKind, 0.0, 0.5);
	}
	inline TransformOrigin CenterLocation( Geometry::BoundsKind boundsKind)
	{
		return BoundsLocation( boundsKind, 0.5, 0.5);
	}
	inline TransformOrigin RightMiddleLocation( Geometry::BoundsKind boundsKind)
	{
		return BoundsLocation( boundsKind, 1.0, 0.5);
	}
	inline TransformOrigin LeftBottomLocation( Geometry::BoundsKind boundsKind)
	{
		return BoundsLocation( boundsKind, 0.0, 1.0);
	}
	inline TransformOrigin MiddleBottomLocation( Geometry::BoundsKind boundsKind)
	{
		return BoundsLocation( boundsKind, 0.5, 1.0);
	}
	inline TransformOrigin RightBottomLocation( Geometry::BoundsKind boundsKind)
	{
		return BoundsLocation( boundsKind, 1.0, 1.0);
	}




	class TransformValue
	{
		TransformValue();
	public:
		PMMatrix transformMatrix;
		Action transformAction;
		uint32 matrixContent;
		
		TransformValue( Action action, const PMMatrix& matrix, uint32 content)
		  : transformAction(action), transformMatrix(matrix), matrixContent(content)
		{}
	};


	inline TransformValue TransformBy( const PMMatrix& m)
	{
		return TransformValue( TransformBy(), m, 0);
	}

	inline TransformValue TransformTo( const PMMatrix& m, uint32 matrixContent)
	{
		return TransformValue( TransformTo(), m, matrixContent);
	}

	inline TransformValue ScaleBy( PMReal xscale, PMReal yscale)
	{
		return TransformValue( ScaleBy(), PMMatrix( xscale, 0, 0, yscale, 0, 0), 0);
	}

	inline TransformValue ScaleTo( PMReal xscale, PMReal yscale)
	{
		return TransformValue( ScaleTo(), PMMatrix( xscale, 0, 0, yscale, 0, 0), PMMatrix::kHasScaleContent);
	}
	
	inline TransformValue SkewBy( PMReal degrees)
	{
		PMMatrix m;
		m.SkewHorizontal( -degrees); //XFIssue LH coordinates
		return TransformValue( SkewBy(), m, 0);
	}

	inline TransformValue SkewTo( PMReal degrees)
	{
		PMMatrix m;
		m.SkewHorizontal( -degrees); //XFIssue LH coordinates
		return TransformValue( SkewTo(), m, PMMatrix::kHasSkewContent);
	}

	inline TransformValue SkewBySlope( PMReal k)
	{
		return TransformValue( SkewBy(), PMMatrix( 1, 0, -k, 1, 0, 0), 0); //XFIssue LH coordinates
	}

	inline TransformValue SkewToSlope( PMReal k)
	{
		return TransformValue( SkewTo(), PMMatrix( 1, 0, -k, 1, 0, 0), PMMatrix::kHasSkewContent); //XFIssue LH coordinates
	}

	inline TransformValue RotateBy( PMReal degrees)
	{
		PMMatrix m;
		m.Rotate( -degrees); //XFIssue LH coordinates
		return TransformValue( RotateBy(), m, 0);
	}
	
	inline TransformValue RotateTo( PMReal degrees)
	{
		PMMatrix m;
		m.Rotate( -degrees); //XFIssue LH coordinates
		return TransformValue( RotateTo(), m, PMMatrix::kHasRotateContent);
	}

	inline TransformValue RotateBy( PMReal cosine, PMReal sine)
	{
		return TransformValue( RotateBy(), PMMatrix( cosine, -sine, sine, cosine, 0, 0), 0); //XFIssue LH coordinates
	}
	
	inline TransformValue RotateTo( PMReal cosine, PMReal sine)
	{
		return TransformValue( RotateTo(), PMMatrix( cosine, -sine, sine, cosine, 0, 0), PMMatrix::kHasRotateContent); //XFIssue LH coordinates
	}

	inline TransformValue TranslateBy( PMReal deltaX, PMReal deltaY)
	{
		return TransformValue( TranslateBy(), PMMatrix( 1, 0, 0, 1, deltaX, deltaY), 0);
	}

	inline TransformValue TranslateBy( PMPoint delta)
	{
		return TranslateBy( delta.X(), delta.Y());
	}

	inline TransformValue TranslateTo( PMReal x, PMReal y)
	{
		return TransformValue( TranslateTo(), PMMatrix( 1, 0, 0, 1, x, y), PMMatrix::kHasTranslateContent);
	}

	inline TransformValue TranslateTo( PMPoint p)
	{
		return TranslateTo( p.X(), p.Y());
	}


	const uint32 kNoTransformValues = 0;
	const uint32 kScaleXValue = 1;
	const uint32 kScaleYValue = 2;
	const uint32 kScaleValue = kScaleXValue | kScaleYValue;
	const uint32 kSkewValue = 4;
	const uint32 kRotationValue = 8;
	const uint32 kTranslationXValue = 16;
	const uint32 kTranslationYValue = 32;
	const uint32 kTranslationValue = kTranslationXValue | kTranslationYValue;
	const uint32 kAllTransformValues = kScaleValue | kSkewValue | kRotationValue | kTranslationValue;


	/** ScaleMethod specifies whether the transform command will process a RedefineScalingCmd before returning.
			Transform::UseLensScaling() - do not follow the transform with a RedefineScalingCmd
			Transform::UseContentScaling() - do follow the transform with a RedefineScalingCmd
			Transform::ConsultScalingPreference() - consult the user preference to decide which scaling technique to use.
	*/

	struct ScaleMethod
	{
		typedef Int2Type< ScaleMethod, 0> LensScaling;
		typedef Int2Type< ScaleMethod, 1> ContentScaling;
		typedef Int2Type< ScaleMethod, 2> ScalingPreference;


		/*--------trickery below--------*/
		template<value_type v> ScaleMethod( const Int2Type<ScaleMethod, v>& ) : scale_method(v) { }
		friend bool operator==( const ScaleMethod& lhs, const ScaleMethod& rhs) { return lhs.scale_method == rhs.scale_method; }
		friend bool operator!=( const ScaleMethod& lhs, const ScaleMethod& rhs) { return lhs.scale_method != rhs.scale_method; }
		private: value_type scale_method;
	};
	inline ScaleMethod UseLensScaling() { return ScaleMethod::LensScaling();}
	inline ScaleMethod UseContentScaling() { return ScaleMethod::ContentScaling();}
	inline ScaleMethod ConsultScalingPreference() { return ScaleMethod::ScalingPreference();}



} //namespace Transform






#endif	// __TransformTypes__


