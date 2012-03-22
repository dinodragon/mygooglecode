//
//  YFPrinter.m
//  helloproperty
//
//  Created by 飞 杨 on 12-3-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "YFPoint2D.h"

@implementation YFPoint2D(YFPrinter)

-(void) show
{
    NSLog(@"X:%d,Y:%d,Type:%d",x,y,type);
}

@end