//
//  main.m
//  HelloApp
//
//  Created by 飞 杨 on 12-3-26.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


//http://www.douban.com/note/144816024/
//简介启动NSApplication流程。

#import <Cocoa/Cocoa.h>
#import <Foundation/Foundation.h>

int main(int argc, char *argv[])
{
    NSLog(@"Hello, World!");
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    [NSApplication sharedApplication];
    //Create the main window
    NSRect rc = NSMakeRect(0, 0, 800, 600);
    NSUInteger uiStyle = NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask;
    NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
    NSWindow* win = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
    [win setTitle:@"HelloWinTest"];
    [win makeKeyAndOrderFront:win];
    [win makeMainWindow];
    //Start the event loop by calling NSApp run
    
    //演示了加载一个xib文件，这是可选的。
    [NSBundle loadNibNamed:@"MyApp" owner:NSApp];

    
    [NSApp run];
    [pool drain];
    return 0;
}
