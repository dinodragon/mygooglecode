//
//  AppDelegate.h
//  kvcWnd
//
//  Created by 飞 杨 on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface Class1 : NSObject
{
    int f1;
    int f2;
}
@end


@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    int fido;
    IBOutlet NSTextField * textField;
    NSArray *arr;
    Class1 * obj;
}
-(int) fido;
-(void) setFido:(int) fido;

@property (assign) IBOutlet NSWindow *window;

@end
