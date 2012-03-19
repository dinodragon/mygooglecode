//
//  main.m
//  HelloObjC
//
//  Created by 飞 杨 on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "YFPoint2D.h"
#import "YFPoint3D.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        
        // insert code here...
        NSLog(@"Hello, World!");
        YFPoint2D *obj2 = [YFPoint2D new];
        [obj2 setX:1];
        [obj2 setY:2];
        [obj2 show];
        [obj2 setX:3 setY:4];
        [obj2 show]; 
        
        YFPoint3D *obj3 = [YFPoint3D new];
        [obj3 setX:1];
        [obj3 setY:2];
        [obj3 setZ:3];
        [obj3 show];
        [obj3 setX:5 setY:6 setZ:7];
        [obj3 show];        
    }
    return 0;
}

