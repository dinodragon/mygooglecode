//
//  main.m
//  HelloApp2
//
//  Created by 飞 杨 on 12-4-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//


#import <Cocoa/Cocoa.h>
#define IDC_QUIT_BUTTON 101
#define IDC_CONFIRM_BUTTON 102

@interface MyController : NSObject
{
@public
    NSWindow* window;
    NSTextField* nameEdit;
}
- (void) onButtonClicked:(id)sender;
@end

@implementation MyController
- (void) onButtonClicked:(id)sender
{
    NSButton* button = (NSButton*)sender;
    if ([button tag] == IDC_QUIT_BUTTON)
    {
        [NSApp terminate:NSApp];
    }
    else if ([button tag]== IDC_CONFIRM_BUTTON)
    {
        NSBeginInformationalAlertSheet(@"Information", @"Ok", nil, nil,
                                       window, nil, NULL, NULL, NULL,
                                       @"Your name is %s", [[nameEdit stringValue] UTF8String]);
    }
    
}
@end

void createContentView(NSView* view, id object)
{
    NSRect rcControl = NSMakeRect(10, 170, 90, 20);
    NSTextField* nameLabel = [[NSTextField alloc] initWithFrame:rcControl];
    [nameLabel setEditable:NO];
    [nameLabel setTitleWithMnemonic:@"User Name:"];
    [nameLabel setBezeled:NO];
    [nameLabel setBackgroundColor:[NSColor windowBackgroundColor]];
    [view addSubview:nameLabel];
    
    rcControl = NSMakeRect(100, 170, 120, 20);
    NSTextField* nameEdit = [[NSTextField alloc] initWithFrame:rcControl];
    [view addSubview:nameEdit];
    ((MyController*)object)->nameEdit = nameEdit;
    
    NSRect rcView = [[view window] contentRectForFrameRect:[[view window] frame]];
    rcControl = NSMakeRect(rcView.size.width - 80,
                           rcView.size.height - 35, 80, 25);
    NSButton* confirmButton = [[NSButton alloc] initWithFrame:
                               rcControl];
    [confirmButton setTag:IDC_CONFIRM_BUTTON];
    [confirmButton setTitle:@"Confirm"];
    [confirmButton setButtonType:NSMomentaryLightButton];
    [confirmButton setBezelStyle:NSRoundedBezelStyle];
    [confirmButton setTarget:object];
    [confirmButton setAction:@selector(onButtonClicked:)];
    [view addSubview:confirmButton];
    
    return;
}

int main(int argc, char *argv[])
{
    NSAutoreleasePool* pool = [[NSAutoreleasePool alloc] init];
    [NSApplication sharedApplication];
    
    //Create main window
    NSRect rc = NSMakeRect(0, 0, 400, 200);
    NSUInteger uiStyle = NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask;
    NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
    NSWindow* win = [[NSWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
    [win setTitle:@"HelloWin Test"];
    //Create a button and set it as content view
    NSButton* button = [[NSButton alloc] initWithFrame:NSMakeRect(160, 20, 80, 35)];
    [button setTitle:@"Quit Application"];
    [button setButtonType:NSMomentaryLightButton];
    [button setBezelStyle:NSRoundedBezelStyle];
    [button setTag:IDC_QUIT_BUTTON];
    
    NSView* contentView = [win contentView];
    
    MyController* controller = [[MyController alloc]init];
    controller->window = win;
    createContentView(contentView, controller);
    
    [[win contentView] addSubview:button];
    [contentView setAutoresizesSubviews:YES];
    [button setAutoresizingMask:NSViewMaxXMargin | NSViewMinXMargin | NSViewMaxYMargin];
    //Set target and action
    [button setTarget:controller];
    [button setAction:@selector(onButtonClicked:)];
    [win center]; //Center main Window
    [win makeKeyAndOrderFront:win];
    [win makeMainWindow];
    
    [NSApp run];
    [button release];
    [win release];
    [pool drain];
    
    return 0;
}