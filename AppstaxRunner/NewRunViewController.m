//
//  NewRunViewController.m
//  AppstaxRunner
//
//  Created by Leif-Arne Bakker on 26/09/14.
//  Copyright (c) 2014 Leif-Arne Bakker. All rights reserved.
//

#import "NewRunViewController.h"
#import "Run.h"
#import <CoreLocation/CoreLocation.h>
#import "MathController.h"
#import "Location.h"
#import <MapKit/MapKit.h>
#import <AppStax/AppStax.h>

static NSString *const detailSegueName = @"RunDetails";

@interface NewRunViewController () <UIActionSheetDelegate, CLLocationManagerDelegate, MKMapViewDelegate>

@property int seconds;
@property float distance;
@property (nonatomic, strong) CLLocationManager *locationManager;
@property (nonatomic, strong) NSMutableArray *locations;
@property (nonatomic, strong) NSTimer *timer;

@property (nonatomic, strong) Run *run;

@property(nonatomic, weak) IBOutlet UILabel *promptLabel;
@property(nonatomic, weak) IBOutlet UILabel *timeLabel;
@property(nonatomic, weak) IBOutlet UILabel *distLabel;
@property(nonatomic, weak) IBOutlet UILabel *paceLabel;

@property(nonatomic, weak) IBOutlet UIButton *startButton;
@property(nonatomic, weak) IBOutlet UIButton *stopButton;

@property (nonatomic, weak) IBOutlet MKMapView *mapView;

@end

@implementation NewRunViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void) viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    self.startButton.hidden = NO;
    self.promptLabel.hidden = NO;
    
    self.timeLabel.text = @"";
    self.timeLabel.hidden = YES;
    self.distLabel.hidden = YES;
    self.paceLabel.hidden = YES;
    self.stopButton.hidden = YES;
    self.mapView.hidden = YES;

}

- (void)viewWillDisappear:(BOOL)animated
{
    [super viewWillDisappear:animated];
    [self.timer invalidate];
}

- (void)locationManager:(CLLocationManager *)manager
     didUpdateLocations:(NSArray *)locations
{
    
    for (CLLocation *newLocation in locations) {
        
        NSDate *eventDate = newLocation.timestamp;
        
        NSTimeInterval howRecent = [eventDate timeIntervalSinceNow];
        
        if (abs(howRecent) < 10.0 && newLocation.horizontalAccuracy < 20) {
            
            NSString *pace = [MathController stringifyAvgPaceFromDist:self.distance overTime:self.seconds];
            NSString *dist = [MathController stringifyDistance:self.distance];
            
            NSString *time = [MathController stringifySecondCount:self.seconds usingLongFormat:NO];
            AXObject *axRun = [AXObject create:@"AppstaxRun"];
            axRun[@"Pace"]  = pace;
            axRun[@"Distance"] = dist;
            axRun[@"Time"] = time;
            
            
            
            // update distance
            if (self.locations.count > 0) {
                self.distance += [newLocation distanceFromLocation:self.locations.lastObject];
                
                CLLocationCoordinate2D coords[2];
                coords[0] = ((CLLocation *)self.locations.lastObject).coordinate;
                coords[1] = newLocation.coordinate;
                
                NSNumber *longitude = @((CLLocationDegrees)coords[1].longitude);
                NSNumber *latitude = @((CLLocationDegrees)coords[1].latitude);
                
                NSDictionary *dict = [[NSDictionary alloc] initWithObjectsAndKeys: @([newLocation.timestamp timeIntervalSince1970]), @"timestamp", longitude, @"Longitude", latitude, @"Latitude", nil];
                
                NSData *json = [NSJSONSerialization dataWithJSONObject:dict options:NSJSONWritingPrettyPrinted error:nil];
                
                axRun[@"LocationData"] = [[NSString alloc] initWithData:json encoding:NSUTF8StringEncoding];
                
                MKCoordinateRegion region =
                MKCoordinateRegionMakeWithDistance(newLocation.coordinate, 1500, 1500);
                [self.mapView setRegion:region animated:YES];
                
                [self.mapView addOverlay:[MKPolyline polylineWithCoordinates:coords count:2]];
            }
            //Save object to Appstax
            [axRun save];
            [self.locations addObject:newLocation];
        }
    }
}

- (MKOverlayRenderer *)mapView:(MKMapView *)mapView rendererForOverlay:(id < MKOverlay >)overlay
{
    if ([overlay isKindOfClass:[MKPolyline class]]) {
        MKPolyline *polyLine = (MKPolyline *)overlay;
        MKPolylineRenderer *aRenderer = [[MKPolylineRenderer alloc] initWithPolyline:polyLine];
        aRenderer.strokeColor = [UIColor blueColor];
        aRenderer.lineWidth = 3;
        return aRenderer;
    }
    return nil;
}

- (void)startLocationUpdates
{
    // Create the location manager if this object does not
    // already have one.
    if (self.locationManager == nil) {
        self.locationManager = [[CLLocationManager alloc] init];
    }
    
    self.locationManager.delegate = self;
    self.locationManager.desiredAccuracy = kCLLocationAccuracyBest;
    self.locationManager.activityType = CLActivityTypeFitness;
    
    // Movement threshold for new events.
    self.locationManager.distanceFilter = 10; // meters
    
    [self.locationManager requestWhenInUseAuthorization];
    [self.locationManager startUpdatingLocation];
}

- (void)saveRun
{
    Run *newRun = [NSEntityDescription insertNewObjectForEntityForName:@"Run"
                                                inManagedObjectContext:self.managedObjectContext];
    
    newRun.distance = [NSNumber numberWithFloat:self.distance];
    newRun.duration = [NSNumber numberWithInt:self.seconds];
    newRun.timestamp = [NSDate date];
    
    NSMutableArray *locationArray = [NSMutableArray array];
    for (CLLocation *location in self.locations) {
        Location *locationObject = [NSEntityDescription insertNewObjectForEntityForName:@"Location"
                                                                 inManagedObjectContext:self.managedObjectContext];
        
        locationObject.timestamp = location.timestamp;
        locationObject.latitude = [NSNumber numberWithDouble:location.coordinate.latitude];
        locationObject.longitude = [NSNumber numberWithDouble:location.coordinate.longitude];
        [locationArray addObject:locationObject];
    }
    
    newRun.locations = [NSOrderedSet orderedSetWithArray:locationArray];
    self.run = newRun;
    
    // Save the context.
    NSError *error = nil;
    if (![self.managedObjectContext save:&error]) {
        NSLog(@"Unresolved error %@, %@", error, [error userInfo]);
        abort();
    }
}


- (void)eachSecond
{
    self.seconds++;
    self.timeLabel.text = [NSString stringWithFormat:@"Time: %@",  [MathController stringifySecondCount:self.seconds usingLongFormat:NO]];
    self.distLabel.text = [NSString stringWithFormat:@"Distance: %@", [MathController stringifyDistance:self.distance]];
    self.paceLabel.text = [NSString stringWithFormat:@"Pace: %@",  [MathController stringifyAvgPaceFromDist:self.distance overTime:self.seconds]];
}

- (IBAction)startPressed:(id)sender
{
    //hide the start UI
    self.startButton.hidden = YES;
    self.promptLabel.hidden = YES;
    
    // show the running UI
    self.timeLabel.hidden = NO;
    self.distLabel.hidden = NO;
    self.paceLabel.hidden = NO;
    self.stopButton.hidden = NO;
    self.mapView.hidden = NO;
    
    self.seconds = 0;
    self.distance = 0;
    self.locations = [NSMutableArray array];
    self.timer = [NSTimer scheduledTimerWithTimeInterval:(1.0) target:self
                                                selector:@selector(eachSecond) userInfo:nil repeats:YES];
    NSLog(@"About to start location manager");
    [self startLocationUpdates];

}

- (IBAction)stopPressed:(id)sender {
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"" delegate:self cancelButtonTitle:@"Cancel" destructiveButtonTitle:nil otherButtonTitles:@"Save",@"Discard", nil];

    [actionSheet showInView:self.view];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex {
     [self.locationManager stopUpdatingLocation];
    //save
    if (buttonIndex == 0) {
         [self saveRun]; ///< ADD THIS LINE
        [self performSegueWithIdentifier:detailSegueName sender:nil];
    } else if (buttonIndex == 1) {
        [self.navigationController popToRootViewControllerAnimated:YES];
    }
}

- (void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    [[segue destinationViewController] setRun:self.run];
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
