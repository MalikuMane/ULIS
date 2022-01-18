// IDDN.FR.001.250001.005.S.P.2019.000.00000
// ULIS is subject to copyright laws and is the legal and intellectual property of Praxinos,Inc
/*
*   ULIS
*__________________
* @file         AbstractLayerDrawable.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the TAbstractLayerDrawable class.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"
#include "Layer/Components/Drawable.h"
#include "Layer/Layer/Layer.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      TAbstractLayerDrawable
/// @brief      Simple TAbstractLayerDrawable class.
template< class BlockType >
class TAbstractLayerDrawable
    : public virtual ILayer
    , public TDrawable< BlockType >
{
public:
    using ILayer::ILayer;
    virtual ~TAbstractLayerDrawable() override = 0;

    void OnChangeNotifiedInternal() const override {
        ULIS_DEBUG_PRINTF( "Invalidation" )
        TDrawable< BlockType >::InvalidImageCache();
    }
};

ULIS_NAMESPACE_END

#include "Layer/Layer/AbstractLayerDrawable.tpp"

