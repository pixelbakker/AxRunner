//
//  HomeViewController.m
//  AppstaxRunner
//
//  Created by Leif-Arne Bakker on 26/09/14.
//  Copyright (c) 2014 Leif-Arne Bakker. All rights reserved.
//

#import "HomeViewController.h"
#import "NewRunViewController.h"
#import <AppStax/AppStax.h>

@interface HomeViewController ()

@property(nonatomic, weak) IBOutlet UIButton *logoutButton;

@end

@implementation HomeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    // This example just sets the background color
    
    [AXUser requireLogin:^(AXUser *user) {
        
    } withCustomViews:^(AXLoginViews *views) {
        views.signup.backgroundColor = [UIColor whiteColor];
        views.login.backgroundColor  = [UIColor whiteColor];
    }];
}

- (IBAction)logoutPressed:(id)sender {
    [AXUser logout];
    [AXUser requireLogin:^(AXUser *user) {
        
    } withCustomViews:^(AXLoginViews *views) {
        views.signup.backgroundColor = [UIColor whiteColor];
        views.login.backgroundColor  = [UIColor whiteColor];
    }];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    UIViewController *nextController = [segue destinationViewController];
    
    if ([nextController isKindOfClass:[NewRunViewController class]]) {
        ((NewRunViewController *) nextController).managedObjectContext = self.managedObjectContext;
    }
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
