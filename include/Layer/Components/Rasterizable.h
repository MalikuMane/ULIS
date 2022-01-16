// IDDN.FR.001.250001.005.S.P.2019.000.00000
// ULIS is subject to copyright laws and is the legal and intellectual property of Praxinos,Inc
/*
*   ULIS
*__________________
* @file         Rasterizable.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the TRasterizable class.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Math/Geometry/Rectangle.h"
#include "Math/Geometry/Vector.h"
#include "Scheduling/Event.h"
#include "Scheduling/SchedulePolicy.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TRasterizable
/// @brief      Simple Rasterizable class.
template< typename T >
class TRasterizable
{
    virtual T* Rasterize( FContext& iCtx, FEvent* oEvent = nullptr ) = 0;
};

ULIS_NAMESPACE_END

#include "Layer/Components/Rasterizable.tpp"

