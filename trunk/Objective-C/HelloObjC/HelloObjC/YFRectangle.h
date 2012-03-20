//
//  YFRectangle.h
//  HelloObjC
//
//  Created by 飞 杨 on 12-3-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class YFPoint2D;//与C++相同的使用含义，可减少文件编译时的依赖关系。

@interface YFRectangle : NSObject
{
    YFPoint2D *points[4];
}
@end
