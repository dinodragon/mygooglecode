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

void showWindow1();
void showWindow2();

int main(int argc, char *argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    [NSApplication sharedApplication];
    showWindow1();
    showWindow2();
    [NSApp run];
    [pool drain];
    return 0;
}

//方法一
void showWindow1()
{
    //Start the event loop by calling NSApp run
    //Create the main window
    NSRect rc = NSMakeRect(0, 0, 800, 600);
    NSUInteger uiStyle = NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask;
    NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
    NSWindow* win = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
    [win setTitle:@"HelloWinTest"];
    [win makeKeyAndOrderFront:win];
    [win makeMainWindow];
    NSButton* button = [[NSButton alloc] initWithFrame:NSMakeRect(200, 200, 60, 40)];
    [button setTitle:@"Quit Application"];
    NSView * view = [[NSView alloc] init];
    [view addSubview:button];
    [win setContentView:view];
}

//方法二 加载一个xib文件
void showWindow2()
{
    [NSBundle loadNibNamed:@"MyApp" owner:NSApp];
}