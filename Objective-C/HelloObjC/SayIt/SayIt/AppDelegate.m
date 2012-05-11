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

- (void)awakeFromNib {
    // When the table view appears on screen, the default voice // should be selected
    NSString *defaultVoice = [NSSpeechSynthesizer defaultVoice];
    int defaultRow = [voicelist indexOfObject:defaultVoice]; 
    [tableview selectRowIndexes:[NSIndexSet indexSetWithIndex:defaultRow] byExtendingSelection:NO]; 
    [tableview scrollRowToVisible:defaultRow];
}

- (id)init {
    // Logs can help the beginner understand what
    // is happening and hunt down bugs.
    NSLog(@"init");
    // Create a new instance of NSSpeechSynthesizer
    // with the default voice.
    speechSynth = [[NSSpeechSynthesizer alloc] initWithVoice:nil];
    voicelist = [NSSpeechSynthesizer availableVoices];
    [speechSynth setDelegate:self];
    //[textField setDelegate:self];
    //[tableview setDataSource:self];为什么不可以。
    //[tableview setDelegate:self];
    return [super init];
}

//测试方法，此处是测试委托的实现机制。详见：《苹果开发之cocoa编程》p104
- (BOOL)respondsToSelector:(SEL)aSelector
{
    NSString *methodName = NSStringFromSelector(aSelector); 
    NSLog(@"respondsToSelector:%@", methodName);
    return [super respondsToSelector:aSelector];
}

- (void)speechSynthesizer:(NSSpeechSynthesizer *)sender
        didFinishSpeaking:(BOOL)complete
{
    NSLog(@"complete = %d", complete);
    [self updateControlState];
}
/////
////tableview的datesource方法。
- (int)numberOfRowsInTableView:(NSTableView *)tv {
    return [voicelist count];
}

- (id)tableView:(NSTableView *)tv objectValueForTableColumn:(NSTableColumn *)tableColumn
            row:(int)row
{
    NSString *v = [voicelist objectAtIndex:row];
    NSDictionary *dict = [NSSpeechSynthesizer attributesForVoice:v];
    id obj = [dict objectForKey:NSVoiceName];
    return obj;
}


- (void)tableViewSelectionDidChange:(NSNotification *)notification 
{
    int row = [tableview selectedRow];
    if (row == -1) 
    {
        return;
    }
    NSString *selectedVoice = [voicelist objectAtIndex:row]; 
    [speechSynth setVoice:selectedVoice];
    NSLog(@"new voice = %@", selectedVoice);
}
/////

-(void)updateControlState
{
    BOOL isspeaking = [speechSynth isSpeaking];
    NSString *string = [textField stringValue];
    BOOL isempty = [string length] == 0;
    [startButton setEnabled:(!isspeaking && !isempty)];
    [stopButton setEnabled:isspeaking];
    [tableview setEnabled:!isspeaking];
}


-(IBAction)sayit:(id)sender
{
    NSString *string = [textField stringValue];
    // Is the string zero-length?
    if ([string length] == 0) {
        NSLog(@"string from %@ is of zero-length", textField);
        return; }
    [speechSynth startSpeakingString:string];
    [self updateControlState];
    NSLog(@"Have started to say: %@", string);
    
}

-(IBAction)stopit:(id)sender
{
    NSLog(@"stopping");
    [speechSynth stopSpeaking];
   [self updateControlState];
}

@end
