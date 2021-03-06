//
//  NotifyWnd.h
//  RenRenMenu
//
//  Created by 飞 杨 on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface NotifyWnd : NSWindow
{
    CAAnimation *anim;
    NSButton * close;
    BOOL willClose;
    
    NSImageView * head;
    NSTextField * userName;
    NSTextField * msg;
    NSBox * line;
    
    NSImage *myImage;
    NSString * strUserName;
    NSString * strMsg;
}

-(void) onCloseButtonClicked:(id)sender;

-(void) setImage:(NSImage *) head setUserName:(NSString *) userName setMsg:(NSString *) msg;
-(void) InitView;

@end
