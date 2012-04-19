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
#import "MyController.h"

void showWindow1();
void showWindow2();


@interface MyDelegate : NSObject<NSWindowDelegate> {
	
}
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication;
- (BOOL)windowShouldClose:(id)window;
@end

@implementation MyDelegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)theApplication
{
    return YES;
}

- (BOOL)windowShouldClose:(id)window
{
    NSAlert* alert = [[NSAlert alloc] init];
    [alert setAlertStyle:NSInformationalAlertStyle];
    [alert setMessageText:@"Are you sure you want to quit?"];
    [alert addButtonWithTitle:@"Yes"];
    [alert addButtonWithTitle:@"No"];
    NSInteger result = [alert runModal];
    if (result == NSAlertFirstButtonReturn)
    {
        [alert release];
        return YES;
    }
    [alert release];
    return NO;   
}
@end

int main(int argc, char *argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    [NSApplication sharedApplication];
    showWindow1();
    //showWindow2();
    [NSApp run];
    [pool drain];
    return 0;
}

//方法一
void showWindow1()
{
    //Start the event loop by calling NSApp run
    //Create the main window
    NSRect rc = NSMakeRect(400, 300, 300, 186);
    NSUInteger uiStyle = NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask;
    NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
    NSWindow* win = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
    [win setTitle:@"HelloWinTest"];
    [win makeKeyAndOrderFront:win];
    [win makeMainWindow];
    NSButton* button = [[NSButton alloc] initWithFrame:NSMakeRect(120, 70, 100, 40)];
    [button setTitle:@"Quit Application"];
    //NSView * view = [[NSView alloc] init];
    //[view addSubview:button];
    //[win setContentView:view];
    [[win contentView] addSubview:button];
    NSColor * c = [NSColor colorWithCalibratedRed:100 green:100 blue:100 alpha:0.5];
    [win setBackgroundColor:c]; //半透明
    //[win center];
    [win setOpaque:NO];
    
    [button setBezelStyle:NSRoundedBezelStyle];
    [button setAutoresizingMask:NSViewMaxXMargin | NSViewMinXMargin | NSViewMaxYMargin];
    
    //Set delegate to application object
    MyDelegate* myDelegate = [[MyDelegate alloc] init];
    //Use the same delegate object to window object
    [win setDelegate:myDelegate];
    [NSApp setDelegate:myDelegate];
    [myDelegate autorelease];
    
    MyController* controller = [[MyController alloc] init];
    [button setTarget:controller];
    [button setAction:@selector(onButtonClicked:)];
}

//方法二 加载一个xib文件
void showWindow2()
{
    [NSBundle loadNibNamed:@"MyApp" owner:NSApp];
}