// IDDN.FR.001.250001.005.S.P.2019.000.00000
// ULIS is subject to copyright laws and is the legal and intellectual property of Praxinos,Inc
/*
*   ULIS
*__________________
* @file         AbstractLayerDrawable.tpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the TAbstractLayerDrawable class.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Layer/Layer/AbstractLayerDrawable.h"

ULIS_NAMESPACE_BEGIN
template< class BlockType >
TAbstractLayerDrawable<BlockType>::~TAbstractLayerDrawable() {
    ULIS_DEBUG_PRINTF( "TAbstractLayerDrawable Destroyed" )
}
ULIS_NAMESPACE_END

