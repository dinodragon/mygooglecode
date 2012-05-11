//
//  MainWindowController.m
//  phototext
//
//  Created by 飞 杨 on 12-4-28.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MainWindowController.h"
#import "MyMainWindow.h"
#import "PhotoTextControl.h"

#define FULLSIZE (NSViewMinXMargin | NSViewWidthSizable | NSViewMaxXMargin | NSViewMinYMargin | NSViewHeightSizable | NSViewMaxYMargin)


@implementation MainWindowController

-(void) ShowWindow
{
    NSRect rc = NSMakeRect(400, 300, 300, 186);
    NSUInteger uiStyle = NSTitledWindowMask | NSResizableWindowMask | NSClosableWindowMask;
    NSBackingStoreType backingStoreStyle = NSBackingStoreBuffered;
    MyMainWindow* win = [[MyMainWindow alloc] initWithContentRect:rc styleMask:uiStyle backing:backingStoreStyle defer:NO];
    [win InitView];
    [[win contentView] setAutoresizesSubviews:YES];
    NSRect frame=[win frame];
    PhotoTextControl * ptview = [[PhotoTextControl alloc] initWithFrame:frame];
    [ptview setDataSource:self];
    
    NSTableColumn * col = [[NSTableColumn alloc] initWithIdentifier:@"field1"];
    [[col headerCell] setStringValue:@"asdsd"];
    [ptview addTableColumn:col];
    [col release];
    
    NSScrollView *scrollView = [[NSScrollView alloc] initWithFrame:frame];
    [scrollView setDocumentView:ptview];
    //[scrollView setBackgroundColor:[NSColor redColor]];
    [ptview retain];
    [win setContentView:scrollView];


}



- (NSInteger)numberOfRowsInTableView:(NSTableView *)tableView 
{
    return 10;
}

- (id)tableView:(NSTableView *)tableView objectValueForTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row 
{
    NSString *str = @"field1";
    return str;
}


- (void)tableView:(NSTableView *)tableView willDisplayCell:(id)cell forTableColumn:(NSTableColumn *)tableColumn row:(NSInteger)row {
    
    NSLog(@"%@",@"willDisplayCell");
    
//    ATDesktopImageEntity *entity = [self _imageEntityForRow:row];
//    if (entity != nil) {
//        // Setup the image and fill color
//        ATImageTextCell *imageTextCell = (ATImageTextCell *)cell;
//        imageTextCell.image = entity.thumbnailImage;
//        imageTextCell.fillColor = entity.fillColor;
//        imageTextCell.fillColorName = entity.fillColorName;
//    }
}

- (NSView *)dynamicTableView:(PhotoTextControl *)tableView viewForRow:(NSInteger)row {
    // Return a spinner for rows that are loading
    NSLog(@"%@",@"dynamicTableView");
    NSProgressIndicator *result = nil;
//    ATDesktopImageEntity *entity = [self _imageEntityForRow:row];
//    if (entity != nil && entity.thumbnailImage == nil) {
//        NSRect cellFrame = [tableView frameOfCellAtColumn:0 row:row];
//        ATImageTextCell *imageCell = (ATImageTextCell *)[tableView preparedCellAtColumn:0 row:row];
//        NSRect imageFrame = [imageCell imageRectForBounds:cellFrame];
//        result = [[[NSProgressIndicator alloc] initWithFrame:imageFrame] autorelease];
//        [result setIndeterminate:YES];
//        [result setStyle:NSProgressIndicatorSpinningStyle];
//        [result setControlSize:NSRegularControlSize];        
//        [result sizeToFit];
//        [result startAnimation:nil];
//        NSRect progressFrame = [result frame];
//        // Center it in the image frame
//        progressFrame.origin.x = NSMinX(imageFrame) + floor((NSWidth(imageFrame) - NSWidth(progressFrame)) / 2.0);
//        progressFrame.origin.y = NSMinY(imageFrame) + floor((NSHeight(imageFrame) - NSHeight(progressFrame)) / 2.0);
//        [result setFrame:progressFrame];
//    }
    return result;
}


@end
