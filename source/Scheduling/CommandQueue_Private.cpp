// IDDN FR.001.250001.004.S.X.2019.000.00000
// ULIS is subject to copyright laws and is the legal and intellectual property of Praxinos,Inc
/*
*   ULIS
*__________________
* @file         CommandQueue_Private.cpp
* @author       Clement Berthaud
* @brief        This file provides the definition for the FCommandQueue_Private class.
* @copyright    Copyright 2018-2021 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#pragma once
#include "Scheduling/CommandQueue_Private.h"
#include "System/ThreadPool.h"

ULIS_NAMESPACE_BEGIN
FCommandQueue::FCommandQueue_Private::~FCommandQueue_Private()
{
    // Cleanse unprocessed commands
    while( !mQueue.IsEmpty() )
    {
        const FCommand* cmd = mQueue.Front();
        delete  cmd;
        mQueue.Pop();
    }
}

FCommandQueue::FCommandQueue_Private::FCommandQueue_Private( FThreadPool& iPool )
    : mQueue( tQueue() )
    , mPool( iPool )
{
}

void
FCommandQueue::FCommandQueue_Private::Flush()
{
    while( !mQueue.IsEmpty() )
    {
        const FCommand* cmd = mQueue.Front();
        mQueue.Pop();
        mPool.ScheduleCommand( cmd );
    }
}

void
FCommandQueue::FCommandQueue_Private::Finish()
{
    Flush();
    Fence();
}

void
FCommandQueue::FCommandQueue_Private::Fence()
{
    mPool.WaitForCompletion();
}

void
FCommandQueue::FCommandQueue_Private::Push( const FCommand* iCommand )
{
    ULIS_ASSERT( iCommand, "Error: no input command" );
    iCommand->Event()->SetStatus( eEventStatus::EventStatus_Queued );
    mQueue.Push( iCommand );
}

ULIS_NAMESPACE_END

