//
//  AppDelegate.m
//  kvcWnd
//
//  Created by 飞 杨 on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "AppDelegate.h"



@implementation Class1
@end


@implementation AppDelegate

@synthesize window = _window;

- (id) init
{
    Class1 * obj1 = [Class1 new];
    [obj1 setValue:[NSNumber numberWithInt:10] forKey:@"f1"];
    NSLog(@"f1:%@",[obj1 valueForKey:@"f1"]);
    Class1 * obj2 = [Class1 new];
    [obj2 setValue:[NSNumber numberWithInt:20] forKey:@"f1"];
    NSLog(@"f1:%@",[obj2 valueForKey:@"f1"]);

    arr = [NSArray arrayWithObjects:obj1,obj2,nil];
    //此时textField还没有初始化。还是nil
    [textField setStringValue:@"aaa2"];
    
    obj = [Class1 new];
    [obj setValue:[NSNumber numberWithInt:30] forKey:@"f1"];
    
    
    
    NSLog(@"init call");
    if (self = [super init]) {
        //构造代码。
        fido = 70;
    }
    return self;
}

-(int) fido
{
    NSLog(@"Get fido:%d",fido);
    return fido;
}

-(void) setFido:(int) fidoValue
{
    NSLog(@"Set fido:%d，oldvalue：%d",fidoValue,fido);
    fido = fidoValue;
}

//先调用init，后调用awakeFromNib,为什么滑动条值为70，是有两个对象吗?
//不是，是因为：
//先调用了init，fido=70.
//然后当 slider 做 init 时,调用了 appController 的 valueForKey,参数是fido。
//然后调用awakeFromNib
- (void) awakeFromNib
{
     NSLog(@"call awakeFromNib.");
    fido = 80;
    //[self setFido:80];//这样修改可以使slider读取到新值。因为slider和textfield订阅了该值，当该值使用访问方法调用时即会通知到订阅方。
    //[textField setStringValue:@"aaa"];//可以生效
    [textField bind:@"value" toObject:self withKeyPath:@"obj.f1" options:nil];//此处好像默认不支持arr的@arg方式。
    NSLog(@"%@",[self valueForKeyPath:@"arr.@avg.f1"]);
}

- (void)dealloc
{
    NSLog(@"call dealloc.");
    [super dealloc];
}


- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    // Insert code here to initialize your application
    [obj setValue:[NSNumber numberWithInt:40] forKey:@"f1"];
    [textField unbind:@"value"];
    [obj setValue:[NSNumber numberWithInt:50] forKey:@"f1"];
    NSLog(@"call applicationDidFinishLaunching.");
}

@end
