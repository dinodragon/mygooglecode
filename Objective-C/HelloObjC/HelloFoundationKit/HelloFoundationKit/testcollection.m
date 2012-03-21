//
//  testcollection.c
//  HelloFoundationKit
//
//  Created by 飞 杨 on 12-3-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

void testcollection()
{
    NSArray *array = [NSArray arrayWithObjects:@"one",@"two",nil];
    NSLog(@"array count:%d.",(int)[array count]);
}
