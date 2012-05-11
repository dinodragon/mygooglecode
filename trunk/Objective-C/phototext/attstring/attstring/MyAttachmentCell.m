//
//  MyView.m
//  rtfstring
//
//  Created by 飞 杨 on 12-5-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MyAttachmentCell.h"
#import "MyTextView.h"

@implementation MyAttachmentCell

- (id)initWithFrame:(NSRect)frame
{
    //self = [super initWithFrame:frame];
    self = [super init];
    if (self) {
        // Initialization code here.
    }
    return self;
}

- (void)drawWithFrame:(NSRect)cellFrame inView:(MyTextView *)controlView
{
    //NSLog(@"%f,%f,%f,%f",cellFrame.origin.x,cellFrame.origin.y,cellFrame.size.width,cellFrame.size.height);
    NSRect winrect = controlView.window.frame;
    NSPoint pint =  [NSEvent mouseLocation];
    //NSPoint pint2 = controlView.textContainerOrigin;
    //NSRect r = controlView.bounds;
    NSDictionary * at = [[NSGraphicsContext currentContext] attributes];


    NSLog(@"mouseLocation:%f,%f",pint.x - winrect.origin.x,pint.y - winrect.origin.y);
    CGContextRef myContext = [[NSGraphicsContext currentContext] graphicsPort];
    CGContextSetRGBFillColor (myContext, 1, 0, 0, 1);// 3
    CGContextFillRect (myContext, CGRectMake (cellFrame.origin.x, cellFrame.origin.y, 200, 100 ));// 4
    CGContextSetRGBFillColor (myContext, 0, 0, 1, .5);// 5
    CGContextFillRect (myContext, CGRectMake (cellFrame.origin.x, cellFrame.origin.y, 100, 200));
    //[controlView dr]
    
}
- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView untilMouseUp:(BOOL)flag
{
    NSLog(@"%f,%f",cellFrame.origin.x,cellFrame.origin.y);
    return YES;
}

- (BOOL)wantsToTrackMouse
{
    return YES;
}

- (BOOL)wantsToTrackMouseForEvent:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView atCharacterIndex:(NSUInteger)charIndex
{
    NSLog(@"%@",@"wantsToTrackMouseForEvent");
    //[[self attachment]];
    return YES;
}

- (BOOL)trackMouse:(NSEvent *)theEvent inRect:(NSRect)cellFrame ofView:(NSView *)controlView atCharacterIndex:(NSUInteger)charIndex untilMouseUp:(BOOL)flag
{
    NSLog(@"%@",@"trackMouse");
    return NO;
}

- (NSSize)cellSize
{
    return NSMakeSize(220, 220);
}

@end
