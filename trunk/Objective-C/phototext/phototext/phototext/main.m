//
//  main.m
//  phototext
//
//  Created by 飞 杨 on 12-4-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "MainWindowController.h"


int main(int argc, char *argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    [NSApplication sharedApplication];
    MainWindowController * ctrl = [[MainWindowController alloc] init];
    [ctrl ShowWindow];
    [NSApp run];
    [ctrl release];
    [pool drain];
    return 0;
    //return NSApplicationMain(argc,  (const char **) argv);
}
