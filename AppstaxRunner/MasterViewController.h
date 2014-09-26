//
//  MasterViewController.h
//  AppstaxRunner
//
//  Created by Leif-Arne Bakker on 26/09/14.
//  Copyright (c) 2014 Leif-Arne Bakker. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreData/CoreData.h>

@interface MasterViewController : UITableViewController <NSFetchedResultsControllerDelegate>

@property (strong, nonatomic) NSFetchedResultsController *fetchedResultsController;
@property (strong, nonatomic) NSManagedObjectContext *managedObjectContext;


@end

