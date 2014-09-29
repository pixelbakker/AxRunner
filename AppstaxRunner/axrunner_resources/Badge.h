//
//  Badge.h
//  AppstaxRunner
//
//  Created by Leif-Arne Bakker on 29/09/14.
//  Copyright (c) 2014 Leif-Arne Bakker. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface Badge : NSObject

@property (strong, nonatomic) NSString *name;
@property (strong, nonatomic) NSString *imageName;
@property (strong, nonatomic) NSString *information;
@property float distance;

@end
