/*
 * Copyright (c) 2020, NVIDIA CORPORATION. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef __IMAGE_FORMAT_INLINE_H_
#define __IMAGE_FORMAT_INLINE_H_

#include <strings.h>
#include <type_traits>


// imageFormatToStr
inline const char* imageFormatToStr( imageFormat format )
{
	switch(format)
	{
		case FORMAT_RGB8:	 return "rgb8";
		case FORMAT_RGBA8:	 return "rgba8";
		case FORMAT_RGB32:	 return "rgb32";
		case FORMAT_RGBA32:	 return "rgba32";
		case FORMAT_I420:	 return "i420";
		case FORMAT_YV12:	 return "yv12";
		case FORMAT_NV12:	 return "nv12";
		case FORMAT_UYVY:	 return "uyvy";
		case FORMAT_YUYV:	 return "yuyv";
		case FORMAT_GRAY8:	 return "gray8";
		case FORMAT_GRAY32:  return "gray32";
		case FORMAT_UNKNOWN: return "unknown";
	};

	return "unknown";
}


// imageFormatFromStr
inline imageFormat imageFormatFromStr( const char* str )
{
	if( !str )
		return FORMAT_UNKNOWN;

	for( uint32_t n=0; n < FORMAT_COUNT; n++ )
	{
		const imageFormat fmt = (imageFormat)n;

		if( strcasecmp(str, imageFormatToStr(fmt)) == 0 )
			return fmt;
	}

	if( strcasecmp(str, "yuy2") == 0 )
		return FORMAT_YUY2;

	return FORMAT_UNKNOWN;
}


// imageFormatChannels
inline size_t imageFormatChannels( imageFormat format )
{
	switch(format)
	{
		case FORMAT_RGB8:	return 3;
		case FORMAT_RGBA8:	return 4;
		case FORMAT_RGB32:	return 3;
		case FORMAT_RGBA32: return 4;
		case FORMAT_GRAY8:	return 1;
		case FORMAT_GRAY32:	return 1;
		case FORMAT_I420:	return 3;
		case FORMAT_YV12:	return 3;
		case FORMAT_NV12:	return 3;
		case FORMAT_UYVY:	return 3;
		case FORMAT_YUYV:	return 3;
	}

	return 0;
}


// imageFormatDepth
inline size_t imageFormatDepth( imageFormat format )
{
	switch(format)
	{
		case FORMAT_RGB8:	return sizeof(uchar3) * 8;
		case FORMAT_RGBA8:	return sizeof(uchar4) * 8;
		case FORMAT_RGB32:	return sizeof(float3) * 8;
		case FORMAT_RGBA32: return sizeof(float4) * 8;
		case FORMAT_GRAY8:	return sizeof(unsigned char) * 8;
		case FORMAT_GRAY32:	return sizeof(float) * 8;
		case FORMAT_I420:	return 12;
		case FORMAT_YV12:	return 12;
		case FORMAT_NV12:	return 12;
		case FORMAT_UYVY:	return 16;
		case FORMAT_YUYV:	return 16;
	}

	return 0;
}


// imageFormatSize
inline size_t imageFormatSize( imageFormat format, size_t width, size_t height )
{
	return (width * height * imageFormatDepth(format)) / 8;
}


/**
 * @ingroup image
 * @internal
 */
template<typename T> struct assert_false : std::false_type { };


// imageFormatFromType
template<typename T> inline imageFormat imageFormatFromType()	
{ 
	static_assert(assert_false<T>::value, "invalid image format type - supported types are uchar3, uchar4, float3, float4"); 
}

template<> inline imageFormat imageFormatFromType<uchar3>()	{ return FORMAT_RGB8; }
template<> inline imageFormat imageFormatFromType<uchar4>()	{ return FORMAT_RGBA8; }
template<> inline imageFormat imageFormatFromType<float3>()	{ return FORMAT_RGB32; }
template<> inline imageFormat imageFormatFromType<float4>()	{ return FORMAT_RGBA32; }


#endif

