//
//  main.m
//  HelloApp
//
//  Created by 飞 杨 on 12-3-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

int main(int argc, char *argv[])
{
    NSLog(@"Hello, World!");
    //return NSApplicationMain(argc, (const char **)argv);
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    NSApplication* app = [NSApplication sharedApplication];
    //Create the main window
    NSRect rc = NSMakeRect(0, 0, 800, 600);
    NSUInteger uiStyle = NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask;
    NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
    NSWindow* win = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
    [win setTitle:@"HelloWin Test"];
    [win makeKeyAndOrderFront:win];
    [win makeMainWindow];
    //Start the event loop by calling NSApp run
    [NSApp run];
    [pool drain];
    return 0;
}
