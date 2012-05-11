//
//  PhotoTextControl.m
//  phototext
//
//  Created by 飞 杨 on 12-4-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "PhotoTextControl.h"

@implementation PhotoTextControl

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


- (void)viewWillDraw {
    // We have to call super first in case the NSTableView does some layout in -viewWillDraw
    [super viewWillDraw];
    NSLog(@"%@",@"viewWillDraw");
    
    // Calculate the new visible rows and let the delegate do any extra work it wants to
    NSRange newVisibleRows = [self rowsInRect:self.visibleRect];
    BOOL visibleRowsNeedsUpdate = !NSEqualRanges(newVisibleRows, _visibleRows);
    NSRange oldVisibleRows = _visibleRows;
    if (visibleRowsNeedsUpdate) {
        _visibleRows = newVisibleRows;
        // Give the delegate a chance to do any pre-loading or special work that it wants to do
        if ([[self delegate] respondsToSelector:@selector(dynamicTableView:changedVisibleRowsFromRange:toRange:)]) {
            [[self delegate] dynamicTableView:self changedVisibleRowsFromRange:oldVisibleRows toRange:newVisibleRows];
        }
        // We always have to update our views if the visible area changed
        _viewsNeedUpdate = YES;
    }
    
    if (_viewsNeedUpdate) {
        _viewsNeedUpdate = NO;
        // Update any views that the delegate wants to give us
        if ([[self delegate] respondsToSelector:@selector(dynamicTableView:viewForRow:)]) {
            
            if (visibleRowsNeedsUpdate) {
                // First, remove any views that are no longer before our new visible rows
                NSMutableIndexSet *rowIndexesToRemove = [NSMutableIndexSet indexSetWithIndexesInRange:oldVisibleRows];
                // Remove any rows from the set that are STILL visible; we want a resulting index set that has the views which are no longer on screen.
                [rowIndexesToRemove removeIndexesInRange:newVisibleRows];
                // Remove those views which are no longer visible
                [self _removeCachedViewsInIndexSet:rowIndexesToRemove];
            }
            
            [self _ensureVisibleRowsIsCreated];
            
            // Finally, update and add in any new views given to us by the delegate. Use [NSNull null] for things that don't have a view at a particular row
            for (NSInteger row = _visibleRows.location; row < NSMaxRange(_visibleRows); row++) {
                NSNumber *key = [NSNumber numberWithInteger:row];
                id view = [_viewsInVisibleRows objectForKey:key];
                if (view == nil) {
                    // We don't already have a view at that row
                    view = [[self delegate] dynamicTableView:self viewForRow:row];
                    if (view != nil) {
                        [self addSubview:view];
                    } else {
                        // Use null as a place holder so we don't call the delegate again until the row is relaoded
                        view = [NSNull null]; 
                    }
                    [_viewsInVisibleRows setObject:view forKey:key];
                }
            }
        }
    }
}


@end
