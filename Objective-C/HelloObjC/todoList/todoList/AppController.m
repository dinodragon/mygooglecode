//
//  AppController.m
//  todoList
//
//  Created by 飞 杨 on 12-4-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AppController.h"

@implementation AppController


- (NSSize)windowWillResize:(NSWindow *)sender
                    toSize:(NSSize)frameSize
{
    //NSRect oldSize = [sender frame];
    NSSize mySize;
    mySize.width = frameSize.width * 2;
    mySize.height = frameSize.height * 2;
    NSLog(@"mySize is %f wide and %f tall", mySize.width, mySize.height);
    return frameSize;
}

-(id)init
{
    list = [NSMutableArray new];
    return self;
}

- (int)numberOfRowsInTableView:(NSTableView *)tv 
{
    return [list count];
}

- (id)tableView:(NSTableView *)tv 
            objectValueForTableColumn:(NSTableColumn *)tableColumn
            row:(int)row
{
    NSLog(@"Read tableColumn:%@,row:%d!",tableColumn,row);
    NSString *v = [list objectAtIndex:row];
    return v;
}


- (void)tableView:(NSTableView *)tableView sortDescriptorsDidChange:(NSArray *)oldDescriptors
{
    
}

-(IBAction)add:(id)sender
{
    NSString * text = [textField stringValue];
    [list addObject:text];
    [tableview reloadData];
}


@end
