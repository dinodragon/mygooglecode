//
//  MessageView.m
//  RenRenMenu
//
//  Created by 飞 杨 on 12-4-16.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MessageView.h"

@implementation MessageView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
        head = [[NSImageView alloc] initWithFrame:NSMakeRect(12, 14, 40, 40)];
        [self addSubview:head];
        
        userName = [[NSTextField alloc] initWithFrame:NSMakeRect(68, 40, 100, 16)];
        [userName setBordered:NO];
        [userName setEditable:NO];
        [self addSubview:userName];
        
        msg = [[NSTextField alloc] initWithFrame:NSMakeRect(68, 18, 216, 16)];
        [msg setBordered:NO];
        [msg setEditable:NO];
        [self addSubview:msg];
        
        line = [[NSBox alloc] initWithFrame:NSMakeRect(0, 1, frame.size.width, 1)];
        [self addSubview:line];
    }
    return self;
}

-(void) setImage:(NSImage *) head_ setUserName:(NSString *) userName_ setMsg:(NSString *) msg_
{
    myImage = head_;
    strUserName = userName_;
    strMsg = msg_;
}

-(void) InitView
{
    [head setImage:myImage];
    [userName setStringValue:strUserName];
    [msg setStringValue:strMsg];
}

- (void)mouseEntered:(NSEvent *)theEvent
{
    [userName setStringValue:@"当前"];
}


- (void)drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
}

@end
