//
//  MyTextView.m
//  attstring
//
//  Created by 飞 杨 on 12-5-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MyTextView.h"

@implementation MyTextView

- (id)initWithFrame:(NSRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code here.
    }
    
    return self;
}

- (void)drawRect:(NSRect)dirtyRect
{
    // Drawing code here.
    [super drawRect:dirtyRect];
}

- (void)mouseMoved:(NSEvent *)theEvent
{
    controlFrame = self.superview.frame;
    NSLog(@"mouseMoved:%f,%f",theEvent.locationInWindow.x,theEvent.locationInWindow.y);
    [self display];
}

@end
