// IDDN.FR.001.250001.005.S.P.2019.000.00000
// ULIS is subject to copyright laws and is the legal and intellectual property of Praxinos,Inc
/*
*   ULIS
*__________________
* @file         RegularBlockRenderer.h
* @author       Clement Berthaud
* @brief        This file provides the declaration for the FRegularBlockRenderer class.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Core/Core.h"

ULIS_NAMESPACE_BEGIN
/////////////////////////////////////////////////////
/// @class      FRegularBlockRenderer
/// @brief      Allocator Utility for FBlock
class ULIS_API FRegularBlockRenderer
{
private:
    FRegularBlockRenderer() = default;

public:
    static void Render();
};

ULIS_NAMESPACE_END

