//
//  Document.h
//  RaiseMan
//
//  Created by 飞 杨 on 12-4-10.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface MyDocument : NSDocument
{
    NSMutableArray *employees;
}
- (void)setEmployees:(NSMutableArray *)a;
@end

@interface MyDoc : NSDocument
{
}
@end
