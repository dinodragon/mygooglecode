//
//  YFPoint2D.h
//  helloproperty
//
//  Created by 飞 杨 on 12-3-22.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface YFPoint2D : NSObject
{
    int x;
    int y;
    int type;
}

@property int x;
@property int y;
@property int typeValue;

@end

@interface YFPoint2D(YFPrinter)
-(void) show;
@end
