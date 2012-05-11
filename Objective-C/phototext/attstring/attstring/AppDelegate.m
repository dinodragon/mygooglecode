//
//  AppDelegate.m
//  attstring
//
//  Created by 飞 杨 on 12-5-2.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"
#import "MyAttachmentCell.h"

@implementation AppDelegate

@synthesize window = _window;

- (void)dealloc
{
    [super dealloc];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
}

-(IBAction)refresh:(id)sender
{
    [self addHtml];
    //[tv re]
}

-(void) addHtml
{
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"styles" ofType:@"html"];
    NSAttributedString * attstr = [[NSAttributedString alloc] initWithPath:filePath documentAttributes:nil];
    //NSLog(@"%@",attstr);
    [mytv setEditable:YES];
    [mytv setString:@""];
    attstr = [self AppImageString:attstr];
    attstr = [self AppImageString:attstr];
    [mytv insertText:attstr];
    [mytv setEditable:NO];
}

//在属性字符串中加入自定义控件

- (NSAttributedString *) AppImageString:(NSAttributedString *) attString
{
    NSMutableAttributedString * tempStr = [[NSMutableAttributedString alloc] initWithAttributedString:attString];
    
    //NSImage *icon = [[NSImage alloc] initWithContentsOfURL:[[NSURL alloc] initWithString:@"http://10.2.78.172/img.jpg"]]; // or wherever you are getting your image
    MyAttachmentCell * myview = [[MyAttachmentCell alloc] init];
    NSTextAttachment *attachment = [[[NSTextAttachment alloc] init] autorelease];
    [attachment setAttachmentCell:myview];
    
    NSAttributedString *attrname = (id)[NSMutableAttributedString attributedStringWithAttachment:
                                        attachment];
    [tempStr appendAttributedString: attrname];
    return (tempStr);
}

-(void) awakeFromNib
{
    NSDictionary * linkatt = [NSDictionary dictionaryWithObjectsAndKeys:
                              @"common",NSLinkAttributeName,
                              //NSUnderlineStyleSingle,NSUnderlineStyleAttributeName,
                              [NSCursor pointingHandCursor],NSCursorAttributeName,
                              nil];
    [mytv setLinkTextAttributes:linkatt];
    [mytv setDelegate:self];
    [self addHtml];
    NSRect r = [_scrollView frame];
    //[mytv ]
   //[mytv set]
    //NSRect r = [_scrollView documentVisibleRect];
    //NSSize s = [_scrollView contentSize];
    
    
}

- (BOOL)textView:(NSTextView *)textView clickedOnLink:(id)link atIndex:(NSUInteger)charIndex
{
    NSLog(@"%@",link);
    return YES;
}

//输出属性字符串所有属性
- (void) iterateAttributesForString: (NSAttributedString *) string
{
    NSDictionary *attributeDict;
    NSRange effectiveRange = { 0, 0 };
    do {
        NSRange range;
        range = NSMakeRange (NSMaxRange(effectiveRange),
                             [string length] - NSMaxRange(effectiveRange));
        attributeDict = [string attributesAtIndex: range.location
                            longestEffectiveRange: &effectiveRange
                                          inRange: range];
        NSLog (@"Range: %@ Attributes: %@",
               NSStringFromRange(effectiveRange), attributeDict);
    } while (NSMaxRange(effectiveRange) < [string length]);
}

@end
