//
//  MyClass.h
//  hello
//
//  Created by 飞 杨 on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface YFPoint2D : NSObject
{
    int x;
    int y;
}
-(void) show;
-(void) setX:(int)a_;
-(void) setY:(int)y_;
//两个参数声明
-(void) setX:(int)a_
        setY:(int)b_;

//相当于C＃中的ToString函数。
//在NSObject中已经有声明，此处可以不再声明。
//-(NSString *)description;

@end//A

