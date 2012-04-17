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
    
    
    NSZone *zone = [NSMenu menuZone];
    NSMenu *menu = [[NSMenu allocWithZone:zone] init];
    NSMenuItem *item;
    item = [menu addItemWithTitle:@"Testing" action:@selector(testAction:) keyEquivalent:@""];
    [item setTarget:self];
    item = [menu addItemWithTitle:@"Quit" action:@selector(quitAction:) keyEquivalent:@""];
    [item setTarget:self];
    
    NSImage *myImage = [NSImage imageNamed:@"qq.png"];
    //[myImage draggedImage:<#(NSImage *)#> beganAt:<#(NSPoint)#>
    
    
    
    //trayItem = [[NSStatusBar systemStatusBar] statusItemWithLength:NSSquareStatusItemLength];
    NSStatusBar * statusBar = [NSStatusBar systemStatusBar];
    //NSStatusItem
    trayItem = [statusBar statusItemWithLength:NSVariableStatusItemLength];
    [trayItem setMenu:menu];
    [trayItem setHighlightMode:YES];
    //[trayItem setTitle:@"1"];
    NSAttributedString * attstr = [[NSAttributedString alloc]initWithString:@"1234567890"];
    //attstr 
    
//NSFont *font = [NSFont fontWithName:@"Palatino-Roman" size:12.0];
//NSDictionary *attrsDictionary = [NSDictionary dictionaryWithObject:font
//                            forKey:NSFontAttributeName];
//NSAttributedString *attrString =
//    [[NSAttributedString alloc] initWithString:@"1"
//                                attributes:attrsDictionary];
    
    
    [trayItem setAttributedTitle:attstr];
    [trayItem setImage:myImage];

    
//    NSImage *myImage2 = [NSImage imageNamed:@"qq2.png"] ;
//    trayItem2 = [[NSStatusBar systemStatusBar] statusItemWithLength:NSSquareStatusItemLength];
//    [trayItem2 setMenu:menu];
//    [trayItem2 setHighlightMode:YES];
//    [trayItem2 setImage:myImage2];

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
