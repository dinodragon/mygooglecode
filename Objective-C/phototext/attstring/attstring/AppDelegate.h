//
//  AppDelegate.h
//  attstring
//
//  Created by 飞 杨 on 12-5-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@class MyTextView;

@interface AppDelegate : NSObject <NSApplicationDelegate,NSTextViewDelegate>
{
    IBOutlet MyTextView * mytv;
    IBOutlet NSWindow * _window;
    IBOutlet NSScrollView * _scrollView;
}

@property (assign) IBOutlet NSWindow *window;

-(IBAction)refresh:(id)sender;

@end
