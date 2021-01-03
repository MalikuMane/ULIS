// IDDN FR.001.250001.004.S.X.2019.000.00000
// ULIS is subject to copyright laws and is the legal and intellectual property of Praxinos,Inc
/*
*   ULIS
*__________________
* @file         InternalEvent.cpp
* @author       Clement Berthaud
* @brief        This file provides definition for the FInternalEvent class.
* @copyright    Copyright 2018-2021 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Scheduling/InternalEvent.h"
#include "Scheduling/Event.h"
#include "Scheduling/Event_Private.h"

ULIS_NAMESPACE_BEGIN
FInternalEvent::~FInternalEvent()
{
}

FInternalEvent::FInternalEvent()
    : mWaitList( TArray< FSharedInternalEvent >() )
    , mCommand( nullptr )
    , mStatus( eEventStatus::EventStatus_Idle )
{
}

//static
FSharedInternalEvent
FInternalEvent::Make()
{
    return  std::make_shared< FInternalEvent >();
}

const TArray< FSharedInternalEvent >&
FInternalEvent::WaitList() const
{
    return  mWaitList;
}

void
FInternalEvent::BuildWaitList( uint32 iNumWait, const FEvent* iWaitList )
{
    for( uint32 i = 0; i < iNumWait; ++i )
        mWaitList.PushBack( iWaitList[i].d->m );

#if defined( ULIS_DEBUG )
    CheckCyclicSelfReference();
#endif
}

bool
FInternalEvent::IsCommandBound() const
{
    return  mCommand != nullptr;
}

void
FInternalEvent::BindCommand( FCommand* iCommand )
{
    mCommand = iCommand;
}

void
FInternalEvent::CheckCyclicSelfReference() const
{
    CheckCyclicSelfReference_imp( this );
}

void
FInternalEvent::CheckCyclicSelfReference_imp( const FInternalEvent* iPin ) const
{
    for( uint32 i = 0; i < mWaitList.Size(); ++i )
    {
        FInternalEvent* pin = mWaitList[i].get();
        ULIS_ASSERT( pin != iPin, "Bad self reference in wait list." );
        pin->CheckCyclicSelfReference_imp( iPin );
    }
}

void
FInternalEvent::SetStatus( eEventStatus iStatus )
{
    mStatus = iStatus;
}

eEventStatus
FInternalEvent::Status() const
{
    return  mStatus;
}

bool
FInternalEvent::IsReady() const
{
    for( uint32 i = 0; i < mWaitList.Size(); ++i )
        if( mWaitList[i]->Status() != eEventStatus::EventStatus_Finished )
            return  false;

    return  true;
}


ULIS_NAMESPACE_END

