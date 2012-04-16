//
//  MainWindowController.m
//  RenRenMenu
//
//  Created by 飞 杨 on 12-4-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MainWindowController.h"
#import "MessageView.h"

@interface MainWindowController ()

@end

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
    [self AddStatuItem];
}

- (IBAction) AddUnRead:(id)sender
{
    unReadMsg++;
    NSString * title = [[NSString alloc] initWithFormat:@"Custom Item %d",unReadMsg];
    NSMenuItem * item = [menu addItemWithTitle:title action:@selector(testAction:) keyEquivalent:@""];
    [item setEnabled:YES];
    [item setTitle:title];
    MessageView* myButtonView = [[MessageView alloc] initWithFrame:NSMakeRect(0,0,314,66)];
    NSImage *myImage = [NSImage imageNamed:@"qq2.png"];
    NSString * username = [[NSString alloc] initWithFormat:@"人人用户 %d",unReadMsg];
    [myButtonView setImage:myImage setUserName:username setMsg:@"用户消息测试，用户消息测试。"];
    [myButtonView InitView];
    
	[item setView: myButtonView];
    [myButtonView retain];
    [self UpdateMenuState];
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
