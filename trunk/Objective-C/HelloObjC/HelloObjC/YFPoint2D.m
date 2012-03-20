//
//  MyClass.m
//  hello
//
//  Created by 飞 杨 on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "YFPoint2D.h"

@implementation YFPoint2D

-(id) init
{
    if (self = [super init]) {
        //构造代码。
        x = -1;
        y = -1;
    }
return self;
}

-(void) show
{
    NSLog(@"Point2d:\rX:%d,Y:%d",self->x,self->y);
}

-(void) setX:(int)x_
{
    self->x = x_;
}

-(void) setY:(int)y_
{
    y = y_;
}

-(void) setX:(int)a_ setY:(int)y_
{
    self->x = a_;
    self->y = y_;	
}

-(NSString *)description
{
    return @"I'm Point2d.";
}
@end
