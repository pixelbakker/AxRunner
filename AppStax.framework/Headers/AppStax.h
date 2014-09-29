
#import <Foundation/Foundation.h>
#import <AppStax/AXObject.h>
#import <AppStax/AXUser.h>


/** Welcome to Appstax! 
 A thorough introduction and guide to using this service is available at [appstax.com/docs/](https://appstax.com/docs/iOS_Guide.html)
 
 In this class you use setAppKey: to initialize your app.
 Sign up at [appstax.com](http://appstax.com/) to obtain your key.
 */
@interface AppStax : NSObject

/** Specifies your AppKey. 
 
Call this method from application:didFinishLaunchingWithOptions: in your AppDelegate before making any other calls to AppStax APIs.
 
 Log in to http://appstax.com to find your key.
 
 @param appKey The AppKey
 */
+ (void)setAppKey:(NSString *)appKey;

/** Access the AppStax.bundle
 
 */
+ (NSBundle *)frameworkBundle;

@end