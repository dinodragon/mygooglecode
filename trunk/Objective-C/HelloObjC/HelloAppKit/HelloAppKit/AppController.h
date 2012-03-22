//
//  AppController.h
//  HelloAppKit
//
//  Created by 飞 杨 on 12-3-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AppController : NSObject
{
    IBOutlet NSTextField *textField;
    IBOutlet NSTextField *resultField;
}

-(IBAction)uppercase:(id)sender;
-(IBAction)lowercase:(id)sender;

@end
