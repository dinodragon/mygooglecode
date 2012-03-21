//
//  YFPoint3D.h
//  HelloObjC
//
//  Created by 飞 杨 on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "YFPoint2D.h"

@interface YFPoint3D : YFPoint2D
{
    int z;
}

-(void) setZ:(int)z;
-(void) show;
//-开头的方法叫实例方法。
-(void) setX:(int)a_ setY:(int)b_ setZ:(int)z_;
//+开头的方法叫类方法(class method).相当于静态方法,不通过类实例调用，本质上是没有传入self指针。
+(int) getInitValue; 
@end
