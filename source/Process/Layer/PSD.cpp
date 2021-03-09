// IDDN FR.001.250001.004.S.X.2019.000.00000
// ULIS is subject to copyright laws and is the legal and intellectual property of Praxinos,Inc
/*
*   ULIS
*__________________
* @file         PSD.cpp
* @author       Clement Berthaud
* @brief        This file provides the implementation for the PSD tools.
* @copyright    Copyright 2018-2021 Praxinos, Inc. All Rights Reserved.
* @license      Please refer to LICENSE.md
*/
#include "Process/Layer/PSD.h"

//#include "OdysseyPsdOperations.h"
/*#include "OdysseyMathUtils.h"
#include <ULIS3>
#include "ULISLoaderModule.h"
#include "zlib.h"*/

ULIS_NAMESPACE_BEGIN
FPSDOperations::~FPSDOperations()
{
    /*if( mFileHandle )
    {
        mFileHandle->Flush(true);
        delete mFileHandle;
    }*/
    
    /*if( mImageDst )
        delete [] mImageDst;

    if( mImageDst16 )
        delete [] mImageDst16;

    if(mImageDst32)
        delete[] mImageDst32;

    for( int i = 0; i < mLayersInfo.Num(); i++)
    {
        if( mLayersInfo[i].mLayerImageDst )
            delete [] mLayersInfo[i].mLayerImageDst;

        if( mLayersInfo[i].mLayerImageDst16 )
            delete [] mLayersInfo[i].mLayerImageDst16;

        if(mLayersInfo[i].mLayerImageDst32)
            delete[] mLayersInfo[i].mLayerImageDst32;
    }*/
}

FPSDOperations::FPSDOperations(const std::string& iFilename)
    : mFileHandle( iFilename.c_str(), std::ios::binary | std::ios::ate )
{
    //std::streamsize size = mFileHandle.tellg();
    /*std::vector<char> buffer(size);
    if(!file.read(buffer.data(),size))*/

    /* mChannelsNumber = 0;
     mImageHeight = 0;
     mImageWidth = 0;
     mBitDepth = 0;
     mColorMode = 0;

     mImageStart = 0;
     mImageDst = nullptr;
     mImageDst16 = nullptr;
     mImageDst32 = nullptr;

     mLayerStack = nullptr;

     mLayersInfo = TArray<FPSDLayerInfo>();*/
}

bool FPSDOperations::ReadFileHeader()
{    
    mFileHandle.seekg(0,std::ios::beg);

    char psdValidator[5] = { 0 }; // 4 characters + null termination
    if(!mFileHandle.read(psdValidator,4))

    if( strcmp(psdValidator, "8BPS") != 0 )
    {
        //UE_LOG(LogTemp,Warning,TEXT("This is likely not a PSD file, import failed"));
        return false;
    }

    //---
    /*
    uint16_t versionNumber;
    mFileHandle->Read((uint8*)&versionNumber,2);
    FOdysseyMathUtils::ByteSwap(&versionNumber,2);
    if( versionNumber != 1 )
    {
        UE_LOG(LogTemp,Warning,TEXT("Unknown psd file version, import failed"));
        return false;
    }

    //---

    mFileHandle->Seek( mFileHandle->Tell() + 6 ); // There are 6 zeroed bytes here, we don't care about them

    //---

    mFileHandle->Read((uint8*)&mChannelsNumber,2);
    FOdysseyMathUtils::ByteSwap(&mChannelsNumber,2);
    mFileHandle->Read((uint8*)&mImageHeight,4);
    FOdysseyMathUtils::ByteSwap(&mImageHeight,4);
    mFileHandle->Read((uint8*)&mImageWidth,4);
    FOdysseyMathUtils::ByteSwap(&mImageWidth,4);
    mFileHandle->Read((uint8*)&mBitDepth,2);
    FOdysseyMathUtils::ByteSwap(&mBitDepth,2);
    mFileHandle->Read((uint8*)&mColorMode,2);
    FOdysseyMathUtils::ByteSwap(&mColorMode,2);

    //UE_LOG(LogTemp, Display, TEXT("ChannelsNumber: %d"), mChannelsNumber );
    //UE_LOG(LogTemp,Display,TEXT("mImageHeight: %d"),mImageHeight);
    //UE_LOG(LogTemp,Display,TEXT("mImageWidth: %d"),mImageWidth);
    //UE_LOG(LogTemp,Display,TEXT("mBitDepth: %d"),mBitDepth);
    //UE_LOG(LogTemp,Display,TEXT("mColorMode: %d"),mColorMode);
    */
    return true;
}
//
//bool FPSDOperations::ReadFileColorMode()
//{
//    uint32_t colorModeSize;
//    mFileHandle->Read((uint8*)&colorModeSize,4);
//    FOdysseyMathUtils::ByteSwap(&colorModeSize,4);
//    mFileHandle->Seek( mFileHandle->Tell() + colorModeSize );
//
//    //UE_LOG(LogTemp,Display,TEXT("colorModeSize: %d"),colorModeSize);
//
//    return true;
//}
//
//bool FPSDOperations::ReadImageResources()
//{
//    uint32_t imageResourcesSize;
//    mFileHandle->Read((uint8*)&imageResourcesSize,4);
//    FOdysseyMathUtils::ByteSwap( &imageResourcesSize, 4 );
//
//    //UE_LOG(LogTemp,Display,TEXT("imageResourcesSize: %d"),imageResourcesSize);
//
//    mFileHandle->Seek( mFileHandle->Tell() + imageResourcesSize );
//    return true;
//}
//
//bool FPSDOperations::ReadLayerAndMaskInfo()
//{
//    uint32_t layerAndMaskInfoSize;
//    mFileHandle->Read((uint8*)&layerAndMaskInfoSize,4);
//    FOdysseyMathUtils::ByteSwap(&layerAndMaskInfoSize,4);
//
//    uint32_t position = mFileHandle->Tell();
//
//    //UE_LOG(LogTemp,Display,TEXT("layerAndMaskInfoSize: %d"),layerAndMaskInfoSize);
//
//    bool isAnyLayer = true;
//    if( layerAndMaskInfoSize > 0) 
//    {
//        isAnyLayer = ReadLayerInfo();
//
//        if( isAnyLayer )
//            isAnyLayer = ReadMaskInfo();
//
//        ReadAdditionalLayerInfo(position + layerAndMaskInfoSize);
//    }
//
//    mFileHandle->Seek( mFileHandle->Tell() + layerAndMaskInfoSize );
//
//    mImageStart = position + layerAndMaskInfoSize;
//    //UE_LOG(LogTemp, Display, TEXT("mImageStart:%d"), mImageStart)
//    return isAnyLayer;
//}
//
//bool FPSDOperations::ReadLayerInfo()
//{
//    uint32_t layerInfoSize;
//    mFileHandle->Read((uint8*)&layerInfoSize,4);
//    FOdysseyMathUtils::ByteSwap(&layerInfoSize,4);
//
//    uint32_t position = mFileHandle->Tell();
//
//    //UE_LOG(LogTemp, Display, TEXT("layerInfoSize: %d"), layerInfoSize);
//
//    if( mBitDepth >= 16 && layerInfoSize != 0) 
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Shouldn't have any info for 16+ bit depth, import failed"))
//        return false;
//    }
//
//    if(layerInfoSize != 0)
//        ReadLayers();
//
//    mFileHandle->Seek( position + layerInfoSize );
//    return true;
//}
//
//bool FPSDOperations::ReadMaskInfo()
//{
//    uint32_t maskInfoSize;
//    mFileHandle->Read((uint8*)&maskInfoSize,4);
//    FOdysseyMathUtils::ByteSwap(&maskInfoSize,4);
//    
//    //UE_LOG(LogTemp,Display,TEXT("maskInfoSize: %d"),maskInfoSize);
//
//    mFileHandle->Seek( mFileHandle->Tell() + maskInfoSize );
//    return true;
//}
//
//bool FPSDOperations::ReadLayers()
//{
//    int16 numLayers;
//    mFileHandle->Read( (uint8*)&numLayers, 2);
//    FOdysseyMathUtils::ByteSwap( &numLayers, 2);
//    
//    if( numLayers < 0 )
//        numLayers = -numLayers;
//
//    //UE_LOG(LogTemp,Display,TEXT("numLayers: %d"),numLayers);
//    for (int currLayer = 0; currLayer < numLayers; currLayer++) 
//    {
//        mLayersInfo.Add( FPSDLayerInfo() );
//
//        mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mTop,4);
//        FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mTop,4);
//        mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mLeft,4);
//        FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mLeft,4);
//        mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mBottom,4);
//        FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mBottom,4);
//        mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mRight,4);
//        FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mRight,4);
//        mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mNumChannels,2);
//        FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mNumChannels,2);
//
//
//        /*UE_LOG(LogTemp,Display,TEXT("y: %d"),mLayersInfo[currLayer].mTop);
//        UE_LOG(LogTemp,Display,TEXT("x: %d"),mLayersInfo[currLayer].mLeft);
//        UE_LOG(LogTemp,Display,TEXT("l: %d"),mLayersInfo[currLayer].mBottom);
//        UE_LOG(LogTemp,Display,TEXT("t: %d"),mLayersInfo[currLayer].mRight);
//        UE_LOG(LogTemp,Display,TEXT("numChannels: %d"),mLayersInfo[currLayer].mNumChannels);*/
//
//        for(int currChannel = 0; currChannel < mLayersInfo[currLayer].mNumChannels; currChannel++) 
//        {
//            mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mID[currChannel],2);
//            FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mID[currChannel],2);
//            mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mChannelSize[currChannel],4);
//            FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mChannelSize[currChannel],4);
//            /*UE_LOG(LogTemp,Display,TEXT("id: %d"),mLayersInfo[currLayer].mID[currChannel]);
//            UE_LOG(LogTemp,Display,TEXT("channelSize: %d"),mLayersInfo[currLayer].mChannelSize[currChannel]);*/
//        }
//
//        char psdValidator[5] = {0}; // 4 characters + null termination
//        mFileHandle->Read((uint8*)psdValidator,4);
//        if(strcmp(psdValidator,"8BIM") != 0)
//        {
//            UE_LOG(LogTemp,Warning,TEXT("This is likely not a PSD file, import failed"));
//            return false;
//        }
//
//        mFileHandle->Read((uint8*) mLayersInfo[currLayer].mBlendModeKey, 4);
//
//        mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mOpacity,1);
//        //UE_LOG(LogTemp,Display,TEXT("opacity: %d"),mLayersInfo[currLayer].mOpacity);
//
//        mFileHandle->Seek( mFileHandle->Tell() + 1 ); //Clipping byte
//
//        mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mFlags,1);
//
//        mFileHandle->Seek(mFileHandle->Tell() + 1); //Filler byte
//
//        mFileHandle->Read( (uint8*) &mLayersInfo[currLayer].mExtraSize, 4 );
//        FOdysseyMathUtils::ByteSwap( &mLayersInfo[currLayer].mExtraSize, 4);
//
//        mLayersInfo[currLayer].mExtraPosition = mFileHandle->Tell();
//        mLayersInfo[currLayer].mExtraRead = 0;
//
//        mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mLayerMaskSize,4);
//        FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mLayerMaskSize,4);
//
//        uint32_t position = mFileHandle->Tell();
//
//        if(mLayersInfo[currLayer].mLayerMaskSize != 0) 
//        {
//            mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mYMask,4);
//            FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mYMask,4);
//            mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mXMask,4);
//            FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mXMask,4);
//            mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mWMask,4);
//            FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mWMask,4);
//            mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mHMask,4);
//            FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mHMask,4);
//            mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mColorMask,1);
//            mFileHandle->Read((uint8*)&mLayersInfo[currLayer].mFlagsMask,1);
//
//            /*UE_LOG(LogTemp,Display,TEXT("yMask: %d"),mLayersInfo[currLayer].mYMask);
//            UE_LOG(LogTemp,Display,TEXT("xMask: %d"),mLayersInfo[currLayer].mXMask);
//            UE_LOG(LogTemp,Display,TEXT("lMask: %d"),mLayersInfo[currLayer].mWMask);
//            UE_LOG(LogTemp,Display,TEXT("tMask: %d"),mLayersInfo[currLayer].mHMask);
//            UE_LOG(LogTemp,Display,TEXT("colorMask: %d"),mLayersInfo[currLayer].mColorMask);
//            UE_LOG(LogTemp,Display,TEXT("flagsMask: %d"),mLayersInfo[currLayer].mFlagsMask);*/
//        }
//
//        mFileHandle->Seek( position + mLayersInfo[currLayer].mLayerMaskSize );
//        mLayersInfo[currLayer].mExtraRead += 4 + mLayersInfo[currLayer].mLayerMaskSize;
//
//        mFileHandle->Read( (uint8*) &mLayersInfo[currLayer].mLayerBlendingSize, 4 );
//        FOdysseyMathUtils::ByteSwap( &mLayersInfo[currLayer].mLayerBlendingSize, 4 );
//        mLayersInfo[currLayer].mExtraRead += 4 + mLayersInfo[currLayer].mLayerBlendingSize;
//        mFileHandle->Seek( mFileHandle->Tell() + mLayersInfo[currLayer].mLayerBlendingSize );
//
//        mFileHandle->Read( (uint8*) &mLayersInfo[currLayer].mNameSize, 1 );
//        mLayersInfo[currLayer].mName[256] = {0};
//        mFileHandle->Read( (uint8*) mLayersInfo[currLayer].mName, mLayersInfo[currLayer].mNameSize );
//
//        mFileHandle->Seek( mFileHandle->Tell() + (3 - mLayersInfo[currLayer].mNameSize % 4) ); //4 bytes increments for the name
//        mLayersInfo[currLayer].mExtraRead  += mLayersInfo[currLayer].mNameSize + 4 - mLayersInfo[currLayer].mNameSize%4;
//
//        if(mLayersInfo[currLayer].mName[0] == 0)
//            strcpy(mLayersInfo[currLayer].mName,"background");
//
//        //UE_LOG(LogTemp, Display, TEXT("%s"), mLayersInfo[currLayer].mName);
//
//        position = mFileHandle->Tell();
//
//        while( mLayersInfo[currLayer].mExtraRead < mLayersInfo[currLayer].mExtraSize ) 
//        {
//            if(!ReadAdditionalLayerInfoSignature() )
//                break;
//
//            char lsctKey[5] = {0}; // 4 characters + null termination
//            mFileHandle->Read((uint8*)lsctKey,4);
//
//            uint32_t len;
//            mFileHandle->Read( (uint8*) &len, 4);
//            FOdysseyMathUtils::ByteSwap( &len, 4);
//            position = mFileHandle->Tell();
//            mLayersInfo[currLayer].mExtraRead += 12 + len;
//
//            if(strcmp(lsctKey,"lsct") == 0)
//            {
//                mFileHandle->Read( (uint8*) &mLayersInfo[currLayer].mDividerType,4);
//                FOdysseyMathUtils::ByteSwap(&mLayersInfo[currLayer].mDividerType,4);
//                //UE_LOG(LogTemp,Display,TEXT("mDividerType: %d"),mLayersInfo[currLayer].mDividerType);
//            }
//            mFileHandle->Seek( position + len );
//        }
//        mFileHandle->Seek( mLayersInfo[currLayer].mExtraPosition + mLayersInfo[currLayer].mExtraSize );
//    }
//
//
//    uint32_t imgData = mFileHandle->Tell();
//    for(int i = 0; i < numLayers; i++) 
//    {
//        for(int c = 0; c < mLayersInfo[i].mNumChannels; c++) 
//        {
//            mLayersInfo[i].mStartChannelPos[c] = imgData;
//            imgData += mLayersInfo[i].mChannelSize[c];
//        }
//    }
//
//    return true;
//}
//
//bool FPSDOperations::ReadAdditionalLayerInfoSignature()
//{
//    char psdValidator[5] = {0}; // 4 characters + null termination
//    mFileHandle->Read((uint8*)psdValidator,4);
//
//    if(strcmp(psdValidator,"8BIM") != 0 && strcmp(psdValidator,"8B64") != 0)
//    {
//        UE_LOG(LogTemp,Display,TEXT("No additionnal layer info Signature"));
//        return false;
//    }
//
//    return true;
//}
//
//bool FPSDOperations::ReadAdditionalLayerInfo(uint32_t sectionEnd)
//{
//    uint32_t position = mFileHandle->Tell();
//    if( position > sectionEnd ) 
//    {
//        UE_LOG(LogTemp, Display, TEXT("Error while loading data: out of bounds"));
//        return false;
//    }
//
//    while( position < sectionEnd ) 
//    {
//        if( !ReadAdditionalLayerInfoSignature() )
//            return false;
//
//        char key[5] ={0}; // 4 characters + null termination
//        mFileHandle->Read((uint8*)key,4);
//
//        uint32_t len;
//        mFileHandle->Read( (uint8*) &len, 4);
//        FOdysseyMathUtils::ByteSwap( &len, 4);
//        //UE_LOG(LogTemp, Display, TEXT("len: %d"), len);
//
//        position = mFileHandle->Tell();
//
//        if(strcmp(key,"Lr16") == 0 || strcmp(key,"Lr32") == 0)
//        {
//            ReadLayers();
//            break;
//        } 
//        else if( strcmp(key,"Mt32") == 0 )
//        {
//            mFileHandle->Seek(mFileHandle->Tell() + len);
//            ReadAdditionalLayerInfo(sectionEnd);
//        }
//        else 
//        {
//            mFileHandle->Seek( mFileHandle->Tell() + len );
//            position += len + 4 + 4 + 4;
//        }
//    }
//    return true;
//}
//
///*bool FOdysseyPsdOperations::ReadImageData()
//{
//    if( mImageStart == 0 )
//        return false;
//    if( mImageDst != nullptr )
//    {
//        delete [] mImageDst;
//        mImageDst = nullptr;
//    }
//    mFileHandle->Seek( mImageStart );
//    uint16_t compressionType;
//    mFileHandle->Read( (uint8*) &compressionType, 2 );
//    FOdysseyMathUtils::ByteSwap( &compressionType, 2 );
//    int srcChannelsNumber = mChannelsNumber;
//    if( mChannelsNumber > 4 )
//        srcChannelsNumber = 4; //We're limiting the channels to 4 and try to translate it into RGBA
//    if( mBitDepth > 8 )
//    {
//        uint32_t size = mImageWidth * mImageHeight * srcChannelsNumber;
//        mImageDst16 = new uint16_t[size];
//        if( compressionType == 0 ) //Uncompressed
//        {
//            uint16_t* planarDst = new uint16_t[size];
//            CopyUncompressed(planarDst, size);
//            PlanarByteConvert(planarDst,mImageDst16,size,mChannelsNumber);
//            delete [] planarDst;
//        }
//        else if(compressionType == 1) //RLE 16 Bits
//        {
//            uint16_t* planarDst = new uint16_t[size];
//            mFileHandle->Seek( mFileHandle->Tell() + mImageHeight * srcChannelsNumber * 2 );
//            DecodeAndCopyRLE(planarDst,size);
//            PlanarByteConvert(planarDst,mImageDst16,size,mChannelsNumber);
//            delete [] planarDst;
//        }
//        else
//        {
//            UE_LOG(LogTemp,Warning,TEXT("Compression type unknown, import failed"));
//            return false;
//        }
//    }
//    else 
//    {
//        uint32_t size =  mImageWidth * mImageHeight * srcChannelsNumber;
//        mImageDst = new uint8_t[ size ];
//        if( compressionType == 0 ) // uncompressed
//        {
//            uint8_t* planarDst = new uint8_t[size];
//            CopyUncompressed( mImageDst, size );
//            PlanarByteConvert(planarDst,mImageDst,size,mChannelsNumber);
//            delete [] planarDst;
//        } 
//        else if(compressionType == 1) //RLE
//        {
//            uint8_t* planarDst = new uint8_t[size];
//            mFileHandle->Seek( mFileHandle->Tell() + mImageHeight * mChannelsNumber * 2 );
//            DecodeAndCopyRLE( planarDst, size );
//            PlanarByteConvert( planarDst, mImageDst, size, mChannelsNumber );
//            delete [] planarDst;
//        } 
//        else 
//        {
//            UE_LOG(LogTemp,Warning,TEXT("Compression type unknown, import failed"));
//            return false;
//        }
//    }
//    return true;
//}*/
//
//bool FPSDOperations::ReadLayerStackData()
//{
//    for( uint8_t i = 0; i < mLayersInfo.Num(); i++) 
//    {
//        //UE_LOG(LogTemp, Display, TEXT("Layer Number %d"), i)
//        uint8_t** channelContents = new uint8_t*[mLayersInfo[i].mNumChannels];
//
//        int lx = mLayersInfo[i].mLeft;
//        int ly = mLayersInfo[i].mTop;
//        int lw = mLayersInfo[i].mRight;
//        int lh = mLayersInfo[i].mBottom;
//        uint32_t channelSize =  (lw - lx) * (lh - ly);
//        //UE_LOG(LogTemp, Display, TEXT("CHannelSize layer %d: %d"), i, channelSize );
//
//        for(uint8_t j = 0; j < mLayersInfo[i].mNumChannels; j++) 
//        {
//            //UE_LOG(LogTemp,Display,TEXT("ChannelStart layer %d channel %d: %d"),i, j, mLayersInfo[i].mStartChannelPos[j]);
//
//            //Future TODO: add masks gestion here when we'll have them
//
//            mFileHandle->Seek( mLayersInfo[i].mStartChannelPos[j] );
//            uint16_t cp;
//            mFileHandle->Read( (uint8*) &cp, 2);
//            FOdysseyMathUtils::ByteSwap( &cp, 2 );
//            //UE_LOG(LogTemp, Display, TEXT ("LayerCompression: %d" ), cp );
//
//            channelContents[j] = new uint8_t[channelSize];
//
//            if( cp == 0 ) //No compression
//            {
//                CopyUncompressed( channelContents[j], channelSize );
//                mLayersInfo[i].mSizeLayerImage += channelSize;
//            }
//            else if ( cp == 1 ) //RLE
//            {
//                mFileHandle->Seek(mFileHandle->Tell() + (lh - ly) * 2);
//                DecodeAndCopyRLE(channelContents[j],channelSize);
//                mLayersInfo[i].mSizeLayerImage += channelSize;
//            }
//            else
//            {
//                UE_LOG(LogTemp, Warning, TEXT ("Unknown or unsupported Compression, import failed" ))
//                return false;
//            }
//
//            if(mColorMode == 4 && j != 0)//CMYK, we negate everything but the alpha
//                NegateImage(channelContents[j],channelSize);
//        }
//
//        uint8_t* planarDst = new uint8_t[mLayersInfo[i].mSizeLayerImage];
//        mLayersInfo[i].mLayerImageDst = new uint8_t[ mLayersInfo[i].mSizeLayerImage ];
//
//        uint32_t numBytesWritten = 0;
//        for ( uint16_t currChannel = 0; currChannel < mLayersInfo[i].mNumChannels; currChannel++ )
//        {
//            for( uint32_t currWrite = 0; currWrite < channelSize; currWrite++)
//            {
//                planarDst[numBytesWritten] = channelContents[currChannel][currWrite];
//                numBytesWritten++;
//            }
//        }
//
//        PlanarByteConvert(planarDst,mLayersInfo[i].mLayerImageDst,mLayersInfo[i].mSizeLayerImage,mLayersInfo[i].mNumChannels);
//
//        //UE_LOG(LogTemp, Display, TEXT("size: %d, written: %d"), mLayersInfo[i].mSizeLayerImage, numBytesWritten )
//
//        delete [] planarDst;
//
//        for( int chan = 0; chan < mLayersInfo[i].mNumChannels; chan++)
//            delete [] channelContents[chan];
//
//        delete [] channelContents;
//    }
//
//    return true;
//}
//
//bool FPSDOperations::ReadLayerStackData16()
//{
//    for(uint8_t i = 0; i < mLayersInfo.Num(); i++)
//    {
//        //UE_LOG(LogTemp, Display, TEXT("Layer Number %d"), i)
//        uint16_t** channelContents = new uint16_t*[mLayersInfo[i].mNumChannels];
//
//        int ll = mLayersInfo[i].mLeft;
//        int lt = mLayersInfo[i].mTop;
//        int lr = mLayersInfo[i].mRight;
//        int lb = mLayersInfo[i].mBottom;
//        uint32_t channelSize =  (lr - ll) * (lb - lt);
//
//        //UE_LOG(LogTemp, Display, TEXT("CHannelSize layer %d: %d"), i, channelSize );
//
//        for(uint8_t j = 0; j < mLayersInfo[i].mNumChannels; j++)
//        {
//            //UE_LOG(LogTemp,Display,TEXT("ChannelStart layer %d channel %d: %d"),i, j, mLayersInfo[i].mStartChannelPos[j]);
//
//            //Future TODO: add masks gestion here when we'll have them
//
//            mFileHandle->Seek(mLayersInfo[i].mStartChannelPos[j]);
//            uint16_t cp;
//            mFileHandle->Read((uint8*)&cp,2);
//            FOdysseyMathUtils::ByteSwap(&cp,2);
//            //UE_LOG(LogTemp, Display, TEXT ("LayerCompression: %d" ), cp );
//
//            channelContents[j] = new uint16_t[channelSize];
//
//            if(cp == 0) //No compression
//            {
//                CopyUncompressed(channelContents[j],channelSize);
//                mLayersInfo[i].mSizeLayerImage += channelSize;
//            } 
//            else if(cp == 1) //RLE
//            {
//                mFileHandle->Seek(mFileHandle->Tell() + (lb - lt) * 2);
//                DecodeAndCopyRLE(channelContents[j],channelSize);
//                mLayersInfo[i].mSizeLayerImage += channelSize;
//            } 
//            else if( (cp == 2 || cp == 3) )
//            {
//                uLongf dstSize = channelSize * sizeof( uint16_t );
//                uLongf srcSize = mLayersInfo[i].mChannelSize[j];
//                uint8* srcData = new uint8[srcSize];
//                mFileHandle->Read( srcData, srcSize );
//
//                int zResult = uncompress( (uint8*)channelContents[j], &dstSize, srcData, srcSize );
//
//                if( cp == 3 )
//                    UnpredictZip16( (uint8*)channelContents[j], channelSize * sizeof( uint16_t ), lr - ll, (lr - ll) * sizeof( uint16_t) );
//
//                for( uint32_t currShort = 0; currShort < channelSize; currShort++ )
//                {
//                    FOdysseyMathUtils::ByteSwap( &channelContents[j][currShort], 2 );
//                }
//
//                mLayersInfo[i].mSizeLayerImage += channelSize;
//
//                //UE_LOG(LogTemp, Display, TEXT("returnErrCode: %d"), zResult);
//                delete [] srcData;
//            }
//            else
//            {
//                UE_LOG(LogTemp,Warning,TEXT ("Unknown or unsupported Compression, import failed"))
//                    return false;
//            }
//
//            if(mColorMode == 4 && j != 0)//CMYK, we negate everything but the alpha
//                NegateImage(channelContents[j],channelSize);
//        }
//
//        uint16_t* planarDst = new uint16_t[mLayersInfo[i].mSizeLayerImage];
//        mLayersInfo[i].mLayerImageDst16 = new uint16_t[mLayersInfo[i].mSizeLayerImage];
//
//        uint32_t numShortWritten = 0;
//        for(uint16_t currChannel = 0; currChannel < mLayersInfo[i].mNumChannels; currChannel++)
//        {
//            for(uint32_t currWrite = 0; currWrite < channelSize; currWrite++)
//            {
//                planarDst[numShortWritten] = channelContents[currChannel][currWrite];
//                numShortWritten++;
//            }
//        }
//
//        PlanarByteConvert(planarDst,mLayersInfo[i].mLayerImageDst16,mLayersInfo[i].mSizeLayerImage,mLayersInfo[i].mNumChannels);
//
//        //UE_LOG(LogTemp, Display, TEXT("size: %d, written: %d"), mLayersInfo[i].mSizeLayerImage, numBytesWritten )
//
//        delete[] planarDst;
//
//        for(int chan = 0; chan < mLayersInfo[i].mNumChannels; chan++)
//            delete[] channelContents[chan];
//
//        delete[] channelContents;
//    }
//
//    return true;
//}
//
//bool FPSDOperations::ReadLayerStackData32()
//{
//    for(uint8_t i = 0; i < mLayersInfo.Num(); i++)
//    {
//        //UE_LOG(LogTemp, Display, TEXT("Layer Number %d"), i)
//        uint32_t** channelContents = new uint32_t*[mLayersInfo[i].mNumChannels];
//
//        int ll = mLayersInfo[i].mLeft;
//        int lt = mLayersInfo[i].mTop;
//        int lr = mLayersInfo[i].mRight;
//        int lb = mLayersInfo[i].mBottom;
//        uint32_t channelSize =  (lr - ll) * (lb - lt);
//
//        //UE_LOG(LogTemp, Display, TEXT("CHannelSize layer %d: %d"), i, channelSize );
//
//        for(uint8_t j = 0; j < mLayersInfo[i].mNumChannels; j++)
//        {
//            //UE_LOG(LogTemp,Display,TEXT("ChannelStart layer %d channel %d: %d"),i, j, mLayersInfo[i].mStartChannelPos[j]);
//
//            //Future TODO: add masks gestion here when we'll have them
//
//            mFileHandle->Seek(mLayersInfo[i].mStartChannelPos[j]);
//            uint16_t cp;
//            mFileHandle->Read((uint8*)&cp,2);
//            FOdysseyMathUtils::ByteSwap(&cp,2);
//            //UE_LOG(LogTemp, Display, TEXT ("LayerCompression: %d" ), cp );
//
//            channelContents[j] = new uint32_t[channelSize];
//
//            if(cp == 0) //No compression
//            {
//                CopyUncompressed(channelContents[j],channelSize);
//                mLayersInfo[i].mSizeLayerImage += channelSize;
//            } 
//            else if(cp == 1) //RLE
//            {
//                mFileHandle->Seek(mFileHandle->Tell() + (lb - lt) * 2);
//                DecodeAndCopyRLE(channelContents[j],channelSize);
//                mLayersInfo[i].mSizeLayerImage += channelSize;
//            } 
//            else if((cp == 2 || cp == 3))
//            {
//                uLongf dstSize = channelSize * sizeof(uint32_t);
//                uLongf srcSize = mLayersInfo[i].mChannelSize[j];
//                uint8* srcData = new uint8[srcSize];
//                uint32_t* dstData = new uint32_t[channelSize];
//
//                mFileHandle->Read(srcData,srcSize);
//
//                int zResult = uncompress((uint8*)dstData,&dstSize,srcData,srcSize);
//
//                if(cp == 3)
//                    UnpredictZip32((uint8*)dstData, (uint8*)channelContents[j], channelSize * sizeof(uint32_t),lr - ll, lb - lt, (lr - ll) * sizeof(uint32_t));
//
//                for(uint32_t currLong = 0; currLong < channelSize; currLong++)
//                {
//                    //channelContents[j][currLong] = channelContents[j][currLong] >> 8;
//                    FOdysseyMathUtils::ByteSwap(&channelContents[j][currLong],4);
//                    //channelContents[j][currLong]*=255;
//                }
//
//                mLayersInfo[i].mSizeLayerImage += channelSize;
//
//                //UE_LOG(LogTemp, Display, TEXT("returnErrCode: %d"), zResult);
//                delete[] srcData;
//                delete[] dstData;
//            } 
//            else
//            {
//                UE_LOG(LogTemp,Warning,TEXT ("Unknown or unsupported Compression, import failed"))
//                    return false;
//            }
//
//            //lerp24BitsInto32Bits( channelContents[j], channelSize );
//
//            if(mColorMode == 4 && mLayersInfo[i].mID[j] != -1)//CMYK, we negate everything but the alpha
//                NegateImage(channelContents[j],channelSize);
//        }
//
//        uint32_t* planarDst = new uint32_t[mLayersInfo[i].mSizeLayerImage];
//        mLayersInfo[i].mLayerImageDst32 = new uint32_t[mLayersInfo[i].mSizeLayerImage];
//
//        uint32_t numLongWritten = 0;
//        for(uint16_t currChannel = 0; currChannel < mLayersInfo[i].mNumChannels; currChannel++)
//        {
//            for(uint32_t currWrite = 0; currWrite < channelSize; currWrite++)
//            {
//                planarDst[numLongWritten] = channelContents[currChannel][currWrite];
//                numLongWritten++;
//            }
//        }
//
//        PlanarByteConvert(planarDst,mLayersInfo[i].mLayerImageDst32,mLayersInfo[i].mSizeLayerImage,mLayersInfo[i].mNumChannels);
//
//        //UE_LOG(LogTemp, Display, TEXT("size: %d, written: %d"), mLayersInfo[i].mSizeLayerImage, numBytesWritten )
//
//        delete[] planarDst;
//
//        for(int chan = 0; chan < mLayersInfo[i].mNumChannels; chan++)
//            delete[] channelContents[chan];
//
//        delete[] channelContents;
//    }
//
//    return true;
//}
//
//void FPSDOperations::GenerateLayerStackFromLayerStackData()
//{
//    ::ul3::tFormat format;
//
//    if(mBitDepth > 8)
//        format = ULISFormatForUE4TextureSourceFormat(ETextureSourceFormat::TSF_RGBA16);
//    else
//        format = ULISFormatForUE4TextureSourceFormat(ETextureSourceFormat::TSF_BGRA8);
//
//    if( mLayersInfo.Num() != 0 )
//    {
//        mLayerStack = new FOdysseyLayerStack();
//        mLayerStack->Init(mImageWidth,mImageHeight,format);
//    }
//
//    //Special case: bitmap --------------------------------------
//    if( mColorMode == 0  /*BitMap*/ ) //If we're dealing with bitmap, the data is at ImgDst, and not in the layers info
//    {
//        if( mImageStart == 0 )
//            return;
//
//        if(mImageDst != nullptr)
//        {
//            delete[] mImageDst;
//            mImageDst = nullptr;
//        }
//
//        mLayerStack = new FOdysseyLayerStack();
//        mLayerStack->Init(mImageWidth,mImageHeight,format);
//
//        mFileHandle->Seek(mImageStart);
//
//        uint16_t compressionType;
//        mFileHandle->Read((uint8*)&compressionType,2);
//        FOdysseyMathUtils::ByteSwap(&compressionType,2);
//
//        uint32_t size =  mImageWidth * mImageHeight * 4; //Converted to BGRA -> 4 channels;
//        mImageDst = new uint8_t[size];
//
//        if(compressionType == 0) // uncompressed
//        {
//            uint8_t* planar = new uint8_t[(mImageWidth * mImageHeight) / 8 + 1];
//            CopyUncompressed(planar,size);
//            PlanarByteConvertBitMapToBGRA8( planar, mImageDst, (mImageWidth * mImageHeight) / 8 + 1 );
//            delete[] planar;
//        } 
//        else if(compressionType == 1) //RLE
//        {
//            uint32_t sizeBitmap = (mImageWidth * mImageHeight) / 8 + 1;
//            uint8_t* planar = new uint8_t[sizeBitmap];
//            mFileHandle->Seek(mFileHandle->Tell() + mImageHeight * 2);
//            DecodeAndCopyRLE(planar,sizeBitmap);
//            PlanarByteConvertBitMapToBGRA8(planar,mImageDst,sizeBitmap);
//            delete[] planar;
//        }
//        ::ul3::FBlock* srcblock = new ::ul3::FBlock((::ul3::tByte*)mImageDst,mImageWidth,mImageHeight,ULIS3_FORMAT_BGRA8);;
//        FOdysseyBlock* layerBlock = new FOdysseyBlock(mImageWidth,mImageHeight,ULIS3_FORMAT_BGRA8);
//
//        IULISLoaderModule& hULIS = IULISLoaderModule::Get();
//        ::ul3::uint32 MT_bit = ULIS3_PERF_MT;
//        ::ul3::uint32 perfIntent = MT_bit | ULIS3_PERF_SSE42;
//
//
//        ::ul3::Copy(hULIS.ThreadPool()
//                            ,ULIS3_BLOCKING
//                            ,perfIntent
//                            ,hULIS.HostDeviceInfo()
//                            ,ULIS3_NOCB
//                            ,srcblock
//                            ,layerBlock->GetBlock()
//                            ,srcblock->Rect()
//                            ,::ul3::FVec2I(0,0));
//
//        TSharedPtr<FOdysseyImageLayer> imageLayer = MakeShareable(new FOdysseyImageLayer(TEXT("Layer1"),layerBlock));
//        mLayerStack->AddLayer( imageLayer );
//
//        delete srcblock;
//    }
//    //-----------------------------------------------------------
//
//    TSharedPtr<IOdysseyLayer> currentRoot = mLayerStack->GetCurrentLayer();
//
//    for( int i = mLayersInfo.Num() - 1; i >= 0; i-- )
//    {
//        if( mLayersInfo[i].mDividerType == 0 ) //Rasterizable layer
//        {
//            FName layerName = FName(mLayersInfo[i].mName);
//            uint32_t w = mLayersInfo[i].mRight - mLayersInfo[i].mLeft;
//            uint32_t h = mLayersInfo[i].mBottom - mLayersInfo[i].mTop;
//
//            ::ul3::FBlock* srcblock;
//            FOdysseyBlock* convBlock;
//            FOdysseyBlock* layerBlock;
//
//            if( mBitDepth == 32 )
//            {
//                switch(mColorMode)
//                {
//                    case 1: //GrayScale
//                    {
//                        if(mLayersInfo[i].mNumChannels == 2)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst32,w,h,ULIS3_FORMAT_AGF);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst32,w,h,ULIS3_FORMAT_GF);
//                        break;
//                    }
//                    case 3: //RGB
//                    {
//                        if(mLayersInfo[i].mNumChannels == 4)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst32,w,h,ULIS3_FORMAT_ARGBF);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst32,w,h,ULIS3_FORMAT_RGBF);
//                        break;
//                    }
//                    case 4: //CMYK
//                    {
//                        if(mLayersInfo[i].mNumChannels == 5)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst32,w,h,ULIS3_FORMAT_ACMYKF);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst32,w,h,ULIS3_FORMAT_CMYKF);
//                        break;
//                    }
//                    case 9: //LAB
//                    {
//                        if(mLayersInfo[i].mNumChannels == 4)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst32,w,h,ULIS3_FORMAT_ALabF);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst32,w,h,ULIS3_FORMAT_LabF);
//                        break;
//                    }
//                    default: //ERROR
//                        return;
//                }
//
//                //We don't handle drawing on 32 bits, so we convert to 16 bits
//                convBlock =  new FOdysseyBlock(w,h,ULIS3_FORMAT_RGBA16);
//                layerBlock = new FOdysseyBlock(mImageWidth,mImageHeight,ULIS3_FORMAT_RGBA16);
//            }
//            else if( mBitDepth == 16 )
//            {
//                switch (mColorMode)
//                {
//                    case 1: //GrayScale
//                    {
//                        if(mLayersInfo[i].mNumChannels == 2)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst16,w,h,ULIS3_FORMAT_AG16);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst16,w,h,ULIS3_FORMAT_G16);
//                        break;
//                    }
//                    case 3: //RGB
//                    {
//                        if( mLayersInfo[i].mNumChannels == 4 )
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst16,w,h,ULIS3_FORMAT_ARGB16);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst16,w,h,ULIS3_FORMAT_RGB16);
//                        break;
//                    }
//                    case 4: //CMYK
//                    {
//                        if( mLayersInfo[i].mNumChannels == 5 )
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst16,w,h,ULIS3_FORMAT_ACMYK16);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst16,w,h,ULIS3_FORMAT_CMYK16);
//                        break;
//                    }
//                    case 9: //LAB
//                    {
//                        if(mLayersInfo[i].mNumChannels == 4)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst16,w,h,ULIS3_FORMAT_ALab16);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst16,w,h,ULIS3_FORMAT_Lab16);
//                        break;
//                    }
//                    default: //ERROR
//                        return;
//                }
//
//                convBlock =  new FOdysseyBlock(w,h,ULIS3_FORMAT_RGBA16);
//                layerBlock = new FOdysseyBlock(mImageWidth,mImageHeight,ULIS3_FORMAT_RGBA16);
//            }
//            else if( mBitDepth == 8 )
//            {
//                switch(mColorMode)
//                {
//                    case 1: //GrayScale
//                    {
//                        if(mLayersInfo[i].mNumChannels == 2)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst,w,h,ULIS3_FORMAT_AG8);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst,w,h,ULIS3_FORMAT_G8);
//                        break;
//                    }
//                    case 3: //RGB
//                    {
//                        if(mLayersInfo[i].mNumChannels == 4)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst,w,h,ULIS3_FORMAT_ARGB8);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst,w,h,ULIS3_FORMAT_RGB8);
//                        break;
//                    }
//                    case 4: //CMYK
//                    {
//                        if(mLayersInfo[i].mNumChannels == 5)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst,w,h,ULIS3_FORMAT_ACMYK8);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst,w,h,ULIS3_FORMAT_CMYK8);
//                        break;
//                    }
//                    case 9: //LAB
//                    {
//                        if(mLayersInfo[i].mNumChannels == 4)
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst,w,h,ULIS3_FORMAT_ALab8);
//                        else
//                            srcblock = new ::ul3::FBlock((::ul3::tByte*)mLayersInfo[i].mLayerImageDst,w,h,ULIS3_FORMAT_Lab8);
//                        break;
//                    }
//                    default: //ERROR
//                        return;
//                }
//
//                convBlock =  new FOdysseyBlock(w,h,ULIS3_FORMAT_BGRA8);
//                layerBlock = new FOdysseyBlock(mImageWidth,mImageHeight,ULIS3_FORMAT_BGRA8);
//            }
//            else
//            {
//                UE_LOG(LogTemp, Warning, TEXT("Error: we don't handle this bit depth, import failed" ))
//                return;
//            }
//
//            IULISLoaderModule& hULIS = IULISLoaderModule::Get();
//            ::ul3::uint32 MT_bit = ULIS3_PERF_MT;
//            ::ul3::uint32 perfIntent = MT_bit | ULIS3_PERF_SSE42;
//            
//            ::ul3::Clear( hULIS.ThreadPool(), ULIS3_BLOCKING, perfIntent, hULIS.HostDeviceInfo(), ULIS3_NOCB, layerBlock->GetBlock(), layerBlock->GetBlock()->Rect() );
//            ::ul3::Conv(hULIS.ThreadPool(),ULIS3_BLOCKING,perfIntent,hULIS.HostDeviceInfo(),ULIS3_NOCB,srcblock,convBlock->GetBlock());
//            ::ul3::Copy(hULIS.ThreadPool()
//                                ,ULIS3_BLOCKING
//                                ,perfIntent
//                                ,hULIS.HostDeviceInfo()
//                                ,ULIS3_NOCB
//                                ,convBlock->GetBlock()
//                                ,layerBlock->GetBlock()
//                                ,srcblock->Rect()
//                                ,::ul3::FVec2I( mLayersInfo[i].mLeft, mLayersInfo[i].mTop ));
//
//            TSharedPtr<FOdysseyImageLayer> imageLayer = MakeShareable(new FOdysseyImageLayer(layerName,layerBlock));
//            if( currentRoot->GetType() == IOdysseyLayer::eType::kFolder )
//                mLayerStack->AddLayer( imageLayer, currentRoot );
//            else
//                mLayerStack->AddLayer( imageLayer );
//
//            imageLayer->SetOpacity( (float)mLayersInfo[i].mOpacity / 255.0 );
//            imageLayer->SetIsAlphaLocked(mLayersInfo[i].mFlags & 0x01);
//            imageLayer->SetIsVisible(!(mLayersInfo[i].mFlags & 0x02));
//            imageLayer->SetBlendingMode( GetBlendingModeFromPSD(mLayersInfo[i].mBlendModeKey) );
//            
//            //UE_LOG(LogTemp,Display,TEXT("flags: %d"),mLayersInfo[i].mFlags)
//            //Todo: Locked
//
//            delete srcblock;
//            delete convBlock;
//            //delete layerBlock;
//
//        }
//        else if( mLayersInfo[i].mDividerType == 1 || mLayersInfo[i].mDividerType == 2 ) //Open folder / Closed Folder
//        {
//            FName layerName = FName(mLayersInfo[i].mName);
//            TSharedPtr<FOdysseyFolderLayer> folderLayer = MakeShareable(new FOdysseyFolderLayer( layerName ));
//
//            if(currentRoot->GetType() == IOdysseyLayer::eType::kFolder )
//                mLayerStack->AddLayer(folderLayer,currentRoot);
//            else
//                mLayerStack->AddLayer(folderLayer);
//
//            currentRoot = folderLayer;
//
//            folderLayer->SetOpacity((float)mLayersInfo[i].mOpacity / 255.0);
//            folderLayer->SetIsVisible(!(mLayersInfo[i].mFlags & 0x02));
//            folderLayer->SetBlendingMode( GetBlendingModeFromPSD(mLayersInfo[i].mBlendModeKey) );
//
//            //UE_LOG(LogTemp, Display, TEXT("flags: %d"), mLayersInfo[i].mFlags)
//
//            //UE_LOG(LogTemp,Display,TEXT("Open folder"));
//        }
//        else if( mLayersInfo[i].mDividerType == 3 ) //Break -> Exit current folder
//        {
//            currentRoot = currentRoot->GetParent();
//        }
//    }
//}
//
//void FPSDOperations::CopyUncompressed(uint32_t* dst,uint32_t length)
//{
//    for(uint32_t i = 0; i < length; i++)
//    {
//        mFileHandle->Read((uint8*) &(dst[i]),4);
//        FOdysseyMathUtils::ByteSwap(&(dst[i]),4);
//    }
//}
//
//void FPSDOperations::CopyUncompressed(uint16_t* dst, uint32_t length)
//{
//    for( uint32_t i = 0; i < length; i++ )
//    {
//        mFileHandle->Read( (uint8*) &(dst[i]), 2 );
//        FOdysseyMathUtils::ByteSwap( &(dst[i]), 2 );
//    }
//}
//
//void FPSDOperations::CopyUncompressed(uint8_t* dst, uint32_t length)
//{
//    mFileHandle->Read((uint8*) dst, length);
//}
//
//void FPSDOperations::DecodeAndCopyRLE(uint32_t* dst,uint32_t length)
//{
//    while(length > 0)
//    {
//        int32_t k;
//        mFileHandle->Read((uint8*)&k,4);
//        FOdysseyMathUtils::ByteSwap(&k,4);
//
//        if(k >= 0)
//        {
//            uint32_t n = k + 1;
//            if(n > length)
//                n = length;
//
//            for(uint32_t i = 0; i < n; i++)
//            {
//                mFileHandle->Read((uint8*)dst,n);
//                FOdysseyMathUtils::ByteSwap(&dst,4);
//                dst++;
//            }
//            length -= n;
//        } else
//        {
//            uint32_t n = -k + 1;
//            if(n > length)
//                n = length;
//
//            uint32_t fileLong;
//            mFileHandle->Read((uint8*)&fileLong,4);
//            FOdysseyMathUtils::ByteSwap(&fileLong,4);
//
//            for(uint32_t i = 0; i < n; i++)
//                *dst++ = fileLong;
//
//            length -= n;
//        }
//    }
//}
//
//void FPSDOperations::DecodeAndCopyRLE(uint16_t* dst,uint32_t length)
//{
//    while( length > 0 )
//    {
//        int16_t k;
//        mFileHandle->Read( (uint8*) &k, 2 );
//        FOdysseyMathUtils::ByteSwap( &k, 2 );
//
//        if(k >= 0)
//        {
//            uint32_t n = k + 1;
//            if( n > length )
//                n = length;
//
//            for( uint32_t i = 0; i < n; i++ )
//            {
//                mFileHandle->Read((uint8*)dst,n);
//                FOdysseyMathUtils::ByteSwap( &dst, 2 );
//                dst++;
//            }
//            length -= n;
//        }
//        else
//        {
//            uint32_t n = -k + 1;
//            if(n > length)
//                n = length;
//
//            uint16_t fileShort;
//            mFileHandle->Read((uint8*)&fileShort,2);
//            FOdysseyMathUtils::ByteSwap( &fileShort, 2 );
//
//            for(uint32_t i = 0; i < n; i++)
//                *dst++ = fileShort; 
//
//            length -= n;
//        }
//    }
//}
//
//void FPSDOperations::DecodeAndCopyRLE(uint8_t* dst, uint32_t length)
//{
//    //uint32_t numBytesRead = 0;
//    while( length > 0 )
//    {
//        char k;
//        mFileHandle->Read( (uint8*) &k, 1 );
//
//        if(k >= 0) 
//        {
//            uint32_t n = k + 1;
//            if(n > length)
//                n = length;
//
//            mFileHandle->Read( (uint8*) dst, n );
//            //numBytesRead += n;
//
//            dst += n;
//            length -= n;
//        } 
//        else 
//        {
//            uint32_t n = -k + 1;
//            if(n > length)
//                n = length;
//
//            uint8_t fileByte;
//            mFileHandle->Read( (uint8*) &fileByte, 1 );
//            //numBytesRead ++;
//
//            memset(dst,fileByte,n);
//
//            dst += n;
//            length -= n;
//        }
//    }
//    //UE_LOG(LogTemp, Display, TEXT("%d"), numBytesRead)
//}
//
//void FPSDOperations::UnpredictZip16(uint8_t* dst,uint32_t length, uint32_t numColumns, uint32_t rowSize)
//{
//    while (length > 0)
//    {
//        uint32_t c = numColumns;
//        while( --c )
//        {
//            dst[2]+=dst[0]+((dst[1]+dst[3]) >> 8);
//            dst[3]+=dst[1];
//            dst+=2;
//        }
//        dst+=2;
//        length-=rowSize;
//    }
//}
//
//void FPSDOperations::UnpredictZip32(uint8* src, uint8* dst, uint32_t length,uint32_t numColumns, uint32_t numRows, uint32_t rowSize)
//{
//    uint32 remaining;
//    uint8* start;
//
//    for(uint32_t y = 0; y < numRows; y++)
//    {
//        start=src;
//        remaining=rowSize;
//        while(--remaining)
//        {
//            *(src+1)+=*src;
//            src++;
//        }
//
//        src=start;
//        remaining=numColumns;
//        while(remaining--)
//        {
//            *(dst++)=*src;
//            *(dst++)=*(src + numColumns);
//            *(dst++)=*(src + numColumns * 2);
//            *(dst++)=*(src + numColumns * 3);
//
//            src++;
//        }
//        src=start+rowSize;
//    }
//}
//
//void FPSDOperations::PlanarByteConvertBitMapToBGRA8(uint8_t* src,uint8_t* dst,uint32_t length)
//{
//    unsigned int mask = 1U << 7;
//    for( uint32_t i = 0; i < length; i++ )
//    {
//        for(int j = 0; j < 8; j++)
//        {
//            dst[i*8*4 + j*4] = ((src[i] & mask) ? 0 : 1) * 255;
//            dst[i*8*4 + j*4 + 1] = dst[i*8*4 + j*4];
//            dst[i*8*4 + j*4 + 2] = dst[i*8*4 + j*4];
//            dst[i*8*4 + j*4 + 3] = 255;
//
//            src[i] <<= 1;
//        }
//    }
//}
//
//
//
//void FPSDOperations::PlanarByteConvertOrdered(uint8_t* src,uint8_t* dst,uint32_t length,uint8_t numChannels,uint8_t channelsOrder[])
//{
//    uint32_t maxByChannel = length / numChannels;
//    for(uint32_t i = 0; i < maxByChannel; i++)
//    {
//        for(uint16_t j = 0; j < numChannels; j++)
//        {
//            dst[i * numChannels + channelsOrder[j]] = src[i + j * maxByChannel];
//        }
//    }
//}
//
//void FPSDOperations::PlanarByteConvertOrdered(uint16_t* src,uint16_t* dst,uint32_t length,uint8_t numChannels,uint8_t channelsOrder[])
//{
//    uint32_t maxByChannel = length / numChannels;
//    for(uint32_t i = 0; i < maxByChannel; i++)
//    {
//        for(uint16_t j = 0; j < numChannels; j++)
//        {
//            dst[i * numChannels + channelsOrder[j]] = src[i + j * maxByChannel];
//        }
//    }
//}
//
//void FPSDOperations::PlanarByteConvert( uint8_t* src, uint8_t* dst, uint32_t length, uint8_t numChannels )
//{
//    uint32_t maxByChannel = length / numChannels;
//    for( uint32_t i = 0; i < maxByChannel; i++ )
//    {
//        for (uint16_t j = 0; j < numChannels; j++)
//        {
//            dst[i * numChannels + j] = src[i + j * maxByChannel];
//        }
//    }
//}
//
//void FPSDOperations::PlanarByteConvert(uint16_t* src,uint16_t* dst,uint32_t length,uint8_t numChannels)
//{
//    uint32_t maxByChannel = length / numChannels;
//    for(uint32_t i = 0; i < maxByChannel; i++)
//    {
//        for(uint16_t j = 0; j < numChannels; j++)
//        {
//            dst[i * numChannels + j] = src[i + j * maxByChannel];
//        }
//    }
//}
//
//void FPSDOperations::PlanarByteConvert(uint32_t* src,uint32_t* dst,uint32_t length,uint8_t numChannels)
//{
//    uint32_t maxByChannel = length / numChannels;
//    for(uint32_t i = 0; i < maxByChannel; i++)
//    {
//        for(uint16_t j = 0; j < numChannels; j++)
//        {
//            dst[i * numChannels + j] = src[i + j * maxByChannel];
//        }
//    }
//}
//
//void FPSDOperations::NegateImage(uint8_t* ioSrc,uint32_t length )
//{
//    for( uint32_t i = 0; i < length; i++ )
//        ioSrc[i] = MAX_uint8 - ioSrc[i];
//}
//
//void FPSDOperations::NegateImage(uint16_t* ioSrc,uint32_t length )
//{
//    for(uint32_t i = 0; i < length; i++)
//        ioSrc[i] = MAX_uint16 - ioSrc[i];
//}
//
//void FPSDOperations::NegateImage(uint32_t* ioSrc,uint32_t length)
//{
//    for(uint32_t i = 0; i < length; i++)
//        ioSrc[i] = MAX_uint32 - ioSrc[i];
//}
//
//void FPSDOperations::lerp24BitsInto32Bits(uint32_t* ioSrc,uint32_t length)
//{
//    for(uint32_t i = 0; i < length; i++)
//    {
//        ioSrc[i] = ioSrc[i] << 8;
//    }
//}
//
//eBlendMode FPSDOperations::GetBlendingModeFromPSD(char iBlendModeKey[5])
//{
//    if(strcmp(iBlendModeKey,"norm") == 0) { return ::ul3::eBlendingMode::BM_NORMAL; }
//    if(strcmp(iBlendModeKey,"diss") == 0) { return ::ul3::eBlendingMode::BM_DISSOLVE; }
//    if(strcmp(iBlendModeKey,"dark") == 0) { return ::ul3::eBlendingMode::BM_DARKEN; }
//    if(strcmp(iBlendModeKey,"mul ") == 0) { return ::ul3::eBlendingMode::BM_MULTIPLY; }
//    if(strcmp(iBlendModeKey,"idiv") == 0) { return ::ul3::eBlendingMode::BM_COLORBURN; }
//    if(strcmp(iBlendModeKey,"lbrn") == 0) { return ::ul3::eBlendingMode::BM_LINEARBURN; }
//    if(strcmp(iBlendModeKey,"dkCl") == 0) { return ::ul3::eBlendingMode::BM_DARKERCOLOR; }
//    if(strcmp(iBlendModeKey,"lite") == 0) { return ::ul3::eBlendingMode::BM_LIGHTEN; }
//    if(strcmp(iBlendModeKey,"scrn") == 0) { return ::ul3::eBlendingMode::BM_SCREEN; }
//    if(strcmp(iBlendModeKey,"div ") == 0) { return ::ul3::eBlendingMode::BM_COLORDODGE; }
//    if(strcmp(iBlendModeKey,"lddg") == 0) { return ::ul3::eBlendingMode::BM_LINEARDODGE; }
//    if(strcmp(iBlendModeKey,"lgCl") == 0) { return ::ul3::eBlendingMode::BM_LIGHTERCOLOR; }
//    if(strcmp(iBlendModeKey,"over") == 0) { return ::ul3::eBlendingMode::BM_OVERLAY; }
//    if(strcmp(iBlendModeKey,"sLit") == 0) { return ::ul3::eBlendingMode::BM_SOFTLIGHT; }
//    if(strcmp(iBlendModeKey,"hLit") == 0) { return ::ul3::eBlendingMode::BM_HARDLIGHT; }
//    if(strcmp(iBlendModeKey,"vLit") == 0) { return ::ul3::eBlendingMode::BM_VIVIDLIGHT; }
//    if(strcmp(iBlendModeKey,"lLit") == 0) { return ::ul3::eBlendingMode::BM_LINEARLIGHT; }
//    if(strcmp(iBlendModeKey,"pLit") == 0) { return ::ul3::eBlendingMode::BM_PINLIGHT; }
//    if(strcmp(iBlendModeKey,"hMix") == 0) { return ::ul3::eBlendingMode::BM_HARDMIX; }
//    if(strcmp(iBlendModeKey,"diff") == 0) { return ::ul3::eBlendingMode::BM_DIFFERENCE; }
//    if(strcmp(iBlendModeKey,"smud") == 0) { return ::ul3::eBlendingMode::BM_EXCLUSION; }
//    if(strcmp(iBlendModeKey,"fsub") == 0) { return ::ul3::eBlendingMode::BM_SUBSTRACT; }
//    if(strcmp(iBlendModeKey,"fdiv") == 0) { return ::ul3::eBlendingMode::BM_DIVIDE; }
//    if(strcmp(iBlendModeKey,"hue ") == 0) { return ::ul3::eBlendingMode::BM_HUE; }
//    if(strcmp(iBlendModeKey,"sat ") == 0) { return ::ul3::eBlendingMode::BM_SATURATION; }
//    if(strcmp(iBlendModeKey,"colr") == 0) { return ::ul3::eBlendingMode::BM_COLOR; }
//    if(strcmp(iBlendModeKey,"lum ") == 0) { return ::ul3::eBlendingMode::BM_LUMINOSITY; }
//
//    //unknown blending mode, we return the normal one by default
//    return ::ul3::eBlendingMode::BM_NORMAL;
//}
//
//uint16_t FPSDOperations::GetChannelsNumber()
//{
//    return mChannelsNumber;
//}
//
//uint32_t FPSDOperations::GetImageHeight()
//{
//    return mImageHeight;
//}
//
//uint32_t FPSDOperations::GetImageWidth()
//{
//    return mImageWidth;
//}
//
//uint16_t FPSDOperations::GetBitDepth()
//{
//    return mBitDepth;
//}
//
//uint16_t FPSDOperations::GetColorMode()
//{
//    return mColorMode;
//}
//
//uint8_t* FPSDOperations::GetImageDst()
//{
//    return mImageDst;
//}
//
//uint16_t* FPSDOperations::GetImageDst16()
//{
//    return mImageDst16;
//}
//
//FOdysseyLayerStack* FPSDOperations::GetLayerStack()
//{
//    return mLayerStack;
//}
//
//bool FPSDOperations::Import()
//{
//    if(!ReadFileHeader() )
//        return false;
//
//    if(!ReadFileColorMode() )
//        return false;
//
//    if( !ReadImageResources() )
//        return false;
//
//    if( !ReadLayerAndMaskInfo() )
//        return false;
//
//    //We can get it faster by blending the whole layer stack
//    /*if( !ReadImageData() )
//        return false;*/
//    if( mBitDepth == 32)
//    {
//        if(!ReadLayerStackData32())
//            return false;
//    }
//    else if( mBitDepth == 16 )
//    {
//        if( !ReadLayerStackData16() )
//            return false;
//    }
//    else if( mBitDepth == 8 )
//    {
//        if(!ReadLayerStackData())
//            return false;
//    }
//    else
//    {
//        UE_LOG(LogTemp, Warning, TEXT("Unsupported bit depth, Import failed"));
//        return false;
//    }
//
//    GenerateLayerStackFromLayerStackData();
//    
//    return true;
//}

ULIS_NAMESPACE_END

