//
//  nsstringtest.m
//  HelloFoundationKit
//
//  Created by 飞 杨 on 12-3-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

void testnsstring()
{
    NSLog(@"Hello, World!");
    NSString *str;
    str = [NSString stringWithFormat:@"中test,%d,%d",1,2];
    NSLog(@"%@",str);
    int len = [str length];
    NSLog(@"str的长度：%d",len);
    NSString *str1 = @"string1";
    NSString *str2 = @"string2";
    if ([str1 isEqualToString:str2]) {
        NSLog(@"equal.");
    }
    else {
        NSLog(@"Not equal.");
    }
    if ([str1 hasPrefix:@"str"]) {
        NSLog(@"Prefix str.");
    }
    
    NSMutableString *mustr = [NSMutableString stringWithCapacity:10];
    [mustr appendString:@"appString abcdefghijklmnopqrstuvwxyz."];
    NSLog(@"%@",mustr);
}
