//
//  AppController.h
//  todoList
//
//  Created by 飞 杨 on 12-4-6.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AppController : NSObject
{
    NSMutableArray *list;
    IBOutlet NSTableView *tableview;
    IBOutlet NSTextField *textField;
}

-(IBAction)add:(id)sender;

@end
