//
//  MainWindowController.m
//  RenRenMenu
//
//  Created by 飞 杨 on 12-4-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MainWindowController.h"
#import "MessageView.h"
#import "NotifyWnd.h"


@implementation MainWindowController

- (id)init
{
    self = [super init];
    if (self) {
        // Initialization code here.
        unReadMsg = 0;
        menu = [[NSMenu allocWithZone:[NSMenu menuZone]] initWithTitle:@"CustomSub"];
    }
    return self;
}

-(void) awakeFromNib
{
    [userName setStringValue:@"人人用户1"];
    [msg setStringValue:@"用户消息测试，用户消息测试。"];
    [self AddStatuItem];
}

-(IBAction) ReduceUnRead:(id)sender
{
    if (unReadMsg > 0) {
        unReadMsg--;
        [self UpdateMenuState];
    }
}

-(void) UpdateMenuState
{
    NSString * unreadstr = @"";
    if (0 < unReadMsg) {
        unreadstr = [[NSString alloc] initWithFormat:@"%d",unReadMsg];
    }
    NSAttributedString * str = [[NSAttributedString alloc] initWithString:unreadstr];
    [statusItem setAttributedTitle:str];
}

-(IBAction) Send:(id)sender
{
    unReadMsg++;
    NSString * title = [[NSString alloc] initWithFormat:@"Custom Item %d",unReadMsg];
    NSMenuItem * item = [menu addItemWithTitle:title action:@selector(testAction:) keyEquivalent:@""];
    [item setEnabled:YES];
    [item setTitle:title];
    MessageView* myButtonView = [[MessageView alloc] initWithFrame:NSMakeRect(0,0,314,66)];
    NSImage *myImage = [NSImage imageNamed:@"qq2.png"];
    [myButtonView setImage:myImage setUserName:[userName stringValue] setMsg:[msg stringValue]];
    [myButtonView InitView];
	[item setView: myButtonView];
    [myButtonView retain];
    [self UpdateMenuState];
    
    NSScreen * scr = [NSScreen mainScreen];
    int x = scr.frame.origin.x + scr.frame.size.width - 280;
    int y = scr.frame.origin.y + scr.frame.size.height - 40 - 124 * unReadMsg;
    NSRect rc = NSMakeRect(x, y, 260, 84);

    //NSUInteger uiStyle = NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask;
    NSUInteger uiStyle = NSBorderlessWindowMask;
    NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
    NotifyWnd* win = [[NotifyWnd alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
    [win setImage:myImage setUserName:[userName stringValue] setMsg:[msg stringValue]];
    [win InitView];
    [win setTitle:@"HelloWinTest"];
    [win orderFront:win];

}

- (void) AddStatuItem
{    
    NSImage *myImage = [NSImage imageNamed:@"qq.png"];
    NSStatusBar * statusBar = [NSStatusBar systemStatusBar];
    statusItem = [statusBar statusItemWithLength:NSVariableStatusItemLength];
    [statusItem setMenu:menu];
    [statusItem setHighlightMode:YES];
    [statusItem setImage:myImage];
    [statusItem retain];
    [self UpdateMenuState];
}

- (IBAction)testAction:(id)sender;
{
    NSLog(@"Hello World");
}

- (IBAction)quitAction:(id)sender;
{
    [NSApp terminate:sender];
}

@end
