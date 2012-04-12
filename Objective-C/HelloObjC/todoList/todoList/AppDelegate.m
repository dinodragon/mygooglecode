//
//  AppDelegate.m
//  todoList
//
//  Created by 飞 杨 on 12-4-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window = _window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    
    
    //NSZone *zone = [NSMenu menuZone];
    //NSMenu *menu = [[[NSMenu allocWithZone:zone] init] autorelease];
    NSMenu *menu = [NSMenu new];
    NSMenuItem *item;
    item = [menu addItemWithTitle:@"Testing" action:@selector(testAction:) keyEquivalent:@""];
    [item setTarget:self];
    item = [menu addItemWithTitle:@"Quit" action:@selector(quitAction:) keyEquivalent:@""];
    [item setTarget:self];
    
    NSImage *myImage = [NSImage imageNamed:@"qq2.png"] ;
    
    trayItem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSSquareStatusItemLength];
    [trayItem setMenu:menu];
    [trayItem setHighlightMode:YES];
    [trayItem setImage:myImage];
    
    NSImage *myImage2 = [NSImage imageNamed:@"qq.png"] ;
    trayItem2 = [[NSStatusBar systemStatusBar] statusItemWithLength:NSSquareStatusItemLength];
    [trayItem2 setMenu:menu];
    [trayItem2 setHighlightMode:YES];
    [trayItem2 setImage:myImage2];

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
