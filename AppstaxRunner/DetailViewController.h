//
//  DetailViewController.h
//  AppstaxRunner
//
//  Created by Leif-Arne Bakker on 26/09/14.
//  Copyright (c) 2014 Leif-Arne Bakker. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DetailViewController : UIViewController

@property (strong, nonatomic) id detailItem;
@property (weak, nonatomic) IBOutlet UILabel *detailDescriptionLabel;

@end

