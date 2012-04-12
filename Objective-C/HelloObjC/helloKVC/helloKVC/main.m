//
//  main.m
//  helloKVC
//
//  Created by 飞 杨 on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface Student:NSObject
{
    NSString * studentName;
    int age;
    int Age;
}
@property (assign) NSString * sName;
@property int age;
@property int Age;
@end


@implementation Student
@synthesize sName = studentName;  //属性名与字段名不同。
@synthesize age;
@synthesize Age;
@end


@interface Class1 : NSObject
{
    int f1;
    int f2;
}
@end

@implementation Class1
@end

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        // insert code here...
        NSLog(@"Hello, World!");
        Student * s = [Student new];
        [s setValue:@"namevalue" forKey:@"sName"];
        [s setValue:[NSNumber numberWithInt:10] forKey:@"Age"];  //此处设置的是小写的age
        NSLog(@"Name:%@",[s sName]);
        NSLog(@"age:%@",[s valueForKey:@"age"]);   //此处取出了10；
        NSLog(@"age:%d",[s Age]);//取出了0.
        
        Class1 * obj1 = [Class1 new];
        [obj1 setValue:[NSNumber numberWithInt:10] forKey:@"f1"];
        NSLog(@"f1:%@",[obj1 valueForKey:@"f1"]);
        Class1 * obj2 = [Class1 new];
        [obj2 setValue:[NSNumber numberWithInt:20] forKey:@"f1"];
        NSLog(@"f1:%@",[obj2 valueForKey:@"f1"]);
        
        NSArray *arr = [NSArray arrayWithObjects:obj1,obj2,nil];
        //[arr count]
        
        //平均
        NSLog(@"avg:%@",[arr valueForKeyPath:@"@avg.f1"]);
        //求和
        NSLog(@"sum:%@",[arr valueForKeyPath:@"@sum.f1"]);
    }
    return 0;
}


//属性大小写问题还需要仔细研究。

