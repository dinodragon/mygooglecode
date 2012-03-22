//
//  AppController.m
//  HelloAppKit
//
//  Created by 飞 杨 on 12-3-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AppController.h"

@implementation AppController

-(id) init
{
//    if(self = [super inti])
//    {
//        NSLog(@"inti:text %@,results:%@",textField,resultField);
//    }
    NSLog(@"inti:text %@,results:%@",textField,resultField);
    return self;
}

-(IBAction)uppercase:(id)sender
{
    NSString * original;
    original = [textField stringValue];
    NSString *uppercase;
    uppercase = [original uppercaseString];
    [resultField setStringValue:uppercase];
}

-(IBAction)lowercase:(id)sender
{
    NSString * original;
    original = [textField stringValue];
    NSString *lowercase;
    lowercase = [original lowercaseString];
    [resultField setStringValue:lowercase];
}
@end
