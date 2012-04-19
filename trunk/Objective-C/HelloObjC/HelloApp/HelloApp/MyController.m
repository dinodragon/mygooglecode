//
//  MyController.m
//  HelloApp
//
//  Created by 飞 杨 on 12-4-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MyController.h"

@implementation MyController

-(void) onButtonClicked:(id)sender
{
    NSLog(@"onButtonClicked");
    [NSApp terminate:NSApp];
}
@end
