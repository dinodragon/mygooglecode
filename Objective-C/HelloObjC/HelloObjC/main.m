//
//  main.m
//  HelloObjC
//
//  Created by 飞 杨 on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YFPoint2D.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        
        // insert code here...
        NSLog(@"Hello, World!");
        YFPoint2D *obj = [YFPoint2D new];
        [obj setX:1];
        [obj setY:2];
        [obj show];
        [obj setX:3 setY:4];
        [obj show];        
    }
    return 0;
}

