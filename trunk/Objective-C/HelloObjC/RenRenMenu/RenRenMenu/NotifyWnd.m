//
//  NotifyWnd.m
//  RenRenMenu
//
//  Created by 飞 杨 on 12-4-20.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "NotifyWnd.h"
#import <QuartzCore/CoreAnimation.h>
#import <QuartzCore/QuartzCore.h>

@implementation NotifyWnd

-(id) initWithContentRect:(NSRect)contentRect styleMask:(NSUInteger)aStyle backing:(NSBackingStoreType)bufferingType defer:(BOOL)flag;
{
    self = [super initWithContentRect:contentRect styleMask:aStyle backing:bufferingType defer:flag];
    if (self) {
        // Initialization code here.
        willClose = FALSE;
        anim = [CABasicAnimation animation];
        [anim setDelegate:self];
        NSDictionary * dic = [NSDictionary dictionaryWithObject:anim forKey:@"alphaValue"];
        [self setAnimations:dic];
        [self setAlphaValue:0.0];
        [self.animator setAlphaValue:0.9];
        NSImage *closeImage = [NSImage imageNamed:@"close_btn1.png"];
        close = [[NSButton alloc] initWithFrame:NSMakeRect(0,[self frame].size.height - [closeImage size].height, [closeImage size].width, [closeImage size].height)];
        [close setImage:closeImage];
        [[self contentView] addSubview:close];
        [close setTarget:self];
        [close setAction:@selector(onCloseButtonClicked:)];
        
        head = [[NSImageView alloc] initWithFrame:NSMakeRect(12, 14, 40, 40)];
        [[self contentView] addSubview:head];
        
        userName = [[NSTextField alloc] initWithFrame:NSMakeRect(68, 40, 100, 16)];
        [userName setBordered:NO];
        [userName setEditable:NO];
        [userName setBackgroundColor:[NSColor clearColor]];
        [[self contentView] addSubview:userName];
        
        msg = [[NSTextField alloc] initWithFrame:NSMakeRect(68, 18, 216, 16)];
        [msg setBordered:NO];
        [msg setEditable:NO];
        [msg setBackgroundColor:[NSColor clearColor]];
        [[self contentView] addSubview:msg];
        
        CALayer * layer = [[CALayer alloc] init];
        [layer setBorderWidth:30.0];
        [layer setCornerRadius:10.0];
        

        [[self.contentView layer] setCornerRadius:10];    
//        [[self.contentView layer] setBorderColor:[[[NSColor alloc] colorWithRed:0.52 green:0.09 blue:0.07 alpha:1]CGColor]];    
        [[self.contentView layer] setShadowOffset:CGSizeMake(5, 5)];  
        [[self.contentView layer] setShadowOpacity:0.6];   
        //[[self.contentView layer] setShadowColor:[UIColor blackColor].CGColor]; 

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

-(void) onCloseButtonClicked:(id)sender
{
    [self windowShouldClose:sender];
}

-(BOOL)windowShouldClose:(id)sender
{
    [self.animator setAlphaValue:0.0];
    willClose = TRUE;
    return NO;
}

- (void)animationDidStop:(CAAnimation *)animation finished:(BOOL)flag 
{
    if (willClose) {
        [self close];
    }
}
@end
