//
//  main.m
//  helloproperty
//
//  Created by 飞 杨 on 12-3-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YFPoint2D.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        
        // insert code here...
        NSLog(@"Hello, World!");
        YFPoint2D * p2d = [[YFPoint2D alloc] init];
        p2d.x = 1;
        [p2d setY:2];//两种访问方式。y成为属性后，改成了大写。
        p2d.typeValue = 3;
        NSLog(@"X:%d,Y:%d",[p2d x],p2d.y);
        [p2d show];
    }
    return 0;
}

