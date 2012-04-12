//
//  AppDelegate.h
//  todoList
//
//  Created by 飞 杨 on 12-4-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    NSStatusItem * trayItem;
    NSStatusItem * trayItem2;
}

@property (assign) IBOutlet NSWindow *window;

@end
