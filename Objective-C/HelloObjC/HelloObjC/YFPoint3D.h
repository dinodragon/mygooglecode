//
//  YFPoint3D.h
//  HelloObjC
//
//  Created by 飞 杨 on 12-3-19.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#import "YFPoint2D.h"

@interface YFPoint3D : YFPoint2D
{
    int z;
}

-(void) setZ:(int)z;
-(void) show;
-(void) setX:(int)a_ setY:(int)b_ setZ:(int)z_;
@end
