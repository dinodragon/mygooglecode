//
//  AppDelegate.m
//  SayIt
//
//  Created by 飞 杨 on 12-4-5.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window = _window;

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
}

- (id)init {
    // Logs can help the beginner understand what
    // is happening and hunt down bugs.
    NSLog(@"init");
    // Create a new instance of NSSpeechSynthesizer
    // with the default voice.
    speechSynth = [[NSSpeechSynthesizer alloc] initWithVoice:nil];
    return [super init];
}

-(IBAction)sayit:(id)sender
{
    NSString *string = [textField stringValue];
    // Is the string zero-length?
    if ([string length] == 0) {
        NSLog(@"string from %@ is of zero-length", textField);
        return; }
    [speechSynth startSpeakingString:string];
    NSLog(@"Have started to say: %@", string);
    
}

-(IBAction)stopit:(id)sender
{
    NSLog(@"stopping");
    [speechSynth stopSpeaking];
}

@end
