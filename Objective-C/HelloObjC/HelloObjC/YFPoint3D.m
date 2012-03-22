//
//  YFPoint3D.m
//  HelloObjC
//
//  Created by 飞 杨 on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "YFPoint3D.h"

@implementation YFPoint3D

-(id) init
{
    if (self = [super init]) {
        //构造代码。
        z = -1;
    }
    return self;
}

-(void)setZ:(int)z_
{
    z = z_;
}

-(void)show
{
    NSLog(@"Point3d:\rX:%d,Y:%d,Z:%d",self->x,self->y,z);
}

-(void)setX:(int)a_ setY:(int)b_ setZ:(int)z_
{
    [super setX:a_ setY:b_];
    [self setZ:z_];
}

+(int) getInitValue
{
    return -1;
    //return z;
}

//相当于析构函数。
-(void) dealloc
{
    NSLog(@"Call dealloc");
    //[super dealloc];
}
@end
