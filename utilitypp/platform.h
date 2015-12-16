//
//  platform.h
//  utilitypp
//
//  Created by tabu on 15/12/16.
//  Copyright © 2015年 tabu. All rights reserved.
//

#ifndef utilitypp_platform_h
#define utilitypp_platform_h

#define __ASSERT(exp)  do{ }while(0);

#ifdef __APPLE__
#define __PLATFORM_DARWIN__
#endif

#if defined ( WIN32 ) || defined ( WIN64)
#define __PLATFORM_WINDOWS__
#elif defined( _ANDROID) || defined( ANDROID )
#ifndef __PLATFORM_ANDROID__
#define __PLATFORM_ANDROID__
#endif // __ANDROID_PLATFORM__
#elif defined( _IPHONE )
#ifndef __PLATFORM_IPHONE__
#define __PLATFORM_IPHONE__
#endif
#endif

#endif /* utilitypp_platform_h */
