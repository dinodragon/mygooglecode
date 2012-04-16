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
}

-(IBAction) AddUnRead:(id)sender;
-(IBAction) ReduceUnRead:(id)sender;
-(void) AddStatuItem;


@end
