//
//  Location.h
//  AppstaxRunner
//
//  Created by Leif-Arne Bakker on 26/09/14.
//  Copyright (c) 2014 Leif-Arne Bakker. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreData/CoreData.h>

@class Run;

@interface Location : NSManagedObject

@property (nonatomic, retain) NSNumber * latitude;
@property (nonatomic, retain) NSNumber * longitude;
@property (nonatomic, retain) NSDate * timestamp;
@property (nonatomic, retain) Run *run;

@end
