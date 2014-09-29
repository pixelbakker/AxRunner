
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/** The AXLoginViews class is used in [AXUser requireLogin:withCustomViews:] to customize the appearance of the signup and login screens.
 
 A thorough introduction and guide to handling users is available at [appstax.com/docs/](https://appstax.com/docs/iOS_Guide.html)
 */
@interface AXLoginViews : NSObject

/** Set properties or assign a completely different UIView instance to this property to change the background for the login screen. */
@property UIView *login;

/** Set properties or assign a completely different UIView instance to this property to change the background for the signup screen. */
@property UIView *signup;

@end
