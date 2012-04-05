//
//  AppDelegate.h
//  SayIt
//
//  Created by 飞 杨 on 12-4-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate,NSSpeechSynthesizerDelegate>
{
    IBOutlet NSTextField *textField;
    IBOutlet NSButton *stopButton;
    IBOutlet NSButton *startButton;
    NSSpeechSynthesizer *speechSynth;
}

@property (assign) IBOutlet NSWindow *window;

-(IBAction)sayit:(id)sender;
-(IBAction)stopit:(id)sender;

@end
