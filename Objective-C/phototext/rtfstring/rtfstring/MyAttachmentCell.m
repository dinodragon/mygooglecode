//
//  MyView.m
//  rtfstring
//
//  Created by 飞 杨 on 12-5-4.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "MyView.h"

@implementation MyAttachmentCell

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
    
    CGContextRef myContext = [[NSGraphicsContext // 1
                               currentContext] graphicsPort];
    // ********** Your drawing code here ********** // 2
    CGContextSetRGBFillColor (myContext, 1, 0, 0, 1);// 3
    CGContextFillRect (myContext, CGRectMake (0, 0, 200, 100 ));// 4
    CGContextSetRGBFillColor (myContext, 0, 0, 1, .5);// 5
    CGContextFillRect (myContext, CGRectMake (0, 0, 100, 200));
    
    NSAttributedString *str = [[NSAttributedString alloc] initWithString:@"abc"];
    [str drawInRect:NSMakeRect(50,50,200,200)];
    
    // Drawing code here.
    NSString *longText = @"袁唯来来 Lorem ipsum dolor sit amet, Before the iPad was released you had basically two ways how to get text on screen. Either you would stick with UILabel or UITextView provided by UIKit or if you felt hard-core you would draw the text yourself on the Quartz level incurring all the headaches induced by having to mentally switch between Objective-C and C API functions.\
        As of iOS 3.2 we gained a third alternative in Core Text promising full control over styles, thread safety and performance. However for most of my apps I did not want to break 3.x compatibility and so I procrastinated looking at this powerful new API. Apps running only on iPads could have made use of Core Text from day 1, but to me it made more sense supporting iPad via hybrid apps where the iPhone part would still be backwards compatible.\
            Now as the year has turned the adoption of 4.x on all iOS platforms is ever more accelerating. Many new iPads where found under the Christmas tree and by now even the most stubborn people (read needing 3.x for jailbreaking and sim-unlocking) have little reason to stick with 3.x. Thus we have almost no incentive left to stick with 3.x compatibility. Yay!"; /* … */
    
    //创建AttributeString
    NSMutableAttributedString *string = [[NSMutableAttributedString alloc]
                                         initWithString:longText];
    
    //创建字体以及字体大小
    CTFontRef helvetica = CTFontCreateWithName(CFSTR("Helvetica"), 14.0, NULL);
    CTFontRef helveticaBold = CTFontCreateWithName(CFSTR("Helvetica-Bold"), 14.0, NULL);
    
    //添加字体 目标字符串从下标0开始到字符串结尾
    [string addAttribute:(id)kCTFontAttributeName
                   value:(id)helvetica
                   range:NSMakeRange(0, [string length])];
    
    //添加字体 目标字符串从下标0开始，截止到4个单位的长度
    [string addAttribute:(id)kCTFontAttributeName
                   value:(id)helveticaBold
                   range:NSMakeRange(0, 4)];
    
    //添加字体 目标字符串从下标6开始，截止到5个单位长度
    [string addAttribute:(id)kCTFontAttributeName
                   value:(id)helveticaBold
                   range:NSMakeRange(6, 5)];
    
    //添加字体 目标字符串从下标109开始，截止到9个单位长度
    [string addAttribute:(id)kCTFontAttributeName
                   value:(id)helveticaBold
                   range:NSMakeRange(109, 9)];
    
    //添加字体 目标字符串从下标223开始，截止到6个单位长度
    [string addAttribute:(id)kCTFontAttributeName
                   value:(id)helveticaBold
                   range:NSMakeRange(223, 6)];
    
    //添加颜色，目标字符串从下标0开始，截止到4个单位长度
    [string addAttribute:(id)NSForegroundColorAttributeName
                   value:(id)[NSColor blueColor]
                   range:NSMakeRange(0, 4)];
    
    //添加过程同上
    [string addAttribute:(id)NSForegroundColorAttributeName
                   value:(id)[NSColor redColor]
                   range:NSMakeRange(18, 3)];
    
    [string addAttribute:(id)NSForegroundColorAttributeName
                   value:(id)[NSColor greenColor]
                   range:NSMakeRange(657, 6)];
    
    [string addAttribute:(id)NSForegroundColorAttributeName
                   value:(id)[NSColor blueColor]
                   range:NSMakeRange(153, 6)];

    
    //创建文本对齐方式
    CTTextAlignment alignment = kCTLeftTextAlignment;//左对齐 kCTRightTextAlignment为右对齐
    CTParagraphStyleSetting alignmentStyle;
    alignmentStyle.spec=kCTParagraphStyleSpecifierAlignment;//指定为对齐属性
    alignmentStyle.valueSize=sizeof(alignment);
    alignmentStyle.value=&alignment;

    
    //创建文本行间距
    CGFloat lineSpace=5.0f;//间距数据
    CTParagraphStyleSetting lineSpaceStyle;
    lineSpaceStyle.spec=kCTParagraphStyleSpecifierLineSpacing;//指定为行间距属性
    lineSpaceStyle.valueSize=sizeof(lineSpace);
    lineSpaceStyle.value=&lineSpace;

    [string drawInRect:NSMakeRect(0,0,400,400)];
    //创建样式数组
//    CTParagraphStyleSetting settings[]={
//        alignmentStyle,lineSpaceStyle
//    };
//    
//    //设置样式
//    CTParagraphStyleRef paragraphStyle = CTParagraphStyleCreate(settings, sizeof(settings));
//    
//    //给字符串添加样式attribute
//    [string addAttribute:(id)kCTParagraphStyleAttributeName
//                   value:(id)paragraphStyle
//                   range:NSMakeRange(0, [string length])];
    
    
    // layout master
//    CTFramesetterRef framesetter = CTFramesetterCreateWithAttributedString(
//                                                                           (CFAttributedStringRef)string);
//    
//    CGMutablePathRef leftColumnPath = CGPathCreateMutable();
//    CGPathAddRect(leftColumnPath, NULL,
//                  CGRectMake(0, 0,
//                             self.bounds.size.width,
//                             self.bounds.size.height));
//    
//    CTFrameRef leftFrame = CTFramesetterCreateFrame(framesetter,
//                                                    CFRangeMake(0, 0),
//                                                    leftColumnPath, NULL);
    
    // flip the coordinate system
//    CGContextRef context = NSGraphicsGetCurrentContext();
//    CGContextSetTextMatrix(context, CGAffineTransformIdentity);
//    CGContextTranslateCTM(context, 0, self.bounds.size.height);
//    CGContextScaleCTM(context, 1.0, -1.0);
//    
//    // draw
//    CTFrameDraw(leftFrame, context);
//    
//    // cleanup
//    
//    CGPathRelease(leftColumnPath);
//    CFRelease(framesetter);
//    CFRelease(helvetica);
//    CFRelease(helveticaBold);
    [string release];
//    UIGraphicsPushContext(context);
}

@end
