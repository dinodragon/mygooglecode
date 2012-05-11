//
//  MainWindowController.h
//  RenRenMenu
//
//  Created by 飞 杨 on 12-4-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface MainWindowController : NSObject
{
    NSStatusItem * statusItem;
    NSMenu * menu;
    int unReadMsg;
    IBOutlet NSTextField * userName;
    IBOutlet NSTextField * msg;
}

-(IBAction) ReduceUnRead:(id)sender;
-(IBAction) Send:(id)sender;
-(void) AddStatuItem;


@end
