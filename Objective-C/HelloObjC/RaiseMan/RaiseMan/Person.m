//
//  Person.m
//  RaiseMan
//
//  Created by 飞 杨 on 12-4-12.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "Person.h"

@implementation Person

- (id)init
{
    [super init];
    expectedRaise = 0.1;
    personName = @"New Person";
    return self;
}
- (void)dealloc
{
    [personName release];
    [super dealloc];
}
@synthesize personName;
@synthesize expectedRaise;

- (void)setNilValueForKey:(NSString *)key
{
    if ([key isEqual:@"expectedRaise"]) {
        [self setExpectedRaise:0.0];
    } else {
        [super setNilValueForKey:key];
    }
}

@end
